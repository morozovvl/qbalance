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

#include <QtWidgets/QApplication>
#include <QtCore/QHash>
#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QPointer>
//#include <QtUiTools>
//#include <QtWidgets/QTextEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMessageBox>
//#include <QPrinter>
#include <QtSql/QSqlQuery>
//#include <QVariant>
#include "configvars.h"
#include "../storage/filetype.h"
#include "../serialport/qmyextserialport.h"
#include "../bankterminal/bankterminal.h"
#include "../emailclient/emailclient.h"
#include "updates.h"


#define FR_NET_DRIVER_TIMEOUT                 "FR_NET_DRIVER_TIMEOUT"
#define MAX_NET_TIMEOUT                       "MAX_NET_TIMEOUT"
#define BANK_TERMINAL_PLUGIN_NAME             "bankterminal"

#ifndef APPLICATION_NAME
    #define APPLICATION_NAME    "qbalance"
#endif

class Dictionary;
class Dictionaries;
class Saldo;
class Topers;
class DBFactory;
class GUIFactory;
class Documents;
class MainWindow;
class MessageWindow;
class Form;
class Dialog;
class BankTerminal;
class TcpServer;
class DriverFR;
class ScriptEngine;
class BarCodeReader;
class CardCodeReader;
class MessageWindow;
class MyProgressDialog;


enum  ReportTemplateTypes
{
    OOreportTemplate,
    OOUNOreportTemplate,
    OOXMLreportTemplate,
    OpenRPTreportTemplate
};


enum ConfigEntryType
{
    CONFIG_VALUE_BOUND,
    CONFIG_VALUE_STRING,
    CONFIG_VALUE_INTEGER,
    CONFIG_VALUE_BOOLEAN,
    CONFIG_VALUE_LABELSIZE,
    CONFIG_VALUE_PASSWORD,
    CONFIG_VALUE_PUSHBUTTON
};


struct ConfigEntry
{
    QString name;
    QString type;
    QString label;
    ConfigEntryType valueType;
    QVariant value;
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
    static QStringList scriptParameter;
    static bool    serverMode;
    static bool loadDefaultConfig;

    TApplication(int& argc, char** argv);
    ~TApplication();
    Q_INVOKABLE virtual Dictionaries* getDictionaries();
    Q_INVOKABLE virtual Dictionary* getDictionary(QString name);
    Q_INVOKABLE virtual Saldo* getSaldo(QString acc);
    Q_INVOKABLE virtual bool addDictionary(QString name);
    Q_INVOKABLE virtual bool addSaldo(QString acc);
    Q_INVOKABLE virtual void removeDictionary(QString name);
    Q_INVOKABLE Documents* getDocuments(int);
    void removeDocuments(int opNumber);
    Q_INVOKABLE virtual DBFactory* getDBFactory();
    Q_INVOKABLE virtual void clearMessageOnStatusBar();
    Q_INVOKABLE virtual void showMessageOnStatusBar(QString message = "", int timeout = 5000 );
    Q_INVOKABLE QVariant getConst(QString, bool = false);
    Q_INVOKABLE void setConst(QString, QVariant);
    virtual GUIFactory* getGUIFactory();
    Q_INVOKABLE QString getLogin();
    Q_INVOKABLE virtual bool isSA();
    Q_INVOKABLE QDate getBeginDate();
    Q_INVOKABLE QDate getEndDate();
    QString getLogsPath();
    QString getMessagesLogsPath(QString = "");
    QString getFormsPath(QString = "", QString = "");
    QString getScriptsPath(QString = "", QString = "");
    QString getReportsPath(QString = "", QString = "");
    QString getPath(QString, int, QString = "");
    QString getCrashDumpsPath();
    QString getUpdatesPath();
    Q_INVOKABLE QString getPhotosPath(QString = "");
    QString getConfigPrefix();
    virtual MainWindow* getMainWindow();
    QMdiSubWindow* getActiveSubWindow();

    void show();

