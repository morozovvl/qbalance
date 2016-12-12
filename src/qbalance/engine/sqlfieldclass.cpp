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
#include "sqlfieldclass.h"
#include "sqlfieldprototype.h"


Q_DECLARE_METATYPE(QSqlField)
Q_DECLARE_METATYPE(QSqlField*)
Q_DECLARE_METATYPE(SqlFieldClass*)


SqlFieldClass::SqlFieldClass(QScriptEngine* engine)
     : QObject(engine), QScriptClass(engine)
{
    proto = engine->newQObject(new SqlFieldPrototype(this));
    proto.setPrototype(engine->globalObject().property("Object").property("prototype"));
    ctor = engine->newFunction(construct, proto);
    ctor.setData(engine->toScriptValue(this));
}

SqlFieldClass::~SqlFieldClass()
{
}


QString SqlFieldClass::name() const
{
    return "SqlField";
}


QScriptEngine* SqlFieldClass::getEngine()
{
    return engine();
}


QScriptValue SqlFieldClass::prototype() const
{
    return proto;
}

QScriptValue SqlFieldClass::constructor()
{
    return ctor;
}

QScriptValue SqlFieldClass::newInstance(const QString &fieldName, QVariant::Type type)
{
    return newInstance(QSqlField(fieldName, type));
}

QScriptValue SqlFieldClass::newInstance(const QSqlField &q)
{
    QScriptValue data = engine()->newVariant(qVariantFromValue(q));
    return engine()->newObject(this, data);
}

QScriptValue SqlFieldClass::construct(QScriptContext *ctx, QScriptEngine *)
{
    SqlFieldClass *cls = qscriptvalue_cast<SqlFieldClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();
    QScriptValue arg = ctx->argument(0);
    if (arg.instanceOf(ctx->callee()))
        return cls->newInstance(qscriptvalue_cast<QSqlField>(arg.toString()));
    return cls->newInstance(arg.toString());
 }

