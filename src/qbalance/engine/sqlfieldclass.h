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

#ifndef SQLFIELDCLASS_H
#define SQLFIELDCLASS_H

#include <QtCore/QObject>
#include <QtScript/QScriptClass>
#include <QtScript/QScriptEngine>
#include <QtSql/QSqlField>

class SqlFieldClass : public QObject, QScriptClass
{
public:
    SqlFieldClass(QScriptEngine*);
    ~SqlFieldClass();
    QScriptValue constructor();
    QScriptValue newInstance(const QString & fieldName = QString(), QVariant::Type type = QVariant::Invalid);
    QScriptValue newInstance(const QSqlField &);
    QScriptValue prototype() const;
    QString name() const { return "SqlField"; }
    QScriptEngine* getEngine() { return engine(); }
private:
    QScriptValue proto;
    QScriptValue ctor;
    static QScriptValue construct(QScriptContext *, QScriptEngine *);
};

#endif // SQLFIELDCLASS_H
