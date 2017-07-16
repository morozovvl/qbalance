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
#include <QtUiTools/QUiLoader>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "topers.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "../gui/guifactory.h"
#include "../gui/passwordform.h"
#include "../gui/formgrid.h"
#include "../gui/mainwindow.h"
#include "../gui/configform.h"
#include "../gui/messagewindow.h"
#include "../gui/dialog.h"
#include "../engine/documentscriptengine.h"
#include "../storage/dbfactory.h"
#include "../bankterminal/bankterminal.h"
#include "../driverfr/driverfr.h"
#include "../barcodereader/barcodereader.h"
#include "../cardcodereader/cardcodereader.h"
#include "../engine/documentscriptengine.h"


QList<QString>      TApplication::DebugModes;
TApplication*       TApplication::Exemplar   = 0;
QString             TApplication::username         = "";
QString             TApplication::password         = "";
QString             TApplication::host             = "";
int                 TApplication::port                 = 0;
QString             TApplication::database         = "";
QString             TApplication::script           = "";
QStringList         TApplication::scriptParameter;
bool                TApplication::serverMode = false;
bool                TApplication::sendCommandMode = false;
GUIFactory*         TApplication::gui          = 0;
bool                TApplication::timeIsOut = false;
QTimer              TApplication::timer;
bool                TApplication::loadDefaultConfig = false;
bool                TApplication::fullDebugInfo = false;                  // По умолчанию выводится неполная отладочная информация (для лучшей читаемости журнала)





TApplication::TApplication(int & argc, char** argv)
    : QApplication(argc, argv)
{
    setOrganizationName("Enterprise");
    setApplicationName("qbalance");
    setApplicationVersion("0.1");
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
    updates = 0;

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
    debugToBuffer = false;
    writeDebug = true;
}


TApplication::~TApplication()
{
    delete gui;
    delete db;
}


Dictionary* TApplication::getDictionary(QString name)
{
    return getDictionaries()->getDictionary(name);
}


Saldo* TApplication::getSaldo(QString acc)
{
    return getDictionaries()->getSaldo(acc);
}


bool TApplication::addDictionary(QString name)
{
    return getDictionaries()->addDictionary(name);
}


bool TApplication::addSaldo(QString acc)
{
    return getDictionaries()->getSaldo(acc);
}


void TApplication::removeDictionary(QString name)
{
    getDictionaries()->removeDictionary(name);
}


DBFactory* TApplication::getDBFactory()
{
    return db;
}


void TApplication::clearMessageOnStatusBar()
{
    gui->getMainWindow()->getStatusBar()->clearMessage();
}


GUIFactory* TApplication::getGUIFactory()
{
    return gui;
}


QString TApplication::getLogin()
{
    return db->getLogin();
}


bool TApplication::isSA()
{
    return getLogin().toLower() == "sa" ? true : false;
}


QDate TApplication::getBeginDate()
{
    return beginDate;
}


QDate TApplication::getEndDate()
{
    return endDate;
}


MainWindow* TApplication::getMainWindow()
{
    return gui->getMainWindow();
}


QMdiSubWindow* TApplication::getActiveSubWindow()
{
    return gui->getMainWindow()->getWorkSpace()->activeSubWindow();
}


void TApplication::show()
{
    gui->show();
}


void TApplication::showDictionaries()
{
    dictionaryList->show();
}


void TApplication::showDocuments()
{
    topersList->show();
}


void TApplication::setPeriod()
{
    gui->setPeriod();
}                                               // Установим рабочий интервал


void TApplication::setBeginDate(QDate date)
{
    beginDate = date;
}


void TApplication::setEndDate(QDate date)
{
    endDate = date;
}


QString TApplication::authors()
{
    return "Морозов Владимир (morozovvladimir@mail.ru)";
}


bool TApplication::isDebugMode(int mode)
{
    return DebugModes.contains(QString("%1").arg(mode));
}


QString TApplication::debugFileName(QString debugMode)
{
    return getLogsPath().append(QString("debug%1.log").arg(debugMode));
}


QString TApplication::errorFileName()
{
    return "error.log";
}


QString TApplication::logTimeFormat()
{
    return "dd.MM.yy hh.mm.ss.zzz";
}


QString TApplication::resourcesFile()
{
    return applicationDirPath() + "/resources.qrc";
}


QString TApplication::getScriptFileName(int oper)
{
    return QString("формулы%1.qs").arg(oper);
}


void TApplication::setDebugToBuffer(bool buff)
{
    debugToBuffer = buff;
}


void TApplication::setWriteDebug(bool write)
{
    writeDebug = write;
}


bool TApplication::getFullDebugInfo()
{
    return fullDebugInfo;
}


int TApplication::getReportTemplateType()
{
    return reportTemplateType;
}


bool TApplication::drvFRisValid()
{
    return driverFRisValid;
}


DriverFR* TApplication::getDrvFR()
{
    return driverFR;
}


BankTerminal* TApplication::getBankTerminal()
{
    return bankTerminal;
}


TcpServer* TApplication::getTcpServer()
{
    return tcpServer;
}


TcpClient* TApplication::getTcpClient()
{
    return tcpClient;
}


