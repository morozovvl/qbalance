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


QSqlQuery *SqlQueryPrototype::thisSqlQuery() const
{
    return qscriptvalue_cast<QSqlQuery*>(thisObject().data());
}
