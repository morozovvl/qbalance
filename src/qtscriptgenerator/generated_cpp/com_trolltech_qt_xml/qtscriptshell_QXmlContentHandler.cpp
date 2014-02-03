#include "qtscriptshell_QXmlContentHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlLocator*)
Q_DECLARE_METATYPE(QXmlAttributes)

QtScriptShell_QXmlContentHandler::QtScriptShell_QXmlContentHandler()
    : QXmlContentHandler() {}

QtScriptShell_QXmlContentHandler::~QtScriptShell_QXmlContentHandler() {}

bool  QtScriptShell_QXmlContentHandler::characters(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::characters() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::endDocument() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::endElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName)
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::endElement() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, namespaceURI)
            << qScriptValueFromValue(_q_engine, localName)
            << qScriptValueFromValue(_q_engine, qName)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::endPrefixMapping(const QString&  prefix)
{
    QScriptValue _q_function = __qtscript_self.property("endPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endPrefixMapping") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::endPrefixMapping() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, prefix)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QXmlContentHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::errorString() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::ignorableWhitespace(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("ignorableWhitespace");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("ignorableWhitespace") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::ignorableWhitespace() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::processingInstruction(const QString&  target, const QString&  data)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::processingInstruction() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, target)
            << qScriptValueFromValue(_q_engine, data)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QXmlContentHandler::setDocumentLocator(QXmlLocator*  locator)
{
    QScriptValue _q_function = __qtscript_self.property("setDocumentLocator");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDocumentLocator") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::setDocumentLocator() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, locator));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QXmlContentHandler::skippedEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("skippedEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("skippedEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::skippedEntity() is abstract!");
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

bool  QtScriptShell_QXmlContentHandler::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::startDocument() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::startElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName, const QXmlAttributes&  atts)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::startElement() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, namespaceURI)
            << qScriptValueFromValue(_q_engine, localName)
            << qScriptValueFromValue(_q_engine, qName)
            << qScriptValueFromValue(_q_engine, atts)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlContentHandler::startPrefixMapping(const QString&  prefix, const QString&  uri)
{
    QScriptValue _q_function = __qtscript_self.property("startPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startPrefixMapping") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QXmlContentHandler::startPrefixMapping() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, prefix)
            << qScriptValueFromValue(_q_engine, uri)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

