#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include "sqlitedbfactory.h"
#include "../kernel/app.h"
#include <iostream>
#include "../../sqlite/sqlite3.h"
//#include "../../sqlite/sqlite3ext.h"


using namespace std;


static void upperFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if( argc != 1 )
        return;

    switch (sqlite3_value_type(argv[0]))
    {
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
    }
}


static void lowerFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if( argc != 1 )
        return;

    switch (sqlite3_value_type(argv[0]))
    {
            case SQLITE_TEXT:
            {
                    QString wstr((char*)sqlite3_value_text(argv[0]));
                    QByteArray array = wstr.toLower().toUtf8();
                    sqlite3_result_text(context, array.data(), array.size() , SQLITE_TRANSIENT );
                    break;
            }
            default:
                    sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
                    break;
    }
}


static void encodeFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if( argc != 2 )
        return;

    switch (sqlite3_value_type(argv[0]))
    {
            case SQLITE_TEXT:
            {
                    switch (sqlite3_value_type(argv[1]))
                    {
                        case SQLITE_TEXT:
                        {
                            QString wstr((char*)sqlite3_value_text(argv[0]));
                            if (QString((char*)sqlite3_value_text(argv[1])) == "hex")
                            {
                                QByteArray array = QByteArray::fromHex(QByteArray().append(wstr));
                                sqlite3_result_text(context, array.data(), array.size() , SQLITE_TRANSIENT );
                            }
                            break;
                        }
                        default:
                                sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
                                break;
                    }
                    break;
            }
            default:
                    sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
                    break;
    }
}

/*
static void to_charFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if( argc != 2 )
        return;

    switch (sqlite3_value_type(argv[0]))
    {
            case SQLITE_TEXT:
            {
                    switch (sqlite3_value_type(argv[1]))
                    {
                        case SQLITE_TEXT:
                        {
                            QString wstr((char*)sqlite3_value_text(argv[0]));
                            QString format((char*)sqlite3_value_text(argv[0]));
                            QByteArray array = wstr..toUtf8();
                            sqlite3_result_text(context, array.data(), array.size() , SQLITE_TRANSIENT );
                            break;
                        }
                        default:
                                sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
                                break;
                    }
                    break;
            }
            default:
                    sqlite3_result_text(context, "NULL", 4, SQLITE_STATIC );
                    break;
    }
}
*/


SQLiteDBFactory::SQLiteDBFactory(): DBFactory()
{
    dbName = "qbalance";
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));

    if (db->isValid())
        dbExtend = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "qt_sql_pictures_connection"));
}


