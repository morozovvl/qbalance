#include <QDebug>
#include <QScriptEngine>
#include <QSqlRecord>
#include "sqlrecordclass.h"
#include "sqlrecordprototype.h"

Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlRecord*)
Q_DECLARE_METATYPE(SqlRecordClass*)


SqlRecordClass::SqlRecordClass(QScriptEngine *engine, SqlFieldClass* fieldClass)
     : QObject(engine), QScriptClass(engine)
{
    proto = engine->newQObject(new SqlRecordPrototype(this, fieldClass), QScriptEngine::ScriptOwnership);
    proto.setPrototype(engine->globalObject().property("Object").property("prototype"));
    ctor = engine->newFunction(construct, proto);
    ctor.setData(qScriptValueFromValue(engine, this));
}

SqlRecordClass::~SqlRecordClass()
{
}

QScriptValue SqlRecordClass::prototype() const
{
    return proto;
}

QScriptValue SqlRecordClass::constructor()
{
    return ctor;
}

QScriptValue SqlRecordClass::newInstance()
{
   return newInstance(QSqlRecord());
}

QScriptValue SqlRecordClass::newInstance(const QSqlRecord &q)
{
    QScriptValue data = engine()->newVariant(qVariantFromValue(q));
    return engine()->newObject(this, data);
}

QScriptValue SqlRecordClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    SqlRecordClass *cls = qscriptvalue_cast<SqlRecordClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    return cls->newInstance();
 }

