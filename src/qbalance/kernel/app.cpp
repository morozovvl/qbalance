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
#include <QPaintEngine>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "../gui/guifactory.h"
#include "../gui/passwordform.h"
#include "../gui/formgrid.h"
#include "../gui/mainwindow.h"
#include "../gui/configform.h"
#include "../gui/tableview.h"
#include "../engine/documentscriptengine.h"


QFile*  TApplication::DebugFile        = new QFile(QDir::currentPath() + "/" + TApplication::debugFileName());
//QTextStream* TApplication::DebugStream = new QTextStream(TApplication::DebugFile);
int    TApplication::DebugMode         = 0;
TApplication* TApplication::Exemplar   = 0;
QString TApplication::userName         = "";



TApplication::TApplication(int & argc, char** argv)
    : QApplication(argc, argv)
{
    setOrganizationName("Enterprise");
    setApplicationName("QBalance");
    setApplicationVersion("0.0.1");
    setWindowIcon(QIcon(":qbalance.ico"));

    db  = new DBFactory();
    gui = new GUIFactory(db);

    dictionaryList = 0;
    topersList = 0;
    driverFR = new DriverFR(this);
    barCodeReader = new BarCodeReader(this, config.barCodeReaderPort);

    driverFRisValid = false;
    driverFRlocked = false;
    fsWebCamIsValid = true;                     // Поначалу будем считать, что утилита fsWebCam установлена

    reportTemplateType = OOXMLreportTemplate;

    cardReaderCode = "";                        // Прочитанный код на магнитной карте

    if (!Exemplar)
    {
        Exemplar = this;
    }
    initConfig();
}


TApplication::~TApplication()
{
    delete driverFR;
    delete gui;
    delete db;
}


void TApplication::initConfig()
{
#ifdef Q_OS_WIN32
    config.barCodeReaderPort = "COM3";                  // COM-порт сканера штрих кодов в Windows
    config.frDriverPort = 3;                            // COM-порт фискального регистратора
    config.frDriverBaudRate = 6;
#else
    config.barCodeReaderPort = "/dev/ttyUSB0";          // COM-порт сканера штрих кодов в Linux
    config.frDriverPort = 1;                            // COM-порт фискального регистратора
    config.frDriverBaudRate = 6;
#endif
    config.frDriverPassword = 30;
    config.cardReaderPrefix = ";8336322632=";           // Префикс магнитной карты
    config.localPort = 44444;
    config.remoteHost = "192.168.0.1";
    config.remotePort = 44444;
}


