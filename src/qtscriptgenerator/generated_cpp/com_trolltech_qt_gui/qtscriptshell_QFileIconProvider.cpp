#include "qtscriptshell_QFileIconProvider.h"

#include <QtScript/QScriptEngine>
#include <QIconEngine>
#include <QVariant>
#include <qfileiconprovider.h>
#include <qfileinfo.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QFileIconProvider::IconType)

QtScriptShell_QFileIconProvider::QtScriptShell_QFileIconProvider()
    : QFileIconProvider() {}

QtScriptShell_QFileIconProvider::~QtScriptShell_QFileIconProvider() {}

QIcon  QtScriptShell_QFileIconProvider::icon(QFileIconProvider::IconType  type) const
{
    QScriptValue _q_function = __qtscript_self.property("icon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("icon") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QFileIconProvider::icon(type);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QIcon _q_retval = qscriptvalue_cast<QIcon >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QIcon  QtScriptShell_QFileIconProvider::icon(const QFileInfo&  info) const
{
    QScriptValue _q_function = __qtscript_self.property("icon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("icon") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QFileIconProvider::icon(info);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QIcon _q_retval = qscriptvalue_cast<QIcon >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, info)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QFileIconProvider::type(const QFileInfo&  info) const
{
    QScriptValue _q_function = __qtscript_self.property("type");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("type") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QFileIconProvider::type(info);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, info)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

