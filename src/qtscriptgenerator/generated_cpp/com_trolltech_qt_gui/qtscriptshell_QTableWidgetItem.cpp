#include "qtscriptshell_QTableWidgetItem.h"

#include <QtScript/QScriptEngine>
#include <QIconEngine>
#include <QVariant>
#include <qbrush.h>
#include <qdatastream.h>
#include <qfont.h>
#include <qsize.h>
#include <qtablewidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QTableWidgetItem*)

QtScriptShell_QTableWidgetItem::QtScriptShell_QTableWidgetItem(const QIcon&  icon, const QString&  text, int  type)
    : QTableWidgetItem(icon, text, type) {}

QtScriptShell_QTableWidgetItem::QtScriptShell_QTableWidgetItem(const QString&  text, int  type)
    : QTableWidgetItem(text, type) {}

QtScriptShell_QTableWidgetItem::QtScriptShell_QTableWidgetItem(int  type)
    : QTableWidgetItem(type) {}

QtScriptShell_QTableWidgetItem::~QtScriptShell_QTableWidgetItem() {}

QTableWidgetItem*  QtScriptShell_QTableWidgetItem::clone() const
{
    QScriptValue _q_function = __qtscript_self.property("clone");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clone") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableWidgetItem::clone();
    } else {
        _q_function.setData(QScriptValue(true));
        QTableWidgetItem* _q_retval = qscriptvalue_cast<QTableWidgetItem* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QTableWidgetItem::data(int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableWidgetItem::data(role);
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

void QtScriptShell_QTableWidgetItem::setData(int  role, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableWidgetItem::setData(role, value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, role)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

