#include "qtscriptshell_QRunnable.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QRunnable::QtScriptShell_QRunnable()
    : QRunnable() {}

QtScriptShell_QRunnable::~QtScriptShell_QRunnable() {}

void QtScriptShell_QRunnable::run()
{
    QScriptValue _q_function = __qtscript_self.property("run");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("run") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QRunnable::run() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

