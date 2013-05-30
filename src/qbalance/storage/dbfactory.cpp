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
}


DBFactory::~DBFactory()
{
    delete dbExtend;
    delete db;

    QStringList list = QSqlDatabase::connectionNames();
    for(int i = 0; i < list.count(); ++i)
        QSqlDatabase::removeDatabase(list[i]);

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
                QProcess proc;
                QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                env.insert("PGPASSWORD", password);
                env.insert("PGCLIENTENCODING", TApplication::encoding());
                proc.setProcessEnvironment(env);
                proc.start(QString("psql -h %1 -p %2 -U postgres -f %3 %4").arg(hostName, QString::number(port), *script, dbName));

                lResult = proc.waitForStarted();

                if (!lResult)
                {// выдадим сообщение об ошибке и выйдем из цикла
                    TApplication::exemplar()->showError(QObject::trUtf8("Не удалось запустить psql"));
                }
                else
                {
                    lResult = proc.waitForFinished();
                    if (!lResult)
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
    wasError = true;
    errorText = errText;
    if (TApplication::debugMode())
    {
        TApplication::debugStream() << QDateTime().currentDateTime().toString(TApplication::logTimeFormat()) << " Error: " << errorText << "\n";
    }
    TApplication::exemplar()->showError(errText);
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
//  Владимир.
//  У меня этот вариант не работает ...
//    db->setConnectOptions("client_encoding=" + TApplication::encoding());
//    if (db->open(login, password)) {
//  поэтому пришлось сделать так:
    if (db->open()) {
        exec(QString("set client_encoding='%1';").arg(TApplication::encoding()));
        exec("set standard_conforming_strings=on;");
        currentLogin = login;
        currentPassword = password;

        return true;
    }
    else
        setError(db->lastError().text());
    return false;
}


void DBFactory::initDBFactory()
{
    initObjectNames();                  // Инициируем переводчик имен объектов из внутренних наименований в наименования БД
    loadSystemTables();

    files = execQuery(QString("SELECT %1, %2, %3, %4 FROM %5;").arg(getObjectNameCom("файлы.код"))
                                                               .arg(getObjectNameCom("файлы.имя"))
                                                               .arg(getObjectNameCom("файлы.тип"))
                                                               .arg(getObjectNameCom("файлы.контрсумма"))
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

    dictionariesPermitions.clear();
    dictionariesPermitions = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("доступ_к_справочникам")));

    columnsProperties.clear();
    columnsProperties = execQuery("SELECT DISTINCT lower(trim(table_name)) AS table_name, ins.ordinal_position::integer - 1 AS \"order\", ins.column_name AS column_name, ins.data_type AS type, COALESCE(ins.character_maximum_length::integer, 0) + COALESCE(ins.numeric_precision::integer, 0) AS length, COALESCE(ins.numeric_scale::integer, 0) AS \"precision\", ins.is_updatable AS updateable " \
                                  "FROM information_schema.columns ins " \
                                  "WHERE ins.table_schema = 'public' " \
                                  "ORDER BY table_name");

    config.clear();
    config = execQuery("SELECT name, value FROM configs;");

    accounts.clear();
    accounts = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("vw_счета")));

    columnsRestrictions.clear();
    columnsRestrictions = execQuery(QString("SELECT %1 FROM %2 WHERE %3=5 AND (%4 ILIKE '\%'||\"current_user\"()::text||'%' OR %4 ILIKE '\%*\%');")
                                                               .arg(getObjectNameCom("доступ.имя"))
                                                               .arg(getObjectNameCom("доступ"))
                                                               .arg(getObjectNameCom("доступ.код_типыобъектов"))
                                                               .arg(getObjectNameCom("доступ.пользователь")));


    dictionaries.clear();
    dictionaries = execQuery(QString("SELECT * FROM %1 ORDER BY %2;").arg(getObjectNameCom("справочники")).arg(getObjectNameCom("справочники.имя")));

    columnsHeaders.clear();
    columnsHeaders = execQuery(QString("SELECT lower(%1) AS %1, upper(%2) AS %2, %3, %4, %5 FROM %6;").arg(getObjectNameCom("vw_столбцы.справочник"))
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
    TApplication::debug("Exec: " + str + "\n");
    clearError();
    QSqlQuery* query;
    if (db != 0 && db->isValid())
        query = new QSqlQuery(*db);
    else
        query = new QSqlQuery();

    bool lResult = query->exec(str);
    if (!lResult && showError)
    {
        setError(query->lastError().text());
    }
    query->clear();
    delete query;
    return lResult;
}


