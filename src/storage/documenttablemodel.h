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

#ifndef DOCUMENTTABLEMODEL_H
#define DOCUMENTTABLEMODEL_H

#include <QObject>
#include <QModelIndex>
#include <QVariant>
#include <QHash>
#include "mysqlrelationaltablemodel.h"

class TApplication;

struct UpdateInfoStruct {
    QString     originField;        // Наименование обновляемого поля в модели
    QString     table;              // Наименование обновляемой таблицы
    int         keyFieldColumn;     // Номер колонки ключевого поля в модели
    QString     field;              // Наименование обновляемого поля в таблице
    int         fieldColumn;        // Номер колонки обновляемого поля в модели
};

class DocumentTableModel : public MySqlRelationalTableModel {
    Q_OBJECT
public:
    DocumentTableModel();
    void setUpdateInfo(QString originField, QString table, QString field, int fieldColumn, int keyFieldColumn);
    virtual bool submit(const QModelIndex&);
private:
    QMap<int, UpdateInfoStruct>     updateInfo;
};

#endif // DOCUMENTTABLEMODEL_H
