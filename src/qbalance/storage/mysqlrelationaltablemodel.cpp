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
#include <QtCore/QMap>
#include <QtCore/QUuid>
#include <QtCore/QLocale>
#include <QDebug>
#include "mysqlrelationaltablemodel.h"
#include "../kernel/app.h"


MySqlRelationalTableModel::MySqlRelationalTableModel() : QSqlRelationalTableModel()
{
    parent = NULL;
    sortClause = "";
    isPrepared = false;
    readOnly = false;
    preparedStatementName = "";
    preparedStatement = "";
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    db = TApplication::exemplar()->getDBFactory();

//    setReadOnly(true);
}


bool MySqlRelationalTableModel::insertColumns(int column, int count, const QModelIndex & parent)
{
    if (QSqlQueryModel::insertColumns(column, count, parent))
    {
        for (int i = 0; i < count; i++)
            insertedColumns.append(column + i);
        return true;
    }
    return false;
}


int MySqlRelationalTableModel::fieldIndex(const QString &fieldName) const
{
    int result;
    result = QSqlTableModel::fieldIndex(fieldName);
    if (result >= 0)
        return result;      // Если искомое поле было в базовой таблице, то просто вернем его номер
    for (int i = 0; i < insertedColumns.size(); i++)
    {
        QString fldName = relation(insertedColumns[i]).tableName().toUpper() + "__" + relation(insertedColumns[i]).displayColumn();
        if (fieldName == fldName)
            return insertedColumns[i];
    }
    if (fieldsList.size() > 0 && fieldsList.contains(fieldName))
        return fieldsList.indexOf(fieldName);
    return -1;
}


