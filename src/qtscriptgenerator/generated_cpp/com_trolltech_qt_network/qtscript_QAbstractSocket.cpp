#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractsocket.h>
#include <QVariant>
#include <qabstractsocket.h>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>

#include "qtscriptshell_QAbstractSocket.h"

static const char * const qtscript_QAbstractSocket_function_names[] = {
    "QAbstractSocket"
    // static
    // prototype
    , "abort"
    , "bind"
    , "connectToHost"
    , "disconnectFromHost"
    , "flush"
    , "getError"
    , "isValid"
    , "localAddress"
    , "localPort"
    , "pauseMode"
    , "peerAddress"
    , "peerName"
    , "peerPort"
    , "proxy"
    , "readBufferSize"
    , "resume"
    , "setLocalAddress"
    , "setLocalPort"
    , "setPauseMode"
    , "setPeerAddress"
    , "setPeerName"
    , "setPeerPort"
    , "setProxy"
    , "setReadBufferSize"
    , "setSocketDescriptor"
    , "setSocketError"
    , "setSocketOption"
    , "setSocketState"
    , "socketDescriptor"
    , "socketOption"
    , "socketType"
    , "state"
    , "waitForConnected"
    , "waitForDisconnected"
    , "toString"
};

static const char * const qtscript_QAbstractSocket_function_signatures[] = {
    "SocketType socketType, QObject parent"
    // static
    // prototype
    , ""
    , "QHostAddress address, unsigned short port, BindMode mode\nunsigned short port, BindMode mode"
    , "QHostAddress address, unsigned short port, OpenMode mode\nString hostName, unsigned short port, OpenMode mode, NetworkLayerProtocol protocol"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QHostAddress address"
    , "unsigned short port"
    , "PauseModes pauseMode"
    , "QHostAddress address"
    , "String name"
    , "unsigned short port"
    , "QNetworkProxy networkProxy"
    , "qint64 size"
    , "qintptr socketDescriptor, SocketState state, OpenMode openMode"
    , "SocketError socketError"
    , "SocketOption option, Object value"
    , "SocketState state"
    , ""
    , "SocketOption option"
    , ""
    , ""
    , "int msecs"
    , "int msecs"
""
};

