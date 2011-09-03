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

DBFactory::DBFactory() : Custom() {
    cHostName = "localhost";
    port = 5432;
    cDbName = "enterprise";
    clearError();
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
}

bool DBFactory::createNewDB(QString hostName, QString dbName, int port) {
    bool lResult = false;
    QString defaultDatabase = getDatabaseName();
    setHostName(hostName);
    setDatabaseName("postgres");
    setPort(port);
    PassWordForm frm;
    frm.addLogin("postgres");
    if (frm.exec()) {
        QString login = frm.getLogin();
        QString password = frm.getPassword();
        if (open(login, password)) {
            QString initScriptFileName = QFileDialog::getOpenFileName(0, tr("Выберите файл инициализации"), "", "SQL (*.sql)");
            if (initScriptFileName.size() > 0) {
#ifdef Q_OS_WIN32
                QString encoding = "WIN1251";
#else
                QString encoding = "UTF-8";
#endif
                if (exec(QString("CREATE DATABASE %1 WITH TEMPLATE template0 ENCODING = '%2';").arg(dbName).arg(encoding))) {
                    close();
                    QProcess* proc = new QProcess();
                    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                    env.insert("PGPASSWORD", password);
                    proc->setProcessEnvironment(env);
                    proc->start("psql", QStringList() << "-h" << hostName << "-p" << QString(port) << "-U" << "postgres" << "-f" << initScriptFileName << dbName);
                    if (!proc->waitForStarted())
                        app->showError(QObject::tr("Не удалось запустить psql"));                   // выдадим сообщение об ошибке
                    else
                        if (proc->waitForFinished())
                            lResult = true;
                }
                else
                    app->showError(getErrorText());
            }
       }
       else
          app->showCriticalError(QObject::tr("Не удалось создать соединение с сервером."));
    }
    setDatabaseName(defaultDatabase);
    return lResult;
}

void DBFactory::clearError() {
    wasError = false;
    errorText = "";
}

void DBFactory::setError(QString errText) {
    wasError = true;
    errorText = errText;
    if (programDebugMode) {
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Error: " << errorText << "\n";
    }
}

bool DBFactory::doOpen() {
    return DBFactory::doOpen("", "");
}

bool DBFactory::doOpen(QString login, QString password) {
    clearError();
    db->setHostName(cHostName);
    db->setDatabaseName(cDbName);
    db->setPort(port);
    if (db->open(login, password)) {
        currentLogin = login;
        return true;
    }
    else
        setError(db->lastError().text());
    return false;
}

void DBFactory::doClose() {
    clearError();
    db->removeDatabase("default");
    db->close();
    delete db;
}

bool DBFactory::exec(QString str) {
    if (programDebugMode)
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Query: " << str << "\n";
    clearError();
    QSqlQuery query;
    bool lResult = query.exec(str);
    if (!lResult)
        setError(query.lastError().text());
    return lResult;
}

QSqlQuery DBFactory::execQuery(QString str) {
    if (programDebugMode) {
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Query: " << str << "\n";
    }
    clearError();
    QSqlQuery query;
    bool lResult = query.exec(str);
    if (!lResult) {
        setError(query.lastError().text());
    }
    return query;
}

QStringList DBFactory::getUserList() {
    clearError();
    QStringList list;
    QSqlQuery query;
    QSqlRecord rec;
    query = execQuery("SELECT * FROM vw_пользователи ORDER BY " + programNameFieldName);
    rec = query.record();
    while (query.next()) {
        list << query.value(rec.indexOf(programNameFieldName)).toString();
        }
    return list;
}

QSqlQuery DBFactory::getDictionariesProperties() {
    clearError();
    return execQuery("SELECT * FROM vw_доступ_к_справочникам");
}

QStringList DBFactory::getFieldsList(QMap<int, fldType>* columnsProperties) {
    QStringList fieldList;
    foreach (int i, columnsProperties->keys())
        fieldList << columnsProperties->value(i).name;
    return fieldList;
}