Documents* TApplication::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {
        Documents* doc = new Documents(opNumber);
        if (!doc->open())
            return 0;
        doc->query();
        doc->getGridTable()->selectRow(doc->getTableModel()->rowCount() - 1);
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
    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);
    if (gui->open())
    {  // Попытаемся открыть графический интерфейс
//        formLoader = new QUiLoader(gui);
//        formLoader->addPluginPath(applicationDirPath() + "/plugins");
//        formLoader->setWorkingDirectory(getFormsPath());

        pid = QCoreApplication::applicationPid();

        messagesWindow = new MessageWindow();

        tcpServer = new TcpServer(config.localPort, this);

        if (driverFR->open(config.frDriverPort, config.frDriverBaudRate, config.frDriverPassword, config.remoteHost, config.remotePort))
        {
            driverFRisValid = true;
        }

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

                    // Загрузим константы
                    Dictionary* constDict = dictionaryList->getDictionary(db->getObjectName("константы"), true);
                    if (constDict != 0)
                    {
                        constDict->setPhotoEnabled(false);
                        constDict->query();
                    }

                    // Загрузим счета
                    Dictionary* accDict = dictionaryList->getDictionary(db->getObjectName("счета"), true);
                    if (accDict != 0)
                    {
                        accDict->setPhotoEnabled(false);
                    }

                    secDiff = QDateTime::currentDateTime().secsTo(db->getValue("SELECT now();", 0, 0).toDateTime());

                    if (driverFRisValid && driverFR->Connect())
                    {
                        showMessageOnStatusBar("Найден фискальный регистратор.");
                        if (!driverFR->isRemote())  // Если фискальник подсоединен к этому компьютеру
                            driverFR->Beep();       // То выдадим сигнал о подключении компьютера к фискальнику
                        driverFR->DisConnect();
                    }
                    else
                    {
                        driverFRisValid = false;
                        showMessageOnStatusBar("Фискальный регистратор не найден.");
                    }

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


void TApplication::close()
{
//    delete formLoader;
    if (driverFR)
    {
        driverFR->close();
    }

    delete tcpServer;

    delete messagesWindow;

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
    return getAnyPath("forms", formName);
}


QString TApplication::getScriptsPath() {
    return getAnyPath("scripts");
}


QString TApplication::getReportsPath(QString reportName) {
    return getAnyPath("reports", reportName);
}


QString TApplication::getPhotosPath(QString photoName) {
    return getAnyPath("photos", photoName);
}


QString TApplication::getAnyPath(QString subPath, QString fName)
{
    QString dir = applicationDirPath() + "/" + subPath + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += getConfigPrefix() + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + fName;
    return fileName;

}


Dialog* TApplication::createForm(QString fileName)
{
    QPointer<Dialog> formWidget = 0;
    QString path = getFormsPath();
    QString fName = fileName + ".ui";
    if (!Essence::getFile(path, fName, FormFileType))
    {
        fName = fileName + ".ui";
        if (!Essence::getFile(path, fName, FormFileType))
            fName = "";
    }
    if (fName.size() > 0)
    {
        QFile file(path + fName);
        if (file.open(QIODevice::ReadOnly))
        {
            QUiLoader formLoader(gui);
            formLoader.addPluginPath(applicationDirPath() + "/plugins");
            formLoader.setWorkingDirectory(getFormsPath());

//          formWidget = qobject_cast<Dialog*>(formLoader.load(&file));
            formWidget = (Dialog*)(formLoader.load(&file));
            file.close();
            if (formWidget != 0)
            {
                if (QString::compare(formWidget->metaObject()->className(), "Dialog",  Qt::CaseSensitive) != 0)
                {
                    showError(QString(QObject::trUtf8("Загружаемая форма %1 должна иметь тип Dialog.")).arg(fileName));
                    return 0;
                }
//                formWidget->setApp(this);
                formWidget->findCmdOk();
//                formWidget->findCmdCancel();
            }
        }
    }
    return formWidget;
}


Form* TApplication::createNewForm(QString fileName)
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


bool TApplication::setDebugMode(const int& value)
{
    bool result = true;
    DebugMode = value;
    return result;
}


void TApplication::debug(int mode, const QString& value)
{
    if (debugMode() == mode || mode == 0)
    {
        QFile file(debugFileName());
        if (file.open(QFile::WriteOnly | QFile::Append))
        {
            QTextStream out(&file);
            if (file.size() == 0)
                out << QDateTime::currentDateTime().toString(logTimeFormat()) << " Program startup.\n";
            out << QDateTime::currentDateTime().toString(logTimeFormat()) << " " << value << "\n";
        }
        file.close();
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
    debug(0, "Error: " + error + "\n");
}


void TApplication::showCriticalError(QString error)
{
    gui->showCriticalError(error);
    debug(0, "Error: " + error + "\n");
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


QProcess* TApplication::runProcess(QString command, QString progName, bool show_Error)
{
    QProcess* ooProcess = new QProcess();
    ooProcess->start(command);
    if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning) && show_Error)
    {   // Подождем 1 секунду и если процесс не запустился
        showError(QString(QObject::trUtf8("Не удалось запустить %1 ")).arg(progName.size() > 0 ? progName : QObject::trUtf8("программу")));                   // выдадим сообщение об ошибке
        return 0;
    }
    return ooProcess;
}


bool TApplication::waitProcessEnd(QProcess* proc)
{   // Процедура ждет окончания процесса или истечения 10 секунд
    bool result = true;
    QTimer t;
    t.start(10000);
    QEventLoop loop;
    connect(&t, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), &loop, SLOT(quit()));
    loop.exec();
    if (proc->exitStatus() != QProcess::NormalExit)
        result = false;
    delete proc;
    return result;
}


void TApplication::timeOut(int ms)
{
    QTimer t;
    t.start(ms);
    QEventLoop loop;
    connect(&t, SIGNAL(timeout()), &loop, SLOT(quit()));
    loop.exec();
}


void TApplication::showProcesses()
{
/*
    QDir dir = QDir(getScriptsPath());
    QString ext = ".qs";
    QStringList files;
    // Получим шаблоны с сервера
    QStringList fs = db->getFilesList("", ScriptFileType, true);
    foreach (QString f, fs)
    {
        if (!files.contains(f))
            files << f;
    }

    // Получим список локальных шаблонов отчетов
    fs = dir.entryList(QStringList("*" + ext), QDir::Files, QDir::Name);
    foreach (QString f, fs)
    {
        if (!files.contains(f))
        {
            files << f;
            Essence::getFile(getScriptsPath(), f, ScriptFileType);
        }
    }
*/
    runScript("analizeBankAccount");
}


void TApplication::runScript(QString scriptName)
{
    ScriptEngine* scriptEngine;
    scriptEngine = new ScriptEngine();
    if (scriptEngine->open())
    {
        scriptEngine->evaluate(QString("evaluateScript(\"%1.js\")").arg(scriptName));
        scriptEngine->close();
    }
    delete scriptEngine;
}


void TApplication::barCodeReadyRead(QString barCodeString)
{
    Dialog* dialog = 0;
    QWidget* widget = activeWindow();
    if (QString(widget->metaObject()->className()).trimmed().compare("Dialog", Qt::CaseInsensitive) == 0)
    {
        dialog = qobject_cast<Dialog*>(widget);
    }
    else
    {
        if (getActiveSubWindow() != 0 && getMainWindow() != 0)
        {
            MyMdiSubWindow* mdiSubWindow = getMainWindow()->findMdiWindow(getActiveSubWindow()->widget());
            if (mdiSubWindow != 0)
            {
                dialog = qobject_cast<Dialog*>(mdiSubWindow->widget());
            }
        }
    }
    if (dialog != 0)
        dialog->getForm()->getParent()->keyboardReaded(barCodeString.trimmed());
}


