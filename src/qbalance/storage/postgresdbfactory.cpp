#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlDriver>
#include "postgresdbfactory.h"
#include "../kernel/app.h"
#include "../gui/guifactory.h"

PostgresDBFactory::PostgresDBFactory(): DBFactory()
{
    port = 5432;
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    if (db->isValid())
        dbExtend = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL", "qt_sql_pictures_connection"));
}


int PostgresDBFactory::openDBDialog()
{
    int result = app->getGUIFactory()->openDB();
    if (result == 0)
    {
        initDBFactory();
    }
    return result;
}


bool PostgresDBFactory::open(QString login, QString password)
{
    clearError();
    if (db->isValid())
    {
        currentLogin = login;
        currentPassword = password;

        db->setHostName(hostName);
        db->setDatabaseName(dbName);
        db->setPort(port);
        db->setUserName(currentLogin);
        db->setPassword(currentPassword);
        if (db->open())
        {
            exec("SET SEARCH_PATH TO system, public;");
            exec(QString("SET CLIENT_ENCODING TO '%1';").arg(TApplication::encoding()));
            exec("SET DATESTYLE TO ISO, DMY;");
            exec("SET standard_conforming_strings TO on;");

            // Откроем базу с картинками
            dbExtend->setHostName(hostName);
            dbExtend->setDatabaseName(dbName + "_extend");
            dbExtend->setPort(port);
            dbExtend->setUserName(currentLogin);
            dbExtend->setPassword(currentPassword);
            if (dbExtend->open())
            {
                 exec("SET SEARCH_PATH TO system, public;", dbExtend);
                 exec(QString("SET CLIENT_ENCODING TO '%1';").arg(TApplication::encoding()), dbExtend);
                 exec("SET DATESTYLE TO ISO, DMY;", dbExtend);
                 exec("SET standard_conforming_strings TO on;", dbExtend);

                 extDbExist = true;
            }

            pid = getValue("SELECT pg_backend_pid();").toInt();
            secDiff = QDateTime::currentDateTime().secsTo(getValue("SELECT now();", 0, 0).toDateTime());
            return true;
        }
        else
        {
            errorNumber = 1;    // Предположим, что сервер работает
            setError(db->lastError().text());
            db->setHostName(hostName);
            db->setDatabaseName("postgres");
            db->setPort(port);
            db->setUserName(login);
            db->setPassword(password);
            if (db->open())
            {
                db->close();
            }
            else
            {
                if (db->lastError().text().contains("could not connect to server"))
                    errorNumber = 2;    // Сервер не работает
            }
        }
    }
    return false;
}


void PostgresDBFactory::initDBFactory()
{
    DBFactory::initDBFactory();
/*
   // Откроем базу с картинками
    dbExtend->setHostName(hostName);
    dbExtend->setDatabaseName(dbName + "_extend");
    dbExtend->setPort(port);
    dbExtend->setUserName(currentLogin);
    dbExtend->setPassword(currentPassword);
    if (dbExtend->open())
    {
        exec(QString("set client_encoding='%1';").arg(TApplication::encoding()), dbExtend);
        exec("set standard_conforming_strings=on;");
        extDbExist = true;
    }
*/
}


QString PostgresDBFactory::getConnectionName()
{
    return QString("%1-%2-%3").arg(getHostName()).arg(getPort()).arg(getDatabaseName());
}


void PostgresDBFactory::loadSystemTables()
{
    DBFactory::loadSystemTables();

    objectTypes = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("типыобъектов")));

    config = execQuery("SELECT \"group\", \"name\", \"value\" FROM configs;");

    columnsRestrictions = execQuery(QString("SELECT %1 FROM %2 WHERE %3=5 AND (%4 ILIKE '\%'||\"current_user\"()::text||'%' OR %4 ILIKE '\%*\%');")
                                                               .arg(getObjectNameCom("доступ.имя"))
                                                               .arg(getObjectNameCom("доступ"))
                                                               .arg(getObjectNameCom("доступ.код_типыобъектов"))
                                                               .arg(getObjectNameCom("доступ.имя_пользователи")));

    QSqlQuery query = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("systables")));
    while (query.next())
    {
        sysTables.append(query.value(0).toString());
    }

    query = execQuery(QString("SELECT tablename, 'table' AS type FROM pg_tables UNION SELECT viewname AS tableName, 'view' AS type FROM pg_views;"));
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


void PostgresDBFactory::reloadColumnProperties()
{
    columnsProperties.clear();
    columnsProperties = execQuery("SELECT DISTINCT lower(trim(table_name)) AS table_name, ins.ordinal_position::integer - 1 AS \"order\", ins.column_name AS column_name, ins.data_type AS type, COALESCE(ins.character_maximum_length::integer, 0) + COALESCE(ins.numeric_precision::integer, 0) AS length, COALESCE(ins.numeric_scale::integer, 0) AS \"precision\", ins.is_updatable AS updateable " \
                                  "FROM information_schema.columns ins " \
                                  "ORDER BY table_name;");
}


int PostgresDBFactory::getSecDiff()
{
    return secDiff;
}


bool PostgresDBFactory::lockDocument(int docId)
{
    if (isTableExists("блокдокументов"))
    {
        int id = getValue(QString("SELECT \"PID\" FROM \"блокдокументов\" WHERE \"КОД_ДОКУМЕНТЫ\" = %1;").arg(docId)).toInt();
        if (id > 0)
            return false;
        exec(QString("INSERT INTO \"блокдокументов\" (\"PID\", \"КОД_ДОКУМЕНТЫ\") VALUES (%1, %2);").arg(pid).arg(docId));
    }
    return true;
}


