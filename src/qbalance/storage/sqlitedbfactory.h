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

    virtual QString getConnectionName();
    virtual void loadSystemTables();
    virtual void getColumnsProperties(QList<FieldType>*, QString = "", QString = "", int = 0);

    virtual void setFile(QString, FileType, QByteArray, bool = false);
    virtual int insertDictDefault(QString, QHash<QString, QVariant>*);                 // Вставляет в справочник новую строку
    virtual QString getILIKEexpression(QString, QString);

    virtual bool getPeriod(QDate&, QDate&);
};

#endif // SQLITEDBFACTORY_H
