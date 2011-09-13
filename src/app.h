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

class App : public Custom {
    Q_OBJECT

public:
    QMap<QString, Documents*> documents;                        // Объекты списков документов

    App(QApplication*);
    virtual ~App() { ; }
    QApplication* getApplication() { return application; }
    Q_INVOKABLE Dictionaries* getDictionaries() { return dictionaryList; }
    QVariant getDictionaryProperty(QString dictName, const char* property) { return dictionaryList->getDictionaryProperty(dictName, property); }
    QVariant getToperProperty(int operNumber, QString property) { return topersList->getToperProperty(operNumber, property); }
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

public slots:
    void showError(QString error) { gui->showError(error); }
    void showCriticalError(QString error) { gui->showCriticalError(error); }

private:
    Dictionaries* dictionaryList;                         // Форма со списком справочников
    Topers* topersList;                                   // Форма со списком операций
    DBFactory* db;
    GUIFactory* gui;
    QApplication* application;
    QString organizationName;
    QDate beginDate;
    QDate endDate;

    bool doOpen();
    void doClose();
    void loadConsts();
};

#endif
