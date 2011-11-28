#include <QObject>
#include <QTextStream>
#include <QDateTime>
#include <QMap>
#include "dbfactory.h"
#include "../kernel/app.h"
#include "../gui/passwordform.h"

DBFactory::DBFactory()
: QObject()
{
    hostName = "localhost";
    port = 5432;
    dbName = "enterprise";
    clearError();
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
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
            //Drake
            //Базу данных следует всегда создавать в UTF-8
            //т.к. есть возможность возвращать данные на клиент в нужной кодировке
            if (exec(QString("CREATE DATABASE %1 WITH TEMPLATE template0 ENCODING = '%2';").arg(dbName, DBFactory::storageEncoding())))
            {
                close();
                const QStringList scripts = initializationScriptList();
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
                    else
                        TApplication::exemplar()->showCriticalError(QString(QObject::trUtf8("Не найден файл инициализации БД <%1>.")).arg(*script));
                }
            }
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
    errorText = "";
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
//  Владимир.
//  У меня этот вариант не работает ...
//    db->setConnectOptions("client_encoding=" + TApplication::encoding());
//    if (db->open(login, password)) {
//  поэтому пришлось сделать так:
    if (db->open(login, password)) {
        exec(QString("set client_encoding='%1';").arg(TApplication::encoding()));
        currentLogin = login;
        initObjectNames();// Инициируем переводчик имен объектов из внутренних наименований в наименования БД
        objectTypes = execQuery(QString("SELECT * FROM %1").arg(getObjectName("типыобъектов")));
        return true;
    }
    else
        setError(db->lastError().text());
    return false;
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
    static const QString clause = QString("SELECT %1 FROM vw_пользователи ORDER BY %1").arg(TApplication::nameFieldName());
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
    return execQuery("SELECT * FROM vw_доступ_к_справочникам");
}


QSqlRecord DBFactory::getDictionariesProperties(QString tableName/* = ""*/)
{
    QSqlRecord result;
    clearError();
    QSqlQuery query = execQuery(QString("SELECT * FROM vw_доступ_к_справочникам WHERE таблица = '%1'").arg(tableName));
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


void DBFactory::getColumnsProperties(QMap<int, FieldType>* result, QString table)
{
    clearError();
    QString command(QString("SELECT s.*, COALESCE(c.заголовок, '') AS header, COALESCE(c.номер, 0) AS number " \
                            "FROM (SELECT ordinal_position-1 AS column, column_name AS name, data_type AS type, COALESCE(character_maximum_length, 0) + COALESCE(numeric_precision, 0) AS length, COALESCE(numeric_scale, 0) AS precision, is_updatable " \
                                   "FROM information_schema.columns " \
                                   "WHERE table_name LIKE '%1') s " \
                                   "LEFT OUTER JOIN " \
                                   "(SELECT столбцы.имя, столбцы.заголовок, столбцы.номер "\
                                    "FROM столбцы " \
                                    "INNER JOIN справочники " \
                                    "ON столбцы.код_vw_справочники_со_столбцами = справочники.код " \
                                    "WHERE справочники.имя = '%1' " \
                                    ") c ON s.name = c.имя " \
                                    "ORDER BY s.column;").arg(table.trimmed()));
    QSqlQuery query = execQuery(command);
    int i = 0;
    for (query.first(); query.isValid(); query.next())
    {
        FieldType fld;
        fld.name      = query.value(1).toString().trimmed();
        fld.type      = query.value(2).toString().trimmed();
        fld.length    = query.value(3).toInt();
        fld.precision = query.value(4).toInt();
        fld.readOnly  = query.value(5).toString().trimmed().toUpper() == "YES" ? false : true;
        fld.header    = query.value(6).toString().trimmed();
        fld.number    = query.value(7).toInt();
        result->insert(i, fld);
        i++;
    }
    if (QString::compare(table, "сальдо", Qt::CaseInsensitive) == 0)
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
    getColumnsProperties(&fields, table);
    foreach (FieldType fld, fields.values())
    {
        result->append(fld);
    }
}


void DBFactory::addColumnProperties(QMap<int, FieldType>* columnsProperties, QString name, QString type, int length, int precision, bool read)
{
    int maxKey = 0;
    if (columnsProperties->count() > 0)
    {
        foreach (int i, columnsProperties->keys())
            if (i > maxKey)
                maxKey = i;
        maxKey++;
    }
    FieldType fld;
    fld.name = name;
    fld.type = type;
    fld.length = length;
    fld.precision = precision;
    fld.readOnly = read;
    columnsProperties->insert(maxKey, fld);
}


void DBFactory::getColumnsRestrictions(QString table, QMap<int, FieldType>* columns)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT имя, доступ FROM доступ WHERE код_типыобъектов=5 AND (пользователь ILIKE '\%'||\"current_user\"()::text||'%' OR пользователь ILIKE '\%*\%') AND имя ILIKE '%1.\%'").arg(table.trimmed()));
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


