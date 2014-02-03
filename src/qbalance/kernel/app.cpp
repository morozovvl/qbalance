/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QtCore/QDate>
#include <QMessageBox>
#include <QtCore/QObject>
#include <QtCore/QTextCodec>
#include <QPushButton>
#include <QDebug>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "../gui/guifactory.h"
#include "../gui/passwordform.h"
#include "../gui/formgrid.h"
#include "../gui/mainwindow.h"
#include "../gui/configform.h"
#include "../../qextserialport/src/qextserialport.h"
#include "../engine/documentscriptengine.h"


QFile*  TApplication::DebugFile        = new QFile(QDir::currentPath() + "/" + TApplication::debugFileName());
QTextStream* TApplication::DebugStream = new QTextStream(TApplication::DebugFile);
bool    TApplication::DebugMode        = false;
TApplication* TApplication::Exemplar   = 0;



TApplication::TApplication(int & argc, char** argv)
    : QApplication(argc, argv)
{
    setOrganizationName("Enterprise");
    setApplicationName("QBalance");
    setApplicationVersion("0.0.1");
    setWindowIcon(QIcon(":qbalance.ico"));

    db  = new DBFactory();
    gui = new GUIFactory(db);

    formLoader = new QUiLoader(this);
    formLoader->addPluginPath(applicationDirPath() + "/plugins");
    formLoader->setWorkingDirectory(getFormsPath());

    dictionaryList = 0;
    topersList = 0;
    plugins = 0;
    driverFR = new DriverFR(this);

//456
/*
#ifdef Q_OS_WIN32
    barCodeReaderComPort = new QextSerialPort("COM3", QextSerialPort::EventDriven);
#else
    barCodeReaderComPort = new QextSerialPort("/dev/ttyUSB0", QextSerialPort::EventDriven);
#endif
*/

    barCodeString = "";
    driverFRisValid = false;

//    reportTemplateType = OOreportTemplate;   // модуль печати по умолчанию пока будет OOReportEngine, пока нет других
//    reportTemplateType = OpenRPTreportTemplate;
    reportTemplateType = OOXMLreportTemplate;

    if (!Exemplar)
    {
        Exemplar = this;
    }
}


TApplication::~TApplication()
{
    delete formLoader;
//456     delete barCodeReaderComPort;
    delete driverFR;
    delete gui;
    delete db;
}


Documents* TApplication::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {
        Documents* doc = new Documents(opNumber);
        if (!doc->open())
            return 0;
        doc->query();
        doc->getForm()->selectRow(doc->getTableModel()->rowCount() - 1);
        documents.insert(operName, doc);
    }
    return documents[operName];
}


void TApplication::removeDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (documents.contains(operName)) {
        Documents* doc = documents.value(operName);
        doc->close();
        documents.remove(operName);
    }
}


Dictionaries* TApplication::getDictionaries()
{
    return dictionaryList;
}


QString TApplication::getReportTemplateExt()
{
    switch (getReportTemplateType())
    {
        case OOreportTemplate:
            return "ods";
        case OOUNOreportTemplate:
            return "ods";
        case OOXMLreportTemplate:
            return "ods";
        case OpenRPTreportTemplate:
            return "xml";
    }
    return "";
}


