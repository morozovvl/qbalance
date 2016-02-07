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


MySqlRelationalTableModel::MySqlRelationalTableModel(QString tableName, Table* par) : QSqlRelationalTableModel()
{
    parent = par;
    setTable(tableName);
    sortClause = "";
    readOnly = false;
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    app = TApplication::exemplar();
    db = app->getDBFactory();
    selectCommand = "";
    testSelect = false;
}


MySqlRelationalTableModel::~MySqlRelationalTableModel()
{
    updateInfo.clear();
}


int MySqlRelationalTableModel::fieldIndex(const QString &fieldName) const
{
    int result;
    result = QSqlTableModel::fieldIndex(fieldName);
    if (result >= 0)
        return result;      // Если искомое поле было в базовой таблице, то просто вернем его номер
    return getFieldsList().indexOf(fieldName);
}



bool MySqlRelationalTableModel::setData(const QModelIndex &index, const QVariant &value, bool force, int role)
{
    bool lResult = false;
    if ((index.isValid() || force) && rowCount() > 0)
    {  // Если столбец не числится среди добавленных столбцов, для добавленных столбцов ничего не будем делать
        if (!readOnly && value != data(index))
        {   // Если данные разрешено модифицировать
            // и новые данные не равны старым
            lResult = QSqlTableModel::setData(index, value, role);
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
            query.append(" " + orderByClause());
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
    if (parent != 0)
        query = parent->transformSelectStatement(query);
    if (testSelect)
        query = "SELECT * FROM (" + query + ")s LIMIT 0";
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
    if (!updateInfo.contains(fieldColumn))
    {
        UpdateInfoStruct info;
        info.originField = originField;
        info.table = table;
        info.keyFieldColumn = keyFieldColumn;
        info.field = field;
        info.type = type;
        info.length = len;
        info.precision = prec;
        updateInfo.insert(fieldColumn, info);
    }
}


bool MySqlRelationalTableModel::submit(const QModelIndex& index)
{
    bool write = true;
    if (editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        if (updateInfo.contains(index.column()))
        {
            QString value;
            QString fieldName = updateInfo.value(index.column()).originField;
            int length = updateInfo.value(index.column()).length;
            QVariant recValue = ((Essence*)parent)->getValue(fieldName, index.row());
            // Возьмем исходное значение из модели, которое необходимо сохранить в базу
            // Определим его тип для того, чтобы правильно подготовить текст команды сохранения для сервера
            QString type = updateInfo.value(index.column()).type.toUpper();
            if (type == "CHARACTER" || type == "CHARACTER VARYING")
            {
                value = QString("'%1'").arg(recValue.toString().trimmed().left(length));
            }
            else if (type == "TEXT")
            {
                value = QString("'%1'").arg(recValue.toString().trimmed());
            }
            else if (type == "DATE")
            {
                value = recValue.toString();
                if (value.size() == 0)
                    write = false;
                else
                    value = QString("'%1'").arg(value);
            }
            else if (type == "DATETIME")
            {
                value = recValue.toString();
                if (value.size() == 0)
                    write = false;
                else
                    value = QString("'%1'").arg(value);
            }
            else if (type == "BYTEA")
            {
                value = recValue.toByteArray().toHex();
                if (value.size() == 0)
                    write = false;
                else
                    value = QString("'%1'").arg(value);
            }
            else if (type == "NUMERIC")
            {
                value = recValue.toString();
                if (value.size() == 0)
                    write = false;
                else
                {
                    int prec = updateInfo.value(index.column()).precision;
                    value = QString("%1").arg(value.toDouble(), 0, 'f', prec);
                }
            }
            else
            {
                value = QString("%1").arg(recValue.toString().trimmed());
            }
            // Сгенерируем для сервера команду сохранения значения из модели
            if (write)
            {
                int id = record(index.row()).value(updateInfo.value(index.column()).keyFieldColumn).toInt();
                if (id > 0)
                {
                    UpdateValues values;
                    values.table = updateInfo.value(index.column()).table;
                    values.field = updateInfo.value(index.column()).field;
                    values.value = value;
                    values.recId = id;
                    db->appendCommand(values);
                }
            }
        }
    }
    return true;
}


QVariant MySqlRelationalTableModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical && QSqlRelationalTableModel::headerData(section,Qt::Vertical) == "*")
    {
        return section + 1;
    }
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}
