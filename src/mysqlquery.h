#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include <QSqlQuery>
#include <QObject>

class MySqlQuery : public QObject {
    Q_OBJECT

public:
    MySqlQuery(const QString&);
    MySqlQuery(const QSqlQuery&);
    ~MySqlQuery();
    Q_INVOKABLE int size() { return query->size(); }

private:
    QSqlQuery* query;
};

#endif // MYSQLQUERY_H
