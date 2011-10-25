#include "mysqlrecord.h"


MySqlRecord::MySqlRecord(QObject* parent): QObject(parent), QScriptable()
{
    record = new QSqlRecord();
}


MySqlRecord::~MySqlRecord()
{
    delete record;
}


/*
SqlRecord::SqlRecord(QSqlRecord other, QObject* parent)
    :QObject(parent)
{
    record = other;
}
*/
