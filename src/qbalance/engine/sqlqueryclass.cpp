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
#include <QtScript/QScriptContext>
#include "sqlqueryclass.h"
#include "sqlqueryprototype.h"


Q_DECLARE_METATYPE(QSqlQuery)
Q_DECLARE_METATYPE(QSqlQuery*)
Q_DECLARE_METATYPE(SqlQueryClass*)


SqlQueryClass::SqlQueryClass(QScriptEngine* engine, SqlRecordClass* recordClass)
     : QObject(engine), QScriptClass(engine)
{
    proto = engine->newQObject(new SqlQueryPrototype(this, recordClass), QScriptEngine::ScriptOwnership);
    proto.setPrototype(engine->globalObject().property("Object").property("prototype"));
    ctor = engine->newFunction(construct, proto);
    ctor.setData(qScriptValueFromValue(engine, this));
}

SqlQueryClass::~SqlQueryClass()
{
}

QScriptValue SqlQueryClass::prototype() const
{
    return proto;
}

QScriptValue SqlQueryClass::constructor()
{
    return ctor;
}

QScriptValue SqlQueryClass::newInstance(const QString s)
{
    return newInstance(QSqlQuery(s));
}

QScriptValue SqlQueryClass::newInstance(const QSqlQuery &q)
{
    QScriptValue data = engine()->newVariant(qVariantFromValue(q));
    return engine()->newObject(this, data);
}

QScriptValue SqlQueryClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    SqlQueryClass *cls = qscriptvalue_cast<SqlQueryClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    QScriptValue arg = ctx->argument(0);
    if (arg.instanceOf(ctx->callee()))
        return cls->newInstance(qscriptvalue_cast<QSqlQuery>(arg.toString()));
    return cls->newInstance(arg.toString());
 }

