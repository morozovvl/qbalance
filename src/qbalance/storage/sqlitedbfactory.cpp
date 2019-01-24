#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include "sqlitedbfactory.h"
#include "../kernel/app.h"


SQLiteDBFactory::SQLiteDBFactory(): DBFactory()
{
    dbName = "qbalance.sqlite3";
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    if (db->isValid())
        dbExtend = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "qt_sql_pictures_connection"));
}


bool SQLiteDBFactory::open(QString login, QString password)
{
    clearError();
    if (db->isValid())
    {
        db->setDatabaseName(dbName);
        if (db->open())
        {
            qDebug() << "Ok";
            return true;
        }
    }
    return false;
}


int SQLiteDBFactory::openDBDialog()
{
    int returnCode = 0;     // По умолчанию будем считать, что удалось открыть БД
    if (open())
        initDBFactory();
    else
        returnCode = -2;
    return returnCode;
}


QString SQLiteDBFactory::getConnectionName()
{
    return QString("%1").arg(getDatabaseName());
}


void SQLiteDBFactory::loadSystemTables()
{
    DBFactory::loadSystemTables();

    reloadDictionariesPermitions();
    dbIsOpened = true;
}


void SQLiteDBFactory::reloadColumnProperties()
{
    DBFactory::reloadColumnProperties();
/*
    columnsProperties = execQuery("SELECT DISTINCT lower(trim(table_name)) AS table_name, ins.ordinal_position::integer - 1 AS \"order\", ins.column_name AS column_name, ins.data_type AS type, COALESCE(ins.character_maximum_length::integer, 0) + COALESCE(ins.numeric_precision::integer, 0) AS length, COALESCE(ins.numeric_scale::integer, 0) AS \"precision\", ins.is_updatable AS updateable " \
                                  "FROM information_schema.columns ins " \
                                  "ORDER BY table_name;");
*/
    QSqlQuery q = execQuery("PRAGMA table_info(товар)");
    q.first();
    while (q.isValid())
    {
        qDebug() << q.record().value("name") << q.record().value("type");
        q.next();
    }
}
