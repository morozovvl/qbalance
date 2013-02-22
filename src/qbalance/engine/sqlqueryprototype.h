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
    void	addBindValue (const QVariant &val, QSql::ParamType paramType = QSql::In)
                                                { thisSqlQuery()->addBindValue(val, paramType); }
    int         at() const                      { return thisSqlQuery()->at(); }
    void	bindValue(const QString &placeholder,
                          const QVariant &val,
                          QSql::ParamType paramType = QSql::In)
                                                { thisSqlQuery()->bindValue(placeholder, val, paramType); }
    void	bindValue(int pos,
                          const QVariant &val,
                          QSql::ParamType paramType = QSql::In)
                                                { thisSqlQuery()->bindValue(pos, val, paramType); }
    QVariant	boundValue(const QString &placeholder) const
                                                { return thisSqlQuery()->boundValue(placeholder); }
    QVariant	boundValue(int pos) const       { return thisSqlQuery()->boundValue(pos); }
    void	clear()                         { thisSqlQuery()->clear(); }
    bool	exec(const QString & query)     { return thisSqlQuery()->exec(query); }
    bool	exec()                          { return thisSqlQuery()->exec(lastQuery()); }
    bool	execBatch(QSqlQuery::BatchExecutionMode mode = QSqlQuery::ValuesAsRows)
                                                { return thisSqlQuery()->execBatch(mode); }
    QString	executedQuery() const           { return thisSqlQuery()->executedQuery(); }
    void	finish()                        { thisSqlQuery()->finish(); }
    bool	first()                         { return thisSqlQuery()->first(); }
    bool	isActive() const                { return thisSqlQuery()->isActive(); }
    bool	isForwardOnly() const           { return thisSqlQuery()->isForwardOnly(); }
    bool	isNull(int field) const         { return thisSqlQuery()->isNull(field); }
    bool	isSelect() const                { return thisSqlQuery()->isSelect(); }
    bool	isValid() const                 { return thisSqlQuery()->isValid(); }
    bool	last()                          { return thisSqlQuery()->last(); }
    QString     lastError()                     { return thisSqlQuery()->lastError().text(); }
    QVariant	lastInsertId() const            { return thisSqlQuery()->lastInsertId(); }
    QString     lastQuery()                     { return thisSqlQuery()->lastQuery(); }
    bool	next()                          { return thisSqlQuery()->next(); }
    bool	nextResult()                    { return thisSqlQuery()->nextResult(); }
    int         numRowsAffected() const         { return thisSqlQuery()->numRowsAffected(); }
    QSql::NumericalPrecisionPolicy
                numericalPrecisionPolicy() const { return thisSqlQuery()->numericalPrecisionPolicy(); }
    bool	prepare(const QString &query)   { return thisSqlQuery()->prepare(query); }
    bool	previous()                      { return thisSqlQuery()->previous(); }
    QScriptValue record()                       { return sqlRecordClass->newInstance(thisSqlQuery()->record()); }
    bool	seek(int index, bool relative = false)
                                                { return thisSqlQuery()->seek(index, relative); }
    void	setForwardOnly (bool forward)   { return thisSqlQuery()->setForwardOnly(forward); }
    void	setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy)
                                                { return thisSqlQuery()->setNumericalPrecisionPolicy(precisionPolicy); }
    int         size() const                    { return thisSqlQuery()->size(); }
    QVariant	value(int index) const          { return thisSqlQuery()->value(index); }

/* Осталось определить:
    QMap<QString, QVariant>	boundValues () const
    const QSqlDriver *	driver () const
    QSqlError	lastError () const
    const QSqlResult *	result () const
*/

private:
    SqlRecordClass*     sqlRecordClass;
    QSqlQuery*          thisSqlQuery() const;
};

#endif // SQLQUERYPROTOTYPE_H
