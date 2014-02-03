#include "qtscriptshell_QHeaderView.h"

#include <QtScript/QScriptEngine>
#include <QIconEngine>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qheaderview.h>
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>
#include <qwindow.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QActionEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractItemDelegate::EndEditHint)
Q_DECLARE_METATYPE(QCloseEvent*)
Q_DECLARE_METATYPE(QContextMenuEvent*)
Q_DECLARE_METATYPE(QVector<int>)
Q_DECLARE_METATYPE(QDragEnterEvent*)
Q_DECLARE_METATYPE(QDragLeaveEvent*)
Q_DECLARE_METATYPE(QDragMoveEvent*)
Q_DECLARE_METATYPE(QDropEvent*)
Q_DECLARE_METATYPE(QAbstractItemView::EditTrigger)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QHideEvent*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QMoveEvent*)
Q_DECLARE_METATYPE(long*)
Q_DECLARE_METATYPE(QPaintEngine*)
Q_DECLARE_METATYPE(QPaintEvent*)
Q_DECLARE_METATYPE(QPoint*)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QResizeEvent*)
Q_DECLARE_METATYPE(QAbstractItemView::ScrollHint)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QItemSelection)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QItemSelectionModel*)
Q_DECLARE_METATYPE(QShowEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTabletEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QWheelEvent*)

QtScriptShell_QHeaderView::QtScriptShell_QHeaderView(Qt::Orientation  orientation, QWidget*  parent)
    : QHeaderView(orientation, parent) {}

QtScriptShell_QHeaderView::~QtScriptShell_QHeaderView() {}