bool TApplication::open() {
    bool lResult = false;   // По умолчанию будем считать, что приложение открыть не удалось
    if (debugMode())
    {
        TApplication::debug("Program startup.\n");
    }
    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);
    if (gui->open()) {  // Попытаемся открыть графический интерфейс
        forever         // Будем бесконечно пытаться открыть базу, пока пользователь не откажется
        {
            int result = gui->openDB(); // Попытаемся открыть базу данных
            if (result == 0)
            {   // БД открыть удалось
                dictionaryList = new Dictionaries();
                topersList = new Topers();
                if (dictionaryList->open() && topersList->open())
                {   // Удалось открыть спосок справочников и типовых операций
                    db->getPeriod(beginDate, endDate);
                    gui->getMainWindow()->showPeriod();
                    if (driverFR->open())
                        driverFRisValid = true;
//456
/*
                    if (barCodeReaderComPort != 0)
                    {
                        barCodeReaderComPort->setBaudRate(BAUD9600);
                        barCodeReaderComPort->setFlowControl(FLOW_OFF);
                        barCodeReaderComPort->setParity(PAR_NONE);
                        barCodeReaderComPort->setDataBits(DATA_8);
                        barCodeReaderComPort->setStopBits(STOP_2);
                        if (barCodeReaderComPort->open(QIODevice::ReadWrite))
                            connect(barCodeReaderComPort, SIGNAL(readyRead()), this, SLOT(barCodeReadyRead()));

                    }
*/

                    // Загрузим константы
                    Dictionary* constDict = dictionaryList->getDictionary(db->getObjectName("константы"));
                    if (constDict != 0)
                    {
                        constDict->setPhotoEnabled(false);
                        constDict->query();
                    }

                    QPluginLoader pluginLoader;
                    plugins = pluginLoader.instance();

                    lResult = true;     // Приложение удалось открыть
                    break;  // Выйдем из бесконечного цикла открытия БД
                }
            }
            else if (result == -2)
                {   // Произошла ошибка соединения с сервером
                if (gui->showMessage(QObject::trUtf8("Не удалось соединиться с базой данных (БД). Возможно БД отсутствует."),
                                     QObject::trUtf8("Попытаться создать новую БД?")) == QMessageBox::Yes)
                    // Попытаемся создать новую БД
                    db->createNewDBs(gui->getLastHostName(), gui->getLastDbName(), gui->getLastPort());
            }
            else if (result == -1)      // Пользователь нажал кнопку Отмена
                break;  // Выйдем из бесконечного цикла открытия БД
        }
    }
    return lResult;
}


void TApplication::close() {
    if (documents.count() > 0)
    {
        foreach(QString operName, documents.keys())
        {
            Documents* doc = documents.value(operName);
            doc->close();
            delete doc;
            documents.remove(operName);
        }
    }
    if (dictionaryList != 0)
    {
        dictionaryList->close();
        delete dictionaryList;
    }
    if (topersList != 0)
    {
        topersList->close();
        delete topersList;
    }
    if (gui != 0)
        gui->close();
    if (db != 0)
        db->close();
    if (debugMode())
    {
        TApplication::debug("Program shutdown.\n\n");
        TApplication::DebugFile->close();
    }
}


void TApplication::showMessageOnStatusBar(const QString &message, int timeout)
{
    gui->getMainWindow()->getStatusBar()->showMessage(message, timeout);
}


void TApplication::showConfigs() {
    ConfigForm* form = new ConfigForm();
    if (form->open(getMainWindow())) {
        form->exec();
        form->close();
    }
    delete form;
}


QString TApplication::getFormsPath(QString formName) {
    QString dir = applicationDirPath() + "/forms/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += getConfigPrefix() + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + formName;
    return fileName;
}


QString TApplication::getReportsPath(QString reportName) {
    QString dir = applicationDirPath() + "/reports/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += getConfigPrefix() + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + reportName;
    return fileName;
}


QString TApplication::getPhotosPath(QString photoName) {
    QString dir = applicationDirPath() + "/photos/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += getConfigPrefix() + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + photoName;
    return fileName;
}


Dialog* TApplication::createForm(QString fileName)
{
    Dialog* formWidget = 0;
    QString path = getFormsPath();
    QString fName = fileName + ".ui";
    if (!Essence::getFile(path, fName, FormFileType))
    {
        fName = getLogin() + "/" + fName;
        if (!Essence::getFile(path, fName, FormFileType))
            fName = "";
    }
    if (fName.size() > 0)
    {
        QFile file(path + fName);
        if (file.open(QIODevice::ReadOnly))
        {
            formWidget = (Dialog*)formLoader->load(&file);
            file.close();
            if (QString::compare(formWidget->metaObject()->className(), "Dialog",  Qt::CaseSensitive) != 0)
            {
                showError(QString(QObject::trUtf8("Загружаемая форма %1 должна иметь тип Dialog.")).arg(fileName));
                return 0;
            }
            formWidget->setApp(this);
            formWidget->findCmdOk();
        }
    }
    return formWidget;
}


