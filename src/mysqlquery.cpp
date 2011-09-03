#include "mysqlquery.h"

MySqlQuery::MySqlQuery(QString queryString) : QObject(0) {
    query = new QSqlQuery(queryString);
}

MySqlQuery::MySqlQuery(QSqlQuery q) : QObject(0) {
    query = new QSqlQuery(q);
}