static const int qtscript_QAbstractSocket_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 3
    , 4
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 3
    , 1
    , 2
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractSocket_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QAbstractSocket : public QAbstractSocket
{
    friend QScriptValue qtscript_QAbstractSocket_setLocalAddress(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractSocket_setLocalPort(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractSocket_setPeerAddress(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractSocket_setPeerName(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractSocket_setPeerPort(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractSocket_setSocketError(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractSocket_setSocketState(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QAbstractSocket_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QAbstractSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QAbstractSocket_metaObject()
{
    return &QAbstractSocket::staticMetaObject;
}

Q_DECLARE_METATYPE(QAbstractSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractSocket*)
Q_DECLARE_METATYPE(QAbstractSocket::NetworkLayerProtocol)
Q_DECLARE_METATYPE(QAbstractSocket::SocketOption)
Q_DECLARE_METATYPE(QAbstractSocket::PauseMode)
Q_DECLARE_METATYPE(QFlags<QAbstractSocket::PauseMode>)
Q_DECLARE_METATYPE(QAbstractSocket::SocketType)
Q_DECLARE_METATYPE(QAbstractSocket::BindFlag)
Q_DECLARE_METATYPE(QFlags<QAbstractSocket::BindFlag>)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(qintptr)
Q_DECLARE_METATYPE(QIODevice*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QAbstractSocket::SocketState
//

static const QAbstractSocket::SocketState qtscript_QAbstractSocket_SocketState_values[] = {
    QAbstractSocket::UnconnectedState
    , QAbstractSocket::HostLookupState
    , QAbstractSocket::ConnectingState
    , QAbstractSocket::ConnectedState
    , QAbstractSocket::BoundState
    , QAbstractSocket::ListeningState
    , QAbstractSocket::ClosingState
};

static const char * const qtscript_QAbstractSocket_SocketState_keys[] = {
    "UnconnectedState"
    , "HostLookupState"
    , "ConnectingState"
    , "ConnectedState"
    , "BoundState"
    , "ListeningState"
    , "ClosingState"
};

static QString qtscript_QAbstractSocket_SocketState_toStringHelper(QAbstractSocket::SocketState value)
{
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketState_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketState_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketState_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketState &out)
{
    out = qvariant_cast<QAbstractSocket::SocketState>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketState>(arg));
    return context->throwError(QString::fromLatin1("SocketState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketState value = qscriptvalue_cast<QAbstractSocket::SocketState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketState_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketState value = qscriptvalue_cast<QAbstractSocket::SocketState>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketState_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketState,
        qtscript_QAbstractSocket_SocketState_valueOf, qtscript_QAbstractSocket_SocketState_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketState>(engine, qtscript_QAbstractSocket_SocketState_toScriptValue,
        qtscript_QAbstractSocket_SocketState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::SocketError
//

static const QAbstractSocket::SocketError qtscript_QAbstractSocket_SocketError_values[] = {
    QAbstractSocket::UnknownSocketError
    , QAbstractSocket::ConnectionRefusedError
    , QAbstractSocket::RemoteHostClosedError
    , QAbstractSocket::HostNotFoundError
    , QAbstractSocket::SocketAccessError
    , QAbstractSocket::SocketResourceError
    , QAbstractSocket::SocketTimeoutError
    , QAbstractSocket::DatagramTooLargeError
    , QAbstractSocket::NetworkError
    , QAbstractSocket::AddressInUseError
    , QAbstractSocket::SocketAddressNotAvailableError
    , QAbstractSocket::UnsupportedSocketOperationError
    , QAbstractSocket::UnfinishedSocketOperationError
    , QAbstractSocket::ProxyAuthenticationRequiredError
    , QAbstractSocket::SslHandshakeFailedError
    , QAbstractSocket::ProxyConnectionRefusedError
    , QAbstractSocket::ProxyConnectionClosedError
    , QAbstractSocket::ProxyConnectionTimeoutError
    , QAbstractSocket::ProxyNotFoundError
    , QAbstractSocket::ProxyProtocolError
    , QAbstractSocket::OperationError
    , QAbstractSocket::SslInternalError
    , QAbstractSocket::SslInvalidUserDataError
    , QAbstractSocket::TemporaryError
};

static const char * const qtscript_QAbstractSocket_SocketError_keys[] = {
    "UnknownSocketError"
    , "ConnectionRefusedError"
    , "RemoteHostClosedError"
    , "HostNotFoundError"
    , "SocketAccessError"
    , "SocketResourceError"
    , "SocketTimeoutError"
    , "DatagramTooLargeError"
    , "NetworkError"
    , "AddressInUseError"
    , "SocketAddressNotAvailableError"
    , "UnsupportedSocketOperationError"
    , "UnfinishedSocketOperationError"
    , "ProxyAuthenticationRequiredError"
    , "SslHandshakeFailedError"
    , "ProxyConnectionRefusedError"
    , "ProxyConnectionClosedError"
    , "ProxyConnectionTimeoutError"
    , "ProxyNotFoundError"
    , "ProxyProtocolError"
    , "OperationError"
    , "SslInternalError"
    , "SslInvalidUserDataError"
    , "TemporaryError"
};

static QString qtscript_QAbstractSocket_SocketError_toStringHelper(QAbstractSocket::SocketError value)
{
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketError");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketError_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketError_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketError_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketError &out)
{
    out = qvariant_cast<QAbstractSocket::SocketError>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketError");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketError>(arg));
    return context->throwError(QString::fromLatin1("SocketError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketError value = qscriptvalue_cast<QAbstractSocket::SocketError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketError value = qscriptvalue_cast<QAbstractSocket::SocketError>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketError_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketError,
        qtscript_QAbstractSocket_SocketError_valueOf, qtscript_QAbstractSocket_SocketError_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketError>(engine, qtscript_QAbstractSocket_SocketError_toScriptValue,
        qtscript_QAbstractSocket_SocketError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 24; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::NetworkLayerProtocol
//

static const QAbstractSocket::NetworkLayerProtocol qtscript_QAbstractSocket_NetworkLayerProtocol_values[] = {
    QAbstractSocket::UnknownNetworkLayerProtocol
    , QAbstractSocket::IPv4Protocol
    , QAbstractSocket::IPv6Protocol
    , QAbstractSocket::AnyIPProtocol
};

static const char * const qtscript_QAbstractSocket_NetworkLayerProtocol_keys[] = {
    "UnknownNetworkLayerProtocol"
    , "IPv4Protocol"
    , "IPv6Protocol"
    , "AnyIPProtocol"
};

static QString qtscript_QAbstractSocket_NetworkLayerProtocol_toStringHelper(QAbstractSocket::NetworkLayerProtocol value)
{
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("NetworkLayerProtocol");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSocket_NetworkLayerProtocol_toScriptValue(QScriptEngine *engine, const QAbstractSocket::NetworkLayerProtocol &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_NetworkLayerProtocol_toStringHelper(value));
}

static void qtscript_QAbstractSocket_NetworkLayerProtocol_fromScriptValue(const QScriptValue &value, QAbstractSocket::NetworkLayerProtocol &out)
{
    out = qvariant_cast<QAbstractSocket::NetworkLayerProtocol>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_NetworkLayerProtocol(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("NetworkLayerProtocol");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::NetworkLayerProtocol>(arg));
    return context->throwError(QString::fromLatin1("NetworkLayerProtocol(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_NetworkLayerProtocol_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::NetworkLayerProtocol value = qscriptvalue_cast<QAbstractSocket::NetworkLayerProtocol>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_NetworkLayerProtocol_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::NetworkLayerProtocol value = qscriptvalue_cast<QAbstractSocket::NetworkLayerProtocol>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_NetworkLayerProtocol_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_NetworkLayerProtocol_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_NetworkLayerProtocol,
        qtscript_QAbstractSocket_NetworkLayerProtocol_valueOf, qtscript_QAbstractSocket_NetworkLayerProtocol_toString);
    qScriptRegisterMetaType<QAbstractSocket::NetworkLayerProtocol>(engine, qtscript_QAbstractSocket_NetworkLayerProtocol_toScriptValue,
        qtscript_QAbstractSocket_NetworkLayerProtocol_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_NetworkLayerProtocol_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_NetworkLayerProtocol_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::SocketOption
//

static const QAbstractSocket::SocketOption qtscript_QAbstractSocket_SocketOption_values[] = {
    QAbstractSocket::LowDelayOption
    , QAbstractSocket::KeepAliveOption
    , QAbstractSocket::MulticastTtlOption
    , QAbstractSocket::MulticastLoopbackOption
    , QAbstractSocket::TypeOfServiceOption
};

static const char * const qtscript_QAbstractSocket_SocketOption_keys[] = {
    "LowDelayOption"
    , "KeepAliveOption"
    , "MulticastTtlOption"
    , "MulticastLoopbackOption"
    , "TypeOfServiceOption"
};

static QString qtscript_QAbstractSocket_SocketOption_toStringHelper(QAbstractSocket::SocketOption value)
{
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketOption_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketOption_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketOption_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketOption &out)
{
    out = qvariant_cast<QAbstractSocket::SocketOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketOption>(arg));
    return context->throwError(QString::fromLatin1("SocketOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketOption value = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketOption value = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketOption,
        qtscript_QAbstractSocket_SocketOption_valueOf, qtscript_QAbstractSocket_SocketOption_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketOption>(engine, qtscript_QAbstractSocket_SocketOption_toScriptValue,
        qtscript_QAbstractSocket_SocketOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::PauseMode
//

static const QAbstractSocket::PauseMode qtscript_QAbstractSocket_PauseMode_values[] = {
    QAbstractSocket::PauseNever
    , QAbstractSocket::PauseOnSslErrors
};

static const char * const qtscript_QAbstractSocket_PauseMode_keys[] = {
    "PauseNever"
    , "PauseOnSslErrors"
};

static QString qtscript_QAbstractSocket_PauseMode_toStringHelper(QAbstractSocket::PauseMode value)
{
    if ((value >= QAbstractSocket::PauseNever) && (value <= QAbstractSocket::PauseOnSslErrors))
        return qtscript_QAbstractSocket_PauseMode_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::PauseNever)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_PauseMode_toScriptValue(QScriptEngine *engine, const QAbstractSocket::PauseMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_PauseMode_toStringHelper(value));
}

static void qtscript_QAbstractSocket_PauseMode_fromScriptValue(const QScriptValue &value, QAbstractSocket::PauseMode &out)
{
    out = qvariant_cast<QAbstractSocket::PauseMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_PauseMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::PauseNever) && (arg <= QAbstractSocket::PauseOnSslErrors))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::PauseMode>(arg));
    return context->throwError(QString::fromLatin1("PauseMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_PauseMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseMode value = qscriptvalue_cast<QAbstractSocket::PauseMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_PauseMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseMode value = qscriptvalue_cast<QAbstractSocket::PauseMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_PauseMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_PauseMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_PauseMode,
        qtscript_QAbstractSocket_PauseMode_valueOf, qtscript_QAbstractSocket_PauseMode_toString);
    qScriptRegisterMetaType<QAbstractSocket::PauseMode>(engine, qtscript_QAbstractSocket_PauseMode_toScriptValue,
        qtscript_QAbstractSocket_PauseMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_PauseMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_PauseMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::PauseModes
//

static QScriptValue qtscript_QAbstractSocket_PauseModes_toScriptValue(QScriptEngine *engine, const QAbstractSocket::PauseModes &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAbstractSocket_PauseModes_fromScriptValue(const QScriptValue &value, QAbstractSocket::PauseModes &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAbstractSocket::PauseModes>())
        out = qvariant_cast<QAbstractSocket::PauseModes>(var);
    else if (var.userType() == qMetaTypeId<QAbstractSocket::PauseMode>())
        out = qvariant_cast<QAbstractSocket::PauseMode>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAbstractSocket_PauseModes(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseModes result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAbstractSocket::PauseModes>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAbstractSocket::PauseMode>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("PauseModes(): argument %0 is not of type PauseMode").arg(i));
            }
            result |= qvariant_cast<QAbstractSocket::PauseMode>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAbstractSocket_PauseModes_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseModes value = qscriptvalue_cast<QAbstractSocket::PauseModes>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_PauseModes_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseModes value = qscriptvalue_cast<QAbstractSocket::PauseModes>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QAbstractSocket_PauseMode_values[i]) == qtscript_QAbstractSocket_PauseMode_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAbstractSocket_PauseMode_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAbstractSocket_PauseModes_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAbstractSocket::PauseModes>() == otherObj.value<QAbstractSocket::PauseModes>())));
}

static QScriptValue qtscript_create_QAbstractSocket_PauseModes_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAbstractSocket_PauseModes, qtscript_QAbstractSocket_PauseModes_valueOf,
        qtscript_QAbstractSocket_PauseModes_toString, qtscript_QAbstractSocket_PauseModes_equals);
    qScriptRegisterMetaType<QAbstractSocket::PauseModes>(engine, qtscript_QAbstractSocket_PauseModes_toScriptValue,
        qtscript_QAbstractSocket_PauseModes_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAbstractSocket::SocketType
//

static const QAbstractSocket::SocketType qtscript_QAbstractSocket_SocketType_values[] = {
    QAbstractSocket::UnknownSocketType
    , QAbstractSocket::TcpSocket
    , QAbstractSocket::UdpSocket
};

static const char * const qtscript_QAbstractSocket_SocketType_keys[] = {
    "UnknownSocketType"
    , "TcpSocket"
    , "UdpSocket"
};

static QString qtscript_QAbstractSocket_SocketType_toStringHelper(QAbstractSocket::SocketType value)
{
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketType_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketType_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketType &out)
{
    out = qvariant_cast<QAbstractSocket::SocketType>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSocket_metaObject();
    int idx = meta->indexOfEnumerator("SocketType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketType>(arg));
    return context->throwError(QString::fromLatin1("SocketType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketType value = qscriptvalue_cast<QAbstractSocket::SocketType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketType value = qscriptvalue_cast<QAbstractSocket::SocketType>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketType_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketType,
        qtscript_QAbstractSocket_SocketType_valueOf, qtscript_QAbstractSocket_SocketType_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketType>(engine, qtscript_QAbstractSocket_SocketType_toScriptValue,
        qtscript_QAbstractSocket_SocketType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::BindFlag
//

static const QAbstractSocket::BindFlag qtscript_QAbstractSocket_BindFlag_values[] = {
    QAbstractSocket::DefaultForPlatform
    , QAbstractSocket::ShareAddress
    , QAbstractSocket::DontShareAddress
    , QAbstractSocket::ReuseAddressHint
};

static const char * const qtscript_QAbstractSocket_BindFlag_keys[] = {
    "DefaultForPlatform"
    , "ShareAddress"
    , "DontShareAddress"
    , "ReuseAddressHint"
};

static QString qtscript_QAbstractSocket_BindFlag_toStringHelper(QAbstractSocket::BindFlag value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QAbstractSocket_BindFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QAbstractSocket_BindFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_BindFlag_toScriptValue(QScriptEngine *engine, const QAbstractSocket::BindFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_BindFlag_toStringHelper(value));
}

static void qtscript_QAbstractSocket_BindFlag_fromScriptValue(const QScriptValue &value, QAbstractSocket::BindFlag &out)
{
    out = qvariant_cast<QAbstractSocket::BindFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_BindFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QAbstractSocket_BindFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::BindFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("BindFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_BindFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::BindFlag value = qscriptvalue_cast<QAbstractSocket::BindFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_BindFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::BindFlag value = qscriptvalue_cast<QAbstractSocket::BindFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_BindFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_BindFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_BindFlag,
        qtscript_QAbstractSocket_BindFlag_valueOf, qtscript_QAbstractSocket_BindFlag_toString);
    qScriptRegisterMetaType<QAbstractSocket::BindFlag>(engine, qtscript_QAbstractSocket_BindFlag_toScriptValue,
        qtscript_QAbstractSocket_BindFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_BindFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_BindFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::BindMode
//

static QScriptValue qtscript_QAbstractSocket_BindMode_toScriptValue(QScriptEngine *engine, const QAbstractSocket::BindMode &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAbstractSocket_BindMode_fromScriptValue(const QScriptValue &value, QAbstractSocket::BindMode &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAbstractSocket::BindMode>())
        out = qvariant_cast<QAbstractSocket::BindMode>(var);
    else if (var.userType() == qMetaTypeId<QAbstractSocket::BindFlag>())
        out = qvariant_cast<QAbstractSocket::BindFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAbstractSocket_BindMode(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::BindMode result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAbstractSocket::BindMode>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAbstractSocket::BindFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("BindMode(): argument %0 is not of type BindFlag").arg(i));
            }
            result |= qvariant_cast<QAbstractSocket::BindFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAbstractSocket_BindMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::BindMode value = qscriptvalue_cast<QAbstractSocket::BindMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_BindMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::BindMode value = qscriptvalue_cast<QAbstractSocket::BindMode>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QAbstractSocket_BindFlag_values[i]) == qtscript_QAbstractSocket_BindFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAbstractSocket_BindFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAbstractSocket_BindMode_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAbstractSocket::BindMode>() == otherObj.value<QAbstractSocket::BindMode>())));
}

static QScriptValue qtscript_create_QAbstractSocket_BindMode_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAbstractSocket_BindMode, qtscript_QAbstractSocket_BindMode_valueOf,
        qtscript_QAbstractSocket_BindMode_toString, qtscript_QAbstractSocket_BindMode_equals);
    qScriptRegisterMetaType<QAbstractSocket::BindMode>(engine, qtscript_QAbstractSocket_BindMode_toScriptValue,
        qtscript_QAbstractSocket_BindMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAbstractSocket
//

static QScriptValue qtscript_QAbstractSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 34;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QAbstractSocket* _q_self = reinterpret_cast<qtscript_QAbstractSocket*>(qscriptvalue_cast<QAbstractSocket*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractSocket.%0(): this object is not a QAbstractSocket")
            .arg(qtscript_QAbstractSocket_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->abort();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->bind();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            bool _q_result = _q_self->bind(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
            bool _q_result = _q_self->bind(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            bool _q_result = _q_self->bind(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QFlags<QAbstractSocket::BindFlag> >() == context->argument(1).toVariant().userType())) {
            unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
            QFlags<QAbstractSocket::BindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QAbstractSocket::BindFlag> >(context->argument(1));
            bool _q_result = _q_self->bind(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        QFlags<QAbstractSocket::BindFlag> _q_arg2 = qscriptvalue_cast<QFlags<QAbstractSocket::BindFlag> >(context->argument(2));
        bool _q_result = _q_self->bind(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            _q_self->connectToHost(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            _q_self->connectToHost(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
        QAbstractSocket::NetworkLayerProtocol _q_arg3 = qscriptvalue_cast<QAbstractSocket::NetworkLayerProtocol>(context->argument(3));
        _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->disconnectFromHost();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->flush();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->localAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->localPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QFlags<QAbstractSocket::PauseMode> _q_result = _q_self->pauseMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->peerAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->peerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->peerPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QNetworkProxy _q_result = _q_self->proxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->readBufferSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        _q_self->resume();
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        _q_self->setLocalAddress(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
        _q_self->setLocalPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QFlags<QAbstractSocket::PauseMode> _q_arg0 = qscriptvalue_cast<QFlags<QAbstractSocket::PauseMode> >(context->argument(0));
        _q_self->setPauseMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        _q_self->setPeerAddress(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPeerName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
        _q_self->setPeerPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QNetworkProxy _q_arg0 = qscriptvalue_cast<QNetworkProxy>(context->argument(0));
        _q_self->setProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setReadBufferSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        qintptr _q_arg0 = qscriptvalue_cast<qintptr>(context->argument(0));
        bool _q_result = _q_self->setSocketDescriptor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qintptr _q_arg0 = qscriptvalue_cast<qintptr>(context->argument(0));
        QAbstractSocket::SocketState _q_arg1 = qscriptvalue_cast<QAbstractSocket::SocketState>(context->argument(1));
        bool _q_result = _q_self->setSocketDescriptor(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        qintptr _q_arg0 = qscriptvalue_cast<qintptr>(context->argument(0));
        QAbstractSocket::SocketState _q_arg1 = qscriptvalue_cast<QAbstractSocket::SocketState>(context->argument(1));
        QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
        bool _q_result = _q_self->setSocketDescriptor(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QAbstractSocket::SocketError _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketError>(context->argument(0));
        _q_self->setSocketError(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 2) {
        QAbstractSocket::SocketOption _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setSocketOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QAbstractSocket::SocketState _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketState>(context->argument(0));
        _q_self->setSocketState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        qintptr _q_result = _q_self->socketDescriptor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QAbstractSocket::SocketOption _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->argument(0));
        QVariant _q_result = _q_self->socketOption(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketType _q_result = _q_self->socketType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketState _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForConnected();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForConnected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForDisconnected();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForDisconnected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34: {
    QString result = QString::fromLatin1("QAbstractSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSocket_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSocket_function_names[_id+1],
        qtscript_QAbstractSocket_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QAbstractSocket::SocketType _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketType>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QAbstractSocket* _q_cpp_result = new QtScriptShell_QAbstractSocket(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSocket_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSocket_function_names[_id],
        qtscript_QAbstractSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractSocket_toScriptValue(QScriptEngine *engine, QAbstractSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractSocket_fromScriptValue(const QScriptValue &value, QAbstractSocket* &out)
{
    out = qobject_cast<QAbstractSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 35; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractSocket_prototype_call, qtscript_QAbstractSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractSocket*>(engine, qtscript_QAbstractSocket_toScriptValue, 
        qtscript_QAbstractSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractSocket_static_call, proto, qtscript_QAbstractSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SocketState"),
        qtscript_create_QAbstractSocket_SocketState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketError"),
        qtscript_create_QAbstractSocket_SocketError_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NetworkLayerProtocol"),
        qtscript_create_QAbstractSocket_NetworkLayerProtocol_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketOption"),
        qtscript_create_QAbstractSocket_SocketOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PauseMode"),
        qtscript_create_QAbstractSocket_PauseMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PauseModes"),
        qtscript_create_QAbstractSocket_PauseModes_class(engine));
    ctor.setProperty(QString::fromLatin1("SocketType"),
        qtscript_create_QAbstractSocket_SocketType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BindFlag"),
        qtscript_create_QAbstractSocket_BindFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BindMode"),
        qtscript_create_QAbstractSocket_BindMode_class(engine));
    return ctor;
}
