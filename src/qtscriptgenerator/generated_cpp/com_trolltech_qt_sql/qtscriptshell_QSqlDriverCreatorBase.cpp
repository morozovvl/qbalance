#include "qtscriptshell_QSqlDriverCreatorBase.h"

#include <QtScript/QScriptEngine>
#include <QSqlDriver>
#include <QVariant>
#include <qsqldriver.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QSqlDriver*)

QtScriptShell_QSqlDriverCreatorBase::QtScriptShell_QSqlDriverCreatorBase()
    : QSqlDriverCreatorBase() {}

QtScriptShell_QSqlDriverCreatorBase::~QtScriptShell_QSqlDriverCreatorBase() {}

QSqlDriver*  QtScriptShell_QSqlDriverCreatorBase::createObject() const
{
    QScriptValue _q_function = __qtscript_self.property("createObject");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createObject") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlDriverCreatorBase::createObject() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QSqlDriver* _q_retval = qscriptvalue_cast<QSqlDriver* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

