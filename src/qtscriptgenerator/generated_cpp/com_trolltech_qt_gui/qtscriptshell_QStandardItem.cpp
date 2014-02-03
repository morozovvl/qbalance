#include "qtscriptshell_QStandardItem.h"

#include <QtScript/QScriptEngine>
#include <QIconEngine>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbrush.h>
#include <qdatastream.h>
#include <qfont.h>
#include <qlist.h>
#include <qsize.h>
#include <qstandarditemmodel.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QStandardItem*)

QtScriptShell_QStandardItem::QtScriptShell_QStandardItem()
    : QStandardItem() {}

QtScriptShell_QStandardItem::QtScriptShell_QStandardItem(const QIcon&  icon, const QString&  text)
    : QStandardItem(icon, text) {}

QtScriptShell_QStandardItem::QtScriptShell_QStandardItem(const QStandardItem&  other)
    : QStandardItem(other) {}

QtScriptShell_QStandardItem::QtScriptShell_QStandardItem(const QString&  text)
    : QStandardItem(text) {}

QtScriptShell_QStandardItem::QtScriptShell_QStandardItem(int  rows, int  columns)
    : QStandardItem(rows, columns) {}

QtScriptShell_QStandardItem::~QtScriptShell_QStandardItem() {}

QStandardItem*  QtScriptShell_QStandardItem::clone() const
{
    QScriptValue _q_function = __qtscript_self.property("clone");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clone") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QStandardItem::clone();
    } else {
        _q_function.setData(QScriptValue(true));
        QStandardItem* _q_retval = qscriptvalue_cast<QStandardItem* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QStandardItem::data(int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QStandardItem::data(role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QStandardItem::setData(const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QStandardItem::setData(value, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QStandardItem::type() const
{
    QScriptValue _q_function = __qtscript_self.property("type");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("type") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QStandardItem::type();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

