#include "qtscriptshell_QSpacerItem.h"

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

QtScriptShell_QSpacerItem::QtScriptShell_QSpacerItem(int  w, int  h, QSizePolicy::Policy  hData, QSizePolicy::Policy  vData)
    : QSpacerItem(w, h, hData, vData) {}

QtScriptShell_QSpacerItem::~QtScriptShell_QSpacerItem() {}

QSizePolicy::ControlTypes  QtScriptShell_QSpacerItem::controlTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("controlTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("controlTypes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::controlTypes();
    } else {
        _q_function.setData(QScriptValue(true));
        QSizePolicy::ControlTypes _q_retval = qscriptvalue_cast<QSizePolicy::ControlTypes >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

Qt::Orientations  QtScriptShell_QSpacerItem::expandingDirections() const
{
    QScriptValue _q_function = __qtscript_self.property("expandingDirections");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expandingDirections") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::expandingDirections();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::Orientations _q_retval = qscriptvalue_cast<Qt::Orientations >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QSpacerItem::geometry() const
{
    QScriptValue _q_function = __qtscript_self.property("geometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("geometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::geometry();
    } else {
        _q_function.setData(QScriptValue(true));
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSpacerItem::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::hasHeightForWidth();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QSpacerItem::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::heightForWidth(arg__1);
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

void QtScriptShell_QSpacerItem::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSpacerItem::invalidate();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSpacerItem::isEmpty() const
{
    QScriptValue _q_function = __qtscript_self.property("isEmpty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isEmpty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::isEmpty();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QLayout*  QtScriptShell_QSpacerItem::layout()
{
    QScriptValue _q_function = __qtscript_self.property("layout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::layout();
    } else {
        _q_function.setData(QScriptValue(true));
        QLayout* _q_retval = qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSize  QtScriptShell_QSpacerItem::maximumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("maximumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("maximumSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::maximumSize();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QSpacerItem::minimumHeightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("minimumHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::minimumHeightForWidth(arg__1);
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

QSize  QtScriptShell_QSpacerItem::minimumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("minimumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::minimumSize();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSpacerItem::setGeometry(const QRect&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSpacerItem::setGeometry(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QSpacerItem::sizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::sizeHint();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSpacerItem*  QtScriptShell_QSpacerItem::spacerItem()
{
    QScriptValue _q_function = __qtscript_self.property("spacerItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("spacerItem") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::spacerItem();
    } else {
        _q_function.setData(QScriptValue(true));
        QSpacerItem* _q_retval = qscriptvalue_cast<QSpacerItem* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QWidget*  QtScriptShell_QSpacerItem::widget()
{
    QScriptValue _q_function = __qtscript_self.property("widget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widget") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSpacerItem::widget();
    } else {
        _q_function.setData(QScriptValue(true));
        QWidget* _q_retval = qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

