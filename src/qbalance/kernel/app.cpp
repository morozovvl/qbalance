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
#include <QtGui/QMessageBox>
#include <QtCore/QObject>
#include <QtCore/QTextCodec>
#include <QtGui/QFileDialog>
#include <QtGui/QPushButton>
#include <QtGui/QPaintEngine>
#include <QtNetwork/QHttp>
#include <QtDesigner/QFormBuilder>
#include <QtGui/QInputDialog>
#include <QtGui/QWidget>
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
bool  TApplication::loadDefaultConfig = false;





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
    cardCodeReader = 0;
    bankTerminal = 0;

    driverFRisValid = false;
    driverFRlocked = false;
    fsWebCamIsValid = true;                     // Поначалу будем считать, что утилита fsWebCam установлена

    reportTemplateType = OOXMLreportTemplate;

    if (!Exemplar)
    {
        Exemplar = this;
    }
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
    setConfigTypeName("server", "Сервер взаимодействия");
    setConfig("server", LOCAL_PORT, "Локальный порт", 44444);

    setConfigTypeName("client", "Клиент взаимодействия");
    setConfig("client", REMOTE_HOST, "Удаленный хост", "192.168.0.1");
    setConfig("client", REMOTE_PORT, "Удаленный порт", 44444);

    setConfigTypeName("fr", "Фискальный регистратор");
    setConfig("fr", FR_NEEDED, "Использовать ФР", false);
#ifdef Q_OS_WIN32
    setConfig("fr", FR_DRIVER_PORT, "COM порт", "COM1");
#else
    setConfig("fr", FR_DRIVER_PORT, "COM порт", "/dev/ttyUSB0");
#endif
    setConfig("fr", FR_DRIVER_BOUD_RATE, "Скорость", 6, true);
    setConfig("fr", FR_DRIVER_TIMEOUT, "Таймаут, мс", 100);
    setConfig("fr", FR_LOCAL_DRIVER_TIMEOUT, "Таймаут для локального ФР, мс", 100);
    setConfig("fr", FR_REMOTE_DRIVER_TIMEOUT, "Таймаут для сетевого ФР, мс", 150);
    setConfig("fr", FR_NET_DRIVER_TIMEOUT, "Таймаут для обмена по сети, мс", 200);
    setConfig("fr", FR_DRIVER_PASSWORD, "Пароль администратора ФР", 30);
    setConfig("fr", FR_CONNECT_SIGNAL, "Подавать сигнал на ФР при подключении", true);

    setConfigTypeName("cReader", "Ридер магнитных карт");
    setConfig("cReader", CARD_READER_NEEDED, "Использовать считыватель магнитных карт", false);
    setConfig("cReader", CARD_READER_PREFIX, "Префикс магнитной карты", ";8336322632=");

    setConfigTypeName("bcReader", "Сканер штрих кодов");
    setConfig("bcReader", BAR_CODE_READER_NEEDED, "Использовать сканер штрих кодов", false);
#ifdef Q_OS_WIN32
    setConfig("bcReader", BAR_CODE_READER_PORT, "COM порт", "COM3");
#else
    setConfig("bcReader", BAR_CODE_READER_PORT, "COM порт", "/dev/ttyUSB0");
#endif
    setConfig("bcReader", BAR_CODE_READER_BAUD_RATE, "Скорость", 6, true);
    setConfig("bcReader", BAR_CODE_READER_TIMEOUT, "Таймаут, мс", 100);


    setConfigTypeName("bt", "Банковский терминал");
    setConfig("bt", BANK_TERMINAL_NEEDED, "Использовать банковский терминал", false);
    setConfig("bt", BANK_TERMINAL_PRINT_WAIT_TIME, "Продолжительность остановок при печати слипов, мс", 0);
    setConfig("bt", BANK_TERMINAL_PRINT_WAIT_MESSAGE, "Показывать сообщение о продолжении при печати слипов", false);
    setConfig("bt", BANK_TERMINAL_PROGRAM_WAIT_TIME, "Время ожидания окончания работы программы банковского терминала, мс", 60000);
    setConfig("bt", BANK_TERMINAL_INTERVAL_EMPTY_LINES, "Количество пустых строк между слипами и чеком", 2);
