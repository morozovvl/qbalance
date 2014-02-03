#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>
#include <qevent.h>
#include <qpoint.h>
#include <qrect.h>
#include <qvector.h>
#include <qvector2d.h>

static const char * const qtscript_QTouchEvent_TouchPoint_function_names[] = {
    "QTouchEvent_TouchPoint"
    // static
    // prototype
    , "id"
    , "lastNormalizedPos"
    , "lastPos"
    , "lastScenePos"
    , "lastScreenPos"
    , "normalizedPos"
    , "operator_assign"
    , "pos"
    , "pressure"
    , "rawScreenPositions"
    , "rect"
    , "scenePos"
    , "sceneRect"
    , "screenPos"
    , "screenRect"
    , "setId"
    , "setLastNormalizedPos"
    , "setLastPos"
    , "setLastScenePos"
    , "setLastScreenPos"
    , "setNormalizedPos"
    , "setPos"
    , "setPressure"
    , "setRawScreenPositions"
    , "setRect"
    , "setScenePos"
    , "setSceneRect"
    , "setScreenPos"
    , "setScreenRect"
    , "setStartNormalizedPos"
    , "setStartPos"
    , "setStartScenePos"
    , "setStartScreenPos"
    , "setState"
    , "setVelocity"
    , "startNormalizedPos"
    , "startPos"
    , "startScenePos"
    , "startScreenPos"
    , "state"
    , "swap"
    , "velocity"
    , "toString"
};

static const char * const qtscript_QTouchEvent_TouchPoint_function_signatures[] = {
    "QTouchEvent_TouchPoint other\nint id"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTouchEvent_TouchPoint other"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int id"
    , "QPointF lastNormalizedPos"
    , "QPointF lastPos"
    , "QPointF lastScenePos"
    , "QPointF lastScreenPos"
    , "QPointF normalizedPos"
    , "QPointF pos"
    , "qreal pressure"
    , "List positions"
    , "QRectF rect"
    , "QPointF scenePos"
    , "QRectF sceneRect"
    , "QPointF screenPos"
    , "QRectF screenRect"
    , "QPointF startNormalizedPos"
    , "QPointF startPos"
    , "QPointF startScenePos"
    , "QPointF startScreenPos"
    , "TouchPointStates state"
    , "QVector2D v"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTouchEvent_TouchPoint other"
    , ""
""
};

static const int qtscript_QTouchEvent_TouchPoint_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTouchEvent_TouchPoint_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTouchEvent_TouchPoint::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTouchEvent::TouchPoint)
Q_DECLARE_METATYPE(QTouchEvent::TouchPoint*)
Q_DECLARE_METATYPE(QTouchEvent::TouchPoint::InfoFlag)
Q_DECLARE_METATYPE(QVector<QPointF>)
Q_DECLARE_METATYPE(QFlags<Qt::TouchPointState>)
Q_DECLARE_METATYPE(Qt::TouchPointState)

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
// QTouchEvent::TouchPoint::InfoFlag
//

static const QTouchEvent::TouchPoint::InfoFlag qtscript_QTouchEvent_TouchPoint_InfoFlag_values[] = {
    QTouchEvent::TouchPoint::Pen
};

static const char * const qtscript_QTouchEvent_TouchPoint_InfoFlag_keys[] = {
    "Pen"
};

static QString qtscript_QTouchEvent_TouchPoint_InfoFlag_toStringHelper(QTouchEvent::TouchPoint::InfoFlag value)
{
    if ((value >= QTouchEvent::TouchPoint::Pen) && (value <= QTouchEvent::TouchPoint::Pen))
        return qtscript_QTouchEvent_TouchPoint_InfoFlag_keys[static_cast<int>(value)-static_cast<int>(QTouchEvent::TouchPoint::Pen)];
    return QString();
}

static QScriptValue qtscript_QTouchEvent_TouchPoint_InfoFlag_toScriptValue(QScriptEngine *engine, const QTouchEvent::TouchPoint::InfoFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTouchEvent_TouchPoint"));
    return clazz.property(qtscript_QTouchEvent_TouchPoint_InfoFlag_toStringHelper(value));
}

