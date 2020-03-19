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

#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlField>
#include <QtSql/QSqlResult>
#include <QtCore/QStringList>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtCore/QHash>
#include <QtCore/QUuid>
#include <QtCore/QLocale>
#include <QtCore/QDebug>
#include "mysqlrelationaltablemodel.h"
#include "../kernel/app.h"
#include "../kernel/essence.h"
#include "../storage/dbfactory.h"


MySqlRelationalTableModel::MySqlRelationalTableModel(QString tName, Table* par) : QSqlRelationalTableModel()
{
    parent = par;
    tableName = tName;
    setTable(tableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    sortClause = "";
    readOnly = false;
    app = TApplication::exemplar();
    db = app->getDBFactory();
    selectCommand = "";
    testSelect = false;
    fullDebugInfo = false;
    updateInfo = new QHash<int, UpdateInfoStruct>;
}


MySqlRelationalTableModel::~MySqlRelationalTableModel()
{
    updateInfo->clear();
    delete updateInfo;
    updateInfo = 0 /*nullptr*/;
}


void MySqlRelationalTableModel::setRelationalAlias(int column, QString alias)
{
    tablesAliases.insert(column, alias);
}


QString MySqlRelationalTableModel::getSelectStatement()
{
    return selectCommand;
}


void MySqlRelationalTableModel::setSelectStatement(QString string)
{
    selectCommand = string;
}


bool MySqlRelationalTableModel::select()
{
    bool result =QSqlRelationalTableModel::select();

    while (canFetchMore())
        fetchMore();

    return result;
}


void MySqlRelationalTableModel::setFilter(const QString &filter)
{
    QSqlRelationalTableModel::setFilter(filter);
}

void MySqlRelationalTableModel::setReadOnly(bool ro)
{
    readOnly = ro;
}


bool MySqlRelationalTableModel::isReadOnly()
{
    return readOnly;
}


QString MySqlRelationalTableModel::getFieldName(int i)
{
    return record().fieldName(i);
}


void MySqlRelationalTableModel::setTestSelect(bool test)
{
    testSelect = test;
}


bool MySqlRelationalTableModel::isTestSelect()
{
    return testSelect;
}


void MySqlRelationalTableModel::setFullDebugInfo(bool full)
{
    fullDebugInfo = full;
}


int MySqlRelationalTableModel::fieldIndex(const QString &fieldName) const
{
    int result;
    result = QSqlTableModel::fieldIndex(fieldName);
    if (result >= 0)
        return result;      // Если искомое поле было в базовой таблице, то просто вернем его номер
    return getFieldsList().indexOf(fieldName);
}



bool MySqlRelationalTableModel::setData(const QModelIndex &index, const QVariant &value, bool readOnly, int role)
{
    bool lResult = false;
    if (index.isValid() && rowCount() > 0)
    {  // Если столбец не числится среди добавленных столбцов, для добавленных столбцов ничего не будем делать
        if (value != data(index))
        {   // Если данные разрешено модифицировать
            // и новые данные не равны старым
            lResult = QSqlRelationalTableModel::setData(index, value, role);  // QSqlQuery::value: not positioned on a valid record  // POSSIBLY MEMORY LEAK
            if (!readOnly)
                prepareCommand(index);
        }
        else
        {
            lResult = true;
        }
    }
    return lResult;
}


bool MySqlRelationalTableModel::updateRowInTable(int row, const QSqlRecord &values)
{
    if (!readOnly)
        return QSqlRelationalTableModel::updateRowInTable(row, values);
    return true;
}


QStringList MySqlRelationalTableModel::getFieldsList() const
{
    QStringList fields;
    for (int i = 0; i < record().count(); i++)
    {
        fields << record().fieldName(i);
    }
    return fields;
}


void MySqlRelationalTableModel::setRelation(int column, const QSqlRelation &relation)
{
    QSqlRelationalTableModel::setRelation(column, relation);
}


void MySqlRelationalTableModel::setRelation(int column, int keyColumn, const QSqlRelation &rel)
{
// устанавливает реляционную связь relation для колонки column на основании ключа в колонке keyColumn
    if ((column >= 0 && column < columnCount()) &&          // Если колонка с таким номером присутствует
            !relation(column).isValid() &&                    // Если для колонки column еще не установлена реляционная связь
            relation(keyColumn).isValid())
    {                  // а для колонки keyColumn реляционная связь наоборот установлена
        keyColumns.insert(column, keyColumn);
        QSqlRelationalTableModel::setRelation(column, rel);
    }
}


void MySqlRelationalTableModel::setOrderClause(QString sort) {
    sortClause = sort;
}


QString MySqlRelationalTableModel::orderByClause() const
{
    return sortClause.size() > 0 ? QString("ORDER BY %1").arg(sortClause) : "";
}


QString MySqlRelationalTableModel::selectStatement() const
{
    QString query;
    query = selectCommand;
    if (!orderByClause().isEmpty())
    {
        int lastIndex = query.lastIndexOf("LIMIT");
        if (lastIndex == -1)
        {
            if (QString::compare(parent->metaObject()->className(), "Document", Qt::CaseInsensitive) != 0)
                query.append(" " + orderByClause());
        }
        else
            query.replace(lastIndex, 5, orderByClause() + " LIMIT");
    }
    if (!filter().isEmpty())
    {
        int lastIndex = query.lastIndexOf("ORDER BY");
        if (lastIndex == -1)
            query.append(" WHERE ").append(filter());
        else
            query.replace(lastIndex, 8, "WHERE " + filter() + " ORDER BY");
    }
    if (parent != 0 /*nullptr*/)
        query = parent->transformSelectStatement(query);
    if (testSelect)
        query = "SELECT * FROM (" + query + ") s LIMIT 0";

    if (fullDebugInfo)
        app->debug(1, "Query: " + query);

    return query;
}


QString MySqlRelationalTableModel::escapedRelationField(const QString &tableName, const QString &fieldName) const
{
    QString esc;
    esc.reserve(tableName.size() + fieldName.size() + 1);
    esc.append(tableName).append(QLatin1Char('.')).append(fieldName);
    return database().driver()->escapeIdentifier(esc, QSqlDriver::FieldName);
}


void MySqlRelationalTableModel::setUpdateInfo(QString originField, QString table, QString field, QString type, int len, int prec, int fieldColumn, int keyFieldColumn)
{
    if (!updateInfo->contains(fieldColumn) && field.toUpper() != "FTS")
    {
        UpdateInfoStruct info;
        info.originField = originField;
        info.table = table;
        info.keyFieldColumn = keyFieldColumn;
        info.field = field;
        info.type = type;
        info.length = len;
        info.precision = prec;
        updateInfo->insert(fieldColumn, info);
    }
}


bool MySqlRelationalTableModel::prepareCommand(const QModelIndex& index)
{
    if (editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        int columnIndex = index.column();
        int rowIndex = index.row();
        if (updateInfo->contains(columnIndex))
        {
            QString value;
            QString fieldName = updateInfo->value(columnIndex).originField;
            QVariant recValue = static_cast<Essence*>(parent)->getValue(fieldName, rowIndex);
            // Возьмем исходное значение из модели, которое необходимо сохранить в базу
            // Определим его тип для того, чтобы правильно подготовить текст команды сохранения для сервера
            QString type = updateInfo->value(columnIndex).type.toUpper();

            value = prepareValueToWrite(type, recValue, updateInfo->value(columnIndex).precision);

            // Сгенерируем для сервера команду сохранения значения из модели
            if (value.size() > 0)
            {
                int id = record(rowIndex).value(updateInfo->value(columnIndex).keyFieldColumn).toInt();
                if (id > 0)
                {
                    UpdateValues values;
                    values.table = updateInfo->value(columnIndex).table;
                    values.field = updateInfo->value(columnIndex).field;
                    values.value = value;
                    values.recId = id;
                    db->appendCommand(values);
                }
            }
        }
    }
    return true;
}


QString MySqlRelationalTableModel::prepareValueToWrite(QString type, QVariant recValue, int prec)
{
    QString value = "";

    if (type == "CHARACTER" || type == "CHARACTER VARYING" || type == "TEXT")
    {
        value = recValue.toString();
        value.replace("'", "''");
        value = QString("'%1'").arg(value);
    }
    else if (type == "DATE" || type == "DATETIME" || type.left(9) == "TIMESTAMP")
    {
        value = recValue.toString();
        if (value.size() > 0)
            value = QString("'%1'").arg(value);
    }
    else if (type == "BYTEA")
    {
        value = recValue.toByteArray().toHex();
        if (value.size() > 0)
            value = QString("'%1'").arg(value);
    }
    else if (type == "NUMERIC")
    {
        value = recValue.toString();
        if (value.size() > 0)
            value = QString("%1").arg(value.toDouble(), 0, 'f', prec);
    }
    else
    {
        value = recValue.toString();
    }
    return value;
}


QVariant MySqlRelationalTableModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical && QSqlRelationalTableModel::headerData(section,Qt::Vertical) == "*")
    {
        return section + 1;
    }
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}
