#include "qtscriptshell_QXmlDeclHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlDeclHandler::QtScriptShell_QXmlDeclHandler()
    : QXmlDeclHandler() {}

QtScriptShell_QXmlDeclHandler::~QtScriptShell_QXmlDeclHandler() {}

bool  QtScriptShell_QXmlDeclHandler::attributeDecl(const QString&  eName, const QString&  aName, const QString&  type, const QString&  valueDefault, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attributeDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributeDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDeclHandler::attributeDecl() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, eName)
            << qScriptValueFromValue(_q_engine, aName)
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, valueDefault)
            << qScriptValueFromValue(_q_engine, value)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QXmlDeclHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDeclHandler::errorString() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDeclHandler::externalEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("externalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("externalEntityDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDeclHandler::externalEntityDecl() is abstract!");
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

bool  QtScriptShell_QXmlDeclHandler::internalEntityDecl(const QString&  name, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("internalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("internalEntityDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlDeclHandler::internalEntityDecl() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

