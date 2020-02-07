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
#include <QtSql/QSqlField>
#include <QtScript/QScriptClass>

#include "../kernel/app.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"

Table::Table(QString, QObject *parent): QObject(parent)
{
    db = nullptr;
    tableModel = nullptr;
}


Table::~Table()
{
    if (tableModel != nullptr)
    {
        delete tableModel;
        tableModel = nullptr;
    }
}


void Table::postInitialize(QString name, QObject *parent)
{
    setParent(parent);
    app = TApplication::exemplar();
    db = app->getDBFactory();
    fullDebugInfo = app->getFullDebugInfo();
    opened = false;

    queryTableName = "";
    tableName = name.trimmed().toLower();
    tagName = tableName;
    sqlCommand = "";
}


bool Table::open(QString command)
{
    if (command.size() > 0)
        sqlCommand = command;
    opened = setTableModel();
    if (opened)
    {
        fieldList = getFieldsList();
        if (fieldList.count() == 0)
            opened = false;
    }
    return opened;
}


void Table::close()
{
/*
    if (tableModel != nullptr)
    {
        tableModel->clear();
    }
*/
    opened = false;
}


MySqlRelationalTableModel*  Table::getTableModel()
{
    return tableModel;
}


QString Table::transformSelectStatement(QString string)
{
    return string;
}


QString Table::getTableName()
{
    return tableName;
}


QString Table::getTagName()
{
    return tagName;
}


QString Table::getQueryTableName()
{
    return queryTableName;
}


void Table::setFullDebugInfo(bool full)
{
    fullDebugInfo = full;
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
    if (tableModel != nullptr)
    {
        tableModel->setFilter(filter);
        if (tableModel->rowCount() == 0)
        {
            tableModel->select();
        }

        tableModel->setFullDebugInfo(fullDebugInfo);

        if (!fullDebugInfo)
        {
            QString command;
            if (tableName.size() > 0)
            {
                QString fList;
                if (manualFieldList.count() > 0)
                {
                    fieldList = manualFieldList;
                    foreach (QString f, fieldList)
                    {
                        if (fList.size() > 0)
                            fList.append(",");
                        fList.append(f);
                    }
                }
                else
                    fList = "*";
                command = QString("SELECT %1 FROM %2").arg(fList).arg(tableName);
            }
            else if (sqlCommand.size() > 0)
                command = sqlCommand;
            if (command.size() > 0)
            {
                if (filter.size() > 0)
                {
                    if (command.contains(" WHERE "))
                        command.replace(" WHERE ", QString(" WHERE %1 AND ").arg(filter));
                    else
                        command.append(QString(" WHERE %1").arg(filter));
                }

                if (tableModel->isTestSelect())
                    command.append(QString(" LIMIT 0"));
                app->debug(1, "Query:(*) " + command);
            }
        }

        if (tableModel->lastError().isValid())
        {
           app->showError(tableModel->lastError().text());
        }
    }
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
    if (tableModel != nullptr)
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


void Table::setFieldsList(QStringList list)
{
    manualFieldList = list;
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
        case QVariant::Bool:
            result = "BOOLEAN";
            break;
        case QVariant::Invalid:
            result = "CHARACTER VARYING";
            break;
        default:
            app->showError(QString("Не найден тип %1 в методе <QString Table::defineFieldType(QVariant::Type type)>. Необходимо поправить исходный код.").arg(type));
    }
    return result;
}


TApplication* Table::getApp()
{
    return app;
}


void Table::setTagName(QString name)
{
    tagName = name;
}

