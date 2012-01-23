#include "documenttablemodel.h"
#include <QDebug>
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "mysqlrelationaltablemodel.h"

class TApplication;

DocumentTableModel::DocumentTableModel(): MySqlRelationalTableModel() {
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setBlockUpdate(true);
}

bool DocumentTableModel::submit(const QModelIndex& index) {
    if (editStrategy() == QSqlTableModel::OnManualSubmit) {
        if (database().transaction()) {
            QList<int>::iterator key;
            for (key = updateKeys.begin(); key != updateKeys.end(); key++) {
                QString command;
                foreach (int field, updateKeyFields.keys()) {
                    if (*key == updateKeyFields[field]) {
                        command.append(QString("%1=%2, ").arg(updateFields[field]).arg(record(index.row()).value(field).toString()));
                    }
                }
                command.chop(2);
                command = QString("UPDATE проводки SET %1 WHERE код=%2;").arg(command).arg(record(index.row()).value(*key).toString());
                if (!TApplication::exemplar()->getDBFactory()->exec(command))
                {
                    database().rollback();
                    return false;
                }
            }
            database().commit();
            return true;
        }
    }
    return false;
}

void DocumentTableModel::setUpdateInfo(int column, int keyColumn, QString fieldName) {
    QStringList fields;
    fields << "кол" << "цена" << "сумма";
    if (fields.contains(fieldName)) {
        if (!updateKeys.contains(keyColumn))
            updateKeys.append(keyColumn);
        updateKeyFields.insert(column, keyColumn);
        updateFields.insert(column, fieldName);
    }
}
