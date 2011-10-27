#ifndef SQLFIELDPROTOTYPE_H
#define SQLFIELDPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QSqlField>
#include <QSqlError>
#include <QVariant>
#include "sqlfieldclass.h"


class SqlFieldPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    SqlFieldPrototype(QObject*);
    ~SqlFieldPrototype();
public slots:
    QString     fieldName() { return "SqlFieldPrototype"; }
private:
    QSqlField*          thisSqlField() const;
};

#endif // SQLFIELDPROTOTYPE_H
