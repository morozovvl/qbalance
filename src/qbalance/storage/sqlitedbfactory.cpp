#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include "sqlitedbfactory.h"
#include "../kernel/app.h"
#include <iostream>
#include <sqlite3.h>

using namespace std;


static void upperFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if( argc != 1 )
        return;
    switch(sqlite3_value_type(argv[0]))
    {
            case SQLITE_NULL:
            {
                    sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
                    break;
            }
            case SQLITE_TEXT:
            {

                    QString wstr((char*)sqlite3_value_text(argv[0]));
                    QByteArray array = wstr.toUpper().toUtf8();
                    sqlite3_result_text(context, array.data(), array.size() , SQLITE_TRANSIENT );
                    break;
            }
            default:
                    sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
            break;
    }}


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
            QVariant v = db->driver()->handle();
            if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*")==0)
            {
                sqlite3 *db_handle = *static_cast<sqlite3 **>(v.data());
                if (db_handle != 0)
                { // check that it is not NULL
                    sqlite3_initialize();
                    sqlite3_create_function(db_handle, "upper", 1, SQLITE_UTF8, NULL, &upperFunc, NULL, NULL);
                }
            }
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


QString SQLiteDBFactory::getLogin()
{
    return "sa";
}


QString SQLiteDBFactory::getConnectionName()
{
    return QString("%1").arg(getDatabaseName());
}


void SQLiteDBFactory::loadSystemTables()
{
    DBFactory::loadSystemTables();

    QSqlQuery query = execQuery(QString("SELECT name, type FROM sqlite_master;"));
    while (query.next())
    {
            QString tableName = query.value(0).toString();
            QString type = query.value(1).toString();
            if (!tables.contains(tableName))
                tables.insert(tableName, type);
    }

    reloadDictionariesPermitions();
    dbIsOpened = true;
}


void SQLiteDBFactory::getColumnsProperties(QList<FieldType>* result, QString table, QString originTable, int level)
{
    QSqlQuery q = execQuery(QString("PRAGMA table_info(%1);").arg(table));
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


void SQLiteDBFactory::setFile(QString file, FileType type, QByteArray fileData, bool extend)
{
    QString fileName = file.replace(app->applicationDirPath(), "~");
    clearError();
    qulonglong size = app->calculateCRC32(&fileData);
    QString text;
    if (isFileExist(fileName, type, extend))
    {
        // Если в базе уже есть такой файл
        if (!extend)
            text = QString("UPDATE %1 SET %2 = hex('%10'), %3 = %4, %9 = current_timestamp WHERE %5 = '%6' AND %7 = %8;").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(size)
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(fileName)
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(type)
                                                                                  .arg(getObjectNameCom("файлы.датавремя"))
                                                                                  .arg(QString(fileData.toHex()));
         else
            text = QString("UPDATE %1 SET %2 = hex('%9'), %3 = %4 WHERE %5 = '%6' AND %7 = %8;").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(size)
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(fileName)
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(type)
                                                                                  .arg(QString(fileData.toHex()));
    }
    else
    {
        text = QString("INSERT INTO %1 (%2, %3, %4, %6) VALUES ('%7', %8, %9, hex('%10'));").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(fileName)
                                                                                  .arg(type)
                                                                                  .arg(size)
                                                                                  .arg(QString(fileData.toHex()));
    }
    if (text.size() > 0)
    {
        app->setWriteDebug(false);         // Не будем записывать в журнал команды сохранения файлов в БД, чтобы уменьшить разрастание журнала
        exec(text, true, (extend && extDbExist) ? dbExtend : db);
        app->setWriteDebug(true);
        if (!extend)
            saveUpdate(text);
    }
}


int SQLiteDBFactory::insertDictDefault(QString tableName, QHash<QString, QVariant>* values)
{
    int result = -1;
    QString command;
    clearError();
    if (values->size() == 0)
    {
        values->insert(getObjectNameCom(tableName + ".ИМЯ"), QVariant(""));
    }
    if (values->size() > 0)
    {
        QString fieldsList;
        QString valuesList;
        foreach (QString key, values->keys())
        {
            QString field = getObjectName(tableName + "." + key);
            field = field.size() > 0 ? field : key;
            if (fieldsList.size() > 0)
                fieldsList.append(',');
            fieldsList.append(field);
            QString str = values->value(key).toString();
            str.replace("'", "''");                         // Если в строке встречается апостроф, то заменим его двойным апострофом, иначе сервер не поймет
            str = "'" + str + "'";
            if (valuesList.size() > 0)
                valuesList.append(',');
            valuesList.append(str);
        }
        command = QString("INSERT INTO %1 (%2) VALUES (%3);").arg(getObjectNameCom(tableName))
                                                                          .arg(fieldsList)
                                                                          .arg(valuesList);
    }
    execQuery(command);
    result = getValue("SELECT last_insert_rowid();").toInt();
    if (sysTables.contains(tableName))
        saveUpdate(command);
    return result;
}


QString SQLiteDBFactory::getILIKEexpression(QString arg1, QString arg2)
{
    return QString("upper(%1) LIKE %2").arg(arg1).arg(arg2.toUpper());
}

