#include "qtscriptshell_QGraphicsLineItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qline.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpen.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QGraphicsSceneContextMenuEvent*)
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
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneWheelEvent*)

QtScriptShell_QGraphicsLineItem::QtScriptShell_QGraphicsLineItem(QGraphicsItem*  parent)
    : QGraphicsLineItem(parent) {}

QtScriptShell_QGraphicsLineItem::QtScriptShell_QGraphicsLineItem(const QLineF&  line, QGraphicsItem*  parent)
    : QGraphicsLineItem(line, parent) {}

QtScriptShell_QGraphicsLineItem::QtScriptShell_QGraphicsLineItem(qreal  x1, qreal  y1, qreal  x2, qreal  y2, QGraphicsItem*  parent)
    : QGraphicsLineItem(x1, y1, x2, y2, parent) {}

QtScriptShell_QGraphicsLineItem::~QtScriptShell_QGraphicsLineItem() {}

void QtScriptShell_QGraphicsLineItem::advance(int  phase)
{
    QScriptValue _q_function = __qtscript_self.property("advance");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("advance") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::advance(phase);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, phase));
        _q_function.setData(QScriptValue(false));
    }
}

QRectF  QtScriptShell_QGraphicsLineItem::boundingRect() const
{
    QScriptValue _q_function = __qtscript_self.property("boundingRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("boundingRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::boundingRect();
    } else {
        _q_function.setData(QScriptValue(true));
        QRectF _q_retval = qscriptvalue_cast<QRectF >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QGraphicsLineItem::collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const
{
    QScriptValue _q_function = __qtscript_self.property("collidesWithItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("collidesWithItem") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::collidesWithItem(other, mode);
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

bool  QtScriptShell_QGraphicsLineItem::collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const
{
    QScriptValue _q_function = __qtscript_self.property("collidesWithPath");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("collidesWithPath") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::collidesWithPath(path, mode);
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

bool  QtScriptShell_QGraphicsLineItem::contains(const QPointF&  point) const
{
    QScriptValue _q_function = __qtscript_self.property("contains");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contains") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::contains(point);
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

void QtScriptShell_QGraphicsLineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::contextMenuEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::dragEnterEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::dragEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::dragLeaveEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::dragLeaveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::dragMoveEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::dragMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::dropEvent(QGraphicsSceneDragDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::dropEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QGraphicsLineItem::extension(const QVariant&  variant) const
{
    QScriptValue _q_function = __qtscript_self.property("extension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("extension") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::extension(variant);
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

void QtScriptShell_QGraphicsLineItem::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::focusInEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::focusOutEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverEnterEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::hoverEnterEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverLeaveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::hoverLeaveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("hoverMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hoverMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::hoverMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::inputMethodEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QGraphicsLineItem::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::inputMethodQuery(query);
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

bool  QtScriptShell_QGraphicsLineItem::isObscuredBy(const QGraphicsItem*  item) const
{
    QScriptValue _q_function = __qtscript_self.property("isObscuredBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isObscuredBy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::isObscuredBy(item);
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

QVariant  QtScriptShell_QGraphicsLineItem::itemChange(QGraphicsItem::GraphicsItemChange  change, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("itemChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemChange") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::itemChange(change, value);
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

void QtScriptShell_QGraphicsLineItem::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::keyPressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::keyReleaseEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::keyReleaseEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::mouseDoubleClickEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::mouseMoveEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::mousePressEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::mousePressEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::mouseReleaseEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

QPainterPath  QtScriptShell_QGraphicsLineItem::opaqueArea() const
{
    QScriptValue _q_function = __qtscript_self.property("opaqueArea");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("opaqueArea") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::opaqueArea();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainterPath _q_retval = qscriptvalue_cast<QPainterPath >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsLineItem::paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::paint(painter, option, widget);
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

bool  QtScriptShell_QGraphicsLineItem::sceneEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("sceneEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sceneEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::sceneEvent(event);
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

bool  QtScriptShell_QGraphicsLineItem::sceneEventFilter(QGraphicsItem*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("sceneEventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sceneEventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::sceneEventFilter(watched, event);
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

QPainterPath  QtScriptShell_QGraphicsLineItem::shape() const
{
    QScriptValue _q_function = __qtscript_self.property("shape");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("shape") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::shape();
    } else {
        _q_function.setData(QScriptValue(true));
        QPainterPath _q_retval = qscriptvalue_cast<QPainterPath >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QGraphicsLineItem::type() const
{
    QScriptValue _q_function = __qtscript_self.property("type");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("type") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsLineItem::type();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsLineItem::wheelEvent(QGraphicsSceneWheelEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLineItem::wheelEvent(event);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
        _q_function.setData(QScriptValue(false));
    }
}

