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

class DocumentTableModel : public MySqlRelationalTableModel {
    Q_OBJECT
public:
    DocumentTableModel();
    void setUpdateInfo(int, int, QString);
    virtual bool submit(const QModelIndex&);
private:
    // Структуры updateKeys и updateFields хранят записи, необходимые для генерации команды сохранения данных
    QList<int> updateKeys;                   // Список ключевых полей
    QHash<int, int> updateKeyFields;   // Хранит номер ключевого столбца
    QHash<int, QString> updateFields;   // Хранит имя поля в БД для текущего столбца
};

#endif // DOCUMENTTABLEMODEL_H
