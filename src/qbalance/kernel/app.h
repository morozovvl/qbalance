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

#ifndef APP_H
#define APP_H

#include <QtGui/QApplication>
#include <QtCore/QHash>
#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QPointer>
#include <QtUiTools/QtUiTools>
#include <QtGui/QTextEdit>
#include <QtGui/QFileDialog>
#include "dictionaries.h"
#include "documents.h"
#include "topers.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "../gui/guifactory.h"
#include "../gui/mainwindow.h"
#include "../gui/dialog.h"
#include "../gui/messagewindow.h"
#include "../gui/myprogressdialog.h"
#include "../driverfr/driverfr.h"
#include "../bankterminal/bankterminal.h"
#include "../serialport/qmyextserialport.h"
#include "../barcodereader/barcodereader.h"
#include "../cardcodereader/cardcodereader.h"

class Dictionaries;
class Topers;
class DBFactory;
class GUIFactory;
class Documents;
class MainWindow;
class Dialog;


enum  ReportTemplateTypes
{
    OOreportTemplate,
    OOUNOreportTemplate,
    OOXMLreportTemplate,
    OpenRPTreportTemplate
};


struct ConfigEntry
{
    QString type;
    QString label;
    QVariant value;
    bool isBoud;
};


enum ConfigVars {
    LOCAL_PORT,
    REMOTE_HOST,
    REMOTE_PORT,
    FR_NEEDED,
    FR_DRIVER_PORT,
    FR_DRIVER_BOUD_RATE,
    FR_DRIVER_MAX_TIMEOUT,
    FR_LOCAL_DRIVER_TIMEOUT,
    FR_REMOTE_DRIVER_TIMEOUT,
    FR_NET_DRIVER_TIMEOUT,
    FR_DRIVER_PASSWORD,
    FR_CONNECT_SIGNAL,
    CARD_READER_NEEDED,
    CARD_READER_PREFIX,
    BAR_CODE_READER_NEEDED,
    BAR_CODE_READER_PORT,
    BAR_CODE_READER_BAUD_RATE,
    BAR_CODE_READER_TIMEOUT,
    BANK_TERMINAL_NEEDED,
    BANK_TERMINAL_PRINT_WAIT_TIME,
    BANK_TERMINAL_PRINT_WAIT_MESSAGE,
    BANK_TERMINAL_PROGRAM_WAIT_TIME,
    BANK_TERMINAL_INTERVAL_EMPTY_LINES,
    BANK_TERMINAL_PATH,
    SAVE_FORM_CONFIG_TO_DB,
    ASK_LOAD_UPDATES_TO_DB,
    SAVE_DB_UPDATES_TO_LOCAL,
    GET_PICTURE_FROM_SERVER_IN_DOCUMENT,
    PARAMETERS
};


class TApplication : public QApplication {
    Q_OBJECT

public:
    QHash<QString, Documents*> documents;                        // Объекты списков документов
    static QString username;
    static QString password;
    static QString host;
    static int port;
    static QString database;
    static QString script;
    static QString scriptParameter;
    static bool    serverMode;
    static bool loadDefaultConfig;

    TApplication(int& argc, char** argv);
    ~TApplication();
    Q_INVOKABLE virtual Dictionaries* getDictionaries();
    Q_INVOKABLE virtual Dictionary* getDictionary(QString name) { return getDictionaries()->getDictionary(name); }
    Q_INVOKABLE virtual Saldo* getSaldo(QString acc)  { return getDictionaries()->getSaldo(acc); }
    Q_INVOKABLE virtual bool addDictionary(QString name)  { return getDictionaries()->addDictionary(name); }
    Q_INVOKABLE virtual bool addSaldo(QString acc)  { return getDictionaries()->getSaldo(acc); }
    Q_INVOKABLE virtual void removeDictionary(QString name)  { getDictionaries()->removeDictionary(name); }
    Q_INVOKABLE Documents* getDocuments(int);
    void removeDocuments(int opNumber);
    Q_INVOKABLE virtual DBFactory* getDBFactory() { return db; }
    Q_INVOKABLE void clearMessageOnStatusBar() { gui->getMainWindow()->getStatusBar()->clearMessage(); }
    Q_INVOKABLE virtual void showMessageOnStatusBar(const QString &message = "", int timeout = 3000 );
    Q_INVOKABLE QVariant getConst(QString);
    virtual GUIFactory* getGUIFactory() { return gui; }
    Q_INVOKABLE QString getLogin() { return db->getLogin(); }
    Q_INVOKABLE bool isSA() { return getLogin().toLower() == "sa" ? true : false; }
    QDate getBeginDate() { return beginDate; }
    QDate getEndDate() { return endDate; }
    QString getLogsPath();
    QString getMessagesLogsPath(QString = "");
    QString getFormsPath(QString = "");
    QString getScriptsPath(QString = "");
    QString getReportsPath(QString = "");
    QString getCrashDumpsPath();
    Q_INVOKABLE QString getPhotosPath(QString = "");
    QString getConfigPrefix();
    virtual MainWindow* getMainWindow() { return gui->getMainWindow(); }
    QMdiSubWindow* getActiveSubWindow() { return gui->getMainWindow()->getWorkSpace()->activeSubWindow(); }