bool TApplication::isBarCodeReaded()
{
    return barCodeReaded;
}


void TApplication::savePhotoToServer(QString file, QString localFile)
{
    saveFileToServer(file, localFile, PictureFileType, true);
}


MessageWindow* TApplication::getMessageWindow()
{
    return messagesWindow;
}


int TApplication::getSecDiff()
{
    return secDiff;
}


bool TApplication::isTimeOut()
{
    return timeIsOut;
}


void TApplication::setDirName(QString str)
{
    dirName = str;
}


QString TApplication::getScript()
{
    return script;
}                                  // Вернуть название скрипта, заданного в параметрах при запуске программы


QString TApplication::getScriptParameter(int i)
{
    if (i < scriptParameter.count())
        return scriptParameter.at(i);
    return "";
}


void TApplication::setScriptMode(bool mode)
{
    scriptMode = mode;
}


bool TApplication::isScriptMode()
{
    return scriptMode;
}


void TApplication::setServerMode(bool mode)
{
    serverMode = mode;
}


bool TApplication::isServerMode()
{
    return serverMode;
}


void TApplication::setSendCommandMode(bool mode)
{
    sendCommandMode = mode;
}


bool TApplication::isSendCommandMode()
{
    return sendCommandMode;
}


QMyExtSerialPort* TApplication::getSerialPort(const QString & name, QMyExtSerialPort::QueryMode mode, QObject* parent)
{
    return new QMyExtSerialPort(name, mode, parent);
}


MyProgressDialog* TApplication::getMyProgressDialog(QString mess)
{
    return new MyProgressDialog(mess, getMainWindow());
}


QString TApplication::getConfigTypeName(QString type)
{
    return configTypes.value(type);
}


QHash<QString, ConfigEntry>* TApplication::getConfigs()
{
    return &configs;
}


void TApplication::setConfigs(QHash<QString, ConfigEntry>* conf)
{
    configs = *conf;
}


