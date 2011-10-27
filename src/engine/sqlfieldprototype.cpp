#include <QScriptEngine>
#include <QSqlField>
#include <QSqlRecord>
#include <QScriptClass>
#include "sqlfieldclass.h"
#include "sqlfieldprototype.h"

Q_DECLARE_METATYPE(QSqlField*)
Q_DECLARE_METATYPE(QSqlRecord*)

SqlFieldPrototype::SqlFieldPrototype(QObject *parent)
     : QObject(parent)
{
}


SqlFieldPrototype::~SqlFieldPrototype()
{
}


QSqlField *SqlFieldPrototype::thisSqlField() const
{
    return qscriptvalue_cast<QSqlField*>(thisObject().data());
}
