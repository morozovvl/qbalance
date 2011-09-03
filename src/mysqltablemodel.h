#ifndef MYSQLTABLEMODEL_H
#define MYSQLTABLEMODEL_H

#include <QModelIndex>
#include <QVariant>
#include <QSqlTableModel>
#include <QSqlRecord>

class MySqlTableModel : public QSqlTableModel {
public:
    MySqlTableModel();
    bool setData(const QModelIndex &, const QVariant &, int);
};

#endif // MYSQLTABLEMODEL_H