static void qtscript_QTouchEvent_TouchPoint_InfoFlag_fromScriptValue(const QScriptValue &value, QTouchEvent::TouchPoint::InfoFlag &out)
{
    out = qvariant_cast<QTouchEvent::TouchPoint::InfoFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QTouchEvent_TouchPoint_InfoFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTouchEvent::TouchPoint::Pen) && (arg <= QTouchEvent::TouchPoint::Pen))
        return qScriptValueFromValue(engine,  static_cast<QTouchEvent::TouchPoint::InfoFlag>(arg));
    return context->throwError(QString::fromLatin1("InfoFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTouchEvent_TouchPoint_InfoFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTouchEvent::TouchPoint::InfoFlag value = qscriptvalue_cast<QTouchEvent::TouchPoint::InfoFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTouchEvent_TouchPoint_InfoFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTouchEvent::TouchPoint::InfoFlag value = qscriptvalue_cast<QTouchEvent::TouchPoint::InfoFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QTouchEvent_TouchPoint_InfoFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QTouchEvent_TouchPoint_InfoFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTouchEvent_TouchPoint_InfoFlag,
        qtscript_QTouchEvent_TouchPoint_InfoFlag_valueOf, qtscript_QTouchEvent_TouchPoint_InfoFlag_toString);
    qScriptRegisterMetaType<QTouchEvent::TouchPoint::InfoFlag>(engine, qtscript_QTouchEvent_TouchPoint_InfoFlag_toScriptValue,
        qtscript_QTouchEvent_TouchPoint_InfoFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTouchEvent_TouchPoint_InfoFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTouchEvent_TouchPoint_InfoFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTouchEvent_TouchPoint
//

static QScriptValue qtscript_QTouchEvent_TouchPoint_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 42;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTouchEvent::TouchPoint* _q_self = qscriptvalue_cast<QTouchEvent::TouchPoint*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTouchEvent_TouchPoint.%0(): this object is not a QTouchEvent_TouchPoint")
            .arg(qtscript_QTouchEvent_TouchPoint_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->id();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->lastNormalizedPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->lastPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->lastScenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->lastScreenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->normalizedPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QTouchEvent::TouchPoint _q_arg0 = qscriptvalue_cast<QTouchEvent::TouchPoint>(context->argument(0));
        QTouchEvent::TouchPoint _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->pressure();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QVector<QPointF> _q_result = _q_self->rawScreenPositions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->rect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->scenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->sceneRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->screenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->screenRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setId(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setLastNormalizedPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setLastPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setLastScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setLastScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setNormalizedPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPressure(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QVector<QPointF> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setRawScreenPositions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->setRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->setSceneRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->setScreenRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setStartNormalizedPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setStartPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setStartScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setStartScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QFlags<Qt::TouchPointState> _q_arg0 = qscriptvalue_cast<QFlags<Qt::TouchPointState> >(context->argument(0));
        _q_self->setState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QVector2D _q_arg0 = qscriptvalue_cast<QVector2D>(context->argument(0));
        _q_self->setVelocity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->startNormalizedPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->startPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->startScenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->startScreenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 0) {
        Qt::TouchPointState _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        QTouchEvent::TouchPoint _q_arg0 = qscriptvalue_cast<QTouchEvent::TouchPoint>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QVector2D _q_result = _q_self->velocity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 42: {
    QString result = QString::fromLatin1("QTouchEvent_TouchPoint");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTouchEvent_TouchPoint_throw_ambiguity_error_helper(context,
        qtscript_QTouchEvent_TouchPoint_function_names[_id+1],
        qtscript_QTouchEvent_TouchPoint_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTouchEvent_TouchPoint_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTouchEvent_TouchPoint(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTouchEvent::TouchPoint _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTouchEvent::TouchPoint>() == context->argument(0).toVariant().userType())) {
            QTouchEvent::TouchPoint _q_arg0 = qscriptvalue_cast<QTouchEvent::TouchPoint>(context->argument(0));
            QTouchEvent::TouchPoint _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QTouchEvent::TouchPoint _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTouchEvent_TouchPoint_throw_ambiguity_error_helper(context,
        qtscript_QTouchEvent_TouchPoint_function_names[_id],
        qtscript_QTouchEvent_TouchPoint_function_signatures[_id]);
}

QScriptValue qtscript_create_QTouchEvent_TouchPoint_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent::TouchPoint*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTouchEvent::TouchPoint*)0));
    for (int i = 0; i < 43; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTouchEvent_TouchPoint_prototype_call, qtscript_QTouchEvent_TouchPoint_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTouchEvent_TouchPoint_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent::TouchPoint>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent::TouchPoint*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTouchEvent_TouchPoint_static_call, proto, qtscript_QTouchEvent_TouchPoint_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("InfoFlag"),
        qtscript_create_QTouchEvent_TouchPoint_InfoFlag_class(engine, ctor));
    return ctor;
}
