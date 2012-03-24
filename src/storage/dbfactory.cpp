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

#include <QObject>
#include <QTextStream>
#include <QDateTime>
#include <QMap>
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
}


DBFactory::~DBFactory()
{
    delete db;
}


bool DBFactory::createNewDB(QString hostName, QString dbName, int port)
// Создает новую БД на сервере, если она отсутствует
{
    bool    lResult = true;
    QString defaultDatabase = getDatabaseName();
    setHostName(hostName);
    setDatabaseName("postgres");
    setPort(port);
    PassWordForm frm;
    frm.open();
    frm.addLogin("postgres");
    if (frm.exec())
    {
        const QString login = frm.getLogin();
        const QString password = frm.getPassword();
        if (open(login, password))
        {
            const QStringList scripts = initializationScriptList();
            if (scripts.size() > 0)
            {
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
                            env.insert("PGCLIENTENCODING", TApplication::encoding() );
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
            }
            else
                TApplication::exemplar()->showCriticalError(QString(QObject::trUtf8("Не найден файл(ы) инициализации БД (initdb*.sql).")));
            close();
       }
       else
          TApplication::exemplar()->showCriticalError(QObject::trUtf8("Не удалось создать соединение с сервером."));
    }
    setDatabaseName(defaultDatabase);
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
        currentLogin = login;
        return true;
    }
//    else
//        setError(db->lastError().text());
    return false;
}


void DBFactory::initDBFactory()
{
    initObjectNames();                  // Инициируем переводчик имен объектов из внутренних наименований в наименования БД
    objectTypes = execQuery(QString("SELECT * FROM %1;").arg(getObjectName("типыобъектов")));
}


void DBFactory::close()
{
    clearError();
    db->close();
    db->removeDatabase("default");
}


bool DBFactory::exec(QString str)
{
    TApplication::debug(" Query: " + str + "\n");

    clearError();
    QSqlQuery query;
    bool lResult = query.exec(str);
    if (!lResult)
    {
        setError(query.lastError().text());
    }
    return lResult;
}


QSqlQuery DBFactory::execQuery(QString str)
{
    TApplication::debug(" Query: " + str + "\n");

    clearError();
    QSqlQuery query;
    if (!query.exec(str))
    {
        setError(query.lastError().text());
    }
    return query;
}


QStringList DBFactory::getUserList()
{
    static const QString clause = QString("SELECT %1 FROM %2 ORDER BY %1;").arg(getObjectName("имя"))
                                                                          .arg(getObjectName("vw_пользователи"));
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
    return execQuery(QString("SELECT * FROM %1;").arg(getObjectName("vw_доступ_к_справочникам")));
}


QSqlRecord DBFactory::getDictionariesProperties(QString tableName/* = ""*/)
{
    QSqlRecord result;
    clearError();
    QString command = QString("SELECT * FROM %1 WHERE %2 = '%3';").arg(getObjectName("vw_доступ_к_справочникам"))
            .arg(getObjectName("vw_доступ_к_справочникам.таблица"))
            .arg(tableName);
    QSqlQuery query = execQuery(command);
    query.first();
    if (query.isValid())
    {
        result = query.record();
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


QStringList DBFactory::getFieldsList(QString tableName)
{
    QStringList result;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 LIMIT 0;").arg(tableName));
    for (int i = 0; i < query.record().count(); i++)
        result << query.record().fieldName(i);
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
            for (int k = 0; k < fieldList.count(); k++)
                if (QString(fieldList.at(k)).contains(getObjectName("код") + "_", Qt::CaseInsensitive)) {
                    result = true;                              // это набор, т.к. нет поля ИМЯ и есть поля-ссылки на другие справочники
                    break;
                }
            }
    }
    return result;
}


QSqlQuery DBFactory::getColumnsPropertiesQuery(QMap<int, FieldType>* result, QString table, QString tblName, QString prefix)
{
    QString tableName = (tblName.size() == 0 ? table : tblName);
    QString command(QString("SELECT DISTINCT s.*, COALESCE(c.%4, '') AS header, COALESCE(c.%5, 0) AS number " \
                            "FROM (SELECT ordinal_position-1 AS column, column_name AS name, data_type AS type, COALESCE(character_maximum_length, 0) + COALESCE(numeric_precision, 0) AS length, COALESCE(numeric_scale, 0) AS precision, is_updatable " \
                                   "FROM information_schema.columns " \
                                   "WHERE table_name LIKE '%1') s " \
                                   "LEFT OUTER JOIN " \
                                   "(SELECT %2 AS %3, %4, %5 "\
                                    "FROM %6 " \
                                    "WHERE trim(%7) = '%8' " \
                                    ") c ON s.name = c.%3 " \
                                    "ORDER BY s.column;").arg(table)
                                                         .arg(getObjectName("vw_столбцы.столбец"))
                                                         .arg(getObjectName("vw_столбцы.имя"))
                                                         .arg(getObjectName("vw_столбцы.заголовок"))
                                                         .arg(getObjectName("vw_столбцы.номер"))
                                                         .arg(getObjectName("vw_столбцы"))
                                                         .arg(getObjectName("vw_столбцы.справочник"))
                                                         .arg(tableName));
    QSqlQuery query = execQuery(command);
    int i = result->count();
    for (query.first(); query.isValid(); query.next())
    {
        FieldType fld;
        fld.name      = prefix + query.value(1).toString().trimmed();
        fld.type      = query.value(2).toString().trimmed();
        fld.length    = query.value(3).toInt();
        fld.precision = query.value(4).toInt();
        if (fld.name == getObjectName("код"))
            fld.readOnly = true;
        else
            fld.readOnly  = query.value(5).toString().trimmed().toUpper() == "YES" ? false : true;
        fld.header    = query.value(6).toString().trimmed();
        fld.number    = query.value(7).toInt();
        result->insert(i, fld);
        i++;
    }
    return query;
}


