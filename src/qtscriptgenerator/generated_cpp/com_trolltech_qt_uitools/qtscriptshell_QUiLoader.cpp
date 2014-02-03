#include "qtscriptshell_QUiLoader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdir.h>
#include <qiodevice.h>
#include <qlayout.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <quiloader.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QActionGroup*)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QUiLoader::QtScriptShell_QUiLoader(QObject*  parent)
    : QUiLoader(parent) {}

QtScriptShell_QUiLoader::~QtScriptShell_QUiLoader() {}

void QtScriptShell_QUiLoader::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QUiLoader::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QAction*  QtScriptShell_QUiLoader::createAction(QObject*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createAction") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QUiLoader::createAction(parent, name);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QAction* _q_retval = qscriptvalue_cast<QAction* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QActionGroup*  QtScriptShell_QUiLoader::createActionGroup(QObject*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createActionGroup");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createActionGroup") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QUiLoader::createActionGroup(parent, name);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QActionGroup* _q_retval = qscriptvalue_cast<QActionGroup* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QLayout*  QtScriptShell_QUiLoader::createLayout(const QString&  className, QObject*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createLayout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createLayout") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QUiLoader::createLayout(className, parent, name);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QLayout* _q_retval = qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, className)
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QWidget*  QtScriptShell_QUiLoader::createWidget(const QString&  className, QWidget*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createWidget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createWidget") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QUiLoader::createWidget(className, parent, name);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QWidget* _q_retval = qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, className)
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QUiLoader::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QUiLoader::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QUiLoader::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QUiLoader::event(arg__1);
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

bool  QtScriptShell_QUiLoader::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QUiLoader::eventFilter(arg__1, arg__2);
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

void QtScriptShell_QUiLoader::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QUiLoader::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

