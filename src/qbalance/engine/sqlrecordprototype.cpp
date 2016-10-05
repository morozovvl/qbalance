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
#include <QtSql/QSqlRecord>
#include "sqlrecordprototype.h"
#include "sqlfieldclass.h"

Q_DECLARE_METATYPE(QSqlRecord*)
Q_DECLARE_METATYPE(QSqlField)


SqlRecordPrototype::SqlRecordPrototype(QObject *parent, SqlFieldClass* fieldClass)
     : QObject(parent)
{
    sqlFieldClass = fieldClass;
}

SqlRecordPrototype::~SqlRecordPrototype()
{
}


void SqlRecordPrototype::clear()
{
    return thisSqlRecord()->clear();
}


void SqlRecordPrototype::clearValues()
{
    return thisSqlRecord()->clearValues();
}


bool SqlRecordPrototype::contains(const QString &name) const
{
    return thisSqlRecord()->contains(name);
}


int SqlRecordPrototype::count() const
{
    return thisSqlRecord()->count();
}


QScriptValue SqlRecordPrototype::field(int index) const
{
    return sqlFieldClass->newInstance(thisSqlRecord()->fieldName(index));
}


QScriptValue SqlRecordPrototype::field(const QString &name) const
{
    return sqlFieldClass->newInstance(name);
}


QString	SqlRecordPrototype::fieldName(int index) const
{
    return thisSqlRecord()->fieldName(index);
}


int SqlRecordPrototype::indexOf(const QString &name) const
{
    return thisSqlRecord()->indexOf(name);
}


bool SqlRecordPrototype::isEmpty() const
{
    return thisSqlRecord()->isEmpty();
}


bool SqlRecordPrototype::isGenerated(const QString &name) const
{
    return thisSqlRecord()->isGenerated(name);
}


bool SqlRecordPrototype::isGenerated(int index) const
{
    return thisSqlRecord()->isGenerated(index);
}


bool SqlRecordPrototype::isNull(const QString &name) const
{
    return thisSqlRecord()->isNull(name);
}


bool SqlRecordPrototype::isNull(int index) const
{
    return thisSqlRecord()->isNull(index);
}


void SqlRecordPrototype::remove(int pos)
{
    return thisSqlRecord()->remove(pos);
}


void SqlRecordPrototype::setGenerated(const QString &name, bool generated)
{
    return thisSqlRecord()->setGenerated(name, generated);
}


void SqlRecordPrototype::setGenerated(int index, bool generated)
{
    return thisSqlRecord()->setGenerated(index, generated);
}


void SqlRecordPrototype::setNull(int index)
{
    return thisSqlRecord()->setNull(index);
}


void SqlRecordPrototype::setNull(const QString &name)
{
    return thisSqlRecord()->setNull(name);
}


void SqlRecordPrototype::setValue(int index, const QVariant &val)
{
    return thisSqlRecord()->setValue(index, val);
}


void SqlRecordPrototype::setValue(const QString &name, const QVariant &val)
{
    return thisSqlRecord()->setValue(name, val);
}


QVariant SqlRecordPrototype::value(int index) const
{
    return thisSqlRecord()->value(index);
}


QVariant SqlRecordPrototype::value(const QString &name) const
{
    return thisSqlRecord()->value(name);
}


QSqlRecord *SqlRecordPrototype::thisSqlRecord() const
{
    return qscriptvalue_cast<QSqlRecord*>(thisObject().data());
}


void SqlRecordPrototype::append(QScriptValue field)
{
    if (field.isObject() && sqlFieldClass->name().compare(field.scriptClass()->name(), Qt::CaseSensitive) == 0)
    {
        QSqlField sqlField = qscriptvalue_cast<QSqlField>(field.data());
        thisSqlRecord()->append(sqlField);
    }
}


void SqlRecordPrototype::insert(int pos, QScriptValue field)
{
    if (field.isObject() && sqlFieldClass->name().compare(field.scriptClass()->name(), Qt::CaseSensitive) == 0)
    {
        QSqlField sqlField = qscriptvalue_cast<QSqlField>(field.data());
        thisSqlRecord()->insert(pos, sqlField);
    }

}


void SqlRecordPrototype::replace(int pos, QScriptValue field)
{
    if (field.isObject() && sqlFieldClass->name().compare(field.scriptClass()->name(), Qt::CaseSensitive) == 0)
    {
        QSqlField sqlField = qscriptvalue_cast<QSqlField>(field.data());
        thisSqlRecord()->replace(pos, sqlField);
    }
}

