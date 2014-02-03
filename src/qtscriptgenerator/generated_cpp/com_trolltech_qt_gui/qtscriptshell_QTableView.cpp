#include "qtscriptshell_QTableView.h"

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
#include <qtableview.h>
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

QtScriptShell_QTableView::QtScriptShell_QTableView(QWidget*  parent)
    : QTableView(parent) {}

QtScriptShell_QTableView::~QtScriptShell_QTableView() {}

void QtScriptShell_QTableView::actionEvent(QActionEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("actionEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::actionEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::changeEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("changeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("changeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::changeEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("closeEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::closeEditor(editor, hint);
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

void QtScriptShell_QTableView::closeEvent(QCloseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("closeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::closeEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::commitData(QWidget*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("commitData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("commitData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::commitData(editor);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::contextMenuEvent(QContextMenuEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::contextMenuEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::currentChanged(const QModelIndex&  current, const QModelIndex&  previous)
{
    QScriptValue _q_function = __qtscript_self.property("currentChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::currentChanged(current, previous);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, current)
            << qScriptValueFromValue(_q_engine, previous));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("dataChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dataChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::dataChanged(topLeft, bottomRight, roles);
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

int  QtScriptShell_QTableView::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::devType();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTableView::doItemsLayout()
{
    QScriptValue _q_function = __qtscript_self.property("doItemsLayout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doItemsLayout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::doItemsLayout();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::dragEnterEvent(QDragEnterEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::dragEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::dragLeaveEvent(QDragLeaveEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::dragLeaveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::dragMoveEvent(QDragMoveEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::dragMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::dropEvent(QDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::dropEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QTableView::edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("edit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("edit") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::edit(index, trigger, event);
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

void QtScriptShell_QTableView::editorDestroyed(QObject*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("editorDestroyed");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorDestroyed") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::editorDestroyed(editor);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::enterEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("enterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("enterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::enterEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QTableView::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::event(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QTableView::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::eventFilter(arg__1, arg__2);
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

void QtScriptShell_QTableView::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::focusInEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QTableView::focusNextPrevChild(bool  next)
{
    QScriptValue _q_function = __qtscript_self.property("focusNextPrevChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusNextPrevChild") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::focusNextPrevChild(next);
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

void QtScriptShell_QTableView::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::focusOutEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QTableView::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::hasHeightForWidth();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QTableView::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::heightForWidth(arg__1);
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

void QtScriptShell_QTableView::hideEvent(QHideEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("hideEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hideEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::hideEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QTableView::horizontalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("horizontalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalOffset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::horizontalOffset();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTableView::horizontalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::horizontalScrollbarAction(action);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::horizontalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarValueChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::horizontalScrollbarValueChanged(value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

QModelIndex  QtScriptShell_QTableView::indexAt(const QPoint&  p) const
{
    QScriptValue _q_function = __qtscript_self.property("indexAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::indexAt(p);
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

void QtScriptShell_QTableView::initPainter(QPainter*  painter) const
{
    QScriptValue _q_function = __qtscript_self.property("initPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("initPainter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::initPainter(painter);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::inputMethodEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QTableView::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::inputMethodQuery(query);
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

bool  QtScriptShell_QTableView::isIndexHidden(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("isIndexHidden");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isIndexHidden") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::isIndexHidden(index);
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

void QtScriptShell_QTableView::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::keyPressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::keyReleaseEvent(QKeyEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::keyReleaseEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::keyboardSearch(const QString&  search)
{
    QScriptValue _q_function = __qtscript_self.property("keyboardSearch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyboardSearch") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::keyboardSearch(search);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, search));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::leaveEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("leaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("leaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::leaveEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QTableView::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::metric(arg__1);
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

void QtScriptShell_QTableView::mouseDoubleClickEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::mouseDoubleClickEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::mouseMoveEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::mouseMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::mousePressEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::mousePressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::mouseReleaseEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::mouseReleaseEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::moveEvent(QMoveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("moveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::moveEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QTableView::nativeEvent(const QByteArray&  eventType, void*  message, long*  result)
{
    QScriptValue _q_function = __qtscript_self.property("nativeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nativeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::nativeEvent(eventType, message, result);
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

QPaintEngine*  QtScriptShell_QTableView::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::paintEngine();
    } else {
        _q_function.setData(QScriptValue(true));
        QPaintEngine* _q_retval = qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTableView::paintEvent(QPaintEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("paintEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::paintEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

QPaintDevice*  QtScriptShell_QTableView::redirected(QPoint*  offset) const
{
    QScriptValue _q_function = __qtscript_self.property("redirected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("redirected") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::redirected(offset);
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

void QtScriptShell_QTableView::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::reset();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::resizeEvent(QResizeEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("resizeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resizeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::resizeEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsAboutToBeRemoved");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsAboutToBeRemoved") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::rowsAboutToBeRemoved(parent, start, end);
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

void QtScriptShell_QTableView::rowsInserted(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsInserted");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsInserted") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::rowsInserted(parent, start, end);
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

void QtScriptShell_QTableView::scrollContentsBy(int  dx, int  dy)
{
    QScriptValue _q_function = __qtscript_self.property("scrollContentsBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollContentsBy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::scrollContentsBy(dx, dy);
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

void QtScriptShell_QTableView::scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("scrollTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollTo") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::scrollTo(index, hint);
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

void QtScriptShell_QTableView::selectAll()
{
    QScriptValue _q_function = __qtscript_self.property("selectAll");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectAll") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::selectAll();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QList<QModelIndex >  QtScriptShell_QTableView::selectedIndexes() const
{
    QScriptValue _q_function = __qtscript_self.property("selectedIndexes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedIndexes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::selectedIndexes();
    } else {
        _q_function.setData(QScriptValue(true));
        QList<QModelIndex > _q_retval = qscriptvalue_cast<QList<QModelIndex > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTableView::selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected)
{
    QScriptValue _q_function = __qtscript_self.property("selectionChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::selectionChanged(selected, deselected);
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

QItemSelectionModel::SelectionFlags  QtScriptShell_QTableView::selectionCommand(const QModelIndex&  index, const QEvent*  event) const
{
    QScriptValue _q_function = __qtscript_self.property("selectionCommand");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionCommand") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::selectionCommand(index, event);
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

void QtScriptShell_QTableView::setModel(QAbstractItemModel*  model)
{
    QScriptValue _q_function = __qtscript_self.property("setModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::setModel(model);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, model));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::setRootIndex(const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("setRootIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRootIndex") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::setRootIndex(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command)
{
    QScriptValue _q_function = __qtscript_self.property("setSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::setSelection(rect, command);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, command));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::setSelectionModel(QItemSelectionModel*  selectionModel)
{
    QScriptValue _q_function = __qtscript_self.property("setSelectionModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelectionModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::setSelectionModel(selectionModel);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selectionModel));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::setupViewport(QWidget*  viewport)
{
    QScriptValue _q_function = __qtscript_self.property("setupViewport");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setupViewport") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::setupViewport(viewport);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, viewport));
        _q_function.setData(QScriptValue(false));
    }
}

QPainter*  QtScriptShell_QTableView::sharedPainter() const
{
    QScriptValue _q_function = __qtscript_self.property("sharedPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sharedPainter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::sharedPainter();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainter* _q_retval = qscriptvalue_cast<QPainter* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTableView::showEvent(QShowEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("showEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("showEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::showEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QTableView::sizeHintForColumn(int  column) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForColumn") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::sizeHintForColumn(column);
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

int  QtScriptShell_QTableView::sizeHintForRow(int  row) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForRow") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::sizeHintForRow(row);
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

void QtScriptShell_QTableView::startDrag(Qt::DropActions  supportedActions)
{
    QScriptValue _q_function = __qtscript_self.property("startDrag");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDrag") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::startDrag(supportedActions);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, supportedActions));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::tabletEvent(QTabletEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("tabletEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tabletEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::tabletEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::timerEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::updateEditorData()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::updateEditorData();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::updateEditorGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometries") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::updateEditorGeometries();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::updateGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometries") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::updateGeometries();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QTableView::verticalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("verticalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalOffset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::verticalOffset();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QTableView::verticalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::verticalScrollbarAction(action);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QTableView::verticalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarValueChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::verticalScrollbarValueChanged(value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

QStyleOptionViewItem  QtScriptShell_QTableView::viewOptions() const
{
    QScriptValue _q_function = __qtscript_self.property("viewOptions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewOptions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::viewOptions();
    } else {
        _q_function.setData(QScriptValue(true));
        QStyleOptionViewItem _q_retval = qscriptvalue_cast<QStyleOptionViewItem >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QTableView::viewportEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("viewportEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::viewportEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSize  QtScriptShell_QTableView::viewportSizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("viewportSizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportSizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::viewportSizeHint();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QTableView::visualRect(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::visualRect(index);
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

QRegion  QtScriptShell_QTableView::visualRegionForSelection(const QItemSelection&  selection) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRegionForSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRegionForSelection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTableView::visualRegionForSelection(selection);
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

void QtScriptShell_QTableView::wheelEvent(QWheelEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QTableView::wheelEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

