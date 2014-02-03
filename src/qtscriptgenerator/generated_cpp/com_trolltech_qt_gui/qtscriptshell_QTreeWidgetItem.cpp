#include "qtscriptshell_QTreeWidgetItem.h"

#include <QtScript/QScriptEngine>
#include <QIconEngine>
#include <QVariant>
#include <qbrush.h>
#include <qdatastream.h>
#include <qfont.h>
#include <qlist.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qtreewidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QTreeWidgetItem*)

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, QTreeWidgetItem*  after, int  type)
    : QTreeWidgetItem(view, after, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, const QStringList&  strings, int  type)
    : QTreeWidgetItem(view, strings, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, int  type)
    : QTreeWidgetItem(view, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, QTreeWidgetItem*  after, int  type)
    : QTreeWidgetItem(parent, after, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, const QStringList&  strings, int  type)
    : QTreeWidgetItem(parent, strings, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, int  type)
    : QTreeWidgetItem(parent, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(const QStringList&  strings, int  type)
    : QTreeWidgetItem(strings, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(int  type)
    : QTreeWidgetItem(type) {}

QtScriptShell_QTreeWidgetItem::~QtScriptShell_QTreeWidgetItem() {}

QTreeWidgetItem*  QtScriptShell_QTreeWidgetItem::clone() const
{
    QScriptValue _q_function = __qtscript_self.property("clone");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clone") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTreeWidgetItem::clone();
    } else {
        _q_function.setData(QScriptValue(true));
        QTreeWidgetItem* _q_retval = qscriptvalue_cast<QTreeWidgetItem* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QTreeWidgetItem::data(int  column, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTreeWidgetItem::data(column, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTreeWidgetItem::setData(int  column, int  role, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTreeWidgetItem::setData(column, role, value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, role)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

