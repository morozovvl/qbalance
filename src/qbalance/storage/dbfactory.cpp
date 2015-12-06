/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QDebug>
#include "dbfactory.h"
#include "../kernel/app.h"
#include "../gui/passwordform.h"
#include "../kernel/dictionaries.h"


DBFactory::DBFactory()
: QObject()
{
    errorText.clear();
    hostName = "localhost";
    port = 5432;
    dbName = "qbalance";
    clearError();
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    dbExtend = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL", "qt_sql_pictures_connection"));
    extDbExist = true;
    commands.clear();
    dbIsOpened = false;
}


DBFactory::~DBFactory()
{
    delete dbExtend;
    delete db;

/*
    QStringList list = QSqlDatabase::connectionNames();

    for(int i = 0; i < list.count(); ++i)
    {
        QSqlDatabase::database(list[i]).close();
        QSqlDatabase::removeDatabase(list[i]);
    }
*/
}


bool DBFactory::createNewDBs(QString hostName, QString dbName, int port)
// Создает новую БД на сервере, если она отсутствует
{
    bool    lResult = true;
    QString defaultDatabase = getDatabaseName();
    setHostName(hostName);
    setDatabaseName("postgres");
    setPort(port);
    PassWordForm* frm = new PassWordForm();
    frm->open();
    frm->addLogin("postgres");
    if (frm->exec())
    {
        const QString login = frm->getLogin();
        const QString password = frm->getPassword();
        if (open(login, password))
        {
            const QStringList scripts = initializationScriptList();
            if (scripts.size() > 0)
            {
                createNewDB(dbName, password, scripts);
                const QStringList extScripts = initializationScriptList("ext");
                if (scripts.size() > 0)
                {
                    createNewDB(dbName + "_extend", password, extScripts);
                }
            }
            else
                TApplication::exemplar()->showCriticalError(QString(QObject::trUtf8("Не найден файл(ы) инициализации БД (initdb*.sql).")));
            close();
       }
       else
          TApplication::exemplar()->showCriticalError(QObject::trUtf8("Не удалось создать соединение с сервером."));
    }
    delete frm;
    setDatabaseName(defaultDatabase);
    return lResult;
}


bool DBFactory::createNewDB(QString dbName, QString password, QStringList scripts)
{
    bool    lResult = true;
    //Drake
    //Базу данных следует всегда создавать в UTF-8
    //т.к. есть возможность возвращать данные на клиент в нужной кодировке
    QString command = QString("CREATE DATABASE %1 WITH TEMPLATE template0 ENCODING = '%2';").arg(dbName, DBFactory::storageEncoding());
    if (exec(command))
    {
        //Drake
        //Нет смысла создавать локальный временный экземпляр в куче
        //Лучше на стеке - система его удалит
        QDir dir;

        for (QStringList::const_iterator script = scripts.constBegin(); lResult && script !=scripts.constEnd(); ++script)
        {
            if (dir.exists(*script))
            {
                QString command;
                QProcess proc;
                QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                env.insert("PGPASSWORD", password);
                env.insert("PGCLIENTENCODING", TApplication::encoding());
                proc.setProcessEnvironment(env);
                command = QString("psql -h %1 -p %2 -U postgres -f %3 %4").arg(hostName, QString::number(port), *script, dbName);
                proc.start(command);

                lResult = proc.waitForStarted();
                if (!lResult)
                {// выдадим сообщение об ошибке и выйдем из цикла
                    TApplication::exemplar()->showError(QObject::trUtf8("Не удалось запустить psql"));
                }
                else
                {
                    proc.waitForFinished();
                    if (proc.exitStatus() == QProcess::CrashExit)
                    {
                        TApplication::exemplar()->showCriticalError(QString(QObject::trUtf8("Файл инициализации <%1> по каким то причинам не загрузился.")).arg(*script));
                    }
                }
            }
        }
        command = QString("ALTER DATABASE %1 OWNER TO %2;").arg(dbName).arg("sa");
        exec(command);
    }
    return lResult;
}


void DBFactory::clearError()
{
    wasError = false;
    errorText.clear();
}


void DBFactory::setError(QString errText)
{
    bool emergencyExit = false;
    wasError = true;
    errorText = errText.trimmed();
    if (errorText.size() == 0)
    {
        errorText = "Ошибка соединения";
        emergencyExit = true;
    }
    TApplication::exemplar()->debug(1, " Error: " + errorText);
    TApplication::exemplar()->showError(errText);
    if (emergencyExit)
        TApplication::exemplar()->exit();
}


bool DBFactory::open()
{
    return DBFactory::open("", "");
}


bool DBFactory::open(QString login, QString password)
{
    clearError();
    db->setHostName(hostName);
    db->setDatabaseName(dbName);
    db->setPort(port);
    db->setUserName(login);
    db->setPassword(password);
    if (db->open()) {
        exec(QString("set client_encoding='%1';").arg(TApplication::encoding()));
        exec("set standard_conforming_strings=on;");
        currentLogin = login;
        currentPassword = password;

        pid = getValue("SELECT pg_backend_pid();").toInt();
        clearLockedDocuementList();
        dbIsOpened = true;
        return true;
    }
    else
    {
        setError(db->lastError().text());
    }
    return false;
}


bool DBFactory::beginTransaction()
{
    QString command = "BEGIN;";
//    TApplication::exemplar()->debug(1, command);
    return exec(command);
}


void DBFactory::commitTransaction()
{
    QString command = "COMMIT;";
//    TApplication::exemplar()->debug(1, command);
    exec(command);
}


void DBFactory::rollbackTransaction()
{
    QString command = "ROLLBACK;";
//    TApplication::exemplar()->debug(1, command);
    exec(command);
}


void DBFactory::initDBFactory()
{
    initObjectNames();                  // Инициируем переводчик имен объектов из внутренних наименований в наименования БД
    loadSystemTables();

    files = execQuery(QString("SELECT %1, %2, %3, %4, %5 FROM %6;").arg(getObjectNameCom("файлы.код"))
                                                               .arg(getObjectNameCom("файлы.имя"))
                                                               .arg(getObjectNameCom("файлы.тип"))
                                                               .arg(getObjectNameCom("файлы.контрсумма"))
                                                               .arg(getObjectNameCom("файлы.датавремя"))
                                                               .arg(getObjectNameCom("файлы")));

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
    }
    else
    {
        extDbExist = false;
//  Закомментировано: Не сообщать, что расширенная БД (для картинок) отсутствует. Работать без нее
//        setError(dbExtend->lastError().text());
    }
}


void DBFactory::loadSystemTables()
{
    objectTypes.clear();
    objectTypes = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("типыобъектов")));

    reloadDictionariesPermitions();

    reloadColumnProperties();

    config.clear();
    config = execQuery("SELECT \"group\", \"name\", \"value\" FROM configs;");

    accounts.clear();
    accounts = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("vw_счета")));

    columnsRestrictions.clear();
    columnsRestrictions = execQuery(QString("SELECT %1 FROM %2 WHERE %3=5 AND (%4 ILIKE '\%'||\"current_user\"()::text||'%' OR %4 ILIKE '\%*\%');")
                                                               .arg(getObjectNameCom("доступ.имя"))
                                                               .arg(getObjectNameCom("доступ"))
                                                               .arg(getObjectNameCom("доступ.код_типыобъектов"))
                                                               .arg(getObjectNameCom("доступ.имя_пользователи")));


    dictionaries.clear();
    dictionaries = execQuery(QString("SELECT * FROM %1 ORDER BY %2;").arg(getObjectNameCom("справочники")).arg(getObjectNameCom("справочники.имя")));

    reloadColumnHeaders();
}


void DBFactory::reloadDictionariesPermitions()
{
    dictionariesPermitions.clear();
    dictionariesPermitions = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("доступ_к_справочникам")));
}


void DBFactory::reloadColumnProperties()
{

    columnsProperties.clear();
    columnsProperties = execQuery("SELECT DISTINCT lower(trim(table_name)) AS table_name, ins.ordinal_position::integer - 1 AS \"order\", ins.column_name AS column_name, ins.data_type AS type, COALESCE(ins.character_maximum_length::integer, 0) + COALESCE(ins.numeric_precision::integer, 0) AS length, COALESCE(ins.numeric_scale::integer, 0) AS \"precision\", ins.is_updatable AS updateable " \
                                  "FROM information_schema.columns ins " \
                                  "WHERE ins.table_schema = 'public' " \
                                  "ORDER BY table_name;");
}


void DBFactory::reloadColumnHeaders()
{
    columnsHeaders.clear();
    columnsHeaders = execQuery(QString("SELECT lower(%1) AS %1, lower(%2) AS %2, upper(%3) AS %3, %4, %5, %6 FROM %7;").arg(getObjectNameCom("vw_столбцы.базсправочник"))
                                                                        .arg(getObjectNameCom("vw_столбцы.справочник"))
                                                                        .arg(getObjectNameCom("vw_столбцы.столбец"))
                                                                        .arg(getObjectNameCom("vw_столбцы.заголовок"))
                                                                        .arg(getObjectNameCom("vw_столбцы.номер"))
                                                                        .arg(getObjectNameCom("vw_столбцы.толькочтение"))
                                                                        .arg(getObjectNameCom("vw_столбцы")));
}


void DBFactory::close()
{
    clearError();

    if(db != 0 && db->isOpen())
    {
        db->close();
    }

    if(dbExtend != 0 && dbExtend->isOpen())
    {
        dbExtend->close();
    }
}


bool DBFactory::exec(QString str, bool showError, QSqlDatabase* db)
{
    TApplication::exemplar()->debug(1, "Exec: " + str);

    clearError();
    QSqlQuery* query;
    if (db != 0 && db->isValid())
        query = new QSqlQuery(*db);
    else
        query = new QSqlQuery();

    bool lResult = query->exec(str);
    if (!lResult && showError)
    {
        QString errorText = query->lastError().text().trimmed();
        if (errorText.size() > 0)
            setError(errorText);
    }
//    query->clear();
    delete query;
    return lResult;
}


QSqlQuery DBFactory::execQuery(QString str, bool showError, QSqlDatabase* extDb)
{
    TApplication::exemplar()->debug(1, QString("Query: %1").arg(str));
    clearError();
    QSqlQuery result;
    QSqlQuery* query;
    if (extDb != 0 && extDb->isValid())
        query = new QSqlQuery(*extDb);
    else
        query = new QSqlQuery(*db);

    if (!query->exec(str) && showError)
    {
        setError(query->lastError().text());
    }
    result = *query;
//    query->clear();
    delete query;
    return result;
}


QHash<int, UserInfo> DBFactory::getUserList()
{
    QHash<int, UserInfo> result;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("пр_пользователи")));
    while (query.next())
    {
        UserInfo u;
        u.loginName = query.value(1).toString();
        u.userName = query.value(2).toString().trimmed();
        result.insert(query.value(0).toInt(), u);
    }
    return result;
}




QSqlQuery DBFactory::getDictionariesProperties()
{
    clearError();
    return execQuery(QString("SELECT * FROM %1 ORDER BY %2;").arg(getObjectNameCom("доступ_к_справочникам"))
                                                          .arg(getObjectNameCom("доступ_к_справочникам.имя")));
}


QSqlRecord DBFactory::getDictionariesProperties(QString tName)
{
    QSqlRecord result;
    QString tableName = getObjectName("доступ_к_справочникам.справочник");
    if (dictionariesPermitions.first())
    {
        do
        {
            if (dictionariesPermitions.record().value(tableName).toString() == tName)
            {
                result = dictionariesPermitions.record();
                break;
            }
        } while (dictionariesPermitions.next());
    }
    return result;
}


QStringList DBFactory::getFieldsList(QHash<int, FieldType>* columnsProperties)
{
    QStringList result;
    foreach (int i, columnsProperties->keys())
        result << columnsProperties->value(i).name;
    return result;
}


QStringList DBFactory::getFieldsList(QString tableName, int level)
{
    QStringList result;
    QList<FieldType> fields;
    getColumnsProperties(&fields, tableName);

    for (int i = 0; i < fields.count(); i++)
    {
        if (level == -1 || fields.value(i).level <= level)
            result << fields.value(i).column;
    }
    if (result.count() == 0)
        TApplication::exemplar()->showError(QString("Список полей таблицы <%1> пустой. Возможно, таблица недоступна.").arg(tableName));
    return result;
}