void TApplication::initConfig()
{
//    setConfigTypeName("server", "Сервер взаимодействия");
//    setConfig("server", "LOCAL_PORT", "Локальный порт", CONFIG_VALUE_INTEGER, 44444);

    setConfigTypeName("client", "Клиент(сервер) взаимодействия");
    setConfig("client", "REMOTE_HOST", "Удаленный хост", CONFIG_VALUE_STRING, "192.168.0.1");
    setConfig("client", "REMOTE_PORT", "Удаленный порт (локальный порт сервера)", CONFIG_VALUE_INTEGER, 44444);
    setConfig("client", FR_NET_DRIVER_TIMEOUT, "Таймаут для обмена по сети, мс", CONFIG_VALUE_INTEGER, 100);
    setConfig("client", MAX_NET_TIMEOUT, "Максимальное время ожидания ответа по сети, мс", CONFIG_VALUE_INTEGER, 10000);

    setConfigTypeName("fr", "Фискальный регистратор");
    setConfig("fr", "FR_NEEDED", "Использовать ФР", CONFIG_VALUE_BOOLEAN, false);
#ifdef Q_OS_WIN32
    setConfig("fr", "FR_DRIVER_PORT", "COM порт", CONFIG_VALUE_STRING, "COM1");
#else
    setConfig("fr", "FR_DRIVER_PORT", "COM порт", CONFIG_VALUE_STRING, "/dev/ttyUSB0");
#endif
    setConfig("fr", "FR_DRIVER_BOUD_RATE", "Скорость", CONFIG_VALUE_BOUND, 6);
    setConfig("fr", "FR_DRIVER_MAX_TIMEOUT", "Максимальное время ожидания ФР, с", CONFIG_VALUE_INTEGER, 60);
    setConfig("fr", "FR_LOCAL_DRIVER_TIMEOUT", "Таймаут для локального ФР, мс", CONFIG_VALUE_INTEGER, 100);
    setConfig("fr", "FR_REMOTE_DRIVER_TIMEOUT", "Таймаут для сетевого ФР, мс", CONFIG_VALUE_INTEGER, 150);
    setConfig("fr", "FR_DRIVER_PASSWORD", "Пароль администратора ФР", CONFIG_VALUE_INTEGER, 30);
    setConfig("fr", "FR_CONNECT_SIGNAL", "Подавать сигнал на ФР при подключении", CONFIG_VALUE_BOOLEAN, true);

    setConfigTypeName("cReader", "Ридер магнитных карт");
    setConfig("cReader", "CARD_READER_NEEDED", "Использовать считыватель магнитных карт", CONFIG_VALUE_BOOLEAN, false);
    setConfig("cReader", "CARD_READER_PREFIX", "Префикс магнитной карты", CONFIG_VALUE_STRING, ";8336322632=");

    setConfigTypeName("bcReader", "Сканер штрих кодов");
    setConfig("bcReader", "BAR_CODE_READER_NEEDED", "Использовать сканер штрих кодов", CONFIG_VALUE_BOOLEAN, false);
#ifdef Q_OS_WIN32
    setConfig("bcReader", "BAR_CODE_READER_PORT", "COM порт", CONFIG_VALUE_STRING, "COM3");
#else
    setConfig("bcReader", "BAR_CODE_READER_PORT", "COM порт", CONFIG_VALUE_STRING, "/dev/ttyUSB0");
#endif
    setConfig("bcReader", "BAR_CODE_READER_BAUD_RATE", "Скорость", CONFIG_VALUE_BOUND, 6);
    setConfig("bcReader", "BAR_CODE_READER_TIMEOUT", "Таймаут, мс", CONFIG_VALUE_INTEGER, 100);

    setConfigTypeName("bcPrinter", "Принтер этикеток");
    setConfig("bcPrinter", "BAR_CODE_PRINTER_NEEDED", "Использовать принтер этикеток", CONFIG_VALUE_BOOLEAN, false);
    setConfig("bcPrinter", "BAR_CODE_PRINTER_NAME", "Имя принтера этикеток", CONFIG_VALUE_STRING, "");
    setConfig("bcPrinter", "BAR_CODE_PRINTER_BARCODESIZE", "Размер этикеток (ширина*высота), мм", CONFIG_VALUE_LABELSIZE, "30*20");
    setConfig("bcPrinter", "BAR_CODE_PRINTER_BARCODETYPE", "Тип штрихкода (в кодах генератора ШК zint)", CONFIG_VALUE_INTEGER, 13);
    setConfig("bcPrinter", "BAR_CODE_PRINTER_BARCODEHEIGHT", "Высота штрихкода", CONFIG_VALUE_INTEGER, 20);
    setConfig("bcPrinter", "BAR_CODE_PRINTER_BARCODEHUMANREADABLE", "Человеко-читаемая подпись штрихкода", CONFIG_VALUE_BOOLEAN, true);
    setConfig("bcPrinter", "BAR_CODE_PRINTER_BARCODEPREVIEW", "Предпросмотр этикетки", CONFIG_VALUE_BOOLEAN, false);

    setConfigTypeName(BANK_TERMINAL_PLUGIN_NAME, "Банковский терминал");
    setConfig(BANK_TERMINAL_PLUGIN_NAME, BANK_TERMINAL_NEEDED, "Использовать банковский терминал", CONFIG_VALUE_BOOLEAN, false);

    setConfigTypeName("form", "Формы");
    setConfig("form", "SAVE_FORM_CONFIG_TO_DB", "Сохранять геометрию форм на сервере", CONFIG_VALUE_BOOLEAN, false);

    setConfigTypeName("dbUpdates", "Обновления БД");
    setConfig("dbUpdates", "ASK_LOAD_UPDATES_TO_DB", "Спрашивать, если есть обновления базы данных", CONFIG_VALUE_BOOLEAN, true);
    setConfig("dbUpdates", "SAVE_DB_UPDATES_TO_LOCAL", "Сохранять обновления БД локально", CONFIG_VALUE_BOOLEAN, false);

    setConfigTypeName("photo", "Фотографии");
    setConfig("photo", "GET_PICTURE_FROM_SERVER_IN_DOCUMENT", "Загружать фото с сервера в документе (замедлит работу с документом)", CONFIG_VALUE_BOOLEAN, false);

    setConfigTypeName("params", "Параметры");
    setConfig("params", "PARAMETERS_D1", "Журнал комманд запросов (файл debug1.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_D2", "Журнал алгоритмов ядра (файл debug2.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_D3", "Журнал скриптов (файл debug3.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_D4", "Журнал устройства COM-порта (файл debug4.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_D5", "Журнал обмена между экземплярами приложения (файл debug5.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_D6", "Журнал банковского терминала (файл debug6.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_UL", "Объединить все включенные журналы отладки в одном файле (debug.log)", CONFIG_VALUE_BOOLEAN, false);
    setConfig("params", "PARAMETERS_FD", "Выводить полную отладочную информацию", CONFIG_VALUE_BOOLEAN, false);

    setConfigTypeName("updates", "Обновления");
    setConfig("updates", "UPDATES_FTP_URL", "FTP сервер", CONFIG_VALUE_STRING, "vm13720.hv8.ru");
    setConfig("updates", "UPDATES_FTP_PORT", "Порт", CONFIG_VALUE_INTEGER, 21);
    setConfig("updates", "UPDATES_FTP_ADMIN_CLIENT", "Логин клиента-администратора", CONFIG_VALUE_STRING, "ftpclient");
    setConfig("updates", "UPDATES_FTP_ADMIN_CLIENT_PASSWORD", "Пароль клиента-администратора", CONFIG_VALUE_PASSWORD, "");
    setConfig("updates", "UPDATES_FTP_CLIENT", "Логин клиента", CONFIG_VALUE_STRING, "ftp");
    setConfig("updates", "UPDATES_FTP_CLIENT_PASSWORD", "Пароль клиента", CONFIG_VALUE_PASSWORD, "");
}


void TApplication::setConfig(QString type, QString name, QString label, ConfigEntryType valType, QVariant value)
{
    ConfigEntry entry;
    configs.remove(name);
    configNames.removeAll(name);
    entry.type = type;
    entry.label = label;
    entry.valueType = valType;
    entry.value = value;
    configs.insert(name, entry);
    configNames.append(name);
}


void TApplication::removeConfig(QString name)
{
    configs.remove(name);
    configNames.removeAll(name);
}


