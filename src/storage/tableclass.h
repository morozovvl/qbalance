#ifndef TABLECLASS_H
#define TABLECLASS_H

#include <QObject>
#include <QScriptEngine>
#include <QScriptClass>
#include "table.h"

//typedef Table* ptrTable;

class TableClass : public QObject, public QScriptClass {
public:
    TableClass(QScriptEngine *);
    ~TableClass();
    QScriptValue constructor();
    QScriptValue newInstance(QScriptContext*);
    QueryFlags queryProperty(const QScriptValue &, const QScriptString &, QueryFlags, uint *);
    QScriptValue property(const QScriptValue &, const QScriptString &, uint);
    void setProperty(QScriptValue &, const QScriptString &, uint, const QScriptValue &);
    QString name() const;
    QScriptValue prototype() const;

private:
    static QScriptValue construct(QScriptContext *, QScriptEngine *);
//    static QScriptValue toScriptValue(QScriptEngine *, const ptrTable &);
//    static void fromScriptValue(const QScriptValue &, ptrTable &);
//    static QScriptValue toScriptValue(QScriptEngine *, const Table &);
//    static void fromScriptValue(const QScriptValue &, Table &);
    Table* table;
    QScriptEngine* engine;
    QScriptString tableName;
    QScriptValue proto;
    QScriptValue ctor;
};

#endif // TABLECLASS_H
