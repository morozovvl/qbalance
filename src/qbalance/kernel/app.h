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
#include "dictionaries.h"
#include "documents.h"
#include "topers.h"
#include "barcodereader.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "../gui/guifactory.h"
#include "../gui/mainwindow.h"
#include "../gui/dialog.h"
#include "../gui/messagewindow.h"
#include "../driverfr/driverfr.h"

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


struct ConfigVars {
    QString         barCodeReaderPort;          // COM-порт сканера штрих кодов
    QString         frDriverPort;               // COM-порт фискального регистратора
    int             frDriverBaudRate;           // Скорость COM-порта фискального регистратора
    int             frDriverTimeOut;
    int             frDriverPassword;
    QString         cardReaderPrefix;           // Префикс магнитной карты
    int             localPort;                  // Порт, по которому программа принимает соединения
    QString         remoteHost;                 // Адрес удаленного хоста, к которому будет пытаться соединиться программа
    int             remotePort;                 // Порт удаленного хоста, к которому будет пытаться соединиться программа
    bool            saveFormConfigToDB;
};


class TApplication : public QApplication {
    Q_OBJECT

public:
    QHash<QString, Documents*> documents;                        // Объекты списков документов
    static QString userName;

    TApplication(int& argc, char** argv);
    ~TApplication();
    Q_INVOKABLE virtual Dictionaries* getDictionaries();
    Q_INVOKABLE Documents* getDocuments(int);
    void removeDocuments(int opNumber);
    Q_INVOKABLE DBFactory* getDBFactory() { return db; }
    Q_INVOKABLE void clearMessageOnStatusBar() { gui->getMainWindow()->getStatusBar()->clearMessage(); }
    Q_INVOKABLE virtual void showMessageOnStatusBar(const QString &message = "", int timeout = 3000 );
    Q_INVOKABLE QVariant getConst(QString);
    GUIFactory* getGUIFactory() { return gui; }
    Q_INVOKABLE QString getLogin() { return db->getLogin(); }
    Q_INVOKABLE bool isSA() { return getLogin().toLower() == "sa" ? true : false; }
    QDate getBeginDate() { return beginDate; }
    QDate getEndDate() { return endDate; }
    QString getFormsPath(QString = "");
    QString getScriptsPath();
    QString getReportsPath(QString = "");
    Q_INVOKABLE QString getPhotosPath(QString = "");
    QString getConfigPrefix() { return QString("%1-%2-%3").arg(db->getHostName()).arg(db->getPort()).arg(db->getDatabaseName()); }
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
    static QTextCodec* codec();

    static QString authors()       { return "Морозов Владимир (morozovvladimir@mail.ru)";}
    static int debugMode()        { return DebugMode;}
    static QString debugFileName() { return QString("debug%1.log").arg(DebugMode);}
    static QString errorFileName() { return "error.log";}
    static QFile&  debugFile()     { return *DebugFile;}
    static QString logTimeFormat() { return "dd.MM.yy hh.mm.ss.zzz";}
    static QString resourcesFile() { return applicationDirPath() + "/resources.qrc";}
    static QString getScriptFileName(int oper) { return QString("./scripts/формулы%1.qs").arg(oper); }
    static bool setDebugMode(const int& value);

    Q_INVOKABLE static void debug(int, const QString&, bool = false);

    static TApplication* exemplar();

    virtual bool open();
    virtual void close();

    int getReportTemplateType() { return reportTemplateType; }
    bool getSaveFormConfigToDb() { return config.saveFormConfigToDB; }
    QString getReportTemplateExt();
    Q_INVOKABLE bool drvFRisValid() { return driverFRisValid; }
    Q_INVOKABLE DriverFR* getDrvFR() { return driverFR; }

    void virtual showError(QString);
    void virtual showCriticalError(QString);

    Q_INVOKABLE QProcess* runProcess(QString, QString = "", bool = true);
    Q_INVOKABLE bool waitProcessEnd(QProcess *);
    void         barCodeReadyRead(QString);
    virtual bool readCardReader(QKeyEvent*);

    Q_INVOKABLE void capturePhoto(QString fileName = "", QString deviceName = "");    // Захватить кадр с видеокамеры и записать в базу
    Q_INVOKABLE void saveFileToServer(QString, QString, FileType, bool = false);
    Q_INVOKABLE void savePhotoToServer(QString file, QString localFile) { saveFileToServer(file, localFile, PictureFileType, true); }
    Q_INVOKABLE void saveFile(QString, QByteArray*);
    Q_INVOKABLE void print(QString = "");
    Q_INVOKABLE void printToArray(QString, QString);
    Q_INVOKABLE void printArray(QString);
    Q_INVOKABLE void clearPrintArrays();
    MessageWindow* getMessageWindow() { return messagesWindow; }
    int getSecDiff() { return secDiff; }
    void    initConfig();
    QString     findFileFromEnv(QString);
    Q_INVOKABLE void timeOut(int);
    Q_INVOKABLE void startTimeOut(int);
    Q_INVOKABLE bool isTimeOut() { return timeIsOut; }

    void saveCustomization();
    void printReportWithoutCleaning();
    void runScript(QString);

    ConfigVars* getConfig() { return &config; }

signals:
    void cardCodeReaded(QString);

private:
    Dictionaries*           dictionaryList;                               // Форма со списком справочников
    Topers*                 topersList;                                   // Форма со списком операций
    DBFactory*              db;
    GUIFactory*             gui;
    QDate                   beginDate;
    QDate                   endDate;
    DriverFR*               driverFR;
    bool                    driverFRisValid;
    bool                    driverFRlocked;
    bool                    fsWebCamIsValid;
    static QFile*           DebugFile;
    static int              DebugMode;
    static TApplication*    Exemplar;
    BarCodeReader*          barCodeReader;
    QString                 cardReaderCode;
    MessageWindow*          messagesWindow;
    int                     secDiff;                                // Разница в секундах между временем на этой машине и на сервере
                                                                    // Если число положительное, то время на этих часах отстает
                                                                    // Чтобы получить приблизительное время на сервере
                                                                    // нужно к текущему времени прибавить эту разницу


    // Свойства, устанавливаемые из настроек приложения
    ReportTemplateTypes     reportTemplateType;                        // тип шаблона печати
    ConfigVars              config;
//    QUiLoader               *formLoader;

    QHash<QString, QStringList>     arraysForPrint;
    TcpServer*              tcpServer;
    QTimer                  timer;
    bool                    timeIsOut;

    void loadConsts();
    QString getAnyPath(QString, QString = "");

private slots:
    void                    setTimeIsOut() { timeIsOut = true; }
};

#endif
