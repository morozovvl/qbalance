#include "qtscriptshell_QVBoxLayout.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qboxlayout.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qmargins.h>
#include <qobject.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QLayoutItem*)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QFlags<QSizePolicy::ControlType>)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QSpacerItem*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QVBoxLayout::QtScriptShell_QVBoxLayout()
    : QVBoxLayout() {}

QtScriptShell_QVBoxLayout::QtScriptShell_QVBoxLayout(QWidget*  parent)
    : QVBoxLayout(parent) {}

QtScriptShell_QVBoxLayout::~QtScriptShell_QVBoxLayout() {}

void QtScriptShell_QVBoxLayout::addItem(QLayoutItem*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("addItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addItem") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QVBoxLayout::addItem(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QVBoxLayout::childEvent(QChildEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QVBoxLayout::childEvent(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

QSizePolicy::ControlTypes  QtScriptShell_QVBoxLayout::controlTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("controlTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("controlTypes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::controlTypes();
    } else {
        _q_function.setData(QScriptValue(true));
        QSizePolicy::ControlTypes _q_retval = qscriptvalue_cast<QSizePolicy::ControlTypes >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QVBoxLayout::count() const
{
    QScriptValue _q_function = __qtscript_self.property("count");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("count") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::count();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QVBoxLayout::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QVBoxLayout::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QVBoxLayout::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::event(arg__1);
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

bool  QtScriptShell_QVBoxLayout::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::eventFilter(arg__1, arg__2);
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

Qt::Orientations  QtScriptShell_QVBoxLayout::expandingDirections() const
{
    QScriptValue _q_function = __qtscript_self.property("expandingDirections");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expandingDirections") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::expandingDirections();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::Orientations _q_retval = qscriptvalue_cast<Qt::Orientations >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QVBoxLayout::geometry() const
{
    QScriptValue _q_function = __qtscript_self.property("geometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("geometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::geometry();
    } else {
        _q_function.setData(QScriptValue(true));
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QVBoxLayout::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::hasHeightForWidth();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QVBoxLayout::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::heightForWidth(arg__1);
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

int  QtScriptShell_QVBoxLayout::indexOf(QWidget*  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOf");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOf") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::indexOf(arg__1);
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

void QtScriptShell_QVBoxLayout::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QVBoxLayout::invalidate();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QVBoxLayout::isEmpty() const
{
    QScriptValue _q_function = __qtscript_self.property("isEmpty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isEmpty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::isEmpty();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QLayoutItem*  QtScriptShell_QVBoxLayout::itemAt(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("itemAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::itemAt(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QLayoutItem* _q_retval = qscriptvalue_cast<QLayoutItem* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QLayout*  QtScriptShell_QVBoxLayout::layout()
{
    QScriptValue _q_function = __qtscript_self.property("layout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::layout();
    } else {
        _q_function.setData(QScriptValue(true));
        QLayout* _q_retval = qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSize  QtScriptShell_QVBoxLayout::maximumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("maximumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("maximumSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::maximumSize();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QVBoxLayout::minimumHeightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("minimumHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumHeightForWidth") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::minimumHeightForWidth(arg__1);
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

QSize  QtScriptShell_QVBoxLayout::minimumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("minimumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::minimumSize();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QVBoxLayout::setGeometry(const QRect&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QVBoxLayout::setGeometry(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QVBoxLayout::sizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::sizeHint();
    } else {
        _q_function.setData(QScriptValue(true));
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSpacerItem*  QtScriptShell_QVBoxLayout::spacerItem()
{
    QScriptValue _q_function = __qtscript_self.property("spacerItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("spacerItem") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::spacerItem();
    } else {
        _q_function.setData(QScriptValue(true));
        QSpacerItem* _q_retval = qscriptvalue_cast<QSpacerItem* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QLayoutItem*  QtScriptShell_QVBoxLayout::takeAt(int  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("takeAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("takeAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::takeAt(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QLayoutItem* _q_retval = qscriptvalue_cast<QLayoutItem* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QVBoxLayout::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QVBoxLayout::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QWidget*  QtScriptShell_QVBoxLayout::widget()
{
    QScriptValue _q_function = __qtscript_self.property("widget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widget") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QVBoxLayout::widget();
    } else {
        _q_function.setData(QScriptValue(true));
        QWidget* _q_retval = qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