void DBFactory::getColumnsProperties(QMap<int, FieldType>* result, QString table, int oper)
{
    clearError();
    table = table.trimmed();
    QString tableName = (oper == 0 ? table : QString("СписокДокументов%1").arg(oper));
    result->clear();
    QSqlQuery query = getColumnsPropertiesQuery(result, table, tableName, "");
    // Просмотрим поля зависимых справочников
    for (query.first(); query.isValid(); query.next())
    {
        QString fieldName = query.value(1).toString().trimmed();
        if (fieldName.left(4) == getObjectName("код") + "_")    // Если это поле - ссылка на другой справочник
        {
            QString setDictName = fieldName;
            setDictName.remove(0, 4);               // Получим имя связанного справочника
            setDictName = setDictName.toLower();
            getColumnsPropertiesQuery(result, setDictName, "", setDictName + ".");
        }
    }
    if (QString::compare(table, getObjectName("сальдо"), Qt::CaseInsensitive) == 0)
    {
        foreach (int i, result->keys())
        {
            if ((QString(result->value(i).name).compare("конкол",    Qt::CaseInsensitive) == 0) ||
                (QString(result->value(i).name).compare("концена",   Qt::CaseInsensitive) == 0) ||
                (QString(result->value(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
            {
                  addColumnProperties(result, result->value(i).name, result->value(i).type, result->value(i).length, result->value(i).precision, result->value(i).readOnly);
            }
        }
    }
}


void DBFactory::getColumnsProperties(QList<FieldType>* result, QString table)
{   // Просто возвращает свойства колонок в виде QList, а не QMap
    QMap<int, FieldType> fields;
    result->clear();
    getColumnsProperties(&fields, table);
    foreach (FieldType fld, fields.values())
    {
        result->append(fld);
    }
}


void DBFactory::addColumnProperties(QMap<int, FieldType>* columnsProperties, QString name, QString type, int length, int precision, bool read, int number)
{
    int maxKey = 0;
    if (columnsProperties->count() > 0)
    {
        foreach (int i, columnsProperties->keys())
        {
            if (columnsProperties->value(i).name == name &&
                columnsProperties->value(i).type == type)
                return;
            if (i > maxKey)
                maxKey = i;
        }
        maxKey++;
    }
    FieldType fld;
    fld.name = name;
    fld.type = type;
    fld.length = length;
    fld.precision = precision;
    fld.readOnly = read;
    fld.number = number;
    columnsProperties->insert(maxKey, fld);
}


void DBFactory::getColumnsRestrictions(QString table, QMap<int, FieldType>* columns)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1, %2 " \
                                        "FROM %3 " \
                                        "WHERE %4=5 AND "\
                                            "(%5 ILIKE '\%'||\"current_user\"()::text||'%' OR "\
                                            "%5 ILIKE '\%*\%') AND " \
                                            "%1 ILIKE '%6.\%'").arg(getObjectName("доступ.имя"))
                                                               .arg(getObjectName("доступ.доступ"))
                                                               .arg(getObjectName("доступ"))
                                                               .arg(getObjectName("доступ.код_типыобъектов"))
                                                               .arg(getObjectName("доступ.пользователь"))
                                                               .arg(table.trimmed()));
    while (query.next()) {
        QString field = QString(query.value(0).toString()).remove(table.trimmed() + ".", Qt::CaseInsensitive).trimmed().toLower();
        foreach (int i, columns->keys())
        {
            if (columns->value(i).name.toLower() == field)
            {
                if (query.value(1).toString().contains("ro", Qt::CaseInsensitive))
                {
                    FieldType fld = columns->value(i);
                    fld.readOnly = true;
                    columns->remove(i);
                    columns->insert(i, fld);
                    break;
                } else if (query.value(1).toString().contains("hide", Qt::CaseInsensitive))
                {
                    columns->remove(i);
                    break;
                }
            }
        }
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
    QString dict = getObjectName("vw_справочники_со_столбцами");
    QString dictId = getObjectName("vw_справочники_со_столбцами.код");
    QString dictName = getObjectName("vw_справочники_со_столбцами.имя");
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = '%4';").arg(dictId)
                                                                             .arg(dict)
                                                                             .arg(dictName)
                                                                             .arg(dictionaryName));
    query.first();
    if (query.isValid()) {
        return query.value(0).toInt();
    }
    if (dictName.left(16) == "СписокДокументов")
    {
        int number = 1000000;
        clearError();
        QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2 WHERE %3 LIKE 'СписокДокументов%'").arg(dictId)
                                                                                                       .arg(dict)
                                                                                                       .arg(dictName));
        if (query.first())
        {
            return query.value(0).toInt() + 1;
        }
        return number;
    }
    if (dictName.left(8) == "Документ")
    {
        int number = 2000000;
        clearError();
        QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2 WHERE %3 LIKE 'Документ%'").arg(dictId)
                                                                                               .arg(dict)
                                                                                               .arg(dictName));
        if (query.first())
        {
            return query.value(0).toInt() + 1;
        }
        return number;
    }
    dict = getObjectName("справочники");
    dictId = getObjectName("справочники.код");
    dictName = getObjectName("справочники.имя");
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
    {   // Если такой таблицы не существует, то добавим ее
        QString command = QString("CREATE TABLE \"%1\" ("    \
                                  "\"%2\" SERIAL NOT NULL," \
                                  "\"%3\" CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING)" \
                                  "WITH (OIDS=FALSE);" \
                                  "REVOKE ALL ON \"%1\" FROM PUBLIC;"    \
                                  "GRANT ALL ON \"%1\" TO %4;" \
                                  "ALTER TABLE \"%1\" ADD CONSTRAINT \"%1_pkey\" PRIMARY KEY(\"%2\");")
                                  .arg(tName)
                                  .arg(getObjectName("код"))
                                  .arg(getObjectName("имя"))
                                  .arg(getLogin());
        if (exec(command))
        {
            command = QString("INSERT INTO \"%1\" (%2, %3, %4, %5) VALUES (%6, %7, '%8', '%9');")
                        .arg(getObjectName("доступ"))
                        .arg(getObjectName("доступ.меню"))
                        .arg(getObjectName("доступ.код_типыобъектов"))
                        .arg(getObjectName("доступ.пользователь"))
                        .arg(getObjectName("доступ.имя"))
                        .arg(menu ? "true" : "false")
                        .arg(getTypeId(getObjectName("типыобъектов.справочник")))
                        .arg(getLogin())
                        .arg(tName);
            if (exec(command))
            {
                command = QString("INSERT INTO \"%1\" (%2, %3) VALUES ('%4', '%5');")
                            .arg(getObjectName("справочники"))
                            .arg(getObjectName("справочники.имя"))
                            .arg(getObjectName("справочники.имя_в_списке"))
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
            command = QString("DELETE FROM \"%1\" WHERE %2 = %3 AND %4 = '%5' AND %6 = '%7';")
                        .arg(getObjectName("доступ"))
                        .arg(getObjectName("доступ.код_типыобъектов"))
                        .arg(getTypeId(getObjectName("типыобъектов.справочник")))
                        .arg(getObjectName("доступ.пользователь"))
                        .arg(getLogin())
                        .arg(getObjectName("доступ.имя"))
                        .arg(tName);
            if (exec(command))
            {
                command = QString("DELETE FROM \"%1\" WHERE %2 = '%3';")
                            .arg(getObjectName("справочники"))
                            .arg(getObjectName("справочники.имя"))
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
    return exec(QString("UPDATE %1 SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(getObjectName("справочники"))
                                                                             .arg(getObjectName("справочники.имя_в_списке"))
                                                                             .arg(menuName)
                                                                             .arg(getObjectName("справочники.имя_в_форме"))
                                                                             .arg(formName)
                                                                             .arg(getObjectName("справочники.имя"))
                                                                             .arg(tableName));
}


bool DBFactory::renameTableColumn(QString table, QString oldColumnName, QString newColumnName)
{
    clearError();
    exec(QString("ALTER TABLE %1 RENAME COLUMN %2 TO %3;").arg(table).arg(oldColumnName).arg(newColumnName));
    QSqlQuery dict = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = '" + table + "';").arg(getObjectName("справочники.код"))
                                                                                       .arg(getObjectName("справочники"))
                                                                                       .arg(getObjectName("справочники.имя")));
    dict.first();
    if (dict.isValid())
    {
        return exec(QString("UPDATE %1 SET %2 = '%3' WHERE \"%4\" = %5 AND %2 = '%3';").arg(getObjectName("столбцы"))
                                                                                   .arg(getObjectName("столбцы.имя"))
                                                                                   .arg(newColumnName)
                                                                                   .arg(getObjectName("столбцы.код_vw_справочники_со_столбцами"))
                                                                                   .arg(dict.value(0).toInt())
                                                                                   .arg(oldColumnName));
    }
    return false;
}


bool DBFactory::setTableColumnHeaderOrder(int tableId, QString column, QString header, int number)
{
    QString command;
    clearError();
    command = QString("SELECT * FROM %1 WHERE \"%2\" = %3 AND %4 = '%5';").arg(getObjectName("столбцы"))
                                                                     .arg(getObjectName("столбцы.код_vw_справочники_со_столбцами"))
                                                                     .arg(tableId)
                                                                     .arg(getObjectName("столбцы.имя"))
                                                                     .arg(column);
    QSqlQuery query = execQuery(command);
    query.first();
    if (query.isValid())
    {
        return updateColumnHeader(tableId, column, header, number);
    }
    return appendColumnHeader(tableId, column, header, number);
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
    return execQuery(QString("SELECT * FROM %1").arg(getObjectName("vw_доступ_к_топер")));
}


QSqlRecord DBFactory::getTopersProperties(int operNumber)
{
    clearError();
    QSqlRecord result;
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 WHERE %2 = %3;").arg(getObjectName("vw_доступ_к_топер"))
                                                                          .arg(getObjectName("vw_доступ_к_топер.опер"))
                                                                          .arg(operNumber));
    if (query.first())
        result = query.record();
    return result;
}


QSqlQuery DBFactory::getToper(int operNumber)
{
    clearError();
    return execQuery(QString("SELECT * FROM %1 WHERE %2 = %3 ORDER BY %4;").arg(getObjectName("топер"))
                                                                           .arg(getObjectName("топер.опер"))
                                                                           .arg(operNumber)
                                                                           .arg(getObjectName("топер.номер")));
}


bool DBFactory::deleteToper(int operNumber)
{
    clearError();
    return exec(QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectName("топер"))
                                                             .arg(getObjectName("топер.опер"))
                                                             .arg(operNumber));
}


bool DBFactory::deleteAllToperInfo(int operNumber)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT count(*) FROM %1 WHERE %2 = %3;").arg(getObjectName("документы"))
                                                                                 .arg(getObjectName("документы.опер"))
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
    exec(QString("DELETE FROM %1 WHERE \"%2\" = %3;").arg(getObjectName("столбцы"))
                                                .arg(getObjectName("столбцы.код_vw_справочники_со_столбцами"))
                                                .arg(getDictionaryId(QString("Документ%1").arg(operNumber))));
    exec(QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectName("топер"))
                                                 .arg(getObjectName("топер.опер"))
                                                 .arg(operNumber));
    exec(QString("DELETE FROM %1 WHERE %2 = '%3';").arg(getObjectName("файлы"))
                                                   .arg(getObjectName("файлы.имя"))
                                                   .arg(TApplication::exemplar()->getScriptFileName(operNumber)));
    commitTransaction();
    }
    return true;
}


