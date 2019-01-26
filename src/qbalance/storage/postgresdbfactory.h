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

    virtual QString getConnectionName();

    virtual void loadSystemTables();
//    virtual void reloadColumnHeaders();
    virtual void reloadColumnProperties();
    virtual int getSecDiff();

    virtual bool    lockDocument(int);
    virtual void    unlockDocument(int);
    virtual void    clearLockedDocumentList();

    virtual void getColumnsProperties(QList<FieldType>*, QString, QString, int);

protected:
    QSqlQuery               columnsProperties;

};

#endif // POSTGRESDBFACTORY_H