void DBFactory::getColumnsProperties(QMap<int, fldType>* result, QString table) {
    clearError();
    QString command(QString("SELECT ordinal_position-1 AS column, column_name AS name, data_type AS type, COALESCE(character_maximum_length, 0) + COALESCE(numeric_precision, 0) AS length, COALESCE(numeric_scale, 0) AS precision, is_updatable FROM information_schema.columns WHERE table_name LIKE '%1' ORDER BY ordinal_position").arg(table.trimmed()));
    QSqlQuery query = execQuery(command);
    if (query.first()) {
        do {
            if (query.isValid()) {
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
    if (QString().compare(table, "сальдо", Qt::CaseInsensitive) == 0) {
        foreach (int i, result->keys()) {
            if ((QString(result->value(i).name).compare("конкол", Qt::CaseInsensitive) == 0) ||
                (QString(result->value(i).name).compare("концена", Qt::CaseInsensitive) == 0) ||
                (QString(result->value(i).name).compare("консальдо", Qt::CaseInsensitive) == 0)) {
                addColumnProperties(result, result->value(i).name, result->value(i).type, result->value(i).length, result->value(i).precision, result->value(i).readOnly);
            }
        }
    }
}

void DBFactory::addColumnProperties(QMap<int, fldType>* columnsProperties, QString name, QString type, int length, int precision, bool read) {
    int maxKey = 0;
    if (columnsProperties->count() > 0) {
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

void DBFactory::getColumnsRestrictions(QString table, QMap<int, fldType>* columns) {
    clearError();
    QSqlQuery query = execQuery(QString("SELECT имя, доступ FROM доступ WHERE код_типыобъектов=5 AND (пользователь ILIKE '\%'||\"current_user\"()::text||'%' OR пользователь ILIKE '\%*\%') AND имя ILIKE '%1.\%'").arg(table.trimmed()));
    while (query.next()) {
        QString field = QString(query.value(0).toString()).remove(table.trimmed() + ".", Qt::CaseInsensitive).trimmed().toLower();
        foreach (int i, columns->keys()) {
            if (columns->value(i).name.toLower() == field) {
                if (query.value(1).toString().contains("ro", Qt::CaseInsensitive)) {
                    fldType fld = columns->value(i);
                    fld.readOnly = true;
                    columns->remove(i);
                    columns->insert(i, fld);
                    break;
                } else if (query.value(1).toString().contains("hide", Qt::CaseInsensitive)) {
                        columns->remove(i);
                        break;
                        }
            }
        }
    }
}

QSqlQuery DBFactory::getTopersProperties() {
    clearError();
    return execQuery("SELECT * FROM vw_доступ_к_топер");
}

QSqlQuery DBFactory::getToper(int oper) {
    clearError();
    return execQuery(QString("SELECT * FROM vw_топер WHERE опер = %1 ORDER BY номер").arg(oper));
}

QString DBFactory::getPhotoDatabase() {
    clearError();
    QString result;
    QSqlQuery query = execQuery(QString("SELECT значение FROM vw_константы WHERE имя = 'база_фото'"));
    if (query.first())
        result = query.record().field(0).value().toString();
    return result;
}

QString DBFactory::getPhotoPath(QString tableName) {
    clearError();
    QString result;
    QSqlQuery query = execQuery(QString("SELECT фото FROM справочники WHERE имя = '" + tableName + "'"));
    if (query.first())
        result = query.record().field(0).value().toString().trimmed();
    return result;
}

QSqlQuery DBFactory::getColumnsHeaders(QString tableName) {
    clearError();
    return execQuery("SELECT столбец, заголовок FROM vw_столбцы WHERE справочник = '" + tableName + "' ORDER BY номер");
}

bool DBFactory::insertDictDefault(QString tableName, QStringList fields, QVariantList values) {
    clearError();
    if (fields.size() > 0) {
        if (fields.size() == values.size()) {
            int i;
            QString fieldsList;
            for (i = 0; i < fields.size(); i++)
                fieldsList.append(fields.at(i)).append(',');
            fieldsList.chop(1);
            QString valuesList;
            for (i = 0; i < values.size(); i++) {
                QString str = values.at(i).toString();
                if (values.at(i).type() == QVariant::String) {
                    str.replace("'", "''");
                    str = "'" + str + "'";
                }
                valuesList.append(str).append(',');
            }
            valuesList.chop(1);
            QString command = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName).arg(fieldsList).arg(valuesList);
            execQuery(command);
        }
        else {
            wasError = true;
            errorText = QObject::tr("Количество полей записи не равно количеству аргументов.");
        }
    }
    else
        execQuery("INSERT INTO " + tableName + " DEFAULT VALUES");
    return !wasError;
}

bool DBFactory::removeDictValue(QString tableName, qulonglong id) {
    clearError();
    execQuery(QString("DELETE FROM %1 WHERE код = %2").arg(tableName).arg(id));
    return !wasError;
}

bool DBFactory::addDoc(int operNumber, QDate date) {
    clearError();
    return exec(QString("SELECT sp_InsertDoc(%1,'%2')").arg(operNumber).arg(date.toString("dd.MM.yyyy")));
}

bool DBFactory::removeDoc(int docId) {
    clearError();
    return exec(QString("SELECT sp_DeleteDoc(%1)").arg(docId));
}

bool DBFactory::addDocStr(int operNumber, int docId, QString cParam, int nQuan, int nDocStr) {
    clearError();
    return exec(QString("SELECT sp_InsertDocStr(%1,%2,'%3'::character varying,%4,%5)").arg(operNumber).arg(docId).arg(cParam).arg(nQuan).arg(nDocStr));
}

bool DBFactory::removeDocStr(int docId, int nDocStr) {
    clearError();
    return exec(QString("SELECT sp_DeleteDocStr(%1,%2)").arg(docId).arg(nDocStr));
}

void DBFactory::setPeriod(QDate begDate, QDate endDate) {
    clearError();
    exec(QString("UPDATE блокпериоды SET начало='%1', конец='%2' WHERE пользователь='%3'").arg(begDate.toString(Qt::LocaleDate)).arg(endDate.toString(Qt::LocaleDate)).arg(app->getLogin()));
}

void DBFactory::getPeriod(QDate& begDate, QDate& endDate) {
    clearError();
    QSqlQuery query = execQuery(QString("SELECT начало, конец FROM блокпериоды WHERE пользователь='%1'").arg(app->getLogin()));
    if (query.first()) {
        begDate = query.record().field(0).value().toDate();
        endDate = query.record().field(1).value().toDate();
    }
}

void DBFactory::setConstDictId(QString fieldName, QVariant val, int docId, int oper, int operNum) {
    clearError();
    exec(QString("UPDATE проводки SET %1 = %2 WHERE доккод = %3 AND опер = %4 AND номеропер = %5").arg(fieldName).arg(val.toString()).arg(docId).arg(oper).arg(operNum));
}
