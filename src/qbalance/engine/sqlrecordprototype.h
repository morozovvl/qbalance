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

class SqlFieldClass;


class SqlRecordPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    SqlRecordPrototype(QObject *parent, SqlFieldClass*);
    ~SqlRecordPrototype();
public slots:
    void	append(QScriptValue);
    void	clear();
    void	clearValues();
    bool	contains(const QString &name) const;
    int         count() const;
    QScriptValue    field(int index) const;
    QScriptValue    field(const QString &name) const;
    QString	fieldName(int index) const;
    int         indexOf(const QString &name) const;
    void	insert(int, QScriptValue);
    bool	isEmpty() const;
    bool	isGenerated(const QString &name) const;
    bool	isGenerated(int index) const;
    bool	isNull(const QString &name) const;
    bool	isNull(int index) const;
    void	remove(int pos);
    void	replace(int, QScriptValue);
    void	setGenerated(const QString &name, bool generated);
    void	setGenerated(int index, bool generated);
    void	setNull(int index);
    void	setNull(const QString &name);
    void	setValue(int index, const QVariant &val);
    void	setValue(const QString &name, const QVariant &val);
    QVariant	value(int index) const;
    QVariant	value(const QString &name) const;
private:
    SqlFieldClass*     sqlFieldClass;
    QSqlRecord* thisSqlRecord() const;
};

#endif // SQLRECORDPROTOTYPE_H