void TApplication::setConfigValue(QString name, QVariant value)
{
    ConfigEntry entry;
    if (configs.contains(name))
        entry = configs.value(name);
    entry.value = value;
    setConfig(entry.type, name, entry.label, entry.valueType, entry.value);
}


QVariant TApplication::getConfigValue(QString name)
{
    QVariant result;
    if (configs.contains(name))
        result = configs.value(name).value;
    return result;
}


QStringList TApplication::getConfigTypes()
{
    QStringList result;
    foreach (QString name, configs.keys())
    {
        QString type = configs.value(name).type;
        if (!result.contains(type))
            result.append(type);
    }
    return result;
}



QList<QString> TApplication::getConfigNames(QString type)
{
    QList<QString> result;
    foreach (QString name, configNames)
    {
        if (type.size() == 0 || type == configs.value(name).type)
            result.append(name);
    }
    return result;
}


Documents* TApplication::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {

        Documents* doc = Documents::create<Documents>(opNumber);
        if (!doc->open())
            return 0;
        doc->query();
        doc->setCurrentRow(doc->getTableModel()->rowCount() - 1);
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

    gui = new GUIFactory();
    lResult = gui->open();

    return lResult;
}


bool TApplication::initApplication()
{
    bool lResult = false;   // По умолчанию будем считать, что приложение открыть не удалось

    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);

    initConfig();

    if (!loadDefaultConfig)
        readSettings();

    tcpServer = new TcpServer(getConfigValue("REMOTE_PORT").toInt(), this);
    tcpClient = new TcpClient(getConfigValue("REMOTE_HOST").toString(), getConfigValue("REMOTE_PORT").toInt(), this);
    timeOut(getConfigValue(FR_NET_DRIVER_TIMEOUT).toInt());                                  // Подеждем, пока произойдет соенинение с сервером приложения

    if (!isScriptMode())
        openPlugins();

    if (!loadDefaultConfig)
        readSettings();

    db  = new DBFactory();

    messagesWindow = new MessageWindow();

    forever         // Будем бесконечно пытаться открыть базу, пока пользователь не откажется
    {
        int result = gui->openDB(); // Попытаемся открыть базу данных
        if (result == 0)
        {   // БД открыть удалось

            secDiff = QDateTime::currentDateTime().secsTo(db->getValue("SELECT now();", 0, 0).toDateTime());
            dictionaryList = Dictionaries::create<Dictionaries>();
            topersList = Topers::create<Topers>();

            if (dictionaryList->open() && topersList->open())
            {
                updates = new Updates(this);
//                updates->open(getConfigValue("UPDATES_FTP_URL").toString());

                gui->showMenus();

                // Удалось открыть спосок справочников и типовых операций
                db->getPeriod(beginDate, endDate);
                gui->getMainWindow()->showPeriod();

                // Проверим обновления БД, и если надо, применим их
                if (getConfigValue("ASK_LOAD_UPDATES_TO_DB").toBool())
                {
                    int updatesCnt = db->updatesCount();
                    if (updatesCnt > 0)
                    {
                        if (gui->showYesNo(QString(QObject::trUtf8("Найдено обновлений базы данных: %1. Применить их?")).arg(updatesCnt)) == QMessageBox::Yes)
                            db->loadUpdates();
                    }
                }

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

                if (getConfigValue("FR_NEEDED").toBool() && !isScriptMode())
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
/*
            if (gui->showMessage(QObject::trUtf8("Не удалось соединиться с базой данных (БД). Возможно БД отсутствует."),
                                 QObject::trUtf8("Попытаться создать новую БД?")) == QMessageBox::Yes)
                // Попытаемся создать новую БД
                db->createNewDBs(gui->getLastHostName(), gui->getLastDbName(), gui->getLastPort());
*/
            break;
        }
        else if (result == -1)      // Пользователь нажал кнопку Отмена
            break;  // Выйдем из бесконечного цикла открытия БД
    }
    return lResult;
}


