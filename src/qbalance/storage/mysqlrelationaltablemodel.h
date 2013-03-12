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

#ifndef MYSQLRELATIONALTABLEMODEL_H
#define MYSQLRELATIONALTABLEMODEL_H

#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRecord>

#include "../kernel/table.h"

class Table;
class DBFactory;

struct UpdateInfoStruct {
    QString     originField;        // Наименование обновляемого поля в модели
    QString     table;              // Наименование обновляемой таблицы
    int         keyFieldColumn;     // Номер колонки ключевого поля в модели
    QString     field;              // Наименование обновляемого поля в таблице
//    int         fieldColumn;        // Номер колонки обновляемого поля в модели
};

class MySqlRelationalTableModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    MySqlRelationalTableModel();
    void setParent(Table* par) { parent = par; }
    Q_INVOKABLE void setTable(const QString& str) { QSqlRelationalTableModel::setTable(str); }

// Функции, помогающие усовершенствовать механизм создания реляционных отношений
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    virtual int fieldIndex(const QString &) const;
    void setRelation(int, const QSqlRelation &);
    void setRelation(int, int, const QSqlRelation &);
    void setRelationalAlias(int column, QString alias) { tablesAliases.insert(column, alias); }

// Функции, помогающие в генерации SQL запросов и работающие с ним
    Q_INVOKABLE QString getSelectStatement() { return selectStatement(); }
    QString getSelectClause() const;
    QString orderByClause() const;
    QString escapedRelationField(const QString &, const QString &) const;
    virtual QString selectStatement() const;
    void setSelectClause(QString string = "");
    void setSelectStatement(QString string = "");
    void setSortClause(QString sort) { sortClause = sort; }
    virtual void setSort(int, Qt::SortOrder);
    void setPrepared(bool p = true) { isPrepared = p; }
    Q_INVOKABLE bool select() { return QSqlRelationalTableModel::select(); }
    Q_INVOKABLE void setFilter(const QString &filter) { QSqlRelationalTableModel::setFilter(filter); }
    Q_INVOKABLE int rowCount() { return QSqlRelationalTableModel::rowCount(); }

// Функции для сохранения данных
    void setReadOnly(bool ro) { readOnly = ro; }
    bool isReadOnly() { return readOnly; }
    virtual bool setData(const QModelIndex &, const QVariant &, int role = Qt::EditRole);
    virtual bool submit(const QModelIndex&, bool = false);
    virtual bool submit();
    int submitCount();
    virtual bool updateRowInTable(int, const QSqlRecord&);
    virtual void setUpdateInfo(QString originField, QString table, QString field, int fieldColumn, int keyFieldColumn);

// Прочие функции
    QStringList getFieldsList();
    QString getFieldName(int i) { return record().fieldName(i); }
    void setAlias(QString alias) { tableAlias = alias; }


protected:
    Table*                  parent;
private:
// Свойства для механизма реляционных отношений
    QMap<int, int>          keyColumns;
    QList<int>              insertedColumns;
    QMap<int, QString>      tablesAliases;

// Свойства для обслуживания SQL запросов
    QString                 selectClause;
    QString                 selectCommand;
    QString                 sortClause;
    mutable QString         preparedStatementName;
    mutable QString         preparedStatement;
    bool                    isPrepared;
    int                     sortColumn;
    Qt::SortOrder           sortOrder;
    QMap<int, UpdateInfoStruct>     updateInfo;

// Прочие свойства
    QStringList             fieldsList;
    QString                 tableAlias;
    bool                    readOnly;

    DBFactory*              db;
};

#endif // MYSQLRELATIONALTABLEMODEL_H
