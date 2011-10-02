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
#include "mysqlquery.h"

class Table;

class MySqlRelationalTableModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    MySqlRelationalTableModel();
    QStringList getFieldsList();
    Q_INVOKABLE QString getSelectStatement() { return selectStatement(); }
    QString getSelectClause() const;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    int fieldIndex(const QString &) const;
    QString orderByClause() const;
    void setAlias(QString alias) { tableAlias = alias; }
    void setRelationalAlias(int column, QString alias) { tablesAliases.insert(column, alias); }
    virtual bool setData(const QModelIndex &, const QVariant &, int role = Qt::EditRole);
//    void setFieldsList(QStringList);
    void setRelation(int, const QSqlRelation &);
    void setRelation(int, int, const QSqlRelation &);
    void setSelectClause(QString string = "");
    void setSelectStatement(QString string = "");
    void setSortClause(QString sort) { sortClause = sort; }
    void setBlockUpdate(bool block) { blockUpdate = block; }
    virtual void setUpdateInfo(int, int, QString) { ; }
    virtual void setSort(int, Qt::SortOrder);
    void setPrepared(bool p = true) { isPrepared = p; }
    void setParent(Table* par) { parent = par; }
    bool relationsIsEmpty() { return relIsEmpty; }
    QString escapedRelationField(const QString &, const QString &) const;
    virtual QString selectStatement() const;
//    virtual QString getPreparedSelectStatement() const;
//    virtual bool submit(const QModelIndex& index) { Q_UNUSED(index); return QSqlRelationalTableModel::submit(); }
    virtual bool submit(const QModelIndex& index) { Q_UNUSED(index); return true; }
    virtual bool updateRowInTable(int, const QSqlRecord&);
    Q_INVOKABLE void setTable(const QString& str) { QSqlRelationalTableModel::setTable(str.toUtf8()); }
    Q_INVOKABLE MySqlQuery* query();
    Q_INVOKABLE int rowCount() { return QSqlRelationalTableModel::rowCount(); }
    Q_INVOKABLE bool select() { return QSqlRelationalTableModel::select(); }
    Q_INVOKABLE void setFilter(const QString &filter) { QSqlRelationalTableModel::setFilter(filter.toUtf8()); }

protected:
    Table* parent;
private:
    QMap<int, int> keyColumns;
    QList<int> insertedColumns;
    QMap<int, QString> tablesAliases;
    QStringList fieldsList;
    QString tableAlias;
    QString selectClause;
    QString selectCommand;
    QString sortClause;
    mutable QString preparedStatementName;
    mutable QString preparedStatement;
    bool relIsEmpty;
    bool isPrepared;
    bool blockUpdate;
    int sortColumn;
    Qt::SortOrder sortOrder;
};

#endif // MYSQLRELATIONALTABLEMODEL_H
