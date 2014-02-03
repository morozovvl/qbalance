#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qiconengine.h>
#include <QVariant>
#include <qiconengine.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>

#include "qtscriptshell_QIconEngine.h"

static const char * const qtscript_QIconEngine_function_names[] = {
    "QIconEngine"
    // static
    // prototype
    , "actualSize"
    , "addFile"
    , "addPixmap"
    , "availableSizes"
    , "clone"
    , "iconName"
    , "key"
    , "paint"
    , "pixmap"
    , "toString"
};

static const char * const qtscript_QIconEngine_function_signatures[] = {
    ""
    // static
    // prototype
    , "QSize size, Mode mode, State state"
    , "String fileName, QSize size, Mode mode, State state"
    , "QPixmap pixmap, Mode mode, State state"
    , "Mode mode, State state"
    , ""
    , ""
    , ""
    , "QPainter painter, QRect rect, Mode mode, State state"
    , "QSize size, Mode mode, State state"
""
};

static const int qtscript_QIconEngine_function_lengths[] = {
    0
    // static
    // prototype
    , 3
    , 4
    , 3
    , 2
    , 0
    , 0
    , 0
    , 4
    , 3
    , 0
};

static QScriptValue qtscript_QIconEngine_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QIconEngine::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QIconEngine*)
Q_DECLARE_METATYPE(QtScriptShell_QIconEngine*)
Q_DECLARE_METATYPE(QIconEngine::IconEngineHook)
Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QIcon::State)
Q_DECLARE_METATYPE(QList<QSize>)
Q_DECLARE_METATYPE(QPainter*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QIconEngine::IconEngineHook
//

static const QIconEngine::IconEngineHook qtscript_QIconEngine_IconEngineHook_values[] = {
    QIconEngine::AvailableSizesHook
    , QIconEngine::IconNameHook
};

static const char * const qtscript_QIconEngine_IconEngineHook_keys[] = {
    "AvailableSizesHook"
    , "IconNameHook"
};

static QString qtscript_QIconEngine_IconEngineHook_toStringHelper(QIconEngine::IconEngineHook value)
{
    if ((value >= QIconEngine::AvailableSizesHook) && (value <= QIconEngine::IconNameHook))
        return qtscript_QIconEngine_IconEngineHook_keys[static_cast<int>(value)-static_cast<int>(QIconEngine::AvailableSizesHook)];
    return QString();
}

static QScriptValue qtscript_QIconEngine_IconEngineHook_toScriptValue(QScriptEngine *engine, const QIconEngine::IconEngineHook &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QIconEngine"));
    return clazz.property(qtscript_QIconEngine_IconEngineHook_toStringHelper(value));
}

static void qtscript_QIconEngine_IconEngineHook_fromScriptValue(const QScriptValue &value, QIconEngine::IconEngineHook &out)
{
    out = qvariant_cast<QIconEngine::IconEngineHook>(value.toVariant());
}

static QScriptValue qtscript_construct_QIconEngine_IconEngineHook(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QIconEngine::AvailableSizesHook) && (arg <= QIconEngine::IconNameHook))
        return qScriptValueFromValue(engine,  static_cast<QIconEngine::IconEngineHook>(arg));
    return context->throwError(QString::fromLatin1("IconEngineHook(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QIconEngine_IconEngineHook_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QIconEngine::IconEngineHook value = qscriptvalue_cast<QIconEngine::IconEngineHook>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QIconEngine_IconEngineHook_toString(QScriptContext *context, QScriptEngine *engine)
{
    QIconEngine::IconEngineHook value = qscriptvalue_cast<QIconEngine::IconEngineHook>(context->thisObject());
    return QScriptValue(engine, qtscript_QIconEngine_IconEngineHook_toStringHelper(value));
}

static QScriptValue qtscript_create_QIconEngine_IconEngineHook_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QIconEngine_IconEngineHook,
        qtscript_QIconEngine_IconEngineHook_valueOf, qtscript_QIconEngine_IconEngineHook_toString);
    qScriptRegisterMetaType<QIconEngine::IconEngineHook>(engine, qtscript_QIconEngine_IconEngineHook_toScriptValue,
        qtscript_QIconEngine_IconEngineHook_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QIconEngine_IconEngineHook_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QIconEngine_IconEngineHook_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QIconEngine
//

static QScriptValue qtscript_QIconEngine_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QIconEngine* _q_self = qscriptvalue_cast<QIconEngine*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QIconEngine.%0(): this object is not a QIconEngine")
            .arg(qtscript_QIconEngine_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
        QSize _q_result = _q_self->actualSize(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        QIcon::Mode _q_arg2 = qscriptvalue_cast<QIcon::Mode>(context->argument(2));
        QIcon::State _q_arg3 = qscriptvalue_cast<QIcon::State>(context->argument(3));
        _q_self->addFile(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
        _q_self->addPixmap(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QSize> _q_result = _q_self->availableSizes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QIcon::Mode _q_arg0 = qscriptvalue_cast<QIcon::Mode>(context->argument(0));
        QList<QSize> _q_result = _q_self->availableSizes(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIcon::Mode _q_arg0 = qscriptvalue_cast<QIcon::Mode>(context->argument(0));
        QIcon::State _q_arg1 = qscriptvalue_cast<QIcon::State>(context->argument(1));
        QList<QSize> _q_result = _q_self->availableSizes(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QIconEngine* _q_result = _q_self->clone();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->iconName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->key();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QIcon::Mode _q_arg2 = qscriptvalue_cast<QIcon::Mode>(context->argument(2));
        QIcon::State _q_arg3 = qscriptvalue_cast<QIcon::State>(context->argument(3));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 3) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
        QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QIconEngine");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIconEngine_throw_ambiguity_error_helper(context,
        qtscript_QIconEngine_function_names[_id+1],
        qtscript_QIconEngine_function_signatures[_id+1]);
}

static QScriptValue qtscript_QIconEngine_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QIconEngine(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QIconEngine* _q_cpp_result = new QtScriptShell_QIconEngine();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QIconEngine*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIconEngine_throw_ambiguity_error_helper(context,
        qtscript_QIconEngine_function_names[_id],
        qtscript_QIconEngine_function_signatures[_id]);
}

QScriptValue qtscript_create_QIconEngine_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QIconEngine*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QIconEngine*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QIconEngine_prototype_call, qtscript_QIconEngine_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QIconEngine_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QIconEngine*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QIconEngine_static_call, proto, qtscript_QIconEngine_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("IconEngineHook"),
        qtscript_create_QIconEngine_IconEngineHook_class(engine, ctor));
    return ctor;
}
