#include "qtscriptshell_QGraphicsLayoutItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qgraphicsitem.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(Qt::SizeHint)

QtScriptShell_QGraphicsLayoutItem::QtScriptShell_QGraphicsLayoutItem(QGraphicsLayoutItem*  parent, bool  isLayout)
    : QGraphicsLayoutItem(parent, isLayout) {}

QtScriptShell_QGraphicsLayoutItem::~QtScriptShell_QGraphicsLayoutItem() {}

void QtScriptShell_QGraphicsLayoutItem::getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const
{
    QScriptValue _q_function = __qtscript_self.property("getContentsMargins");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("getContentsMargins") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLayoutItem::getContentsMargins(left, top, right, bottom);
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

void QtScriptShell_QGraphicsLayoutItem::setGeometry(const QRectF&  rect)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLayoutItem::setGeometry(rect);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rect));
        _q_function.setData(QScriptValue(false));
    }
}

QSizeF  QtScriptShell_QGraphicsLayoutItem::sizeHint(Qt::SizeHint  which, const QSizeF&  constraint) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QGraphicsLayoutItem::sizeHint() is abstract!");
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

void QtScriptShell_QGraphicsLayoutItem::updateGeometry()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGraphicsLayoutItem::updateGeometry();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

