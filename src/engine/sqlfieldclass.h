#ifndef SQLFIELDCLASS_H
#define SQLFIELDCLASS_H

#include <QObject>
#include <QScriptClass>
#include <QScriptEngine>
#include <QSqlField>

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
