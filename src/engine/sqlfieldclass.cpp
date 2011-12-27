#include <QScriptEngine>
#include "sqlfieldclass.h"
#include "sqlfieldprototype.h"


Q_DECLARE_METATYPE(QSqlField)
Q_DECLARE_METATYPE(QSqlField*)
Q_DECLARE_METATYPE(SqlFieldClass*)


SqlFieldClass::SqlFieldClass(QScriptEngine* engine)
     : QObject(engine), QScriptClass(engine)
{
    proto = engine->newQObject(new SqlFieldPrototype(this), QScriptEngine::ScriptOwnership);
    proto.setPrototype(engine->globalObject().property("Object").property("prototype"));
    ctor = engine->newFunction(construct, proto);
    ctor.setData(qScriptValueFromValue(engine, this));
}

SqlFieldClass::~SqlFieldClass()
{
}

QScriptValue SqlFieldClass::prototype() const
{
    return proto;
}

QScriptValue SqlFieldClass::constructor()
{
    return ctor;
}

QScriptValue SqlFieldClass::newInstance(const QString &fieldName, QVariant::Type type)
{
    return newInstance(QSqlField(fieldName, type));
}

QScriptValue SqlFieldClass::newInstance(const QSqlField &q)
{
    QScriptValue data = engine()->newVariant(qVariantFromValue(q));
    return engine()->newObject(this, data);
}

QScriptValue SqlFieldClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    SqlFieldClass *cls = qscriptvalue_cast<SqlFieldClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    QScriptValue arg = ctx->argument(0);
    if (arg.instanceOf(ctx->callee()))
        return cls->newInstance(qscriptvalue_cast<QSqlField>(arg.toString()));
    return cls->newInstance(arg.toString());
 }

