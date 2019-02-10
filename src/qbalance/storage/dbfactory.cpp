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

#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlDriver>
#include <QtCore/QHash>
#include "dbfactory.h"
#include "../kernel/app.h"
#include "../gui/passwordform.h"
#include "../gui/messagewindow.h"
#include "../kernel/dictionaries.h"


DBFactory::DBFactory() : QObject()
{
    app = TApplication::exemplar();
    db = 0;
    dbExtend = 0;
    updateNum = 0;
    proc = 0;
    dbIsOpened = false;
    extDbExist = false;

    errorText.clear();
    //    clearError();
    commands.clear();

    hostName = "localhost";
    port = 0;
    dbName = "qbalance";
    secDiff;
}


DBFactory::~DBFactory()
{
    delete dbExtend;
    delete db;
}


bool DBFactory::open()
{
    return open("", "");
}


bool DBFactory::open(QString, QString)
{
    return true;
}


bool DBFactory::isOpened()
{
    return dbIsOpened;
}

int DBFactory::openDBDialog()
{
    return 0;
}


int DBFactory::getPort()
{
    return port;
}


QString DBFactory::getHostName()
{
    return hostName;
}


QString DBFactory::getLogin()
{
    return currentLogin;
}


void DBFactory::setHostName(QString name)
{
    hostName = (name == "127.0.0.1" ? "localhost" : name);
}


void DBFactory::setPort(int portNum)
{
    port = portNum;
}


void DBFactory::setDatabaseName(QString name)
{
    dbName = name;
}


QString DBFactory::getDatabaseName()
{
    return dbName;
}


QSqlDatabase* DBFactory::getDB()
{
    return db;
}


QSqlQuery DBFactory::getAccounts()
{
    return accounts;
}

void DBFactory::getConfig(QString configName, QHash<QString, int> *values)
{
    config.first();
    while (config.isValid())
    {
        if (config.record().value("group").toString() == configName)
        {
            values->insert(config.record().value("name").toString(), config.record().value("value").toInt());
        }
        config.next();
    }
}


QVariant DBFactory::getValue(QString command)
{
    return getValue(command, 0, 0);
}


bool DBFactory::createNewDBs(QString hostName, QString dbName, int port)
// Создает новую БД на сервере, если она отсутствует
{
    bool    lResult = true;
    QString defaultDatabase = getDatabaseName();
    setHostName(hostName);
    setDatabaseName(dbName);
    setPort(port);
    PassWordForm* frm = new PassWordForm();
    frm->open();
    frm->addLogin("postgres");
    if (frm->exec())
    {
        const QString login = frm->getLogin();
        const QString password = frm->getPassword();
/*
        if (open(login, password))
        {
*/
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
                app->showError(QString(QObject::trUtf8("Не найден файл(ы) инициализации БД (initdb*.sql).")));
            close();
/*
       }
       else
          app->showError(QObject::trUtf8("Не удалось создать соединение с сервером."));
*/
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
    app->getMessageWindow()->show();
    QString command = QString("CREATE DATABASE %1 WITH TEMPLATE template0 ENCODING = 'UTF-8';").arg(dbName);
    if (execPSql(QStringList() << QString("-c \"%1\"").arg(command), "postgres", password))
    {
        //Drake
        //Нет смысла создавать локальный временный экземпляр в куче
        //Лучше на стеке - система его удалит
        foreach (QString script, scripts)
        {
            lResult = execPSql(QStringList() << "-f" << script << dbName, "postgres", password);
        }
        command = QString("ALTER DATABASE %1 OWNER TO %2;").arg(dbName).arg("sa");
        lResult = execPSql(QStringList() << QString("-c \"%1\"").arg(command), "postgres", password);
    }
//    app->saveMessages();
    app->getMessageWindow()->hide();
    return lResult;
}


bool DBFactory::execPSql(QStringList comm, QString user, QString password)
{
    bool result = false;
    QStringList parameters;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PGPASSWORD", password);
    env.insert("PGCLIENTENCODING", TApplication::encoding());
    proc = new QProcess(app);
    proc->setWorkingDirectory(app->applicationDirPath());
    proc->setProcessEnvironment(env);

    QString command;

    parameters.append(QString("-U %1").arg(user));
    parameters.append(QString("-h %1").arg(hostName));
    parameters.append(QString("-p %1").arg(port));
    parameters.append(comm);

    command.append("psql ").append(parameters.join(" "));

    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(showPSqlMessage()));
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(showPSqlMessage()));

    app->print(command);

    app->debug(1, "Init command: " + command);

    proc->start(command);
    if (proc->waitForFinished(-1))
        result = true;

    disconnect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(showPSqlMessage()));
    disconnect(proc, SIGNAL(readyReadStandardError()), this, SLOT(showPSqlMessage()));

    delete proc;
    return result;
}


