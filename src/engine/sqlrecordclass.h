#ifndef SQLRECORDCLASS_H
#define SQLRECORDCLASS_H

#include <QObject>
#include <QScriptClass>
#include <QSqlRecord>
#include "sqlfieldclass.h"

class SqlRecordClass : public QObject, QScriptClass
{
public:
    SqlRecordClass(QScriptEngine *engine, SqlFieldClass*);
    ~SqlRecordClass();
    QScriptValue constructor();
    QScriptValue newInstance();
    QScriptValue newInstance(const QSqlRecord &);
    QScriptValue prototype() const;
    QString name() const { return "SqlRecord"; }
private:
    QScriptValue proto;
    QScriptValue ctor;
    static QScriptValue construct(QScriptContext *, QScriptEngine *);
};

#endif // SQLRECORDCLASS_H