bool MySqlRelationalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool lResult = false;
    if (indexInQuery(index).isValid() && !insertedColumns.contains(index.column()))
    {  // Если столбец не числится среди добавленных столбцов, для добавленных столбцов ничего не будем делать
        if (!readOnly && value != data(index))
        {   // Если данные разрешено модифицировать
            // и новые данные не равны старым
            QSqlRecord rec = record(index.row());
            if (rec.indexOf(TApplication::exemplar()->getDBFactory()->getObjectName("код")) != index.column())
            {   // Если мы не пытаемся поменять значение ключевого столбца
                rec.setValue(index.column(), value);
                rec.setGenerated(index.column(), true);
                for (int i = insertedColumns.count() - 1; i >= 0; i--)
                {   // Для корректной генерации команды сохранения
                    // уберем добавленные столбцы из записи
                    rec.remove(insertedColumns[i]);
                }
                lResult = QSqlRelationalTableModel::setData(index, value, role);
                emit dataChanged(index, index);
            }
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


QStringList MySqlRelationalTableModel::getFieldsList()
{
    if (fieldsList.count() == 0)
    {
        for (int i = 0; i < record().count(); i++)
        {
            fieldsList << record().fieldName(i).toUpper();
        }
    }
    return fieldsList;
}

/*
void MySqlRelationalTableModel::setFieldsList(QStringList list) {
    if (insertedColumns.size() == 0)                // Если реляции уже заданы, то нельзя переназначать список полей во избежание неправильной генерации SQL команды
        fieldsList = list;
}
*/

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


void MySqlRelationalTableModel::setSort(int column, Qt::SortOrder order)
{
    sortColumn = column;
    sortOrder = order;
    QSqlRelationalTableModel::setSort(column, order);
}


QString MySqlRelationalTableModel::orderByClause() const
{
    if (sortClause.size() > 0)
        return QString("ORDER BY %1").arg(sortClause.toUpper());
    QString s;
    QSqlField f = record().field(sortColumn);
    if (!f.isValid())
        return s;
    QString table;
    QString field;
    if (!relation(sortColumn).isValid())
    {
        table = database().driver()->escapeIdentifier(tableName(), QSqlDriver::TableName);
        field = database().driver()->escapeIdentifier(f.name(), QSqlDriver::FieldName);
    }
    else
    {
        QSqlRelation rel = relation(sortColumn);
        if (rel.isValid())
        {
            table = database().driver()->escapeIdentifier(rel.tableName(), QSqlDriver::TableName);
            field = database().driver()->escapeIdentifier(rel.displayColumn(), QSqlDriver::FieldName);
        }
    }
    if ((table.size() > 0) && (field.size() > 0))
    {
        s.append(QLatin1String("ORDER BY ")).append(table).append(QLatin1Char('.')).append(field);
        s += sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");
    }
    return s;
}


void MySqlRelationalTableModel::setSelectClause(QString string)
{
    if (string.size() == 0)
        selectClause = getSelectClause();
    else
        selectClause = string;
}


void MySqlRelationalTableModel::setSelectStatement(QString string)
{
    selectCommand = string;
}


QString MySqlRelationalTableModel::selectStatement() const
{
    QString query;
    if (selectCommand.size() > 0)
        query = selectCommand;
    else
    {
        if (selectClause.size() > 0)            // Если уже имеется готовый текст запроса
            query = selectClause;
        else                                    // Иначе создадим его заново
            query = getSelectClause();
        if (query.size() > 0)
        {
            if (!filter().isEmpty())
                query.append(QLatin1String(" WHERE ")).append(filter());
            if (!orderByClause().isEmpty())
                query.append(QLatin1Char(' ')).append(orderByClause());
        }
    }
    if (parent != NULL)
        query = parent->transformSelectStatement(query);

    return query;
}


QString MySqlRelationalTableModel::getSelectClause() const
{
    QString query;
    if (!tableName().isEmpty())
    {
        QString selectList;
        QString fromList;
        QStringList aliases;

        fromList = database().driver()->escapeIdentifier(tableName(), QSqlDriver::TableName);
        if (tableAlias.size() > 0)
        {
            fromList.append(" ").append(database().driver()->escapeIdentifier(tableAlias, QSqlDriver::TableName));
            aliases << tableAlias;
        }
        else
            aliases << tableName();
        QSqlRecord rec = record();
        for (int i = 0; i < rec.count(); ++i)               // составим список полей для секции SELECT
            if (!insertedColumns.contains(i))
            {           // в исходный список полей включим только те поля, которые не были добавлены при создании реляций
                if (tableAlias.size() > 0)
                {
                    selectList.append(escapedRelationField(tableAlias, rec.fieldName(i)));
                    selectList.append(QString::fromLatin1(" AS %1__%2").arg(tableAlias.toUpper()).arg(rec.fieldName(i).toUpper()));
                    selectList.append(QLatin1Char(','));
                }
                else
                    selectList.append(escapedRelationField(tableName(), rec.fieldName(i))).append(QLatin1Char(','));
            }
        if (insertedColumns.size() > 0) {
            for (QMap<int, int>::const_iterator it = keyColumns.constBegin(); it != keyColumns.constEnd(); it++)
            {
                QSqlRelation relation = QSqlRelationalTableModel::relation(it.key());
                QString alias = tablesAliases.contains(it.key()) ? tablesAliases.value(it.key()) : relation.tableName();
                selectList.append(escapedRelationField(alias, relation.displayColumn()));
                selectList.append(QString::fromLatin1(" AS %1__%2").arg(alias.toUpper()).arg(relation.displayColumn()));
                selectList.append(QLatin1Char(','));
                if (!aliases.contains(alias))
                {
                    fromList.append(" LEFT OUTER JOIN ").append(database().driver()->escapeIdentifier(relation.tableName(), QSqlDriver::TableName));
                    if (tablesAliases.value(it.key()).size() > 0 && QString(relation.tableName()).compare(tablesAliases.value(it.key())) != 0)          // если имя таблицы и ее алиас не совпадают
                        fromList.append(" ").append(database().driver()->escapeIdentifier(tablesAliases.value(it.key()), QSqlDriver::TableName));
                    fromList.append(" ON ").append(escapedRelationField((tableAlias.size() == 0 ? tableName() : tableAlias), rec.fieldName(it.value())));
                    fromList.append(QLatin1Char('='));
                    fromList.append(escapedRelationField(alias, relation.indexColumn()));
                    aliases << alias;
                }
            }
        }
        selectList.chop(1);
        query.append(QLatin1String("SELECT DISTINCT ")).append(selectList);;
        query.append(QLatin1String(" FROM ")).append(fromList);
    }
    return query;
}


QString MySqlRelationalTableModel::escapedRelationField(const QString &tableName, const QString &fieldName) const
{
    QString esc;
    esc.reserve(tableName.size() + fieldName.size() + 1);
    esc.append(tableName).append(QLatin1Char('.')).append(fieldName);
    return database().driver()->escapeIdentifier(esc, QSqlDriver::FieldName);
}


void MySqlRelationalTableModel::setUpdateInfo(QString originField, QString table, QString field, int fieldColumn, int keyFieldColumn)
{
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


int MySqlRelationalTableModel::submitCount()
{   // Подсчитывает, в скольких колонках произошли изменения
    int counter = 0;
    for (int i = 0; i < record().count(); i++)
    {
        QString fieldName = updateInfo.value(i).originField;
        if (fieldName.size() > 0)
        {
            QVariant newValue = ((Essence*)parent)->getValue(fieldName);
            QVariant oldValue = ((Essence*)parent)->getOldValue(fieldName);
            if (newValue != oldValue)
                counter++;
        }
    }
    return counter;
}


bool MySqlRelationalTableModel::submit()
{
    return QSqlRelationalTableModel::submit();
}


bool MySqlRelationalTableModel::submit(const QModelIndex& index)
{
    if (editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        if (updateInfo.contains(index.column()))
        {
            QString value;
            QString fieldName = updateInfo.value(index.column()).originField;
            QVariant recValue = ((Essence*)parent)->getValue(fieldName);
            if (recValue != ((Essence*)parent)->getOldValue(fieldName))
            {
                // Возьмем исходное значение из модели, которое необходимо сохранить в базу
                // Определим его тип для того, чтобы правильно подготовить текст команды сохранения для сервера
                switch (recValue.type())
                {
                    case QVariant::String:
                        value = QString("'%1'").arg(recValue.toString().trimmed());
                        break;
                    case QVariant::Date:
                        value = QString("'%1'").arg(recValue.toString());
                        break;
                    case QVariant::DateTime:
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
                                                                         .arg(db->getObjectName(updateInfo.value(index.column()).table + "." + updateInfo.value(index.column()).field))
                                                                         .arg(value)
                                                                         .arg(db->getObjectName(updateInfo.value(index.column()).table + ".код"))
                                                                         .arg(record(index.row()).value(updateInfo.value(index.column()).keyFieldColumn).toString());
                    if (!db->exec(command))
                    {
                       return false;
                    }
                }
            }
        }
    }
    return true;
}

