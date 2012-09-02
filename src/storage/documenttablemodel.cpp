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
    DBFactory* db = TApplication::exemplar()->getDBFactory();
    if (editStrategy() == QSqlTableModel::OnManualSubmit) {
        if (updateInfo.contains(index.column()))
        {
            QString value;
            // Возьмем исходное значение из модели, которое необходимо сохранить в базу
            QVariant recValue = ((Document*)parent)->getValue(updateInfo.value(index.column()).originField);
            // Определим его тип для того, чтобы правильно подготовить текст команды сохранения для сервера
            switch (recValue.type())
            {
                case QVariant::String:
                    value = QString("'%1'").arg(recValue.toString());
                    break;
                default:
                    value = QString("%1").arg(recValue.toString());
                    break;
            }
            if (value.size() > 0)
            {
                // Сгенерируем для сервера команду сохранения значения из модели
                QString command;
                command = QString("UPDATE %1 SET %2=%3 WHERE %4=%5;").arg(db->getObjectName(updateInfo.value(index.column()).table))
                                                                     .arg(db->getObjectName(updateInfo.value(index.column()).field))
                                                                     .arg(value)
                                                                     .arg(db->getObjectName(updateInfo.value(index.column()).table + ".код"))
                                                                     .arg(record(index.row()).value(updateInfo.value(index.column()).keyFieldColumn).toString());
                if (!db->exec(command))
                {
                   return false;
                }
            }
            return true;
        }
    }
    return false;
}

void DocumentTableModel::setUpdateInfo(QString originField, QString table, QString field, int fieldColumn, int keyFieldColumn) {
    if (!updateInfo.contains(fieldColumn))
    {
        UpdateInfoStruct info;
        info.originField = originField;
        info.table = table;
        info.keyFieldColumn = keyFieldColumn;
        info.field = field;
        updateInfo.insert(fieldColumn, info);
    }
}
