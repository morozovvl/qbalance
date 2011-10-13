#include "mysqlquery.h"

MySqlQuery::MySqlQuery(const QString& queryString) : QObject(0) {
    query = new QSqlQuery(queryString);
}

MySqlQuery::MySqlQuery(const QSqlQuery& q) : QObject(0) {
    query = new QSqlQuery(q);
}

MySqlQuery::~MySqlQuery()
{
    if (query)
    {
        delete query;
        query = NULL;
    }
}