    void showDictionaries();
    void showDocuments();
//    void showProcesses();
    void showReports();
    void showConfigs();
    void setPeriod();
    void setBeginDate(QDate date);
    void setEndDate(QDate date);

    Q_INVOKABLE Dialog* createForm(QString);           // Открыть форму с заданным именем
    Q_INVOKABLE Form* createNewForm(QString);
    Q_INVOKABLE virtual void setIcons(QWidget*);         // Устанавливает иконки на кнопки указанной формы

    static QString encoding();
    Q_INVOKABLE virtual QTextCodec* codec();

    static QString authors();
    virtual bool isDebugMode(int mode);
    QString debugFileName(QString debugMode);
    static QString errorFileName();
    static QString logTimeFormat();
    static QString dateFormat();
    static QString resourcesFile();
    static QString getScriptFileName(int oper);
    static void setDebugMode(int = 0, bool = true);
    void    setDebugToBuffer(bool buff);
    int getDebugBufferCount(int mode);
    void clearDebugBuffer(int mode);
    void setWriteDebug(bool write);
    QString getLastValueInDebugBuffer(int);
    void removeLastValueInDebugBuffer(int);
    bool    getFullDebugInfo();
    qulonglong calculateCRC32(QByteArray*);


    Q_INVOKABLE virtual void debug(int, const QString&, bool = false);

    static TApplication* exemplar();

    virtual bool open();
    virtual void close();

    int getReportTemplateType();
    QString getReportTemplateExt();
    Q_INVOKABLE virtual bool drvFRisValid();
    Q_INVOKABLE virtual DriverFR* getDrvFR();
    virtual int decodeTimeOut(int);
    virtual int codeTimeOut(int);


    Q_INVOKABLE bool bankTerminalIsValid();
    Q_INVOKABLE BankTerminal* getBankTerminal();

    virtual TcpServer* getTcpServer();
    virtual TcpClient* getTcpClient();

    Q_INVOKABLE int virtual showMessage(QString message, QString question = "",
                    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::StandardButton defButton = QMessageBox::No);      // Вывести сообщение пользователю и возможно задать вопрос
    Q_INVOKABLE int showYesNo(QString question);

    Q_INVOKABLE QProcess* runProcess(QString, QString = "", bool = true);
    Q_INVOKABLE bool waitProcessEnd(QProcess *);
    virtual void barCodeReadyRead(QString);
    Q_INVOKABLE     bool    isBarCodeReaded();
    virtual void readCardReader(QKeyEvent*);

    Q_INVOKABLE void capturePhoto(QString fileName = "", QString deviceName = "");    // Захватить кадр с видеокамеры и записать в базу
    Q_INVOKABLE void saveFileToServer(QString, QString, FileType, bool = false);
    Q_INVOKABLE void savePhotoToServer(QString file, QString localFile);
    Q_INVOKABLE void saveFile(QString, QByteArray*);
    Q_INVOKABLE void print(QString = "");
    Q_INVOKABLE void print(QStringList);
    Q_INVOKABLE void printToArray(QString, QString);
    Q_INVOKABLE void printArray(QString);
    Q_INVOKABLE void clearPrintArrays();
    Q_INVOKABLE int printArrayCount(QString);
    MessageWindow* getMessageWindow();
    void    initConfig();
    QString     findFileFromEnv(QString);
    Q_INVOKABLE virtual void timeOut(int);
    Q_INVOKABLE bool isTimeOut();
    Q_INVOKABLE virtual void sleep(int);

    Q_INVOKABLE void setDirName(QString str);
    Q_INVOKABLE QString getOpenFileName(QWidget* parent = 0, const QString caption = QString(), const QString dir = QString(), const QString filter = QString(), QString* selectedFilter = 0, QFileDialog::Options options = 0);

    void saveCustomization();
    void printReportWithoutCleaning();
    Q_INVOKABLE virtual int runScript(QString);
    Q_INVOKABLE void printReport(QString, QSqlQuery* = 0);
    Q_INVOKABLE void printReport(QString, Dictionary*);
    Q_INVOKABLE QString getScript();                                  // Вернуть название скрипта, заданного в параметрах при запуске программы
    Q_INVOKABLE QString getScriptParameter(int = 0);