    void show() { gui->show(); }

    void showDictionaries() { dictionaryList->show(); }
    void showDocuments() { topersList->show(); }
    void showProcesses();
    void showReports() { ; }
    void showConfigs();
    void setPeriod() { gui->setPeriod(); }                                               // Установим рабочий интервал
    void setBeginDate(QDate date) { beginDate = date; }
    void setEndDate(QDate date) { endDate = date; }

    Q_INVOKABLE Dialog* createForm(QString);           // Открыть форму с заданным именем
    Q_INVOKABLE Form* createNewForm(QString);
    Q_INVOKABLE virtual void setIcons(QWidget*);         // Устанавливает иконки на кнопки указанной формы

    static QString encoding();
    Q_INVOKABLE virtual QTextCodec* codec();

    static QString authors()       { return "Морозов Владимир (morozovvladimir@mail.ru)";}
    virtual bool isDebugMode(int mode)        { return DebugModes.contains(QString("%1").arg(mode));}
    QString debugFileName(QString debugMode) {  return getLogsPath().append(QString("debug%1.log").arg(debugMode));}
    static QString errorFileName() { return "error.log";}
    static QString logTimeFormat() { return "dd.MM.yy hh.mm.ss.zzz";}
    static QString resourcesFile() { return applicationDirPath() + "/resources.qrc";}
    static QString getScriptFileName(int oper) { return QString("формулы%1.qs").arg(oper); }
    static void setDebugMode(QString value);
    void    setDebugToBuffer(bool buff) { debugToBuffer = buff; }
    int getDebugBufferCount(int mode);
    void clearDebugBuffer(int mode);
    void setWriteDebug(bool write) { writeDebug = write; }
    QString getLastValueInDebugBuffer(int);
    void removeLastValueInDebugBuffer(int);

    Q_INVOKABLE virtual void debug(int, const QString&, bool = false);

    static TApplication* exemplar();

    virtual bool open();
    virtual void close();

    int getReportTemplateType() { return reportTemplateType; }
    QString getReportTemplateExt();
    Q_INVOKABLE bool drvFRisValid() { return driverFRisValid; }
    Q_INVOKABLE virtual DriverFR* getDrvFR() { return driverFR; }
    virtual int decodeTimeOut(int);
    virtual int codeTimeOut(int);


    Q_INVOKABLE bool bankTerminalIsValid();
    Q_INVOKABLE BankTerminal* getBankTerminal() { return bankTerminal; }

    TcpServer* getTcpServer() { return tcpServer; }

    Q_INVOKABLE void virtual showError(QString);
    Q_INVOKABLE int virtual showMessage(QString message, QString question = "",
                    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::StandardButton defButton = QMessageBox::No);      // Вывести сообщение пользователю и возможно задать вопрос

    Q_INVOKABLE QProcess* runProcess(QString, QString = "", bool = true);
    Q_INVOKABLE bool waitProcessEnd(QProcess *);
    virtual void barCodeReadyRead(QString);
    Q_INVOKABLE     bool    isBarCodeReaded() { return barCodeReaded; }
    virtual void readCardReader(QKeyEvent*);

    Q_INVOKABLE void capturePhoto(QString fileName = "", QString deviceName = "");    // Захватить кадр с видеокамеры и записать в базу
    Q_INVOKABLE void saveFileToServer(QString, QString, FileType, bool = false);
    Q_INVOKABLE void savePhotoToServer(QString file, QString localFile) { saveFileToServer(file, localFile, PictureFileType, true); }
    Q_INVOKABLE void saveFile(QString, QByteArray*);
    Q_INVOKABLE void print(QString = "");
    Q_INVOKABLE void printToArray(QString, QString);
    Q_INVOKABLE void printArray(QString);
    Q_INVOKABLE void clearPrintArrays();
    Q_INVOKABLE int printArrayCount(QString);
    MessageWindow* getMessageWindow() { return messagesWindow; }
    int getSecDiff() { return secDiff; }
    void    initConfig();
    QString     findFileFromEnv(QString);
    Q_INVOKABLE virtual void timeOut(int);
    Q_INVOKABLE void startTimeOut(int);
    Q_INVOKABLE bool isTimeOut() { return timeIsOut; }
    Q_INVOKABLE virtual void sleep(int);

