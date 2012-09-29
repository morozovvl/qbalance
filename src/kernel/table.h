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

#ifndef TABLE_H
#define TABLE_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QMap>
#include "../storage/dbfactory.h"
#include "../storage/mysqlrelationaltablemodel.h"

class TApplication;
class MySqlRelationalTableModel;
struct FieldType;

class Table : public QObject {
    Q_OBJECT

public:
    Table(QString table = "", QObject *parent = 0);

    Q_INVOKABLE virtual bool            open();
    Q_INVOKABLE virtual void            close();
    Q_INVOKABLE virtual void            query(QString filter = "");

    bool                                relationsIsEmpty();
    QList<FieldType>*                   getColumnsProperties();
    MySqlRelationalTableModel*          getMyRelationalTableModel() { return tableModel; }
    QSqlTableModel*                     getTableModel() { return (QSqlTableModel*)tableModel; }
    virtual QString                     transformSelectStatement(QString string) { return string; }

    Q_INVOKABLE QStringList             getFieldsList();
    Q_INVOKABLE QString                 getFieldName(int);
    Q_INVOKABLE QString                 getTableName() { return tableName; }
    QString                             getTagName() { return tagName; }

protected:
    DBFactory*                          db;
    bool                                opened;
    QString                             tableName;
    QString                             tagName;            // Тэг, на основе которого будут создаваться имена конфигураций форм и создаваться список полей табличной части
    MySqlRelationalTableModel*          tableModel;
//***    QMap<int, FieldType>                columnsProperties;
    QList<FieldType>                    columnsProperties;
    virtual void                        setTableModel();
};

#endif // TABLE_H
