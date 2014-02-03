#include "qtscriptshell_QXmlDTDHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlDTDHandler::QtScriptShell_QXmlDTDHandler()
    : QXmlDTDHandler() {}

QtScriptShell_QXmlDTDHandler::~QtScriptShell_QXmlDTDHandler() {}

QString  QtScriptShell_QXmlDTDHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDTDHandler::errorString() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDTDHandler::notationDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("notationDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notationDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDTDHandler::notationDecl() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDTDHandler::unparsedEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId, const QString&  notationName)
{
    QScriptValue _q_function = __qtscript_self.property("unparsedEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unparsedEntityDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDTDHandler::unparsedEntityDecl() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)
            << qScriptValueFromValue(_q_engine, notationName)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

