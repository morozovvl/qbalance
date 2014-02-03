#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qlocalserver.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocalserver.h>
#include <qlocalsocket.h>
#include <qobject.h>

#include "qtscriptshell_QLocalServer.h"

static const char * const qtscript_QLocalServer_function_names[] = {
    "QLocalServer"
    // static
    , "removeServer"
    // prototype
    , "close"
    , "errorString"
    , "fullServerName"
    , "hasPendingConnections"
    , "incomingConnection"
    , "isListening"
    , "listen"
    , "maxPendingConnections"
    , "nextPendingConnection"
    , "serverError"
    , "serverName"
    , "setMaxPendingConnections"
    , "waitForNewConnection"
    , "toString"
};

static const char * const qtscript_QLocalServer_function_signatures[] = {
    "QObject parent"
    // static
    , "String name"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "quintptr socketDescriptor"
    , ""
    , "String name\nqintptr socketDescriptor"
    , ""
    , ""
    , ""
    , ""
    , "int numConnections"
    , "int msec"
""
};

static const int qtscript_QLocalServer_function_lengths[] = {
    1
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QLocalServer_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QLocalServer : public QLocalServer
{
    friend QScriptValue qtscript_QLocalServer_incomingConnection(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QLocalServer_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QLocalServer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLocalServer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLocalServer*)
Q_DECLARE_METATYPE(QtScriptShell_QLocalServer*)
Q_DECLARE_METATYPE(QLocalServer::SocketOption)
Q_DECLARE_METATYPE(QFlags<QLocalServer::SocketOption>)
Q_DECLARE_METATYPE(quintptr)
Q_DECLARE_METATYPE(qintptr)
Q_DECLARE_METATYPE(QLocalSocket*)

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
// QLocalServer::SocketOption
//

static const QLocalServer::SocketOption qtscript_QLocalServer_SocketOption_values[] = {
    QLocalServer::NoOptions
    , QLocalServer::UserAccessOption
    , QLocalServer::GroupAccessOption
    , QLocalServer::OtherAccessOption
    , QLocalServer::WorldAccessOption
};

static const char * const qtscript_QLocalServer_SocketOption_keys[] = {
    "NoOptions"
    , "UserAccessOption"
    , "GroupAccessOption"
    , "OtherAccessOption"
    , "WorldAccessOption"
};

static QString qtscript_QLocalServer_SocketOption_toStringHelper(QLocalServer::SocketOption value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QLocalServer_SocketOption_values[i] == value)
            return QString::fromLatin1(qtscript_QLocalServer_SocketOption_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QLocalServer_SocketOption_toScriptValue(QScriptEngine *engine, const QLocalServer::SocketOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocalServer"));
    return clazz.property(qtscript_QLocalServer_SocketOption_toStringHelper(value));
}

static void qtscript_QLocalServer_SocketOption_fromScriptValue(const QScriptValue &value, QLocalServer::SocketOption &out)
{
    out = qvariant_cast<QLocalServer::SocketOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocalServer_SocketOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QLocalServer_SocketOption_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QLocalServer::SocketOption>(arg));
    }
    return context->throwError(QString::fromLatin1("SocketOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocalServer_SocketOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocalServer::SocketOption value = qscriptvalue_cast<QLocalServer::SocketOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocalServer_SocketOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocalServer::SocketOption value = qscriptvalue_cast<QLocalServer::SocketOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocalServer_SocketOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocalServer_SocketOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocalServer_SocketOption,
        qtscript_QLocalServer_SocketOption_valueOf, qtscript_QLocalServer_SocketOption_toString);
    qScriptRegisterMetaType<QLocalServer::SocketOption>(engine, qtscript_QLocalServer_SocketOption_toScriptValue,
        qtscript_QLocalServer_SocketOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocalServer_SocketOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocalServer_SocketOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocalServer::SocketOptions
//

static QScriptValue qtscript_QLocalServer_SocketOptions_toScriptValue(QScriptEngine *engine, const QLocalServer::SocketOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QLocalServer_SocketOptions_fromScriptValue(const QScriptValue &value, QLocalServer::SocketOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QLocalServer::SocketOptions>())
        out = qvariant_cast<QLocalServer::SocketOptions>(var);
    else if (var.userType() == qMetaTypeId<QLocalServer::SocketOption>())
        out = qvariant_cast<QLocalServer::SocketOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QLocalServer_SocketOptions(QScriptContext *context, QScriptEngine *engine)
{
    QLocalServer::SocketOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QLocalServer::SocketOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QLocalServer::SocketOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("SocketOptions(): argument %0 is not of type SocketOption").arg(i));
            }
            result |= qvariant_cast<QLocalServer::SocketOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QLocalServer_SocketOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocalServer::SocketOptions value = qscriptvalue_cast<QLocalServer::SocketOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocalServer_SocketOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocalServer::SocketOptions value = qscriptvalue_cast<QLocalServer::SocketOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QLocalServer_SocketOption_values[i]) == qtscript_QLocalServer_SocketOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QLocalServer_SocketOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QLocalServer_SocketOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QLocalServer::SocketOptions>() == otherObj.value<QLocalServer::SocketOptions>())));
}

