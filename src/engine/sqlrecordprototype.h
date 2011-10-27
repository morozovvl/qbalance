#ifndef SQLRECORDPROTOTYPE_H
#define SQLRECORDPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QSqlRecord>
#include <QVariant>
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