bool DBFactory::addToperPrv(int operNumber, QString name, QString dbAcc, bool dbAccConst, bool dbVisible, bool dbSalVisible, QString crAcc, bool crAccConst, bool crVisible, bool crSalVisible, QString itog, bool freePrv)
{
    int number = 1;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2 WHERE %3 = %4;").arg(getObjectName("топер.номер"))
                                                                                .arg(getObjectName("топер"))
                                                                                .arg(getObjectName("топер.опер"))
                                                                                .arg(operNumber));
    if (query.first())
    {
        number = query.record().value(0).toInt() + 1;
    }
    QString command;
    command = QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14) " \
                      "VALUES (%15, %16, '%17', '%18', %19, %20, %21, '%22', %23, %24, %25, '%26', %27);").arg(getObjectName("топер"))
                                                                                             .arg(getObjectName("топер.опер"))
                                                                                             .arg(getObjectName("топер.номер"))
                                                                                             .arg(getObjectName("топер.имя"))
                                                                                             .arg(getObjectName("топер.дбсчет"))
                                                                                             .arg(getObjectName("топер.дбпост"))
                                                                                             .arg(getObjectName("топер.дбвидим"))
                                                                                             .arg(getObjectName("топер.дбсалвидим"))
                                                                                             .arg(getObjectName("топер.крсчет"))
                                                                                             .arg(getObjectName("топер.крпост"))
                                                                                             .arg(getObjectName("топер.крвидим"))
                                                                                             .arg(getObjectName("топер.крсалвидим"))
                                                                                             .arg(getObjectName("топер.итоги"))
                                                                                             .arg(getObjectName("топер.независим"))
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
                                                                                             .arg(freePrv ? "true" : "false");
    return exec(command);
}


int DBFactory::getNewToper()
{
    int number = 1;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT MAX(%1) FROM %2;").arg(getObjectName("топер.опер"))
                                                                  .arg(getObjectName("топер")));
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
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = 'база_фото';").arg(getObjectName("vw_константы.значение"))
                                                                                    .arg(getObjectName("vw_константы"))
                                                                                    .arg(getObjectName("vw_константы.имя")));
    if (query.first())
        result = query.record().field(0).value().toString();
    return result;
}

QString DBFactory::getPhotoPath(QString tableName)
{
    clearError();
    QString result, command;
    command = QString("SELECT %1 FROM %2 WHERE trim(%3) = '" + tableName + "';").arg(getObjectName("справочники.фото"))
            .arg(getObjectName("справочники"))
            .arg(getObjectName("справочники.имя"));
    QSqlQuery query = execQuery(command);
    if (query.first())
        result = query.record().field(0).value().toString().trimmed();
    return result;
}


QSqlQuery DBFactory::getColumnsHeaders(QString tableName)
{
    clearError();
    QString command = QString("SELECT %1, %2, %3 FROM %4 WHERE trim(%5) = '" + tableName + "' ORDER BY %3;").arg(getObjectName("vw_столбцы.столбец"))
            .arg(getObjectName("vw_столбцы.заголовок"))
            .arg(getObjectName("vw_столбцы.номер"))
            .arg(getObjectName("vw_столбцы"))
            .arg(getObjectName("vw_столбцы.справочник"));
    return execQuery(command);
}