#ifdef Q_OS_WIN32
    setConfig("bt", BANK_TERMINAL_PATH, "Каталог программы банковского терминала", "C:/BankTerminal/");
#else
    setConfig("bt", BANK_TERMINAL_PATH, "Каталог программы банковского терминала", "/home/vladimir/BankTerminal/");
#endif

    setConfigTypeName("form", "Формы");
    setConfig("form", SAVE_FORM_CONFIG_TO_DB, "Сохранять геометрию форм на сервере", true);

    setConfigTypeName("dbUpdates", "Обновления БД");
    setConfig("dbUpdates", ASK_LOAD_UPDATES_TO_DB, "Спрашивать, если есть обновления базы данных", true);
    setConfig("dbUpdates", SAVE_DB_UPDATES_TO_LOCAL, "Сохранять обновления БД локально", false);

    setConfigTypeName("photo", "Фотографии");
    setConfig("photo", GET_PICTURE_FROM_SERVER_IN_DOCUMENT, "Загружать фото с сервера в документе (замедлит работу с документом)", false);
}


void TApplication::setConfig(QString type, ConfigVars name, QString label, QVariant value, bool isBoud)
{
    ConfigEntry entry;
    configs.remove(name);
    configNames.removeAll(name);
    entry.type = type;
    entry.label = label;
    entry.value = value;
    entry.isBoud = isBoud;
    configs.insert(name, entry);
    configNames.append(name);
}

void TApplication::setConfigValue(ConfigVars name, QVariant value)
{
    ConfigEntry entry;
    if (configs.contains(name))
        entry = configs.value(name);
    entry.value = value;
    setConfig(entry.type, name, entry.label, entry.value, entry.isBoud);
}


QVariant TApplication::getConfigValue(ConfigVars name)
{
    QVariant result;
    if (configs.contains(name))
        result = configs.value(name).value;
    return result;
}


QStringList TApplication::getConfigTypes()
{
    QStringList result;
    foreach (ConfigVars name, configs.keys())
    {
        QString type = configs.value(name).type;
        if (!result.contains(type))
            result.append(type);
    }
    return result;
}



