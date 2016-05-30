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
    queryTableName = "";
    app = TApplication::exemplar();
    db = app->getDBFactory();
    fullDebugInfo = app->getFullDebugInfo();
}


Table::~Table()
{
}


QList<FieldType>* Table::getColumnsProperties()
{
    if (columnsProperties.count() > 0)
        return &columnsProperties;
    tableModel->setTestSelect(true);
    query();
    tableModel->setTestSelect(false);
    for (int i = 0; i < tableModel->record().count(); i++)
    {
        FieldType fld;
        fld.table  = queryTableName;
        fld.name      = tableModel->record().field(i).name();
        fld.type      = defineFieldType(tableModel->record().field(i).type());
        fld.length    = tableModel->record().field(i).length();
        fld.precision = tableModel->record().field(i).precision();
        fld.precision = fld.precision == -1 ? 0 : fld.precision;
        fld.constReadOnly = true;
        fld.readOnly = true;
        fld.level = 0;
        fld.column = fld.name;
        fld.header = "";
        fld.headerExist = false;
        fld.number    = 0;
        fld.constReadOnly = true;
        columnsProperties.append(fld);
    }
    return &columnsProperties;
}


QList<FieldType> Table::returnColumnsProperties()
{
    getColumnsProperties();
    return columnsProperties;
}


void Table::query(QString filter)
{
    tableModel->setFilter(filter);
    tableModel->setFullDebugInfo(fullDebugInfo);

    if (!fullDebugInfo)
    {
        QString command = QString("SELECT * FROM %1").arg(tableModel->tableName());
        if (filter.size() > 0)
            command.append(QString(" WHERE %1;").arg(filter));
        if (tableModel->isTestSelect())
            command.append(QString(" LIMIT 0;"));
        app->debug(1, "Query:(*) " + command);
    }

    if (!tableModel->select())
        app->showError(tableModel->lastError().text());
 }


bool Table::open()
{
    opened = false;
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
        app->showError(QString(QObject::trUtf8("Не существует таблица <%1>")).arg(tableName));
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
    QStringList fields;
    if (columnsProperties.size() == 0)
        columnsProperties = returnColumnsProperties();
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


QString Table::defineFieldType(QVariant::Type type)
{
    QString result;
    switch (type)
    {
        case QVariant::String:
            result = "CHARACTER VARYING";
            break;
        case QVariant::LongLong:
            result = "INTEGER";
            break;
        case QVariant::Int:
            result = "INTEGER";
            break;
        case QVariant::Double:
            result = "NUMERIC";
            break;
        case QVariant::Date:
            result = "DATE";
            break;
        case QVariant::DateTime:
            result = "DATETIME";
            break;
        default:
            app->showError(QString("Не найден тип %1 в методе <QString Table::defineFieldType(QVariant::Type type)>. Необходимо поправить исходный код.").arg(type));
    }
    return result;
}
