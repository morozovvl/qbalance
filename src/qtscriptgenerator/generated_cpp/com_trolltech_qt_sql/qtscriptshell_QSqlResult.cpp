#include "qtscriptshell_QSqlResult.h"

#include <QtScript/QScriptEngine>
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

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QFlags<QSql::ParamTypeFlag>)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSql::NumericalPrecisionPolicy)

QtScriptShell_QSqlResult::QtScriptShell_QSqlResult(const QSqlDriver*  db)
    : QSqlResult(db) {}

QtScriptShell_QSqlResult::~QtScriptShell_QSqlResult() {}

void QtScriptShell_QSqlResult::bindValue(const QString&  placeholder, const QVariant&  val, QSql::ParamType  type)
{
    QScriptValue _q_function = __qtscript_self.property("bindValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bindValue") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::bindValue(placeholder, val, type);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, placeholder)
            << qScriptValueFromValue(_q_engine, val)
            << qScriptValueFromValue(_q_engine, type));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::bindValue(int  pos, const QVariant&  val, QSql::ParamType  type)
{
    QScriptValue _q_function = __qtscript_self.property("bindValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bindValue") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::bindValue(pos, val, type);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pos)
            << qScriptValueFromValue(_q_engine, val)
            << qScriptValueFromValue(_q_engine, type));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QSqlResult::data(int  i)
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::data() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, i)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlResult::detachFromResultSet()
{
    QScriptValue _q_function = __qtscript_self.property("detachFromResultSet");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("detachFromResultSet") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::detachFromResultSet();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSqlResult::exec()
{
    QScriptValue _q_function = __qtscript_self.property("exec");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("exec") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::exec();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::execBatch(bool  arrayBind)
{
    QScriptValue _q_function = __qtscript_self.property("execBatch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("execBatch") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::execBatch(arrayBind);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arrayBind)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::fetch(int  i)
{
    QScriptValue _q_function = __qtscript_self.property("fetch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetch") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::fetch() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, i)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::fetchFirst()
{
    QScriptValue _q_function = __qtscript_self.property("fetchFirst");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchFirst") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::fetchFirst() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::fetchLast()
{
    QScriptValue _q_function = __qtscript_self.property("fetchLast");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchLast") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::fetchLast() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::fetchNext()
{
    QScriptValue _q_function = __qtscript_self.property("fetchNext");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchNext") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::fetchNext();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::fetchPrevious()
{
    QScriptValue _q_function = __qtscript_self.property("fetchPrevious");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchPrevious") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::fetchPrevious();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QSqlResult::handle() const
{
    QScriptValue _q_function = __qtscript_self.property("handle");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("handle") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::handle();
    } else {
        _q_function.setData(QScriptValue(true));
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::isNull(int  i)
{
    QScriptValue _q_function = __qtscript_self.property("isNull");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isNull") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::isNull() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, i)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QSqlResult::lastInsertId() const
{
    QScriptValue _q_function = __qtscript_self.property("lastInsertId");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lastInsertId") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::lastInsertId();
    } else {
        _q_function.setData(QScriptValue(true));
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::nextResult()
{
    QScriptValue _q_function = __qtscript_self.property("nextResult");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextResult") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::nextResult();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QSqlResult::numRowsAffected()
{
    QScriptValue _q_function = __qtscript_self.property("numRowsAffected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("numRowsAffected") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::numRowsAffected() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::prepare(const QString&  query)
{
    QScriptValue _q_function = __qtscript_self.property("prepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("prepare") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::prepare(query);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QSqlRecord  QtScriptShell_QSqlResult::record() const
{
    QScriptValue _q_function = __qtscript_self.property("record");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("record") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::record();
    } else {
        _q_function.setData(QScriptValue(true));
        QSqlRecord _q_retval = qscriptvalue_cast<QSqlRecord >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::reset(const QString&  sqlquery)
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::reset() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sqlquery)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlResult::savePrepare(const QString&  sqlquery)
{
    QScriptValue _q_function = __qtscript_self.property("savePrepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("savePrepare") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlResult::savePrepare(sqlquery);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sqlquery)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlResult::setActive(bool  a)
{
    QScriptValue _q_function = __qtscript_self.property("setActive");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setActive") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setActive(a);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, a));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::setAt(int  at)
{
    QScriptValue _q_function = __qtscript_self.property("setAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setAt(at);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, at));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::setForwardOnly(bool  forward)
{
    QScriptValue _q_function = __qtscript_self.property("setForwardOnly");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setForwardOnly") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setForwardOnly(forward);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, forward));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::setLastError(const QSqlError&  e)
{
    QScriptValue _q_function = __qtscript_self.property("setLastError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLastError") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setLastError(e);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy  policy)
{
    QScriptValue _q_function = __qtscript_self.property("setNumericalPrecisionPolicy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setNumericalPrecisionPolicy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setNumericalPrecisionPolicy(policy);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, policy));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::setQuery(const QString&  query)
{
    QScriptValue _q_function = __qtscript_self.property("setQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setQuery(query);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlResult::setSelect(bool  s)
{
    QScriptValue _q_function = __qtscript_self.property("setSelect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlResult::setSelect(s);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, s));
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QSqlResult::size()
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QSqlResult::size() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