    Q_INVOKABLE void sendSMS(QString url, QString number, QString message, QString from = "", bool = false);                     // Посылка СМС через сервис SMS.RU
    Q_INVOKABLE void sendSMS(QString url, QString number, bool = false);                               // Посылка СМС через сервис SMS.RU

    void    setScriptMode(bool mode);
    Q_INVOKABLE bool    isScriptMode();

    void    setServerMode(bool mode);
    bool    isServerMode();

    static void    setSendCommandMode(bool mode);
    static bool    isSendCommandMode();

    QList<ScriptEngine*>     getScriptStack();
    void            appendScriptStack(ScriptEngine* script);
    void            removeLastScriptStack();
    ScriptEngine*   getLastScriptStack();

    QObject*        createPlugin(QString);
    virtual QMyExtSerialPort* getSerialPort(const QString & name, QObject * parent = 0);
    virtual MyProgressDialog* getMyProgressDialog(QString mess);
    QString         getReportFile(QString, bool, QWidget*, QRect);
    QString         getProcessFile(QString, QWidget*, QRect);

    void    openPlugins();

// Работа с пользовательской конфигурацией программы
    virtual QVariant        getConfigValue(QString name);
    QStringList     getConfigTypes();
    QString         getConfigTypeName(QString type);
    QHash<QString, ConfigEntry>* getConfigs();
    void            setConfigs(QHash<QString, ConfigEntry>* conf);
    QList<QString>     getConfigNames(QString type = "");
    virtual void            setConfig(QString type, QString name, QString label, ConfigEntryType valType, QVariant value);
    virtual void            removeConfig(QString name);

    static bool readParameters(int argc, char *argv[]);
    virtual QString getConfigFileName();

    bool initApplication();
    QString         OSType();
    void                    saveMessages();

    Q_INVOKABLE virtual void showError(QString);
    Updates*        getUpdates();
    static QString         getTrueApplicationName();


public slots:
    void loadScriptFile();
    void loadReportFile();
    void loadFormFile();

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
    BarCodeReader*          barCodeReader;
    CardCodeReader*         cardCodeReader;
    EMailClient*            smtpclient;
    bool                    fsWebCamIsValid;
    static QList<QString>       DebugModes;
    static TApplication*    Exemplar;
    DBFactory*              db;
    bool                    barCodeReaded;
    MessageWindow*          messagesWindow;
    Updates*                updates;
//    int                     secDiff;                                // Разница в секундах между временем на этой машине и на сервере
                                                                    // Если число положительное, то время на этих часах отстает
                                                                    // Чтобы получить приблизительное время на сервере
                                                                    // нужно к текущему времени прибавить эту разницу


    // Свойства, устанавливаемые из настроек приложения
    ReportTemplateTypes     reportTemplateType;                        // тип шаблона печати

    QHash<QString, QStringList>     arraysForPrint;
    TcpServer*              tcpServer;
    TcpClient*              tcpClient;
    static QTimer           timer;
    static bool             timeIsOut;
    bool                    scriptMode;
    static bool             sendCommandMode;
    QHash<QString, QString>     dirs;
    QString                 dirName;
    QHash<QString, ConfigEntry> configs;
    QList<QString>              configNames;
    QHash<QString, QString>     configTypes;
    QHash<QString, QStringList> tempDebugBuffer;
    bool                    debugToBuffer;
    bool                    writeDebug;
    static  bool            fullDebugInfo;
    static QString                 trueApplicationName;

    void loadConsts();
    QString getAnyPath(QString, QString = "", QString = "");
    void                    readSettings();
    void                    writeSettings();
    void            setConfigValue(QString name, QVariant value);
    void            setConfigTypeName(QString type, QString name) { configTypes.insert(type, name); }
    void            writeToDebugFile(QString, QString);

private slots:
    void                    setTimeIsOut();
};

#endif
