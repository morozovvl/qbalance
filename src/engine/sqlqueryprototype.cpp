#include <QScriptEngine>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QScriptClass>
#include "sqlqueryclass.h"
#include "sqlqueryprototype.h"

Q_DECLARE_METATYPE(QSqlQuery*)
Q_DECLARE_METATYPE(QSqlRecord*)

SqlQueryPrototype::SqlQueryPrototype(QObject *parent, SqlRecordClass* recordClass)
     : QObject(parent)
{
    sqlRecordClass = recordClass;
}


SqlQueryPrototype::~SqlQueryPrototype()
{
}


QSqlQuery *SqlQueryPrototype::thisSqlQuery() const
{
    return qscriptvalue_cast<QSqlQuery*>(thisObject().data());
}
