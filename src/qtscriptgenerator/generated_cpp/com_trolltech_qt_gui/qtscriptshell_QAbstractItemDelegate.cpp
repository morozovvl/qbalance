#include "qtscriptshell_QAbstractItemDelegate.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QHelpEvent*)
Q_DECLARE_METATYPE(QAbstractItemView*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QVector<int>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QAbstractItemDelegate::QtScriptShell_QAbstractItemDelegate(QObject*  parent)
    : QAbstractItemDelegate(parent) {}

QtScriptShell_QAbstractItemDelegate::~QtScriptShell_QAbstractItemDelegate() {}

void QtScriptShell_QAbstractItemDelegate::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QWidget*  QtScriptShell_QAbstractItemDelegate::createEditor(QWidget*  parent, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("createEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractItemDelegate::createEditor(parent, option, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QWidget* _q_retval = qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAbstractItemDelegate::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAbstractItemDelegate::destroyEditor(QWidget*  editor, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("destroyEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("destroyEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::destroyEditor(editor, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QAbstractItemDelegate::editorEvent(QEvent*  event, QAbstractItemModel*  model, const QStyleOptionViewItem&  option, const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("editorEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractItemDelegate::editorEvent(event, model, option, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)
            << qScriptValueFromValue(_q_engine, model)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QAbstractItemDelegate::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractItemDelegate::event(arg__1);
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

bool  QtScriptShell_QAbstractItemDelegate::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractItemDelegate::eventFilter(arg__1, arg__2);
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

bool  QtScriptShell_QAbstractItemDelegate::helpEvent(QHelpEvent*  event, QAbstractItemView*  view, const QStyleOptionViewItem&  option, const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("helpEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("helpEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractItemDelegate::helpEvent(event, view, option, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)
            << qScriptValueFromValue(_q_engine, view)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAbstractItemDelegate::paint(QPainter*  painter, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractItemDelegate::paint() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

QVector<int >  QtScriptShell_QAbstractItemDelegate::paintingRoles() const
{
    QScriptValue _q_function = __qtscript_self.property("paintingRoles");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintingRoles") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAbstractItemDelegate::paintingRoles();
    } else {
        _q_function.setData(QScriptValue(true));
        QVector<int > _q_retval = qscriptvalue_cast<QVector<int > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAbstractItemDelegate::setEditorData(QWidget*  editor, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("setEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEditorData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::setEditorData(editor, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAbstractItemDelegate::setModelData(QWidget*  editor, QAbstractItemModel*  model, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("setModelData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModelData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::setModelData(editor, model, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, model)
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QAbstractItemDelegate::sizeHint(const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAbstractItemDelegate::sizeHint() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAbstractItemDelegate::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QAbstractItemDelegate::updateEditorGeometry(QWidget*  editor, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAbstractItemDelegate::updateEditorGeometry(editor, option, index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