int DBFactory::getDictionaryTypeId()
{
    QString dict = getObjectName("типыобъектов.справочник").toLower();
    while (objectTypes.next()) {
        if (objectTypes.value(1).toString().toLower() == dict)
        {
            return objectTypes.value(0).toInt();
        }
    }
    return 0;
}


int DBFactory::getDictionaryId(QString dictName)
{
    clearError();
    QSqlQuery query = execQuery("SELECT код FROM справочники WHERE имя = '" + dictName + "';");
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
                                  .arg(TApplication::idFieldName())
                                  .arg(TApplication::nameFieldName())
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
                        .arg(getDictionaryTypeId())
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
                        .arg(getDictionaryTypeId())
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
    return exec(QString("UPDATE справочники SET имя_в_списке = '%1', имя_в_форме = '%2' WHERE имя = '%3'").arg(menuName).arg(formName).arg(tableName));
}


bool DBFactory::renameTableColumn(QString table, QString oldColumnName, QString newColumnName)
{
    clearError();
    exec(QString("ALTER TABLE %1 RENAME COLUMN %2 TO %3;").arg(table).arg(oldColumnName).arg(newColumnName));
    QSqlQuery dict = execQuery("SELECT код FROM справочники WHERE имя = '" + table + "';");
    dict.first();
    if (dict.isValid())
    {
        return exec(QString("UPDATE столбцы SET имя = '%1' WHERE код_vw_справочники_со_столбцами = %2 AND имя = '%3';").arg(newColumnName).arg(dict.value(0).toInt()).arg(oldColumnName));
    }
    return false;
}


bool DBFactory::setTableColumnHeaderOrder(int tableId, QString columnName, int order)
{
    clearError();
    return exec(QString("UPDATE столбцы SET номер = %1 WHERE код_vw_справочники_со_столбцами = %2 AND имя = '%3';").arg(order).arg(tableId).arg(columnName));
}


bool DBFactory::alterTableColumn(QString table, QString columnName, QString type)
{
    clearError();
    return exec(QString("ALTER TABLE %1 ALTER COLUMN %2 TYPE %3;").arg(table).arg(columnName).arg(type));
}


bool DBFactory::addTableColumn(QString table, QString columnName, QString type)
{
    clearError();
    return exec(QString("ALTER TABLE %1 ADD COLUMN %2 %3;").arg(table).arg(columnName).arg(type));
}


bool DBFactory::dropTableColumn(QString table, QString columnName)
{
    clearError();
    return exec(QString("ALTER TABLE %1 DROP COLUMN %2;").arg(table).arg(columnName));
}


QSqlQuery DBFactory::getTopersProperties()
{
    clearError();
    return execQuery("SELECT * FROM vw_доступ_к_топер");
}


QSqlRecord DBFactory::getTopersProperties(int operNumber)
{
    clearError();
    QSqlRecord result;
    QSqlQuery query = execQuery(QString("SELECT * FROM vw_доступ_к_топер WHERE опер = %1").arg(operNumber));
    if (query.first())
        result = query.record();
    return result;
}


QSqlQuery DBFactory::getToper(int operNumber)
{
    clearError();
    return execQuery(QString("SELECT * FROM топер WHERE опер = %1 ORDER BY номер").arg(operNumber));
}


QString DBFactory::getPhotoDatabase()
{
    clearError();
    QString result;
    QSqlQuery query = execQuery(QString("SELECT значение FROM vw_константы WHERE имя = 'база_фото'"));
    if (query.first())
        result = query.record().field(0).value().toString();
    return result;
}

QString DBFactory::getPhotoPath(QString tableName)
{
    clearError();
    QString result;
    QSqlQuery query = execQuery(QString("SELECT фото FROM справочники WHERE имя = '" + tableName + "'"));
    if (query.first())
        result = query.record().field(0).value().toString().trimmed();
    return result;
}


QSqlQuery DBFactory::getColumnsHeaders(QString tableName)
{
    clearError();
    return execQuery("SELECT столбец, заголовок FROM vw_столбцы WHERE справочник = '" + tableName + "' ORDER BY номер;");
}


bool DBFactory::appendColumnHeader(int tableId, QString column, QString header)
{
    clearError();
    return exec(QString("INSERT INTO столбцы (код_vw_справочники_со_столбцами, имя, заголовок, номер) VALUES (%1, '%2', '%3', 999);").arg(tableId).arg(column).arg(header));
}


bool DBFactory::updateColumnHeader(int tableId, QString column, QString header)
{
    clearError();
    return exec(QString("UPDATE столбцы SET заголовок = %1 WHERE код_vw_справочники_со_столбцами = %2 AND имя = '%3';").arg(header).arg(tableId).arg(column));
}


