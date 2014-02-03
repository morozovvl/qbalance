#include "qtscriptshell_QXmlStreamEntityResolver.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlStreamEntityResolver::QtScriptShell_QXmlStreamEntityResolver()
    : QXmlStreamEntityResolver() {}

QtScriptShell_QXmlStreamEntityResolver::~QtScriptShell_QXmlStreamEntityResolver() {}

QString  QtScriptShell_QXmlStreamEntityResolver::resolveEntity(const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("resolveEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlStreamEntityResolver::resolveEntity(publicId, systemId);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QXmlStreamEntityResolver::resolveUndeclaredEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("resolveUndeclaredEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveUndeclaredEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlStreamEntityResolver::resolveUndeclaredEntity(name);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