bool DBFactory::isSet(QString tableName)
{
    bool result = false;
    if (tableName.size() > 0)
    {
        // Найдем имя прототипа для этого справочника
        QStringList fieldList = getFieldsList(tableName);
        // определим, это набор или обычный справочник
        if (fieldList.contains(getObjectName("имя"), Qt::CaseInsensitive)) {
            result = false;                                     // это справочник, т.к. есть поле ИМЯ
        }
        else {
            QString id = getObjectName("код") + "_";
            for (int k = 0; k < fieldList.count(); k++)
                if (QString(fieldList.at(k).left(id.size())).compare(id, Qt::CaseInsensitive) == 0) {
                    result = true;                              // это набор, т.к. нет поля ИМЯ и есть поля-ссылки на другие справочники
                    break;
                }
            }
    }
    return result;
}


void DBFactory::getColumnsProperties(QList<FieldType>* result, QString table, QString originTable, int level)
{
    QString fldTable = table;
    QString tableAlias = table;
    if (table.left(9) == "документы" && table.size() > 9)
    {
        table = "vw_спрдокументы";
        fldTable = "документы";
    }
    else if (table.left(11) == "докатрибуты" && table.size() > 11)
    {
        fldTable = "документы";
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


void DBFactory::addColumnProperties(QList<FieldType>* columnsProperties, QString table, QString name, QString type, int length, int precision, bool read, bool constRead, int number)
{
    // Выясним, нет ли уже такого поля, чтобы избежать появления двойных полей
    int maxKey = 0;
    if (columnsProperties->count() > 0)
    {
        for (int i = 0; i < columnsProperties->count(); i++)
        {
              if (columnsProperties->at(i).table == table &&
                  columnsProperties->at(i).column.toUpper() == name.toUpper() &&
                  columnsProperties->at(i).type == type)
                return;                 // такое поле уже существует, не будем ничего добавлять
            if (i > maxKey)
                maxKey = i;
        }
        maxKey++;
    }
    FieldType fld;
    fld.table = table;
    fld.name = name.toUpper();
    fld.column = name.toUpper();
    fld.header = name.toUpper();
    fld.type = type;
    fld.length = length;
    fld.precision = precision;
    fld.readOnly = read;
    fld.constReadOnly = constRead;
    fld.number = number;
    columnsProperties->insert(maxKey, fld);
}


void DBFactory::getColumnsRestrictions(QString table, QList<FieldType>* columns)
{
    columnsRestrictions.first();
    while (columnsRestrictions.isValid())
    {
        if (columnsRestrictions.record().value(getObjectNameCom("доступ.имя")).toString().trimmed() == table.trimmed())
        {
            QString field = QString(columnsRestrictions.record().value(0).toString()).remove(table.trimmed() + ".", Qt::CaseInsensitive).trimmed().toLower();
            for (int i = 0; i < columns->count(); i++)
            {
                if (columns->value(i).name.toLower() == field)
                {
                    if (columnsRestrictions.record().value(1).toString().contains("ro", Qt::CaseInsensitive))
                    {
                        FieldType fld = columns->value(i);
                        fld.readOnly = true;
                        columns->removeAt(i);
                        columns->insert(i, fld);
                        break;
                    } else if (columnsRestrictions.record().value(1).toString().contains("hide", Qt::CaseInsensitive))
                    {
                        columns->removeAt(i);
                        break;
                    }
                }
            }
        }
        columnsRestrictions.next();
    }
}


int DBFactory::getTypeId(QString dict)
{
    objectTypes.first();
    do {
        if (objectTypes.value(1).toString().trimmed().toLower() == dict.toLower())
        {
            return objectTypes.value(0).toInt();
        }
    } while (objectTypes.next());
    return 0;
}


int DBFactory::getDictionaryId(QString dictionaryName)
{
    clearError();
    QString dict = getObjectNameCom("vw_справочники_со_столбцами");
    QString dictId = getObjectNameCom("vw_справочники_со_столбцами.код");
    QString dictName = getObjectNameCom("vw_справочники_со_столбцами.имя");
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = '%4';").arg(dictId)
                                                                             .arg(dict)
                                                                             .arg(dictName)
                                                                             .arg(dictionaryName));
    query.first();
    if (query.isValid()) {
        return query.value(0).toInt();
    }
    if (dictionaryName.left(16) == "СписокДокументов")
    {
        int number = 1000000;
        clearError();
        QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2 WHERE %3 LIKE 'СписокДокументов%';").arg(dictId)
                                                                                                       .arg(dict)
                                                                                                       .arg(dictName));
        if (query.first())
        {
            return query.value(0).toInt() + 1;
        }
        return number;
    }
    if (dictionaryName.left(8) == "Документ")
    {
        int number = 2000000;
        clearError();
        QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2 WHERE %3 LIKE 'Документ%';").arg(dictId)
                                                                                               .arg(dict)
                                                                                               .arg(dictName));
        if (query.first())
        {
            return query.value(0).toInt() + 1;
        }
        return number;
    }
    if (dictionaryName.left(9) == "документы" && dictionaryName.size() > 9)
    {
        int number = 4000000;
        number += QString(dictionaryName).replace("документы", "").toInt();
        return number;
    }
    dict = getObjectNameCom("справочники");
    dictId = getObjectNameCom("справочники.код");
    dictName = getObjectNameCom("справочники.имя");
    query = execQuery(QString("SELECT %1 FROM %2 WHERE trim(%3) = '%4';").arg(dictId)
                                                                   .arg(dict)
                                                                   .arg(dictName)
                                                                   .arg(dictionaryName));
    query.first();
    if (query.isValid()) {
        return query.value(0).toInt();
    }
    return 0;
}


bool DBFactory::isTableExists(QString tName)
{
    QString command = QString("SELECT tablename AS name, tableowner as owner FROM pg_tables WHERE tablename = '%1' " \
                              "UNION " \
                              "SELECT viewname AS name, viewowner as owner FROM pg_views WHERE viewname = '%1';").arg(tName);
    return execQuery(command).size() > 0 ? true : false;
}


bool DBFactory::createNewDictionary(QString tName, QString tTitle/* = ""*/, bool menu)
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
                        .arg(menu ? "true" : "false")
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


bool DBFactory::removeDictionary(QString tName)
{
    if (isTableExists(tName))
    {
        beginTransaction();
        QString command = QString("DROP TABLE \"%1\";")
                                  .arg(tName);
        if (exec(command))
        {
            command = QString("DELETE FROM %1 WHERE %2 = %3 AND %4 = '%5' AND %6 = '%7';")
                        .arg(getObjectNameCom("доступ"))
                        .arg(getObjectNameCom("доступ.код_типыобъектов"))
                        .arg(getTypeId(getObjectName("типыобъектов.справочник")))
                        .arg(getObjectNameCom("доступ.имя_пользователи"))
                        .arg(getLogin())
                        .arg(getObjectNameCom("доступ.имя"))
                        .arg(tName);
            if (exec(command))
            {
                command = QString("DELETE FROM %1 WHERE %2 = '%3';")
                            .arg(getObjectNameCom("справочники"))
                            .arg(getObjectNameCom("справочники.имя"))
                            .arg(tName);
                if (exec(command))
                {
                    commitTransaction();
                    return true;
                }

            }
        }
        rollbackTransaction();
        return false;

    }
    return true;
}


bool DBFactory::setTableGuiName(QString tableName, QString menuName, QString formName)
{
    clearError();
    QString command;
    command = QString("UPDATE %1 SET %2 = '%3', %4 = '%5' WHERE trim(%6) = '%7';").arg(getObjectNameCom("справочники"))
                                                                            .arg(getObjectNameCom("справочники.имя_в_списке"))
                                                                            .arg(menuName)
                                                                            .arg(getObjectNameCom("справочники.имя_в_форме"))
                                                                            .arg(formName)
                                                                            .arg(getObjectNameCom("справочники.имя"))
                                                                            .arg(tableName);
    return exec(command);
}


bool DBFactory::renameTableColumn(QString table, QString oldColumnName, QString newColumnName)
{
    clearError();
    exec(QString("ALTER TABLE %1 RENAME COLUMN %2 TO %3;").arg(table).arg(oldColumnName).arg(newColumnName));
    QSqlQuery dict = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = '" + table + "';").arg(getObjectNameCom("справочники.код"))
                                                                                       .arg(getObjectNameCom("справочники"))
                                                                                       .arg(getObjectNameCom("справочники.имя")));
    dict.first();
    if (dict.isValid())
    {
        return exec(QString("UPDATE %1 SET %2 = '%3' WHERE \"%4\" = %5 AND %2 = '%3';").arg(getObjectNameCom("столбцы"))
                                                                                   .arg(getObjectNameCom("столбцы.имя"))
                                                                                   .arg(newColumnName)
                                                                                   .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
                                                                                   .arg(dict.value(0).toInt())
                                                                                   .arg(oldColumnName));
    }
    return false;
}


bool DBFactory::alterTableColumn(QString table, QString columnName, QString type)
{
    clearError();
    return exec(QString("ALTER TABLE %1 ALTER COLUMN %2 TYPE %3;").arg(getObjectNameCom(table)).arg(getObjectNameCom(table + "." + columnName)).arg(type));
}


bool DBFactory::addTableColumn(QString table, QString columnName, QString type)
{
    clearError();
    QString command = QString("ALTER TABLE %1 ADD COLUMN %2 %3;").arg(getObjectNameCom(table))
                                                                 .arg(getObjectNameCom(table + "." + columnName))
                                                                 .arg(type);
    return exec(command);
}


bool DBFactory::dropTableColumn(QString table, QString columnName)
{
    clearError();
    return exec(QString("ALTER TABLE %1 DROP COLUMN %2;").arg(getObjectNameCom(table)).arg(getObjectNameCom(table + "." + columnName)));
}


QSqlQuery DBFactory::getTopersProperties()
{
    clearError();
    return execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("доступ_к_топер")));
}


QSqlRecord DBFactory::getTopersProperties(int operNumber)
{
    clearError();
    QSqlRecord result;
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("доступ_к_топер"))
                                                                          .arg(getObjectNameCom("доступ_к_топер.опер"))
                                                                          .arg(operNumber));
    if (query.first())
        result = query.record();
    return result;
}


QSqlQuery DBFactory::getToper(int operNumber)
{
    clearError();
    return execQuery(QString("SELECT * FROM %1 WHERE %2 = %3 ORDER BY %4;").arg(getObjectNameCom("топер"))
                                                                           .arg(getObjectNameCom("топер.опер"))
                                                                           .arg(operNumber)
                                                                           .arg(getObjectNameCom("топер.номер")));
}


bool DBFactory::deleteToper(int operNumber, int operNumber1)
{
    clearError();
    return exec(QString("DELETE FROM %1 WHERE %2=%3 AND %4>=%5;").arg(getObjectNameCom("топер"))
                                                             .arg(getObjectNameCom("топер.опер"))
                                                             .arg(operNumber)
                                                             .arg(getObjectNameCom("топер.номер"))
                                                             .arg(operNumber1));
}


bool DBFactory::deleteAllToperInfo(int operNumber)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT count(*) FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("документы"))
                                                                                 .arg(getObjectNameCom("документы.опер"))
                                                                                 .arg(operNumber));
    if (query.first())
    {
        if (query.value(0).toInt() > 0)
        {   // Если есть документы для данной типовой операции
            errorText = QObject::trUtf8("Нельзя удалить типовую операцию, т.к. по ней уже созданы документы");
            TApplication::exemplar()->showError(errorText);
            return false;
        }
    beginTransaction();
    exec(QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("столбцы"))
                                                .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
                                                .arg(getDictionaryId(QString("Документ%1").arg(operNumber))));
    exec(QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("топер"))
                                                 .arg(getObjectNameCom("топер.опер"))
                                                 .arg(operNumber));
    exec(QString("DELETE FROM %1 WHERE %2 = '%3';").arg(getObjectNameCom("файлы"))
                                                   .arg(getObjectNameCom("файлы.имя"))
                                                   .arg(TApplication::exemplar()->getScriptFileName(operNumber)));
    commitTransaction();
    }
    return true;
}


