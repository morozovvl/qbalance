#ifndef DBFACTORY_H
#define DBFACTORY_H

#include <QObject>
#include "custom.h"
#include <QtSql>
#include <QDate>
#include <QVariantList>

class App;
extern App* app;

struct fldType {
    QString name;
    QString type;
    int length;
    int precision;
    bool readOnly;
};

class DBFactory : public Custom {
    Q_OBJECT

public:
    DBFactory();
    virtual ~DBFactory() { ; }
    bool addDoc(int, QDate);
    bool removeDoc(int);
    bool addDocStr(int, int, QString cParam = "''", int nQuan = 1, int nDocStr = 0);
    bool removeDocStr(int, int);
    void clearError();
    bool createNewDB(QString, QString, int);
    bool open(QString login, QString password) { return doOpen(login, password); }
    QString getHostName() { return cHostName; }
    QString getLogin() { return currentLogin; }
    int getPort() { return port; }
    QString getDatabaseName() { return cDbName; }
    QSqlQuery getColumnsHeaders(QString);
    QSqlQuery getDictionariesProperties();
    QStringList getFieldsList(QMap<int, fldType>*);
    Q_INVOKABLE virtual void getColumnsProperties(QMap<int, fldType>*, QString);
    void getColumnsRestrictions(QString, QMap<int, fldType>*);
    void addColumnProperties(QMap<int, fldType>*, QString, QString, int, int, bool readOnly = false);
    QSqlQuery getTopersProperties();
    QSqlQuery getToper(int);
    QString getPhotoDatabase();
    bool insertDictDefault(QString tableName, QStringList fields = QStringList(), QVariantList values = QVariantList());// Вставляет в справочник новую строку со значениями по умолчанию
    bool removeDictValue(QString, qulonglong);                                          // Удаляет строку в указанном справочнике с заданным кодом
    void setHostName(QString name) { cHostName = name; }
    void setPort(int portNum) { port = portNum; }
    void setDatabaseName(QString name) { cDbName = name; }
    void setPeriod(QDate, QDate);
    void getPeriod(QDate&, QDate&);
    void setConstDictId(QString, QVariant, int, int, int);
    QString prepareSearchParameters();
    Q_INVOKABLE bool exec(QString);
    Q_INVOKABLE QSqlQuery execQuery(QString);
    QStringList getUserList();
    QString getPhotoPath(QString);

    bool isError() { return wasError; }
    QString getErrorText() { return errorText; }

    QString initializationScriptPath() const;
    QStringList initializationScriptList() const;

private:
    QSqlDatabase* db;
    QString cHostName;
    QString currentLogin;
    int port;
    QString cDbName;
    bool wasError;
    QString errorText;
    void setError(QString);
    virtual bool doOpen();
    virtual bool doOpen(QString, QString);
    virtual void doClose();
};

#endif