bool DBFactory::appendColumnHeader(int tableId, QString column, QString header, int number)
{
    clearError();
    QString command = QString("INSERT INTO %1 (\"%2\", %3, %4, %5) VALUES (%6, '%7', '%8', %9);").arg(getObjectName("столбцы"))
            .arg(getObjectName("столбцы.код_vw_справочники_со_столбцами"))
            .arg(getObjectName("столбцы.имя"))
            .arg(getObjectName("столбцы.заголовок"))
            .arg(getObjectName("столбцы.номер"))
            .arg(tableId)
            .arg(column)
            .arg(header)
            .arg(number);
    return exec(command);
}


bool DBFactory::updateColumnHeader(int tableId, QString column, QString header, int number)
{
    clearError();
    if (number == 0)
        return exec(QString("UPDATE %1 SET %2 = '%3' WHERE \"%4\" = %5 AND %6 = '%7';").arg(getObjectName("столбцы"))
                    .arg(getObjectName("столбцы.заголовок"))
                    .arg(header)
                    .arg(getObjectName("столбцы.код_vw_справочники_со_столбцами"))
                    .arg(tableId)
                    .arg(getObjectName("столбцы.имя"))
                    .arg(column));
    return exec(QString("UPDATE %1 SET %2 = '%3', %4 = %5 WHERE \"%6\" = %7 AND %8 = '%9';").arg(getObjectName("столбцы"))
                .arg(getObjectName("столбцы.заголовок"))
                .arg(header)
                .arg(getObjectName("столбцы.номер"))
                .arg(number)
                .arg(getObjectName("столбцы.код_vw_справочники_со_столбцами"))
                .arg(tableId)
                .arg(getObjectName("столбцы.имя"))
                .arg(column));
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
            fieldsList.append(key).append(',');
            QString str = values->value(key).toString();
            str.replace("'", "''");                         // Если в строке встречается апостроф, то заменим его двойным апострофом, иначе сервер не поймет
            str = "'" + str + "'";
            valuesList.append(str).append(',');
        }
        fieldsList.chop(1);
        valuesList.chop(1);
        QString command = QString("INSERT INTO %1 (\"%2\") VALUES (%3)").arg(tableName).arg(fieldsList).arg(valuesList);
        execQuery(command);
    }
    else
        execQuery("INSERT INTO " + tableName + " DEFAULT VALUES");
    return !wasError;
}


bool DBFactory::removeDictValue(QString tableName, qulonglong id)
{
    clearError();
    execQuery(QString("DELETE FROM %1 WHERE %2 = %3").arg(tableName).arg(getObjectName("код")).arg(id));
    return !wasError;
}


bool DBFactory::addDoc(int operNumber, QDate date)
{
    clearError();
    return exec(QString("SELECT sp_InsertDoc(%1,'%2')").arg(operNumber).arg(date.toString("dd.MM.yyyy")));
}


bool DBFactory::removeDoc(int docId)
{
    clearError();
    return exec(QString("SELECT sp_DeleteDoc(%1)").arg(docId));
}


bool DBFactory::addDocStr(int operNumber, int docId, QString cParam, int nQuan, int nDocStr)
{
    clearError();
    return exec(QString("SELECT sp_InsertDocStr(%1,%2,'%3'::character varying,%4,%5)").arg(operNumber).arg(docId).arg(cParam).arg(nQuan).arg(nDocStr));
}


bool DBFactory::removeDocStr(int docId, int nDocStr)
{
    clearError();
    return exec(QString("SELECT sp_DeleteDocStr(%1,%2)").arg(docId).arg(nDocStr));
}


void DBFactory::setPeriod(QDate begDate, QDate endDate)
{
    clearError();
    exec(QString("UPDATE %1 SET %2='%3', %4='%5' WHERE %6='%7';").arg(getObjectName("блокпериоды"))
                                                                 .arg(getObjectName("блокпериоды.начало"))
                                                                 .arg(begDate.toString(Qt::LocaleDate))
                                                                 .arg(getObjectName("блокпериоды.конец"))
                                                                 .arg(endDate.toString(Qt::LocaleDate))
                                                                 .arg(getObjectName("блокпериоды.пользователь"))
                                                                 .arg(TApplication::exemplar()->getLogin()));
}


void DBFactory::getPeriod(QDate& begDate, QDate& endDate)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1, %2 FROM %3 WHERE %4='%5';").arg(getObjectName("блокпериоды.начало"))
                                                                               .arg(getObjectName("блокпериоды.конец"))
                                                                               .arg(getObjectName("блокпериоды"))
                                                                               .arg(getObjectName("блокпериоды.пользователь"))
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
    exec(QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND %6 = %7 AND %8 = %9").arg(getObjectName("проводки"))
                                                                               .arg(fieldName)
                                                                               .arg(val.toString())
                                                                               .arg(getObjectName("проводки.доккод"))
                                                                               .arg(docId)
                                                                               .arg(getObjectName("проводки.опер"))
                                                                               .arg(oper)
                                                                               .arg(getObjectName("проводки.номеропер"))
                                                                               .arg(operNum));
}


QString DBFactory::initializationScriptPath() const
{
    QString result = QCoreApplication::applicationDirPath();

    result.append("/src/");

    return result;
}


