#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>
#include <qevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qtouchdevice.h>
#include <qwindow.h>

#include "qtscriptshell_QTouchEvent.h"

static const char * const qtscript_QTouchEvent_function_names[] = {
    "QTouchEvent"
    // static
    // prototype
    , "device"
    , "setDevice"
    , "setTarget"
    , "setTouchPointStates"
    , "setTouchPoints"
    , "setWindow"
    , "target"
    , "touchPointStates"
    , "touchPoints"
    , "window"
    , "toString"
};

static const char * const qtscript_QTouchEvent_function_signatures[] = {
    "Type eventType, QTouchDevice device, KeyboardModifiers modifiers, TouchPointStates touchPointStates, List touchPoints"
    // static
    // prototype
    , ""
    , "QTouchDevice adevice"
    , "QObject atarget"
    , "TouchPointStates aTouchPointStates"
    , "List atouchPoints"
    , "QWindow awindow"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTouchEvent_function_lengths[] = {
    5
    // static
    // prototype
    , 0
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
};

static QScriptValue qtscript_QTouchEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTouchEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTouchEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QTouchEvent*)
Q_DECLARE_METATYPE(QTouchDevice*)
Q_DECLARE_METATYPE(QFlags<Qt::TouchPointState>)
Q_DECLARE_METATYPE(QTouchEvent::TouchPoint)
Q_DECLARE_METATYPE(QList<QTouchEvent::TouchPoint>)
Q_DECLARE_METATYPE(QWindow*)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QInputEvent*)

//
// QTouchEvent
//

static QScriptValue qtscript_QTouchEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTouchEvent* _q_self = qscriptvalue_cast<QTouchEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTouchEvent.%0(): this object is not a QTouchEvent")
            .arg(qtscript_QTouchEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTouchDevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QTouchDevice* _q_arg0 = qscriptvalue_cast<QTouchDevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->setTarget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QFlags<Qt::TouchPointState> _q_arg0 = qscriptvalue_cast<QFlags<Qt::TouchPointState> >(context->argument(0));
        _q_self->setTouchPointStates(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QList<QTouchEvent::TouchPoint> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setTouchPoints(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QWindow* _q_arg0 = qscriptvalue_cast<QWindow*>(context->argument(0));
        _q_self->setWindow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->target();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QFlags<Qt::TouchPointState> _q_result = _q_self->touchPointStates();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QList<QTouchEvent::TouchPoint> _q_result = _q_self->touchPoints();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QWindow* _q_result = _q_self->window();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QTouchEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTouchEvent_throw_ambiguity_error_helper(context,
        qtscript_QTouchEvent_function_names[_id+1],
        qtscript_QTouchEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTouchEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTouchEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 5) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QTouchDevice* _q_arg1 = qscriptvalue_cast<QTouchDevice*>(context->argument(1));
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        QFlags<Qt::TouchPointState> _q_arg3 = qscriptvalue_cast<QFlags<Qt::TouchPointState> >(context->argument(3));
        QList<QTouchEvent::TouchPoint> _q_arg4;
        qScriptValueToSequence(context->argument(4), _q_arg4);
        QtScriptShell_QTouchEvent* _q_cpp_result = new QtScriptShell_QTouchEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTouchEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTouchEvent_throw_ambiguity_error_helper(context,
        qtscript_QTouchEvent_function_names[_id],
        qtscript_QTouchEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QTouchEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTouchEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent*>()));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTouchEvent_prototype_call, qtscript_QTouchEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTouchEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTouchEvent_static_call, proto, qtscript_QTouchEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
