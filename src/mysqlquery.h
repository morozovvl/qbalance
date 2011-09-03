#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include <QSqlQuery>
#include <QObject>

class MySqlQuery : public QObject {
    Q_OBJECT

public:
    MySqlQuery(QString);
    MySqlQuery(QSqlQuery);
    Q_INVOKABLE int size() { return query->size(); }

private:
    QSqlQuery* query;
};

#endif // MYSQLQUERY_H
