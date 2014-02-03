#include "qtscriptshell_QXmlInputSource.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlInputSource::QtScriptShell_QXmlInputSource()
    : QXmlInputSource() {}

QtScriptShell_QXmlInputSource::QtScriptShell_QXmlInputSource(QIODevice*  dev)
    : QXmlInputSource(dev) {}

QtScriptShell_QXmlInputSource::~QtScriptShell_QXmlInputSource() {}

QString  QtScriptShell_QXmlInputSource::data() const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlInputSource::data();
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QXmlInputSource::fetchData()
{
    QScriptValue _q_function = __qtscript_self.property("fetchData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlInputSource::fetchData();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QString  QtScriptShell_QXmlInputSource::fromRawData(const QByteArray&  data, bool  beginning)
{
    QScriptValue _q_function = __qtscript_self.property("fromRawData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fromRawData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlInputSource::fromRawData(data, beginning);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, beginning)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QChar  QtScriptShell_QXmlInputSource::next()
{
    QScriptValue _q_function = __qtscript_self.property("next");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("next") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QXmlInputSource::next();
    } else {
        _q_function.setData(QScriptValue(true));
        QChar _q_retval = qscriptvalue_cast<QChar >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QXmlInputSource::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlInputSource::reset();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlInputSource::setData(const QByteArray&  dat)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlInputSource::setData(dat);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dat));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QXmlInputSource::setData(const QString&  dat)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QXmlInputSource::setData(dat);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dat));
        _q_function.setData(QScriptValue(false));
    }
}