void TApplication::close()
{
    if (updates != 0)
    {
        updates->close();
        delete updates;
    }

    saveMessages();
    writeSettings();

    if (driverFR)
    {
        driverFR->close();
        delete driverFR;
    }

    if (tcpServer != 0)
        delete tcpServer;

    if (tcpClient != 0)
        delete tcpClient;

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


void    TApplication::openPlugins()
{
    // Если нужно и если есть соответствующий плагин, попытаемся открыть драйвер фискального регистратора
    if (getConfigValue("FR_NEEDED").toBool())
    {
        driverFR = (DriverFR*)createPlugin("driverfr");
        if (driverFR != 0)
        {
            driverFR->setApp(this);
            if (driverFR->open(getConfigValue("FR_DRIVER_PORT").toString(),
                               getConfigValue("FR_DRIVER_BOUD_RATE").toInt(),
                               getConfigValue("FR_LOCAL_DRIVER_TIMEOUT").toInt(),
                               getConfigValue("FR_DRIVER_PASSWORD").toInt()))
                    driverFRisValid = true;
            else
            {
                driverFR->close();
                driverFR = 0;
            }
        }
    }
    else
    {
        if (driverFR != 0)
        {
            driverFR->close();
            driverFR = 0;
        }
    }

    // Запустим сканер штрих-кодов, если есть его плагин
    if (getConfigValue("BAR_CODE_READER_NEEDED").toBool())
    {
        barCodeReader = (BarCodeReader*)createPlugin("barcodereader");
        if (barCodeReader != 0)
        {
            barCodeReader->setApp(this);
            if (!barCodeReader->open(getConfigValue("BAR_CODE_READER_PORT").toString(),
                                     getConfigValue("BAR_CODE_READER_BAUD_RATE").toInt(),
                                     getConfigValue("BAR_CODE_READER_TIMEOUT").toInt()))
            {
                barCodeReader->close();
                barCodeReader = 0;
            }
        }
    }
    else
    {
        if (barCodeReader != 0)
        {
            barCodeReader->close();
            barCodeReader = 0;
        }
    }


    // Запустим банковский терминал, если есть плагин
    if (getConfigValue(BANK_TERMINAL_NEEDED).toBool())
    {
        bankTerminal = (BankTerminal*)createPlugin(BANK_TERMINAL_PLUGIN_NAME);
        if (bankTerminal != 0)
        {
            bankTerminal->setApp(this);
            bankTerminal->getDefaultConfigs(BANK_TERMINAL_PLUGIN_NAME);
            if (!bankTerminal->open())
            {
                bankTerminal->close();
                bankTerminal = 0;
            }
        }
    }
    else
    {
        if (bankTerminal != 0)
        {
            bankTerminal->removeConfigs();
            bankTerminal->close();
            bankTerminal = 0;
        }
    }

    // Запустим считыватель магнитных карт, если есть его плагин
    if (getConfigValue("CARD_READER_NEEDED").toBool())
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
                connect(cardCodeReader, SIGNAL(cardCodeReaded(QString)), this, SIGNAL(cardCodeReaded(QString)));
        }
    }
    else
    {
        if (cardCodeReader != 0)
        {
            disconnect(cardCodeReader, SIGNAL(cardCodeReaded(QString)), this, SIGNAL(cardCodeReaded(QString)));
            cardCodeReader->close();
            cardCodeReader = 0;
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
    {
        if (timeout == -1)
            timeout = 0;
        gui->getMainWindow()->getStatusBar()->showMessage(message, timeout);
    }
}


void TApplication::showConfigs()
{
    ConfigForm* form = new ConfigForm();
    if (form->open(getMainWindow())) {
        form->exec();
        form->close();
    }
    delete form;
}


QString TApplication::getLogsPath()
{
    return getAnyPath("/logs");
}


QString TApplication::getMessagesLogsPath(QString fileName)
{
    return getAnyPath("/logs", fileName);
}


QString TApplication::getFormsPath(QString fileName)
{
    return getAnyPath("/forms", fileName);
}


QString TApplication::getScriptsPath(QString fileName)
{
    return getAnyPath("/scripts", fileName);
}


QString TApplication::getReportsPath(QString fileName)
{
    return getAnyPath("/reports", fileName);
}


QString TApplication::getPhotosPath(QString fileName)
{
    return getAnyPath("/photos", fileName);
}


QString TApplication::getCrashDumpsPath()
{
    return getAnyPath("/data/crashdumps");
}


QString TApplication::getUpdatesPath()
{
    QString dir = applicationDirPath() + "/updates";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    return dir;
}


QString TApplication::getAnyPath(QString subPath, QString fName)
{
    QString dir = applicationDirPath() + "/data";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    if (subPath.left(5) != dir.right(5))
    {
        dir += "/" + getConfigPrefix();
        if (!QDir().exists(dir))
            QDir().mkdir(dir);
        dir += subPath;
    }
    else
    {
        dir = applicationDirPath() + subPath;
    }
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir;
    fileName += "/" + fName;
    return fileName;

}


QString TApplication::getConfigFileName()
{
    return applicationDirPath() + "/configs";
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
                formWidget->setApp(this);
            }
        }
    }
    return formWidget;
}


