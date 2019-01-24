#ifndef SQLITEDBFACTORY_H
#define SQLITEDBFACTORY_H
#include "dbfactory.h"


class SQLiteDBFactory : public DBFactory
{
public:
    SQLiteDBFactory();

    virtual bool open(QString = "", QString = "");
    virtual int openDBDialog();

    virtual QString getConnectionName();

    virtual void loadSystemTables();
    virtual void reloadColumnProperties();
};

#endif // SQLITEDBFACTORY_H
