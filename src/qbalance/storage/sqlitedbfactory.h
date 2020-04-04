#ifndef SQLITEDBFACTORY_H
#define SQLITEDBFACTORY_H
#include "dbfactory.h"


class SQLiteDBFactory : public DBFactory
{
public:
    SQLiteDBFactory();

    virtual bool open(QString = "", QString = "");
    virtual int openDBDialog();
    virtual QString getLogin();
    virtual void setConnectionTimeout(int = 0);

    virtual QString getConnectionName();
    virtual void loadSystemTables();
    virtual void reloadColumnProperties();

    virtual int insertDictDefault(QString, QHash<QString, QVariant>*);                 // Вставляет в справочник новую строку
    virtual QString getILIKEexpression(QString, QString);

    virtual bool getPeriod(QDate&, QDate&);

    virtual bool createNewDictionary(QString, QString = "", bool = true);

    virtual QString getTrueValue();
    virtual QString getFalseValue();

    virtual int addDoc(int, QDate = QDate::currentDate());       // Создать новый документ по типовой операции operNumber с датой date
    virtual bool removeDoc(int);                                 // Удалить документ с идентификатором docId
    virtual int addDocStr(int, int, QString = "", int = 1, int = 0);    // Добавить новую строку в документ по типовой операции operNumber
    virtual bool removeDocStr(int, int);                                                          // Удалить строку в документе docId под номером nDocStr

    virtual QString getCurrentTimeStamp();

    Q_INVOKABLE virtual int getInsertReturningId(QString, QString, QString);

    virtual void setFile(QString, FileType, QByteArray, bool = false);
    Q_INVOKABLE virtual bool exec(QString = "", bool = true, QSqlDatabase* = 0 /*nullptr*/);

    virtual QDate toDate(QVariant);

    Q_INVOKABLE virtual QSqlQuery execQuery(QString, bool = true, QSqlDatabase* = 0 /*nullptr*/);

    virtual int querySize(QSqlQuery*);

private:
    void _reloadColumnProperties(QString, QString);
};

#endif // SQLITEDBFACTORY_H