QStringList DBFactory::initializationScriptList() const
{
    QStringList result;

    QDir dir(initializationScriptPath());
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setSorting(QDir::Name | QDir::IgnoreCase);
    dir.setNameFilters(QStringList() << "*.sql");
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
    QSqlQuery query = execQuery(QString("SELECT * FROM objectnames;"));
    if (query.first())
    {   // Если на сервере есть определение имен объектов, то прочитаем его
        do {
            ObjectNames.insert(query.record().value("name").toString(), query.record().value("value").toString());
        } while (query.next());
        return;
    }
    // Если нет определения имен объектов, то заполним по умолчанию
    ObjectNames.insert("код", "код");
    ObjectNames.insert("имя", "имя");
    ObjectNames.insert("документы", "документы");
    ObjectNames.insert("документы.код", "код");
    ObjectNames.insert("документы.дата", "дата");
    ObjectNames.insert("документы.датавремя", "датавремя");
    ObjectNames.insert("документы.номер", "номер");
    ObjectNames.insert("документы.комментарий", "комментарий");
    ObjectNames.insert("документы.сумма", "сумма");
    ObjectNames.insert("документы.опер", "опер");
    ObjectNames.insert("документы.описание", "описание");
    ObjectNames.insert("документы.авто", "авто");
    ObjectNames.insert("документы.переменные", "переменные");
    ObjectNames.insert("проводки", "проводки");
    ObjectNames.insert("проводки.код", "код");
    ObjectNames.insert("проводки.дбкод", "дбкод");
    ObjectNames.insert("проводки.дбсчет", "дбсчет");
    ObjectNames.insert("проводки.кркод", "кркод");
    ObjectNames.insert("проводки.крсчет", "крсчет");
    ObjectNames.insert("проводки.кол", "кол");
    ObjectNames.insert("проводки.цена", "цена");
    ObjectNames.insert("проводки.сумма", "сумма");
    ObjectNames.insert("проводки.стр", "стр");
    ObjectNames.insert("проводки.доккод", "доккод");
    ObjectNames.insert("проводки.опер", "опер");
    ObjectNames.insert("проводки.номеропер", "номеропер");
    ObjectNames.insert("vw_топер", "vw_топер");
    ObjectNames.insert("vw_топер.код", "код");
    ObjectNames.insert("vw_топер.опер", "опер");
    ObjectNames.insert("vw_топер.номер", "номер");
    ObjectNames.insert("vw_топер.дбвидим", "дбвидим");
    ObjectNames.insert("vw_топер.крвидим", "крвидим");
    ObjectNames.insert("vw_топер.дбсалвидим", "дбсалвидим");
    ObjectNames.insert("vw_топер.крсалвидим", "крсалвидим");
    ObjectNames.insert("vw_топер.дбкол", "дбкол");
    ObjectNames.insert("vw_топер.кркол", "кркол");
    ObjectNames.insert("vw_топер.однаоперация", "однаоперация");
    ObjectNames.insert("константы", "константы");
    ObjectNames.insert("константы.имя", "имя");
    ObjectNames.insert("константы.значение", "значение");
    ObjectNames.insert("типыобъектов", "типыобъектов");
    ObjectNames.insert("типыобъектов.имя", "имя");
    ObjectNames.insert("типыобъектов.справочник", "справочник");
    ObjectNames.insert("типыобъектов.топер", "топер");
    ObjectNames.insert("доступ", "доступ");
    ObjectNames.insert("доступ.меню", "меню");
    ObjectNames.insert("доступ.код_типыобъектов", "код_типыобъектов");
    ObjectNames.insert("доступ.пользователь", "пользователь");
    ObjectNames.insert("доступ.имя", "имя");
    ObjectNames.insert("vw_доступ_к_топер", "vw_доступ_к_топер");
    ObjectNames.insert("vw_доступ_к_топер.имя", "имя");
    ObjectNames.insert("vw_доступ_к_топер.опер", "опер");
    ObjectNames.insert("справочники", "справочники");
    ObjectNames.insert("справочники.код", "КОД");
    ObjectNames.insert("справочники.имя", "имя");
    ObjectNames.insert("справочники.имя_в_списке", "имя_в_списке");
    ObjectNames.insert("справочники.имя_в_форме", "имя_в_форме");
    ObjectNames.insert("справочники.прототип", "прототип");
    ObjectNames.insert("справочники.фото", "фото");
    ObjectNames.insert("топер", "топер");
    ObjectNames.insert("топер.код", "код");
    ObjectNames.insert("топер.имя", "имя");
    ObjectNames.insert("топер.опер", "опер");
    ObjectNames.insert("топер.номер", "номер");
    ObjectNames.insert("топер.дбсчет", "дбсчет");
    ObjectNames.insert("топер.крсчет", "крсчет");
    ObjectNames.insert("топер.итоги", "итоги");
    ObjectNames.insert("топер.меню", "меню");
    ObjectNames.insert("топер.независим", "независим");
    ObjectNames.insert("топер.осндокумент", "осндокумент");
    ObjectNames.insert("топер.нумератор", "нумератор");
    ObjectNames.insert("топер.однаоперация", "однаоперация");
    ObjectNames.insert("топер.дбпост", "дбпост");
    ObjectNames.insert("топер.крпост", "крпост");
    ObjectNames.insert("топер.дбвидим", "дбвидим");
    ObjectNames.insert("топер.крвидим", "крвидим");
    ObjectNames.insert("топер.дбсалвидим", "дбсалвидим");
    ObjectNames.insert("топер.крсалвидим", "крсалвидим");
    ObjectNames.insert("счета", "счета");
    ObjectNames.insert("счета.счет", "счет");
    ObjectNames.insert("vw_счета", "vw_счета");
    ObjectNames.insert("vw_счета.код", "код");
    ObjectNames.insert("vw_счета.счет", "счет");
    ObjectNames.insert("vw_счета.имя", "имя");
    ObjectNames.insert("vw_счета.имясправочника", "имясправочника");
    ObjectNames.insert("vw_счета.баланс", "баланс");
    ObjectNames.insert("vw_счета.количество", "количество");
    ObjectNames.insert("vw_счета.прототип", "прототип");
    ObjectNames.insert("сальдо", "сальдо");
    ObjectNames.insert("сальдо.счет", "счет");
    ObjectNames.insert("сальдо.код", "код");
    ObjectNames.insert("сальдо.кол", "кол");
    ObjectNames.insert("сальдо.сальдо", "сальдо");
    ObjectNames.insert("сальдо.дбкол", "дбкол");
    ObjectNames.insert("сальдо.дебет", "дебет");
    ObjectNames.insert("сальдо.дбкол", "дбкол");
    ObjectNames.insert("сальдо.кркол", "кркол");
    ObjectNames.insert("сальдо.конкол", "конкол");
    ObjectNames.insert("сальдо.концена", "концена");
    ObjectNames.insert("сальдо.консальдо", "консальдо");
    ObjectNames.insert("столбцы", "столбцы");
    ObjectNames.insert("столбцы.имя", "имя");
    ObjectNames.insert("столбцы.код_vw_справочники_со_столбцами", "код_vw_справочники_со_столбцами");
    ObjectNames.insert("столбцы.заголовок", "заголовок");
    ObjectNames.insert("столбцы.номер", "номер");
    ObjectNames.insert("vw_столбцы", "vw_столбцы");
    ObjectNames.insert("vw_столбцы.справочник", "справочник");
    ObjectNames.insert("vw_столбцы.столбец", "столбец");
    ObjectNames.insert("vw_столбцы.заголовок", "заголовок");
    ObjectNames.insert("vw_столбцы.номер", "номер");
    ObjectNames.insert("vw_столбцы.имя", "имя");
    ObjectNames.insert("нумераторы", "нумераторы");
    ObjectNames.insert("нумераторы.имя", "имя");
    ObjectNames.insert("vw_доступ_к_справочникам", "vw_доступ_к_справочникам");
    ObjectNames.insert("vw_доступ_к_справочникам.имя", "имя");
    ObjectNames.insert("vw_доступ_к_справочникам.имя_в_форме", "имя_в_форме");
    ObjectNames.insert("vw_доступ_к_справочникам.таблица", "таблица");
    ObjectNames.insert("vw_доступ_к_справочникам.меню", "меню");
    ObjectNames.insert("vw_types", "vw_types");
    ObjectNames.insert("vw_types.код", "код");
    ObjectNames.insert("vw_types.имя", "имя");
    ObjectNames.insert("vw_types.тип", "тип");
    ObjectNames.insert("vw_types.длина", "длина");
    ObjectNames.insert("vw_пользователи", "vw_пользователи");
    ObjectNames.insert("vw_справочники_со_столбцами", "vw_справочники_со_столбцами");
    ObjectNames.insert("vw_справочники_со_столбцами.код", "код");
    ObjectNames.insert("vw_справочники_со_столбцами.имя", "имя");
    ObjectNames.insert("файлы", "файлы");
    ObjectNames.insert("файлы.имя", "имя");
    ObjectNames.insert("файлы.тип", "тип");
    ObjectNames.insert("файлы.значение", "значение");
    ObjectNames.insert("vw_константы", "vw_константы");
    ObjectNames.insert("vw_константы.значение", "значение");
    ObjectNames.insert("vw_константы.имя", "имя");
    ObjectNames.insert("блокпериоды", "блокпериоды");
    ObjectNames.insert("блокпериоды.начало", "начало");
    ObjectNames.insert("блокпериоды.конец", "конец");
    ObjectNames.insert("блокпериоды.пользователь", "пользователь");
}