bool DBFactory::addToperPrv(int operNumber, int operNumber1, QString name, QString dbAcc, bool dbAccConst, bool dbVisible, bool dbSalVisible, QString crAcc, bool crAccConst, bool crVisible, bool crSalVisible, QString itog, bool freePrv, bool attribute)
{
    QString command;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2 WHERE %3=%4 AND %5=%6;").arg(getObjectNameCom("топер.номер"))
                                                                                .arg(getObjectNameCom("топер"))
                                                                                .arg(getObjectNameCom("топер.опер"))
                                                                                .arg(operNumber)
                                                                                .arg(getObjectNameCom("топер.номер"))
                                                                                .arg(operNumber1));
    if (query.first())
    {
        command = QString("UPDATE %1 SET %4='%18', %5='%19', %6=%20, %7=%21, %8=%22, %9='%23', %10=%24, %11=%25, %12=%26, %13='%27', %14=%28, %15=%29 " \
                          "WHERE %2=%16 AND %3=%17;").arg(getObjectNameCom("топер"))
                                                     .arg(getObjectNameCom("топер.опер"))
                                                     .arg(getObjectNameCom("топер.номер"))
                                                     .arg(getObjectNameCom("топер.имя"))
                                                     .arg(getObjectNameCom("топер.дбсчет"))
                                                     .arg(getObjectNameCom("топер.дбпост"))
                                                     .arg(getObjectNameCom("топер.дбвидим"))
                                                     .arg(getObjectNameCom("топер.дбсалвидим"))
                                                     .arg(getObjectNameCom("топер.крсчет"))
                                                     .arg(getObjectNameCom("топер.крпост"))
                                                     .arg(getObjectNameCom("топер.крвидим"))
                                                     .arg(getObjectNameCom("топер.крсалвидим"))
                                                     .arg(getObjectNameCom("топер.итоги"))
                                                     .arg(getObjectNameCom("топер.независим"))
                                                     .arg(getObjectNameCom("топер.атрибуты"))
                                                     .arg(operNumber)
                                                     .arg(operNumber1)
                                                     .arg(name)
                                                     .arg(dbAcc)
                                                     .arg(dbAccConst ? "true" : "false")
                                                     .arg(dbVisible ? "true" : "false")
                                                     .arg(dbSalVisible ? "true" : "false")
                                                     .arg(crAcc)
                                                     .arg(crAccConst ? "true" : "false")
                                                     .arg(crVisible ? "true" : "false")
                                                     .arg(crSalVisible ? "true" : "false")
                                                     .arg(itog)
                                                     .arg(freePrv ? "true" : "false")
                                                     .arg(attribute ? "true" : "false");
    }
    else
    {
        int number = (dbAcc.size() > 0 && crAcc.size() > 0) ? 1 : 0;
        command = QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15) " \
                          "VALUES (%16, %17, '%18', '%19', %20, %21, %22, '%23', %24, %25, %26, '%27', %28, %29);").arg(getObjectNameCom("топер"))
                                                                                                 .arg(getObjectNameCom("топер.опер"))
                                                                                                 .arg(getObjectNameCom("топер.номер"))
                                                                                                 .arg(getObjectNameCom("топер.имя"))
                                                                                                 .arg(getObjectNameCom("топер.дбсчет"))
                                                                                                 .arg(getObjectNameCom("топер.дбпост"))
                                                                                                 .arg(getObjectNameCom("топер.дбвидим"))
                                                                                                 .arg(getObjectNameCom("топер.дбсалвидим"))
                                                                                                 .arg(getObjectNameCom("топер.крсчет"))
                                                                                                 .arg(getObjectNameCom("топер.крпост"))
                                                                                                 .arg(getObjectNameCom("топер.крвидим"))
                                                                                                 .arg(getObjectNameCom("топер.крсалвидим"))
                                                                                                 .arg(getObjectNameCom("топер.итоги"))
                                                                                                 .arg(getObjectNameCom("топер.независим"))
                                                                                                 .arg(getObjectNameCom("топер.атрибуты"))
                                                                                                 .arg(operNumber)
                                                                                                 .arg(number)
                                                                                                 .arg(name)
                                                                                                 .arg(dbAcc)
                                                                                                 .arg(dbAccConst ? "true" : "false")
                                                                                                 .arg(dbVisible ? "true" : "false")
                                                                                                 .arg(dbSalVisible ? "true" : "false")
                                                                                                 .arg(crAcc)
                                                                                                 .arg(crAccConst ? "true" : "false")
                                                                                                 .arg(crVisible ? "true" : "false")
                                                                                                 .arg(crSalVisible ? "true" : "false")
                                                                                                 .arg(itog)
                                                                                                 .arg(freePrv ? "true" : "false")
                                                                                                 .arg(attribute ? "true" : "false");
    }
    return exec(command);
}


int DBFactory::getNewToper()
{
    int number = 1;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2;").arg(getObjectNameCom("топер.опер"))
                                                                  .arg(getObjectNameCom("топер")));
    if (query.first())
    {
        number = query.record().value(0).toInt() + 1;
    }
    return number;
}


QString DBFactory::getPhotoDatabase()
{
    clearError();
    QString result;
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = 'база_фото';").arg(getObjectNameCom("vw_константы.значение"))
                                                                                    .arg(getObjectNameCom("vw_константы"))
                                                                                    .arg(getObjectNameCom("vw_константы.имя")));
    if (query.first())
        result = query.record().field(0).value().toString();
    return result;
}

QString DBFactory::getDictionaryPhotoPath(QString tableName)
{
    clearError();
    QString result, command;
    command = QString("SELECT %1 FROM %2 WHERE trim(%3) = '" + tableName + "';").arg(getObjectNameCom("справочники.фото"))
            .arg(getObjectNameCom("справочники"))
            .arg(getObjectNameCom("справочники.имя"));
    QSqlQuery query = execQuery(command);
    if (query.first())
        result = query.record().field(0).value().toString().trimmed();
    return result;
}


void DBFactory::getColumnsHeaders(QString tableName, QList<FieldType>* fields)
{
    if (tableName.size() > 0)
    {
        int counter = 0;
        for (columnsHeaders.first(); columnsHeaders.isValid(); columnsHeaders.next())
        {
            if (columnsHeaders.record().value(getObjectName("vw_столбцы.базсправочник")).toString().trimmed().toLower() == tableName.toLower())
            {
                int number = columnsHeaders.record().value(getObjectName("vw_столбцы.номер")).toInt();
                if (number > 0)
                {
                    QString table = columnsHeaders.record().value(getObjectName("vw_столбцы.справочник")).toString().trimmed().toLower();
                    QString column1 = columnsHeaders.record().value(getObjectName("vw_столбцы.столбец")).toString().toUpper();

                    for (int i = 0; i < fields->count(); i++)
                    {
                        if ((column1 == fields->at(i).name.toUpper()) &&
                                ((table == fields->at(i).table.toLower()) ||
                                 (table == "проводки") ||
                                (table == "документы") ||
                                (table == "saldo")))
                        {
                            // Заголовок для столбца найден
                            counter++;
                            FieldType field = fields->at(i);
                            field.header = columnsHeaders.record().value(getObjectName("vw_столбцы.заголовок")).toString();
                            field.number = number;
                            field.headerExist = true;   // Для столбца найден заголовок
                            field.readOnly = columnsHeaders.record().value(getObjectName("vw_столбцы.толькочтение")).toBool();
                            fields->removeAt(i);
                            fields->insert(i, field);
                            break;
                        }
                    }
                }
            }
        }
        if (counter == 0)
        {
            for (int i = 0; i < fields->count(); i++)
            {
                FieldType field = fields->at(i);
                field.number = i + 1;
                fields->removeAt(i);
                fields->insert(i, field);
            }
        }
    }
}


bool DBFactory::removeColumnHeaders(int tableId)
{
    clearError();
    QString command;
    command = QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("столбцы"))
                                                      .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
                                                      .arg(tableId);
    return exec(command);
}


bool DBFactory::appendColumnHeader(int mainTableId, int tableId, QString column, QString header, int number, bool readOnly)
{
    clearError();
    QString command;
    command = QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7) VALUES (%8, '%9', '%10', %11, %12, %13);")
            .arg(getObjectNameCom("столбцы"))
            .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
            .arg(getObjectNameCom("столбцы.имя"))
            .arg(getObjectNameCom("столбцы.заголовок"))
            .arg(getObjectNameCom("столбцы.номер"))
            .arg(getObjectNameCom("столбцы.толькочтение"))
            .arg(getObjectNameCom("столбцы.кодтаблицы"))
            .arg(mainTableId)
            .arg(column)
            .arg(header)
            .arg(number)
            .arg(readOnly ? "true" : "false")
            .arg(tableId);
    return exec(command);
}


int DBFactory::insertDictDefault(QString tableName, QHash<QString, QVariant>* values)
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
        command = QString("INSERT INTO %1 (%4, %2) VALUES ((SELECT MAX(%4)+1 FROM %1),%3) RETURNING %4;").arg(getObjectNameCom(tableName))
                                                                          .arg(fieldsList)
                                                                          .arg(valuesList)
                                                                          .arg(getObjectNameCom(tableName + ".КОД"));
    }
    QSqlQuery query = execQuery(command);
    if (query.first())
    {
        result = query.record().field(0).value().toInt();
    }
    return result;
}


bool DBFactory::removeDictValue(QString tableName, qulonglong id)
{
    clearError();
    QString command = QString("DELETE FROM \"%1\" WHERE \"%2\" = %3;").arg(tableName).arg(getObjectName("код")).arg(id);
    execQuery(command);
    return !wasError;
}


int DBFactory::addDoc(int operNumber, QDate date)
{
    int result = 0;
    clearError();
    QString command = QString("SELECT sp_InsertDoc(%1,'%2');").arg(operNumber).arg(date.toString("dd.MM.yyyy"));
    QSqlQuery query = execQuery(command);
    if (query.first())
    {
        result = query.record().field(0).value().toInt();
    }
    return result;
}


bool DBFactory::removeDoc(int docId)
{
    clearError();
    return exec(QString("SELECT sp_DeleteDoc(%1);").arg(docId));
}


int DBFactory::addDocStr(int operNumber, int docId, QString cParam, int nQuan, int nDocStr)
{
    int result = 0;
    clearError();
    QString command = QString("SELECT sp_InsertDocStr(%1,%2,'%3'::character varying,%4,%5);").arg(operNumber).arg(docId).arg(cParam).arg(nQuan).arg(nDocStr);
    QSqlQuery query = execQuery(command);
    if (query.first())
    {
        result = query.record().field(0).value().toInt();
    }
    return result;
}


void DBFactory::saveDocAttribute(int operNumber, int docId, QString attribute, QVariant val)
{
    clearError();
    QString value;
    if (val.type() == QVariant::String)
        value = QString("'%1'").arg(val.toString());
    else
        value = val.toString();
    QString command = QString("UPDATE %1%2 SET %3=%4 WHERE %5=%6 AND %7=(SELECT max(%7) FROM %1%2 WHERE %5=%6);").arg(getObjectName("атрибуты"))
                                                                                                                 .arg(operNumber)
                                                                                                                 .arg(attribute)
                                                                                                                 .arg(value)
                                                                                                                 .arg(getObjectNameCom("атрибуты.доккод"))
                                                                                                                 .arg(docId)
                                                                                                                 .arg(getObjectNameCom("атрибуты.стр"));
    exec(command);
}


bool DBFactory::removeDocStr(int docId, int nDocStr)
{
    clearError();
    return exec(QString("SELECT sp_DeleteDocStr(%1,%2);").arg(docId).arg(nDocStr));
}


