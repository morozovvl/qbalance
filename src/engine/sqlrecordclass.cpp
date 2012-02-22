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
#include "sqlrecordclass.h"
#include "sqlrecordprototype.h"

Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlRecord*)
Q_DECLARE_METATYPE(SqlRecordClass*)


SqlRecordClass::SqlRecordClass(QScriptEngine *engine, SqlFieldClass* fieldClass)
     : QObject(engine), QScriptClass(engine)
{
    proto = engine->newQObject(new SqlRecordPrototype(this, fieldClass), QScriptEngine::ScriptOwnership);
    proto.setPrototype(engine->globalObject().property("Object").property("prototype"));
    ctor = engine->newFunction(construct, proto);
    ctor.setData(qScriptValueFromValue(engine, this));
}

SqlRecordClass::~SqlRecordClass()
{
}

QScriptValue SqlRecordClass::prototype() const
{
    return proto;
}

QScriptValue SqlRecordClass::constructor()
{
    return ctor;
}

QScriptValue SqlRecordClass::newInstance()
{
   return newInstance(QSqlRecord());
}

QScriptValue SqlRecordClass::newInstance(const QSqlRecord &q)
{
    QScriptValue data = engine()->newVariant(qVariantFromValue(q));
    return engine()->newObject(this, data);
}

QScriptValue SqlRecordClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    SqlRecordClass *cls = qscriptvalue_cast<SqlRecordClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    return cls->newInstance();
 }

