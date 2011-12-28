#include <QDebug>
#include "tableclass.h"
#include "tableprototype.h"

//Q_DECLARE_METATYPE(ptrTable)
//Q_DECLARE_METATYPE(ptrTable*)
Q_DECLARE_METATYPE(Table)
Q_DECLARE_METATYPE(TableClass*)

TableClass::TableClass(QScriptEngine *eng) : QObject(eng), QScriptClass(eng) {
    qDebug() << "TableClass";
    engine = eng;
//    qScriptRegisterMetaType<Table>(engine, toScriptValue, fromScriptValue);

    tableName = engine->toStringHandle(QLatin1String("tableName"));

    proto = engine->newQObject(new Table(),
                               QScriptEngine::QtOwnership,
                               QScriptEngine::SkipMethodsInEnumeration
                               | QScriptEngine::ExcludeSuperClassMethods
                               | QScriptEngine::ExcludeSuperClassProperties);
    QScriptValue global = engine->globalObject();
    proto.setPrototype(global.property("Object").property("prototype"));

    ctor = engine->newFunction(construct, proto);
    ctor.setData(qScriptValueFromValue(engine, this));
}

TableClass::~TableClass() {
    qDebug() << "~TableClass";
    table->close();
}

QScriptClass::QueryFlags TableClass::queryProperty(const QScriptValue &object, const QScriptString &name, QueryFlags flags, uint *id) {
    qDebug() << "queryProperty";
     Table* t = qscriptvalue_cast<Table*>(object.data());
     if (!t)
         return 0;
     if (name == tableName) {
         return flags;
     }
     return 0;
 }


QScriptValue TableClass::property(const QScriptValue &object, const QScriptString &name, uint) {
    qDebug() << "property";
    Table *p = qscriptvalue_cast<Table*>(object.data());
    if (!p)
        return QScriptValue();
    else {
        if (name == tableName)
            return QScriptValue(engine, p->getTableName());
    }
    return QScriptValue();
}

void TableClass::setProperty(QScriptValue &object, const QScriptString &, uint, const QScriptValue &) {
    qDebug() << "setProperty";
    Table *p = qscriptvalue_cast<Table*>(object.data());
}

QString TableClass::name() const {
    qDebug() << "name";
    return QLatin1String("Table");
}

QScriptValue TableClass::prototype() const {
    qDebug() << "prototype";
    return proto;
}

QScriptValue TableClass::constructor() {
    qDebug() << "constructor";
    return ctor;
}

QScriptValue TableClass::newInstance(QScriptContext* ctx) {
    qDebug() << "newInstance";
//    QScriptValue data = engine()->newVariant(qVariantFromValue(p));
    qDebug() << ctx->argument(0).toString();
    table = new Table(ctx->argument(0).toString());
    if (table->open())
        qDebug() << table->getFieldsList();
    QScriptValue data = engine->newQObject(table);
    return data;
}

QScriptValue TableClass::construct(QScriptContext *ctx, QScriptEngine *) {
    qDebug() << "construct";
    TableClass *cls = qscriptvalue_cast<TableClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    QScriptValue inst = cls->newInstance(ctx);
    if (inst.isNull())
        qDebug() << "is null";
    return inst;
}

/*
QScriptValue TableClass::toScriptValue(QScriptEngine *eng, const Table &p) {
    qDebug() << "toScriptValue";
    QScriptValue ctor = eng->globalObject().property("Table");
    TableClass *cls = qscriptvalue_cast<TableClass*>(ctor.data());
    if (!cls)
        return eng->newVariant(qVariantFromValue(p));
//    return cls->newInstance(p);
}

void TableClass::fromScriptValue(const QScriptValue &obj, Table &p) {
    qDebug() << "fromScriptValue";
    p = qvariant_cast<Table>(obj.data().toVariant());
}
*/
