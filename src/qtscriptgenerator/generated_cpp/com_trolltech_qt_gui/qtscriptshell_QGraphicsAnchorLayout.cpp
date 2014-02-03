#include "qtscriptshell_QGraphicsAnchorLayout.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qgraphicsanchorlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(Qt::SizeHint)
Q_DECLARE_METATYPE(QEvent*)

QtScriptShell_QGraphicsAnchorLayout::QtScriptShell_QGraphicsAnchorLayout(QGraphicsLayoutItem*  parent)
    : QGraphicsAnchorLayout(parent) {}

QtScriptShell_QGraphicsAnchorLayout::~QtScriptShell_QGraphicsAnchorLayout() {}

int  QtScriptShell_QGraphicsAnchorLayout::count() const
{
    QScriptValue _q_function = __qtscript_self.property("count");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("count") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsAnchorLayout::count();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsAnchorLayout::getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const
{
    QScriptValue _q_function = __qtscript_self.property("getContentsMargins");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("getContentsMargins") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsAnchorLayout::getContentsMargins(left, top, right, bottom);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, left)
            << qScriptValueFromValue(_q_engine, top)
            << qScriptValueFromValue(_q_engine, right)
            << qScriptValueFromValue(_q_engine, bottom));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsAnchorLayout::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsAnchorLayout::invalidate();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QGraphicsLayoutItem*  QtScriptShell_QGraphicsAnchorLayout::itemAt(int  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsAnchorLayout::itemAt(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QGraphicsLayoutItem* _q_retval = qscriptvalue_cast<QGraphicsLayoutItem* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsAnchorLayout::removeAt(int  index)
{
    QScriptValue _q_function = __qtscript_self.property("removeAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsAnchorLayout::removeAt(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsAnchorLayout::setGeometry(const QRectF&  rect)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsAnchorLayout::setGeometry(rect);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rect));
        _q_function.setData(QScriptValue(false));
    }
}

QSizeF  QtScriptShell_QGraphicsAnchorLayout::sizeHint(Qt::SizeHint  which, const QSizeF&  constraint) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGraphicsAnchorLayout::sizeHint(which, constraint);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSizeF _q_retval = qscriptvalue_cast<QSizeF >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, which)
            << qScriptValueFromValue(_q_engine, constraint)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGraphicsAnchorLayout::updateGeometry()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsAnchorLayout::updateGeometry();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGraphicsAnchorLayout::widgetEvent(QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("widgetEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widgetEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsAnchorLayout::widgetEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

