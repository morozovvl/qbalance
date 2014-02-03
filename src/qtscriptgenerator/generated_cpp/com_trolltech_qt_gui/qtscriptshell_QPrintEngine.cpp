#include "qtscriptshell_QPrintEngine.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPrinter::PrinterState)
Q_DECLARE_METATYPE(QPrintEngine::PrintEnginePropertyKey)

QtScriptShell_QPrintEngine::QtScriptShell_QPrintEngine()
    : QPrintEngine() {}

QtScriptShell_QPrintEngine::~QtScriptShell_QPrintEngine() {}

bool  QtScriptShell_QPrintEngine::abort()
{
    QScriptValue _q_function = __qtscript_self.property("abort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("abort") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QPrintEngine::abort() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QPrintEngine::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QPrintEngine::metric() is abstract!");
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

bool  QtScriptShell_QPrintEngine::newPage()
{
    QScriptValue _q_function = __qtscript_self.property("newPage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("newPage") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QPrintEngine::newPage() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QPrinter::PrinterState  QtScriptShell_QPrintEngine::printerState() const
{
    QScriptValue _q_function = __qtscript_self.property("printerState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("printerState") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QPrintEngine::printerState() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QPrinter::PrinterState _q_retval = qscriptvalue_cast<QPrinter::PrinterState >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QPrintEngine::property(QPrintEngine::PrintEnginePropertyKey  key) const
{
    QScriptValue _q_function = __qtscript_self.property("property");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("property") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QPrintEngine::property() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, key)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QPrintEngine::setProperty(QPrintEngine::PrintEnginePropertyKey  key, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setProperty") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QPrintEngine::setProperty() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, key)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

