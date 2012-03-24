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

#include <QModelIndex>
#include <QVariant>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QMap>
#include <QList>
#include <QStringList>

#include "table.h"

class Table;

class MySqlRelationalTableModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    MySqlRelationalTableModel();
    void setParent(Table* par) { parent = par; }
    Q_INVOKABLE void setTable(const QString& str) { QSqlRelationalTableModel::setTable(str); }

// Функции, помогающие усовершенствовать механизм создания реляционных отношений
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    int fieldIndex(const QString &) const;
    bool relationsIsEmpty() { return relIsEmpty; }
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
    virtual bool setData(const QModelIndex &, const QVariant &, int role = Qt::EditRole);
    void setBlockUpdate(bool block) { blockUpdate = block; }
    virtual bool submit(const QModelIndex& index) { Q_UNUSED(index); return QSqlRelationalTableModel::submit(); }
    virtual bool updateRowInTable(int, const QSqlRecord&);
    virtual void setUpdateInfo(int, int, QString) { ; }


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
    bool relIsEmpty;

// Свойства для обслуживания SQL запросов
    QString                 selectClause;
    QString                 selectCommand;
    QString                 sortClause;
    mutable QString         preparedStatementName;
    mutable QString         preparedStatement;
    bool                    isPrepared;
    int                     sortColumn;
    Qt::SortOrder           sortOrder;

// Прочие свойства
    QStringList             fieldsList;
    QString                 tableAlias;
    bool                    blockUpdate;
};

#endif // MYSQLRELATIONALTABLEMODEL_H