bool TApplication::readCardReader(QKeyEvent* keyEvent)
{
    // Обработаем поступление с клавиатуры кодов кард-ридера
    QString text;

    if (keyEvent->key() == 59 || keyEvent->key() == 1046)   // Если это клавиша ";" в английской или русской раскладке
        text = ";";
    else
        text = keyEvent->text();

    cardReaderCode.append(text);
    int leftSize = cardReaderCode.size() <= config.cardReaderPrefix.size() ? cardReaderCode.size() : config.cardReaderPrefix.size();
    if (leftSize > 0 && (config.cardReaderPrefix.left(leftSize) == cardReaderCode.left(leftSize)))   // Если начальные введенные символы начинают совпадать с префиксом
    {                                                                // считывателя магнитных карт
        if (config.cardReaderPrefix == cardReaderCode.left(leftSize))       // Если префикс полностью совпал
        {
            if (keyEvent->key() == 44 || keyEvent->key() == 63)     // Последовательность заканчивается клавишей "?"
            {
                QString cardCode = cardReaderCode;
                cardCode.replace(config.cardReaderPrefix, "");
                cardCode.chop(1);
                emit cardCodeReaded(cardCode.trimmed());
                cardReaderCode = "";
            }
        }
        return true;                // Строка, вводимая с клавиатуры (кард-ридера) начинает походить на префикс карты
    }
    else
        cardReaderCode = "";
    return false;                   // Строка не похожа на префикс карты
}


void TApplication::capturePhoto(QString fileName, QString deviceName)
{
    if (fsWebCamIsValid)
    {
        QString localFile = applicationDirPath() + "/shot.jpg";
        QProcess* proc = runProcess(QString("fswebcam %1 -r 640x480 --jpeg 85 %2").arg(deviceName.size() != 0 ? "-d " + deviceName : "").arg(localFile), "fswebcam", false);
        if (proc != 0 && waitProcessEnd(proc))
            saveFileToServer(localFile, fileName, PictureFileType, true);
        fsWebCamIsValid = false;        // Утилита fsWebCam не установлена, не будем больше пытаться ее запускать
    }
}


void TApplication::saveFileToServer(QString file, QString localFile, FileType type, bool extend)
{
//    QString resultFileName;
    QFile file1(file);
    if (file1.exists() && file1.open(QIODevice::ReadOnly))
    {
        QByteArray array = file1.readAll();
        qulonglong localFileCheckSum = db->calculateCRC32(&array);
        qulonglong removeFileCheckSum = localFile.size() != 0 ? db->getFileCheckSum(localFile, type, extend) : 0;
        if (removeFileCheckSum != localFileCheckSum)    // контрольные суммы не совпадают, загрузим локальный файл в базу
                                                        // предполагается, что локальный файл свежее того, который в базе
        {
            db->setFile(localFile, type, array, extend);      // Сохранить картинку в расширенную базу
        }
        file1.close();
    }
}


void TApplication::saveFile(QString file, QByteArray* array)
{
    QString dir = QFileInfo(file).absolutePath();

    if (!QDir().exists(dir))
        QDir().mkdir(dir);

    QFile pictFile(file);
    if (pictFile.open(QIODevice::WriteOnly))
    {
        pictFile.write(*array);
        pictFile.close();
    }
}


void TApplication::print(QString str)
{
    messagesWindow->print(str);
}


void TApplication::printToArray(QString array, QString value)
{
    if (!arraysForPrint.contains(array))
        arraysForPrint.insert(array, QStringList());
    arraysForPrint[array].append(value);
}


void TApplication::printArray(QString array)
{
    foreach (QString val, arraysForPrint.value(array))
        messagesWindow->print(val);
}


void TApplication::clearPrintArrays()
{
    foreach (QString array, arraysForPrint.keys())
        arraysForPrint[array].clear();

}

QString TApplication::findFileFromEnv(QString file)
{
    QString result;
    QStringList sl(QProcessEnvironment::systemEnvironment().toStringList());
    int idx = sl.indexOf(QRegExp("^PATH=.*", Qt::CaseInsensitive));
    QString path = sl.value(idx).remove("PATH=", Qt::CaseInsensitive);
#ifdef Q_OS_WIN32
    QStringList sl1(path.split(";"));
#else
    QStringList sl1(path.split(":"));
#endif
    foreach (QString path, sl1)
    {
#ifdef Q_OS_WIN32
        result = path + "\\" + file;
#else
        result = path + "/" + file;
#endif
        if (QFile::exists(result))
            break;
    }
    return result;
}


void TApplication::saveCustomization()
{
    // Получим шаблоны с сервера
    QStringList fs = db->getFilesList("", ScriptFileType, false);
    foreach (QString f, fs)
    {
        qDebug() << f;
    }
}