void DBFactory::setPeriod(QDate begDate, QDate endDate)
{
    clearError();
    QString command = QString("UPDATE %1 SET %2='%3', %4='%5' WHERE %6='%7';").arg(getObjectNameCom("блокпериоды"))
                                                                 .arg(getObjectNameCom("блокпериоды.начало"))
                                                                 .arg(begDate.toString(Qt::LocaleDate))
                                                                 .arg(getObjectNameCom("блокпериоды.конец"))
                                                                 .arg(endDate.toString(Qt::LocaleDate))
                                                                 .arg(getObjectNameCom("блокпериоды.пользователь"))
                                                                 .arg(TApplication::exemplar()->getLogin());
    exec(command);
}


void DBFactory::getPeriod(QDate& begDate, QDate& endDate)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1, %2 FROM %3 WHERE %4='%5';").arg(getObjectNameCom("блокпериоды.начало"))
                                                                               .arg(getObjectNameCom("блокпериоды.конец"))
                                                                               .arg(getObjectNameCom("блокпериоды"))
                                                                               .arg(getObjectNameCom("блокпериоды.пользователь"))
                                                                               .arg(TApplication::exemplar()->getLogin()));
    if (query.first())
    {
        begDate = query.record().field(0).value().toDate();
        endDate = query.record().field(1).value().toDate();
    }
}


void DBFactory::setConstDictId(QString fieldName, QVariant val, int docId, int oper, int operNum)
{
    clearError();
    exec(QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND %6 = %7 AND %8 = %9;").arg(getObjectNameCom("проводки"))
                                                                               .arg(fieldName)
                                                                               .arg(val.toString())
                                                                               .arg(getObjectNameCom("проводки.доккод"))
                                                                               .arg(docId)
                                                                               .arg(getObjectNameCom("проводки.опер"))
                                                                               .arg(oper)
                                                                               .arg(getObjectNameCom("проводки.номеропер"))
                                                                               .arg(operNum));
}


QStringList DBFactory::initializationScriptList(QString ext) const
{
    QStringList result;

    QDir dir(QCoreApplication::applicationDirPath());
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setSorting(QDir::Name | QDir::IgnoreCase);
    dir.setNameFilters(QStringList() << "initdb" + ext + "*.sql");
    QFileInfoList files = dir.entryInfoList();

    for (QFileInfoList::const_iterator file = files.constBegin(); file != files.constEnd(); ++file)
    {
        result.append(file->canonicalFilePath());
    }

    return result;
}


void DBFactory::initObjectNames()
{
    clearError();
    QSqlQuery query = execQuery("SELECT * FROM objectnames;", false);   // Если что, то не сообщать об отсутствии таблицы
    if (query.first())
    {   // Если на сервере есть определение имен объектов, то прочитаем его
        do {
            ObjectNames.insert(query.record().value("name").toString(), query.record().value("value").toString());
        } while (query.next());
        return;
    }
    ObjectNames.insert("код", "КОД");
    ObjectNames.insert("имя", "ИМЯ");
}


QString DBFactory::getObjectName(const QString& n)
// транслирует имена объектов БД из "внутренних" в реальные наименования
{
    QString name = n.toLower();
    QString result;
    if (ObjectNames.contains(name))
        result = ObjectNames.value(name);
    else
    {
        // Присвоим результату значение по умолчанию
        if (n.contains('.'))
        {   // В искомом значении есть имя таблицы и наименование поля
            QString fieldName = n.mid(n.indexOf('.') + 1);
            result = fieldName.toUpper();       // Зададим имя поля по умолчанию, если не найдем другого значения
        }
        else
            result = n;
    }
    return result;
}


QString DBFactory::getObjectNameCom(const QString& name)
{
    return '"' + getObjectName(name) + '"';
}


QByteArray DBFactory::getFile(QString file, FileType type, bool extend)
{
    QString fileName = file.replace(TApplication::exemplar()->applicationDirPath(), "~");
    if (extend && extDbExist)
    {   // Если будем смотреть файлы в расширенной базе данных
        QString text = QString("SELECT encode(%1, 'hex') FROM %2 WHERE %3 = '%4' AND %5 = %6;").arg(getObjectNameCom("файлы.значение"))
                                                                              .arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName)
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        QSqlQuery query = execQuery(text, true, dbExtend);
        query.first();
        if (query.isValid())
        {
            return QByteArray::fromHex(query.record().value(0).toByteArray());
        }
        return QByteArray();
    }
    files.first();
    while (files.isValid())
    {
        if (files.record().value(getObjectName("файлы.имя")).toString().trimmed() == fileName &&
            files.record().value(getObjectName("файлы.тип")).toInt() == type)
        {   // Если найден файл нужного типа и с нужным именем, то запросим его содержимое в БД
            int id = files.record().value(getObjectName("файлы.код")).toInt();
            QString text = QString("SELECT encode(%1, 'hex') FROM %2 WHERE %3 = %4;").arg(getObjectNameCom("файлы.значение"))
                                                                      .arg(getObjectNameCom("файлы"))
                                                                      .arg(getObjectNameCom("файлы.код"))
                                                                      .arg(id);
            QSqlQuery query = execQuery(text);
            query.first();
            if (query.isValid())
            {
                return QByteArray::fromHex(query.record().value(0).toByteArray());
            }
        }
        files.next();
    }
    return QByteArray();
}


void DBFactory::copyFile(QString fileFrom, FileType type, QString fileTo, bool extend)
{
    if (isFileExist(fileFrom, type, extend))
    {
        QString text;
        if (!isFileExist(fileTo, type, extend))
        {
            text = QString("INSERT INTO %1 (%2, %3, %4, %5) SELECT '%6', %3, %4, %5 FROM %1 WHERE %2 = '%7';").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(fileTo)
                                                                                  .arg(fileFrom);
            exec(text, true, (extend && extDbExist) ? dbExtend : db);
        }
    }
}


