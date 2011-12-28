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
    virtual void setUpdateInfo(int, int, QString) { ; }

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
