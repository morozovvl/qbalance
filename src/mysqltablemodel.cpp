#include <QModelIndex>
#include <QVariant>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlResult>
#include <QDebug>
#include <QSqlError>
#include "mysqltablemodel.h"

MySqlTableModel::MySqlTableModel() : QSqlTableModel() {
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

bool MySqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    bool lResult = false;
    lResult = QSqlTableModel::setData(index, value, role);
    if (lResult) {
        QSqlRecord rec = record(index.row());
        rec.setValue(index.column(), value);
        rec.setGenerated(index.column(), true);
        lResult = updateRowInTable(index.row(), rec);
    }
    return lResult;
}

