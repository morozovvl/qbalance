#include "qtscriptshell_QXmlEntityResolver.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlInputSource*)

QtScriptShell_QXmlEntityResolver::QtScriptShell_QXmlEntityResolver()
    : QXmlEntityResolver() {}

QtScriptShell_QXmlEntityResolver::~QtScriptShell_QXmlEntityResolver() {}

QString  QtScriptShell_QXmlEntityResolver::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlEntityResolver::errorString() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlEntityResolver::resolveEntity(const QString&  publicId, const QString&  systemId, QXmlInputSource*&  ret)
{
    QScriptValue _q_function = __qtscript_self.property("resolveEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlEntityResolver::resolveEntity() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)
            << qScriptValueFromValue(_q_engine, ret)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

