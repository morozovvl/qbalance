#include "qtscriptshell_QAccessibleBridge.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessibleEvent*)
Q_DECLARE_METATYPE(QAccessibleInterface*)

QtScriptShell_QAccessibleBridge::QtScriptShell_QAccessibleBridge()
    : QAccessibleBridge() {}

QtScriptShell_QAccessibleBridge::~QtScriptShell_QAccessibleBridge() {}

void QtScriptShell_QAccessibleBridge::notifyAccessibilityUpdate(QAccessibleEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("notifyAccessibilityUpdate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notifyAccessibilityUpdate") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleBridge::notifyAccessibilityUpdate() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAccessibleBridge::setRootObject(QAccessibleInterface*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setRootObject");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRootObject") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleBridge::setRootObject() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