void PostgresDBFactory::unlockDocument(int docId)
{
    if (isTableExists("блокдокументов"))
        exec(QString("DELETE FROM \"блокдокументов\" WHERE \"PID\" = %1 AND \"КОД_ДОКУМЕНТЫ\" = %2;").arg(pid).arg(docId));
}


void PostgresDBFactory::clearLockedDocumentList()
{
    if (isTableExists("блокдокументов"))
        exec(QString("DELETE FROM %1 WHERE %2 IN (SELECT %2 FROM %1 WHERE %2 NOT IN (SELECT pid FROM pg_stat_activity WHERE datname = '%3'))").arg("блокдокументов").arg("\"PID\"").arg(dbName));
}


void PostgresDBFactory::getColumnsProperties(QList<FieldType>* result, QString table, QString originTable, int level)
{
    QString fldTable = table;
    QString tableAlias = table;
    if (table.left(9) == "документы" && table.size() > 9)
    {
        table = "vw_спрдокументы";
    }

    for (columnsProperties.first(); columnsProperties.isValid(); columnsProperties.next())
    {
        QSqlRecord record = columnsProperties.record();
        if (QString().compare(record.value("table_name").toString(), table.trimmed(), Qt::CaseInsensitive) == 0)
        {
            FieldType fld;
            fld.table  = tableAlias;
            fld.name      = record.value("column_name").toString().trimmed();
            fld.type      = record.value("type").toString().trimmed();
            fld.length    = record.value("length").toInt();
            fld.precision = record.value("precision").toInt();
            fld.constReadOnly = false;
            if (fld.name == getObjectName("код"))
                fld.readOnly = true;
            else
            {
                if (level > 0)
                    fld.readOnly = true;        // Если это связанный справочник, то у него любое поле запрещено изменять напрямую
                else
                    fld.readOnly  = record.value("updateable").toString().trimmed().toUpper() == "YES" ? false : true;
            }
            fld.level = level;
            // Если это столбец из связанной таблицы, то наименование столбца приведем к виду "таблица__столбец"
            if (originTable.size() > 0 && originTable != table)
                fld.column = fldTable.toUpper() + "__" + fld.name;
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
                int currentRecord = columnsProperties.at();
                getColumnsProperties(result, dictName, table, level + 1);
                columnsProperties.seek(currentRecord);

                if (dictName.left(9) == "документы" && dictName.size() > 9)
                {
                    QString oper = dictName.remove("документы");
                    QString dictName = QString("докатрибуты%1").arg(oper);
                    if (isTableExists(dictName))
                    {
                        getColumnsProperties(result, dictName, table, level + 1);
                        columnsProperties.seek(currentRecord);
                    }
                }
            }
        }
    }
}


int PostgresDBFactory::insertDictDefault(QString tableName, QHash<QString, QVariant>* values)
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
        command = QString("INSERT INTO %1 (%2) VALUES (%3) RETURNING %4;").arg(getObjectNameCom(tableName))
                                                                          .arg(fieldsList)
                                                                          .arg(valuesList)
                                                                          .arg(getObjectNameCom(tableName + ".КОД"));
    }
    QSqlQuery query = execQuery(command);
    if (query.first())
    {
        result = query.record().field(0).value().toInt();
    }
    if (sysTables.contains(tableName))
        saveUpdate(command);
    return result;
}


QString PostgresDBFactory::getILIKEexpression(QString arg1, QString arg2)
{
    return QString("%1 ILIKE %2").arg(arg1).arg(arg2);
}


bool PostgresDBFactory::createNewDictionary(QString tName, QString tTitle/* = ""*/, bool menu)
{
    if (!isTableExists(tName))
    {   // Если такой таблицы нет, то добавим ее
        QString command = QString("CREATE TABLE \"%1\" ("    \
                                  "%2 SERIAL NOT NULL," \
                                  "%3 CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING)" \
                                  "WITH (OIDS=FALSE);" \
                                  "REVOKE ALL ON \"%1\" FROM PUBLIC;"    \
                                  "GRANT ALL ON \"%1\" TO %4;" \
                                  "ALTER TABLE \"%1\" ADD CONSTRAINT \"%1_pkey\" PRIMARY KEY(%2);")
                                  .arg(tName)
                                  .arg(getObjectNameCom("код"))
                                  .arg(getObjectNameCom("имя"))
                                  .arg(getLogin());
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
                }

            }
        }
        return false;
    }
    return true;
}


int PostgresDBFactory::getInsertReturningId(QString tableName, QString columns, QString values)
{
    return getValue(QString("INSERT INTO %1 (%2) VALUES (%3) RETURNING %4;")
                    .arg(getObjectNameCom(tableName))
                    .arg(columns)
                    .arg(values)
                    .arg(getObjectNameCom(tableName + ".КОД"))).toInt();
}


void PostgresDBFactory::setFile(QString file, FileType type, QByteArray fileData, bool extend)
{
    QString fileName = file.replace(app->applicationDirPath(), "~");
    clearError();
    qulonglong size = app->calculateCRC32(&fileData);
    QString text;
    if (isFileExist(fileName, type, extend))
    {
        // Если в базе уже есть такой файл
        if (!extend)
            text = QString("UPDATE %1 SET %2 = decode('%10', 'hex'), %3 = %4, %9 = %11 WHERE %5 = '%6' AND %7 = %8;")
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
            text = QString("UPDATE %1 SET %2 = decode('%9', 'hex'), %3 = %4 WHERE %5 = '%6' AND %7 = %8;").arg(getObjectNameCom("файлы"))
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
        text = QString("INSERT INTO %1 (%2, %3, %4, %6) VALUES ('%7', %8, %9, decode('%10', 'hex'));").arg(getObjectNameCom("файлы"))
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