QObject* TApplication::createPlugin(QString fileName)
{
    QObject* result = 0;
    QString pluginFile = applicationDirPath() + "/plugins/";
#ifdef Q_OS_WIN32
    pluginFile.append(QString("%1.dll").arg(fileName));
#else
    pluginFile.append(QString("lib%1.so").arg(fileName));
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


void TApplication::setDebugMode(int value, bool active)
{
    if (value < 0)
    {
        active = false;
        value = -value;
    }
    QString valName = value > 0 ? QString("%1").arg(value) : "";
    if (active)
    {
        if (!DebugModes.contains(valName))
            DebugModes.append(valName);
    }
    else
    {
        if (DebugModes.contains(valName))
            DebugModes.removeAll(valName);
    }
}


void TApplication::debug(int mode, const QString& value, bool timeIsEnabled)
{
    if ((writeDebug && isDebugMode(mode)) || mode == 0)
    {
        QString debugMode = QString("%1").arg(mode);
        if (DebugModes.contains("") || mode == 0)
            debugMode = "";
        if (!(db == 0 || debugToBuffer))                    // Если база данных открыта, то будем писать отладочную информацию в файл, иначе в буфер
        {
            if (tempDebugBuffer.contains(debugMode))                        // Если есть информация в буфере
            {
                foreach (QString str, tempDebugBuffer.value(debugMode))     // то скинем ее в файл
                {
                    writeToDebugFile(debugMode, str);
                }
                tempDebugBuffer.remove(debugMode);                          // и закроем буфер
            }
            QString str;                                                    // дальше будем писать в файл
            if (!timeIsEnabled)         // Если в строке не указано время, то укажем его
                str = QDateTime::currentDateTime().toString(logTimeFormat()) + " ";
            writeToDebugFile(debugMode, str + value);
        }
        else
        {
            QString str;                                                    // дальше будем писать в файл
            QStringList buffer;
            if (tempDebugBuffer.contains(debugMode))
            {
                buffer = tempDebugBuffer.value(debugMode);
                tempDebugBuffer.remove(debugMode);
            }
            if (!timeIsEnabled)         // Если в строке не указано время, то укажем его
                str = QDateTime::currentDateTime().toString(logTimeFormat()) + " ";
            buffer.append(str + value);
            tempDebugBuffer.insert(debugMode, buffer);
        }
    }
}


void TApplication::writeToDebugFile(QString debugMode, QString value)
{
    QString fileName = debugFileName(debugMode);
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Append))
    {
        QTextStream out(&file);
        out << value << "\n";
    }
    file.close();
}


int TApplication::getDebugBufferCount(int mode)
{
    QString smode = QString("%1").arg(mode);
    if (DebugModes.contains(""))
        smode = "";
    if (tempDebugBuffer.contains(smode))
    {
        return tempDebugBuffer.value(smode).count();
    }
    return 0;
}


void TApplication::clearDebugBuffer(int mode)
{
    QString smode = QString("%1").arg(mode);
    if (DebugModes.contains(""))
        smode = "";
    tempDebugBuffer.remove(smode);
}


QString TApplication::getLastValueInDebugBuffer(int mode)
{
    QString smode = QString("%1").arg(mode);
    if (DebugModes.contains(""))
        smode = "";
    QStringList list = tempDebugBuffer.value(smode);
    if (list.size() > 0)
        return tempDebugBuffer.value(smode).last();
    return "";
}


