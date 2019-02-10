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

#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRecord>


class Table;
class TApplication;
class DBFactory;

struct UpdateInfoStruct {
    QString     originField;        // Наименование обновляемого поля в модели
    QString     table;              // Наименование обновляемой таблицы
    int         keyFieldColumn;     // Номер колонки ключевого поля в модели
    QString     field;              // Наименование обновляемого поля в таблице
    QString     type;
    int         length;
    int         precision;
};

class MySqlRelationalTableModel : public QSqlRelationalTableModel {
    Q_OBJECT

public:
    MySqlRelationalTableModel(QString, Table* = 0);
    ~MySqlRelationalTableModel();

// Функции, помогающие усовершенствовать механизм создания реляционных отношений
    virtual int fieldIndex(const QString &) const;
    virtual void setRelation(int, const QSqlRelation &);
    virtual void setRelation(int, int, const QSqlRelation &);
    virtual void setRelationalAlias(int column, QString alias);

// Функции, помогающие в генерации SQL запросов и работающие с ним
    QString virtual orderByClause() const;
    QString virtual escapedRelationField(const QString &, const QString &) const;
    virtual QString selectStatement() const;
    QString virtual getSelectStatement();
    virtual void setSelectStatement(QString string = "");
    virtual void setOrderClause(QString);
    Q_INVOKABLE virtual bool select();
    Q_INVOKABLE virtual void setFilter(const QString &filter);

// Функции для сохранения данных
    virtual void setReadOnly(bool ro);
    virtual bool isReadOnly();
    virtual bool setData(const QModelIndex &, const QVariant &, bool = false, int role = Qt::EditRole);
    virtual bool updateRowInTable(int, const QSqlRecord&);
    virtual void setUpdateInfo(QString originField, QString table, QString field, QString type, int length, int prec, int fieldColumn, int keyFieldColumn);
    virtual bool prepareCommand(const QModelIndex&);        // Готовит SQL команды для сохранения изменений
    QString prepareValueToWrite(QString, QVariant, int);

// Прочие функции
    virtual QStringList getFieldsList() const;
    virtual QString getFieldName(int i);
    virtual void    setTestSelect(bool test);
    virtual bool    isTestSelect();

    virtual QVariant headerData (int, Qt::Orientation, int = Qt::DisplayRole) const;
    void            setFullDebugInfo(bool full);

protected:
    Table*                  parent;
private:
// Свойства для механизма реляционных отношений
    QHash<int, int>          keyColumns;
    QHash<int, QString>      tablesAliases;

// Свойства для обслуживания SQL запросов
    QString                 selectCommand;
    QString                 sortClause;
    QHash<int, UpdateInfoStruct>     updateInfo;

// Прочие свойства
    QString                 tableAlias;
    QString                 tableName;
    bool                    readOnly;
    TApplication*           app;
    DBFactory*              db;
    bool                    testSelect;
    bool                    fullDebugInfo;
};

#endif // MYSQLRELATIONALTABLEMODEL_H
