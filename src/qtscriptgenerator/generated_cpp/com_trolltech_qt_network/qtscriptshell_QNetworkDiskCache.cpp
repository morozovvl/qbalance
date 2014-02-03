#include "qtscriptshell_QNetworkDiskCache.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qnetworkdiskcache.h>
#include <qobject.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QNetworkCacheMetaData)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QNetworkDiskCache::QtScriptShell_QNetworkDiskCache(QObject*  parent)
    : QNetworkDiskCache(parent) {}

QtScriptShell_QNetworkDiskCache::~QtScriptShell_QNetworkDiskCache() {}

qint64  QtScriptShell_QNetworkDiskCache::cacheSize() const
{
    QScriptValue _q_function = __qtscript_self.property("cacheSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cacheSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::cacheSize();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QNetworkDiskCache::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkDiskCache::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QNetworkDiskCache::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkDiskCache::clear();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QNetworkDiskCache::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkDiskCache::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QIODevice*  QtScriptShell_QNetworkDiskCache::data(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::data(url);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QIODevice* _q_retval = qscriptvalue_cast<QIODevice* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QNetworkDiskCache::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::event(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QNetworkDiskCache::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::eventFilter(arg__1, arg__2);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QNetworkDiskCache::expire()
{
    QScriptValue _q_function = __qtscript_self.property("expire");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expire") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::expire();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QNetworkDiskCache::insert(QIODevice*  device)
{
    QScriptValue _q_function = __qtscript_self.property("insert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insert") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkDiskCache::insert(device);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, device));
        _q_function.setData(QScriptValue(false));
    }
}

QNetworkCacheMetaData  QtScriptShell_QNetworkDiskCache::metaData(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("metaData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metaData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::metaData(url);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QNetworkCacheMetaData _q_retval = qscriptvalue_cast<QNetworkCacheMetaData >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QIODevice*  QtScriptShell_QNetworkDiskCache::prepare(const QNetworkCacheMetaData&  metaData)
{
    QScriptValue _q_function = __qtscript_self.property("prepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("prepare") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::prepare(metaData);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QIODevice* _q_retval = qscriptvalue_cast<QIODevice* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metaData)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QNetworkDiskCache::remove(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("remove");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("remove") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkDiskCache::remove(url);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QNetworkDiskCache::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkDiskCache::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QNetworkDiskCache::updateMetaData(const QNetworkCacheMetaData&  metaData)
{
    QScriptValue _q_function = __qtscript_self.property("updateMetaData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateMetaData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkDiskCache::updateMetaData(metaData);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metaData));
        _q_function.setData(QScriptValue(false));
    }
}

