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
#include <QHttp>
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
QString TApplication::username         = "";
QString TApplication::password         = "";
QString TApplication::host             = "";
int TApplication::port                 = 0;
QString TApplication::database         = "";
QString TApplication::script           = "";
QString TApplication::scriptParameter  = "";


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
    driverFR = 0;
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

    connect(&timer, SIGNAL(timeout()), this, SLOT(setTimeIsOut()));
    timeIsOut = false;
    tcpServer = 0;
    scriptMode = false;
}


TApplication::~TApplication()
{
    delete gui;
    delete db;
}


void TApplication::initConfig()
{
#ifdef Q_OS_WIN32
    config.barCodeReaderPort = "COM3";                  // COM-порт сканера штрих кодов в Windows
    config.frDriverPort = "COM1";                       // COM-порт фискального регистратора
    config.frDriverBaudRate = 3;
#else
    config.barCodeReaderPort = "/dev/ttyUSB0";          // COM-порт сканера штрих кодов в Linux
    config.frDriverPort = "/dev/ttyUSB0";                 // COM-порт фискального регистратора
    config.frDriverBaudRate = 6;
#endif
    config.frDriverTimeOut = 50;
    config.frDriverPassword = 30;
    config.cardReaderPrefix = ";8336322632=";           // Префикс магнитной карты
    config.localPort = 44444;
    config.remoteHost = "192.168.0.1";
    config.remotePort = 44444;
    config.saveFormConfigToDB = true;
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

    readSettings();

    if (gui->open())
    {  // Попытаемся открыть графический интерфейс

        messagesWindow = new MessageWindow();
        tcpServer = new TcpServer(config.localPort, this);

        driverFR = new DriverFR(this);
        if (driverFR->open(config.frDriverPort, config.frDriverBaudRate, config.frDriverTimeOut, config.frDriverPassword, config.remoteHost, config.remotePort))
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
                {
                    // Удалось открыть спосок справочников и типовых операций
                    db->getPeriod(beginDate, endDate);
                    gui->getMainWindow()->showPeriod();

                    // Загрузим константы
                    Dictionary* constDict = dictionaryList->getDictionary(db->getObjectName("константы"));
                    if (constDict != 0)
                    {
                        constDict->setPhotoEnabled(false);
                        constDict->query();
                    }

                    // Загрузим счета
                    Dictionary* accDict = dictionaryList->getDictionary(db->getObjectName("счета"));
                    if (accDict != 0)
                    {
                        accDict->setPhotoEnabled(false);
                    }

                    secDiff = QDateTime::currentDateTime().secsTo(db->getValue("SELECT now();", 0, 0).toDateTime());

                    if (driverFRisValid)
                        showMessageOnStatusBar("Найден фискальный регистратор.\n");
                    else
                        showMessageOnStatusBar("Фискальный регистратор не найден.\n");

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
    saveMessages();
    writeSettings();

//    delete formLoader;
    if (driverFR)
    {
        driverFR->close();
        delete driverFR;
    }

    if (tcpServer != 0)
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
//      delete dictionaryList;
        dictionaryList->deleteLater();
    }
    if (topersList != 0)
    {
        topersList->close();
//        delete topersList;
        topersList->deleteLater();
    }
    if (gui != 0)
        gui->close();
    if (db != 0)
        db->close();
}


void TApplication::showMessageOnStatusBar(const QString &message, int timeout)
{
    if (scriptMode)
    {
        QTextStream(stdout) << message << "\r";
    }
    else
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
    QString dir = applicationDirPath() + "/data";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += "/" + getConfigPrefix();
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += "/" + subPath;
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + "/" + fName;
    return fileName;

}


Dialog* TApplication::createForm(QString fileName)
{
    QPointer<Dialog> formWidget = 0;
    QString path = getFormsPath();
    QString fName = fileName + ".ui";
    if (!Essence::getFile(path, fName, FormFileType))
        fName = "";
    if (fName.size() > 0)
    {
        QFile file(path + fName);
        if (file.open(QIODevice::ReadOnly))
        {
            QUiLoader formLoader(gui);
            formLoader.addPluginPath(applicationDirPath() + "/plugins/designer");
            formLoader.setWorkingDirectory(getFormsPath());

//            formWidget = qobject_cast<Dialog*>(formLoader.load(&file));
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


void TApplication::debug(int mode, const QString& value, bool timeIsEnabled)
{
    if (debugMode() == mode || mode == 0)
    {
        QFile file(debugFileName());
        if (file.open(QFile::WriteOnly | QFile::Append))
        {
            QTextStream out(&file);
            if (!timeIsEnabled)         // Если в строке не указано время, то укажем его
                out << QDateTime::currentDateTime().toString(logTimeFormat()) << " ";
            out << value << "\n";
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
    if (!isScriptMode())
        gui->showError(error);
    else
        showMessageOnStatusBar(error);      // В скриптовом режиме сообщение будет выведено в консоль
    debug(0, "Error: " + error + "\n");
}


void TApplication::showCriticalError(QString error)
{
    if (!isScriptMode())
        gui->showCriticalError(error);
    else
        showMessageOnStatusBar(error);      // В скриптовом режиме сообщение будет выведено в консоль
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
    timer.start(ms);
    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    loop.exec();
}


void TApplication::startTimeOut(int ms)
{
    timeIsOut = false;
    timer.start(ms);
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
    runScript("analizeBankAccount.js");
}


int TApplication::runScript(QString scriptName)
{
    int result = 0;
    ScriptEngine* scriptEngine;
    scriptEngine = new ScriptEngine();
    if (scriptEngine->open())
    {
        scriptEngine->evaluate(QString("evaluateScript(\"%1\")").arg(scriptName)).toInteger();
        result = scriptEngine->evaluate("scriptResult").toInteger();
        scriptEngine->close();
    }
    delete scriptEngine;
    showMessageOnStatusBar(QString(trUtf8("Скрипт %1 %2\n")).arg(scriptName).arg(result ? "выполнен" : "не выполнен"));
    if (isScriptMode())
        QTextStream(stdout) << "" << endl;
    return result;
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
        qulonglong remoteFileCheckSum = localFile.size() != 0 ? db->getFileCheckSum(localFile, type, extend) : 0;
        if (remoteFileCheckSum != localFileCheckSum)    // контрольные суммы не совпадают, загрузим локальный файл в базу
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


void TApplication::sendSMS(QString message)
{
    QEventLoop loop;
    QNetworkReply* reply;
    QNetworkAccessManager manager;
    QByteArray data;
    QString sms(message);
    reply = manager.get(QNetworkRequest(QUrl(sms)));
    connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << sms << reply->error() << reply->errorString() << QString(data);
}


void TApplication::readSettings()
{
    QSettings settings;
    settings.beginGroup("app");
    config.barCodeReaderPort = settings.value("barCodeReaderPort", config.barCodeReaderPort).toString();
    config.frDriverPort = settings.value("frDriverPort", config.frDriverPort).toString();
    config.frDriverBaudRate = settings.value("frDriverBaudRate", config.frDriverBaudRate).toInt();
    config.frDriverTimeOut = settings.value("frDriverTimeOut", config.frDriverTimeOut).toInt();
    config.frDriverPassword = settings.value("frDriverPassword", config.frDriverPassword).toInt();
    config.cardReaderPrefix = settings.value("cardReaderPrefix", config.cardReaderPrefix).toString();
    config.localPort = settings.value("localPort", config.localPort).toInt();
    config.remoteHost = settings.value("remoteHost", config.remoteHost).toString();
    config.remotePort = settings.value("remotePort", config.remotePort).toInt();
    config.saveFormConfigToDB = settings.value("saveFormConfigToDB", config.saveFormConfigToDB).toBool();
    settings.endGroup();
}


void TApplication::writeSettings()
{
    // Сохраним данные локально, на компьютере пользователя
    QSettings settings;
    settings.beginGroup("app");
    settings.setValue("barCodeReaderPort", config.barCodeReaderPort);
    settings.setValue("frDriverPort", config.frDriverPort);
    settings.setValue("frDriverBaudRate", config.frDriverBaudRate);
    settings.setValue("frDriverTimeOut", config.frDriverTimeOut);
    settings.setValue("frDriverPassword", config.frDriverPassword);
    settings.setValue("cardReaderPrefix", config.cardReaderPrefix);
    settings.setValue("localPort", config.localPort);
    settings.setValue("remoteHost", config.remoteHost);
    settings.setValue("remotePort", config.remotePort);
    settings.setValue("saveFormConfigToDB", config.saveFormConfigToDB);
    settings.endGroup();
}


void TApplication::saveMessages()
{
    QString text = messagesWindow->getTextEditor()->toPlainText();
    if (text.size() > 0)
    {
        QString fileName = getLogPath() + "/messages_" + QDate::currentDate().toString("dd_MM_yyyy");
        if (QDir().exists(fileName + ".log"))
        {
            for (int i = 1; true; i++)
            {
                QString fileName1 = QString("%1_%2").arg(fileName).arg(i);
                if (!QDir().exists(fileName1 + ".log"))
                {
                    fileName = fileName1;
                    break;
                }
            }
        }
        QFile file(fileName + ".log");
        if (file.open(QFile::WriteOnly | QFile::Append))
        {
            QTextStream out(&file);
            out << text << "\n";
        }
        file.close();
    }
}
