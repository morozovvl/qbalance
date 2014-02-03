#include "qtscriptshell_QSslSocket.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qsslcertificate.h>
#include <qsslcipher.h>
#include <qsslconfiguration.h>
#include <qsslerror.h>
#include <qsslkey.h>
#include <qsslsocket.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(QAbstractSocket::NetworkLayerProtocol)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(qintptr)
Q_DECLARE_METATYPE(QAbstractSocket::SocketOption)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QSslSocket::QtScriptShell_QSslSocket(QObject*  parent)
    : QSslSocket(parent) {}

QtScriptShell_QSslSocket::~QtScriptShell_QSslSocket() {}

bool  QtScriptShell_QSslSocket::atEnd() const
{
    QScriptValue _q_function = __qtscript_self.property("atEnd");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atEnd") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::atEnd();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QSslSocket::bytesAvailable() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesAvailable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesAvailable") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::bytesAvailable();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QSslSocket::bytesToWrite() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesToWrite");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesToWrite") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::bytesToWrite();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSslSocket::canReadLine() const
{
    QScriptValue _q_function = __qtscript_self.property("canReadLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canReadLine") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::canReadLine();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSslSocket::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSslSocket::close()
{
    QScriptValue _q_function = __qtscript_self.property("close");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("close") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::close();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSslSocket::connectToHost(const QString&  hostName, unsigned short  port, QIODevice::OpenMode  openMode, QAbstractSocket::NetworkLayerProtocol  protocol)
{
    QScriptValue _q_function = __qtscript_self.property("connectToHost");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("connectToHost") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::connectToHost(hostName, port, openMode, protocol);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, hostName)
            << qScriptValueFromValue(_q_engine, port)
            << qScriptValueFromValue(_q_engine, openMode)
            << qScriptValueFromValue(_q_engine, protocol));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSslSocket::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSslSocket::disconnectFromHost()
{
    QScriptValue _q_function = __qtscript_self.property("disconnectFromHost");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("disconnectFromHost") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::disconnectFromHost();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSslSocket::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::event(arg__1);
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

bool  QtScriptShell_QSslSocket::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::eventFilter(arg__1, arg__2);
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

bool  QtScriptShell_QSslSocket::isSequential() const
{
    QScriptValue _q_function = __qtscript_self.property("isSequential");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSequential") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::isSequential();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSslSocket::open(QIODevice::OpenMode  mode)
{
    QScriptValue _q_function = __qtscript_self.property("open");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("open") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::open(mode);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, mode)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QSslSocket::pos() const
{
    QScriptValue _q_function = __qtscript_self.property("pos");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pos") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::pos();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qint64  QtScriptShell_QSslSocket::readData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::readData(data, maxlen);
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

qint64  QtScriptShell_QSslSocket::readLineData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readLineData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readLineData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::readLineData(data, maxlen);
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

bool  QtScriptShell_QSslSocket::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::reset();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSslSocket::resume()
{
    QScriptValue _q_function = __qtscript_self.property("resume");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resume") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::resume();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSslSocket::seek(qint64  pos)
{
    QScriptValue _q_function = __qtscript_self.property("seek");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("seek") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::seek(pos);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pos)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSslSocket::setReadBufferSize(qint64  size)
{
    QScriptValue _q_function = __qtscript_self.property("setReadBufferSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setReadBufferSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::setReadBufferSize(size);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, size));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSslSocket::setSocketDescriptor(qintptr  socketDescriptor, QAbstractSocket::SocketState  state, QIODevice::OpenMode  openMode)
{
    QScriptValue _q_function = __qtscript_self.property("setSocketDescriptor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSocketDescriptor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::setSocketDescriptor(socketDescriptor, state, openMode);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, socketDescriptor)
            << qScriptValueFromValue(_q_engine, state)
            << qScriptValueFromValue(_q_engine, openMode)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSslSocket::setSocketOption(QAbstractSocket::SocketOption  option, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setSocketOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSocketOption") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::setSocketOption(option, value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

qint64  QtScriptShell_QSslSocket::size() const
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::size();
    } else {
        _q_function.setData(QScriptValue(true));
        qint64 _q_retval = qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

qintptr  QtScriptShell_QSslSocket::socketDescriptor() const
{
    QScriptValue _q_function = __qtscript_self.property("socketDescriptor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("socketDescriptor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::socketDescriptor();
    } else {
        _q_function.setData(QScriptValue(true));
        qintptr _q_retval = qscriptvalue_cast<qintptr >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QSslSocket::socketOption(QAbstractSocket::SocketOption  option)
{
    QScriptValue _q_function = __qtscript_self.property("socketOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("socketOption") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::socketOption(option);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSslSocket::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSslSocket::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSslSocket::waitForBytesWritten(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForBytesWritten");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForBytesWritten") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::waitForBytesWritten(msecs);
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

bool  QtScriptShell_QSslSocket::waitForConnected(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForConnected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForConnected") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::waitForConnected(msecs);
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

bool  QtScriptShell_QSslSocket::waitForDisconnected(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForDisconnected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForDisconnected") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::waitForDisconnected(msecs);
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

bool  QtScriptShell_QSslSocket::waitForReadyRead(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForReadyRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForReadyRead") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::waitForReadyRead(msecs);
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

qint64  QtScriptShell_QSslSocket::writeData(const char*  data, qint64  len)
{
    QScriptValue _q_function = __qtscript_self.property("writeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("writeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSslSocket::writeData(data, len);
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

