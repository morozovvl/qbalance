#include "sqlqueryprototype.h"
#include <QScriptEngine>
#include <QSqlQuery>

Q_DECLARE_METATYPE(QSqlQuery*)

SqlQueryPrototype::SqlQueryPrototype(QObject *parent)
     : QObject(parent)
{
}

SqlQueryPrototype::~SqlQueryPrototype()
{
}

QSqlQuery *SqlQueryPrototype::thisSqlQuery() const
{
    return qscriptvalue_cast<QSqlQuery*>(thisObject().data());
}
