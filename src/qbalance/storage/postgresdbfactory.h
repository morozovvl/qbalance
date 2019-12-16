#ifndef POSTGRESDBFACTORY_H
#define POSTGRESDBFACTORY_H
#include "dbfactory.h"

class PostgresDBFactory : public DBFactory
{
public:
    PostgresDBFactory();

    virtual bool open(QString, QString);
    virtual int openDBDialog();
    virtual void initDBFactory();
    virtual void setConnectionTimeout(int = 0);

    virtual QString getConnectionName();

    virtual void loadSystemTables();
    virtual void reloadColumnProperties();
    virtual int getSecDiff();
    virtual int insertDictDefault(QString, QHash<QString, QVariant>*);                 // Вставляет в справочник новую строку

    virtual bool    lockDocument(int);
    virtual void    unlockDocument(int);
    virtual void    clearLockedDocumentList();

    virtual QString getILIKEexpression(QString, QString);

    virtual bool createNewDictionary(QString, QString = "", bool = true);

    Q_INVOKABLE virtual int getInsertReturningId(QString, QString, QString);

    virtual void setFile(QString, FileType, QByteArray, bool = false);
    virtual QDate toDate(QVariant);

    Q_INVOKABLE virtual QSqlQuery execQuery(QString, bool = true, QSqlDatabase* = nullptr);

    virtual int querySize(QSqlQuery*);

};

#endif // POSTGRESDBFACTORY_H