qulonglong DBFactory::getFileCheckSum(QString file, FileType type, bool extend)
{
    QString fileName = file.replace(TApplication::exemplar()->applicationDirPath(), "~");
    QString text = QString("SELECT %6 FROM %1 WHERE %2 = '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                           .arg(getObjectNameCom("файлы.имя"))
                                                                           .arg(fileName)
                                                                           .arg(getObjectNameCom("файлы.тип"))
                                                                           .arg(type)
                                                                           .arg(getObjectNameCom("файлы.контрсумма"));
    QSqlQuery query = execQuery(text, true, (extend && extDbExist) ? dbExtend : db);
    query.first();
    if (query.isValid())
    {
        qulonglong result = query.record().value(0).toLongLong();
        if (result == 0)    // Видимо раньше не была обозначена контрольная сумма
            result = 1;     // Сделаем ее не равной 0, иначе фотография не будет показана, хотя она в базе есть
        return result;
    }
    return 0;
}


QDateTime DBFactory::getFileDateTime(QString file, FileType type, bool extend)
{
    QDateTime result;
    QString fileName = file.replace(TApplication::exemplar()->applicationDirPath(), "~");
    QString text = QString("SELECT %6 FROM %1 WHERE %2 = '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                          .arg(getObjectNameCom("файлы.имя"))
                                                                          .arg(fileName)
                                                                          .arg(getObjectNameCom("файлы.тип"))
                                                                          .arg(type)
                                                                          .arg(getObjectNameCom("файлы.датавремя"));
    QSqlQuery query = execQuery(text, true, (extend && extDbExist) ? dbExtend : db);
    query.first();
    if (query.isValid())
    {
        result = query.record().value(0).toDateTime();
    }
    return result;
}



QStringList DBFactory::getFilesList(QString fileName, FileType type, bool extend)
{
    QStringList filesList;
    if (extend && extDbExist)
    {
        QString text = QString("SELECT * FROM %1 WHERE %2 ILIKE '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName + ".%")
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        QSqlQuery query = execQuery(text, dbExtend);
        query.first();
        while (query.isValid())
        {
            QString fileName = query.record().value(getObjectName("файлы.имя")).toString();
            if (!filesList.contains(fileName))
                filesList << fileName;
            query.next();
        }
        return filesList;
    }
    files.first();
    while (files.isValid())
    {
        if (files.record().value(getObjectName("файлы.имя")).toString().trimmed().startsWith(fileName) &&
            files.record().value(getObjectName("файлы.тип")).toInt() == type)
        {   // Если найден файл нужного типа и с нужным именем, то вернем его контрольную сумму
            QString fileName = files.record().value(getObjectName("файлы.имя")).toString();
            if (!filesList.contains(fileName))
                filesList << fileName;
        }
        files.next();
    }
    return filesList;
}



bool DBFactory::isFileExist(QString fileName, FileType type, bool extend)
{
    if (extend && extDbExist)
    {
        QString text = QString("SELECT count(*) FROM %1 WHERE %2 = '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName)
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        QSqlQuery query = execQuery(text, true, dbExtend);
        query.first();
        if (query.isValid())
        {
            int quan = query.record().value(0).toInt();
            if (quan > 0)
                return true;
        }
        return false;
    }
    files.first();
    while (files.isValid())
    {
        if (files.record().value(getObjectName("файлы.имя")).toString().trimmed() == fileName &&
            files.record().value(getObjectName("файлы.тип")).toInt() == type)
        {   // Если найден файл нужного типа и с нужным именем, то вернем его контрольную сумму
            return true;
        }
        files.next();
    }
    return false;
}


void DBFactory::removeFile(QString fileName, FileType type, bool extend)
{
    QString text;
    text = QString("DELETE FROM %1 WHERE %2 = '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                             .arg(getObjectNameCom("файлы.имя"))
                                                                             .arg(fileName)
                                                                             .arg(getObjectNameCom("файлы.тип"))
                                                                             .arg(type);
    exec(text, true, (extend && extDbExist) ? dbExtend : db);
}


void DBFactory::setFile(QString file, FileType type, QByteArray fileData, bool extend)
{
    QString fileName = file.replace(TApplication::exemplar()->applicationDirPath(), "~");
    clearError();
    qulonglong size = calculateCRC32(&fileData);
    QString text;
    if (isFileExist(fileName, type, extend))
    {
        // Если в базе уже есть такой файл
/*
        text = QString("UPDATE %1 SET %2 = (:value), %3 = %4, %9 = now() WHERE %5 = '%6' AND %7 = %8;").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(size)
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(fileName)
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(type)
                                                                                  .arg(getObjectNameCom("файлы.датавремя"));
*/
        if (!extend)
            text = QString("UPDATE %1 SET %2 = decode('%10', 'hex'), %3 = %4, %9 = now() WHERE %5 = '%6' AND %7 = %8;").arg(getObjectNameCom("файлы"))
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
/*
        text = QString("INSERT INTO %1 (%2, %3, %4, %6) VALUES ('%7', %8, %9, (:value));").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(fileName)
                                                                                  .arg(type)
                                                                                  .arg(size);
*/
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
    exec(text, true, (extend && extDbExist) ? dbExtend : db);
}


QString DBFactory::storageEncoding()
{
    QString result("UTF-8");
#ifdef Q_OS_WIN32
    result = "Windows-1251";
#endif
    return result;
}


void DBFactory::getToperData(int oper, QList<ToperType>* topersList)
{
    clearError();
    bool docAttr = isTableExists(QString("докатрибуты%1").arg(oper));
    bool attr = isTableExists(QString("атрибуты%1").arg(oper));
    QSqlQuery toper = execQuery(QString("SELECT * FROM %1 WHERE %2=%3 ORDER BY %4;").arg(getObjectNameCom("vw_топер")).arg(getObjectNameCom("vw_топер.опер")).arg(oper).arg(getObjectNameCom("vw_топер.номер")));
    toper.first();
    // Сначала составим список справочников и проверим на предмет присутствия одного и того же справочника и по дебету и по кредиту
    while (toper.isValid())
    {
        ToperType toperT;
        toperT.number = toper.record().value("номер").toInt();
        toperT.dbAcc = toper.record().value("дбсчет").toString().trimmed();
        toperT.dbDict = toper.record().value("дбсправ").toString().trimmed();
        toperT.dbQuan = toper.record().value("дбкол").toBool();
        toperT.dbConst = toper.record().value("дбпост").toBool();
        toperT.dbSaldoVisible = toper.record().value("дбсалвидим").toBool();
        toperT.crAcc = toper.record().value("крсчет").toString().trimmed();
        toperT.crDict = toper.record().value("крсправ").toString().trimmed();
        toperT.crQuan = toper.record().value("кркол").toBool();
        toperT.crConst = toper.record().value("крпост").toBool();
        toperT.crSaldoVisible = toper.record().value("крсалвидим").toBool();
        toperT.isSingleString = toper.record().value("однаоперация").toBool();
        toperT.itog = toper.record().value("итоги").toString();
        toperT.freePrv = toper.record().value("независим").toBool();
        toperT.attributes = attr;
        toperT.docattributes = docAttr;
        topersList->append(toperT);
        toper.next();
    }
}


void DBFactory::getToperDictAliases(int oper, QList<ToperType>* topersList, QList<DictType>* dictsList)
{
    QString dictName;
    QString idFieldName = getObjectName("код");
    // Укажем, как обращаться к справочникам для заполнения кодов в проводках
    if (topersList->at(0).attributes && topersList->at(0).number == 0)
    {
        // Если в документе отсутствуют проводки, но присутствуют атрибуты, то в локальный список справочников попадают
        // связанные справочники из атрибутов
        QString attrName = QString("%1%2").arg(getObjectName("атрибуты")).arg(oper);
        foreach (QString fieldName, getFieldsList(attrName))
        {
            if (fieldName.left(4) == idFieldName + "_")
            {        // Если поле ссылается на другую таблицу
                dictName = fieldName;
                dictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                DictType dict;
                dict.name = dictName.toLower();
                dict.prototype = dict.name;
                dict.isSaldo = false;
                dict.isConst = false;
                dictsList->append(dict);
            }
        }
    }
    else
    {
        // Если в документе присутствуют проводки, то в локальный список справочников счетов попадают только справочники из корреспондирующих счетов
        // и не попадают связанные справочники из атрибутов
        QStringList prototypes;
        for (int i = 0; i < topersList->count(); i++)
        {
            ToperType toperT;
            DictType dict;
            bool    accFounded;
            toperT = topersList->at(i);
            // Присвоим имена справочникам, как они будут называться в списке справочников Dictionaries
            accounts.first();
            accFounded = false;
            while (accounts.isValid())
            {
                if (accounts.record().value(getObjectName("vw_счета.счет")).toString().trimmed().toLower() == toperT.crAcc)
                {
                    dictName = accounts.record().value(getObjectName("vw_счета.имясправочника")).toString().trimmed().toLower();
                    toperT.crDict = dictName;
                    toperT.crQuan = accounts.record().value(getObjectName("vw_счета.количество")).toBool();
                    if (dictName.size() > 0)
                    {
                        dict.name = dictName;
                        if (toperT.crQuan)
                        {      // Если в кредитовом справочнике ведется количественный учет
                            dict.acc = toperT.crAcc;
                            dict.isSaldo = true;
                            toperT.crDictAlias = "saldo" + dict.acc;
                        }
                        else
                        {
                            dict.isSaldo = false;
                            toperT.crDictAlias = dictName;
                        }
                        dict.prototype = accounts.record().value(getObjectName("vw_счета.прототип")).toString();
                        if (dict.prototype.size() == 0)
                            dict.prototype = dict.name;
                        if (!prototypes.contains(dict.prototype))
                        {
                            prototypes.append(dict.prototype);
                            if (dictName.left(9) == "ДОКУМЕНТЫ")
                                dict.isConst = true;
                            else
                                dict.isConst = toperT.crConst;
                            dict.isSet   = isSet(dictName);
                            dictsList->append(dict);
                        }
                    }
                    accFounded = true;
                    break;
                }
                accounts.next();
            }
            accounts.first();
            accFounded = false;
            while (accounts.isValid())
            {
                if (accounts.record().value(getObjectName("vw_счета.счет")).toString().trimmed().toLower() == toperT.dbAcc)
                {
                    dictName = accounts.record().value(getObjectName("vw_счета.имясправочника")).toString().trimmed().toLower();
                    toperT.dbDict = dictName;
                    toperT.dbQuan = accounts.record().value(getObjectName("vw_счета.количество")).toBool();
                    if (dictName.size() > 0)
                    {
                        dict.name = dictName;
                        dict.prototype = accounts.record().value(getObjectName("vw_счета.прототип")).toString();
                        if (dict.prototype.size() == 0)
                            dict.prototype = dict.name;
                        toperT.dbDictAlias = dictName;
                        if (!prototypes.contains(dict.prototype))
                        {
                            prototypes.append(dict.prototype);
                            dict.isSaldo = false;
                            dict.isConst = toperT.dbConst;
                            dict.isSet   = isSet(dictName);
                            dictsList->append(dict);
                            if (dict.isSet)     // Это набор справочников и счет дебетовый, поэтому откроем связанные справочники
                            {
                                foreach (QString fieldName, getFieldsList(dictName))
                                {
                                    if (fieldName.left(4) == idFieldName + "_")
                                    {        // Если поле ссылается на другую таблицу
                                        dictName = fieldName;
                                        dictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                        DictType childDict;
                                        childDict.name = dictName.toLower();
                                        childDict.prototype = childDict.name;
                                        childDict.isSaldo = false;
                                        if (dictName.left(9) == "ДОКУМЕНТЫ")
                                            childDict.isConst = true;
                                        else
                                            childDict.isConst = false;
                                        childDict.isSet = false;
                                        dictsList->append(childDict);
                                    }
                                }
                            }
                        }
                    }
                    accFounded = true;
                    break;
                }
                accounts.next();
            }
            if (!accFounded)
                TApplication::exemplar()->showError(QString(QObject::trUtf8("Не найден счет %1 в справочнике счетов").arg(toperT.dbAcc)));

            if (!accFounded)
                TApplication::exemplar()->showError(QString(QObject::trUtf8("Не найден счет %1 в справочнике счетов").arg(toperT.crAcc)));

            topersList->removeAt(i);
            topersList->insert(i, toperT);
        }
    }
}


QSqlQuery DBFactory::getDocumentAddQueriesList(int oper)
// Возвращает список наименований запросов, доступных для заполнения документа по данной типовой операции
{
    QString command = QString("SELECT %1, %2, %3 FROM %4 WHERE %5=%6 ORDER BY %1;").arg(getObjectNameCom("vw_запросы.имя"))
                                                                               .arg(getObjectNameCom("vw_запросы.код"))
                                                                               .arg(getObjectNameCom("vw_запросы.комментарий"))
                                                                               .arg(getObjectNameCom("vw_запросы"))
                                                                               .arg(getObjectNameCom("vw_запросы.опер"))
                                                                               .arg(oper);
    clearError();
    return execQuery(command);
}

/*
QString DBFactory::getDocumentSqlSelectStatement(int oper,  QList<ToperType>* topersList, QList<FieldType>* columnsProperties, int* retPrv1)
{
    QString selectStatement;
    QStringList columns;
    if (topersList->count() == 0)
    {   // В случае, если таблица проводок типовой операции пустая, то запрашиваем ее с сервера. Но она может быть и не пустая, если ее сформировал мастер
        getToperData(oper, topersList);
    }
    if (topersList->count() > 0)
    {
        QString selectClause, fromClause, whereClause;
        int prv, prv1 = 0;
        if (columnsProperties != 0)
            columnsProperties->clear();

        // Создадим клаузу проводок в секции SELECT
        QString tableName = getObjectName("проводки").toLower();
        QString idFieldName = getObjectName("код");
        QStringList prvFieldsList = getFieldsList(tableName, 0);
        QList<FieldType> fields;
        getColumnsProperties(&fields, tableName);
        QString field = getObjectName("проводки.код");
        selectClause.append(QString("p%1.\"%2\"").arg(topersList->at(0).number).arg(field));
        addColumnProperties(columnsProperties, tableName, QString("%1").arg(field), fields.at(0).type, fields.at(0).length, fields.at(0).precision, fields.at(0).readOnly, fields.at(0).constReadOnly);
        for (int i = 0; i < topersList->count(); i++)
        {   // Для всех проводок данной типовой операции
            prv = topersList->at(i).number;                     // получим номер проводки в типовой операции
            if (prv > 0)
            {
                foreach (const QString field, prvFieldsList)
                {// Для всех полей таблицы "проводки"
                    selectClause += (!selectClause.isEmpty() ? "," : "");                   // Добавим запятую, если это необходимо
                    selectClause.append(QString("p%1.\"%2\" AS \"P%1__%3\"").arg(prv).arg(getObjectName("проводки." + field)).arg(field.toUpper()));  // запишем в клаузу элемент <таблица>.<поле> с именем <таблица>__<поле>
                    for (int i = 0; i < fields.count(); i++)
                    {
                        if (fields.at(i).table == tableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, tableName, QString("P%1__%2").arg(prv).arg(field), fields.at(i).type, fields.at(i).length, fields.at(i).precision, fields.at(i).readOnly, fields.at(i).constReadOnly);
                    }
                }
                if (i == 0)
                {
                    fromClause = QString(" FROM \"%1\" p%2").arg(tableName).arg(prv);
                    prv1 = prv;
                    whereClause = " WHERE p";       // Создадим пометку в команде с пустой секцией WHERE.
                                                    // Непосредственно перед отправкой команды на сервер
                                                    // пустая секция WHERE заполняется реальной с фильтрами для текущего документа
                                                    // в фунции transformSelectStatement(QString)
                                                    // p в конце означает, что нужно ставить фильтр для типовой операции с проводками
                }
                else
                    fromClause.append(QString(" LEFT OUTER JOIN \"%1\" p%2 ON p%3.%4=p%2.%4 AND p%3.%5=p%2.%5 AND p%3.%6=p%2.%6 AND p%2.%7=%2").arg(tableName).arg(prv).arg(prv1).arg(getObjectNameCom("проводки.доккод")).arg(getObjectNameCom("проводки.стр")).arg(getObjectNameCom("проводки.опер")).arg(getObjectNameCom("проводки.номеропер")));
            }
        }
        // Соберем команду SELECT для проводок табличной части документа
        selectClause = QString("SELECT ").append(selectClause);
        selectStatement = selectClause + fromClause + whereClause;

        if (topersList->at(0).attributes)
        {   // Если имеются атрибуты для документа в данной операции
            QString attrName = QString("%1%2").arg(getObjectName("атрибуты")).arg(oper).toLower();
            getColumnsProperties(&fields, attrName);
            selectClause = "";
            QString attrSelectClause = "";
            QString attrFromClause = "";
            bool fieldReadOnly;
            foreach (QString fieldName, getFieldsList(attrName, 0))
            {
                if (fieldName == getObjectName(attrName + ".код") ||
                    fieldName == getObjectName(attrName + ".доккод") ||
                    fieldName == getObjectName(attrName + ".стр"))
                    fieldReadOnly = true;
                else
                    fieldReadOnly = false;
                if (fieldName.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    QString dictName = fieldName.toLower();
                    dictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                    selectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName.toUpper()).arg(fieldName.toUpper()));
                    attrSelectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName).arg(fieldName.toUpper()));
                    for (int i = 0; i < fields.count(); i++)
                        if (fields.at(i).table == attrName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, attrName, fieldName, fields.at(i).type, fields.at(i).length, fields.at(i).precision, fieldReadOnly, fieldReadOnly);
                    getColumnsProperties(&fields, dictName);
                    foreach (QString dictFieldName, getFieldsList(dictName, 0))
                    {
                            selectClause.append(QString("a.%1__%2,").arg(dictName.toUpper()).arg(dictFieldName.toUpper()));
                            attrSelectClause.append(QString("\"%1\".\"%3\" AS %2__%4,").arg(dictName).arg(dictName.toUpper()).arg(dictFieldName).arg(dictFieldName.toUpper()));
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == dictFieldName.toUpper() && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(dictName).arg(dictFieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                    }
                    attrFromClause.append(QString(" LEFT OUTER JOIN %1 ON a.%2=%1.%3").arg(dictName.toLower()).arg(fieldName).arg(getObjectName(dictName.toLower() + ".код")));
                }
                else
                {
                    selectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName.toUpper()).arg(fieldName.toUpper()));
                    attrSelectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName).arg(fieldName.toUpper()));
                    for (int i = 0; i < fields.count(); i++)
                        if (fields.at(i).table == attrName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, attrName, fieldName, fields.at(i).type, fields.at(i).length, fields.at(i).precision, fieldReadOnly, fieldReadOnly);
                }
            }
            selectClause.chop(1);
            attrSelectClause.chop(1);
            attrSelectClause = QString("SELECT DISTINCT ").append(attrSelectClause);
            attrFromClause = QString(" FROM %1 a").arg(attrName).append(attrFromClause);
            attrSelectClause.append(attrFromClause);

            if (fromClause.size() > 0)
            {   // Если типовая операция включает в себя проводки
                selectStatement = QString("SELECT DISTINCT p.*, %1 FROM (%2) p LEFT OUTER JOIN (%3) a ON p.\"P1__%4\"=a.%5 AND p.\"P1__%6\"=a.%7").arg(selectClause)
                                                                                                                                      .arg(selectStatement)
                                                                                                                                      .arg(attrSelectClause)
                                                                                                                                      .arg(getObjectName("атрибуты.доккод").toUpper())
                                                                                                                                      .arg(getObjectNameCom("атрибуты.доккод"))
                                                                                                                                      .arg(getObjectName("атрибуты.стр").toUpper())
                                                                                                                                      .arg(getObjectNameCom("атрибуты.стр"));
            }
            else
            {   // Если проводок нет
                selectStatement = attrSelectClause + " WHERE a ";
                // Создадим пометку в команде с пустой секцией WHERE.
                // Непосредственно перед отправкой команды на сервер
                // пустая секция WHERE заполняется реальной с фильтрами для текущего документа
                // в фунции transformSelectStatement(QString)
                // "a" в конце означает, что нужно ставить фильтр для типовой операции без проводок, но с атрибутами
            }
        }

        selectClause = "SELECT DISTINCT p.*";
        fromClause = " FROM (" + selectStatement + ") p";

        // Приступим к генерации секции SELECT, которая относится к задействованным в типовой операции справочникам
        QString dictName, prDictName__, prDictName, prefix;
        QStringList dictsNames;

        for (int i = 0; i < topersList->count(); i++)
        {
            prv = topersList->at(i).number;
            if (!topersList->at(i).dbConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).dbDict.toLower();
                if (topersList->at(i).dbAcc == topersList->at(i).crAcc && topersList->at(i).dbDict == topersList->at(i).crDict)
                {
                    prefix = "ДБ";
                    prDictName__ = QString(prefix + dictName + "__").toUpper();
                    prDictName = QString(prefix + dictName).toLower();
                }
                else
                {
                    prefix = "";
                    prDictName__ = dictName;
                    prDictName = dictName;
                }
                if (dictName.size() > 0 && !dictsNames.contains(prefix + dictName))
                {   // Если в по дебетовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (isSet(dictName))
                    { // Это набор (справочников)
                      // Сгенерируем команду SELECT для набора и входящих в него справочников
                        QString setSelectClause, setFromClause;
                        foreach (QString fieldName, getFieldsList(dictName, 0)) {
                            if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                                QString setDictName = fieldName.toLower();
                                setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                    setDictName = "документы";
                                getColumnsProperties(&fields, setDictName);
                                foreach (QString setDictFieldName, getFieldsList(setDictName, 0))
                                {
                                    QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper());
                                    if (!selectClause.contains(alias))
                                    {
                                        setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3\"").arg(setDictName).arg(setDictFieldName).arg(alias));
                                        selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(prDictName).arg(alias));
                                        for (int i = 0; i < fields.count(); i++)
                                            if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                                addColumnProperties(columnsProperties, prDictName, alias, fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                    }
                                }
                                if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                    setFromClause.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"документы\" ON \"%1\".\"%2\"=\"документы\".%3").arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                                else
                                    setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                            }
                        }
                        setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(getObjectNameCom(dictName + ".код")).append(setSelectClause);
                        setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                        setSelectClause.append(setFromClause);
                        fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(prDictName).arg(prv).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName, 0)) {
                            selectClause.append(QString(",%1.\"%2\" AS \"%3%4__%5\"").arg(prDictName).arg(field).arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(field.toUpper()));
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(prDictName).arg(prv).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectName(dictName + ".код")));
                    }
                    dictsNames << prefix + dictName;
                }
            }
            if (!topersList->at(i).crConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).crDict.toLower();
                if (topersList->at(i).dbAcc == topersList->at(i).crAcc && topersList->at(i).dbDict == topersList->at(i).crDict)
                {
                    prefix = "КР";
                    prDictName__ = QString(prefix + dictName + "__").toUpper();
                    prDictName = QString(prefix + dictName).toLower();
                }
                else
                {
                    prefix = "";
                    prDictName__ = dictName;
                    prDictName = dictName;
                }
                if (dictName.size() > 0 && !dictsNames.contains(prefix + dictName))
                {   // Если в по кредитовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (isSet(dictName))
                    {  // Это набор (справочников)
                        // Сгенерируем команду SELECT для набора и входящих в него справочников
                          QString setSelectClause, setFromClause;
                          foreach (QString fieldName, getFieldsList(dictName, 0)) {
                              if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                                  QString setDictName = fieldName.toLower();
                                  setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                  if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                      setDictName = "документы";
                                  getColumnsProperties(&fields, setDictName);
                                  foreach (QString setDictFieldName, getFieldsList(setDictName, 0))
                                  {
                                      QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper());
                                      if (!selectClause.contains(alias))
                                      {
                                          setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3\"").arg(setDictName).arg(setDictFieldName).arg(alias));
                                          selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(prDictName).arg(alias));
                                          for (int i = 0; i < fields.count(); i++)
                                              if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                                  addColumnProperties(columnsProperties, prDictName, alias, fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                      }
                                  }
                                  if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                      setFromClause.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"документы\" ON \"%1\".\"%2\"=\"документы\".%3").arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                                  else
                                      setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                              }
                          }
                          setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(getObjectNameCom(dictName + ".код")).append(setSelectClause);
                          setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                          setSelectClause.append(setFromClause);
                          fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(prDictName).arg(prv).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName, 0)) {
                            selectClause.append(QString(",%1.\"%2\" AS \"%3%4__%5\"").arg(prDictName).arg(field).arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(field.toUpper()));
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(prDictName).arg(prv).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectName(dictName + ".код")));
                    }
                    dictsNames << prefix + dictName;
                }
            }

            // Приступим к генерации списка сальдо
            QString salTableName = getObjectName("сальдо");
            getColumnsProperties(&fields, salTableName);
            QString field;
            if (topersList->at(i).dbSaldoVisible) {
                dictName = QString("дб%1").arg(topersList->at(i).dbAcc);
                if (topersList->at(i).dbQuan) {
                    field = getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                    field = getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                }
                field = getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                for (int i  = 0; i < fields.count(); i++)
                    if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                        addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.\"P%3__%4\"=%2.%5 AND p.\"P%3__%6\"=%2.%7").arg(getObjectNameCom("сальдо")).arg(dictName).arg(prv).arg(getObjectName("проводки.дбсчет").toUpper()).arg(getObjectNameCom("сальдо.счет")).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectNameCom("сальдо.код")));
            }
            if (topersList->at(i).crSaldoVisible) {
                dictName = QString("кр%1").arg(topersList->at(i).crAcc);
                if (topersList->at(i).crQuan) {
                    field = getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                    field = getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                }
                field = getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                for (int i  = 0; i < fields.count(); i++)
                    if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                        addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.\"P%3__%4\"=%2.%5 AND p.\"P%3__%6\"=%2.%7").arg(getObjectNameCom("сальдо")).arg(dictName).arg(prv).arg(getObjectName("проводки.крсчет").toUpper()).arg(getObjectNameCom("сальдо.счет")).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectNameCom("сальдо.код")));
            }
        }

        if (retPrv1 != 0)
            *retPrv1 = prv1;
        if (topersList->at(0).attributes && topersList->at(0).number == 0)
            selectStatement = selectClause + fromClause + QString(" ORDER BY %1 ASC;").arg(getObjectNameCom("атрибуты.стр"));
        else
            selectStatement = selectClause + fromClause + QString(" ORDER BY \"P1__%1\" ASC;").arg(getObjectName("проводки.стр").toUpper());

        // Получим заголовки столбцов
        getColumnsHeaders(QString("Документ%1").arg(oper), columnsProperties);
    }
    return selectStatement;
}
*/


QString DBFactory::getDocumentSqlSelectStatement(int oper,  QList<ToperType>* topersList, QList<FieldType>* columnsProperties, int* retPrv1)
{
    QString selectStatement;
    QStringList columns;
    if (topersList->count() == 0)
    {   // В случае, если таблица проводок типовой операции пустая, то запрашиваем ее с сервера. Но она может быть и не пустая, если ее сформировал мастер
        getToperData(oper, topersList);
    }
    if (topersList->count() > 0)
    {
        QString selectClause, fromClause, whereClause;
        int prv, prv1 = 0;
        if (columnsProperties != 0)
            columnsProperties->clear();

        // Создадим клаузу проводок в секции SELECT
        QString tableName = getObjectName("проводки").toLower();
        QString idFieldName = getObjectName("код");
        QStringList prvFieldsList = getFieldsList(tableName, 0);
        QList<FieldType> fields;
        getColumnsProperties(&fields, tableName);
        for (int i = 0; i < topersList->count(); i++)
        {   // Для всех проводок данной типовой операции
            prv = topersList->at(i).number;                     // получим номер проводки в типовой операции
            if (prv > 0)
            {
                foreach (const QString field, prvFieldsList)
                {// Для всех полей таблицы "проводки"
                    selectClause += (!selectClause.isEmpty() ? "," : "");                   // Добавим запятую, если это необходимо
                    selectClause.append(QString("p%1.\"%2\" AS \"P%1__%3\"").arg(prv).arg(getObjectName("проводки." + field)).arg(field.toUpper()));  // запишем в клаузу элемент <таблица>.<поле> с именем <таблица>__<поле>
                    for (int i = 0; i < fields.count(); i++)
                    {
                        if (fields.at(i).table == tableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, tableName, QString("P%1__%2").arg(prv).arg(field), fields.at(i).type, fields.at(i).length, fields.at(i).precision, fields.at(i).readOnly, fields.at(i).constReadOnly);
                    }
                }
                if (i == 0)
                {
                    fromClause = QString(" FROM \"%1\" p%2").arg(tableName).arg(prv);
                    prv1 = prv;
                    whereClause = " WHERE p";       // Создадим пометку в команде с пустой секцией WHERE.
                                                    // Непосредственно перед отправкой команды на сервер
                                                    // пустая секция WHERE заполняется реальной с фильтрами для текущего документа
                                                    // в фунции transformSelectStatement(QString)
                                                    // p в конце означает, что нужно ставить фильтр для типовой операции с проводками
                }
                else
                    fromClause.append(QString(" LEFT OUTER JOIN \"%1\" p%2 ON p%3.%4=p%2.%4 AND p%3.%5=p%2.%5 AND p%3.%6=p%2.%6 AND p%2.%7=%2").arg(tableName).arg(prv).arg(prv1).arg(getObjectNameCom("проводки.доккод")).arg(getObjectNameCom("проводки.стр")).arg(getObjectNameCom("проводки.опер")).arg(getObjectNameCom("проводки.номеропер")));
            }
        }
        // Соберем команду SELECT для проводок табличной части документа
        selectClause = QString("SELECT ").append(selectClause);
        selectStatement = selectClause + fromClause + whereClause;

        fromClause = QString("(%1) p").arg(selectStatement);
        selectClause = "SELECT DISTINCT p.*";
        // Приступим к генерации секции SELECT, которая относится к задействованным в типовой операции справочникам
        QString dictName, prDictName__, prDictName, prefix;
        QStringList dictsNames;

        for (int i = 0; i < topersList->count(); i++)
        {
            prv = topersList->at(i).number;
            if (!topersList->at(i).dbConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).dbDict.toLower();
                if (topersList->at(i).dbAcc == topersList->at(i).crAcc && topersList->at(i).dbDict == topersList->at(i).crDict)
                {
                    prefix = "ДБ";
                    prDictName__ = QString(prefix + dictName + "__").toUpper();
                    prDictName = QString(prefix + dictName).toLower();
                }
                else
                {
                    prefix = "";
                    prDictName__ = dictName;
                    prDictName = dictName;
                }
                if (dictName.size() > 0 && !dictsNames.contains(prefix + dictName))
                {   // Если в по дебетовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (isSet(dictName))
                    { // Это набор (справочников)
                      // Сгенерируем команду SELECT для набора и входящих в него справочников
                        QString setSelectClause, setFromClause;
                        foreach (QString fieldName, getFieldsList(dictName, 0))
                        {
                            if (fieldName.left(4) == idFieldName + "_")
                            {        // Если поле ссылается на другую таблицу
                                QString setDictName = fieldName.toLower();
                                setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                    setDictName = "документы";
                                getColumnsProperties(&fields, setDictName);
                                foreach (QString setDictFieldName, getFieldsList(setDictName, 0))
                                {
                                    QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper());
                                    if (!columns.contains(alias))
                                    {
                                        setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3\"").arg(setDictName).arg(setDictFieldName).arg(alias));
                                        selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(prDictName).arg(alias));
                                        for (int i = 0; i < fields.count(); i++)
                                            if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                                addColumnProperties(columnsProperties, prDictName, alias, fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                        columns.append(alias);
                                    }
                                }
                                if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                    setFromClause.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"документы\" ON \"%1\".\"%2\"=\"документы\".%3").arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                                else
                                    setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                            }
                            else
                            {
                                getColumnsProperties(&fields, dictName);
                                QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(fieldName.toUpper());
                                if (!columns.contains(alias))
                                {
                                    selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(fieldName).arg(alias));
                                    for (int i = 0; i < fields.count(); i++)
                                        if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                                            addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(fieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                    columns.append(alias);
                                }
                            }
                        }
                        setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(getObjectNameCom(dictName + ".код")).append(setSelectClause);
                        setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                        setSelectClause.append(setFromClause);
                        fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(prDictName).arg(prv).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName, 0))
                        {
                            QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(field.toUpper());
                            if (!columns.contains(alias))
                            {
                                selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(field).arg(alias));
                                for (int i = 0; i < fields.count(); i++)
                                    if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                        addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                columns.append(alias);
                            }
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(prDictName).arg(prv).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectName(dictName + ".код")));
                    }
                    dictsNames << prefix + dictName;
                }
            }
            if (!topersList->at(i).crConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).crDict.toLower();
                if (topersList->at(i).dbAcc == topersList->at(i).crAcc && topersList->at(i).dbDict == topersList->at(i).crDict)
                {
                    prefix = "КР";
                    prDictName__ = QString(prefix + dictName + "__").toUpper();
                    prDictName = QString(prefix + dictName).toLower();
                }
                else
                {
                    prefix = "";
                    prDictName__ = dictName;
                    prDictName = dictName;
                }
                if (dictName.size() > 0 && !dictsNames.contains(prefix + dictName))
                {   // Если в по кредитовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (isSet(dictName))
                    {  // Это набор (справочников)
                        // Сгенерируем команду SELECT для набора и входящих в него справочников
                          QString setSelectClause, setFromClause;
                          foreach (QString fieldName, getFieldsList(dictName, 0))
                          {
                              if (fieldName.left(4) == idFieldName + "_")
                              {        // Если поле ссылается на другую таблицу
                                  QString setDictName = fieldName.toLower();
                                  setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                  if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                      setDictName = "документы";
                                  getColumnsProperties(&fields, setDictName);
                                  foreach (QString setDictFieldName, getFieldsList(setDictName, 0))
                                  {
                                      QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper());
                                      if (!columns.contains(alias))
                                      {
                                          setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3\"").arg(setDictName).arg(setDictFieldName).arg(alias));
                                          selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(prDictName).arg(alias));
                                          for (int i = 0; i < fields.count(); i++)
                                              if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                                  addColumnProperties(columnsProperties, prDictName, alias, fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                          columns.append(alias);
                                      }
                                  }
                                  if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                      setFromClause.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"документы\" ON \"%1\".\"%2\"=\"документы\".%3").arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                                  else
                                      setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                              }
                              else
                              {
                                  getColumnsProperties(&fields, dictName);
                                  QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(fieldName.toUpper());
                                  if (!columns.contains(alias))
                                  {
                                      selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(fieldName).arg(alias));
                                      for (int i = 0; i < fields.count(); i++)
                                          if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                                              addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(fieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                      columns.append(alias);
                                  }
                              }
                          }
                          setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(getObjectNameCom(dictName + ".код")).append(setSelectClause);
                          setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                          setSelectClause.append(setFromClause);
                          fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(prDictName).arg(prv).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName, 0))
                        {
                            QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(field.toUpper());
                            if (!columns.contains(alias))
                            {
                                selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(field).arg(alias));
                                for (int i = 0; i < fields.count(); i++)
                                    if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                        addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                columns.append(alias);
                            }
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(prDictName).arg(prv).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectName(dictName + ".код")));
                    }
                    dictsNames << prefix + dictName;
                }
            }
            // Приступим к генерации списка сальдо
            QString salTableName = getObjectName("сальдо");
            getColumnsProperties(&fields, salTableName);
            QString field;
            if (topersList->at(i).dbSaldoVisible)
            {
                dictName = QString("дб%1").arg(topersList->at(i).dbAcc);
                if (topersList->at(i).dbQuan)
                {
                    field = getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                    field = getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                }
                field = getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                for (int i  = 0; i < fields.count(); i++)
                    if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                        addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.\"P%3__%4\"=%2.%5 AND p.\"P%3__%6\"=%2.%7").arg(getObjectNameCom("сальдо")).arg(dictName).arg(prv).arg(getObjectName("проводки.дбсчет").toUpper()).arg(getObjectNameCom("сальдо.счет")).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectNameCom("сальдо.код")));
            }
            if (topersList->at(i).crSaldoVisible)
            {
                dictName = QString("кр%1").arg(topersList->at(i).crAcc);
                if (topersList->at(i).crQuan)
                {
                    field = getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                    field = getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                }
                field = getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                for (int i  = 0; i < fields.count(); i++)
                    if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                        addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.\"P%3__%4\"=%2.%5 AND p.\"P%3__%6\"=%2.%7").arg(getObjectNameCom("сальдо")).arg(dictName).arg(prv).arg(getObjectName("проводки.крсчет").toUpper()).arg(getObjectNameCom("сальдо.счет")).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectNameCom("сальдо.код")));
            }
        }

        if (topersList->at(0).attributes)
        {   // Если имеются атрибуты для документа в данной операции
            QString attrName = QString("%1%2").arg(getObjectName("атрибуты")).arg(oper).toLower();
            getColumnsProperties(&fields, attrName);
            selectClause += ",";
            QString attrSelectClause = "";
            QString attrFromClause = "";
            foreach (QString fieldName, getFieldsList(attrName, 0))
            {
                if (fieldName.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    QString dictName = fieldName.toLower();
                    dictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                    QString alias = QString("%1").arg(fieldName.toUpper());
                    if (!columns.contains(alias))
                    {
                        selectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName.toUpper()).arg(alias));
                        columns.append(alias);
                    }
                    attrSelectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName).arg(fieldName.toUpper()));
                    for (int i = 0; i < fields.count(); i++)
                        if (fields.at(i).table == attrName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                            addColumnProperties(columnsProperties, attrName, fieldName, fields.at(i).type, fields.at(i).length, fields.at(i).precision, false, false);
                    getColumnsProperties(&fields, dictName);
                    foreach (QString dictFieldName, getFieldsList(dictName, 0))
                    {
                        QString alias = QString("%1__%2").arg(dictName.toUpper()).arg(dictFieldName.toUpper());
                        attrSelectClause.append(QString("\"%1\".\"%3\" AS \"%2__%4\",").arg(dictName).arg(dictName.toUpper()).arg(dictFieldName).arg(dictFieldName.toUpper()));
                        if (!columns.contains(alias))
                        {
                            selectClause.append(QString("a.\"%1\",").arg(alias));
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == dictFieldName.toUpper() && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(dictName).arg(dictFieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                            columns.append(alias);
                        }
                    }
                    attrFromClause.append(QString(" LEFT OUTER JOIN %1 ON a.%2=%1.%3").arg(dictName.toLower()).arg(fieldName).arg(getObjectName(dictName.toLower() + ".код")));
                }
                else
                {
                    QString alias = fieldName.toUpper();
                    attrSelectClause.append(QString("a.\"%1\" AS \"%2\",").arg(fieldName).arg(fieldName.toUpper()));
                    if (!columns.contains(alias))
                    {
                        selectClause.append(QString("a.\"%1\" AS \"%2\",").arg(fieldName.toUpper()).arg(alias));
                        for (int i = 0; i < fields.count(); i++)
                            if (fields.at(i).table == attrName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                                addColumnProperties(columnsProperties, attrName, fieldName, fields.at(i).type, fields.at(i).length, fields.at(i).precision, false, false);
                        columns.append(alias);
                    }
                }
            }
            selectClause.chop(1);
            attrSelectClause.chop(1);
            attrSelectClause = QString("SELECT DISTINCT ").append(attrSelectClause);
            attrFromClause = QString(" FROM %1 a").arg(attrName).append(attrFromClause);
            attrSelectClause.append(attrFromClause);


            fromClause.append(QString(" LEFT OUTER JOIN (%1) a ON p.\"P1__%2\"=a.%3 AND p.\"P1__%4\"=a.%5").arg(attrSelectClause)
                                                                                                          .arg(getObjectName("атрибуты.доккод").toUpper())
                                                                                                          .arg(getObjectNameCom("атрибуты.доккод"))
                                                                                                          .arg(getObjectName("атрибуты.стр").toUpper())
                                                                                                          .arg(getObjectNameCom("атрибуты.стр")));
        }
        if (retPrv1 != 0)
            *retPrv1 = prv1;
        if (topersList->at(0).attributes && topersList->at(0).number == 0)
            selectStatement = selectClause + " FROM " + fromClause + QString(" ORDER BY %1 ASC;").arg(getObjectNameCom("атрибуты.стр"));
        else
            selectStatement = selectClause + " FROM " + fromClause + QString(" ORDER BY \"P1__%1\" ASC;").arg(getObjectName("проводки.стр").toUpper());

        // Получим заголовки столбцов
        getColumnsHeaders(QString("Документ%1").arg(oper), columnsProperties);
    }
    return selectStatement;
}


