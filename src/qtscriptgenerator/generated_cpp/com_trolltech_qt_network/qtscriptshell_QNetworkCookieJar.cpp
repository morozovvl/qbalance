#include "qtscriptshell_QNetworkCookieJar.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qnetworkcookie.h>
#include <qnetworkcookiejar.h>
#include <qobject.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QList<QNetworkCookie>)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QNetworkCookieJar::QtScriptShell_QNetworkCookieJar(QObject*  parent)
    : QNetworkCookieJar(parent) {}

QtScriptShell_QNetworkCookieJar::~QtScriptShell_QNetworkCookieJar() {}

void QtScriptShell_QNetworkCookieJar::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkCookieJar::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QList<QNetworkCookie >  QtScriptShell_QNetworkCookieJar::cookiesForUrl(const QUrl&  url) const
{
    QScriptValue _q_function = __qtscript_self.property("cookiesForUrl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cookiesForUrl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::cookiesForUrl(url);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QList<QNetworkCookie > _q_retval = qscriptvalue_cast<QList<QNetworkCookie > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QNetworkCookieJar::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkCookieJar::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QNetworkCookieJar::deleteCookie(const QNetworkCookie&  cookie)
{
    QScriptValue _q_function = __qtscript_self.property("deleteCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("deleteCookie") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::deleteCookie(cookie);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QNetworkCookieJar::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::event(arg__1);
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

bool  QtScriptShell_QNetworkCookieJar::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::eventFilter(arg__1, arg__2);
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

bool  QtScriptShell_QNetworkCookieJar::insertCookie(const QNetworkCookie&  cookie)
{
    QScriptValue _q_function = __qtscript_self.property("insertCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertCookie") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::insertCookie(cookie);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QNetworkCookieJar::setCookiesFromUrl(const QList<QNetworkCookie >&  cookieList, const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("setCookiesFromUrl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setCookiesFromUrl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookieList)
            << qScriptValueFromValue(_q_engine, url)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QNetworkCookieJar::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QNetworkCookieJar::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QNetworkCookieJar::updateCookie(const QNetworkCookie&  cookie)
{
    QScriptValue _q_function = __qtscript_self.property("updateCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCookie") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::updateCookie(cookie);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QNetworkCookieJar::validateCookie(const QNetworkCookie&  cookie, const QUrl&  url) const
{
    QScriptValue _q_function = __qtscript_self.property("validateCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("validateCookie") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QNetworkCookieJar::validateCookie(cookie, url);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)
            << qScriptValueFromValue(_q_engine, url)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