QString DBFactory::getObjectName(const QString& name) const
// транслирует имена объектов БД из "внутренних" в реальные наименования
{
    QString result;
    // Присвоим результату значение по умолчанию
    if (name.contains('.'))
        result = name.mid(name.indexOf('.') + 1);
    else
        result = name;
    QMap<QString, QString>::const_iterator i = ObjectNames.find(name);
    if (i != ObjectNames.end())
    {
        result = i.value();
    }
    return result;
}


QByteArray DBFactory::getFile(QString fileName, FileType type)
{
    QString text = QString("SELECT * FROM %1 WHERE %2 = '%3' AND %4 = %5").arg(getObjectName("файлы"))
                                                                          .arg(getObjectName("файлы.имя"))
                                                                          .arg(fileName)
                                                                          .arg(getObjectName("файлы.тип"))
                                                                          .arg(type);
    QSqlQuery query = execQuery(text);
    if (query.first())
    {
        return query.value(query.record().indexOf("значение")).toByteArray();
    }
    return QByteArray();
}


void DBFactory::setFile(QString fileName, FileType type, QByteArray fileData)
{
    clearError();
    QString text = QString("SELECT * FROM %1 WHERE %2 = '%3' AND %4 = %5").arg(getObjectName("файлы"))
                                                                          .arg(getObjectName("файлы.имя"))
                                                                          .arg(fileName)
                                                                          .arg(getObjectName("файлы.тип"))
                                                                          .arg(type);
    QSqlQuery query = execQuery(text);
    if (query.first())
    {
        // Если в базе уже есть такой файл
        query.clear();
        text = QString("UPDATE %1 SET %2 = (:value) WHERE %3 = '%4' AND %5 = %6;").arg(getObjectName("файлы"))
                                                                                  .arg(getObjectName("файлы.значение"))
                                                                                  .arg(getObjectName("файлы.имя"))
                                                                                  .arg(fileName)
                                                                                  .arg(getObjectName("файлы.тип"))
                                                                                  .arg(type);
    }
    else
    {
        query.clear();
        text = QString("INSERT INTO %1 (%2, %3, %4) VALUES ('%5', %6, (:value));").arg(getObjectName("файлы"))
                                                                                  .arg(getObjectName("файлы.имя"))
                                                                                  .arg(getObjectName("файлы.тип"))
                                                                                  .arg(getObjectName("файлы.значение"))
                                                                                  .arg(fileName)
                                                                                  .arg(type);
    }
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
    QSqlQuery toper = execQuery(QString("SELECT * FROM %1 WHERE %2=%3 ORDER BY %4").arg(getObjectName("vw_топер")).arg(getObjectName("vw_топер.опер")).arg(oper).arg(getObjectName("vw_топер.номер")));
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
        topersList->append(toperT);
        toper.next();
    }
}


void DBFactory::getToperDictAliases(QList<ToperType>* topersList, QList<DictType>* dictsList)
{
    QString dictName;
    // Укажем, как обращаться к справочникам для заполнения кодов в проводках
    for (int i = 0; i < topersList->count(); i++)
    {
        ToperType toperT;
        DictType dict;
        toperT = topersList->at(i);
        // Присвоим имена справочникам, как они будут называться в списке справочников Dictionaries
        QSqlRecord accRecord = getAccountRecord(toperT.dbAcc);
        dictName = accRecord.value(getObjectName("vw_счета.имясправочника")).toString();
        toperT.dbDict = dictName;
        toperT.dbQuan = accRecord.value(getObjectName("vw_счета.количество")).toBool();
        if (dictName.size() > 0)
        {
            dict.name = dictName;
            dict.prototype = accRecord.value(getObjectName("vw_счета.прототип")).toString();
            if (dict.prototype.size() == 0)
                dict.prototype = dict.name;
            toperT.dbDictAlias = dictName;
            dict.isSaldo = false;
            dict.isConst = toperT.dbConst;
            if (dictsList != 0)
                dictsList->append(dict);
        }

        accRecord = getAccountRecord(toperT.crAcc);
        dictName = accRecord.value(getObjectName("vw_счета.имясправочника")).toString();
        toperT.crDict = dictName;
        toperT.crQuan = accRecord.value(getObjectName("vw_счета.количество")).toBool();
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
            dict.prototype = accRecord.value(getObjectName("vw_счета.прототип")).toString();
            if (dict.prototype.size() == 0)
                dict.prototype = dict.name;
            dict.isConst = toperT.crConst;
            if (dictsList != 0)
            dictsList->append(dict);
        }
        topersList->removeAt(i);
        topersList->insert(i, toperT);
    }
}


