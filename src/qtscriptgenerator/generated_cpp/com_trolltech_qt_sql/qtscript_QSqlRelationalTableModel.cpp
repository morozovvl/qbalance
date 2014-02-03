#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqlrelationaltablemodel.h>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <qsqltablemodel.h>
#include <qstringlist.h>
#include <qvector.h>

#include "qtscriptshell_QSqlRelationalTableModel.h"

static const char * const qtscript_QSqlRelationalTableModel_function_names[] = {
    "QSqlRelationalTableModel"
    // static
    // prototype
    , "relation"
    , "relationModel"
    , "setJoinMode"
    , "setRelation"
    , "toString"
};

static const char * const qtscript_QSqlRelationalTableModel_function_signatures[] = {
    "QObject parent, QSqlDatabase db"
    // static
    // prototype
    , "int column"
    , "int column"
    , "JoinMode joinMode"
    , "int column, QSqlRelation relation"
""
};

static const int qtscript_QSqlRelationalTableModel_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 1
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QSqlRelationalTableModel_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QSqlRelationalTableModel : public QSqlRelationalTableModel
{

    friend QScriptValue qtscript_QSqlRelationalTableModel_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QSqlRelationalTableModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlRelationalTableModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlRelationalTableModel*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlRelationalTableModel*)
Q_DECLARE_METATYPE(QSqlRelationalTableModel::JoinMode)
Q_DECLARE_METATYPE(QSqlRelation)
Q_DECLARE_METATYPE(QSqlTableModel*)
Q_DECLARE_METATYPE(QSqlDatabase)

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

//
// QSqlRelationalTableModel::JoinMode
//

static const QSqlRelationalTableModel::JoinMode qtscript_QSqlRelationalTableModel_JoinMode_values[] = {
    QSqlRelationalTableModel::InnerJoin
    , QSqlRelationalTableModel::LeftJoin
};

static const char * const qtscript_QSqlRelationalTableModel_JoinMode_keys[] = {
    "InnerJoin"
    , "LeftJoin"
};

static QString qtscript_QSqlRelationalTableModel_JoinMode_toStringHelper(QSqlRelationalTableModel::JoinMode value)
{
    if ((value >= QSqlRelationalTableModel::InnerJoin) && (value <= QSqlRelationalTableModel::LeftJoin))
        return qtscript_QSqlRelationalTableModel_JoinMode_keys[static_cast<int>(value)-static_cast<int>(QSqlRelationalTableModel::InnerJoin)];
    return QString();
}

static QScriptValue qtscript_QSqlRelationalTableModel_JoinMode_toScriptValue(QScriptEngine *engine, const QSqlRelationalTableModel::JoinMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlRelationalTableModel"));
    return clazz.property(qtscript_QSqlRelationalTableModel_JoinMode_toStringHelper(value));
}

static void qtscript_QSqlRelationalTableModel_JoinMode_fromScriptValue(const QScriptValue &value, QSqlRelationalTableModel::JoinMode &out)
{
    out = qvariant_cast<QSqlRelationalTableModel::JoinMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlRelationalTableModel_JoinMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlRelationalTableModel::InnerJoin) && (arg <= QSqlRelationalTableModel::LeftJoin))
        return qScriptValueFromValue(engine,  static_cast<QSqlRelationalTableModel::JoinMode>(arg));
    return context->throwError(QString::fromLatin1("JoinMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlRelationalTableModel_JoinMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlRelationalTableModel::JoinMode value = qscriptvalue_cast<QSqlRelationalTableModel::JoinMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlRelationalTableModel_JoinMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlRelationalTableModel::JoinMode value = qscriptvalue_cast<QSqlRelationalTableModel::JoinMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlRelationalTableModel_JoinMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlRelationalTableModel_JoinMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlRelationalTableModel_JoinMode,
        qtscript_QSqlRelationalTableModel_JoinMode_valueOf, qtscript_QSqlRelationalTableModel_JoinMode_toString);
    qScriptRegisterMetaType<QSqlRelationalTableModel::JoinMode>(engine, qtscript_QSqlRelationalTableModel_JoinMode_toScriptValue,
        qtscript_QSqlRelationalTableModel_JoinMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlRelationalTableModel_JoinMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlRelationalTableModel_JoinMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlRelationalTableModel
//

static QScriptValue qtscript_QSqlRelationalTableModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QSqlRelationalTableModel* _q_self = reinterpret_cast<qtscript_QSqlRelationalTableModel*>(qscriptvalue_cast<QSqlRelationalTableModel*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlRelationalTableModel.%0(): this object is not a QSqlRelationalTableModel")
            .arg(qtscript_QSqlRelationalTableModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlRelation _q_result = _q_self->relation(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlTableModel* _q_result = _q_self->relationModel(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QSqlRelationalTableModel::JoinMode _q_arg0 = qscriptvalue_cast<QSqlRelationalTableModel::JoinMode>(context->argument(0));
        _q_self->setJoinMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlRelation _q_arg1 = qscriptvalue_cast<QSqlRelation>(context->argument(1));
        _q_self->setRelation(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QSqlRelationalTableModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlRelationalTableModel_throw_ambiguity_error_helper(context,
        qtscript_QSqlRelationalTableModel_function_names[_id+1],
        qtscript_QSqlRelationalTableModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlRelationalTableModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlRelationalTableModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSqlRelationalTableModel* _q_cpp_result = new QtScriptShell_QSqlRelationalTableModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlRelationalTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSqlRelationalTableModel* _q_cpp_result = new QtScriptShell_QSqlRelationalTableModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlRelationalTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QSqlDatabase _q_arg1 = qscriptvalue_cast<QSqlDatabase>(context->argument(1));
        QtScriptShell_QSqlRelationalTableModel* _q_cpp_result = new QtScriptShell_QSqlRelationalTableModel(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlRelationalTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlRelationalTableModel_throw_ambiguity_error_helper(context,
        qtscript_QSqlRelationalTableModel_function_names[_id],
        qtscript_QSqlRelationalTableModel_function_signatures[_id]);
}

static QScriptValue qtscript_QSqlRelationalTableModel_toScriptValue(QScriptEngine *engine, QSqlRelationalTableModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSqlRelationalTableModel_fromScriptValue(const QScriptValue &value, QSqlRelationalTableModel* &out)
{
    out = qobject_cast<QSqlRelationalTableModel*>(value.toQObject());
}

QScriptValue qtscript_create_QSqlRelationalTableModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlRelationalTableModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlRelationalTableModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QSqlTableModel*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlRelationalTableModel_prototype_call, qtscript_QSqlRelationalTableModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlRelationalTableModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSqlRelationalTableModel*>(engine, qtscript_QSqlRelationalTableModel_toScriptValue, 
        qtscript_QSqlRelationalTableModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlRelationalTableModel_static_call, proto, qtscript_QSqlRelationalTableModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("JoinMode"),
        qtscript_create_QSqlRelationalTableModel_JoinMode_class(engine, ctor));
    return ctor;
}
