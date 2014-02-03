#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmargins.h>
#include <QVariant>
#include <qdatastream.h>
#include <qmargins.h>

static const char * const qtscript_QMargins_function_names[] = {
    "QMargins"
    // static
    // prototype
    , "bottom"
    , "isNull"
    , "left"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "readFrom"
    , "right"
    , "setBottom"
    , "setLeft"
    , "setRight"
    , "setTop"
    , "top"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QMargins_function_signatures[] = {
    "\nint left, int top, int right, int bottom"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QMargins margins\nint arg__1"
    , "int arg__1\nqreal arg__1"
    , "QMargins m2"
    , "int arg__1\nqreal arg__1"
    , "QMargins margins\nint arg__1"
    , "QDataStream arg__1"
    , ""
    , "int bottom"
    , "int left"
    , "int right"
    , "int top"
    , ""
    , "QDataStream arg__1"
""
};

static const int qtscript_QMargins_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QMargins_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMargins::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMargins)
Q_DECLARE_METATYPE(QMargins*)
Q_DECLARE_METATYPE(QDataStream*)

//
// QMargins
//

static QScriptValue qtscript_QMargins_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 16;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMargins* _q_self = qscriptvalue_cast<QMargins*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMargins.%0(): this object is not a QMargins")
            .arg(qtscript_QMargins_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->bottom();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->left();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMargins>() == context->argument(0).toVariant().userType())) {
            QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
            QMargins _q_result = _q_self->operator+=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QMargins _q_result = _q_self->operator+=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QMargins _q_result = _q_self->operator/=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            QMargins _q_result = _q_self->operator/=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QMargins _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            QMargins _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMargins>() == context->argument(0).toVariant().userType())) {
            QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
            QMargins _q_result = _q_self->operator-=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QMargins _q_result = _q_self->operator-=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->right();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setBottom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTop(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->top();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 16: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMargins_throw_ambiguity_error_helper(context,
        qtscript_QMargins_function_names[_id+1],
        qtscript_QMargins_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMargins_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMargins(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QMargins _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QMargins _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMargins_throw_ambiguity_error_helper(context,
        qtscript_QMargins_function_names[_id],
        qtscript_QMargins_function_signatures[_id]);
}

QScriptValue qtscript_create_QMargins_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMargins*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMargins*)0));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMargins_prototype_call, qtscript_QMargins_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMargins_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMargins>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QMargins*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMargins_static_call, proto, qtscript_QMargins_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
