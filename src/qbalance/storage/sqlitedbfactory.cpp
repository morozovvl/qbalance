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


void SQLiteDBFactory::getColumnsProperties(QList<FieldType>* result, QString table, QString originTable, int level)
{
    QSqlQuery q = execQuery(QString("PRAGMA table_info(%1)").arg(table));
    q.first();
    while (q.isValid())
    {
        QString type = "";
        QString length = 0;
        QString precision = 0;
        QString incomeType = q.record().value("type").toString().toUpper();
        int leftBracket = incomeType.indexOf("(");
        int rightBracket = incomeType.indexOf(")");
        if (leftBracket >= 0)
        {
            type = incomeType.left(leftBracket);
            length = incomeType.mid(leftBracket + 1, rightBracket - leftBracket - 1);
            int commaPos = length.indexOf(",");
            if (commaPos >= 0)
            {
                precision = length.mid(commaPos + 1);
                length = length.left(commaPos);
            }
        }
        else
        {
            type = incomeType;
            length = "0";
            precision = "0";
        }


        FieldType fld;
        fld.table  = table;
        fld.name      = q.record().value("name").toString().trimmed();
        fld.type      = type;
        fld.length    = length.toInt();
        fld.precision = precision.toInt();
        fld.constReadOnly = false;
        if (fld.name == getObjectName("код"))
            fld.readOnly = true;
        else
        {
            if (level > 0)
                fld.readOnly = true;        // Если это связанный справочник, то у него любое поле запрещено изменять напрямую
            else
            {
                fld.readOnly  = false;
//                fld.readOnly  = record.value("updateable").toString().trimmed().toUpper() == "YES" ? false : true;
            }
        }
        fld.level = level;
        // Если это столбец из связанной таблицы, то наименование столбца приведем к виду "таблица__столбец"
        if (originTable.size() > 0 && originTable != table)
            fld.column = table.toUpper() + "__" + fld.name;
        else
            fld.column = fld.name;
        fld.header = fld.column;
        fld.headerExist = false;        // Пока мы не нашли для столбца заголовок
        fld.number    = 0;
        if (table == getObjectName("документы"))
        {
            if (fld.column == getObjectName("документы.комментарий"))
            {
                fld.readOnly = false;
                fld.constReadOnly = false;
            }
            else
            {
                fld.readOnly = true;
                fld.constReadOnly = true;
            }
        }
        if (table == getObjectName("проводки"))
        {
            if ((fld.column == getObjectName("проводки.дбкод")) ||
                (fld.column == getObjectName("проводки.кркод")) ||
                (fld.column == getObjectName("проводки.кол")) ||
                (fld.column == getObjectName("проводки.цена")) ||
                (fld.column == getObjectName("проводки.сумма")))
            {
                fld.readOnly = false;
                fld.constReadOnly = false;
            }
            else
            {
                fld.readOnly = true;
                fld.constReadOnly = true;
            }
        }
        result->append(fld);

        if (fld.name.left(4) == getObjectName("код") + "_" && level == 0)   // обработаем ссылку на связанную таблицу
        {
            QString dictName = fld.name;
            dictName.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
            dictName = dictName.toLower();                  // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
            getColumnsProperties(result, dictName, table, level + 1);

            if (dictName.left(9) == "документы" && dictName.size() > 9)
            {
                QString oper = dictName.remove("документы");
                QString dictName = QString("докатрибуты%1").arg(oper);
                if (isTableExists(dictName))
                {
                    getColumnsProperties(result, dictName, table, level + 1);
                }
            }
        }

        q.next();
    }

}
