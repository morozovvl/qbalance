#include "qtscriptshell_QGLContext.h"

#include <QtScript/QScriptEngine>
#include <QThread>
#include <QVariant>
#include <qcolor.h>
#include <qgl.h>
#include <qpaintdevice.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QGLContext*)

QtScriptShell_QGLContext::QtScriptShell_QGLContext(const QGLFormat&  format)
    : QGLContext(format) {}

QtScriptShell_QGLContext::QtScriptShell_QGLContext(const QGLFormat&  format, QPaintDevice*  device)
    : QGLContext(format, device) {}

QtScriptShell_QGLContext::~QtScriptShell_QGLContext() {}

bool  QtScriptShell_QGLContext::chooseContext(const QGLContext*  shareContext)
{
    QScriptValue _q_function = __qtscript_self.property("chooseContext");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("chooseContext") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGLContext::chooseContext(shareContext);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QGLContext *>(shareContext))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QGLContext::create(const QGLContext*  shareContext)
{
    QScriptValue _q_function = __qtscript_self.property("create");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("create") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QGLContext::create(shareContext);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QGLContext *>(shareContext))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QGLContext::doneCurrent()
{
    QScriptValue _q_function = __qtscript_self.property("doneCurrent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doneCurrent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGLContext::doneCurrent();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGLContext::makeCurrent()
{
    QScriptValue _q_function = __qtscript_self.property("makeCurrent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("makeCurrent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGLContext::makeCurrent();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QGLContext::swapBuffers() const
{
    QScriptValue _q_function = __qtscript_self.property("swapBuffers");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("swapBuffers") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QGLContext::swapBuffers();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

