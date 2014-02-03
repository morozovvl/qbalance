#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqlresult.h>
#include <QSize>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlrecord.h>
#include <qsqlresult.h>
#include <qvector.h>

#include "qtscriptshell_QSqlResult.h"

static const char * const qtscript_QSqlResult_function_names[] = {
    "QSqlResult"
    // static
    // prototype
    , "addBindValue"
    , "at"
    , "bindValue"
    , "bindValueType"
    , "bindingSyntax"
    , "boundValue"
    , "boundValueCount"
    , "boundValueName"
    , "boundValues"
    , "clear"
    , "data"
    , "detachFromResultSet"
    , "driver"
    , "exec"
    , "execBatch"
    , "executedQuery"
    , "fetch"
    , "fetchFirst"
    , "fetchLast"
    , "fetchNext"
    , "fetchPrevious"
    , "handle"
    , "hasOutValues"
    , "isActive"
    , "isForwardOnly"
    , "isNull"
    , "isSelect"
    , "isValid"
    , "lastError"
    , "lastInsertId"
    , "lastQuery"
    , "nextResult"
    , "numRowsAffected"
    , "numericalPrecisionPolicy"
    , "prepare"
    , "record"
    , "reset"
    , "resetBindCount"
    , "savePrepare"
    , "setActive"
    , "setAt"
    , "setForwardOnly"
    , "setLastError"
    , "setNumericalPrecisionPolicy"
    , "setQuery"
    , "setSelect"
    , "size"
    , "toString"
};

static const char * const qtscript_QSqlResult_function_signatures[] = {
    ""
    // static
    // prototype
    , "Object val, ParamType type"
    , ""
    , "String placeholder, Object val, ParamType type\nint pos, Object val, ParamType type"
    , "String placeholder\nint pos"
    , ""
    , "String placeholder\nint pos"
    , ""
    , "int pos"
    , ""
    , ""
    , "int i"
    , ""
    , ""
    , ""
    , "bool arrayBind"
    , ""
    , "int i"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int i"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String query"
    , ""
    , "String sqlquery"
    , ""
    , "String sqlquery"
    , "bool a"
    , "int at"
    , "bool forward"
    , "QSqlError e"
    , "NumericalPrecisionPolicy policy"
    , "String query"
    , "bool s"
    , ""
""
};

static const int qtscript_QSqlResult_function_lengths[] = {
    0
    // static
    // prototype
    , 2
    , 0
    , 3
    , 1
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
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
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QSqlResult_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QSqlResult : public QSqlResult
{
    friend QScriptValue qtscript_QSqlResult_addBindValue(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_at(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_bindValue(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_bindValueType(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_bindingSyntax(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_boundValue(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_boundValueCount(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_boundValueName(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_boundValues(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_clear(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_data(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_detachFromResultSet(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_driver(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_exec(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_execBatch(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_executedQuery(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_fetch(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_fetchFirst(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_fetchLast(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_fetchNext(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_fetchPrevious(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_hasOutValues(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_isActive(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_isForwardOnly(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_isNull(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_isSelect(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_isValid(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_lastError(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_lastInsertId(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_lastQuery(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_nextResult(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_numRowsAffected(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_numericalPrecisionPolicy(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_prepare(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_record(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_reset(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_resetBindCount(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_savePrepare(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setActive(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setAt(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setForwardOnly(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setLastError(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setNumericalPrecisionPolicy(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setQuery(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_setSelect(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSqlResult_size(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QSqlResult_prototype_call(QScriptContext *, QScriptEngine *);

    friend struct QMetaTypeId< QSqlResult::VirtualHookOperation >;
    friend struct QMetaTypeId< QSqlResult::BindingSyntax >;
};

static QScriptValue qtscript_QSqlResult_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlResult::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlResult*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlResult*)
Q_DECLARE_METATYPE(QFlags<QSql::ParamTypeFlag>)
Q_DECLARE_METATYPE(QSqlResult::BindingSyntax)
Q_DECLARE_METATYPE(QVector<QVariant>)
Q_DECLARE_METATYPE(QSqlDriver*)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSql::NumericalPrecisionPolicy)
Q_DECLARE_METATYPE(QSqlRecord)

//
// QSqlResult
//

static QScriptValue qtscript_QSqlResult_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 47;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QSqlResult* _q_self = reinterpret_cast<qtscript_QSqlResult*>(qscriptvalue_cast<QSqlResult*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlResult.%0(): this object is not a QSqlResult")
            .arg(qtscript_QSqlResult_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        QFlags<QSql::ParamTypeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QSql::ParamTypeFlag> >(context->argument(1));
        _q_self->addBindValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->at();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && true
            && (qMetaTypeId<QFlags<QSql::ParamTypeFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_arg1 = context->argument(1).toVariant();
            QFlags<QSql::ParamTypeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QSql::ParamTypeFlag> >(context->argument(2));
            _q_self->bindValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && true
            && (qMetaTypeId<QFlags<QSql::ParamTypeFlag> >() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_arg1 = context->argument(1).toVariant();
            QFlags<QSql::ParamTypeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QSql::ParamTypeFlag> >(context->argument(2));
            _q_self->bindValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QFlags<QSql::ParamTypeFlag> _q_result = _q_self->bindValueType(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QFlags<QSql::ParamTypeFlag> _q_result = _q_self->bindValueType(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSqlResult::BindingSyntax _q_result = _q_self->bindingSyntax();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_result = _q_self->boundValue(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_result = _q_self->boundValue(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->boundValueCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->boundValueName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QVector<QVariant> _q_result = _q_self->boundValues();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        _q_self->detachFromResultSet();
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QSqlDriver* _q_result = const_cast<QSqlDriver*>(_q_self->driver());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exec();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->execBatch();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        bool _q_result = _q_self->execBatch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->executedQuery();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->fetch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fetchFirst();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fetchLast();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fetchNext();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fetchPrevious();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasOutValues();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isForwardOnly();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isNull(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSelect();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QSqlError _q_result = _q_self->lastError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->lastInsertId();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->lastQuery();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->nextResult();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->numRowsAffected();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        QSql::NumericalPrecisionPolicy _q_result = _q_self->numericalPrecisionPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->prepare(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        QSqlRecord _q_result = _q_self->record();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->reset(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        _q_self->resetBindCount();
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->savePrepare(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setActive(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setAt(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setForwardOnly(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QSqlError _q_arg0 = qscriptvalue_cast<QSqlError>(context->argument(0));
        _q_self->setLastError(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        QSql::NumericalPrecisionPolicy _q_arg0 = qscriptvalue_cast<QSql::NumericalPrecisionPolicy>(context->argument(0));
        _q_self->setNumericalPrecisionPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setQuery(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSelect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47: {
    QString result = QString::fromLatin1("QSqlResult");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlResult_throw_ambiguity_error_helper(context,
        qtscript_QSqlResult_function_names[_id+1],
        qtscript_QSqlResult_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlResult_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QSqlResult cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlResult_throw_ambiguity_error_helper(context,
        qtscript_QSqlResult_function_names[_id],
        qtscript_QSqlResult_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlResult_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlResult*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlResult*)0));
    for (int i = 0; i < 48; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlResult_prototype_call, qtscript_QSqlResult_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlResult_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlResult*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlResult_static_call, proto, qtscript_QSqlResult_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
