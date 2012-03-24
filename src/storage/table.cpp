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

#include "table.h"
#include <QUuid>
#include <QSqlError>
#include <QDateTime>
#include <QSqlRecord>
#include <QScriptClass>

#include "../kernel/app.h"
#include "mysqlrelationaltablemodel.h"

Table::Table(QString name, QObject *parent)
: QObject(parent)
, tableModel(NULL)
{
    opened = false;
    tableName = name.trimmed();
    tagName = tableName;
    db = TApplication::exemplar()->getDBFactory();
}


Table::~Table()
{
}


QMap<int, FieldType>* Table::getColumnsProperties()
{
    return &columnsProperties;
}


bool Table::relationsIsEmpty()
{
    return tableModel->relationsIsEmpty();
}


void Table::query(QString filter)
{
    tableModel->setFilter(filter);
    if (tableModel->rowCount() == 0)
    {
        tableModel->select();
    }
    TApplication::debug(" Query: " + tableModel->selectStatement() + "\n");
 }


bool Table::open()
{
    setTableModel();
    db->getColumnsProperties(&columnsProperties, tableName);
    if (tableModel->lastError().type() == QSqlError::NoError)
    {
        opened = true;
    }
    else
    {// Не удалось открыть таблицу, сообщим об ошибке
        QSqlError error = tableModel->lastError();
        TApplication::exemplar()->showError(error.text());
    }
    return opened;
}


void Table::close()
{
    tableModel->clear();
    delete tableModel;
    opened = false;
}


void Table::setTableModel()
{
    tableModel = new MySqlRelationalTableModel();
    tableModel->setParent(this);
    tableModel->setTable(tableName);
}


QStringList Table::getFieldsList()
{
    return tableModel->getFieldsList();
}


QString Table::getFieldName(int i)
{
    return tableModel->getFieldName(i);
}
