#include "qtscriptshell_QXmlDefaultHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlParseException)
Q_DECLARE_METATYPE(QXmlInputSource*)
Q_DECLARE_METATYPE(QXmlLocator*)
Q_DECLARE_METATYPE(QXmlAttributes)

QtScriptShell_QXmlDefaultHandler::QtScriptShell_QXmlDefaultHandler()
    : QXmlDefaultHandler() {}

QtScriptShell_QXmlDefaultHandler::~QtScriptShell_QXmlDefaultHandler() {}

bool  QtScriptShell_QXmlDefaultHandler::attributeDecl(const QString&  eName, const QString&  aName, const QString&  type, const QString&  valueDefault, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attributeDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributeDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::attributeDecl(eName, aName, type, valueDefault, value);
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

bool  QtScriptShell_QXmlDefaultHandler::characters(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::characters(ch);
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

bool  QtScriptShell_QXmlDefaultHandler::comment(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("comment");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("comment") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::comment(ch);
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

bool  QtScriptShell_QXmlDefaultHandler::endCDATA()
{
    QScriptValue _q_function = __qtscript_self.property("endCDATA");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endCDATA") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::endCDATA();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endDTD()
{
    QScriptValue _q_function = __qtscript_self.property("endDTD");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDTD") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::endDTD();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::endDocument();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName)
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::endElement(namespaceURI, localName, qName);
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

bool  QtScriptShell_QXmlDefaultHandler::endEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("endEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::endEntity(name);
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

bool  QtScriptShell_QXmlDefaultHandler::endPrefixMapping(const QString&  prefix)
{
    QScriptValue _q_function = __qtscript_self.property("endPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endPrefixMapping") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::endPrefixMapping(prefix);
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

bool  QtScriptShell_QXmlDefaultHandler::error(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("error");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("error") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::error(exception);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QXmlDefaultHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::errorString();
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::externalEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("externalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("externalEntityDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::externalEntityDecl(name, publicId, systemId);
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

bool  QtScriptShell_QXmlDefaultHandler::fatalError(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("fatalError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fatalError") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::fatalError(exception);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::ignorableWhitespace(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("ignorableWhitespace");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("ignorableWhitespace") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::ignorableWhitespace(ch);
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

bool  QtScriptShell_QXmlDefaultHandler::internalEntityDecl(const QString&  name, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("internalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("internalEntityDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::internalEntityDecl(name, value);
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

bool  QtScriptShell_QXmlDefaultHandler::notationDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("notationDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notationDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::notationDecl(name, publicId, systemId);
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

bool  QtScriptShell_QXmlDefaultHandler::processingInstruction(const QString&  target, const QString&  data)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::processingInstruction(target, data);
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

bool  QtScriptShell_QXmlDefaultHandler::resolveEntity(const QString&  publicId, const QString&  systemId, QXmlInputSource*&  ret)
{
    QScriptValue _q_function = __qtscript_self.property("resolveEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::resolveEntity(publicId, systemId, ret);
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

void QtScriptShell_QXmlDefaultHandler::setDocumentLocator(QXmlLocator*  locator)
{
    QScriptValue _q_function = __qtscript_self.property("setDocumentLocator");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDocumentLocator") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlDefaultHandler::setDocumentLocator(locator);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, locator));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::skippedEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("skippedEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("skippedEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::skippedEntity(name);
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

bool  QtScriptShell_QXmlDefaultHandler::startCDATA()
{
    QScriptValue _q_function = __qtscript_self.property("startCDATA");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startCDATA") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::startCDATA();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startDTD(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("startDTD");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDTD") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::startDTD(name, publicId, systemId);
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

bool  QtScriptShell_QXmlDefaultHandler::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::startDocument();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName, const QXmlAttributes&  atts)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::startElement(namespaceURI, localName, qName, atts);
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

bool  QtScriptShell_QXmlDefaultHandler::startEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("startEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startEntity") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::startEntity(name);
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

bool  QtScriptShell_QXmlDefaultHandler::startPrefixMapping(const QString&  prefix, const QString&  uri)
{
    QScriptValue _q_function = __qtscript_self.property("startPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startPrefixMapping") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::startPrefixMapping(prefix, uri);
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

bool  QtScriptShell_QXmlDefaultHandler::unparsedEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId, const QString&  notationName)
{
    QScriptValue _q_function = __qtscript_self.property("unparsedEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unparsedEntityDecl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::unparsedEntityDecl(name, publicId, systemId, notationName);
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

bool  QtScriptShell_QXmlDefaultHandler::warning(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("warning");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("warning") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlDefaultHandler::warning(exception);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