void DBFactory::showPSqlMessage()
{
    app->print(QString(proc->readAllStandardOutput()).trimmed());
    app->getMessageWindow()->getTextEditor()->repaint();
}


void DBFactory::clearError()
{
    wasError = false;
    errorNumber = 0;
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
    app->debug(1, " Error: " + errorText);
    app->showError(errText);
    if (emergencyExit)
        app->exit();
}


bool DBFactory::beginTransaction()
{
    QString command = "BEGIN;";
//    app->debug(1, command);
    return exec(command);
}


void DBFactory::commitTransaction()
{
    QString command = "COMMIT;";
//    app->debug(1, command);
    exec(command);
}


void DBFactory::rollbackTransaction()
{
    QString command = "ROLLBACK;";
//    app->debug(1, command);
    exec(command);
}


void DBFactory::initDBFactory()
{
    initObjectNames();                  // Инициируем переводчик имен объектов из внутренних наименований в наименования БД
    loadSystemTables();
}


void DBFactory::loadSystemTables()
{
    objectTypes.clear();
    config.clear();
    accounts.clear();
    columnsRestrictions.clear();

    // Установим прототипы справочников
    QSqlQuery dicts = execQuery(QString("SELECT * FROM %1 ORDER BY %2;").arg(getObjectNameCom("справочники"))
                                           .arg(getObjectNameCom("справочники.имя")));
    QString fieldName = getObjectName("справочники.имя");
    QString prototypeFieldName = getObjectName("справочники.прототип");
    if (dicts.first())
    {
        do
        {
            dictsPrototypes.insert(dicts.record().value(fieldName).toString(), dicts.record().value(prototypeFieldName).toString());
        } while (dicts.next());
    }
}


bool DBFactory::isView(QString tableName)
{
    return (tables.value(tableName) == "view" ? true : false);
}


void DBFactory::reloadDictionariesPermitions()
{
    dictionariesPermitions.clear();
    dictionariesPermitions = execQuery(QString("SELECT * FROM %1;").arg(getObjectNameCom("доступ_к_справочникам")));
    reloadColumnProperties();
    reloadColumnHeaders();
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
    app->debug(1, "Exec: " + str);

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
    delete query;
    return lResult;
}


void DBFactory::exec(QStringList commList)
{
    foreach (QString command, commList)
        exec(command);
}


bool DBFactory::execQueryFile(QString fileName, bool showError)
{
    bool result = false;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly))
    {
        QString script = QString().append(file.readAll());
        if (script.size() > 0)
            result = exec(script, showError);
        file.close();
    }
    return result;
}



bool DBFactory::execSystem(QString command, QString tableName)
{
    if (sysTables.contains(tableName))
        saveUpdate(command);
    return exec(command);
}


