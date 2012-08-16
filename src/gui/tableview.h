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

#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QWidget>
#include <QAbstractItemDelegate>
#include <QDebug>
#include <QScriptValue>
#include <QScriptContext>
#include <QScriptEngine>
#include "myitemdelegate.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"

class TApplication;
class FormGrid;
struct FieldType;

class TableView : public QTableView {
    Q_OBJECT

public:
    TableView(QWidget* = 0, FormGrid* = 0);
    ~TableView();

    void                        setFormGrid(FormGrid* par) { parent = par; }
    void                        setApp(TApplication* a) { app = a; }
    void                        setTableModel(MySqlRelationalTableModel*);
    void                        setTagName(QString tag) { tagName = tag; }

signals:
    void                        rowChanged();

protected:
    virtual void                keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    virtual void                currentChanged(const QModelIndex &, const QModelIndex &);

private:
    QString                     name;
    QString                     tagName;
    FormGrid*                   parent;
    QWidget*                    parentWidget;
    TApplication*               app;
    MySqlRelationalTableModel*  tableModel;


    void                        setColumnsHeaders();
    MyItemDelegate*             getColumnDelegate(FieldType);
    void                        selectNextColumn();         // Перемещает курсор в следующий столбец, разрешенный к редактированию
};

#endif // TABLEVIEW_H