void QtScriptShell_QHeaderView::actionEvent(QActionEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("actionEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::actionEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::changeEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("changeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("changeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::changeEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("closeEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::closeEditor(editor, hint);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, hint));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::closeEvent(QCloseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("closeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::closeEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::commitData(QWidget*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("commitData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("commitData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::commitData(editor);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::contextMenuEvent(QContextMenuEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::contextMenuEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::currentChanged(const QModelIndex&  current, const QModelIndex&  old)
{
    QScriptValue _q_function = __qtscript_self.property("currentChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::currentChanged(current, old);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, current)
            << qScriptValueFromValue(_q_engine, old));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("dataChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dataChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::dataChanged(topLeft, bottomRight, roles);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, topLeft)
            << qScriptValueFromValue(_q_engine, bottomRight)
            << qScriptValueFromValue(_q_engine, roles));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QHeaderView::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::devType();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::doItemsLayout()
{
    QScriptValue _q_function = __qtscript_self.property("doItemsLayout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doItemsLayout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::doItemsLayout();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::dragEnterEvent(QDragEnterEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::dragEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::dragLeaveEvent(QDragLeaveEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::dragLeaveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::dragMoveEvent(QDragMoveEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::dragMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::dropEvent(QDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::dropEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QHeaderView::edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("edit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("edit") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::edit(index, trigger, event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, trigger)
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::editorDestroyed(QObject*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("editorDestroyed");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorDestroyed") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::editorDestroyed(editor);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::enterEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("enterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("enterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::enterEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QHeaderView::event(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::event(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QHeaderView::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::eventFilter(arg__1, arg__2);
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

void QtScriptShell_QHeaderView::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::focusInEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QHeaderView::focusNextPrevChild(bool  next)
{
    QScriptValue _q_function = __qtscript_self.property("focusNextPrevChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusNextPrevChild") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::focusNextPrevChild(next);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, next)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::focusOutEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QHeaderView::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::hasHeightForWidth();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QHeaderView::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::heightForWidth(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::hideEvent(QHideEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("hideEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hideEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::hideEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QHeaderView::horizontalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("horizontalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalOffset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::horizontalOffset();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::horizontalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::horizontalScrollbarAction(action);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::horizontalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarValueChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::horizontalScrollbarValueChanged(value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

QModelIndex  QtScriptShell_QHeaderView::indexAt(const QPoint&  p) const
{
    QScriptValue _q_function = __qtscript_self.property("indexAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::indexAt(p);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QModelIndex _q_retval = qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, p)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::initPainter(QPainter*  painter) const
{
    QScriptValue _q_function = __qtscript_self.property("initPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("initPainter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::initPainter(painter);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::inputMethodEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QHeaderView::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::inputMethodQuery(query);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QHeaderView::isIndexHidden(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("isIndexHidden");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isIndexHidden") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::isIndexHidden(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::keyPressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::keyReleaseEvent(QKeyEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::keyReleaseEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::keyboardSearch(const QString&  search)
{
    QScriptValue _q_function = __qtscript_self.property("keyboardSearch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyboardSearch") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::keyboardSearch(search);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, search));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::leaveEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("leaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("leaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::leaveEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QHeaderView::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::metric(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::mouseDoubleClickEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::mouseDoubleClickEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::mouseMoveEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::mouseMoveEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::mousePressEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::mousePressEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::mouseReleaseEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::mouseReleaseEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::moveEvent(QMoveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("moveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::moveEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QHeaderView::nativeEvent(const QByteArray&  eventType, void*  message, long*  result)
{
    QScriptValue _q_function = __qtscript_self.property("nativeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nativeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::nativeEvent(eventType, message, result);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, eventType)
            << qScriptValueFromValue(_q_engine, message)
            << qScriptValueFromValue(_q_engine, result)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QPaintEngine*  QtScriptShell_QHeaderView::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::paintEngine();
    } else {
        _q_function.setData(QScriptValue(true));
        QPaintEngine* _q_retval = qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::paintEvent(QPaintEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("paintEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::paintEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::paintSection(QPainter*  painter, const QRect&  rect, int  logicalIndex) const
{
    QScriptValue _q_function = __qtscript_self.property("paintSection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintSection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, logicalIndex));
        _q_function.setData(QScriptValue(false));
    }
}

QPaintDevice*  QtScriptShell_QHeaderView::redirected(QPoint*  offset) const
{
    QScriptValue _q_function = __qtscript_self.property("redirected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("redirected") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::redirected(offset);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QPaintDevice* _q_retval = qscriptvalue_cast<QPaintDevice* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, offset)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::reset();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::resizeEvent(QResizeEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("resizeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resizeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::resizeEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsAboutToBeRemoved");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsAboutToBeRemoved") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::rowsAboutToBeRemoved(parent, start, end);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, start)
            << qScriptValueFromValue(_q_engine, end));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::rowsInserted(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsInserted");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsInserted") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::rowsInserted(parent, start, end);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, start)
            << qScriptValueFromValue(_q_engine, end));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::scrollContentsBy(int  dx, int  dy)
{
    QScriptValue _q_function = __qtscript_self.property("scrollContentsBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollContentsBy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::scrollContentsBy(dx, dy);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dx)
            << qScriptValueFromValue(_q_engine, dy));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("scrollTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollTo") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::scrollTo(index, hint);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, hint));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QHeaderView::sectionSizeFromContents(int  logicalIndex) const
{
    QScriptValue _q_function = __qtscript_self.property("sectionSizeFromContents");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sectionSizeFromContents") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::sectionSizeFromContents(logicalIndex);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, logicalIndex)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::selectAll()
{
    QScriptValue _q_function = __qtscript_self.property("selectAll");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectAll") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::selectAll();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QList<QModelIndex >  QtScriptShell_QHeaderView::selectedIndexes() const
{
    QScriptValue _q_function = __qtscript_self.property("selectedIndexes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedIndexes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::selectedIndexes();
    } else {
        _q_function.setData(QScriptValue(true));
        QList<QModelIndex > _q_retval = qscriptvalue_cast<QList<QModelIndex > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected)
{
    QScriptValue _q_function = __qtscript_self.property("selectionChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::selectionChanged(selected, deselected);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selected)
            << qScriptValueFromValue(_q_engine, deselected));
        _q_function.setData(QScriptValue(false));
    }
}

QItemSelectionModel::SelectionFlags  QtScriptShell_QHeaderView::selectionCommand(const QModelIndex&  index, const QEvent*  event) const
{
    QScriptValue _q_function = __qtscript_self.property("selectionCommand");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionCommand") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::selectionCommand(index, event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QItemSelectionModel::SelectionFlags _q_retval = qscriptvalue_cast<QItemSelectionModel::SelectionFlags >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, const_cast<QEvent *>(event))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::setModel(QAbstractItemModel*  model)
{
    QScriptValue _q_function = __qtscript_self.property("setModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::setModel(model);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, model));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::setRootIndex(const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("setRootIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRootIndex") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::setRootIndex(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  flags)
{
    QScriptValue _q_function = __qtscript_self.property("setSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::setSelection(rect, flags);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, flags));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::setSelectionModel(QItemSelectionModel*  selectionModel)
{
    QScriptValue _q_function = __qtscript_self.property("setSelectionModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelectionModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::setSelectionModel(selectionModel);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selectionModel));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::setupViewport(QWidget*  viewport)
{
    QScriptValue _q_function = __qtscript_self.property("setupViewport");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setupViewport") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::setupViewport(viewport);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, viewport));
        _q_function.setData(QScriptValue(false));
    }
}

QPainter*  QtScriptShell_QHeaderView::sharedPainter() const
{
    QScriptValue _q_function = __qtscript_self.property("sharedPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sharedPainter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::sharedPainter();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainter* _q_retval = qscriptvalue_cast<QPainter* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::showEvent(QShowEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("showEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("showEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::showEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QHeaderView::sizeHintForColumn(int  column) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForColumn") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::sizeHintForColumn(column);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QHeaderView::sizeHintForRow(int  row) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForRow") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::sizeHintForRow(row);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::startDrag(Qt::DropActions  supportedActions)
{
    QScriptValue _q_function = __qtscript_self.property("startDrag");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDrag") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::startDrag(supportedActions);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, supportedActions));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::tabletEvent(QTabletEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("tabletEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tabletEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::tabletEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::timerEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::updateEditorData()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::updateEditorData();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::updateEditorGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometries") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::updateEditorGeometries();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::updateGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometries") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::updateGeometries();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QHeaderView::verticalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("verticalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalOffset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::verticalOffset();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::verticalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::verticalScrollbarAction(action);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QHeaderView::verticalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarValueChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::verticalScrollbarValueChanged(value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

QStyleOptionViewItem  QtScriptShell_QHeaderView::viewOptions() const
{
    QScriptValue _q_function = __qtscript_self.property("viewOptions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewOptions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::viewOptions();
    } else {
        _q_function.setData(QScriptValue(true));
        QStyleOptionViewItem _q_retval = qscriptvalue_cast<QStyleOptionViewItem >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QHeaderView::viewportEvent(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("viewportEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::viewportEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSize  QtScriptShell_QHeaderView::viewportSizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("viewportSizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportSizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::viewportSizeHint();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QHeaderView::visualRect(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::visualRect(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRegion  QtScriptShell_QHeaderView::visualRegionForSelection(const QItemSelection&  selection) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRegionForSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRegionForSelection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QHeaderView::visualRegionForSelection(selection);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QRegion _q_retval = qscriptvalue_cast<QRegion >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selection)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QHeaderView::wheelEvent(QWheelEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QHeaderView::wheelEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

