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
#include <QtGui/QFileDialog>
#include <QPushButton>
#include <QPaintEngine>
#include <QHttp>
#include <QFormBuilder>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "../gui/guifactory.h"
#include "../gui/passwordform.h"
#include "../gui/formgrid.h"
#include "../gui/mainwindow.h"
#include "../gui/configform.h"
#include "../engine/documentscriptengine.h"
#include "../storage/dbfactory.h"
#include "../bankterminal/bankterminal.h"
#include "../driverfr/driverfr.h"


QList<int>    TApplication::DebugModes;
TApplication* TApplication::Exemplar   = 0;
QString TApplication::username         = "";
QString TApplication::password         = "";
QString TApplication::host             = "";
int TApplication::port                 = 0;
QString TApplication::database         = "";
QString TApplication::script           = "";
QString TApplication::scriptParameter  = "";
bool TApplication::serverMode = false;
bool TApplication::sendCommandMode = false;
GUIFactory* TApplication::gui          = 0;
bool        TApplication::timeIsOut = false;
QTimer      TApplication::timer;




TApplication::TApplication(int & argc, char** argv)
    : QApplication(argc, argv)
{
    setOrganizationName("Enterprise");
    setApplicationName("QBalance");
    setApplicationVersion("0.0.1");
    setWindowIcon(QIcon(":qbalance.ico"));

    db  = 0;
    gui = 0;

    dictionaryList = 0;
    topersList = 0;
    driverFR = 0;
    barCodeReader = 0;
    barCodeReaded = false;
    bankTerminal = 0;

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
    DebugModes.clear();
    dirName = "";
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
    config.frDriverPort = "/dev/ttyUSB0";               // COM-порт фискального регистратора
    config.frDriverBaudRate = 6;
#endif
    config.frNeeded = false;
    config.frDriverTimeOut = 100;
    config.frLocalDriverTimeOut = 100;
    config.frRemoteDriverTimeOut = 150;
    config.frNetDriverTimeOut = 200;
    config.frDriverPassword = 30;
    config.cardReaderPrefix = ";8336322632=";           // Префикс магнитной карты
    config.localPort = 44444;
    config.remoteHost = "192.168.0.1";
    config.remotePort = 44444;
    config.saveFormConfigToDB = true;
    config.frConnectSignal = true;
}


Documents* TApplication::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {
        Documents* doc = new Documents(opNumber);
        if (!doc->open())
            return 0;
        doc->query();
        doc->getGrdTable()->selectRow(doc->getTableModel()->rowCount() - 1);
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
    gui = new GUIFactory();

    readSettings();

    // Если нужно и если есть соответствующий плагин, попытаемся открыть драйвер фискального регистратора
    if (config.frNeeded && !isScriptMode())
    {
        driverFR = (DriverFR*)createPlugin("driverfr");
        if (driverFR != 0)
        {
            driverFR->setApp(this);
            if (driverFR->open(config.frDriverPort, config.frDriverBaudRate, config.frDriverTimeOut, config.frDriverPassword, config.remoteHost, config.remotePort))
                    driverFRisValid = true;
            else
            {
                driverFR->close();
                driverFR = 0;
            }
        }
    }

    // Запустим сканер штрих-кодов, если есть его плагин
    barCodeReader = (BarCodeReader*)createPlugin("barcodereader");
    if (barCodeReader != 0)
    {
        barCodeReader->setApp(this);
        if (!barCodeReader->open(config.barCodeReaderPort))
        {
            barCodeReader->close();
            barCodeReader = 0;
        }
    }

    // Запустим банковский терминал, если есть плагин
    bankTerminal = (BankTerminal*)createPlugin("bankterminal");
    if (bankTerminal != 0)
    {
        bankTerminal->setApp(this);
        if (!bankTerminal->open())
        {
            bankTerminal->close();
            bankTerminal = 0;
        }
    }

    db  = new DBFactory();
    tcpServer = new TcpServer(config.localPort, this);
    messagesWindow = new MessageWindow();

    if (gui->open())
    {  // Попытаемся открыть графический интерфейс

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

                    if (config.frNeeded)
                    {
                        if (driverFRisValid)
                            showMessageOnStatusBar("Найден фискальный регистратор.\n");
                        else
                        {
                            if (driverFR->isLocked())
                                showMessageOnStatusBar("Фискальный регистратор занят. Не удалось соединиться.\n");
                            else
                                showMessageOnStatusBar("Фискальный регистратор не найден.\n");
                        }
                    }

                    db->clearLockedDocuementList();

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
        dictionaryList->deleteLater();
    }
    if (topersList != 0)
    {
        topersList->close();
        topersList->deleteLater();
    }
    if (gui != 0)
        gui->close();
    if (db != 0)
        db->close();
}


