#include <QScriptEngine>
#include "sqlqueryclass.h"
#include "sqlqueryprototype.h"


Q_DECLARE_METATYPE(QSqlQuery)
Q_DECLARE_METATYPE(QSqlQuery*)
Q_DECLARE_METATYPE(SqlQueryClass*)


SqlQueryClass::SqlQueryClass(QScriptEngine* engine, SqlRecordClass* recordClass)
     : QObject(engine), QScriptClass(engine)
{
    proto = engine->newQObject(new SqlQueryPrototype(this, recordClass), QScriptEngine::ScriptOwnership);
    proto.setPrototype(engine->globalObject().property("Object").property("prototype"));
    ctor = engine->newFunction(construct, proto);
    ctor.setData(qScriptValueFromValue(engine, this));
}

SqlQueryClass::~SqlQueryClass()
{
}

QScriptValue SqlQueryClass::prototype() const
{
    return proto;
}

QScriptValue SqlQueryClass::constructor()
{
    return ctor;
}

QScriptValue SqlQueryClass::newInstance(const QString s)
{
    return newInstance(QSqlQuery(s));
}

QScriptValue SqlQueryClass::newInstance(const QSqlQuery &q)
{
    QScriptValue data = engine()->newVariant(qVariantFromValue(q));
    return engine()->newObject(this, data);
}

QScriptValue SqlQueryClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    SqlQueryClass *cls = qscriptvalue_cast<SqlQueryClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    QScriptValue arg = ctx->argument(0);
    if (arg.instanceOf(ctx->callee()))
        return cls->newInstance(qscriptvalue_cast<QSqlQuery>(arg.toString()));
    return cls->newInstance(arg.toString());
 }

