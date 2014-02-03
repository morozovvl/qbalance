#include "qtscriptshell_QGraphicsTextItem.h"

#include <QtScript/QScriptEngine>
#include <QTextCursor>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtransform.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QGraphicsSceneContextMenuEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneDragDropEvent*)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneHoverEvent*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QGraphicsItem::GraphicsItemChange)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneMouseEvent*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneWheelEvent*)

QtScriptShell_QGraphicsTextItem::QtScriptShell_QGraphicsTextItem(QGraphicsItem*  parent)
    : QGraphicsTextItem(parent) {}

QtScriptShell_QGraphicsTextItem::QtScriptShell_QGraphicsTextItem(const QString&  text, QGraphicsItem*  parent)
    : QGraphicsTextItem(text, parent) {}

QtScriptShell_QGraphicsTextItem::~QtScriptShell_QGraphicsTextItem() {}

void QtScriptShell_QGraphicsTextItem::advance(int  phase)
{
    QScriptValue _q_function = __qtscript_self.property("advance");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("advance") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::advance(phase);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, phase));
        _q_function.setData(QScriptValue(false));
    }
}

QRectF  QtScriptShell_QGraphicsTextItem::boundingRect() const
{
    QScriptValue _q_function = __qtscript_self.property("boundingRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("boundingRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::boundingRect();
    } else {
        _q_function.setData(QScriptValue(true));
        QRectF _q_retval = qscriptvalue_cast<QRectF >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QGraphicsTextItem::collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const
{
    QScriptValue _q_function = __qtscript_self.property("collidesWithItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("collidesWithItem") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::collidesWithItem(other, mode);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QGraphicsItem *>(other))
            << qScriptValueFromValue(_q_engine, mode)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QGraphicsTextItem::collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const
{
    QScriptValue _q_function = __qtscript_self.property("collidesWithPath");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("collidesWithPath") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::collidesWithPath(path, mode);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, path)
            << qScriptValueFromValue(_q_engine, mode)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QGraphicsTextItem::contains(const QPointF&  point) const
{
    QScriptValue _q_function = __qtscript_self.property("contains");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contains") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::contains(point);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, point)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::contextMenuEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::dragEnterEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::dragEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::dragLeaveEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::dragLeaveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::dragMoveEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::dragMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::dropEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::dropEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QGraphicsTextItem::event(QEvent*  ev)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::event(ev);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ev)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QGraphicsTextItem::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::eventFilter(arg__1, arg__2);
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

QVariant  QtScriptShell_QGraphicsTextItem::extension(const QVariant&  variant) const
{
    QScriptValue _q_function = __qtscript_self.property("extension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("extension") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::extension(variant);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, variant)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::focusInEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::focusOutEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::hoverEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::hoverLeaveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::hoverMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::inputMethodEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QGraphicsTextItem::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::inputMethodQuery(query);
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

bool  QtScriptShell_QGraphicsTextItem::isObscuredBy(const QGraphicsItem*  item) const
{
    QScriptValue _q_function = __qtscript_self.property("isObscuredBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isObscuredBy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::isObscuredBy(item);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QGraphicsItem *>(item))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QGraphicsTextItem::itemChange(QGraphicsItem::GraphicsItemChange  change, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("itemChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemChange") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::itemChange(change, value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, change)
            << qScriptValueFromValue(_q_engine, value)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::keyPressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::keyReleaseEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::keyReleaseEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::mouseDoubleClickEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::mouseMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::mousePressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::mouseReleaseEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QPainterPath  QtScriptShell_QGraphicsTextItem::opaqueArea() const
{
    QScriptValue _q_function = __qtscript_self.property("opaqueArea");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("opaqueArea") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::opaqueArea();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainterPath _q_retval = qscriptvalue_cast<QPainterPath >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::paint(painter, option, widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionGraphicsItem *>(option))
            << qScriptValueFromValue(_q_engine, widget));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QGraphicsTextItem::sceneEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("sceneEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sceneEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::sceneEvent(event);
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

bool  QtScriptShell_QGraphicsTextItem::sceneEventFilter(QGraphicsItem*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("sceneEventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sceneEventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::sceneEventFilter(watched, event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QPainterPath  QtScriptShell_QGraphicsTextItem::shape() const
{
    QScriptValue _q_function = __qtscript_self.property("shape");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("shape") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::shape();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainterPath _q_retval = qscriptvalue_cast<QPainterPath >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QGraphicsTextItem::type() const
{
    QScriptValue _q_function = __qtscript_self.property("type");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("type") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsTextItem::type();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsTextItem::wheelEvent(QGraphicsSceneWheelEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsTextItem::wheelEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

