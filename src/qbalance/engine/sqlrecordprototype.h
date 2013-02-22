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

#ifndef SQLRECORDPROTOTYPE_H
#define SQLRECORDPROTOTYPE_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptValue>
#include <QtSql/QSqlRecord>
#include <QtCore/QVariant>
#include "sqlfieldclass.h"

class SqlRecordPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    SqlRecordPrototype(QObject *parent, SqlFieldClass*);
    ~SqlRecordPrototype();
public slots:
    void	append(QScriptValue);
    void	clear()                                                 { return thisSqlRecord()->clear(); }
    void	clearValues()                                           { return thisSqlRecord()->clearValues(); }
    bool	contains(const QString &name) const                     { return thisSqlRecord()->contains(name); }
    int         count() const                                           { return thisSqlRecord()->count(); }
    QScriptValue    field(int index) const                              { return sqlFieldClass->newInstance(thisSqlRecord()->fieldName(index)); }
    QScriptValue    field(const QString &name) const                    { return sqlFieldClass->newInstance(name); }
    QString	fieldName(int index) const                              { return thisSqlRecord()->fieldName(index); }
    int         indexOf(const QString &name) const                      { return thisSqlRecord()->indexOf(name); }
    void	insert(int, QScriptValue);
    bool	isEmpty() const                                         { return thisSqlRecord()->isEmpty(); }
    bool	isGenerated(const QString &name) const                  { return thisSqlRecord()->isGenerated(name); }
    bool	isGenerated(int index) const                            { return thisSqlRecord()->isGenerated(index); }
    bool	isNull(const QString &name) const                       { return thisSqlRecord()->isNull(name); }
    bool	isNull(int index) const                                 { return thisSqlRecord()->isNull(index); }
    void	remove(int pos)                                         { return thisSqlRecord()->remove(pos); }
    void	replace(int, QScriptValue);
    void	setGenerated(const QString &name, bool generated)       { return thisSqlRecord()->setGenerated(name, generated); }
    void	setGenerated(int index, bool generated)                 { return thisSqlRecord()->setGenerated(index, generated); }
    void	setNull(int index)                                      { return thisSqlRecord()->setNull(index); }
    void	setNull(const QString &name)                            { return thisSqlRecord()->setNull(name); }
    void	setValue(int index, const QVariant &val)                { return thisSqlRecord()->setValue(index, val); }
    void	setValue(const QString &name, const QVariant &val)      { return thisSqlRecord()->setValue(name, val); }
    QVariant	value(int index) const                                  { return thisSqlRecord()->value(index); }
    QVariant	value(const QString &name) const                        { return thisSqlRecord()->value(name); }
private:
    SqlFieldClass*     sqlFieldClass;
    QSqlRecord* thisSqlRecord() const;
};

#endif // SQLRECORDPROTOTYPE_H
