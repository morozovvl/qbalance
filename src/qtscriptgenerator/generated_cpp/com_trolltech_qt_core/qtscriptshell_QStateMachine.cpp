#include "qtscriptshell_QStateMachine.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractanimation.h>
#include <qabstractstate.h>
#include <qabstracttransition.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsignaltransition.h>
#include <qstate.h>
#include <qstatemachine.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QStateMachine::QtScriptShell_QStateMachine(QObject*  parent)
    : QStateMachine(parent) {}

QtScriptShell_QStateMachine::QtScriptShell_QStateMachine(QState::ChildMode  childMode, QObject*  parent)
    : QStateMachine(childMode, parent) {}

QtScriptShell_QStateMachine::~QtScriptShell_QStateMachine() {}

void QtScriptShell_QStateMachine::beginMicrostep(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("beginMicrostep");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("beginMicrostep") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::beginMicrostep(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::beginSelectTransitions(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("beginSelectTransitions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("beginSelectTransitions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::beginSelectTransitions(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::endMicrostep(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("endMicrostep");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endMicrostep") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::endMicrostep(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::endSelectTransitions(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("endSelectTransitions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endSelectTransitions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::endSelectTransitions(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QStateMachine::event(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QStateMachine::event(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QStateMachine::eventFilter(QObject*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QStateMachine::eventFilter(watched, event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QStateMachine::onEntry(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("onEntry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("onEntry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::onEntry(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::onExit(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("onExit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("onExit") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::onExit(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QStateMachine::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStateMachine::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

