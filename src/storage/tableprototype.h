#ifndef TABLEPROTOTYPE_H
#define TABLEPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include "table.h"

class TablePrototype : public QObject, public QScriptable {
    Q_OBJECT
public:
    explicit TablePrototype(QObject *parent = 0);
    ~TablePrototype();
signals:

public slots:

private:
     Table* thisTable() const;
};

#endif // TABLEPROTOTYPE_H