QString DBFactory::getDocumentSqlSelectStatement(int oper,  Dictionaries* dictionaries, QList<ToperType>* topersList, QMap<int, FieldType>* columnsProperties, int* retPrv1)
{
    QString selectStatement;
    QList<DictType> dictsList;
    if (topersList->count() == 0)
    {   // В случае, если таблица проводок типовой операции пустая, то запрашиваем ее с сервера. Но она может быть и не пустая, если ее сформировал мастер
        getToperData(oper, topersList);
    }
    if (topersList->count() > 0)
    {
        getToperDictAliases(topersList, &dictsList);
        QString selectClause, fromClause, whereClause;
        int prv, prv1 = 0;
        if (columnsProperties != 0)
            columnsProperties->clear();

        // Создадим клаузу проводок в секции SELECT
        QString tableName = getObjectName("проводки");
        QStringList prvFieldsList = getFieldsList(tableName);
        QMap<int, FieldType> fields;
        getColumnsProperties(&fields, tableName);
        for (int i = 0; i < topersList->count(); i++)
        {   // Для всех проводок данной типовой операции
            prv = topersList->at(i).number;                     // получим номер проводки в типовой операции
            foreach (const QString field, prvFieldsList)
            {// Для всех полей таблицы "проводки"
                selectClause += (!selectClause.isEmpty() ? "," : "");                   // Добавим запятую, если это необходимо
                selectClause.append(QString("p%1.%2 AS p%1__%2").arg(prv).arg(field));  // запишем в клаузу элемент <таблица>.<поле> с именем <таблица>__<поле>
                foreach(int i, fields.keys())
                {
                    if (fields.value(i).name == field && columnsProperties != 0)
                        addColumnProperties(columnsProperties, QString("p%1__%2").arg(prv).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, fields.value(i).readOnly);
                }
            }
            if (i == 0)
            {
                fromClause = QString(" FROM %1 p%2").arg(tableName).arg(prv);
                prv1 = prv;
                whereClause = " WHERE";     // Создадим пометку в команде с пустой секцией WHERE.
                                            // Непосредственно перед отправкой команды на сервер
                                            // пустая секция WHERE заполняется реальной с фильтрами для текущего документа
                                            // в фунции transformSelectStatement(QString)
            }
            else
            {
                fromClause.append(QString(" LEFT OUTER JOIN %1 p%2 ON p%3.%4=p%2.%4 AND p%3.%5=p%2.%5 AND p%3.%6=p%2.%6 AND p%2.%7=%2").arg(tableName).arg(prv).arg(prv1).arg(getObjectName("проводки.доккод")).arg(getObjectName("проводки.стр")).arg(getObjectName("проводки.опер")).arg(getObjectName("проводки.номеропер")));
            }
        }
        // Соберем команду SELECT для проводок табличной части документа
        selectClause = QString("SELECT ").append(selectClause);
        selectStatement = selectClause + fromClause + whereClause;
        selectClause = "SELECT DISTINCT p.*";
        fromClause = " FROM (" + selectStatement + ") p";

        // Приступим к генерации секции SELECT, которая относится к задействованным в типовой операции справочникам
        QString dictName;
        QStringList dictsNames;
        Dictionary* dict;
        QString idFieldName = getObjectName("код");
        for (int i = 0; i < topersList->count(); i++)
        {
            prv = topersList->at(i).number;
            if (!topersList->at(i).dbConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).dbDict;
                if (dictName.size() > 0 && !dictsNames.contains(dictName))
                {   // Если в по дебетовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    dict = dictionaries->getDictionary(dictName);
                    if (dict != 0 && dict->isSet())
                    { // Это набор (справочников)
                      // Сгенерируем команду SELECT для набора и входящих в него справочников
                        QString setSelectClause, setFromClause;
                        foreach (QString fieldName, getFieldsList(dictName)) {
                            if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                                QString setDictName = fieldName;
                                setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                getColumnsProperties(&fields, setDictName);
                                foreach (QString setDictFieldName, getFieldsList(setDictName)) {
                                    setSelectClause.append(QString(",%1.%2 AS %1__%2").arg(setDictName).arg(setDictFieldName));
                                    selectClause.append(QString(",%1.%2 AS %2").arg(dictName).arg(QString("%1__%2").arg(setDictName).arg(setDictFieldName)));
                                    foreach(int i, fields.keys())
                                        if (fields.value(i).name == setDictFieldName && columnsProperties != 0)
                                            addColumnProperties(columnsProperties, QString("%1__%2").arg(setDictName).arg(setDictFieldName), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                                }
                                setFromClause.append(QString(" LEFT OUTER JOIN %1 ON %2.%3=%1.код").arg(setDictName).arg(dictName).arg(fieldName));
                            }
                        }
                        setSelectClause = QString("SELECT %1.код").arg(dictName).append(setSelectClause);
                        setFromClause = QString(" FROM %1").arg(dictName).append(setFromClause);
                        setSelectClause.append(setFromClause);
                        fromClause.append(QString(" LEFT OUTER JOIN (%1) %2 ON p.p%3__%4=%2.код").arg(setSelectClause).arg(dictName).arg(prv).arg(getObjectName("проводки.дбкод")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName)) {
                            selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                            foreach(int i, fields.keys())
                                if (fields.value(i).name == field && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.p%2__%3=%1.код").arg(dictName).arg(prv).arg(getObjectName("проводки.дбкод")));
                    }
                    dictsNames << dictName;
                }
            }
            if (!topersList->at(i).crConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).crDict;
                if (dictName.size() > 0 && !dictsNames.contains(dictName))
                {   // Если в по кредитовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    dict = dictionaries->getDictionary(dictName);
                    if (dict != 0 && dict->isSet())
                    {  // Это набор (справочников)
                        // Сгенерируем команду SELECT для набора и входящих в него справочников
                          QString setSelectClause, setFromClause;
                          foreach (QString fieldName, getFieldsList(dictName)) {
                              if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                                  QString setDictName = fieldName;
                                  setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                  getColumnsProperties(&fields, setDictName);
                                  foreach (QString setDictFieldName, getFieldsList(setDictName)) {
                                      setSelectClause.append(QString(",%1.%2 AS %1__%2").arg(setDictName).arg(setDictFieldName));
                                      selectClause.append(QString(",%1.%2 AS %2").arg(dictName).arg(QString("%1__%2").arg(setDictName).arg(setDictFieldName)));
                                      foreach(int i, fields.keys())
                                          if (fields.value(i).name == setDictFieldName && columnsProperties != 0)
                                              addColumnProperties(columnsProperties, QString("%1__%2").arg(setDictName).arg(setDictFieldName), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                                  }
                                  setFromClause.append(QString(" LEFT OUTER JOIN %1 ON %2.%3=%1.код").arg(setDictName).arg(dictName).arg(fieldName));
                              }
                          }
                          setSelectClause = QString("SELECT %1.код").arg(dictName).append(setSelectClause);
                          setFromClause = QString(" FROM %1").arg(dictName).append(setFromClause);
                          setSelectClause.append(setFromClause);
                          fromClause.append(QString(" LEFT OUTER JOIN (%1) %2 ON p.p%3__%4=%2.код").arg(setSelectClause).arg(dictName).arg(prv).arg(getObjectName("проводки.кркод")));
                    }
                    else
                    {  // Это обычный справочник
                        getColumnsProperties(&fields, dictName);
                        foreach (QString field, getFieldsList(dictName)) {
                            selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                            foreach(int i, fields.keys())
                                if (fields.value(i).name == field && columnsProperties != 0)
                                    addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.p%2__%3=%1.код").arg(dictName).arg(prv).arg(getObjectName("проводки.кркод")));
                    }
                    dictsNames << dictName;
                }
            }
            getColumnsProperties(&fields, getObjectName("сальдо"));
            QString field;
            if (topersList->at(i).dbSaldoVisible) {
                dictName = QString("дбсальдо%1").arg(prv);
                if (topersList->at(i).dbQuan) {
                    field = getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                    foreach(int i, fields.keys())
                        if (fields.value(i).name == field && columnsProperties != 0)
                            addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                    field = getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                    foreach(int i, fields.keys())
                        if (fields.value(i).name == field && columnsProperties != 0)
                            addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                }
                field = getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                foreach(int i, fields.keys())
                    if (fields.value(i).name == field && columnsProperties != 0)
                        addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.p%3__%4=%2.%5 AND p.p%3__%6=%2.%7").arg(getObjectName("сальдо")).arg(dictName).arg(prv).arg(getObjectName("проводки.дбсчет")).arg(getObjectName("сальдо.счет")).arg(getObjectName("проводки.дбкод")).arg(getObjectName("сальдо.код")));
            }
            if (topersList->at(i).crSaldoVisible) {
                dictName = QString("крсальдо%1").arg(prv);
                if (topersList->at(i).crQuan) {
                    field = getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                    foreach(int i, fields.keys())
                        if (fields.value(i).name == field && columnsProperties != 0)
                            addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                    field = getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                    foreach(int i, fields.keys())
                        if (fields.value(i).name == field && columnsProperties != 0)
                            addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                }
                field = getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                foreach(int i, fields.keys())
                    if (fields.value(i).name == field && columnsProperties != 0)
                        addColumnProperties(columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.p%3__%4=%2.%5 AND p.p%3__%6=%2.%7").arg(getObjectName("сальдо")).arg(dictName).arg(prv).arg(getObjectName("проводки.крсчет")).arg(getObjectName("сальдо.счет")).arg(getObjectName("проводки.кркод")).arg(getObjectName("сальдо.код")));
            }
        }

        if (retPrv1 != 0)
            *retPrv1 = prv1;
        selectStatement = selectClause + fromClause + QString(" ORDER BY p.p1__%1 ASC").arg(getObjectName("проводки.стр"));

        QString tagName = QString("Документ%1").arg(oper);
        QSqlQuery headers = getColumnsHeaders(tagName);
        headers.first();
        while (headers.isValid())
        {
            QString header = headers.record().value(0).toString();
            foreach (int i, columnsProperties->keys())
            {
                if (columnsProperties->value(i).name == header)
                {
                    FieldType fld;
                    fld = columnsProperties->value(i);
                    fld.header = headers.record().value(1).toString();
                    fld.number = headers.record().value(2).toInt();
                    columnsProperties->remove(i);
                    columnsProperties->insert(i, fld);
                    break;
                }
            }
            headers.next();
        }

    }
    return selectStatement;
}


QSqlRecord DBFactory::getAccountRecord(QString cAcc)
{
    clearError();
    QString command = QString("SELECT * FROM %1 WHERE trim(%2) = '%3';").arg(getObjectName("vw_счета"))
                                                                        .arg(getObjectName("vw_счета.счет"))
                                                                        .arg(cAcc.trimmed());
    QSqlQuery query = execQuery(command);
    query.first();
    return query.record();
}


bool DBFactory::getToperSingleString(int operNumber)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = %4 AND %5 = 1;").arg(getObjectName("vw_топер.однаоперация"))
                                                                                      .arg(getObjectName("vw_топер"))
                                                                                      .arg(getObjectName("vw_топер.опер"))
                                                                                      .arg(operNumber)
                                                                                      .arg(getObjectName("vw_топер.номер")));
    if (query.first())
    {
        return query.value(0).toBool();
    }
    return false;
}