void TApplication::setFR()
{
/*
    driverFR = new DriverFR(this);
    if (driverFR->open(config.frDriverPort, config.frDriverBaudRate, config.frDriverTimeOut, config.frDriverPassword, config.remoteHost, config.remotePort))
    {
        driverFRisValid = true;
    }
*/
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


QString TApplication::getLogsPath() {
    return getAnyPath("/logs");
}


QString TApplication::getMessagesLogsPath(QString fileName)
{
    return getAnyPath("/logs", fileName);
}


QString TApplication::getFormsPath(QString fileName) {
    return getAnyPath("/forms", fileName);
}


QString TApplication::getScriptsPath(QString fileName) {
    return getAnyPath("/scripts", fileName);
}


QString TApplication::getReportsPath(QString fileName) {
    return getAnyPath("/reports", fileName);
}


QString TApplication::getPhotosPath(QString fileName) {
    return getAnyPath("/photos", fileName);
}


QString TApplication::getCrashDumpsPath() {
    return applicationDirPath() + "/data/crashdumps/";
}


QString TApplication::getAnyPath(QString subPath, QString fName)
{
    QString dir = applicationDirPath() + "/data";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += "/" + getConfigPrefix();
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += subPath;
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir;
    fileName += "/" + fName;
    return fileName;

}


QString TApplication::getConfigPrefix()
{
    if (db != 0 && db->isOpened())
        return QString("%1-%2-%3").arg(db->getHostName()).arg(db->getPort()).arg(db->getDatabaseName());
    return QString();
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
        if (file.exists() && file.open(QIODevice::ReadOnly))
        {
            QUiLoader formLoader(gui);
            formLoader.setWorkingDirectory(getFormsPath());
            formLoader.clearPluginPaths();
            formLoader.addPluginPath(applicationDirPath() + "/plugins/designer");

            formWidget = (Dialog*)(formLoader.load(&file));
            file.close();
            if (formWidget != 0)
            {
                if (QString::compare(formWidget->metaObject()->className(), "Dialog",  Qt::CaseSensitive) != 0)
                {
                    showError(QString(QObject::trUtf8("Загружаемая форма %1 должна иметь тип Dialog.")).arg(fileName));
                    return 0;
                }
                formWidget->findCmdOk();
            }
        }
    }
    return formWidget;
}