bool DBFactory::insertDictDefault(QString tableName, QStringList fields, QVariantList values)
{
    clearError();
    if (fields.size() > 0)
    {
        if (fields.size() == values.size())
        {
            int i;
            QString fieldsList;
            for (i = 0; i < fields.size(); i++)
                fieldsList.append(fields.at(i)).append(',');
            fieldsList.chop(1);
            QString valuesList;
            for (i = 0; i < values.size(); i++)
            {
                QString str = values.at(i).toString();
                if (values.at(i).type() == QVariant::String)
                {
                    str.replace("'", "''");
                    str = "'" + str + "'";
                }
                valuesList.append(str).append(',');
            }
            valuesList.chop(1);
            QString command = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName).arg(fieldsList).arg(valuesList);
            execQuery(command);
        }
        else
        {
            wasError = true;
            errorText = QObject::trUtf8("Количество полей записи не равно количеству аргументов.");
        }
    }
    else
        execQuery("INSERT INTO " + tableName + " DEFAULT VALUES");
    return !wasError;
}


bool DBFactory::removeDictValue(QString tableName, qulonglong id)
{
    clearError();
    execQuery(QString("DELETE FROM %1 WHERE код = %2").arg(tableName).arg(id));
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
    exec(QString("UPDATE блокпериоды SET начало='%1', конец='%2' WHERE пользователь='%3'").arg(
        begDate.toString(Qt::LocaleDate), endDate.toString(Qt::LocaleDate), TApplication::exemplar()->getLogin()));
}


void DBFactory::getPeriod(QDate& begDate, QDate& endDate)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT начало, конец FROM блокпериоды WHERE пользователь='%1'").arg(TApplication::exemplar()->getLogin()));
    if (query.first())
    {
        begDate = query.record().field(0).value().toDate();
        endDate = query.record().field(1).value().toDate();
    }
}


void DBFactory::setConstDictId(QString fieldName, QVariant val, int docId, int oper, int operNum)
{
    clearError();
    exec(QString("UPDATE %1 SET %2 = %3 WHERE доккод = %4 AND опер = %5 AND номеропер = %6").arg(getObjectName("проводки")).arg(fieldName).arg(val.toString()).arg(docId).arg(oper).arg(operNum));
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
// Пока заполняем таблицу "один к одному" без изменения, чтобы можно было работать с существующей БД
// Если объекты БД поменяют названия, то нужно будет поменять их здесь, либо переписать функцию, чтобы она получала соответствия из БД
    ObjectNames.insert("код_", "код_");
    ObjectNames.insert("документы", "документы");
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
    ObjectNames.insert("константы", "константы");
    ObjectNames.insert("константы.имя", "имя");
    ObjectNames.insert("константы.значение", "значение");
    ObjectNames.insert("типыобъектов", "типыобъектов");
    ObjectNames.insert("типыобъектов.имя", "имя");
    ObjectNames.insert("типыобъектов.справочник", "справочник");
    ObjectNames.insert("доступ", "доступ");
    ObjectNames.insert("доступ.меню", "меню");
    ObjectNames.insert("доступ.код_типыобъектов", "код_типыобъектов");
    ObjectNames.insert("доступ.пользователь", "пользователь");
    ObjectNames.insert("доступ.имя", "имя");
    ObjectNames.insert("справочники", "справочники");
    ObjectNames.insert("справочники.имя", "имя");
    ObjectNames.insert("справочники.имя_в_списке", "имя_в_списке");
    ObjectNames.insert("топер", "топер");
    ObjectNames.insert("топер.код", "код");
    ObjectNames.insert("топер.имя", "имя");
    ObjectNames.insert("топер.номер", "номер");
    ObjectNames.insert("топер.дбсчет", "дбсчет");
    ObjectNames.insert("топер.крсчет", "крсчет");
    ObjectNames.insert("топер.итоги", "итоги");
    ObjectNames.insert("топер.меню", "меню");
    ObjectNames.insert("топер.осндокумент", "осндокумент");
    ObjectNames.insert("топер.нумератор", "нумератор");
    ObjectNames.insert("топер.однаоперация", "однаоперация");
    ObjectNames.insert("топер.дбпост", "дбпост");
    ObjectNames.insert("топер.крпост", "крпост");
    ObjectNames.insert("счета", "счета");
    ObjectNames.insert("счета.счет", "счет");
}


QString DBFactory::getObjectName(const QString& name) const
// транслирует имена объектов БД из "внутренних" в реальные наименования
{
    QString result;
    QMap<QString, QString>::const_iterator i = ObjectNames.find(name);
    if (i != ObjectNames.end())
    {
        result = i.value();
    }
    return result;
}


QByteArray DBFactory::getFile(QString fileName, FileType type)
{
    QString text = QString("SELECT * FROM файлы WHERE имя = '%1' AND тип = %2").arg(fileName).arg(type);
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
    QString text = QString("SELECT COUNT(*) FROM файлы WHERE имя = '%1' AND тип = %2").arg(fileName).arg(type);
    QSqlQuery query = execQuery(text);
    if (query.first())
    {
        // Если в базе уже есть такой файл
        query.clear();
        text = QString("UPDATE файлы SET значение = (:value) WHERE имя = '%1' AND тип = %2;").arg(fileName).arg(type);
    }
    else
    {
        query.clear();
        text = QString("INSERT INTO файлы (имя, тип, значение) VALUES ('%1', %2, (:value));").arg(fileName).arg(type);
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
