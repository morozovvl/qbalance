/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QtScript/QScriptEngine>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtScript/QScriptClass>
#include "sqlqueryclass.h"
#include "sqlqueryprototype.h"

Q_DECLARE_METATYPE(QSqlQuery*)
Q_DECLARE_METATYPE(QSqlRecord*)

SqlQueryPrototype::SqlQueryPrototype(QObject *parent, SqlRecordClass* recordClass)
     : QObject(parent)
{
    sqlRecordClass = recordClass;
}


SqlQueryPrototype::~SqlQueryPrototype()
{
}


void SqlQueryPrototype::addBindValue (const QVariant &val, QSql::ParamType paramType)
{
    thisSqlQuery()->addBindValue(val, paramType);
}


int SqlQueryPrototype::at() const
{
    return thisSqlQuery()->at();
}


void SqlQueryPrototype::bindValue(const QString &placeholder,
                      const QVariant &val,
                      QSql::ParamType paramType)
{
    thisSqlQuery()->bindValue(placeholder, val, paramType);
}


void SqlQueryPrototype::bindValue(int pos,
                      const QVariant &val,
                      QSql::ParamType paramType)
{
    thisSqlQuery()->bindValue(pos, val, paramType);
}


QVariant SqlQueryPrototype::boundValue(const QString &placeholder) const
{
    return thisSqlQuery()->boundValue(placeholder);
}


QVariant SqlQueryPrototype::boundValue(int pos) const
{
    return thisSqlQuery()->boundValue(pos);
}


void SqlQueryPrototype::clear()
{
    thisSqlQuery()->clear();
}


bool SqlQueryPrototype::exec(const QString & query)
{
    return thisSqlQuery()->exec(query);
}


bool SqlQueryPrototype::exec()
{
    return thisSqlQuery()->exec(lastQuery());
}


bool SqlQueryPrototype::execBatch(QSqlQuery::BatchExecutionMode mode)
{
    return thisSqlQuery()->execBatch(mode);
}


QString	SqlQueryPrototype::executedQuery() const
{
    return thisSqlQuery()->executedQuery();
}


void SqlQueryPrototype::finish()
{
    thisSqlQuery()->finish();
}


bool SqlQueryPrototype::first()
{
    return thisSqlQuery()->first();
}


bool SqlQueryPrototype::isActive() const
{
    return thisSqlQuery()->isActive();
}


bool SqlQueryPrototype::isForwardOnly() const
{
    return thisSqlQuery()->isForwardOnly();
}


bool SqlQueryPrototype::isNull(int field) const
{
    return thisSqlQuery()->isNull(field);
}


bool SqlQueryPrototype::isSelect() const
{
    return thisSqlQuery()->isSelect();
}


bool SqlQueryPrototype::isValid() const
{
    return thisSqlQuery()->isValid();
}


bool SqlQueryPrototype::last()
{
    return thisSqlQuery()->last();
}


QString SqlQueryPrototype::lastError()
{
    return thisSqlQuery()->lastError().text();
}


QVariant SqlQueryPrototype::lastInsertId() const
{
    return thisSqlQuery()->lastInsertId();
}


QString SqlQueryPrototype::lastQuery()
{
    return thisSqlQuery()->lastQuery();
}


bool SqlQueryPrototype::next()
{
    return thisSqlQuery()->next();
}


bool SqlQueryPrototype::nextResult()
{
    return thisSqlQuery()->nextResult();
}


int SqlQueryPrototype::numRowsAffected() const
{
    return thisSqlQuery()->numRowsAffected();
}


QSql::NumericalPrecisionPolicy SqlQueryPrototype::numericalPrecisionPolicy() const
{
    return thisSqlQuery()->numericalPrecisionPolicy();
}


bool SqlQueryPrototype::prepare(const QString &query)
{
    return thisSqlQuery()->prepare(query);
}


bool SqlQueryPrototype::previous()
{
    return thisSqlQuery()->previous();
}


QScriptValue SqlQueryPrototype::record()
{
    return sqlRecordClass->newInstance(thisSqlQuery()->record());
}


bool SqlQueryPrototype::seek(int index, bool relative)
{
    return thisSqlQuery()->seek(index, relative);
}


void SqlQueryPrototype::setForwardOnly (bool forward)
{
    return thisSqlQuery()->setForwardOnly(forward);
}


void SqlQueryPrototype::setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy)
{
    return thisSqlQuery()->setNumericalPrecisionPolicy(precisionPolicy);
}


int SqlQueryPrototype::size() const
{
    return thisSqlQuery()->size();
}


QVariant SqlQueryPrototype::value(int index) const
{
    return thisSqlQuery()->value(index);
}


QSqlQuery *SqlQueryPrototype::thisSqlQuery() const
{
    return qscriptvalue_cast<QSqlQuery*>(thisObject().data());
}