bool SQLiteDBFactory::open(QString login, QString password)
{
    clearError();
    if (db->isValid())
    {
        db->setDatabaseName(dbName + ".sqlite3");
        if (db->open())
        {
            dbExtend->setDatabaseName(dbName + "_extend.sqlite3");
            if (dbExtend->open())
            {
                extDbExist = true;
            }

            QVariant v = db->driver()->handle();
            if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*") == 0)
            {
                sqlite3 *db_handle = *static_cast<sqlite3 **>(v.data());
                if (db_handle != nullptr)
                {
                    sqlite3_initialize();

                    sqlite3_create_function(db_handle, "upper", 1, SQLITE_UTF8, NULL, &upperFunc, NULL, NULL);
                    sqlite3_create_function(db_handle, "UPPER", 1, SQLITE_UTF8, NULL, &upperFunc, NULL, NULL);
                    sqlite3_create_function(db_handle, "Upper", 1, SQLITE_UTF8, NULL, &upperFunc, NULL, NULL);

                    sqlite3_create_function(db_handle, "lower", 1, SQLITE_UTF8, NULL, &lowerFunc, NULL, NULL);
                    sqlite3_create_function(db_handle, "LOWER", 1, SQLITE_UTF8, NULL, &lowerFunc, NULL, NULL);
                    sqlite3_create_function(db_handle, "Lower", 1, SQLITE_UTF8, NULL, &lowerFunc, NULL, NULL);


                    sqlite3_create_function(db_handle, "encode", 2, SQLITE_UTF8, NULL, &encodeFunc, NULL, NULL);
                    sqlite3_create_function(db_handle, "ENCODE", 2, SQLITE_UTF8, NULL, &encodeFunc, NULL, NULL);
                    sqlite3_create_function(db_handle, "Encode", 2, SQLITE_UTF8, NULL, &encodeFunc, NULL, NULL);
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
        QString length = "";
        QString precision = "";
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


bool SQLiteDBFactory::getPeriod(QDate& begDate, QDate& endDate)
{
    bool result = false;
    clearError();
    if (isTableExists(getObjectName("блокпериоды")))
    {
        QSqlQuery query = execQuery(QString("SELECT %1, %2 FROM %3 WHERE %4='%5';").arg(getObjectNameCom("блокпериоды.начало"))
                                                                               .arg(getObjectNameCom("блокпериоды.конец"))
                                                                               .arg(getObjectNameCom("блокпериоды"))
                                                                               .arg(getObjectNameCom("блокпериоды.пользователь"))
                                                                               .arg(app->getLogin()));
        if (query.first())
        {
            begDate = QDate().fromString(query.record().field(0).value().toString(), "dd.MM.yyyy");
            endDate = QDate().fromString(query.record().field(1).value().toString(), "dd.MM.yyyy");
            result = true;
        }
    }
    return result;
}


bool SQLiteDBFactory::createNewDictionary(QString tName, QString tTitle/* = ""*/, bool menu)
{
    if (!isTableExists(tName))
    {   // Если такой таблицы нет, то добавим ее
        QString command = QString("CREATE TABLE \"%1\" ("    \
                                  "%2 INTEGER PRIMARY KEY," \
                                  "%3 CHARACTER VARYING(100) DEFAULT '');")
                                  .arg(tName)
                                  .arg(getObjectNameCom("код"))
                                  .arg(getObjectNameCom("имя"));
        if (exec(command))
        {
            command = QString("INSERT INTO %1 (%2, %3, %4, %5) VALUES (%6, %7, '%8', '%9');")
                        .arg(getObjectNameCom("доступ"))
                        .arg(getObjectNameCom("доступ.меню"))
                        .arg(getObjectNameCom("доступ.код_типыобъектов"))
                        .arg(getObjectNameCom("доступ.имя_пользователи"))
                        .arg(getObjectNameCom("доступ.имя"))
                        .arg(menu ? getTrueValue() : getFalseValue())
                        .arg(getTypeId(getObjectName("типыобъектов.справочник")))
                        .arg(getLogin())
                        .arg(tName);
            if (exec(command))
            {
                command = QString("INSERT INTO %1 (%2, %3, %4) VALUES ('%5', '%6', '%6');")
                            .arg(getObjectNameCom("справочники"))
                            .arg(getObjectNameCom("справочники.имя"))
                            .arg(getObjectNameCom("справочники.имя_в_списке"))
                            .arg(getObjectNameCom("справочники.комментарий"))
                            .arg(tName)
                            .arg(tTitle);
                if (exec(command))
                {
/*
                    command = QString("CREATE TRIGGER \"testdeleting_%1\" "  \
                                      "BEFORE DELETE ON \"%1\" " \
                                      "FOR EACH ROW " \
                                      "EXECUTE PROCEDURE testdeletingdictobject();")
                                    .arg(tName);
                    if (exec(command))
                    {
                        command = QString("CREATE TRIGGER \"testinserting_%1\" "  \
                                          "BEFORE INSERT ON \"%1\" " \
                                          "FOR EACH ROW " \
                                          "EXECUTE PROCEDURE testinsertingid();")
                                        .arg(tName);
                        if (exec(command))
                        {
                            command = QString("CREATE TRIGGER \"testupdating_%1\" "  \
                                              "BEFORE UPDATE ON \"%1\" " \
                                              "FOR EACH ROW " \
                                              "EXECUTE PROCEDURE testupdatingid();")
                                            .arg(tName);
                            if (exec(command))
                            {
                                return true;
                            }
                        }
                    }
*/
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}


QString SQLiteDBFactory::getTrueValue()
{
    return "1";
}


QString SQLiteDBFactory::getFalseValue()
{
    return "0";
}


int SQLiteDBFactory::addDoc(int operNumber, QDate dDate)
{
    int result = 0;
    clearError();

    beginTransaction();
    QString cNumber = "";
    QString cNumName = getValue(QString("SELECT RTRIM(%1) FROM %2 WHERE %3 = %4 AND %5 = 1 LIMIT 1;")
                                .arg(getObjectNameCom("топер.НУМЕРАТОР"))
                                .arg(getObjectNameCom("топер"))
                                .arg(getObjectNameCom("топер.ОПЕР"))
                                .arg(operNumber)
                                .arg(getObjectNameCom("топер.НОМЕР"))).toString();     // Загрузим наименование нумератора
    if (cNumName.size() > 0)
    {
        int nValue = getValue(QString("SELECT %1 FROM %2 WHERE RTRIM(%3) = '%4' LIMIT 1;")
                              .arg(getObjectNameCom("нумераторы.ЗНАЧЕНИЕ"))
                              .arg(getObjectNameCom("нумераторы"))
                              .arg(getObjectNameCom("нумераторы.ИМЯ"))
                              .arg(cNumName)).toInt();                              // Получим новое значение нумератора
        nValue++;
        execQuery(QString("UPDATE %1 SET %2 = %3 WHERE RTRIM(%4) = '%5';")
                  .arg(getObjectNameCom("нумераторы"))
                  .arg(getObjectNameCom("нумераторы.ЗНАЧЕНИЕ"))
                  .arg(nValue)
                  .arg(getObjectNameCom("нумераторы.ИМЯ"))
                  .arg(cNumName));   // Сохраним новое значение нумератора
        cNumber = QString("%1").arg(nValue);
    }

    execQuery(QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7) VALUES ('%8', CURRENT_TIMESTAMP, %9, '%10', 0, 0);")
                  .arg(getObjectNameCom("документы"))
                  .arg(getObjectNameCom("документы.ДАТА"))
                  .arg(getObjectNameCom("документы.ДАТАВРЕМЯ"))
                  .arg(getObjectNameCom("документы.ОПЕР"))
                  .arg(getObjectNameCom("документы.НОМЕР"))
                  .arg(getObjectNameCom("документы.АВТО"))
                  .arg(getObjectNameCom("документы.КОД_ПЕРСОНАЛ"))
                  .arg(dDate.toString("dd.MM.yyyy"))
                  .arg(operNumber)
                  .arg(cNumber));
    int nDocId = getValue("SELECT last_insert_rowid();").toInt();
    result = nDocId;

    QString docAttrTableName = QString("%1%2")
            .arg(getObjectName("докатрибуты"))
            .arg(operNumber);
    if (getValue(QString("SELECT COUNT(*) FROM sqlite_master WHERE name='%1';").arg(docAttrTableName)).toInt() > 0)
        exec(QString("INSERT INTO %1 (%2) VALUES (%3);")
             .arg(getObjectNameCom(docAttrTableName))
             .arg(getObjectNameCom("КОД"))
             .arg(nDocId));

    commitTransaction();

    return result;
}


void SQLiteDBFactory::removeDoc(int nDocId)
{
   clearError();

   beginTransaction();

   int nOperNum = getValue(QString("SELECT %1 FROM %2 WHERE %3 = %4 LIMIT 1;")
                           .arg(getObjectNameCom("документы.ОПЕР"))
                           .arg(getObjectNameCom("документы"))
                           .arg(getObjectNameCom("документы.КОД"))
                           .arg(nDocId)).toInt();
   exec(QString("DELETE FROM %1 WHERE %2 = %3;")
        .arg(getObjectNameCom("документы"))
        .arg(getObjectNameCom("документы.КОД"))
        .arg(nDocId));
   exec(QString("DELETE FROM %1 WHERE %2 = %3;")
        .arg(getObjectNameCom("проводки"))
        .arg(getObjectNameCom("проводки.ДОККОД"))
        .arg(nDocId));

   QString attrTableName = QString("%1%2")
           .arg(getObjectName("атрибуты"))
           .arg(nOperNum);
   if (getValue(QString("SELECT COUNT(*) FROM sqlite_master WHERE name='%1';").arg(attrTableName)).toInt() > 0)
       exec(QString("DELETE FROM %1 WHERE %2 = %3;")
            .arg(attrTableName)
            .arg(getObjectNameCom(attrTableName + ".ДОККОД"))
            .arg(nDocId));

   QString docAttrTableName = QString("%1%2")
           .arg(getObjectName("докатрибуты"))
           .arg(nOperNum);
   if (getValue(QString("SELECT COUNT(*) FROM sqlite_master WHERE name='%1';").arg(docAttrTableName)).toInt() > 0)
       exec(QString("DELETE FROM %1 WHERE %2 = %3;")
            .arg(docAttrTableName)
            .arg(getObjectNameCom(docAttrTableName + ".ДОККОД"))
            .arg(nDocId));

    commitTransaction();
}


int SQLiteDBFactory::addDocStr(int nOperId, int docId, QString cParam, int nCount, int nDocStr)    // Добавить новую строку в документ по типовой операции operNumber
{
    int result = 0;
    clearError();

    if (cParam.size() == 0)
        cParam = "0,0,0,0,0";

    if (nDocStr == 0)
    {
        nDocStr = getValue(QString("SELECT max(%1) AS max_value FROM %2 WHERE %3 = %4 AND %5 = %6;")
                           .arg(getObjectNameCom("проводки.СТР"))
                           .arg(getObjectNameCom("проводки"))
                           .arg(getObjectNameCom("проводки.ДОККОД"))
                           .arg(docId)
                           .arg(getObjectNameCom("проводки.ОПЕР"))
                           .arg(nOperId)).toInt();
        nDocStr++;
    }

    //  Проверим, существует ли файл с атрибутами для этой типовой операции
    bool bAttrExist = false;
    QString attrTableName = QString("%1%2")
            .arg(getObjectName("атрибуты"))
            .arg(nOperId);
    if (getValue(QString("SELECT COUNT(*) FROM sqlite_master WHERE name='%1';").arg(attrTableName)).toInt() > 0)
        bAttrExist = true;

    // Загрузим список типовых операций
    QSqlQuery toper = execQuery(QString("SELECT %1, %2, %3, %4 FROM %5 WHERE %6 = %7 ORDER BY %3;")
                                .arg(getObjectNameCom("топер.ДБСЧЕТ"))
                                .arg(getObjectNameCom("топер.КРСЧЕТ"))
                                .arg(getObjectNameCom("топер.НОМЕР"))
                                .arg(getObjectNameCom("топер.НЕЗАВИСИМ"))
                                .arg(getObjectNameCom("топер"))
                                .arg(getObjectNameCom("топер.ОПЕР"))
                                .arg(nOperId));

    QStringList paramList = cParam.split(QRegExp(","));

    for (int i = 0; i < nCount; i++)
    {
        if (bAttrExist)
        {
            int attrCount = getValue(QString("SELECT COUNT(*) FROM %1 WHERE %2 = %3 AND %4 = %5;")
                                       .arg(getObjectNameCom(attrTableName))
                                       .arg(getObjectNameCom("проводки.ДОККОД"))
                                       .arg(docId)
                                       .arg(getObjectNameCom("проводки.СТР"))
                                       .arg(nDocStr)).toInt();
            if (attrCount == 0)
            {
                exec(QString("INSERT INTO %1 (%2, %3, %4) VALUES ((SELECT COALESCE((SELECT MAX(%2) FROM %1), 0) + 1), %5, %3);")
                     .arg(getObjectNameCom(attrTableName))
                     .arg(getObjectNameCom("проводки.КОД"))
                     .arg(getObjectNameCom("проводки.ДОККОД"))
                     .arg(getObjectNameCom("проводки.СТР"))
                     .arg(docId));


            }
        }

        QString cParam1 = cParam;

        if (toper.first())
        {
            int tc = 0;
            do
            {
                QString cDbAcc  = toper.record().value(getObjectName("топер.ДБСЧЕТ")).toString();
                QString cCrAcc  = toper.record().value(getObjectName("топер.КРСЧЕТ")).toString();
                int nNum        = toper.record().value(getObjectName("топер.НОМЕР")).toInt();

                QString nDbId   = paramList[tc * 5];
                QString nCrId   = paramList[tc * 5 + 1];
                QString nQuan   = paramList[tc * 5 + 2];
                QString nPrice  = paramList[tc * 5 + 3];
                QString nSum    = paramList[tc * 5 + 4];

                QString insertCommand = QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13) \
                                                VALUES ((SELECT MAX(%2)+1 FROM %1), %14, %15, %16, %17, %18, %19, %20, %21, %22, %23, %24);")
                                                         .arg(getObjectNameCom("проводки"))
                                                         .arg(getObjectNameCom("проводки.КОД"))
                                                         .arg(getObjectNameCom("проводки.ДОККОД"))
                                                         .arg(getObjectNameCom("проводки.СТР"))
                                                         .arg(getObjectNameCom("проводки.ОПЕР"))
                                                         .arg(getObjectNameCom("проводки.НОМЕРОПЕР"))
                                                         .arg(getObjectNameCom("проводки.ДБСЧЕТ"))
                                                         .arg(getObjectNameCom("проводки.ДБКОД"))
                                                         .arg(getObjectNameCom("проводки.КРСЧЕТ"))
                                                         .arg(getObjectNameCom("проводки.КРКОД"))
                                                         .arg(getObjectNameCom("проводки.КОЛ"))
                                                         .arg(getObjectNameCom("проводки.ЦЕНА"))
                                                         .arg(getObjectNameCom("проводки.СУММА"))
                                                         .arg(docId)
                                                         .arg(nDocStr)
                                                         .arg(nOperId)
                                                         .arg(nNum)
                                                         .arg(cDbAcc)
                                                         .arg(nDbId)
                                                         .arg(cCrAcc)
                                                         .arg(nCrId)
                                                         .arg(nQuan)
                                                         .arg(nPrice)
                                                         .arg(nSum);

                if (toper.record().value(getObjectName("топер.НЕЗАВИСИМ")).toBool())
                {
                    int nFreeCount = getValue(QString("SELECT count(*) FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = %7;")
                                              .arg(getObjectNameCom("проводки"))
                                              .arg(getObjectNameCom("проводки.ДОККОД"))
                                              .arg(docId)
                                              .arg(getObjectNameCom("проводки.ОПЕР"))
                                              .arg(nOperId)
                                              .arg(getObjectNameCom("проводки.НОМЕРОПЕР"))
                                              .arg(nNum)
                                              ).toInt();
                    if (nFreeCount == 0)
                        exec(insertCommand);
                }
                else
                    exec(insertCommand);
                tc++;
            } while (toper.next());

            nDocStr++;
        }
    }

    result = nDocStr;

    return result;

/*
CREATE OR REPLACE FUNCTION sp_insertdocstr(
    noper integer,
    ndocid integer,
    pcparam character varying,
    pncount integer,
    pndocstr integer)
  RETURNS integer AS
$BODY$
DECLARE nNum INTEGER;
    cDbAcc VARCHAR(5);
    cCrAcc VARCHAR(5);
    nDbId INTEGER;
    nCrId INTEGER;
    nQuan NUMERIC(8,3);
    nPrice NUMERIC(14,2);
    nSum NUMERIC(14,2);
    cParam1 VARCHAR(100);
    cParam VARCHAR(100);
    nCount INTEGER;
    nCount1 INTEGER;
    nDocStr INTEGER;
    nFreeCount INTEGER;
    bFreePrv BOOLEAN;
    curResult REFCURSOR;
    cCommand VARCHAR(1000);
    bAttrExist BOOLEAN;
BEGIN
    cParam := pcParam;
    nCount := pnCount;
    nDocStr := pnDocStr;

    IF nCount IS NULL THEN
        nCount := 1;
    END IF;
    IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname = 'public' AND tablename = 'атрибуты' || rtrim(ltrim(cast(nOper AS VARCHAR(10))))) > 0 THEN
        bAttrExist := TRUE;
    ELSE
        bAttrExist := FALSE;
    END IF;
    IF nDocStr IS NULL OR nDocStr = 0 THEN
        -- найдем наибольший "НОМЕР" строки в документе
        nDocStr := (SELECT max(p."СТР") AS max_value FROM "проводки" p WHERE p."ДОККОД" = nDocId AND p."ОПЕР" = noper);
        IF nDocStr IS NULL THEN
            nDocStr := 1;
        ELSE
            nDocStr := nDocStr + 1;
        END IF;
    END IF;
    -- вставим в документ проводки для новой строки
    OPEN curResult FOR SELECT "ДБСЧЕТ", "КРСЧЕТ", "НОМЕР", "НЕЗАВИСИМ"  FROM "топер" WHERE "ОПЕР" = noper ORDER BY "НОМЕР";
    WHILE nCount > 0 LOOP
        -- Проверим, не использует ли документ таблицу атрибутов, и если использует, то добавим строку в таблицу атрибутов
        IF bAttrExist THEN
            EXECUTE 'SELECT COUNT(*) FROM "атрибуты'  || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" WHERE "ДОККОД" = ' || nDocId::text || ' AND "СТР" = ' || nDocStr::text INTO nCount1;
            IF nCount1 = 0 THEN
                EXECUTE 'INSERT INTO "атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" ("КОД", "ДОККОД", "СТР") VALUES ((SELECT COALESCE((SELECT MAX("КОД") FROM "атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '"), 0) + 1), ' || nDocId || ', ' || nDocStr || ');';

            END IF;
        END IF;
        cParam1 := cParam;
        FETCH first FROM curResult INTO cDbAcc, cCrAcc, nNum, bFreePrv;
        WHILE found LOOP
            IF length(cParam) = 0 THEN
                cParam1 := '0,0,0,0,0,';
            END IF;
            nDbId := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '999999999');
            cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
            nCrId := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '999999999');
            cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
            nQuan := to_number(replace(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '.', ','), '99999d999');
            cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
            nPrice := to_number(replace(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '.', ','), '99999999d99');
            cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
            nSum := to_number(replace(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '.', ','), '99999999d99');
            cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
            IF bFreePrv THEN
                nFreeCount := (SELECT count(*) FROM "проводки" p WHERE p."ДОККОД" = nDocId AND p."ОПЕР" = noper AND p."НОМЕРОПЕР" = nNum);
                IF nFreeCount = 0 THEN
                    INSERT INTO "проводки" ("КОД", "ДОККОД", "СТР", "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА")
                        VALUES ((SELECT MAX("КОД")+1 FROM "проводки"), nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
                END IF;
            ELSE
                INSERT INTO "проводки" ("КОД", "ДОККОД", "СТР", "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА")
                    VALUES ((SELECT MAX("КОД")+1 FROM "проводки"), nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
            END IF;
            FETCH NEXT FROM curResult INTO cDbAcc, cCrAcc, nNum, bFreePrv;
        END LOOP;
        nCount := nCount - 1;
        nDocStr := nDocStr + 1;
    END LOOP;
    nDocStr := nDocStr - 1;
    CLOSE curResult;
RETURN nDocStr;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION sp_insertdocstr(integer, integer, character varying, integer, integer)
  OWNER TO sa;
GRANT EXECUTE ON FUNCTION sp_insertdocstr(integer, integer, character varying, integer, integer) TO sa;
GRANT EXECUTE ON FUNCTION sp_insertdocstr(integer, integer, character varying, integer, integer) TO public;
GRANT EXECUTE ON FUNCTION sp_insertdocstr(integer, integer, character varying, integer, integer) TO "продавец";

*/
}


QString SQLiteDBFactory::getCurrentTimeStamp()
{
    return "(datetime('now','localtime'))";
}


int SQLiteDBFactory::getInsertReturningId(QString tableName, QString columns, QString values)
{
    exec(QString("INSERT INTO %1 (%2) VALUES (%3);")
                    .arg(getObjectNameCom(tableName))
                    .arg(columns)
                    .arg(values));
    return getValue("SELECT last_insert_rowid();").toInt();
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
            text = QString("UPDATE %1 SET %2 = hex('%10'), %3 = %4, %9 = %11 WHERE %5 = '%6' AND %7 = %8;")
                        .arg(getObjectNameCom("файлы"))
                        .arg(getObjectNameCom("файлы.значение"))
                        .arg(getObjectNameCom("файлы.контрсумма"))
                        .arg(size)
                        .arg(getObjectNameCom("файлы.имя"))
                        .arg(fileName)
                        .arg(getObjectNameCom("файлы.тип"))
                        .arg(type)
                        .arg(getObjectNameCom("файлы.датавремя"))
                        .arg(QString(fileData.toHex()))
                        .arg(getCurrentTimeStamp());
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