QString DBFactory::getDictionarySqlSelectStatement(QString tableName, QString prefix)
{
    QString selectList;
    QString fromList;
    QString selectStatement;
    QList<FieldType> columnsProperties;
    QStringList tables;
    getColumnsProperties(&columnsProperties, tableName, tableName, 0);
    if (columnsProperties.size() > 0)
    {
        tables.append(columnsProperties.at(0).table);
        fromList = getObjectNameCom(tableName);
        FieldType fld, oldFld;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            fld = columnsProperties.at(i);
            if (!tables.contains(fld.table))
            {
                if (fld.table.left(9) == "документы" && fld.table.size() > 9)
                {
                    fromList.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"%1\" ON \"%2\".\"%3\"=\"%1\".\"%4\"").arg(fld.table)
                                                                                                 .arg(oldFld.table)
                                                                                                 .arg(oldFld.name)
                                                                                                 .arg(fld.name));
                    QString docAttr = fld.table;
                    docAttr = QString("докатрибуты%1").arg(docAttr.remove("документы"));
                    if (isTableExists(docAttr))
                    {
                        if (!tables.contains(docAttr))
                        {
                            fromList.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%1\".\"%2\"=\"%3\".\"%4\"").arg(docAttr)
                                                                                                             .arg("КОД")
                                                                                                             .arg(oldFld.table)
                                                                                                             .arg(oldFld.name));
                            tables.append(docAttr);
//                            getColumnsProperties(&columnsProperties, tableName, docAttr);
                        }
                    }
                }
                else
                    fromList.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".\"%4\"").arg(fld.table)
                                                                                                 .arg(oldFld.table)
                                                                                                 .arg(oldFld.name)
                                                                                                 .arg(fld.name));
                tables.append(fld.table);
            }
            if (selectList.size() > 0)
            selectList.append(", ");
            selectList.append(QString("\"%1\".\"%2\" AS \"%3%4\"").arg(fld.table)
                                                                  .arg(fld.name)
                                                                  .arg(prefix.toUpper())
                                                                  .arg(fld.column.toUpper()));
            oldFld = fld;
        }
        selectStatement.append(QLatin1String("SELECT DISTINCT ")).append(selectList);;
        selectStatement.append(QLatin1String(" FROM ")).append(fromList);
    }
    return selectStatement;
}