QObject* TApplication::createPlugin(QString fileName)
{
    QObject* result = 0;
    QString pluginFile = applicationDirPath() + "/plugins/lib" + fileName;
#ifdef Q_OS_WIN32
    pluginFile.append(".dll");
#else
    pluginFile.append(".so");
#endif
    if (QDir().exists(pluginFile))
    {
        QPluginLoader loader(pluginFile);
        loader.setLoadHints(QLibrary::ResolveAllSymbolsHint);
        loader.load();
        if (loader.isLoaded())
        {
            result = loader.instance();
        }
        else
            showError(loader.errorString());
    }
    return result;
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


void TApplication::setDebugMode(const int& value)
{
    DebugModes.append(value);
}


void TApplication::debug(int mode, const QString& value, bool timeIsEnabled)
{
    for (int i = 0; i < DebugModes.count(); i++)
    {
        if (DebugModes.at(i) == mode)
        {
            QFile file(debugFileName(DebugModes.at(i)));
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
        showMessageOnStatusBar(error + "\n");      // В скриптовом режиме сообщение будет выведено в консоль
    debug(0, "Error: " + error);
    for (int i = scriptStack.count(); i > 0; i--)
    {
        QString scriptName = scriptStack.at(i - 1)->getScriptFileName();
        if (scriptName.size() > 0)
            debug(0, QString("Script: %1").arg(scriptName));
    }
//    if (gui->getMainWindow() != 0)
//        gui->getMainWindow()->getWorkSpace()->activeSubWindow()->setFocus();
}


void TApplication::showCriticalError(QString error)
{
    if (!isScriptMode())
        gui->showCriticalError(error);
    else
        showMessageOnStatusBar(error + "\n");      // В скриптовом режиме сообщение будет выведено в консоль
    debug(0, "Error: " + error);
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
    QTimer timer;
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


void TApplication::sleep(int ms)
{
    QTime timer;
    timer.start();
    do
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, ms);
    } while (timer.elapsed() < ms);
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
    if (!sendCommandMode)
    {
        ScriptEngine* scriptEngine;
        scriptEngine = new ScriptEngine();
        if (scriptEngine->open())
        {
            scriptEngine->evaluate(QString("evaluateScript(\"%1\")").arg(scriptName)).toInteger();
            result = scriptEngine->evaluate(QString("scriptResult")).toInteger();
            scriptEngine->close();
        }
        delete scriptEngine;
        QString message = QString(trUtf8("Скрипт %1 %2")).arg(scriptName).arg(result ? "выполнен" : "не выполнен");
        if (isScriptMode())
        {
            QTextStream(stdout) << message << endl;
            debug(0, message);
        }
        else
            showMessageOnStatusBar(message);
    }
    else
    {
        TcpClient tcpcl(host, port);
        if (tcpcl.isValid())
        {
            if (tcpcl.sendToServer(script))
            {
                if (tcpcl.waitResult())
                {
                    QString res = tcpcl.getResult();
                    showMessageOnStatusBar(res);
                }
                else
                    showError(QString("Нет ответа от хоста %1").arg(host));
            }
            else
                showError(QString("Не удалось послать команду хосту %1").arg(host));
        }
        else
            showError(QString("Не удалось подключиться к хосту %1").arg(host));
    }
    return result;
}


void TApplication::barCodeReadyRead(QString barCodeString)
{
    barCodeReaded = true;
    Dialog* dialog = 0;
    if (getActiveSubWindow() != 0)
        dialog = (Dialog*)(getActiveSubWindow()->widget());
    if (dialog != 0)
        dialog->getForm()->getParent()->keyboardReaded(barCodeString.trimmed());
    barCodeReaded = false;
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


int TApplication::printArrayCount(QString array)
{
    return arraysForPrint.value(array).count();
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


void TApplication::loadFile()
{
    if (isSA())
    {
        dirName = "scriptLoadDir";
        QString fileName = getOpenFileName(gui->getMainWindow(), "Откройте файл для загрузки", "", tr("Scripts (*.js *.qs)"));
        if (fileName.size() > 0)
        {
            QFileInfo fi(fileName);
            saveFileToServer(fileName, fi.fileName(), ScriptFileType);
        }
    }
}


QString TApplication::getOpenFileName(QWidget* parent, QString caption, QString dir, QString filter, QString* selectedFilter, QFileDialog::Options options)
{
    if (dir.size() == 0)
    {
        if (dirName.size() > 0)
           dir = dirs.value(dirName);
        if (dir.size() == 0)
           dir = QDir::currentPath();
    }

    QString fileName = QFileDialog::getOpenFileName(parent, caption, dir, filter, selectedFilter, options);
    if (fileName.size() > 0)
    {
        if (dirName.size() > 0)
        {
            dirs.remove(dirName);
            dirs.insert(dirName, fileName);
        }
    }
    dirName = "";
    return fileName;
}


void TApplication::sendSMS(QString url, QString number, QString message, QString from)
{
    QEventLoop loop;
    QNetworkAccessManager manager(this);
    QNetworkReply* reply;
    QString command = QString("%1%2&to=%3&text=%4").arg(url).arg(from.size() > 0 ? "&from=" + from : "").arg(number).arg(message);
    reply = manager.get(QNetworkRequest(QUrl(command)));
    connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    if (reply->error() != QNetworkReply::NoError)
        debug(0, QString("Ошибка SMS: %1 %2").arg(reply->error()).arg(reply->errorString()));
}


void TApplication::readSettings()
{
    QSettings settings;
    settings.beginGroup("app");
    config.frNeeded = settings.value("frNeeded", config.frNeeded).toBool();
    config.barCodeReaderPort = settings.value("barCodeReaderPort", config.barCodeReaderPort).toString();
    config.frDriverPort = settings.value("frDriverPort", config.frDriverPort).toString();
    config.frDriverBaudRate = settings.value("frDriverBaudRate", config.frDriverBaudRate).toInt();
    config.frDriverTimeOut = settings.value("frDriverTimeOut", config.frDriverTimeOut).toInt();
    config.frLocalDriverTimeOut = settings.value("frLocalDriverTimeOut", config.frLocalDriverTimeOut).toInt();
    config.frRemoteDriverTimeOut = settings.value("frRemoteDriverTimeOut", config.frRemoteDriverTimeOut).toInt();
    config.frNetDriverTimeOut = settings.value("frNetDriverTimeOut", config.frNetDriverTimeOut).toInt();
    config.frDriverPassword = settings.value("frDriverPassword", config.frDriverPassword).toInt();
    config.frConnectSignal = settings.value("frConnectSignal", config.frConnectSignal).toBool();
    config.cardReaderPrefix = settings.value("cardReaderPrefix", config.cardReaderPrefix).toString();
    config.localPort = settings.value("localPort", config.localPort).toInt();
    config.remoteHost = settings.value("remoteHost", config.remoteHost).toString();
    config.remotePort = settings.value("remotePort", config.remotePort).toInt();
    config.saveFormConfigToDB = settings.value("saveFormConfigToDB", config.saveFormConfigToDB).toBool();
    int dirsCount = settings.value("dirsCount", 0).toInt();
    for (int i = 0; i < dirsCount; i++)
    {
        QString dirName = settings.value(QString("dirName%1").arg(i), "").toString();
        dirs.insert(dirName, settings.value(QString("dir%1").arg(i), "").toString());
    }
    settings.endGroup();
}


void TApplication::writeSettings()
{
    // Сохраним данные локально, на компьютере пользователя
    QSettings settings;
    settings.beginGroup("app");
    settings.setValue("frNeeded", config.frNeeded);
    settings.setValue("barCodeReaderPort", config.barCodeReaderPort);
    settings.setValue("frDriverPort", config.frDriverPort);
    settings.setValue("frDriverBaudRate", config.frDriverBaudRate);
    settings.setValue("frDriverTimeOut", config.frDriverTimeOut);
    settings.setValue("frLocalDriverTimeOut", config.frLocalDriverTimeOut);
    settings.setValue("frRemoteDriverTimeOut", config.frRemoteDriverTimeOut);
    settings.setValue("frNetDriverTimeOut", config.frNetDriverTimeOut);
    settings.setValue("frDriverPassword", config.frDriverPassword);
    settings.setValue("frConnectSignal", config.frConnectSignal);
    settings.setValue("cardReaderPrefix", config.cardReaderPrefix);
    settings.setValue("localPort", config.localPort);
    settings.setValue("remoteHost", config.remoteHost);
    settings.setValue("remotePort", config.remotePort);
    settings.setValue("saveFormConfigToDB", config.saveFormConfigToDB);
    settings.setValue("dirsCount", dirs.count());
    for (int i = 0; i < dirs.count(); i++)
    {
        QString dirName = dirs.keys().at(i);
        settings.setValue(QString("dirName%1").arg(i), dirName);
        settings.setValue(QString("dir%1").arg(i), dirs.value(dirName));
    }
    settings.endGroup();
}


void TApplication::saveMessages()
{
    QString text = messagesWindow->getTextEditor()->toPlainText();
    if (text.size() > 0)
    {
        QString fileName = getMessagesLogsPath("messages_" + QDate::currentDate().toString("yyyy_MM_dd"));
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
