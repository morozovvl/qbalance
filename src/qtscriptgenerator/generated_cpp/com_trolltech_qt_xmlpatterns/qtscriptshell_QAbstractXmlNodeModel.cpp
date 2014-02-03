#include "qtscriptshell_QAbstractXmlNodeModel.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qsourcelocation.h>
#include <qurl.h>
#include <qvector.h>
#include <qxmlname.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlNodeModelIndex)
Q_DECLARE_METATYPE(QVector<QXmlNodeModelIndex>)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::DocumentOrder)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::NodeKind)
Q_DECLARE_METATYPE(QVector<QXmlName>)
Q_DECLARE_METATYPE(QAbstractXmlNodeModel::SimpleAxis)

QtScriptShell_QAbstractXmlNodeModel::~QtScriptShell_QAbstractXmlNodeModel() {}

QVector<QXmlNodeModelIndex >  QtScriptShell_QAbstractXmlNodeModel::attributes(const QXmlNodeModelIndex&  element) const
{
    QScriptValue _q_function = __qtscript_self.property("attributes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::attributes() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVector<QXmlNodeModelIndex > _q_retval = qscriptvalue_cast<QVector<QXmlNodeModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QUrl  QtScriptShell_QAbstractXmlNodeModel::baseUri(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("baseUri");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("baseUri") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::baseUri() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QUrl _q_retval = qscriptvalue_cast<QUrl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlNodeModelIndex::DocumentOrder  QtScriptShell_QAbstractXmlNodeModel::compareOrder(const QXmlNodeModelIndex&  ni1, const QXmlNodeModelIndex&  ni2) const
{
    QScriptValue _q_function = __qtscript_self.property("compareOrder");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("compareOrder") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::compareOrder() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QXmlNodeModelIndex::DocumentOrder _q_retval = qscriptvalue_cast<QXmlNodeModelIndex::DocumentOrder >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni1)
            << qScriptValueFromValue(_q_engine, ni2)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QUrl  QtScriptShell_QAbstractXmlNodeModel::documentUri(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("documentUri");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("documentUri") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::documentUri() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QUrl _q_retval = qscriptvalue_cast<QUrl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlNodeModelIndex  QtScriptShell_QAbstractXmlNodeModel::elementById(const QXmlName&  NCName) const
{
    QScriptValue _q_function = __qtscript_self.property("elementById");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("elementById") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::elementById() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QXmlNodeModelIndex _q_retval = qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, NCName)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlNodeModelIndex::NodeKind  QtScriptShell_QAbstractXmlNodeModel::kind(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("kind");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("kind") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::kind() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QXmlNodeModelIndex::NodeKind _q_retval = qscriptvalue_cast<QXmlNodeModelIndex::NodeKind >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlName  QtScriptShell_QAbstractXmlNodeModel::name(const QXmlNodeModelIndex&  ni) const
{
    QScriptValue _q_function = __qtscript_self.property("name");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("name") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::name() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QXmlName _q_retval = qscriptvalue_cast<QXmlName >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ni)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVector<QXmlName >  QtScriptShell_QAbstractXmlNodeModel::namespaceBindings(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("namespaceBindings");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("namespaceBindings") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::namespaceBindings() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVector<QXmlName > _q_retval = qscriptvalue_cast<QVector<QXmlName > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlNodeModelIndex  QtScriptShell_QAbstractXmlNodeModel::nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis  axis, const QXmlNodeModelIndex&  origin) const
{
    QScriptValue _q_function = __qtscript_self.property("nextFromSimpleAxis");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextFromSimpleAxis") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::nextFromSimpleAxis() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QXmlNodeModelIndex _q_retval = qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, axis)
            << qScriptValueFromValue(_q_engine, origin)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVector<QXmlNodeModelIndex >  QtScriptShell_QAbstractXmlNodeModel::nodesByIdref(const QXmlName&  NCName) const
{
    QScriptValue _q_function = __qtscript_self.property("nodesByIdref");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nodesByIdref") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::nodesByIdref() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVector<QXmlNodeModelIndex > _q_retval = qscriptvalue_cast<QVector<QXmlNodeModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, NCName)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QXmlNodeModelIndex  QtScriptShell_QAbstractXmlNodeModel::root(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("root");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("root") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::root() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QXmlNodeModelIndex _q_retval = qscriptvalue_cast<QXmlNodeModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QAbstractXmlNodeModel::stringValue(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("stringValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("stringValue") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::stringValue() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QAbstractXmlNodeModel::typedValue(const QXmlNodeModelIndex&  n) const
{
    QScriptValue _q_function = __qtscript_self.property("typedValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("typedValue") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractXmlNodeModel::typedValue() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, n)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

