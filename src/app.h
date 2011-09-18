#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QMap>
#include <QDate>
#include <QString>
#include <QDir>
#include "custom.h"
#include "dictionary.h"
#include "dictionaries.h"
#include "documents.h"
#include "topers.h"
#include "gui/guifactory.h"

class Dictionaries;
class Topers;
class DBFactory;
class GUIFactory;
class Documents;
class MainWindow;

class TApplication : public Custom {
    Q_OBJECT

public:
    QMap<QString, Documents*> documents;                        // Объекты списков документов

    TApplication(QApplication*);
    virtual ~TApplication();
    QApplication* getApplication() { return Application; }
    Q_INVOKABLE Dictionaries* getDictionaries();
    QVariant getDictionaryProperty(QString, const char*);
    QVariant getToperProperty(int, QString);
    Q_INVOKABLE Documents* getDocuments(int);
    Q_INVOKABLE DBFactory* getDBFactory() { return db; }
    GUIFactory* getGUIFactory() { return gui; }
    QString getLogin() { return db->getLogin(); }
    QDate getBeginDate() { return beginDate; }
    QDate getEndDate() { return endDate; }
    QString getOrganizationName() { return organizationName; }
    QString getHomePath() { return QDir().currentPath(); }
    QString getFormsPath(QString formName = "");
    MainWindow* getMainWindow() { return gui->getMainWindow(); }
    void show() { gui->show(); }
    void showDictionaries() { dictionaryList->show(); }
    void showDocuments() { topersList->show(); }
    void showReports() { ; }
    void setPeriod() { gui->setPeriod(); }                                               // Установим рабочий интервал
    void setBeginDate(QDate date) { beginDate = date; }
    void setEndDate(QDate date) { endDate = date; }

    static QString encoding();
    static QTextCodec* codec();

    static QString name()          { return "Enterprise";}
    static QString authors()       { return "Морозов Владимир (morozovvladimir@mail.ru)";}
    static QString version()       { return "0.01";}
    static bool debugMode()        { return false;}
    static QTextStream& debugStream(){ return *DebugStream;}
    static QString debugFileName() { return "debug.log";}
    static QString errorFileName() { return "error.log";}
    static QFile&  debugFile()     { return *DebugFile;}
    static QString logTimeFormat() { return "dd.MM.yy hh.mm.ss";}
    static QString maxSumMask()    { return MaxSumMask;}
    static QString idFieldName()   { return IdFieldName;}
    static QString nameFieldName() { return NameFieldName;}
    static QString resourcesFile() { return QDir::currentPath() + "/src/resources.qrc";}
    static bool setDebugMode(const bool& value);

    static void debug(const QString& value);

    static TApplication* exemplar();
public slots:
    void showError(QString error) { gui->showError(error); }
    void showCriticalError(QString error) { gui->showCriticalError(error); }

private:
    Dictionaries* dictionaryList;                         // Форма со списком справочников
    Topers* topersList;                                   // Форма со списком операций
    DBFactory* db;
    GUIFactory* gui;
    QApplication* Application;
    QString organizationName;
    QDate beginDate;
    QDate endDate;

    bool doOpen();
    void doClose();
    void loadConsts();

    static QFile*        DebugFile;
    static bool          DebugMode;
    static QTextStream*  DebugStream;
    static QString       MaxSumMask;
    static QString IdFieldName;
    static QString NameFieldName;
    static TApplication* Exemplar;
};

#endif