    Q_INVOKABLE void setDirName(QString str) { dirName = str; }
    Q_INVOKABLE QString getOpenFileName(QWidget* parent = 0, const QString caption = QString(), const QString dir = QString(), const QString filter = QString(), QString* selectedFilter = 0, QFileDialog::Options options = 0);

    void saveCustomization();
    void loadFile();
    void printReportWithoutCleaning();
    Q_INVOKABLE virtual int runScript(QString);
    Q_INVOKABLE QString getScript() { return script; }                                  // Вернуть название скрипта, заданного в параметрах при запуске программы
    Q_INVOKABLE QString getScriptParameter() { return scriptParameter; }

    Q_INVOKABLE void sendSMS(QString url, QString number, QString message, QString from = "");                     // Посылка СМС через сервис SMS.RU
    Q_INVOKABLE void sendSMS(QString url, QString number);                               // Посылка СМС через сервис SMS.RU

    void    setScriptMode(bool mode) { scriptMode = mode; }
    bool    isScriptMode() { return scriptMode; }

    void    setServerMode(bool mode) { serverMode = mode; }
    bool    isServerMode() { return serverMode; }

    static void    setSendCommandMode(bool mode) { sendCommandMode = mode; }
    static bool    isSendCommandMode() { return sendCommandMode; }

    QList<ScriptEngine*>     getScriptStack() { return scriptStack; }
    void            appendScriptStack(ScriptEngine* script) { scriptStack.append(script); }
    void            removeLastScriptStack() { scriptStack.removeLast(); }
    ScriptEngine*   getLastScriptStack() { return scriptStack.last(); }

    QObject*        createPlugin(QString);
    virtual QMyExtSerialPort* getSerialPort(const QString & name, QMyExtSerialPort::QueryMode mode = QMyExtSerialPort::EventDriven, QObject * parent = 0) { return new QMyExtSerialPort(name, mode, parent); }
    virtual MyProgressDialog* getMyProgressDialog(QString mess) { return new MyProgressDialog(mess, getMainWindow()); }
    QString         getReportFile(QString, bool, QWidget*, QRect);

    void    openPlugins();

// Работа с пользователской конфигурацией программы
    virtual QVariant        getConfigValue(ConfigVars name);
    QStringList     getConfigTypes();
    QString         getConfigTypeName(QString type) { return configTypes.value(type); }
    QHash<ConfigVars, ConfigEntry>* getConfigs() { return &configs; }
    void            setConfigs(QHash<ConfigVars, ConfigEntry>* conf) { configs = *conf; }
    QList<ConfigVars>     getConfigNames(QString type = "");

    static bool readParameters(int argc, char *argv[]);

signals:
    void cardCodeReaded(QString);

private:
    Dictionaries*           dictionaryList;                               // Форма со списком справочников
    Topers*                 topersList;                                   // Форма со списком операций
    static GUIFactory*      gui;
    QDate                   beginDate;
    QDate                   endDate;
    DriverFR*               driverFR;
    bool                    driverFRisValid;
    bool                    driverFRlocked;
    BankTerminal*           bankTerminal;
    bool                    fsWebCamIsValid;
    static QList<QString>       DebugModes;
    static TApplication*    Exemplar;
    DBFactory*              db;
    BarCodeReader*          barCodeReader;
    CardCodeReader*         cardCodeReader;
    bool                    barCodeReaded;
    MessageWindow*          messagesWindow;
    int                     secDiff;                                // Разница в секундах между временем на этой машине и на сервере
                                                                    // Если число положительное, то время на этих часах отстает
                                                                    // Чтобы получить приблизительное время на сервере
                                                                    // нужно к текущему времени прибавить эту разницу


    // Свойства, устанавливаемые из настроек приложения
    ReportTemplateTypes     reportTemplateType;                        // тип шаблона печати

    QHash<QString, QStringList>     arraysForPrint;
    TcpServer*              tcpServer;
    static QTimer           timer;
    static bool             timeIsOut;
    bool                    scriptMode;
    static bool             sendCommandMode;
    QList<ScriptEngine*>    scriptStack;
    QHash<QString, QString>     dirs;
    QString                 dirName;
    QHash<ConfigVars, ConfigEntry> configs;
    QList<ConfigVars>                 configNames;
    QHash<QString, QString>     configTypes;
    QHash<QString, QStringList> tempDebugBuffer;
    bool                    debugToBuffer;
    bool                    writeDebug;

    void loadConsts();
    QString getAnyPath(QString, QString = "");
    void                    readSettings();
    void                    writeSettings();
    void                    saveMessages();
    void            setConfig(QString type, ConfigVars name, QString label, QVariant value, bool = false);
    void            setConfigValue(ConfigVars name, QVariant value);
    void            setConfigTypeName(QString type, QString name) { configTypes.insert(type, name); }
    void            writeToDebugFile(QString, QString);

private slots:
    void                    setTimeIsOut() { timeIsOut = true; }
};

#endif
