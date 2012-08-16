/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

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
                QString id = record(index.row()).value(*key).toString();
                if (id.size() > 0)
                {
                    command = QString("UPDATE проводки SET %1 WHERE код=%2;").arg(command).arg(id);
                    if (!TApplication::exemplar()->getDBFactory()->exec(command))
                    {
                        database().rollback();
                        return false;
                    }
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
