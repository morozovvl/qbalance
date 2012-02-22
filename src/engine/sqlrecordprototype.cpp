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

#include <QDebug>
#include <QScriptEngine>
#include <QSqlRecord>
#include "sqlrecordprototype.h"

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

