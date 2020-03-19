#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include "sqlitedbfactory.h"
#include <math.h>
#include "../kernel/app.h"
#include <iostream>
#include <sstream>
#include "../../sqlite/sqlite3.h"
//#include "fixed_point.h"

//using namespace std;

//#define double fpml::fixed_point<int32_t, 24>


static QString toString(double val)
{
    QString result;
/*
    std::stringstream buffer;
    buffer.precision(-3);
    buffer << val;
    result = QString().fromUtf8(buffer.str().c_str());
    qDebug() << QString("=== %1 %2").arg(val).arg(result);
*/
    result = QString("%1").arg(val);
    qDebug() << "===" << val << result;
    return result;
}


static double fromString(const char * val)
{
    double result;
/*
    std::stringstream buffer;
    buffer.precision(-3);
    buffer << val;
    buffer >> result;
    qDebug() << QString("*** %1 %2 %3").arg(val).arg(buffer.str().c_str()).arg(toString(result));
*/
    result = QString(val).toDouble();
    qDebug() << "***" << val << result;
    return result;
}


static void calcEndSaldo(sqlite3 *db, QString acc, long id)
{
    sqlite3_stmt *stmt;
    int rc;

   double      quan        = 0.0;
   double      saldo       = 0.0;
   double      dbQuan      = 0.0;
   double      debet       = 0.0;
   double      crQuan      = 0.0;
   double      credit      = 0.0;
   double      endQuan     = 0.0;
   double      endSaldo    = 0.0;
   double      endPrice    = 0.0;

    QString command = QString("SELECT КОЛ, САЛЬДО, ДБКОЛ, ДЕБЕТ, КРКОЛ, КРЕДИТ FROM сальдо WHERE СЧЕТ = '%1' AND КОД = %2;").arg(acc).arg(id);
    sqlite3_prepare_v2(db, command.toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        quan    = sqlite3_column_double(stmt, 0);
        saldo   = sqlite3_column_double(stmt, 1);
        dbQuan  = sqlite3_column_double(stmt, 2);
        debet   = sqlite3_column_double(stmt, 3);
        crQuan  = sqlite3_column_double(stmt, 4);
        credit  = sqlite3_column_double(stmt, 5);
    }
    sqlite3_finalize(stmt);

    endQuan = quan + dbQuan - crQuan;
    endSaldo = saldo + debet - credit;
//    if (endQuan != zero)
//    {
//        endPrice = endSaldo / endQuan;
//    }

    command = QString("UPDATE сальдо SET КОНКОЛ = %1, КОНСАЛЬДО = %2, КОНЦЕНА = %3 WHERE СЧЕТ = '%4' AND КОД = %5;")
            .arg(toString(endQuan))
            .arg(toString(endSaldo))
            .arg(toString(endPrice))
            .arg(acc)
            .arg(id);

    sqlite3_exec(db, command.toUtf8().data(), 0 /*nullptr*/, 0 /*nullptr*/, 0 /*nullptr*/);
}




