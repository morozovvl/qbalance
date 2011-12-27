#ifndef SQLQUERYCLASS_H
#define SQLQUERYCLASS_H

#include <QObject>
#include <QScriptClass>
#include <QScriptEngine>
#include <QSqlQuery>
#include "sqlrecordclass.h"

class SqlQueryClass : public QObject, QScriptClass
{
public:
    SqlQueryClass(QScriptEngine*, SqlRecordClass*);
    ~SqlQueryClass();
    QScriptValue constructor();
    QScriptValue newInstance(const QString s = "");
    QScriptValue newInstance(const QSqlQuery &);
    QScriptValue prototype() const;
    QString name() const { return "SqlQuery"; }
    QScriptEngine* getEngine() { return engine(); }
private:
    QScriptValue proto;
    QScriptValue ctor;
    static QScriptValue construct(QScriptContext *, QScriptEngine *);
};

#endif // SQLQUERYCLASS_H
