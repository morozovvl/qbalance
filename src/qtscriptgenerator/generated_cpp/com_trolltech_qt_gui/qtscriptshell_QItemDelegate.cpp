#include "qtscriptshell_QItemDelegate.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfont.h>
#include <qitemdelegate.h>
#include <qitemeditorfactory.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(Qt::CheckState)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QHelpEvent*)
Q_DECLARE_METATYPE(QAbstractItemView*)
Q_DECLARE_METATYPE(QVector<int>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QItemDelegate::QtScriptShell_QItemDelegate(QObject*  parent)
    : QItemDelegate(parent) {}

QtScriptShell_QItemDelegate::~QtScriptShell_QItemDelegate() {}

void QtScriptShell_QItemDelegate::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QWidget*  QtScriptShell_QItemDelegate::createEditor(QWidget*  parent, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("createEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::createEditor(parent, option, index);
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

void QtScriptShell_QItemDelegate::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QItemDelegate::destroyEditor(QWidget*  editor, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("destroyEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("destroyEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::destroyEditor(editor, index);
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

void QtScriptShell_QItemDelegate::drawCheck(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect, Qt::CheckState  state) const
{
    QScriptValue _q_function = __qtscript_self.property("drawCheck");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawCheck") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::drawCheck(painter, option, rect, state);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, state));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QItemDelegate::drawDecoration(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("drawDecoration");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawDecoration") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::drawDecoration(painter, option, rect, pixmap);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, pixmap));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QItemDelegate::drawDisplay(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect, const QString&  text) const
{
    QScriptValue _q_function = __qtscript_self.property("drawDisplay");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawDisplay") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::drawDisplay(painter, option, rect, text);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, text));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QItemDelegate::drawFocus(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect) const
{
    QScriptValue _q_function = __qtscript_self.property("drawFocus");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawFocus") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::drawFocus(painter, option, rect);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, rect));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QItemDelegate::editorEvent(QEvent*  event, QAbstractItemModel*  model, const QStyleOptionViewItem&  option, const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("editorEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::editorEvent(event, model, option, index);
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

bool  QtScriptShell_QItemDelegate::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::event(arg__1);
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

bool  QtScriptShell_QItemDelegate::eventFilter(QObject*  object, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::eventFilter(object, event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, object)
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QItemDelegate::helpEvent(QHelpEvent*  event, QAbstractItemView*  view, const QStyleOptionViewItem&  option, const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("helpEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("helpEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::helpEvent(event, view, option, index);
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

void QtScriptShell_QItemDelegate::paint(QPainter*  painter, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::paint(painter, option, index);
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

QVector<int >  QtScriptShell_QItemDelegate::paintingRoles() const
{
    QScriptValue _q_function = __qtscript_self.property("paintingRoles");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintingRoles") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::paintingRoles();
    } else {
        _q_function.setData(QScriptValue(true));
        QVector<int > _q_retval = qscriptvalue_cast<QVector<int > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QItemDelegate::setEditorData(QWidget*  editor, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("setEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEditorData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::setEditorData(editor, index);
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

void QtScriptShell_QItemDelegate::setModelData(QWidget*  editor, QAbstractItemModel*  model, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("setModelData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModelData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::setModelData(editor, model, index);
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

QSize  QtScriptShell_QItemDelegate::sizeHint(const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemDelegate::sizeHint(option, index);
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

void QtScriptShell_QItemDelegate::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QItemDelegate::updateEditorGeometry(QWidget*  editor, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QItemDelegate::updateEditorGeometry(editor, option, index);
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