Form* TApplication::createForm1(QString fileName)
{
    Form* form = new Form();
    if (form->open(getMainWindow()->centralWidget(), 0, fileName))
        return form;
    delete form;
    return 0;
}


QString TApplication::encoding()
{
    QString result("UTF-8");
    return result;
}


QTextCodec* TApplication::codec()
{
    return QTextCodec::codecForName(encoding().toLatin1());
}


bool TApplication::setDebugMode(const bool& value)
{
    bool result = true;
    if (value && !debugMode())
    {
        result = debugFile().open(QFile::WriteOnly | QFile::Append);
    }
    else if (!value && debugMode())
    {
        debugFile().close();
    }

    DebugMode = value;

    return result;
}


void TApplication::debug(const QString& value)
{
    if (debugMode())
    {
        TApplication::debugStream() << QDateTime::currentDateTime().toString(logTimeFormat()) << " " << value;
    }
}


TApplication* TApplication::exemplar()
{
    return Exemplar;
}


void TApplication::setIcons(QWidget* formWidget)
{
    QList<QPushButton*> widgets = formWidget->findChildren<QPushButton*>();
    for (int i = 0; i < widgets.size(); i++)
    {
        widgets.at(i)->setIcon(QIcon(":" + widgets.at(i)->objectName()));
    }
}


void TApplication::showError(QString error)
{
    gui->showError(error);
    debug("Error: " + error + "\n");
}


void TApplication::showCriticalError(QString error)
{
    gui->showCriticalError(error);
    debug("Error: " + error + "\n");
}


QVariant TApplication::getConst(QString valueName)
{
    QString constDictionaryName = db->getObjectName("константы");
    QString constNameField = db->getObjectName(constDictionaryName + ".имя");
    QString constValueField = db->getObjectName(constDictionaryName + ".значение");
    QString valName = valueName.trimmed();

    // Откроем справочник констант
    Dictionary* dict = dictionaryList->getDictionary(constDictionaryName);
    if (dict != 0)
    {
        MySqlRelationalTableModel* model = dict->getTableModel();
        for (int i = 0; i < model->rowCount(); i++)
        {
            QSqlRecord rec = model->record(i);
            if (QString().compare(rec.value(constNameField).toString().trimmed(), valName, Qt::CaseInsensitive) == 0)
                return rec.value(constValueField);
        }
    }
    return QVariant();
}


bool TApplication::runProcess(QString command, QString progName)
{
    QProcess* ooProcess = new QProcess();
    ooProcess->start(command);
    if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning))
    {   // Подождем 1 секунду и если процесс не запустился
        showError(QString(QObject::trUtf8("Не удалось запустить %1 ")).arg(progName.size() > 0 ? progName : QObject::trUtf8("программу")));                   // выдадим сообщение об ошибке
        return false;
    }
    return true;
}


void TApplication::barCodeReadyRead()
{
//456
//456     if (barCodeReaderComPort->bytesAvailable())
//456     {
//456         QString readedPart = QString::fromLatin1(barCodeReaderComPort->readAll());
//456         if (readedPart.right(1) == QString('\n'))
//456         {
//456             barCodeString.append(readedPart);

            if (getActiveSubWindow() != 0 && getMainWindow() != 0)
            {
                MyMdiSubWindow* mdiSubWindow = getMainWindow()->findMdiWindow(getActiveSubWindow()->widget());
                if (mdiSubWindow != 0)
                {
                    if (mdiSubWindow->isVisible())
                    {
                        Dialog* widget = qobject_cast<Dialog*>(mdiSubWindow->widget());
                        widget->getForm()->getParent()->keyboardReaded(barCodeString.trimmed());
                    }
                }
            }
//456             barCodeString = "";
//456         }
//456         else
//456             barCodeString.append(readedPart);
//456     }
}


void TApplication::showProcesses()
{
    ScriptEngine* scriptEngine;
    scriptEngine = new ScriptEngine(this);
    if (scriptEngine != 0)
    {
        if (scriptEngine->open("/home/vladimir/work/qbalance1/test.qs"))
        {
            if (scriptEngine->evaluate())
            {
            }
        }
    }
    delete scriptEngine;
}

