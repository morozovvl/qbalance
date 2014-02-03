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

#include <QApplication>
#include <QtCore/QMap>
#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtUiTools/QUiLoader>
#include <QtCore/QPluginLoader>
#include "dictionaries.h"
#include "documents.h"
#include "topers.h"
#include "../gui/guifactory.h"
#include "../gui/mainwindow.h"
#include "../gui/dialog.h"
#include "../driverfr/driverfr.h"

class Dictionaries;
class Topers;
class DBFactory;
class GUIFactory;
class Documents;
class MainWindow;
class Dialog;
//456 class QextSerialPort;


enum  ReportTemplateTypes
{
    OOreportTemplate,
    OOUNOreportTemplate,
    OOXMLreportTemplate,
    OpenRPTreportTemplate
};


class TApplication : public QApplication {
    Q_OBJECT

public:
    QMap<QString, Documents*> documents;                        // Объекты списков документов

    TApplication(int& argc, char** argv);
    ~TApplication();
    Q_INVOKABLE virtual Dictionaries* getDictionaries();
    Q_INVOKABLE Documents* getDocuments(int);
    void removeDocuments(int opNumber);
    Q_INVOKABLE DBFactory* getDBFactory() { return db; }
    Q_INVOKABLE void clearMessageOnStatusBar() { gui->getMainWindow()->getStatusBar()->clearMessage(); }
    Q_INVOKABLE void showMessageOnStatusBar(const QString &message = "", int timeout = 3000 );
    Q_INVOKABLE QVariant getConst(QString);
    GUIFactory* getGUIFactory() { return gui; }
    Q_INVOKABLE QString getLogin() { return db->getLogin(); }
    Q_INVOKABLE bool isSA() { return getLogin().toLower() == "sa" ? true : false; }
    QDate getBeginDate() { return beginDate; }
    QDate getEndDate() { return endDate; }
    QString getFormsPath(QString = "");
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
    Q_INVOKABLE Form* createForm1(QString);
    Q_INVOKABLE virtual void setIcons(QWidget*);         // Устанавливает иконки на кнопки указанной формы

    static QString encoding();
    static QTextCodec* codec();

    static QString authors()       { return "Морозов Владимир (morozovvladimir@mail.ru)";}
    static bool debugMode()        { return DebugMode;}
    static QTextStream& debugStream(){ return *DebugStream;}
    static QString debugFileName() { return "debug.log";}
    static QString errorFileName() { return "error.log";}
    static QFile&  debugFile()     { return *DebugFile;}
    static QString logTimeFormat() { return "dd.MM.yy hh.mm.ss";}
    static QString resourcesFile() { return applicationDirPath() + "/resources.qrc";}
    static QString getScriptFileName(int oper) { return QString("./scripts/формулы%1.qs").arg(oper); }
    static bool setDebugMode(const bool& value);

    static void debug(const QString& value);

    static TApplication* exemplar();

    virtual bool open();
    virtual void close();

    int getReportTemplateType() { return reportTemplateType; }
    bool getSaveFormConfigToDb() { return false; }
    QString getReportTemplateExt();
    Q_INVOKABLE bool drvFRisValid() { return driverFRisValid; }
    Q_INVOKABLE DriverFR* getDrvFR() { return driverFR; }

    void virtual showError(QString);
    void virtual showCriticalError(QString);

    Q_INVOKABLE bool runProcess(QString, QString = "");
    QObject* getPlugins() { return plugins; }

private:
    Dictionaries*           dictionaryList;                               // Форма со списком справочников
    Topers*                 topersList;                                   // Форма со списком операций
    DBFactory*              db;
    GUIFactory*             gui;
    QDate                   beginDate;
    QDate                   endDate;
    DriverFR*               driverFR;
    bool                    driverFRisValid;
    static QFile*           DebugFile;
    static bool             DebugMode;
    static QTextStream*     DebugStream;
    static TApplication*    Exemplar;
//456     QextSerialPort*         barCodeReaderComPort;
    QString                 barCodeString;
    QUiLoader*              formLoader;
    QObject*                plugins;

    // Свойства, устанавливаемые из настроек приложения
    ReportTemplateTypes     reportTemplateType;                        // тип шаблона печати

    void loadConsts();

private slots:
    void                    barCodeReadyRead();
};

#endif