static QScriptValue qtscript_create_QLocalServer_SocketOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QLocalServer_SocketOptions, qtscript_QLocalServer_SocketOptions_valueOf,
        qtscript_QLocalServer_SocketOptions_toString, qtscript_QLocalServer_SocketOptions_equals);
    qScriptRegisterMetaType<QLocalServer::SocketOptions>(engine, qtscript_QLocalServer_SocketOptions_toScriptValue,
        qtscript_QLocalServer_SocketOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QLocalServer
//

static QScriptValue qtscript_QLocalServer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QLocalServer* _q_self = reinterpret_cast<qtscript_QLocalServer*>(qscriptvalue_cast<QLocalServer*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLocalServer.%0(): this object is not a QLocalServer")
            .arg(qtscript_QLocalServer_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->close();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fullServerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPendingConnections();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        quintptr _q_arg0 = qscriptvalue_cast<quintptr>(context->argument(0));
        _q_self->incomingConnection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isListening();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->listen(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qintptr>() == context->argument(0).toVariant().userType())) {
            qintptr _q_arg0 = qscriptvalue_cast<qintptr>(context->argument(0));
            bool _q_result = _q_self->listen(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->maxPendingConnections();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QLocalSocket* _q_result = _q_self->nextPendingConnection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketError _q_result = _q_self->serverError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->serverName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setMaxPendingConnections(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForNewConnection();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForNewConnection(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QLocalServer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocalServer_throw_ambiguity_error_helper(context,
        qtscript_QLocalServer_function_names[_id+2],
        qtscript_QLocalServer_function_signatures[_id+2]);
}

static QScriptValue qtscript_QLocalServer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLocalServer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLocalServer* _q_cpp_result = new QtScriptShell_QLocalServer();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLocalServer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QLocalServer* _q_cpp_result = new QtScriptShell_QLocalServer(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLocalServer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QLocalServer::removeServer(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocalServer_throw_ambiguity_error_helper(context,
        qtscript_QLocalServer_function_names[_id],
        qtscript_QLocalServer_function_signatures[_id]);
}

static QScriptValue qtscript_QLocalServer_toScriptValue(QScriptEngine *engine, QLocalServer* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLocalServer_fromScriptValue(const QScriptValue &value, QLocalServer* &out)
{
    out = qobject_cast<QLocalServer*>(value.toQObject());
}

QScriptValue qtscript_create_QLocalServer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLocalServer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLocalServer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocalServer_prototype_call, qtscript_QLocalServer_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLocalServer_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLocalServer*>(engine, qtscript_QLocalServer_toScriptValue, 
        qtscript_QLocalServer_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLocalServer_static_call, proto, qtscript_QLocalServer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocalServer_static_call,
            qtscript_QLocalServer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLocalServer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("SocketOption"),
        qtscript_create_QLocalServer_SocketOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketOptions"),
        qtscript_create_QLocalServer_SocketOptions_class(engine));
    return ctor;
}
