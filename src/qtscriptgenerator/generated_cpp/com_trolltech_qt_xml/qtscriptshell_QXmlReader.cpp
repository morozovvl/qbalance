#include "qtscriptshell_QXmlReader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlDTDHandler*)
Q_DECLARE_METATYPE(QXmlContentHandler*)
Q_DECLARE_METATYPE(QXmlDeclHandler*)
Q_DECLARE_METATYPE(QXmlEntityResolver*)
Q_DECLARE_METATYPE(QXmlErrorHandler*)
Q_DECLARE_METATYPE(QXmlLexicalHandler*)
Q_DECLARE_METATYPE(QXmlInputSource)
Q_DECLARE_METATYPE(QXmlInputSource*)

QtScriptShell_QXmlReader::QtScriptShell_QXmlReader()
    : QXmlReader() {}

QtScriptShell_QXmlReader::~QtScriptShell_QXmlReader() {}

QXmlDTDHandler*  QtScriptShell_QXmlReader::DTDHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("DTDHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("DTDHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::DTDHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlDTDHandler* _q_retval = qscriptvalue_cast<QXmlDTDHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlContentHandler*  QtScriptShell_QXmlReader::contentHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("contentHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contentHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::contentHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlContentHandler* _q_retval = qscriptvalue_cast<QXmlContentHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlDeclHandler*  QtScriptShell_QXmlReader::declHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("declHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("declHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::declHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlDeclHandler* _q_retval = qscriptvalue_cast<QXmlDeclHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlEntityResolver*  QtScriptShell_QXmlReader::entityResolver() const
{
    QScriptValue _q_function = __qtscript_self.property("entityResolver");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("entityResolver") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::entityResolver() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlEntityResolver* _q_retval = qscriptvalue_cast<QXmlEntityResolver* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlErrorHandler*  QtScriptShell_QXmlReader::errorHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("errorHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::errorHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlErrorHandler* _q_retval = qscriptvalue_cast<QXmlErrorHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlReader::feature(const QString&  name, bool*  ok) const
{
    QScriptValue _q_function = __qtscript_self.property("feature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("feature") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::feature() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlReader::hasFeature(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("hasFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasFeature") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::hasFeature() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlReader::hasProperty(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("hasProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasProperty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::hasProperty() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlLexicalHandler*  QtScriptShell_QXmlReader::lexicalHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("lexicalHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lexicalHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::lexicalHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlLexicalHandler* _q_retval = qscriptvalue_cast<QXmlLexicalHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlReader::parse(const QXmlInputSource&  input)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::parse() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, input)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlReader::parse(const QXmlInputSource*  input)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::parse() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QXmlInputSource *>(input))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void*  QtScriptShell_QXmlReader::property(const QString&  name, bool*  ok) const
{
    QScriptValue _q_function = __qtscript_self.property("property");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("property") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::property() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        void* _q_retval = qscriptvalue_cast<void* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QXmlReader::setContentHandler(QXmlContentHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setContentHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setContentHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setContentHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setDTDHandler(QXmlDTDHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setDTDHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDTDHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setDTDHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setDeclHandler(QXmlDeclHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setDeclHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDeclHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setDeclHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setEntityResolver(QXmlEntityResolver*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setEntityResolver");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEntityResolver") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setEntityResolver() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setErrorHandler(QXmlErrorHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setErrorHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setErrorHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setErrorHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setFeature(const QString&  name, bool  value)
{
    QScriptValue _q_function = __qtscript_self.property("setFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFeature") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setFeature() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setLexicalHandler(QXmlLexicalHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setLexicalHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLexicalHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setLexicalHandler() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlReader::setProperty(const QString&  name, void*  value)
{
    QScriptValue _q_function = __qtscript_self.property("setProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setProperty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlReader::setProperty() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