bool DBFactory::setToperSignleString(int operNumber, bool singleString)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 WHERE %2 = %3 AND %4 = 1;").arg(getObjectName("vw_топер"))
                                                                                     .arg(getObjectName("vw_топер.опер"))
                                                                                     .arg(operNumber)
                                                                                     .arg(getObjectName("vw_топер.номер")));
    if (query.first())
    {   // Если операция существует
        return exec(QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND %6 = 1;").arg(getObjectName("топер"))
                                                                              .arg(getObjectName("топер.однаоперация"))
                                                                              .arg(singleString ? "true" : "false")
                                                                              .arg(getObjectName("топер.опер"))
                                                                              .arg(operNumber)
                                                                              .arg(getObjectName("топер.номер")));
    }
    return false;
}


QString DBFactory::getToperNumerator(int operNumber)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = %4 AND %5 = 1;").arg(getObjectName("топер.нумератор"))
                                                                                      .arg(getObjectName("топер"))
                                                                                      .arg(getObjectName("топер.опер"))
                                                                                      .arg(operNumber)
                                                                                      .arg(getObjectName("топер.номер")));
    if (query.first())
    {
        return query.value(0).toString();
    }
    return "";
}


bool DBFactory::setToperNumerator(int operNumber, QString numerator)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM %1 WHERE %2 = %3 AND %4 = 1;").arg(getObjectName("топер"))
                                                                                     .arg(getObjectName("топер.опер"))
                                                                                     .arg(operNumber)
                                                                                     .arg(getObjectName("топер.номер")));
    if (query.first())
    {   // Если операция существует
        return exec(QString("UPDATE %1 SET %2 = '%3' WHERE %4 = %5 AND %6 = 1;").arg(getObjectName("топер"))
                                                                                .arg(getObjectName("топер.нумератор"))
                                                                                .arg(numerator.trimmed())
                                                                                .arg(getObjectName("топер.опер"))
                                                                                .arg(operNumber)
                                                                                .arg(getObjectName("топер.номер")));
    }
    return false;
}


void DBFactory::setToperPermition(int operNumber, QString user, bool menu) {
    clearError();
    QString command;
    command = QString("SELECT * FROM %1 WHERE %2 = %3 AND %4 = '%5' AND %6 = '%7';").arg(getObjectName("доступ"))
            .arg(getObjectName("доступ.код_типыобъектов"))
            .arg(getTypeId("топер"))
            .arg(getObjectName("доступ.имя"))
            .arg(operNumber)
            .arg(getObjectName("доступ.пользователь"))
            .arg(user);
    QSqlQuery query = execQuery(command);
    if (query.first())
    {   // Если операция существует
        command = QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND %6 = '%7' AND %8 = '%9';").arg(getObjectName("доступ"))
                                                                                             .arg(getObjectName("доступ.меню"))
                                                                                             .arg(menu ? "true" : "false")
                                                                                             .arg(getObjectName("доступ.код_типыобъектов"))
                                                                                             .arg(getTypeId("топер"))
                                                                                             .arg(getObjectName("доступ.имя"))
                                                                                             .arg(operNumber)
                                                                                             .arg(getObjectName("доступ.пользователь"))
                                                                                             .arg(user);
        exec(command);
    }
    else
    {
        command = QString("INSERT INTO %1 (%2, %3, %4, %5) VALUES (%1, '%2', '%3', %4);").arg(getObjectName("доступ"))
                                                                                         .arg(getObjectName("доступ.код_типыобъектов"))
                                                                                         .arg(getObjectName("доступ.имя"))
                                                                                         .arg(getObjectName("доступ.пользователь"))
                                                                                         .arg(getObjectName("доступ.меню"))
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
    QString command = QString("UPDATE %1 SET %2 = (:value) WHERE %3 = %4;").arg(getObjectName("документы"))
                                                                           .arg(getObjectName("документы.переменные"))
                                                                           .arg(getObjectName("документы.код"))
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
    QString command = QString("SELECT %1 FROM %2 WHERE %3 = %4;").arg(getObjectName("документы.переменные"))
                                                              .arg(getObjectName("документы"))
                                                              .arg(getObjectName("документы.код"))
                                                              .arg(docId);
    QSqlQuery query = execQuery(command);
    if (query.first())
        result = QString(query.record().field(0).value().toByteArray());
    return result;

}
