#include "qtscriptshell_QAbstractNetworkCache.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qobject.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QNetworkCacheMetaData)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QAbstractNetworkCache::QtScriptShell_QAbstractNetworkCache(QObject*  parent)
    : QAbstractNetworkCache(parent) {}

QtScriptShell_QAbstractNetworkCache::~QtScriptShell_QAbstractNetworkCache() {}

qint64  QtScriptShell_QAbstractNetworkCache::cacheSize() const
{
    QScriptValue _q_function = __qtscript_self.property("cacheSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cacheSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::cacheSize() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAbstractNetworkCache::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractNetworkCache::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAbstractNetworkCache::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::clear() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAbstractNetworkCache::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractNetworkCache::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QIODevice*  QtScriptShell_QAbstractNetworkCache::data(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::data() is abstract!");
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

bool  QtScriptShell_QAbstractNetworkCache::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractNetworkCache::event(arg__1);
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

bool  QtScriptShell_QAbstractNetworkCache::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractNetworkCache::eventFilter(arg__1, arg__2);
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

void QtScriptShell_QAbstractNetworkCache::insert(QIODevice*  device)
{
    QScriptValue _q_function = __qtscript_self.property("insert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insert") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::insert() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, device));
        _q_function.setData(QScriptValue(false));
    }
}

QNetworkCacheMetaData  QtScriptShell_QAbstractNetworkCache::metaData(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("metaData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metaData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::metaData() is abstract!");
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

QIODevice*  QtScriptShell_QAbstractNetworkCache::prepare(const QNetworkCacheMetaData&  metaData)
{
    QScriptValue _q_function = __qtscript_self.property("prepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("prepare") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::prepare() is abstract!");
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

bool  QtScriptShell_QAbstractNetworkCache::remove(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("remove");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("remove") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::remove() is abstract!");
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

void QtScriptShell_QAbstractNetworkCache::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractNetworkCache::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAbstractNetworkCache::updateMetaData(const QNetworkCacheMetaData&  metaData)
{
    QScriptValue _q_function = __qtscript_self.property("updateMetaData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateMetaData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractNetworkCache::updateMetaData() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metaData));
        _q_function.setData(QScriptValue(false));
    }
}

