#include "qtscriptshell_QParallelAnimationGroup.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractanimation.h>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qparallelanimationgroup.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QAbstractAnimation::Direction)
Q_DECLARE_METATYPE(QAbstractAnimation::State)

QtScriptShell_QParallelAnimationGroup::QtScriptShell_QParallelAnimationGroup(QObject*  parent)
    : QParallelAnimationGroup(parent) {}

QtScriptShell_QParallelAnimationGroup::~QtScriptShell_QParallelAnimationGroup() {}

void QtScriptShell_QParallelAnimationGroup::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QParallelAnimationGroup::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QParallelAnimationGroup::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QParallelAnimationGroup::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QParallelAnimationGroup::duration() const
{
    QScriptValue _q_function = __qtscript_self.property("_qs_duration");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("_qs_duration") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QParallelAnimationGroup::duration();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QParallelAnimationGroup::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QParallelAnimationGroup::event(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QParallelAnimationGroup::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QParallelAnimationGroup::eventFilter(arg__1, arg__2);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QParallelAnimationGroup::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QParallelAnimationGroup::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QParallelAnimationGroup::updateCurrentTime(int  currentTime)
{
    QScriptValue _q_function = __qtscript_self.property("updateCurrentTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCurrentTime") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QParallelAnimationGroup::updateCurrentTime(currentTime);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, currentTime));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QParallelAnimationGroup::updateDirection(QAbstractAnimation::Direction  direction)
{
    QScriptValue _q_function = __qtscript_self.property("updateDirection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateDirection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QParallelAnimationGroup::updateDirection(direction);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, direction));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QParallelAnimationGroup::updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState)
{
    QScriptValue _q_function = __qtscript_self.property("updateState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateState") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QParallelAnimationGroup::updateState(newState, oldState);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, newState)
            << qScriptValueFromValue(_q_engine, oldState));
        _q_function.setData(QScriptValue(false));
    }
}