static void insertNewSaldo(sqlite3 *db, QString acc, long id)
{
    sqlite3_stmt *stmt;
    int analiticAcc = 0;

    sqlite3_prepare_v2(db, QString("SELECT АНАЛИТИКА FROM счета WHERE СЧЕТ = '%1';").arg(acc).toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
    if (sqlite3_step(stmt) == SQLITE_ROW)
        analiticAcc = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    if (analiticAcc == 1)
    {
        if (id > 0)
        {
            sqlite3_prepare_v2(db, QString("SELECT COUNT(*) FROM сальдо WHERE СЧЕТ = '%1' AND КОД = %2;").arg(acc).arg(id).toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                if (sqlite3_column_int(stmt, 0) == 0)
                    sqlite3_exec(db, QString("INSERT INTO сальдо (СЧЕТ, КОД)  VALUES ('%1', %2);").arg(acc).arg(id).toUtf8().data(), 0 /*nullptr*/, 0 /*nullptr*/, 0 /*nullptr*/);
            }
            sqlite3_finalize(stmt);
        }
    }
    else
    {
        sqlite3_prepare_v2(db, QString("SELECT COUNT(*) FROM сальдо WHERE СЧЕТ = '%1' AND КОД = 0;").arg(acc).toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            if (sqlite3_column_int(stmt, 0) == 0)
                sqlite3_exec(db, QString("INSERT INTO сальдо (СЧЕТ, КОД)  VALUES ('%1', 0);").arg(acc).toUtf8().data(), 0 /*nullptr*/, 0 /*nullptr*/, 0 /*nullptr*/);
        }
        sqlite3_finalize(stmt);
    }
}


static void calcDbSaldo(sqlite3 *db, QString acc, long id,double quan,double sum)
{
    sqlite3_stmt *stmt;
    int rc;

    int balanceAcc = 0;     // Счет является балансовым (1) или нет (0)
    int analiticAcc = 0;

    sqlite3_prepare_v2(db, QString("SELECT БАЛАНС, АНАЛИТИКА FROM счета WHERE СЧЕТ = '%1';").arg(acc).toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        balanceAcc = sqlite3_column_int(stmt, 0);
        analiticAcc = sqlite3_column_int(stmt, 1);
    }
    sqlite3_finalize(stmt);

    if (balanceAcc == 1)
    {
       double      dbQuan;
       double      debet;

        QString command = QString("SELECT ДБКОЛ, ДЕБЕТ FROM сальдо WHERE СЧЕТ = '%1' AND КОД = %2;").arg(acc).arg(id);
        sqlite3_prepare_v2(db, command.toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
        if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            dbQuan    = sqlite3_column_double(stmt, 0);
            debet   = sqlite3_column_double(stmt, 1);
        }
        sqlite3_finalize(stmt);

        dbQuan += quan;
        debet += sum;

        command = QString("UPDATE сальдо SET ДБКОЛ = %1, ДЕБЕТ = %2 WHERE СЧЕТ = '%3' AND КОД = %4;")
                .arg(analiticAcc == 0 ? "0.0" : toString(dbQuan))
            .arg(toString(debet))
            .arg(acc)
            .arg(id);

        rc = sqlite3_exec(db, command.toUtf8().data(), 0 /*nullptr*/, 0 /*nullptr*/, 0 /*nullptr*/);
        calcEndSaldo(db, acc, id);
    }
}




static void calcCrSaldo(sqlite3 *db, QString acc, long id,double quan,double sum)
{
    sqlite3_stmt *stmt;
    int rc;

    int balanceAcc = 0;     // Счет является балансовым (1) или нет (0)
    int analiticAcc = 0;

    sqlite3_prepare_v2(db, QString("SELECT БАЛАНС, АНАЛИТИКА FROM счета WHERE СЧЕТ = '%1';").arg(acc).toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        balanceAcc = sqlite3_column_int(stmt, 0);
        analiticAcc = sqlite3_column_int(stmt, 1);
    }
    sqlite3_finalize(stmt);

    if (balanceAcc == 1)
    {
       double crQuan;
       double credit;

        QString command = QString("SELECT КРКОЛ, КРЕДИТ FROM сальдо WHERE СЧЕТ = '%1' AND КОД = %2;").arg(acc).arg(id);
        sqlite3_prepare_v2(db, command.toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
        if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            crQuan   = sqlite3_column_double(stmt, 0);
            credit   = sqlite3_column_double(stmt, 1);
        }
        sqlite3_finalize(stmt);

        crQuan += quan;
        credit += sum;

        qDebug() << toString(credit) << toString(sum);

        command = QString("UPDATE сальдо SET КРКОЛ = %1, КРЕДИТ = %2 WHERE СЧЕТ = '%3' AND КОД = %4;")
                .arg(analiticAcc == 0 ? "0.0" : toString(crQuan))
            .arg(toString(credit))
            .arg(acc)
            .arg(id);

        qDebug() << command;

        rc = sqlite3_exec(db, command.toUtf8().data(), 0 /*nullptr*/, 0 /*nullptr*/, 0 /*nullptr*/);
        calcEndSaldo(db, acc, id);
    }
}




static void insertPrvFunc(sqlite3_context *context, int, sqlite3_value **argv)
{
    sqlite3 *db = sqlite3_context_db_handle(context);
    sqlite3_stmt *stmt;

    QString     newDbAcc((char*)sqlite3_value_text(argv[0]));
    long        newDbId = sqlite3_value_int64(argv[1]);
    QString     newCrAcc((char*)sqlite3_value_text(argv[2]));
    long        newCrId = sqlite3_value_int64(argv[3]);
   double      newQuan =sqlite3_value_double(argv[4]);
   double      newSum = fromString((char*)sqlite3_value_text(argv[5]));
    QString     newOper((char*)sqlite3_value_text(argv[6]));

    sqlite3_prepare_v2(db, QString("SELECT СЧИТАТЬ FROM топер WHERE ОПЕР = %1 AND НОМЕР = 1;").arg(newOper).toUtf8().data(), -1, &stmt, 0 /*nullptr*/);
    if (sqlite3_step(stmt) == SQLITE_ROW)
        if (sqlite3_column_int(stmt, 0) == 1)
        {
            insertNewSaldo(db, newDbAcc, newDbId);
            calcDbSaldo(db, newDbAcc, newDbId, newQuan, newSum);

            insertNewSaldo(db, newCrAcc, newCrId);
            calcCrSaldo(db, newCrAcc, newCrId, -newQuan, -newSum);
        }
    sqlite3_finalize(stmt);
}




static void calcPrvFunc(sqlite3_context *context, int, sqlite3_value **argv)
{
    sqlite3 *db = sqlite3_context_db_handle(context);

    QString     oldDbAcc((char*)sqlite3_value_text(argv[0]));
    long        oldDbId = sqlite3_value_int64(argv[1]);
    QString     oldCrAcc((char*)sqlite3_value_text(argv[2]));
    long        oldCrId = sqlite3_value_int64(argv[3]);
   double      oldQuan = sqlite3_value_double(argv[4]);
   double      oldSum = fromString((char*)sqlite3_value_text(argv[5]));
    QString     newDbAcc((char*)sqlite3_value_text(argv[6]));
    long        newDbId = sqlite3_value_int64(argv[7]);
    QString     newCrAcc((char*)sqlite3_value_text(argv[8]));
    long        newCrId = sqlite3_value_int64(argv[9]);
   double      newQuan = sqlite3_value_double(argv[10]);
   double      newSum = fromString((char*)sqlite3_value_text(argv[11]));

    // Cначала обработаем по дебетовому обороту
    if (oldDbId == newDbId)	// Ссылка на дебетовый объект не изменилась
        calcDbSaldo(db, oldDbAcc, oldDbId, newQuan - oldQuan, newSum - oldSum);
    else
    {
        calcDbSaldo(db, oldDbAcc, oldDbId, -oldQuan, -oldSum);
        insertNewSaldo(db, oldDbAcc, newDbId);
        calcDbSaldo(db, oldDbAcc, newDbId, newQuan, newSum);
    }

    // Теперь обработаем по кредитовому обороту

    if (oldCrId == newCrId)	// Ссылка на кредитовый объект не изменилась
        calcCrSaldo(db, oldCrAcc, oldCrId, newQuan - oldQuan, newSum - oldSum);
    else
    {
        calcCrSaldo(db, oldCrAcc, oldCrId, -oldQuan, -oldSum);
        insertNewSaldo(db, oldCrAcc, newCrId);
        calcCrSaldo(db, oldCrAcc, newCrId, newQuan, newSum);
    }
}




static void removePrvFunc(sqlite3_context *context, int, sqlite3_value **argv)
{
    sqlite3 *db = sqlite3_context_db_handle(context);

    QString     oldDbAcc((char*)sqlite3_value_text(argv[0]));
    long        oldDbId = sqlite3_value_int64(argv[1]);
    QString     oldCrAcc((char*)sqlite3_value_text(argv[2]));
    long        oldCrId = sqlite3_value_int64(argv[3]);
   double      oldQuan = sqlite3_value_double(argv[4]);
   double      oldSum = fromString((char*)sqlite3_value_text(argv[5]));

    // Cначала обработаем по дебетовому обороту
    calcDbSaldo(db, oldDbAcc, oldDbId, -oldQuan, -oldSum);

    // Теперь обработаем по кредитовому обороту
    calcCrSaldo(db, oldCrAcc, oldCrId, -oldQuan,  -oldSum);
}





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


bool SQLiteDBFactory::open(QString, QString)
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
                if (db_handle != 0 /*nullptr*/)
                {
                    sqlite3_initialize();

                    sqlite3_create_function(db_handle, "upper", 1, SQLITE_UTF8, 0 /*nullptr*/, &upperFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "UPPER", 1, SQLITE_UTF8, 0 /*nullptr*/, &upperFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "Upper", 1, SQLITE_UTF8, 0 /*nullptr*/, &upperFunc, 0 /*nullptr*/, 0 /*nullptr*/);

                    sqlite3_create_function(db_handle, "lower", 1, SQLITE_UTF8, 0 /*nullptr*/, &lowerFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "LOWER", 1, SQLITE_UTF8, 0 /*nullptr*/, &lowerFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "Lower", 1, SQLITE_UTF8, 0 /*nullptr*/, &lowerFunc, 0 /*nullptr*/, 0 /*nullptr*/);


                    sqlite3_create_function(db_handle, "encode", 2, SQLITE_UTF8, 0 /*nullptr*/, &encodeFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "ENCODE", 2, SQLITE_UTF8, 0 /*nullptr*/, &encodeFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "Encode", 2, SQLITE_UTF8, 0 /*nullptr*/, &encodeFunc, 0 /*nullptr*/, 0 /*nullptr*/);

                    sqlite3_create_function(db_handle, "insertPrv", 7, SQLITE_UTF8, 0 /*nullptr*/, &insertPrvFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "calcPrv", 12, SQLITE_UTF8, 0 /*nullptr*/, &calcPrvFunc, 0 /*nullptr*/, 0 /*nullptr*/);
                    sqlite3_create_function(db_handle, "removePrv", 6, SQLITE_UTF8, 0 /*nullptr*/, &removePrvFunc, 0 /*nullptr*/, 0 /*nullptr*/);

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

void SQLiteDBFactory::setConnectionTimeout(int secs)
{
    db->setConnectOptions("QSQLITE_BUSY_TIMEOUT=" + QString::number(secs));
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


void SQLiteDBFactory::_reloadColumnProperties(QString _t, QString _u)
{

    QSqlQuery query = execQuery(QString("SELECT tbl_name FROM sqlite_master s WHERE TYPE = '%1';").arg(_t));

    for (query.first(); query.isValid(); query.next())
    {
        QString tableName = query.record().value(0).toString();
        QSqlQuery query1 = execQuery(QString("PRAGMA table_info(%1);").arg(tableName));
        for (query1.first(); query1.isValid(); query1.next())
        {
            QSqlRecord record = query1.record();
            ColumnPropertyType col;

            QString type = "";
            QString length = "";
            QString precision = "";
            QString incomeType = record.value("type").toString().toUpper();
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

            col.name      = record.value("name").toString().trimmed();
            col.type      = type;
            col.length    = QString(length).toInt();
            col.precision = QString(precision).toInt();
            col.updateable = _u;

            columnsProperties.insert(tableName, col);
        }
    }
}


void SQLiteDBFactory::reloadColumnProperties()
{
    columnsProperties.clear();

    _reloadColumnProperties("table", "YES");
    _reloadColumnProperties("view", "NO");
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
            .arg(getObjectNameCom(docAttrTableName + ".КОД"))
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

    if (toper.size() > 1)
        beginTransaction();

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
        }
    }

    if (toper.size() > 1)
        commitTransaction();

    result = nDocStr;

    return result;
}




bool SQLiteDBFactory::removeDocStr(int nDocId, int nDocStr)      // Удалить строку в документе docId под номером nDocStr
{
    clearError();

    beginTransaction();

    int nOperNum = getValue(QString("SELECT %1 FROM %2 WHERE %3 = %4 LIMIT 1;")
                            .arg(getObjectNameCom("документы.ОПЕР"))
                            .arg(getObjectNameCom("документы"))
                            .arg(getObjectNameCom("документы.КОД"))
                            .arg(nDocId)).toInt();

    exec(QString("DELETE FROM %1 WHERE %2 = %3 AND %4 = %5;")
         .arg(getObjectNameCom("проводки"))
         .arg(getObjectNameCom("проводки.ДОККОД"))
         .arg(nDocId)
         .arg(getObjectNameCom("проводки.СТР"))
         .arg(nDocStr));

    QString attrTableName = QString("%1%2")
            .arg(getObjectName("атрибуты"))
            .arg(nOperNum);
    if (getValue(QString("SELECT COUNT(*) FROM sqlite_master WHERE name='%1';").arg(attrTableName)).toInt() > 0)
        exec(QString("DELETE FROM %1 WHERE %2 = %3 AND %4 = %5;")
             .arg(attrTableName)
             .arg(getObjectNameCom(attrTableName + ".ДОККОД"))
             .arg(nDocId)
             .arg(getObjectNameCom("проводки.СТР"))
             .arg(nDocStr));

    commitTransaction();
    return true;

/*
    nOper := (SELECT "ОПЕР" FROM "документы" WHERE "КОД" = nDocId);
    OPEN curResult FOR SELECT "НОМЕР" FROM "топер" WHERE "ОПЕР" = nOper AND "НЕЗАВИСИМ" = true;
    FETCH first FROM curResult INTO nFreeOper;
    WHILE found LOOP
        IF nFreeOper IS NOT NULL THEN
            IF (SELECT "СТР" FROM "проводки" WHERE "ДОККОД" = nDocId AND "НОМЕРОПЕР" = nFreeOper LIMIT 1) = nDocStr THEN
                IF (SELECT COUNT(*) FROM "проводки" WHERE "ДОККОД" = nDocId AND "ОПЕР" = nOper AND "СТР" <> nDocStr) > 1 THEN
                    nNewDocStr := (SELECT MIN("СТР") FROM "проводки" WHERE "ДОККОД" = nDocId AND "ОПЕР" = nOper AND "СТР" <> nDocStr);
                ELSE
                    nNewDocStr := 1;
                END IF;
                IF nNewDocStr IS NOT NULL AND nNewDocStr <> nDocStr THEN
                    INSERT INTO "проводки" ("ДОККОД", "СТР", "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА")
                        SELECT "ДОККОД", nNewDocStr, "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА" FROM "проводки" WHERE "ДОККОД" = nDocId AND "НОМЕРОПЕР" = nFreeOper LIMIT 1;
                END IF;
            END IF;
        END IF;
        FETCH next FROM curResult INTO nFreeOper;
    END LOOP;
    DELETE FROM "проводки" WHERE "ДОККОД" = nDocId AND "СТР" = nDocStr;
    IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname = 'public' AND tablename = 'атрибуты' || rtrim(ltrim(cast(nOper AS VARCHAR(10))))) > 0 THEN
        EXECUTE 'DELETE FROM "атрибуты' || nOper::text || '" WHERE "ДОККОД" = ' || nDocId::text || ' AND "СТР" = ' || nDocStr::text;
    END IF;
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
    QString fileName = file.replace(app->applicationDataDirPath(), "~");
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


bool SQLiteDBFactory::exec(QString str, bool showError, QSqlDatabase* db)
{
    return DBFactory::exec(str, showError, db);
}


QDate SQLiteDBFactory::toDate(QVariant d)
{
    return QDate().fromString(d.toString(), app->dateFormat());
}


QSqlQuery SQLiteDBFactory::execQuery(QString str, bool showError, QSqlDatabase* extDb)
{
    app->debug(1, QString("Query: %1").arg(str));
    clearError();
    QSqlQuery result;
    QSqlQuery* query;
    if (extDb != 0 /*nullptr*/ && extDb->isValid())
        query = new QSqlQuery(*extDb);
    else
        query = new QSqlQuery();

    if (!query->exec(str) && showError)
    {
        setError(query->lastError().text());
    }
    query->first();
    result = *query;
    delete query;
    return result;
}


int SQLiteDBFactory::querySize(QSqlQuery* q)
{
    q->last();
    return q->at() + 1;
}


//#undef double
