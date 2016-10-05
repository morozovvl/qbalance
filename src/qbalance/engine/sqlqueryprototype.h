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

#ifndef SQLQUERYPROTOTYPE_H
#define SQLQUERYPROTOTYPE_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptValue>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>
#include "sqlrecordclass.h"


class SqlQueryPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    SqlQueryPrototype(QObject*, SqlRecordClass*);
    ~SqlQueryPrototype();

public slots:
    void	addBindValue (const QVariant &val, QSql::ParamType paramType = QSql::In);
    int         at() const;
    void	bindValue(const QString &placeholder,
                          const QVariant &val,
                          QSql::ParamType paramType = QSql::In);
    void	bindValue(int pos,
                          const QVariant &val,
                          QSql::ParamType paramType = QSql::In);
    QVariant	boundValue(const QString &placeholder) const;
    QVariant	boundValue(int pos) const;
    void	clear();
    bool	exec(const QString & query);
    bool	exec();
    bool	execBatch(QSqlQuery::BatchExecutionMode mode = QSqlQuery::ValuesAsRows);
    QString	executedQuery() const;
    void	finish();
    bool	first();
    bool	isActive() const ;
    bool	isForwardOnly() const;
    bool	isNull(int field) const;
    bool	isSelect() const;
    bool	isValid() const;
    bool	last();
    QString     lastError();
    QVariant	lastInsertId() const;
    QString     lastQuery();
    bool	next();
    bool	nextResult();
    int         numRowsAffected() const;
    QSql::NumericalPrecisionPolicy numericalPrecisionPolicy() const;
    bool	prepare(const QString &query);
    bool	previous();
    QScriptValue record();
    bool	seek(int index, bool relative = false);
    void	setForwardOnly (bool forward);
    void	setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy);
    int         size() const;
    QVariant	value(int index) const;

/* Осталось определить:
    QHash<QString, QVariant>	boundValues () const
    const QSqlDriver *	driver () const
    QSqlError	lastError () const
    const QSqlResult *	result () const
*/

private:
    SqlRecordClass*     sqlRecordClass;
    QSqlQuery*          thisSqlQuery() const;
};

#endif // SQLQUERYPROTOTYPE_H
