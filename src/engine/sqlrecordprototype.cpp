#include <QDebug>
#include <QScriptEngine>
#include <QSqlRecord>
#include "sqlrecordprototype.h"

Q_DECLARE_METATYPE(QSqlRecord*)
Q_DECLARE_METATYPE(QSqlField)


SqlRecordPrototype::SqlRecordPrototype(QObject *parent, SqlFieldClass* fieldClass)
     : QObject(parent)
{
    sqlFieldClass = fieldClass;
}

SqlRecordPrototype::~SqlRecordPrototype()
{
}


QSqlRecord *SqlRecordPrototype::thisSqlRecord() const
{
    return qscriptvalue_cast<QSqlRecord*>(thisObject().data());
}


void SqlRecordPrototype::append(QScriptValue field)
{
    if (field.isObject() && sqlFieldClass->name().compare(field.scriptClass()->name(), Qt::CaseSensitive) == 0)
    {
        QSqlField sqlField = qscriptvalue_cast<QSqlField>(field.data());
        thisSqlRecord()->append(sqlField);
    }
}


void SqlRecordPrototype::insert(int pos, QScriptValue field)
{
    if (field.isObject() && sqlFieldClass->name().compare(field.scriptClass()->name(), Qt::CaseSensitive) == 0)
    {
        QSqlField sqlField = qscriptvalue_cast<QSqlField>(field.data());
        thisSqlRecord()->insert(pos, sqlField);
    }

}


void SqlRecordPrototype::replace(int pos, QScriptValue field)
{
    if (field.isObject() && sqlFieldClass->name().compare(field.scriptClass()->name(), Qt::CaseSensitive) == 0)
    {
        QSqlField sqlField = qscriptvalue_cast<QSqlField>(field.data());
        thisSqlRecord()->replace(pos, sqlField);
    }
}