QSqlQuery DBFactory::execQuery(QString str, bool showError, QSqlDatabase* extDb)
{
    app->debug(1, QString("Query: %1").arg(str));
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


QString DBFactory::getDictionariesProperties(QString tName, QString nameInForm)
{
    return getDictionariesProperties(tName).value(nameInForm).toString();
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
        app->showError(QString("Список полей таблицы %1 пустой. Возможно, нет разрешения доступа к таблице.").arg(tableName));
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


void DBFactory::addColumnProperties(QList<FieldType>* columnsProperties, QString table, QString name, QString type, int length, int precision, bool read, bool constRead, int number, int level)
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
    fld.level = level;
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
    return tables.contains(tName);
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
    return execSystem(command, "справочники");
}


bool DBFactory::renameTableColumn(QString table, QString oldColumnName, QString newColumnName)
{
    clearError();
    execSystem(QString("ALTER TABLE %1 RENAME COLUMN %2 TO %3;").arg(table).arg(oldColumnName).arg(newColumnName), table);
    QSqlQuery dict = execQuery(QString("SELECT %1 FROM %2 WHERE %3 = '" + table + "';").arg(getObjectNameCom("справочники.код"))
                                                                                       .arg(getObjectNameCom("справочники"))
                                                                                       .arg(getObjectNameCom("справочники.имя")));
    dict.first();
    if (dict.isValid())
    {
        return execSystem(QString("UPDATE %1 SET %2 = '%3' WHERE \"%4\" = %5 AND %2 = '%3';").arg(getObjectNameCom("столбцы"))
                                                                                   .arg(getObjectNameCom("столбцы.имя"))
                                                                                   .arg(newColumnName)
                                                                                   .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
                                                                                   .arg(dict.value(0).toInt())
                                                                                   .arg(oldColumnName), "столбцы");
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


QVariant DBFactory::getTopersProperties(int operNumber, QString columnName)
{
    return getValue(QString("SELECT %1 FROM %2 WHERE %3 = %4;").arg(getObjectNameCom(columnName))
                                                                .arg(getObjectNameCom("доступ_к_топер"))
                                                                .arg(getObjectNameCom("топер.опер"))
                                                                .arg(operNumber));
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
    return execSystem(QString("DELETE FROM %1 WHERE %2=%3 AND %4>=%5;").arg(getObjectNameCom("топер"))
                                                             .arg(getObjectNameCom("топер.опер"))
                                                             .arg(operNumber)
                                                             .arg(getObjectNameCom("топер.номер"))
                                                             .arg(operNumber1),
                                                             "топер");
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
            app->showError(errorText);
            return false;
        }
    beginTransaction();
    execSystem(QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("столбцы"))
                                                .arg(getObjectNameCom("столбцы.код_vw_справочники_со_столбцами"))
                                                .arg(getDictionaryId(QString("Документ%1").arg(operNumber))),
                                                "столбцы");
    execSystem(QString("DELETE FROM %1 WHERE %2 = %3;").arg(getObjectNameCom("топер"))
                                                 .arg(getObjectNameCom("топер.опер"))
                                                 .arg(operNumber),
                                                 "топер");
    execSystem(QString("DELETE FROM %1 WHERE %2 = '%3';").arg(getObjectNameCom("файлы"))
                                                   .arg(getObjectNameCom("файлы.имя"))
                                                   .arg(app->getScriptFileName(operNumber)),
                                                    "файлы");
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
    return execSystem(command, "топер");
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
        int number = 1;
        for (columnsHeaders.first(); columnsHeaders.isValid(); columnsHeaders.next())
        {
            if (columnsHeaders.record().value(getObjectName("vw_столбцы.базсправочник")).toString().trimmed().toLower() == tableName.toLower())
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
                        number++;
                        field.headerExist = true;   // Для столбца найден заголовок
                        field.readOnly = columnsHeaders.record().value(getObjectName("vw_столбцы.толькочтение")).toBool();
                        fields->removeAt(i);
                        fields->insert(i, field);
                        break;
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
    return execSystem(command, "столбцы");
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
    return execSystem(command, "столбцы");
}


void DBFactory::insertSaldo(QString acc, int id)
{
    QString command = QString("SELECT %1 FROM %2 WHERE %3 = '%4' AND %5 = %6;").arg(getObjectNameCom("сальдо.САЛЬДО"))
                                                                              .arg(getObjectNameCom("сальдо"))
                                                                              .arg(getObjectNameCom("сальдо.СЧЕТ"))
                                                                              .arg(acc)
                                                                              .arg(getObjectNameCom("сальдо.КОД"))
                                                                              .arg(id);
    QSqlQuery query = execQuery(command);
    if (!query.first())
    {
        command = QString("INSERT INTO %1 (%2, %3) VALUES ('%4', %5);").arg(getObjectNameCom("сальдо"))
                                                                       .arg(getObjectNameCom("сальдо.СЧЕТ"))
                                                                       .arg(getObjectNameCom("сальдо.КОД"))
                                                                       .arg(acc)
                                                                       .arg(id);
        exec(command);
    }
}


bool DBFactory::removeDictValue(QString tableName, int id)
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
    QString command = QString("SELECT sp_InsertDoc(%1,'%2');").arg(operNumber).arg(date.toString(app->dateFormat()));
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


void DBFactory::saveDocAttribute(int operNumber, int docId, QString attributes)
{
    clearError();
    QString command = QString("UPDATE %1%2 SET %3 WHERE %4=%5 AND %6=(SELECT max(%6) FROM %1%2 WHERE %4=%5);").arg(getObjectName("атрибуты"))
                                                                                                                 .arg(operNumber)
                                                                                                                 .arg(attributes)
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
                                                                 .arg(app->getLogin());
    exec(command);
}


bool DBFactory::getPeriod(QDate& begDate, QDate& endDate)
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
            begDate = query.record().field(0).value().toDate();
            endDate = query.record().field(1).value().toDate();
            result = true;
        }
    }
    return result;
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
    for (int i = 0;; i++)
    {
        QString fileName(QString("initdb%1%2.sql").arg(ext).arg(i));
        if (QFileInfo(QCoreApplication::applicationDirPath() + "/" + fileName).exists())
        {
            result.append(fileName);
        }
        else
            break;
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


QByteArray DBFactory::getFile(QString file, int type, bool extend)
{
    QString fileName = file.replace(app->applicationDirPath(), "~");
    if (extend && extDbExist)
    {   // Если будем смотреть файлы в расширенной базе данных
        QString text = QString("SELECT encode(%1, 'hex') FROM %2 WHERE %3 = '%4' AND %5 = %6;").arg(getObjectNameCom("файлы.значение"))
                                                                              .arg(getObjectNameCom("файлы"))
                                                                              .arg(getObjectNameCom("файлы.имя"))
                                                                              .arg(fileName)
                                                                              .arg(getObjectNameCom("файлы.тип"))
                                                                              .arg(type);
        app->setWriteDebug(false);         // Не будем записывать в журнал команды чтения файла, чтобы уменьшить разрастание журнала
        QSqlQuery query = execQuery(text, true, dbExtend);
        app->setWriteDebug(true);
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
            app->setWriteDebug(false);         // Не будем записывать в журнал команды чтения файла, чтобы уменьшить разрастание журнала
            QSqlQuery query = execQuery(text);
            app->setWriteDebug(true);
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


void DBFactory::copyFile(QString fileFrom, QString fileTo, bool extend)
{
    QString text;
    text = QString("INSERT INTO %1 (%2, %3, %4, %5) SELECT '%6', %3, %4, %5 FROM %1 WHERE %2 = '%7';").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(getObjectNameCom("файлы.значение"))
                                                                                  .arg(getObjectNameCom("файлы.контрсумма"))
                                                                                  .arg(fileTo)
                                                                                  .arg(fileFrom);
    exec(text, true, (extend && extDbExist) ? dbExtend : db);
}


qulonglong DBFactory::getFileCheckSum(QString file, FileType type, bool extend)
{
    QString fileName = file.replace(app->applicationDirPath(), "~");
    QString text = QString("SELECT %6 FROM %1 WHERE %2 = '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                           .arg(getObjectNameCom("файлы.имя"))
                                                                           .arg(fileName)
                                                                           .arg(getObjectNameCom("файлы.тип"))
                                                                           .arg(type)
                                                                           .arg(getObjectNameCom("файлы.контрсумма"));
    app->setWriteDebug(false);         // Не будем записывать в журнал команды проверки контрольной суммы, чтобы уменьшить разрастание журнала
    QSqlQuery query = execQuery(text, true, (extend && extDbExist) ? dbExtend : db);
    app->setWriteDebug(true);
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


FileInfo DBFactory::getFileInfo(QString file, FileType type, bool extend)
{
    FileInfo result;
    QString fileName = file.replace(app->applicationDirPath(), "~");
    QString text = QString("SELECT %6, %7 FROM %1 WHERE %2 = '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                          .arg(getObjectNameCom("файлы.имя"))
                                                                          .arg(fileName)
                                                                          .arg(getObjectNameCom("файлы.тип"))
                                                                          .arg(type)
                                                                          .arg(getObjectNameCom("файлы.датавремя"))
                                                                          .arg(getObjectNameCom("файлы.контрсумма"));
    QSqlQuery query = execQuery(text, true, (extend && extDbExist) ? dbExtend : db);
    query.first();
    if (query.isValid())
    {
        result.lastModified = query.record().value(0).toDateTime();
        result.size = query.record().value(1).toLongLong();
    }
    return result;
}



QStringList DBFactory::getFilesList(QString fileName, FileType type, bool extend)
{
    QStringList filesList;
    if (extend && extDbExist)
    {
        QString text;
        if (app->isSA() || type != ReportTemplateFileType)
            text = QString("SELECT * FROM %1 WHERE %2 ILIKE '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
                                                                                  .arg(getObjectNameCom("файлы.имя"))
                                                                                  .arg(fileName + ".%")
                                                                                  .arg(getObjectNameCom("файлы.тип"))
                                                                                  .arg(type);
        else
            text = QString("SELECT s.* FROM %1 s INNER JOIN доступ_к_отчетам_на_печать d ON s.ИМЯ = d.ИМЯ WHERE s.%2 ILIKE '%3' AND %4 = %5;").arg(getObjectNameCom("файлы"))
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


QString DBFactory::storageEncoding()
{
    QString result("UTF-8");
#if defined(Q_OS_WIN)
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
            if (!accFounded && toperT.crAcc.size() > 0)
                app->showError(QString(QObject::trUtf8("Не найден счет %1 в справочнике счетов").arg(toperT.crAcc)));

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
            if (!accFounded && toperT.dbAcc.size() > 0)
                app->showError(QString(QObject::trUtf8("Не найден счет %1 в справочнике счетов").arg(toperT.dbAcc)));

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
        return execSystem(QString("UPDATE %1 SET %2 = %3 WHERE %4 = %5 AND (%6 = 0 OR %6 = 1);").arg(getObjectNameCom("топер"))
                                                                              .arg(getObjectNameCom("топер.однаоперация"))
                                                                              .arg(singleString ? "true" : "false")
                                                                              .arg(getObjectNameCom("топер.опер"))
                                                                              .arg(operNumber)
                                                                              .arg(getObjectNameCom("топер.номер")),
                                                                              "топер");
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
        return execSystem(QString("UPDATE %1 SET %2 = '%3' WHERE %4 = %5 AND (%6 = 0 OR %6 = 1);").arg(getObjectNameCom("топер"))
                                                                                .arg(getObjectNameCom("топер.нумератор"))
                                                                                .arg(numerator.trimmed())
                                                                                .arg(getObjectNameCom("топер.опер"))
                                                                                .arg(operNumber)
                                                                                .arg(getObjectNameCom("топер.номер")),
                                                                                 "топер");
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
        execSystem(command, "доступ");
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
        execSystem(command, "доступ");
    }

}


void DBFactory::setConfig(QString config, QString name, QString value)
{
    clearError();
    app->setWriteDebug(false);         // Не будем записывать в журнал команды, чтобы уменьшить разрастание журнала
    QString command;
    command = QString("SELECT COUNT(*) FROM configs WHERE \"group\" = '%1' AND name = '%2';").arg(config).arg(name);

    QSqlQuery query = execQuery(command);
    query.first();
    if (query.value(0).toInt() > 0)     // Если уже есть запись о конфигурации
    {
        command = QString("UPDATE configs SET value = '%1' WHERE \"group\" = '%2' AND name = '%3';").arg(value).arg(config).arg(name);
        execSystem(command, "configs");
    }
    else
    {
        command = QString("INSERT INTO configs (\"group\", name, value) VALUES ('%1', '%2', '%3');").arg(config).arg(name).arg(value);
        execSystem(command, "configs");
    }
    app->setWriteDebug(true);
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
        if (value.table == updateValues.at(i).table &&
            value.recId == updateValues.at(i).recId &&
            value.field == updateValues.at(i).field &&
            value.value == updateValues.at(i).value)
        {
            return;
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


void DBFactory::prepareCommands()
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
                    command.append(QString("\"%1\"=%2").arg(updateValues.at(i).field).arg(updateValues.at(i).value));
                }
            }
            if (table.size() > 0)
            {
                command = QString("UPDATE %1 SET %2 WHERE %3=%4;").arg(table).arg(command).arg(getObjectNameCom(table + ".код")).arg(id.id);
                if (!commands.contains(command))
                {
                    commands.append(command);     // Добавим команду к списку готовых команд
                    if (sysTables.contains(table))
                        saveUpdate(command);
                }
            }
        }
    }

    updateValues.clear();
}


bool DBFactory::execCommands()
{
    prepareCommands();
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


QStringList DBFactory::getCommands()
{
    return commands;
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


QSqlRecord DBFactory::getRecord(QString command, int row)
{
    QSqlRecord result;
    QSqlQuery data = execQuery(command);
    if (data.seek(row))
    {
        result = data.record();
    }
    return result;
}


void DBFactory::saveUpdate(QString value)
{
    if (app->isSA() && app->getConfigValue("SAVE_DB_UPDATES_TO_LOCAL").toBool())
    {
        QString templateString = app->applicationDirPath().append("/updates_db/").append(dbName).append("/%1.sql");
        QString fileName;
        if (updateNum == 0)
        {
            updateNum = getValue("SELECT \"ЗНАЧЕНИЕ\" FROM константы WHERE \"ИМЯ\" = 'Last_DB_Update';").toInt();
            // Найдем не занятый номер обновления
            do
            {
                updateNum++;
                fileName = QString(templateString).arg(updateNum);
            } while (QFileInfo(fileName).exists());
            exec(QString("UPDATE константы SET \"ЗНАЧЕНИЕ\" = '%1' WHERE \"ИМЯ\" = 'Last_DB_Update';").arg(updateNum));
        }
        else
            fileName = QString(templateString).arg(updateNum);
        // Сохраним обновление
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Append))
        {
            QTextStream out(&file);
            out << value << "\n";
        }
        file.close();
    }
}


void DBFactory::loadUpdates()
{
    QString templateString = app->applicationDirPath().append("/updates_db/").append(dbName).append("/");
    int updateNum = getValue("SELECT \"ЗНАЧЕНИЕ\" FROM константы WHERE \"ИМЯ\" = 'Last_DB_Update';").toInt();
    do
    {
        updateNum++;
        QString fileName = QString("%1.sql").arg(updateNum);
        QString fullFileName = templateString;
        fullFileName.append(fileName);

        QString reportStr = QString(QObject::trUtf8("Загрузка обновления %1 на сервер...")).arg(fileName);
        if (QDir().exists(fullFileName))
        {
            if (execQueryFile(fullFileName))
                app->print(reportStr + "Ok");
            else
                app->print(reportStr + "Ошибка!");
        }
        else
            break;
        dbUpdatesList.removeOne(fileName);
    } while (!dbUpdatesList.empty());
    app->print("");
    exec(QString("UPDATE константы SET \"ЗНАЧЕНИЕ\" = '%1' WHERE \"ИМЯ\" = 'Last_DB_Update';").arg(updateNum));
}


int DBFactory::updatesCount()
{
    QString tableName = getObjectNameCom("константы");
    QString templateString = app->applicationDirPath().append("/updates_db/").append(dbName).append("/");
    dbUpdatesList = QDir(templateString).entryList(QStringList() << "*.sql", QDir::Files);
    if (isTableExists(tableName))
    {
        int updateNum = getValue("SELECT \"ЗНАЧЕНИЕ\" FROM константы WHERE \"ИМЯ\" = 'Last_DB_Update';").toInt();
        // Удалим предыдущие скрипты из списка
        for (int i = 1; i <= updateNum; i++)
        {
            QString fileName = QString("%1.sql").arg(i);
            if (dbUpdatesList.contains(fileName))
            {
                int index = -1;
                do
                {
                    // Удалим файл вида 1-*.sql
                    QString expr = QString("^").append(QString("%1").arg(i)).append("\\D+\\d*\\.sql");
                    index = dbUpdatesList.indexOf(QRegExp(expr));
                    if (index >= 0)
                        dbUpdatesList.removeAt(index);
                    // Удалим файл вида 1.sql
                    index = dbUpdatesList.indexOf(fileName);
                    if (index >= 0)
                        dbUpdatesList.removeAt(index);
                } while (index >= 0);
            }
        }
    }
    return dbUpdatesList.count();
}


QVariant DBFactory::getAccountsValue(QString cAcc, QString columnName)
{
    QVariant result;
    accounts.first();
    while (accounts.isValid())
    {
        if (accounts.record().value(getObjectName("vw_счета.счет")).toString().trimmed().toLower() == cAcc)
        {
            result = accounts.record().value(columnName);
            break;
        }
        accounts.next();
    }
    return result;
}


void DBFactory::changePassword(QString password)
{
    app->setWriteDebug(false);         // Не будем записывать в журнал команду смены пароля
    exec(QString("ALTER USER %1 WITH PASSWORD '%2';").arg(currentLogin).arg(password));
    app->setWriteDebug(true);
}


int DBFactory::getErrorNumber()
{
    return errorNumber;
}


void DBFactory::clearUpdateNum()
{
    updateNum = 0;
}


int DBFactory::getSecDiff()
{
    return secDiff;
}


QString DBFactory::getDictPrototype(QString dictName)
{
    return dictsPrototypes[dictName];
}
