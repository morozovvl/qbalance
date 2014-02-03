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
#include <QtCore/QUuid>
#include <QtSql/QSqlError>
#include <QtCore/QDateTime>
#include <QtSql/QSqlRecord>
#include <QtScript/QScriptClass>

#include "../kernel/app.h"
#include "../storage/mysqlrelationaltablemodel.h"

Table::Table(QString name, QObject *parent)
: QObject(parent)
, tableModel(0)
{
    opened = false;
    tableName = name.trimmed().toLower();
    tagName = tableName;
    app = TApplication::exemplar();
    db = app->getDBFactory();
}


QList<FieldType>* Table::getColumnsProperties()
{
    return &columnsProperties;
}


void Table::query(QString filter)
{
    if (tableModel->rowCount() > 0 && filter.size() > 0)
        tableModel->setFilter(filter);
    else
    {
        tableModel->setFilter(filter);
        if (!tableModel->select())
        {
            app->showError(tableModel->lastError().text());
        }
    }
    app->debug("Query: " + tableModel->selectStatement() + "\n");
 }


bool Table::open()
{
    opened = setTableModel();
    return opened;
}


void Table::close()
{
    if (tableModel != 0)
    {
        tableModel->clear();
        delete tableModel;
    }
    opened = false;
}


bool Table::setTableModel(int level)
{
    tableModel = new MySqlRelationalTableModel(tableName, this);
    db->getColumnsProperties(&columnsProperties, tableName, tableName, level);
    if (columnsProperties.size() == 0)
    {
        app->showError(QString(QObject::trUtf8("Не существует таблица %1")).arg(tableName));
        return false;
    }
    return true;
}


void Table::setOrderClause(QString sort)
{
    tableModel->setOrderClause(sort);
}


QStringList Table::getFieldsList()
{
//    return tableModel->getFieldsList();
    QStringList fields;
    for (int i = 0; i < columnsProperties.count(); i++)
    {
        fields << columnsProperties.at(i).column;
    }
    return fields;
}


QString Table::getFieldName(int i)
{
    return tableModel->getFieldName(i);
}


void Table::setReadOnly(bool ro)
{
    tableModel->setReadOnly(ro);
}


bool Table::isReadOnly()
{
    return tableModel->isReadOnly();
}