bool DBFactory::getToperSingleString(int operNumber)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = %4 AND (%5 = 0 OR %5 = 1);").arg(getObjectNameCom("vw_топер.однаоперация"))
                                                                                      .arg(getObjectNameCom("vw_топер"))
                                                                                      .arg(getObjectNameCom("vw_топер.опер"))
                                                                                      .arg(operNumber)
                                                                                      .arg(getObjectNameCom("vw_топер.номер")));
    if (query.first())
    {
        return query.value(0).toBool();
    }
    return false;
}


bool DBFactory::setToperSignleString(int operNumber, bool singleString)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 WHERE %2 = %3 AND (%4 = 0 OR %4 = 1);").arg(getObjectNameCom("vw_топер"))
                                                                                     .arg(getObjectNameCom("vw_топер.опер"))
                                                                                     .arg(operNumber)
                                                                                     .arg(getObjectNameCom("vw_топер.номер")));
    if (query.first())
    {   // Если операция существует
        return exec(QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND (%6 = 0 OR %6 = 1);").arg(getObjectNameCom("топер"))
                                                                              .arg(getObjectNameCom("топер.однаоперация"))
                                                                              .arg(singleString ? "true" : "false")
                                                                              .arg(getObjectNameCom("топер.опер"))
                                                                              .arg(operNumber)
                                                                              .arg(getObjectNameCom("топер.номер")));
    }
    return false;
}


