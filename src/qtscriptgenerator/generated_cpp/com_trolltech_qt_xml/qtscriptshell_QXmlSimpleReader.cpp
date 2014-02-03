#include "qtscriptshell_QXmlSimpleReader.h"

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

QtScriptShell_QXmlSimpleReader::QtScriptShell_QXmlSimpleReader()
    : QXmlSimpleReader() {}

QtScriptShell_QXmlSimpleReader::~QtScriptShell_QXmlSimpleReader() {}

QXmlDTDHandler*  QtScriptShell_QXmlSimpleReader::DTDHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("DTDHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("DTDHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::DTDHandler();
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlDTDHandler* _q_retval = qscriptvalue_cast<QXmlDTDHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlContentHandler*  QtScriptShell_QXmlSimpleReader::contentHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("contentHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contentHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::contentHandler();
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlContentHandler* _q_retval = qscriptvalue_cast<QXmlContentHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlDeclHandler*  QtScriptShell_QXmlSimpleReader::declHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("declHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("declHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::declHandler();
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlDeclHandler* _q_retval = qscriptvalue_cast<QXmlDeclHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlEntityResolver*  QtScriptShell_QXmlSimpleReader::entityResolver() const
{
    QScriptValue _q_function = __qtscript_self.property("entityResolver");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("entityResolver") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::entityResolver();
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlEntityResolver* _q_retval = qscriptvalue_cast<QXmlEntityResolver* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlErrorHandler*  QtScriptShell_QXmlSimpleReader::errorHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("errorHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::errorHandler();
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlErrorHandler* _q_retval = qscriptvalue_cast<QXmlErrorHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlSimpleReader::feature(const QString&  name, bool*  ok) const
{
    QScriptValue _q_function = __qtscript_self.property("feature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("feature") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::feature(name, ok);
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

bool  QtScriptShell_QXmlSimpleReader::hasFeature(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("hasFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasFeature") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::hasFeature(name);
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

bool  QtScriptShell_QXmlSimpleReader::hasProperty(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("hasProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasProperty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::hasProperty(name);
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

QXmlLexicalHandler*  QtScriptShell_QXmlSimpleReader::lexicalHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("lexicalHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lexicalHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::lexicalHandler();
    } else {
        _q_function.setData(QScriptValue(true));
        QXmlLexicalHandler* _q_retval = qscriptvalue_cast<QXmlLexicalHandler* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlSimpleReader::parse(const QXmlInputSource&  input)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::parse(input);
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

bool  QtScriptShell_QXmlSimpleReader::parse(const QXmlInputSource*  input)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::parse(input);
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

bool  QtScriptShell_QXmlSimpleReader::parse(const QXmlInputSource*  input, bool  incremental)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::parse(input, incremental);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QXmlInputSource *>(input))
            << qScriptValueFromValue(_q_engine, incremental)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlSimpleReader::parseContinue()
{
    QScriptValue _q_function = __qtscript_self.property("parseContinue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parseContinue") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::parseContinue();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void*  QtScriptShell_QXmlSimpleReader::property(const QString&  name, bool*  ok) const
{
    QScriptValue _q_function = __qtscript_self.property("property");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("property") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlSimpleReader::property(name, ok);
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

void QtScriptShell_QXmlSimpleReader::setContentHandler(QXmlContentHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setContentHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setContentHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setContentHandler(handler);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlSimpleReader::setDTDHandler(QXmlDTDHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setDTDHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDTDHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setDTDHandler(handler);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlSimpleReader::setDeclHandler(QXmlDeclHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setDeclHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDeclHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setDeclHandler(handler);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlSimpleReader::setEntityResolver(QXmlEntityResolver*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setEntityResolver");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEntityResolver") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setEntityResolver(handler);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlSimpleReader::setErrorHandler(QXmlErrorHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setErrorHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setErrorHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setErrorHandler(handler);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlSimpleReader::setFeature(const QString&  name, bool  value)
{
    QScriptValue _q_function = __qtscript_self.property("setFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFeature") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setFeature(name, value);
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

void QtScriptShell_QXmlSimpleReader::setLexicalHandler(QXmlLexicalHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setLexicalHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLexicalHandler") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setLexicalHandler(handler);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlSimpleReader::setProperty(const QString&  name, void*  value)
{
    QScriptValue _q_function = __qtscript_self.property("setProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setProperty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlSimpleReader::setProperty(name, value);
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

