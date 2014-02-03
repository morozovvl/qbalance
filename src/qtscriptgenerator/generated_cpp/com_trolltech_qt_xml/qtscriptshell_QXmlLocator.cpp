#include "qtscriptshell_QXmlLocator.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlLocator::QtScriptShell_QXmlLocator()
    : QXmlLocator() {}

QtScriptShell_QXmlLocator::~QtScriptShell_QXmlLocator() {}

int  QtScriptShell_QXmlLocator::columnNumber() const
{
    QScriptValue _q_function = __qtscript_self.property("columnNumber");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnNumber") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlLocator::columnNumber() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QXmlLocator::lineNumber() const
{
    QScriptValue _q_function = __qtscript_self.property("lineNumber");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lineNumber") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlLocator::lineNumber() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

