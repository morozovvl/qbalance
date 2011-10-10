#include <QtScript/QScriptEngine>
#include <QScriptValue>
#include "tableprototype.h"

Q_DECLARE_METATYPE(Table*)

TablePrototype::TablePrototype(QObject *parent): QObject(parent), QScriptable() {
}

TablePrototype::~TablePrototype() {
}

Table* TablePrototype::thisTable() const {
    return qscriptvalue_cast<Table*>(thisObject().data());
}