QString DBFactory::getToperNumerator(int operNumber)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = %4 AND (%5 = 0 OR %5 = 1);").arg(getObjectNameCom("топер.нумератор"))
                                                                                      .arg(getObjectNameCom("топер"))
                                                                                      .arg(getObjectNameCom("топер.опер"))
                                                                                      .arg(operNumber)
                                                                                      .arg(getObjectNameCom("топер.номер")));
    if (query.first())
    {
        return query.value(0).toString();
    }
    return "";
}


bool DBFactory::setToperNumerator(int operNumber, QString numerator)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 WHERE %2 = %3 AND (%4 = 0 OR %4 = 1);").arg(getObjectNameCom("топер"))
                                                                                     .arg(getObjectNameCom("топер.опер"))
                                                                                     .arg(operNumber)
                                                                                     .arg(getObjectNameCom("топер.номер")));
    if (query.first())
    {   // Если операция существует
        return exec(QString("UPDATE %1 SET %2 = '%3' WHERE %4 = %5 AND (%6 = 0 OR %6 = 1);").arg(getObjectNameCom("топер"))
                                                                                .arg(getObjectNameCom("топер.нумератор"))
                                                                                .arg(numerator.trimmed())
                                                                                .arg(getObjectNameCom("топер.опер"))
                                                                                .arg(operNumber)
                                                                                .arg(getObjectNameCom("топер.номер")));
    }
    return false;
}


void DBFactory::setToperPermition(int operNumber, QString user, bool menu) {
    clearError();
    QString command;
    command = QString("SELECT * FROM %1 WHERE %2 = %3 AND %4 = '%5' AND %6 = '%7';").arg(getObjectNameCom("доступ"))
            .arg(getObjectNameCom("доступ.код_типыобъектов"))
            .arg(getTypeId("топер"))
            .arg(getObjectNameCom("доступ.имя"))
            .arg(operNumber)
            .arg(getObjectNameCom("доступ.имя_пользователи"))
            .arg(user);
    QSqlQuery query = execQuery(command);
    if (query.first())
    {   // Если операция существует
        command = QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND %6 = '%7' AND %8 = '%9';").arg(getObjectNameCom("доступ"))
                                                                                             .arg(getObjectNameCom("доступ.меню"))
                                                                                             .arg(menu ? "true" : "false")
                                                                                             .arg(getObjectNameCom("доступ.код_типыобъектов"))
                                                                                             .arg(getTypeId("топер"))
                                                                                             .arg(getObjectNameCom("доступ.имя"))
                                                                                             .arg(operNumber)
                                                                                             .arg(getObjectNameCom("доступ.имя_пользователи"))
                                                                                             .arg(user);
        exec(command);
    }
    else
    {
        command = QString("INSERT INTO %1 (%2, %3, %4, %5) VALUES ('%6', '%7', '%8', %9);").arg(getObjectNameCom("доступ"))
                                                                                         .arg(getObjectNameCom("доступ.код_типыобъектов"))
                                                                                         .arg(getObjectNameCom("доступ.имя"))
                                                                                         .arg(getObjectNameCom("доступ.имя_пользователи"))
                                                                                         .arg(getObjectNameCom("доступ.меню"))
                                                                                         .arg(getTypeId("топер"))
                                                                                         .arg(operNumber)
                                                                                         .arg(user)
                                                                                         .arg(menu ? "true" : "false");
        exec(command);
    }

}


void DBFactory::saveDocumentVariables(int docId, QString xml)
{
    QByteArray ba;
    QSqlQuery query;
    ba.append(xml);
    QString command = QString("UPDATE %1 SET %2 = E':value' WHERE %3 = %4;").arg(getObjectNameCom("документы"))
                                                                           .arg(getObjectNameCom("документы.переменные"))
                                                                           .arg(getObjectNameCom("документы.код"))
                                                                           .arg(docId);
    query.prepare(command);
    query.bindValue(":value", ba, QSql::In & QSql::Binary);
    if (!query.exec())
    {
        setError(query.lastError().text());
    }
}


QString DBFactory::restoreDocumentVariables(int docId)
{
    QString result;
    QString command = QString("SELECT %1 FROM %2 WHERE %3 = %4;").arg(getObjectNameCom("документы.переменные"))
                                                              .arg(getObjectNameCom("документы"))
                                                              .arg(getObjectNameCom("документы.код"))
                                                              .arg(docId);
    QSqlQuery query = execQuery(command);
    if (query.first())
        result = QString(query.record().field(0).value().toByteArray());
    return result;

}


void DBFactory::setConfig(QString config, QString name, QString value)
{
    clearError();
    QString command;
    command = QString("SELECT COUNT(*) FROM configs WHERE \"group\" = '%1' AND name = '%2';").arg(config).arg(name);

    QSqlQuery query = execQuery(command);
    query.first();
    if (query.value(0).toInt() > 0)     // Если уже есть запись о конфигурации
    {
        command = QString("UPDATE configs SET value = '%1' WHERE \"group\" = '%2' AND name = '%3';").arg(value).arg(config).arg(name);
        exec(command);
    }
    else
    {
        command = QString("INSERT INTO configs (\"group\", name, value) VALUES ('%1', '%2', '%3');").arg(config).arg(name).arg(value);
        exec(command);
    }
}


void DBFactory::appendCommand(QString command)
{
    if (!commands.contains(command))
        commands.append(command);
}


void DBFactory::appendCommand(UpdateValues value)
{
    for (int i = updateValues.count() - 1; i >= 0; i--)
    {
        if (value.recId == updateValues.at(i).recId && value.field == updateValues.at(i).field)
        {
            updateValues.removeAt(i);
        }
    }
    updateValues.append(value);
}


void DBFactory::clearCommands()
{
    updateValues.clear();
    commands.clear();
}


bool DBFactory::isExistsCommands()
{
    if (updateValues.count() > 1 || commands.count() > 1)
        return true;
    return false;
}


bool DBFactory::execCommands()
{
    // Соберем команды, скомпоновав вместе все данные для обновления отдельной записи
    QList<UpdateIds> ids;
    for (int i = 0; i < updateValues.count(); i++)
    {
        UpdateIds id;
        id.id = updateValues.at(i).recId;
        id.table = updateValues.at(i).table;
        bool found = false;
        foreach (UpdateIds i, ids)
        {
            if ((i.id == id.id) && (i.table == id.table))
            {
                found = true;
                break;
            }
        }
        if (!found)
            ids.append(id);
    }

    if (ids.count() > 0)
    {

        foreach(UpdateIds id, ids)
        {
            QString command;
            QString table;
            for (int i = 0; i < updateValues.count(); i++)
            {
                if (updateValues.at(i).recId == id.id && updateValues.at(i).table == id.table)
                {
                    table = updateValues.at(i).table;
                    if (command.size() > 0)
                        command.append(",");
                    command.append(QString("\"%1\"=%2").arg(getObjectName(table + "." + updateValues.at(i).field)).arg(updateValues.at(i).value));
                }
            }
            if (table.size() > 0)
            {
                command = QString("UPDATE \"%1\" SET %2 WHERE %3=%4;").arg(table).arg(command).arg(getObjectNameCom(table + ".код")).arg(id.id);
                appendCommand(command);     // Добавим команду к списку готовых команд
            }
        }
    }

    updateValues.clear();

    // Выполним все команды
    if (commands.count() > 1)                           // Если команд больше одной
    {
        if (beginTransaction())                         // То пачку команд снабдим транзакциями
        {
            for (int i = 0; i < commands.count(); i++)
            {
                if (!exec(commands.at(i)))
                {
                    rollbackTransaction();
                    clearCommands();
                    return false;
                }
            }
            commitTransaction();
        }
        else
        {
            clearCommands();
            return false;
        }
    }
    else if (commands.count() == 1)
        exec(commands.at(0));
    clearCommands();
    return true;
}


qulonglong DBFactory::calculateCRC32(QByteArray* array)
{
    unsigned long crc_table[256];
    unsigned long crc;
    char *buf = array->data();
    unsigned long len = array->count();

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    }

    crc = 0xFFFFFFFFUL;
    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFUL;
}


QVariant DBFactory::getValue(QString command, int row, int column)
{
    QVariant result;
    QSqlQuery data = execQuery(command);
    if (data.seek(row))
    {
        result = data.record().value(column);
    }
    return result;
}


QVariant DBFactory::getValue(QString command, int row, QString column)
{
    QVariant result;
    QSqlQuery data = execQuery(command);
    if (data.seek(row))
    {
        result = data.record().value(column);
    }
    return result;
}


QVariant DBFactory::getOstSum(QString acc, int id)
{
    return getValue(QString("SELECT %1 FROM %2 WHERE %3 = '%4' AND %5 = %6;").arg(getObjectNameCom("сальдо.консальдо"))
                                                                             .arg(getObjectNameCom("сальдо"))
                                                                             .arg(getObjectNameCom("сальдо.счет"))
                                                                             .arg(acc)
                                                                             .arg(getObjectNameCom("сальдо.код"))
                                                                             .arg(id),
                                                                              0, 0);
}


bool DBFactory::lockDocument(int docId)
{
    int id = getValue(QString("SELECT \"PID\" FROM \"блокдокументов\" WHERE \"КОД_ДОКУМЕНТЫ\" = %1;").arg(docId)).toInt();
    if (id > 0)
        return false;
    exec(QString("INSERT INTO \"блокдокументов\" (\"PID\", \"КОД_ДОКУМЕНТЫ\") VALUES (%1, %2);").arg(pid).arg(docId));
    return true;
}


void DBFactory::unlockDocument(int docId)
{
    exec(QString("DELETE FROM \"блокдокументов\" WHERE \"PID\" = %1 AND \"КОД_ДОКУМЕНТЫ\" = %2;").arg(pid).arg(docId));
}


void DBFactory::clearLockedDocuementList()
{
    exec(QString("DELETE FROM %1 WHERE %2 IN (SELECT %2 FROM %1 WHERE %2 NOT IN (SELECT pid FROM pg_stat_activity WHERE datname = '%3'))").arg("блокдокументов").arg("\"PID\"").arg(dbName));
}
