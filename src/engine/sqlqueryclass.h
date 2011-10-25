#ifndef SQLQUERYCLASS_H
#define SQLQUERYCLASS_H

#include <QObject>
#include <QScriptClass>
#include <QScriptEngine>
#include <QSqlQuery>

class SqlQueryClass : public QObject, QScriptClass
{
public:
    SqlQueryClass(QScriptEngine *engine);
    ~SqlQueryClass();
    QScriptValue constructor();
    QScriptValue newInstance(const QString s = "");
    QScriptValue newInstance(const QSqlQuery &);
    QScriptValue prototype() const;

private:
    QScriptValue proto;
    QScriptValue ctor;
    static QScriptValue construct(QScriptContext *, QScriptEngine *);
};

#endif // SQLQUERYCLASS_H
