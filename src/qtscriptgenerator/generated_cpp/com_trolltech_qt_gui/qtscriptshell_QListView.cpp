#include "qtscriptshell_QListView.h"

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
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlistview.h>
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

QtScriptShell_QListView::QtScriptShell_QListView(QWidget*  parent)
    : QListView(parent) {}

QtScriptShell_QListView::~QtScriptShell_QListView() {}

void QtScriptShell_QListView::actionEvent(QActionEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("actionEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::actionEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::changeEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("changeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("changeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::changeEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("closeEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::closeEditor(editor, hint);
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

void QtScriptShell_QListView::closeEvent(QCloseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("closeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::closeEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::commitData(QWidget*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("commitData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("commitData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::commitData(editor);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::contextMenuEvent(QContextMenuEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::contextMenuEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::currentChanged(const QModelIndex&  current, const QModelIndex&  previous)
{
    QScriptValue _q_function = __qtscript_self.property("currentChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::currentChanged(current, previous);
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

void QtScriptShell_QListView::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("dataChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dataChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::dataChanged(topLeft, bottomRight, roles);
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

int  QtScriptShell_QListView::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::devType();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QListView::doItemsLayout()
{
    QScriptValue _q_function = __qtscript_self.property("doItemsLayout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doItemsLayout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::doItemsLayout();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::dragEnterEvent(QDragEnterEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::dragEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::dragLeaveEvent(QDragLeaveEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::dragLeaveEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::dragMoveEvent(QDragMoveEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::dragMoveEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::dropEvent(QDropEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::dropEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QListView::edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("edit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("edit") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::edit(index, trigger, event);
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

void QtScriptShell_QListView::editorDestroyed(QObject*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("editorDestroyed");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorDestroyed") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::editorDestroyed(editor);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::enterEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("enterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("enterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::enterEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QListView::event(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::event(e);
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

bool  QtScriptShell_QListView::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::eventFilter(arg__1, arg__2);
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

void QtScriptShell_QListView::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::focusInEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QListView::focusNextPrevChild(bool  next)
{
    QScriptValue _q_function = __qtscript_self.property("focusNextPrevChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusNextPrevChild") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::focusNextPrevChild(next);
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

void QtScriptShell_QListView::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::focusOutEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QListView::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::hasHeightForWidth();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QListView::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::heightForWidth(arg__1);
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

void QtScriptShell_QListView::hideEvent(QHideEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("hideEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hideEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::hideEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QListView::horizontalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("horizontalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalOffset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::horizontalOffset();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QListView::horizontalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::horizontalScrollbarAction(action);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::horizontalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarValueChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::horizontalScrollbarValueChanged(value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

QModelIndex  QtScriptShell_QListView::indexAt(const QPoint&  p) const
{
    QScriptValue _q_function = __qtscript_self.property("indexAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::indexAt(p);
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

void QtScriptShell_QListView::initPainter(QPainter*  painter) const
{
    QScriptValue _q_function = __qtscript_self.property("initPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("initPainter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::initPainter(painter);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::inputMethodEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QListView::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::inputMethodQuery(query);
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

bool  QtScriptShell_QListView::isIndexHidden(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("isIndexHidden");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isIndexHidden") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::isIndexHidden(index);
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

void QtScriptShell_QListView::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::keyPressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::keyReleaseEvent(QKeyEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::keyReleaseEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::keyboardSearch(const QString&  search)
{
    QScriptValue _q_function = __qtscript_self.property("keyboardSearch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyboardSearch") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::keyboardSearch(search);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, search));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::leaveEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("leaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("leaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::leaveEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QListView::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::metric(arg__1);
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

void QtScriptShell_QListView::mouseDoubleClickEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::mouseDoubleClickEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::mouseMoveEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::mouseMoveEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::mousePressEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::mousePressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::mouseReleaseEvent(QMouseEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::mouseReleaseEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::moveEvent(QMoveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("moveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::moveEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QListView::nativeEvent(const QByteArray&  eventType, void*  message, long*  result)
{
    QScriptValue _q_function = __qtscript_self.property("nativeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nativeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::nativeEvent(eventType, message, result);
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

QPaintEngine*  QtScriptShell_QListView::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::paintEngine();
    } else {
        _q_function.setData(QScriptValue(true));
        QPaintEngine* _q_retval = qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QListView::paintEvent(QPaintEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("paintEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::paintEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

QPaintDevice*  QtScriptShell_QListView::redirected(QPoint*  offset) const
{
    QScriptValue _q_function = __qtscript_self.property("redirected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("redirected") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::redirected(offset);
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

void QtScriptShell_QListView::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::reset();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::resizeEvent(QResizeEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("resizeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resizeEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::resizeEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsAboutToBeRemoved");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsAboutToBeRemoved") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::rowsAboutToBeRemoved(parent, start, end);
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

void QtScriptShell_QListView::rowsInserted(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsInserted");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsInserted") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::rowsInserted(parent, start, end);
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

void QtScriptShell_QListView::scrollContentsBy(int  dx, int  dy)
{
    QScriptValue _q_function = __qtscript_self.property("scrollContentsBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollContentsBy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::scrollContentsBy(dx, dy);
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

void QtScriptShell_QListView::scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("scrollTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollTo") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::scrollTo(index, hint);
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

void QtScriptShell_QListView::selectAll()
{
    QScriptValue _q_function = __qtscript_self.property("selectAll");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectAll") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::selectAll();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QList<QModelIndex >  QtScriptShell_QListView::selectedIndexes() const
{
    QScriptValue _q_function = __qtscript_self.property("selectedIndexes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedIndexes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::selectedIndexes();
    } else {
        _q_function.setData(QScriptValue(true));
        QList<QModelIndex > _q_retval = qscriptvalue_cast<QList<QModelIndex > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QListView::selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected)
{
    QScriptValue _q_function = __qtscript_self.property("selectionChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::selectionChanged(selected, deselected);
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

QItemSelectionModel::SelectionFlags  QtScriptShell_QListView::selectionCommand(const QModelIndex&  index, const QEvent*  event) const
{
    QScriptValue _q_function = __qtscript_self.property("selectionCommand");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionCommand") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::selectionCommand(index, event);
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

void QtScriptShell_QListView::setModel(QAbstractItemModel*  model)
{
    QScriptValue _q_function = __qtscript_self.property("setModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::setModel(model);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, model));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::setRootIndex(const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("setRootIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRootIndex") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::setRootIndex(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command)
{
    QScriptValue _q_function = __qtscript_self.property("setSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::setSelection(rect, command);
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

void QtScriptShell_QListView::setSelectionModel(QItemSelectionModel*  selectionModel)
{
    QScriptValue _q_function = __qtscript_self.property("setSelectionModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelectionModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::setSelectionModel(selectionModel);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selectionModel));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::setupViewport(QWidget*  viewport)
{
    QScriptValue _q_function = __qtscript_self.property("setupViewport");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setupViewport") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::setupViewport(viewport);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, viewport));
        _q_function.setData(QScriptValue(false));
    }
}

QPainter*  QtScriptShell_QListView::sharedPainter() const
{
    QScriptValue _q_function = __qtscript_self.property("sharedPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sharedPainter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::sharedPainter();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainter* _q_retval = qscriptvalue_cast<QPainter* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QListView::showEvent(QShowEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("showEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("showEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::showEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QListView::sizeHintForColumn(int  column) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForColumn") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::sizeHintForColumn(column);
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

int  QtScriptShell_QListView::sizeHintForRow(int  row) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForRow") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::sizeHintForRow(row);
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

void QtScriptShell_QListView::startDrag(Qt::DropActions  supportedActions)
{
    QScriptValue _q_function = __qtscript_self.property("startDrag");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDrag") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::startDrag(supportedActions);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, supportedActions));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::tabletEvent(QTabletEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("tabletEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tabletEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::tabletEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::timerEvent(QTimerEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::timerEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::updateEditorData()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::updateEditorData();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::updateEditorGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometries") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::updateEditorGeometries();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::updateGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometries") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::updateGeometries();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QListView::verticalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("verticalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalOffset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::verticalOffset();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QListView::verticalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::verticalScrollbarAction(action);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QListView::verticalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarValueChanged") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::verticalScrollbarValueChanged(value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

QStyleOptionViewItem  QtScriptShell_QListView::viewOptions() const
{
    QScriptValue _q_function = __qtscript_self.property("viewOptions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewOptions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::viewOptions();
    } else {
        _q_function.setData(QScriptValue(true));
        QStyleOptionViewItem _q_retval = qscriptvalue_cast<QStyleOptionViewItem >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QListView::viewportEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("viewportEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::viewportEvent(event);
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

QSize  QtScriptShell_QListView::viewportSizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("viewportSizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportSizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::viewportSizeHint();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QListView::visualRect(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::visualRect(index);
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

QRegion  QtScriptShell_QListView::visualRegionForSelection(const QItemSelection&  selection) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRegionForSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRegionForSelection") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QListView::visualRegionForSelection(selection);
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

void QtScriptShell_QListView::wheelEvent(QWheelEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QListView::wheelEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