QList<ConfigVars> TApplication::getConfigNames(QString type)
{
    QList<ConfigVars> result;
    foreach (ConfigVars name, configNames)
    {
        if (type.size() == 0 || type == configs.value(name).type)
            result.append(name);
    }
    return result;
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

    initConfig();
    if (!loadDefaultConfig)
        readSettings();

    if (!isScriptMode())
        openPlugins();

    db  = new DBFactory();
    tcpServer = new TcpServer(getConfigValue(LOCAL_PORT).toInt(), this);
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
                    // Проверим обновления БД, и если надо, применим их
                    int updates = db->updatesCount();
                    if (updates > 0)
                    {
                        if (getConfigValue(ASK_LOAD_UPDATES_TO_DB).toBool())
                        {
                            if (gui->showYesNo(QString(QObject::trUtf8("Найдено обновлений базы данных: %1. Применить их?")).arg(updates)) == QMessageBox::Yes)
                                db->loadUpdates();
                        }
                        else
                            db->loadUpdates();
                    }

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

                    if (getConfigValue(FR_NEEDED).toBool() && !isScriptMode())
                    {
                        if (driverFRisValid)
                            showMessageOnStatusBar("Найден фискальный регистратор.\n");
                        else
                        {
                            if (driverFR != 0 && driverFR->isLocked())
                                showMessageOnStatusBar("Фискальный регистратор занят. Не удалось соединиться.\n");
                            else
                                showMessageOnStatusBar("Фискальный регистратор не найден.\n");
                        }
                    }

                    db->clearLockedDocumentList();

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


void    TApplication::openPlugins()
{
    // Если нужно и если есть соответствующий плагин, попытаемся открыть драйвер фискального регистратора
    if (getConfigValue(FR_NEEDED).toBool())
    {
        driverFR = (DriverFR*)createPlugin("driverfr");
        if (driverFR != 0)
        {
            driverFR->setApp(this);
            if (driverFR->open(getConfigValue(FR_DRIVER_PORT).toString(),
                               getConfigValue(FR_DRIVER_BOUD_RATE).toInt(),
                               getConfigValue(FR_DRIVER_TIMEOUT).toInt(),
                               getConfigValue(FR_DRIVER_PASSWORD).toInt(),
                               getConfigValue(REMOTE_HOST).toString(),
                               getConfigValue(REMOTE_PORT).toInt()))
                    driverFRisValid = true;
            else
            {
                driverFR->close();
                driverFR = 0;
            }
        }
    }

    // Запустим сканер штрих-кодов, если есть его плагин
    if (getConfigValue(BAR_CODE_READER_NEEDED).toBool())
    {
        barCodeReader = (BarCodeReader*)createPlugin("barcodereader");
        if (barCodeReader != 0)
        {
            barCodeReader->setApp(this);
            if (!barCodeReader->open(getConfigValue(BAR_CODE_READER_PORT).toString(),
                                     getConfigValue(BAR_CODE_READER_BAUD_RATE).toInt(),
                                     getConfigValue(BAR_CODE_READER_TIMEOUT).toInt()))
            {
                barCodeReader->close();
                barCodeReader = 0;
            }
        }
    }

    // Запустим банковский терминал, если есть плагин
    if (getConfigValue(BANK_TERMINAL_NEEDED).toBool())
    {
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
    }

    // Запустим считыватель магнитных карт, если есть его плагин
    if (getConfigValue(CARD_READER_NEEDED).toBool())
    {
        cardCodeReader = (CardCodeReader*)createPlugin("cardcodereader");
        if (cardCodeReader != 0)
        {
            cardCodeReader->setApp(this);
            if (!cardCodeReader->open())
            {
                cardCodeReader->close();
                cardCodeReader = 0;
            }
            else
                connect (cardCodeReader, SIGNAL(cardCodeReaded(QString)), this, SIGNAL(cardCodeReaded(QString)));
        }
    }
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
    return applicationDirPath() + "/data/crashdumps";
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
    if (!isScriptMode() && error.size() > 0)
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


int TApplication::showMessage(QString message, QString question,
                QMessageBox::StandardButtons buttons,
                QMessageBox::StandardButton defButton)
{
    return gui->showMessage(message, question, buttons, defButton);
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


void TApplication::readCardReader(QKeyEvent* keyEvent)
{
    if (getConfigValue(CARD_READER_NEEDED).toBool())
    {
        if (cardCodeReader != 0)
            cardCodeReader->readCardReader(keyEvent);
    }
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


void TApplication::sendSMS(QString number, QString message)
{
    sendSMS(getConst("СМС_URL").toString(), number, message, getConst("ОтправительСМС").toString());
}


void TApplication::readSettings()
{
    QSettings settings;
    settings.beginGroup("app");
    int dirsCount = settings.value("dirsCount", 0).toInt();
    for (int i = 0; i < dirsCount; i++)
    {
        QString dirName = settings.value(QString("dirName%1").arg(i), "").toString();
        dirs.insert(dirName, settings.value(QString("dir%1").arg(i), "").toString());
    }

    foreach (ConfigVars name, getConfigNames())
    {
        QVariant value = settings.value(QString("ConfigVars%1").arg(name), getConfigValue(name));
        if (value == "true" || value == "false")
            setConfigValue(name, value.toBool());
        else
            setConfigValue(name, value);
    }

    settings.endGroup();
}


void TApplication::writeSettings()
{
    // Сохраним данные локально, на компьютере пользователя
    QSettings settings;
    settings.beginGroup("app");
    settings.setValue("dirsCount", dirs.count());
    for (int i = 0; i < dirs.count(); i++)
    {
        QString dirName = dirs.keys().at(i);
        settings.setValue(QString("dirName%1").arg(i), dirName);
        settings.setValue(QString("dir%1").arg(i), dirs.value(dirName));
    }
    foreach (ConfigVars name, getConfigNames())
    {
        settings.setValue(QString("ConfigVars%1").arg(name), getConfigValue(name));
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


QString TApplication::getReportFile(QString tagName, bool autoPrint, QWidget* formWidget, QRect rect)
{
    QString result;
    QDir dir = QDir(getReportsPath());
    QString ext = "." + getReportTemplateExt();
    QStringList files;
    // Получим шаблоны с сервера
    QStringList fs = db->getFilesList(tagName, ReportTemplateFileType, true);
    foreach (QString f, fs)
    {
        if (!files.contains(f))
            files << f;
    }

    // Получим список локальных шаблонов отчетов
    fs = dir.entryList(QStringList(tagName + ".*" + ext), QDir::Files, QDir::Name);
    foreach (QString f, fs)
    {
        if (!files.contains(f))
        {
            files << f;
            Essence::getFile(getReportsPath(), f, ReportTemplateFileType);
        }
    }

    QStringList reports;
    QMenu* menu = new QMenu(formWidget);
    QAction* newReportAct = new QAction(QObject::trUtf8("Создать новый отчет..."), this);
    if (isSA())
        menu->addAction(newReportAct);
    if (files.count() > 0)
    {
        if (isSA())
            menu->addSeparator();
        for (int i = 0; i < files.size(); i++)
        {
            QString file = files.at(i);
            QString oldFile = file;
            file.remove(tagName + ".", Qt::CaseInsensitive);      // Уберем префикс файла
            if (file != oldFile)
            {
                file.remove(ext, Qt::CaseInsensitive);                                  // И его суффикс
                reports << file;                                                        // Оставшуюся часть (название отчета) поместим в меню
                menu->addAction(file);
            }
        }
    }
    if (autoPrint && files.size() == 1)
        result = files.at(0);
    else
    {
        QAction* action = menu->exec(formWidget->mapToGlobal(formWidget->mapToGlobal(QPoint(rect.x() + 100, rect.y()-menu->height()))));
        if (action != 0)
        {
            if (action == newReportAct)
            {
                QString reportName;                         // Создадим имя отчета по умолчанию
                int i = 1;
                do
                {
                    reportName = QString("Отчет%1").arg(i++);
                } while (reports.contains(reportName));
                bool ok;
                reportName = QInputDialog::getText(formWidget, QObject::trUtf8("Создать новый документ"),
                                              QObject::trUtf8("Наименование документа:"), QLineEdit::Normal,
                                              reportName, &ok);
                if (ok && !reportName.isEmpty())
                    result = tagName + "." + reportName + "." + getReportTemplateExt();
            }
            else
                result = tagName + "." + action->text() + "." + getReportTemplateExt();
        }
    }
    return result;
}


bool TApplication::bankTerminalIsValid()
{
    bool result = true;
    if (bankTerminal == 0)
    {
        result = false;
    }
    return result;
}


int TApplication::decodeTimeOut(int timeOut)
{
    int result = timeOut;
    if (timeOut >= 150 && timeOut < 250)
        result = 150 + ((timeOut - 150) * 150);
    else if (timeOut >= 250 && timeOut <= 255)
        result = 30000 + ((timeOut - 250) * 15000);
    return result;
}


int TApplication::codeTimeOut(int timeOut)
{
    int result = timeOut;
    if (timeOut >= 150 && timeOut <= 15000)
        result = 150 + (timeOut / 150 - 1);
    else if (timeOut > 15000 && timeOut <= 105000)
        result = 250 + (timeOut / 15000 - 2);
    return result;
}