QSqlQuery DBFactory::execQuery(QString str, bool showError, QSqlDatabase* extDb)
{
    TApplication::debug(QString("Query: %1\n").arg(str));
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
    query->clear();
    delete query;
    return result;
}


QStringList DBFactory::getUserList()
{
    static const QString clause = QString("SELECT %1 FROM %2 ORDER BY %1;").arg(getObjectNameCom("имя"))
                                                                          .arg(getObjectNameCom("vw_пользователи"));
    static short index          = 0;

    clearError();
    QStringList result;
    QSqlQuery query = execQuery(clause);

    while (query.next())
    {
        result << query.value(index).toString();
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


QStringList DBFactory::getFieldsList(QMap<int, FieldType>* columnsProperties)
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
    for (columnsProperties.first(); columnsProperties.isValid(); columnsProperties.next())
    {
        QSqlRecord record = columnsProperties.record();
        if (QString().compare(record.value("table_name").toString(), table.trimmed(), Qt::CaseInsensitive) == 0)
        {
            FieldType fld;
            fld.table  = table;
            fld.name      = record.value("column_name").toString().trimmed();
            fld.type      = record.value("type").toString().trimmed();
            fld.length    = record.value("length").toInt();
            fld.precision = record.value("precision").toInt();
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
                int currentRecord = columnsProperties.at();
                getColumnsProperties(result, dictName, table, level + 1);
                columnsProperties.seek(currentRecord);
            }
        }
    }
}


void DBFactory::addColumnProperties(QList<FieldType>* columnsProperties, QString table, QString name, QString type, int length, int precision, bool read, bool constRead, int number)
{
    // Выясним, нет ли уже такого поля, чтобы избежать появления полей
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
    return execQuery(QString("SELECT * FROM pg_tables WHERE schemaname = 'public' AND tablename = '%1'").arg(tName)).size() > 0 ? true : false;
}


