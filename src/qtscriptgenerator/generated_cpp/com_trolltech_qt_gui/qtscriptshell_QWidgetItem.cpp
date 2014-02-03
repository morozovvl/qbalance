#include "qtscriptshell_QWidgetItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QFlags<QSizePolicy::ControlType>)
Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QSpacerItem*)
Q_DECLARE_METATYPE(QWidget*)

QtScriptShell_QWidgetItem::QtScriptShell_QWidgetItem(QWidget*  w)
    : QWidgetItem(w) {}

QtScriptShell_QWidgetItem::~QtScriptShell_QWidgetItem() {}

QSizePolicy::ControlTypes  QtScriptShell_QWidgetItem::controlTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("controlTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("controlTypes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::controlTypes();
    } else {
        _q_function.setData(QScriptValue(true));
        QSizePolicy::ControlTypes _q_retval = qscriptvalue_cast<QSizePolicy::ControlTypes >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

Qt::Orientations  QtScriptShell_QWidgetItem::expandingDirections() const
{
    QScriptValue _q_function = __qtscript_self.property("expandingDirections");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expandingDirections") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::expandingDirections();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::Orientations _q_retval = qscriptvalue_cast<Qt::Orientations >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QWidgetItem::geometry() const
{
    QScriptValue _q_function = __qtscript_self.property("geometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("geometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::geometry();
    } else {
        _q_function.setData(QScriptValue(true));
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QWidgetItem::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::hasHeightForWidth();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QWidgetItem::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::heightForWidth(arg__1);
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

void QtScriptShell_QWidgetItem::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QWidgetItem::invalidate();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QWidgetItem::isEmpty() const
{
    QScriptValue _q_function = __qtscript_self.property("isEmpty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isEmpty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::isEmpty();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QLayout*  QtScriptShell_QWidgetItem::layout()
{
    QScriptValue _q_function = __qtscript_self.property("layout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::layout();
    } else {
        _q_function.setData(QScriptValue(true));
        QLayout* _q_retval = qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSize  QtScriptShell_QWidgetItem::maximumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("maximumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("maximumSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::maximumSize();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QWidgetItem::minimumHeightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("minimumHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::minimumHeightForWidth(arg__1);
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

QSize  QtScriptShell_QWidgetItem::minimumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("minimumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::minimumSize();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QWidgetItem::setGeometry(const QRect&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QWidgetItem::setGeometry(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QWidgetItem::sizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::sizeHint();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSpacerItem*  QtScriptShell_QWidgetItem::spacerItem()
{
    QScriptValue _q_function = __qtscript_self.property("spacerItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("spacerItem") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::spacerItem();
    } else {
        _q_function.setData(QScriptValue(true));
        QSpacerItem* _q_retval = qscriptvalue_cast<QSpacerItem* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QWidget*  QtScriptShell_QWidgetItem::widget()
{
    QScriptValue _q_function = __qtscript_self.property("widget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widget") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QWidgetItem::widget();
    } else {
        _q_function.setData(QScriptValue(true));
        QWidget* _q_retval = qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

