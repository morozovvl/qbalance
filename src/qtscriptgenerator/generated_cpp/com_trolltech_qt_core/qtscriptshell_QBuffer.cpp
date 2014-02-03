#include "qtscriptshell_QBuffer.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbuffer.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QBuffer::QtScriptShell_QBuffer(QByteArray*  buf, QObject*  parent)
    : QBuffer(buf, parent) {}

QtScriptShell_QBuffer::QtScriptShell_QBuffer(QObject*  parent)
    : QBuffer(parent) {}

QtScriptShell_QBuffer::~QtScriptShell_QBuffer() {}

bool  QtScriptShell_QBuffer::atEnd() const
{
    QScriptValue _q_function = __qtscript_self.property("atEnd");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atEnd") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::atEnd();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::bytesAvailable() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesAvailable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesAvailable") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::bytesAvailable();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::bytesToWrite() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesToWrite");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesToWrite") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::bytesToWrite();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QBuffer::canReadLine() const
{
    QScriptValue _q_function = __qtscript_self.property("canReadLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canReadLine") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::canReadLine();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QBuffer::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QBuffer::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QBuffer::close()
{
    QScriptValue _q_function = __qtscript_self.property("close");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("close") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QBuffer::close();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QBuffer::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QBuffer::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QBuffer::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::event(arg__1);
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

bool  QtScriptShell_QBuffer::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::eventFilter(arg__1, arg__2);
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

bool  QtScriptShell_QBuffer::isSequential() const
{
    QScriptValue _q_function = __qtscript_self.property("isSequential");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSequential") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::isSequential();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QBuffer::open(QIODevice::OpenMode  openMode)
{
    QScriptValue _q_function = __qtscript_self.property("open");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("open") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::open(openMode);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, openMode)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::pos() const
{
    QScriptValue _q_function = __qtscript_self.property("pos");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pos") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::pos();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::readData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::readData(data, maxlen);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::readLineData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readLineData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readLineData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::readLineData(data, maxlen);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QBuffer::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::reset();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QBuffer::seek(qint64  off)
{
    QScriptValue _q_function = __qtscript_self.property("seek");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("seek") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::seek(off);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, off)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::size() const
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::size();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QBuffer::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QBuffer::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QBuffer::waitForBytesWritten(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForBytesWritten");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForBytesWritten") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::waitForBytesWritten(msecs);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QBuffer::waitForReadyRead(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForReadyRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForReadyRead") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::waitForReadyRead(msecs);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QBuffer::writeData(const char*  data, qint64  len)
{
    QScriptValue _q_function = __qtscript_self.property("writeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("writeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QBuffer::writeData(data, len);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<char *>(data))
            << qScriptValueFromValue(_q_engine, len)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

