#include "fileinfoclass.h"

#include <QtCore/QMetaType>
#include <QtScript/QScriptClassPropertyIterator>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QDebug>
#include "fileinfoclass.h"
#include "fileinfoprototype.h"

#include <stdlib.h>

Q_DECLARE_METATYPE(QFileInfo*)
Q_DECLARE_METATYPE(FileInfoClass*)


FileInfoClass::FileInfoClass(QScriptEngine *engine)
    : QObject(engine), QScriptClass(engine)
{
    qScriptRegisterMetaType<QFileInfo>(engine, toScriptValue, fromScriptValue);

//    length = engine->toStringHandle(QLatin1String("length"));

    proto = engine->newQObject(new FileInfoPrototype(this),
                               QScriptEngine::QtOwnership,
                               QScriptEngine::SkipMethodsInEnumeration
                               | QScriptEngine::ExcludeSuperClassMethods
                               | QScriptEngine::ExcludeSuperClassProperties);
    QScriptValue global = engine->globalObject();
    proto.setPrototype(global.property("QFileInfo").property("prototype"));

    ctor = engine->newFunction(construct, proto);
    ctor.setData(engine->toScriptValue(this));
}


FileInfoClass::~FileInfoClass()
{
}

/*
QScriptClass::QueryFlags FileInfoClass::queryProperty(const QScriptValue &object,
                                                       const QScriptString &name,
                                                       QueryFlags flags, uint *id)
{
    QFileInfo *ba = qscriptvalue_cast<QFileInfo*>(object.data());
    if (!ba)
        return nullptr;
    if (name == length) {
        return flags;
    } else {
        bool isArrayIndex;
        qint32 pos = name.toArrayIndex(&isArrayIndex);
        if (!isArrayIndex)
            return nullptr;
        *id = pos;
        if ((flags & HandlesReadAccess) && (pos >= ba->size()))
            flags &= ~HandlesReadAccess;
        return flags;
    }
}


//! [4]
QScriptValue FileInfoClass::property(const QScriptValue &object,
                                      const QScriptString &name, uint id)
{
    QFileInfo *ba = qscriptvalue_cast<QFileInfo*>(object.data());
    if (!ba)
        return QScriptValue();
    if (name == length) {
        return ba->length();
    } else {
        qint32 pos = id;
        if ((pos < 0) || (pos >= ba->size()))
            return QScriptValue();
        return uint(ba->at(pos)) & 255;
    }
    return QScriptValue();
}
//! [4]

//! [5]
void FileInfoClass::setProperty(QScriptValue &object,
                                 const QScriptString &name,
                                 uint id, const QScriptValue &value)
{
    QFileInfo *ba = qscriptvalue_cast<QFileInfo*>(object.data());
    if (!ba)
        return;
    if (name == length) {
        resize(*ba, value.toInt32());
    } else {
        qint32 pos = id;
        if (pos < 0)
            return;
        if (ba->size() <= pos)
            resize(*ba, pos + 1);
        (*ba)[pos] = char(value.toInt32());
    }
}
//! [5]

//! [6]
QScriptValue::PropertyFlags FileInfoClass::propertyFlags(
    const QScriptValue &, const QScriptString &name, uint)
{
    if (name == length) {
        return QScriptValue::Undeletable
            | QScriptValue::SkipInEnumeration;
    }
    return QScriptValue::Undeletable;
}

*/
QString FileInfoClass::name() const
{
    return QLatin1String("QFileInfo");
}


QScriptValue FileInfoClass::prototype() const
{
    return proto;
}


QScriptValue FileInfoClass::constructor()
{
    return ctor;
}


QScriptValue FileInfoClass::newInstance()
{
    qDebug() << "Ok";
    engine()->reportAdditionalMemoryCost(sizeof(QFileInfo));
    return newInstance(QFileInfo());
}


QScriptValue FileInfoClass::newInstance(const QFileInfo &ba)
{
    QScriptValue data = engine()->newVariant(QVariant::fromValue(ba));
    return engine()->newObject(this, data);
}


QScriptValue FileInfoClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    FileInfoClass *cls = qscriptvalue_cast<FileInfoClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    QScriptValue arg = ctx->argument(0);
    if (arg.instanceOf(ctx->callee()))
        return cls->newInstance(qscriptvalue_cast<QFileInfo>(arg));
    return cls->newInstance();
}


QScriptValue FileInfoClass::toScriptValue(QScriptEngine *eng, const QFileInfo &ba)
{
    QScriptValue ctor = eng->globalObject().property("QFileInfo");
    FileInfoClass *cls = qscriptvalue_cast<FileInfoClass*>(ctor.data());
    if (!cls)
        return eng->newVariant(QVariant::fromValue(ba));
    return cls->newInstance(ba);
}


void FileInfoClass::fromScriptValue(const QScriptValue &obj, QFileInfo &ba)
{
    ba = qvariant_cast<QFileInfo>(obj.data().toVariant());
}

