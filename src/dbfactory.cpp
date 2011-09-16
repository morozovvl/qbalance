#include <QObject>
#include <QtGui>
#include <QApplication>
#include <QTextStream>
#include <QDateTime>
#include "gui/passwordform.h"
#include "dbfactory.h"
#include "app.h"

extern bool programDebugMode;
extern QTextStream programDebugStream;
extern QString programLogTimeFormat;
extern QString programNameFieldName;


DBFactory::DBFactory()
: Custom()
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
            QString encoding = "UTF-8";
#ifdef Q_OS_WIN32
            encoding = "Windows-1251";
#endif
            if (exec(QString("CREATE DATABASE %1 WITH TEMPLATE template0 ENCODING = '%2';").arg(dbName).arg(encoding)))
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
                        proc.setProcessEnvironment(env);
                        proc.start(QString("psql -h %1 -p %2 -U postgres -f %3 %4").arg(hostName, QString::number(port), *script, dbName));

                        lResult = proc.waitForStarted();

                        if (!lResult)
                        {// выдадим сообщение об ошибке и выйдем из цикла
                            app->showError(QObject::tr("Не удалось запустить psql"));
                        }
                        else
                        {
                            lResult = proc.waitForFinished();
                            if (!lResult)
                            {
                                app->showCriticalError(QString(QObject::tr("Файл инициализации <%1> по каким то причинам не загрузился.")).arg(*script));
                            }
                        }
                    }
                    else
                        app->showCriticalError(QString(QObject::tr("Не найден файл инициализации БД <%1>.")).arg(*script));
                }
            }
       }
       else
          app->showCriticalError(QObject::tr("Не удалось создать соединение с сервером."));
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
    if (programDebugMode)
    {
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Error: " << errorText << "\n";
    }
}


bool DBFactory::doOpen()
{
    return DBFactory::doOpen("", "");
}


bool DBFactory::doOpen(QString login, QString password)
{
    clearError();
    db->setHostName(hostName);
    db->setDatabaseName(dbName);
    db->setPort(port);
    if (db->open(login, password)) {
        currentLogin = login;
        initObjectNames();              // Инициируем переводчик имен объектов из внутренних наименований в наименования БД
        return true;
    }
    else
        setError(db->lastError().text());
    return false;
}


void DBFactory::doClose()
{
    clearError();
    db->close();
    db->removeDatabase("default");
}


bool DBFactory::exec(QString str)
{
    if (programDebugMode)
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Query: " << str << "\n";
    clearError();
    QSqlQuery query;
    bool lResult = query.exec(str);
    if (!lResult)
        setError(query.lastError().text());
    return lResult;
}


QSqlQuery DBFactory::execQuery(QString str)
{
    if (programDebugMode)
    {
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Query: " << str << "\n";
    }
    clearError();
    QSqlQuery query;
    bool lResult = query.exec(str);
    if (!lResult)
    {
        setError(query.lastError().text());
    }
    return query;
}


QStringList DBFactory::getUserList()
{
    clearError();
    QStringList list;
    QSqlQuery query;
    QSqlRecord rec;
    query = execQuery("SELECT * FROM vw_пользователи ORDER BY " + programNameFieldName);
    rec = query.record();
    while (query.next())
    {
        list << query.value(rec.indexOf(programNameFieldName)).toString();
    }
    return list;
}


QSqlQuery DBFactory::getDictionariesProperties()
{
    clearError();
    return execQuery("SELECT * FROM vw_доступ_к_справочникам");
}


QStringList DBFactory::getFieldsList(QMap<int, fldType>* columnsProperties)
{
    QStringList fieldList;
    foreach (int i, columnsProperties->keys())
        fieldList << columnsProperties->value(i).name;
    return fieldList;
}


void DBFactory::getColumnsProperties(QMap<int, fldType>* result, QString table)
{
    clearError();
    QString command(QString("SELECT ordinal_position-1 AS column, column_name AS name, data_type AS type, COALESCE(character_maximum_length, 0) + COALESCE(numeric_precision, 0) AS length, COALESCE(numeric_scale, 0) AS precision, is_updatable FROM information_schema.columns WHERE table_name LIKE '%1' ORDER BY ordinal_position").arg(table.trimmed()));
    QSqlQuery query = execQuery(command);
    if (query.first())
    {
        do
        {
            if (query.isValid())
            {
                fldType fld;
                fld.name = query.value(1).toString().trimmed();
                fld.type = query.value(2).toString().trimmed();
                fld.length = query.value(3).toInt();
                fld.precision = query.value(4).toInt();
                fld.readOnly = query.value(5).toString().trimmed().toUpper() == "YES" ? false : true;
                result->insert(query.value(0).toInt(), fld);
            }
        } while (query.next());
    }
    if (QString().compare(table, "сальдо", Qt::CaseInsensitive) == 0)
        foreach (int i, result->keys())
            if ((QString(result->value(i).name).compare("конкол", Qt::CaseInsensitive) == 0) ||
                (QString(result->value(i).name).compare("концена", Qt::CaseInsensitive) == 0) ||
                (QString(result->value(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
                    addColumnProperties(result, result->value(i).name, result->value(i).type, result->value(i).length, result->value(i).precision, result->value(i).readOnly);
}


void DBFactory::addColumnProperties(QMap<int, fldType>* columnsProperties, QString name, QString type, int length, int precision, bool read)
{
    int maxKey = 0;
    if (columnsProperties->count() > 0)
    {
        foreach (int i, columnsProperties->keys())
            if (i > maxKey)
                maxKey = i;
        maxKey++;
    }
    fldType fld;
    fld.name = name;
    fld.type = type;
    fld.length = length;
    fld.precision = precision;
    fld.readOnly = read;
    columnsProperties->insert(maxKey, fld);
}


void DBFactory::getColumnsRestrictions(QString table, QMap<int, fldType>* columns)
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
                    fldType fld = columns->value(i);
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


QSqlQuery DBFactory::getTopersProperties()
{
    clearError();
    return execQuery("SELECT * FROM vw_доступ_к_топер");
}


QSqlQuery DBFactory::getToper(int oper)
{
    clearError();
    return execQuery(QString("SELECT * FROM vw_топер WHERE опер = %1 ORDER BY номер").arg(oper));
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
    return execQuery("SELECT столбец, заголовок FROM vw_столбцы WHERE справочник = '" + tableName + "' ORDER BY номер");
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
            errorText = QObject::tr("Количество полей записи не равно количеству аргументов.");
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
    exec(QString("UPDATE блокпериоды SET начало='%1', конец='%2' WHERE пользователь='%3'").arg(begDate.toString(Qt::LocaleDate)).arg(endDate.toString(Qt::LocaleDate)).arg(app->getLogin()));
}


void DBFactory::getPeriod(QDate& begDate, QDate& endDate)
{
    clearError();
    QSqlQuery query = execQuery(QString("SELECT начало, конец FROM блокпериоды WHERE пользователь='%1'").arg(app->getLogin()));
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
// Если объекты БД поменяют названия, то нужно будет поменять их здесь, либо переписать функцию
    ObjectNames.insert("проводки", "проводки");
    ObjectNames.insert("vw_топер", "vw_топер");
}


QString DBFactory::getObjectName(QString name) const
// транслирует имена объектов БД из "внутренних" в реальные наименования
{
    QMap<QString, QString>::const_iterator i = ObjectNames.find(name);
    if ( i == ObjectNames.end())
    {
        return QString();
    }
    return ObjectNames.value(i.key());
}