bool DBFactory::createNewDictionary(QString tName, QString tTitle/* = ""*/, bool menu)
{
    if (!isTableExists(tName))
    {   // Если такой таблицы вует, то добавим ее
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
                        .arg(getObjectNameCom("доступ.пользователь"))
                        .arg(getObjectNameCom("доступ.имя"))
                        .arg(menu ? "true" : "false")
                        .arg(getTypeId(getObjectNameCom("типыобъектов.справочник")))
                        .arg(getLogin())
                        .arg(tName);
            if (exec(command))
            {
                command = QString("INSERT INTO %1 (%2, %3) VALUES ('%4', '%5');")
                            .arg(getObjectNameCom("справочники"))
                            .arg(getObjectNameCom("справочники.имя"))
                            .arg(getObjectNameCom("справочники.имя_в_списке"))
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
                        return true;
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
                        .arg(getTypeId(getObjectNameCom("типыобъектов.справочник")))
                        .arg(getObjectNameCom("доступ.пользователь"))
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
    return exec(QString("ALTER TABLE %1 ALTER COLUMN %2 TYPE %3;").arg(table).arg(columnName).arg(type));
}


bool DBFactory::addTableColumn(QString table, QString columnName, QString type)
{
    clearError();
    QString command = QString("ALTER TABLE %1 ADD COLUMN %2 %3;").arg(table).arg(columnName).arg(type);
    return exec(command);
}


bool DBFactory::dropTableColumn(QString table, QString columnName)
{
    clearError();
    return exec(QString("ALTER TABLE %1 DROP COLUMN %2;").arg(table).arg(columnName));
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
    int counter = 0;
    for (columnsHeaders.first(); columnsHeaders.isValid(); columnsHeaders.next())
    {
        if (columnsHeaders.record().value(getObjectName("vw_столбцы.справочник")).toString().trimmed().toLower() == tableName.toLower())
        {
            int number = columnsHeaders.record().value(getObjectName("vw_столбцы.номер")).toInt();
            if (number > 0)
            {
                QString column1 = columnsHeaders.record().value(getObjectName("vw_столбцы.столбец")).toString().toUpper();
                for (int i = 0; i < fields->count(); i++)
                {
                    if (column1 == fields->at(i).column.toUpper())
                    {
                        // Заголовок для столбца найден
                        counter++;
                        FieldType field = fields->at(i);
                        field.header = columnsHeaders.record().value(getObjectName("vw_столбцы.заголовок")).toString();
                        field.number = number;
                        field.headerExist = true;   // Для столбца найден заголовок
                        if (tableName.left(16) != "СписокДокументов" && !field.constReadOnly)
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


bool DBFactory::removeColumnHeaders(int tableId)
{
    clearError();
    QString command;
    command = QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("столбцы"))
                                                      .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
                                                      .arg(tableId);
    return exec(command);
}


bool DBFactory::appendColumnHeader(int tableId, QString column, QString header, int number, bool readOnly)
{
    clearError();
    QString command;
    command = QString("INSERT INTO %1 (%2, %3, %4, %5, %6) VALUES (%7, '%8', '%9', %10, %11);")
            .arg(getObjectNameCom("столбцы"))
            .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
            .arg(getObjectNameCom("столбцы.имя"))
            .arg(getObjectNameCom("столбцы.заголовок"))
            .arg(getObjectNameCom("столбцы.номер"))
            .arg(getObjectNameCom("столбцы.толькочтение"))
            .arg(tableId)
            .arg(column)
            .arg(header)
            .arg(number)
            .arg(readOnly ? "true" : "false");
    return exec(command);
}


bool DBFactory::insertDictDefault(QString tableName, QMap<QString, QVariant>* values)
{
    clearError();
    if (values->size() > 0)
    {
        QString fieldsList;
        QString valuesList;
        foreach (QString key, values->keys())
        {
            QString field = getObjectName(tableName + "." + key);
            field = field.size() > 0 ? field : key;
            fieldsList.append('"' + field + '"').append(',');
            QString str = values->value(key).toString();
            str.replace("'", "''");                         // Если в строке встречается апостроф, то заменим его двойным апострофом, иначе сервер не поймет
            str = "'" + str + "'";
            valuesList.append(str).append(',');
        }
        fieldsList.chop(1);
        valuesList.chop(1);
        QString command = QString("INSERT INTO \"%1\" (%2) VALUES (%3);").arg(tableName).arg(fieldsList).arg(valuesList);
        execQuery(command);
    }
    else
        execQuery("INSERT INTO " + tableName + " DEFAULT VALUES");
    return !wasError;
}


bool DBFactory::removeDictValue(QString tableName, qulonglong id)
{
    clearError();
    execQuery(QString("DELETE FROM \"%1\" WHERE \"%2\" = %3;").arg(tableName).arg(getObjectName("код")).arg(id));
    return !wasError;
}


int DBFactory::addDoc(int operNumber, QDate date)
{
    int result = 0;
    clearError();
    QString command = QString("SELECT sp_InsertDoc(%1,'%2')").arg(operNumber).arg(date.toString("dd.MM.yyyy"));
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
    return exec(QString("SELECT sp_DeleteDoc(%1)").arg(docId));
}


int DBFactory::addDocStr(int operNumber, int docId, QString cParam, int nQuan, int nDocStr)
{
    int result = 0;
    clearError();
    QString command = QString("SELECT sp_InsertDocStr(%1,%2,'%3'::character varying,%4,%5)").arg(operNumber).arg(docId).arg(cParam).arg(nQuan).arg(nDocStr);
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
    return exec(QString("SELECT sp_DeleteDocStr(%1,%2)").arg(docId).arg(nDocStr));
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
    exec(QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND %6 = %7 AND %8 = %9").arg(getObjectNameCom("проводки"))
                                                                               .arg(fieldName)
                                                                               .arg(val.toString())
                                                                               .arg(getObjectNameCom("проводки.доккод"))
                                                                               .arg(docId)
                                                                               .arg(getObjectNameCom("проводки.опер"))
                                                                               .arg(oper)
                                                                               .arg(getObjectNameCom("проводки.номеропер"))
                                                                               .arg(operNum));
}


QString DBFactory::initializationScriptPath() const
{
    QString result = QCoreApplication::applicationDirPath();

//    result.append("/src/qbalance");

    return result;
}


QStringList DBFactory::initializationScriptList(QString ext) const
{
    QStringList result;

    QDir dir(initializationScriptPath());
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
    QMap<QString, QString>::const_iterator i = ObjectNames.find(name);
    if (i != ObjectNames.end())
    {
        result = i.value();
    }
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


QByteArray DBFactory::getFile(QString fileName, FileType type, bool extend)
{
    if (extend && extDbExist)
    {   // Если будем смотреть файлы в расширенной базе данных
        QString text = QString("SELECT * FROM %1 WHERE %2 = '%3' AND %4 = %5").arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName)
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        QSqlQuery query = execQuery(text, dbExtend);
        query.first();
        if (query.isValid())
        {
            return query.record().value(getObjectName("файлы.значение")).toByteArray();
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
            QString text = QString("SELECT %1 FROM %2 WHERE %3 = %4;").arg(getObjectNameCom("файлы.значение"))
                                                                      .arg(getObjectNameCom("файлы"))
                                                                      .arg(getObjectNameCom("файлы.код"))
                                                                      .arg(id);
            QSqlQuery query = execQuery(text);
            query.first();
            if (query.isValid())
            {
                return query.record().value(0).toByteArray();
            }
        }
        files.next();
    }
    return QByteArray();
}


qulonglong DBFactory::getFileCheckSum(QString fileName, FileType type, bool extend)
{
    if (extend && extDbExist)
    {
        QString text = QString("SELECT %6 FROM %1 WHERE %2 = '%3' AND %4 = %5").arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName)
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type)
                                                                              .arg(getObjectNameCom("файлы.контрсумма"));
        QSqlQuery query = execQuery(text, dbExtend);
        query.first();
        if (query.isValid())
        {
            return query.record().value(0).toLongLong();
        }
        return 0;
    }
    files.first();
    while (files.isValid())
    {
        if (files.record().value(getObjectName("файлы.имя")).toString().trimmed() == fileName &&
            files.record().value(getObjectName("файлы.тип")).toInt() == type)
        {   // Если найден файл нужного типа и с нужным именем, то вернем его контрольную сумму
            return files.record().value(getObjectName("файлы.контрсумма")).toLongLong();
        }
        files.next();
    }
    return 0;
}


QStringList DBFactory::getFilesList(QString fileName, FileType type, bool extend)
{
    QStringList filesList;
    if (extend && extDbExist)
    {
        QString text = QString("SELECT * FROM %1 WHERE %2 ILIKE '%3' AND %4 = %5").arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName + "%")
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        QSqlQuery query = execQuery(text, dbExtend);
        query.first();
        if (query.isValid())
        {
            filesList << query.record().value(getObjectName("файлы.имя")).toString();
        }
        return filesList;
    }
    files.first();
    while (files.isValid())
    {
        if (files.record().value(getObjectName("файлы.имя")).toString().trimmed().startsWith(fileName) &&
            files.record().value(getObjectName("файлы.тип")).toInt() == type)
        {   // Если найден файл нужного типа и с нужным именем, то вернем его контрольную сумму
            filesList << files.record().value(getObjectName("файлы.имя")).toString();
        }
        files.next();
    }
    return filesList;
}



bool DBFactory::isFileExist(QString fileName, FileType type, bool extend)
{
    if (extend && extDbExist)
    {
        QString text = QString("SELECT count(*) FROM %1 WHERE %2 = '%3' AND %4 = %5").arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName)
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        QSqlQuery query = execQuery(text, dbExtend);
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


void DBFactory::setFile(QString fileName, FileType type, QByteArray fileData, qulonglong size, bool extend)
{
    clearError();
    QString text;
    if (isFileExist(fileName, type, extend))
    {
        // Если в базе уже есть такой файл
        text = QString("UPDATE %1 SET %2 = (:value), %3 = %4 WHERE %5 = '%6' AND %7 = %8;").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(size)
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(fileName)
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(type);
    }
    else
    {
        text = QString("INSERT INTO %1 (%2, %3, %4, %6) VALUES ('%7', %8, %9, (:value));").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(fileName)
                                                                                  .arg(type)
                                                                                  .arg(size);
    }
    QSqlQuery query(extend && extDbExist ? *dbExtend : *db);
    query.prepare(text);
    query.bindValue(":value", fileData, QSql::In & QSql::Binary);
    if (!query.exec())
    {
        setError(query.lastError().text());
    }
}


QSqlQuery DBFactory::getDataTypes()
{
    clearError();
    return execQuery("SELECT t.typname as name, t.typlen as len " \
                                "FROM pg_type t "\
                                "LEFT JOIN   pg_catalog.pg_namespace n ON n.oid = t.typnamespace " \
                                "WHERE (t.typrelid = 0 OR (SELECT c.relkind = 'c' FROM pg_catalog.pg_class c WHERE c.oid = t.typrelid)) " \
                                "AND NOT EXISTS(SELECT 1 FROM pg_catalog.pg_type el WHERE el.oid = t.typelem AND el.typarray = t.oid)" \
                                "AND n.nspname IN ('pg_catalog', 'information_schema')" \
                                "ORDER BY t.typname;");
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
    QSqlQuery toper = execQuery(QString("SELECT * FROM %1 WHERE %2=%3 ORDER BY %4").arg(getObjectNameCom("vw_топер")).arg(getObjectNameCom("vw_топер.опер")).arg(oper).arg(getObjectNameCom("vw_топер.номер")));
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
        toperT.dbDictVisible = toper.record().value("дбвидим").toBool();
        toperT.crAcc = toper.record().value("крсчет").toString().trimmed();
        toperT.crDict = toper.record().value("крсправ").toString().trimmed();
        toperT.crQuan = toper.record().value("кркол").toBool();
        toperT.crConst = toper.record().value("крпост").toBool();
        toperT.crSaldoVisible = toper.record().value("крсалвидим").toBool();
        toperT.crDictVisible = toper.record().value("крвидим").toBool();
        toperT.isSingleString = toper.record().value("однаоперация").toBool();
        toperT.itog = toper.record().value("итоги").toString();
        toperT.freePrv = toper.record().value("независим").toBool();
        toperT.attributes = toper.record().value("атрибуты").toBool();
        toperT.docattributes = toper.record().value("докатрибуты").toBool();
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
    QString command = QString("SELECT %1, %2 FROM %3 WHERE %4=%5 ORDER BY %1;").arg(getObjectNameCom("запросы.имя"))
                                                                               .arg(getObjectNameCom("запросы.код"))
                                                                               .arg(getObjectNameCom("запросы"))
                                                                               .arg(getObjectNameCom("запросы.опер"))
                                                                               .arg(oper);
    clearError();
    return execQuery(command);
}


QSqlRecord DBFactory::getDocumentAddQuery(int id)
// Возвращает локальный номер и текст запроса с заданным кодом
{
    QString command = QString("SELECT %1, %2 FROM %3 WHERE %4=%5;").arg(getObjectNameCom("запросы.номер"))
                                                                   .arg(getObjectNameCom("запросы.текст"))
                                                                   .arg(getObjectNameCom("запросы"))
                                                                   .arg(getObjectNameCom("запросы.код"))
                                                                   .arg(id);
    QSqlRecord record;
    clearError();
    QSqlQuery query = execQuery(command);
    if (query.next())
        record = query.record();
    return record;
}


QString DBFactory::getDocumentSqlSelectStatement(int oper,  QList<ToperType>* topersList, QList<FieldType>* columnsProperties, int* retPrv1)
{
    QString selectStatement;
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
                if (fieldName == getObjectName("атрибуты.код") ||
                    fieldName == getObjectName("атрибуты.доккод") ||
                    fieldName == getObjectName("атрибуты.стр"))
                    fieldReadOnly = true;
                else
                    fieldReadOnly = false;
                if (!(topersList->at(0).number != 0 && fieldName == getObjectName("атрибуты.код")))
                {
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
                            if (dictFieldName != idFieldName)
                            {  // покажем все поля, кроме поля "код"
                                selectClause.append(QString("a.%1__%2,").arg(dictName.toUpper()).arg(dictFieldName.toUpper()));
                                attrSelectClause.append(QString("\"%1\".\"%3\" AS %2__%4,").arg(dictName).arg(dictName.toUpper()).arg(dictFieldName).arg(dictFieldName.toUpper()));
                                for (int i = 0; i < fields.count(); i++)
                                    if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == dictFieldName.toUpper() && columnsProperties != 0)
                                        addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(dictName).arg(dictFieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                            }
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
        QString dictName;
        QStringList dictsNames;
        for (int i = 0; i < topersList->count(); i++)
        {
            prv = topersList->at(i).number;
            if (!topersList->at(i).dbConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).dbDict.toLower();

                if (dictName.size() > 0 && !dictsNames.contains(dictName))
                {   // Если в по дебетовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (isSet(dictName))
                    { // Это набор (справочников)
                      // Сгенерируем команду SELECT для набора и входящих в него справочников
                        QString setSelectClause, setFromClause;
                        foreach (QString fieldName, getFieldsList(dictName, 0)) {
                            if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                                QString setDictName = fieldName.toLower();
                                setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                getColumnsProperties(&fields, setDictName);
                                foreach (QString setDictFieldName, getFieldsList(setDictName, 0)) {
                                    setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3__%4\"").arg(setDictName).arg(setDictFieldName).arg(setDictName.toUpper()).arg(setDictFieldName.toUpper()));
                                    selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(dictName).arg(QString("%1__%2").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper())));
                                    for (int i = 0; i < fields.count(); i++)
                                        if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                            addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(setDictName).arg(setDictFieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                }
                                setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                            }
                        }
                        setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(getObjectNameCom(dictName + ".код")).append(setSelectClause);
                        setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                        setSelectClause.append(setFromClause);
                        fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(dictName).arg(prv).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName, 0)) {
                            selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(dictName).arg(prv).arg(getObjectName("проводки.дбкод").toUpper()).arg(getObjectName(dictName + ".код")));
                    }
                    dictsNames << dictName;
                }
            }
            if (!topersList->at(i).crConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).crDict.toLower();
                if (dictName.size() > 0 && !dictsNames.contains(dictName))
                {   // Если в по кредитовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (isSet(dictName))
                    {  // Это набор (справочников)
                        // Сгенерируем команду SELECT для набора и входящих в него справочников
                          QString setSelectClause, setFromClause;
                          foreach (QString fieldName, getFieldsList(dictName, 0)) {
                              if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                                  QString setDictName = fieldName.toLower();
                                  setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                  getColumnsProperties(&fields, setDictName);
                                  foreach (QString setDictFieldName, getFieldsList(setDictName, 0)) {
                                      setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3__%4\"").arg(setDictName).arg(setDictFieldName).arg(setDictName.toUpper()).arg(setDictFieldName.toUpper()));
                                      selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(dictName).arg(QString("%1__%2").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper())));
                                      for (int i = 0; i < fields.count(); i++)
                                          if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                              addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(setDictName).arg(setDictFieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                                  }
                                  setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(getObjectNameCom(setDictName + ".код")));
                              }
                          }
                          setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(getObjectNameCom(dictName + ".код")).append(setSelectClause);
                          setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                          setSelectClause.append(setFromClause);
                          fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(dictName).arg(prv).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName)) {
                            selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true);
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(dictName).arg(prv).arg(getObjectName("проводки.кркод").toUpper()).arg(getObjectName(dictName + ".код")));
                    }
                    dictsNames << dictName;
                }
            }
            QString salTableName = getObjectName("сальдо");
            getColumnsProperties(&fields, salTableName);
            QString field;
            if (topersList->at(i).dbSaldoVisible) {
                dictName = QString("дбсальдо%1").arg(prv);
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
                dictName = QString("крсальдо%1").arg(prv);
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
            selectStatement = selectClause + fromClause + QString(" ORDER BY %1 ASC").arg(getObjectNameCom("атрибуты.стр"));
        else
            selectStatement = selectClause + fromClause + QString(" ORDER BY \"P1__%1\" ASC").arg(getObjectName("проводки.стр").toUpper());

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
    QList<FieldType>    columnsProperties;
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
            .arg(getObjectNameCom("доступ.пользователь"))
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
                                                                                             .arg(getObjectNameCom("доступ.пользователь"))
                                                                                             .arg(user);
        exec(command);
    }
    else
    {
        command = QString("INSERT INTO %1 (%2, %3, %4, %5) VALUES ('%6', '%7', '%8', %9);").arg(getObjectNameCom("доступ"))
                                                                                         .arg(getObjectNameCom("доступ.код_типыобъектов"))
                                                                                         .arg(getObjectNameCom("доступ.имя"))
                                                                                         .arg(getObjectNameCom("доступ.пользователь"))
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
    for (int i = 0; i < updateValues.count(); i++)
    {
        if (value.recId == updateValues.at(i).recId && value.field == updateValues.at(i).field)
            return;
    }
    updateValues.append(value);
}


bool DBFactory::execCommands()
{
    // Сначала выполним готовые команды
    if (commands.count() > 1)
        beginTransaction();

    for (int i = 0; i < commands.count(); i++)
    {
        if (!exec(commands.at(i)))
        {
            if (commands.count() > 1)
                rollbackTransaction();
            commands.clear();
            return false;
        }
    }

    if (commands.count() > 1)
        commitTransaction();
    commands.clear();


    // Теперь соберем и выполним команды, скомпоновав вместе все данные для обновления отдельной записи
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

    if (ids.count() > 1)
        beginTransaction();

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
                command = QString("UPDATE \"%1\" SET %2 WHERE %3=%4").arg(table).arg(command).arg(getObjectNameCom(table + ".код")).arg(id.id);
                if (!exec(command))
                {
                    if (ids.count() > 1)
                        rollbackTransaction();
                    updateValues.clear();
                    return false;
                }

            }
        }
    }

    if (ids.count() > 1)
        commitTransaction();

    updateValues.clear();
    return true;
}