void TApplication::removeLastValueInDebugBuffer(int mode)
{
    QString smode = QString("%1").arg(mode);
    if (DebugModes.contains(""))
        smode = "";
    QStringList list = tempDebugBuffer.value(smode);
    if (list.size() > 0)
    {
        list.removeLast();
        tempDebugBuffer.remove(smode);
        tempDebugBuffer.insert(smode, list);
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

/*
void TApplication::showProcesses()
{
    runScript("analizeBankAccount.js");
}
*/

int TApplication::runScript(QString scrName)
{
    int result = 0;
    QString scriptName = scrName;
/*
    if (scriptName.size() == 0 && isSA())
    {
        dirName = "scriptLoadDir";
        scriptName = getOpenFileName(gui->getMainWindow(), "Укажите файл скрипта для выполнения", "", tr("Scripts (*.js *.qs)"));
        if (scriptName.size() == 0)
        {
            return result;
        }
    }
*/
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
        initConfig();
        if (!loadDefaultConfig)
            readSettings();

        TcpClient tcpcl(host, port);
        timeOut(getConfigValue(FR_NET_DRIVER_TIMEOUT).toInt());                                  // Подеждем, пока произойдет соенинение с сервером приложения
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
    return result;
}


void TApplication::barCodeReadyRead(QString barCodeString)
{
    barCodeReaded = true;
    Dialog* dialog = 0;
    if (getActiveSubWindow() != 0)
        dialog = (Dialog*)(getActiveSubWindow()->widget());
    if (dialog != 0)
    {
        if (QString(dialog->metaObject()->className()).compare("Dialog") == 0)
            dialog->getForm()->getParent()->barCodeReaded(barCodeString.trimmed());
    }
    barCodeReaded = false;
}


void TApplication::readCardReader(QKeyEvent* keyEvent)
{
    if (getConfigValue("CARD_READER_NEEDED").toBool())
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
        qulonglong localFileCheckSum = calculateCRC32(&array);
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
    else
        db->exec(QString("INSERT INTO смс_отправленные (ИМЯ, ТЕКСТ) VALUES ('%1', '%2');").arg(number).arg(message));
}


void TApplication::sendSMS(QString number, QString message)
{
    sendSMS(getConst("СМС_URL").toString(), number, message, getConst("ОтправительСМС").toString());
}


void TApplication::readSettings()
{
    QSettings settings(getConfigFileName(), QSettings::IniFormat);
    settings.beginGroup("app");
    int dirsCount = settings.value("dirsCount", 0).toInt();
    for (int i = 0; i < dirsCount; i++)
    {
        QString dirName = settings.value(QString("dirName%1").arg(i), "").toString();
        dirs.insert(dirName, settings.value(QString("dir%1").arg(i), "").toString());
    }

    foreach (QString name, getConfigNames())
    {
        QVariant value = settings.value(name, getConfigValue(name));
        setConfigValue(name, value);
    }

    settings.endGroup();

// Установим некоторые значения параметров
    setDebugMode(1, getConfigValue("PARAMETERS_D1").toBool());
    setDebugMode(2, getConfigValue("PARAMETERS_D2").toBool());
    setDebugMode(3, getConfigValue("PARAMETERS_D3").toBool());
    setDebugMode(4, getConfigValue("PARAMETERS_D4").toBool());
    setDebugMode(5, getConfigValue("PARAMETERS_D5").toBool());
    setDebugMode(6, getConfigValue("PARAMETERS_D6").toBool());
    if (getConfigValue("PARAMETERS_UL").toBool())
        setDebugMode(0);
    fullDebugInfo = getConfigValue("PARAMETERS_FD").toBool();
}


void TApplication::writeSettings()
{
    // Сохраним данные локально, на компьютере пользователя
    QSettings settings(getConfigFileName(), QSettings::IniFormat);
    settings.beginGroup("app");
    settings.setValue("dirsCount", dirs.count());
    for (int i = 0; i < dirs.count(); i++)
    {
        QString dirName = dirs.keys().at(i);
        settings.setValue(QString("dirName%1").arg(i), dirName);
        settings.setValue(QString("dir%1").arg(i), dirs.value(dirName));
    }
    foreach (QString name, getConfigNames())
    {
        settings.setValue(name, getConfigValue(name));
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

    // Получим список локальных шаблонов отчетов, если мы администратор
    if (isSA())
    {
        fs = dir.entryList(QStringList(tagName + ".*" + ext), QDir::Files, QDir::Name);
        foreach (QString f, fs)
        {
            if (!files.contains(f))
            {
                files << f;
                Essence::getFile(getReportsPath(), f, ReportTemplateFileType);
            }
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
                    result = tagName + "." + reportName + ext;
            }
            else
                result = tagName + "." + action->text() + ext;
        }
    }
    return result;
}


QString TApplication::getProcessFile(QString tagName, QWidget* formWidget, QRect rect)
{
    QString result;
    QDir dir = QDir(getScriptsPath());
    QString ext = ".js";
    QStringList files;
    // Получим шаблоны с сервера
    QStringList fs = db->getFilesList(tagName, ScriptFileType, true);
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
            Essence::getFile(getScriptsPath(), f, ScriptFileType);
        }
    }

    QStringList processes;
    QMenu* menu = new QMenu(formWidget);
    QAction* newProcessAct = new QAction(QObject::trUtf8("Создать новую обработку..."), this);
    QAction* execScriptAct = new QAction(QObject::trUtf8("Выполнить скрипт..."), this);
    if (isSA())
    {
        menu->addAction(newProcessAct);
        menu->addAction(execScriptAct);
    }
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
                processes << file;                                                        // Оставшуюся часть (название отчета) поместим в меню
                menu->addAction(file);
            }
        }
    }
    QAction* action = menu->exec(formWidget->mapToGlobal(formWidget->mapToGlobal(QPoint(rect.x() + 100, rect.y()-menu->height()))));
    if (action != 0)
    {
        if (action == newProcessAct)
        {
            QString reportName;                         // Создадим имя отчета по умолчанию
            int i = 1;
            do
            {
                reportName = QString("Отчет%1").arg(i++);
            } while (processes.contains(reportName));
            bool ok;
            reportName = QInputDialog::getText(formWidget, QObject::trUtf8("Создать новый документ"),
                                          QObject::trUtf8("Наименование документа:"), QLineEdit::Normal,
                                          reportName, &ok);
            if (ok && !reportName.isEmpty())
                result = tagName + "." + reportName + ext;
        }
        else if (action == execScriptAct)
        {
            dirName = "scriptLoadDir";
            result = getOpenFileName(gui->getMainWindow(), "Укажите файл скрипта для выполнения", "", tr("Scripts (*.js *.qs)"));
        }
        else
            result = tagName + "." + action->text() + ext;
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


bool TApplication::readParameters(int argc, char *argv[])
{
    bool lContinue = true;
    QTextStream out(stdout);
//    out.setCodec(TApplication::codec());
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).compare("-?", Qt::CaseInsensitive) == 0 ||
            QString(argv[i]).compare("--help", Qt::CaseInsensitive) == 0)
        {
            out << QString(QObject::trUtf8("Использование программы: %1 [Параметр]\n")).arg(applicationName());
            out << QObject::trUtf8("Параметры:\n");
            out << QObject::trUtf8("  -? | --help       - Вывести список параметров запуска программы\n");
            out << QObject::trUtf8("  -v | --version    - Вывести номер версии программы\n");
            out << QObject::trUtf8("  -d1| --debug1     - Включить журнал комманд запросов (файл debug1.log)\n");
            out << QObject::trUtf8("  -d2| --debug2     - Включить журнал алгоритмов ядра (файл debug2.log)\n");
            out << QObject::trUtf8("  -d3| --debug3     - Включить журнал скриптов (файл debug3.log)\n");
            out << QObject::trUtf8("  -d4| --debug4     - Включить журнал устройства COM-порта (файл debug4.log)\n");
            out << QObject::trUtf8("  -d5| --debug5     - Включить журнал обмена между экземплярами приложения (файл debug5.log)\n");
            out << QObject::trUtf8("  -d6| --debug6     - Включить журнал банковского терминала (файл debug6.log)\n");
            out << QObject::trUtf8("  -ul| --unitelogs  - Объединить все включенные журналы отладки в одном файле (debug.log)\n");
            out << QObject::trUtf8("  -fd| --fulldebug  - Выводить полную отладочную информацию (по умолчанию выключено)\n");
            out << QObject::trUtf8("  -h | --host       - IP адрес хоста\n");
            out << QObject::trUtf8("  -p | --port       - Порт на хосте\n");
            out << QObject::trUtf8("  -db| --database   - Наименование базы данных\n");
            out << QObject::trUtf8("  -l | --login      - Логин\n");
            out << QObject::trUtf8("  -pw| --password   - Пароль\n");
            out << QObject::trUtf8("  -s | --script     - Выполнить скрипт с заданным именем и выйти\n");
            out << QObject::trUtf8("  -sp| --scriptparameter - Параметр для скрипта (имя файла или строка, которую скрипт должен сам разобрать)\n");
            out << QObject::trUtf8("  -sr| --server     - Запустить программу в режиме сервера\n");
            out << QObject::trUtf8("  -c | --command    - Послать команду хосту (адрес и порт д.б. заданы параметрами -h и -p)\n");
            out << QObject::trUtf8("  -dc| --def_conf   - Загрузить конфигурационные параметры по умолчанию\n");
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-v", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--version", Qt::CaseInsensitive) == 0)
        {
            out << QString(QObject::trUtf8("Название программы: %1\n")).arg(applicationName());
            out << QString(QObject::trUtf8("Версия: %1\n")).arg(applicationVersion());
            out << QString(QObject::trUtf8("Авторы: %1\n")).arg(authors());
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-d1", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--debug1", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(1);
            }
        else if (QString(argv[i]).compare("-d2", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug2", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(2);
            }
        else if (QString(argv[i]).compare("-d3", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug3", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(3);
            }
        else if (QString(argv[i]).compare("-d4", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug4", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(4);
            }
        else if (QString(argv[i]).compare("-d5", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug5", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(5);
            }
        else if (QString(argv[i]).compare("-d6", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug6", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(6);
            }
        else if (QString(argv[i]).compare("-ul", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--unitelogs", Qt::CaseInsensitive) == 0)
            {
                setDebugMode(0);
            }
        else if (QString(argv[i]).compare("-h", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--host", Qt::CaseInsensitive) == 0)
            {
                host = argv[++i];
            }
        else if (QString(argv[i]).compare("-p", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--port", Qt::CaseInsensitive) == 0)
            {
                port = QString(argv[++i]).toInt();
            }
        else if (QString(argv[i]).compare("-db", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--database", Qt::CaseInsensitive) == 0)
            {
                database = argv[++i];
            }
        else if (QString(argv[i]).compare("-l", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--login", Qt::CaseInsensitive) == 0)
            {
                username = argv[++i];
            }
        else if (QString(argv[i]).compare("-pw", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--password", Qt::CaseInsensitive) == 0)
            {
                password = argv[++i];
            }
        else if (QString(argv[i]).compare("-s", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--script", Qt::CaseInsensitive) == 0)
            {
                script = argv[++i];
            }
        else if (QString(argv[i]).compare("-sp", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--scriptparameter", Qt::CaseInsensitive) == 0)
            {
                scriptParameter.append(argv[++i]);
            }
        else if (QString(argv[i]).compare("-sr", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--server", Qt::CaseInsensitive) == 0)
            {
                serverMode = true;
            }
        else if (QString(argv[i]).compare("-c", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--command", Qt::CaseInsensitive) == 0)
            {
                setSendCommandMode(true);
                script = argv[++i];
            }
        else if (QString(argv[i]).compare("-dc", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--def_conf", Qt::CaseInsensitive) == 0)
            {
                loadDefaultConfig = true;
            }
        else if (QString(argv[i]).compare("-fd", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--fulldebug", Qt::CaseInsensitive) == 0)
            {
                fullDebugInfo = true;
            }
    }
    return lContinue;
}


void TApplication::showReports()
{
}


void TApplication::printReport(QString fileName, QSqlQuery* query)
{
    if (fileName.size() > 0)
    {
        Dictionary* dict = Dictionary::create<Dictionary>();
        if (dict->open("SELECT 0", ""))      // Пустой запрос
        {
            if (query != 0)
            {
                dict->appendPrintValues("данные", query);
            }
            dict->print(fileName);
            dict->close();
        }
        delete dict;
    }
}


void TApplication::printReport(QString fileName, Dictionary* dict)
{
    dict->print(fileName);
}


qulonglong TApplication::calculateCRC32(QByteArray* array)
{
    unsigned long crc_table[256];
    unsigned long crc;
    char *buf = array->data();
    unsigned long len = array->count();

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    }

    crc = 0xFFFFFFFFUL;
    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFUL;
}


QString TApplication::OSType()
{
#ifdef Q_OS_WIN32
    return "Windows";
#endif
#ifdef Q_OS_LINUX
    return "Linux";
#endif
}
