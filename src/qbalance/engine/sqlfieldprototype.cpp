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
#include <QtSql/QSqlField>
#include <QtSql/QSqlRecord>
#include <QtScript/QScriptClass>
#include "sqlfieldclass.h"
#include "sqlfieldprototype.h"

Q_DECLARE_METATYPE(QSqlField*)
Q_DECLARE_METATYPE(QSqlRecord*)

SqlFieldPrototype::SqlFieldPrototype(QObject *parent)
     : QObject(parent)
{
}


SqlFieldPrototype::~SqlFieldPrototype()
{
}


void SqlFieldPrototype::clear()
{
    thisSqlField()->clear();
}


QVariant SqlFieldPrototype::defaultValue() const
{
    return thisSqlField()->defaultValue();
}


bool SqlFieldPrototype::isAutoValue() const
{
    return thisSqlField()->isAutoValue();
}


bool SqlFieldPrototype::isGenerated() const
{
    return thisSqlField()->isGenerated();
}


bool SqlFieldPrototype::isNull() const
{
    return thisSqlField()->isNull();
}


bool SqlFieldPrototype::isReadOnly() const
{
    return thisSqlField()->isReadOnly();
}


bool SqlFieldPrototype::isValid() const
{
    return thisSqlField()->isValid();
}


int SqlFieldPrototype::length() const
{
    return thisSqlField()->length();
}


QString SqlFieldPrototype::name() const
{
    return thisSqlField()->name();
}


int SqlFieldPrototype::precision() const
{
    return thisSqlField()->precision();
}


QSqlField::RequiredStatus SqlFieldPrototype::requiredStatus() const
{
    return thisSqlField()->requiredStatus();
}


void SqlFieldPrototype::setAutoValue(bool autoVal)
{
    thisSqlField()->setAutoValue(autoVal);
}


void SqlFieldPrototype::setDefaultValue(const QVariant &value)
{
    thisSqlField()->setDefaultValue(value);
}


void SqlFieldPrototype::setGenerated(bool gen)
{
    thisSqlField()->setGenerated(gen);
}


void SqlFieldPrototype::setLength(int fieldLength)
{
    thisSqlField()->setLength(fieldLength);
}


void SqlFieldPrototype::setName(const QString &name)
{
    thisSqlField()->setName(name);
}


void SqlFieldPrototype::setPrecision(int precision)
{
    thisSqlField()->setPrecision(precision);
}


void SqlFieldPrototype::setReadOnly(bool readOnly)
{
    thisSqlField()->setReadOnly(readOnly);
}


void SqlFieldPrototype::setRequired(bool required)
{
    thisSqlField()->setRequired(required);
}


void SqlFieldPrototype::setRequiredStatus(QSqlField::RequiredStatus required)
{
    thisSqlField()->setRequiredStatus(required);
}


void SqlFieldPrototype::setType(QVariant::Type type)
{
    thisSqlField()->setType(type);
}


void SqlFieldPrototype::setValue(const QVariant &value)
{
    thisSqlField()->setValue(value);
}


QVariant::Type SqlFieldPrototype::type() const
{
    return thisSqlField()->type();
}


QVariant SqlFieldPrototype::value() const
{
    return thisSqlField()->value();
}


QSqlField *SqlFieldPrototype::thisSqlField() const
{
    return qscriptvalue_cast<QSqlField*>(thisObject().data());
}
