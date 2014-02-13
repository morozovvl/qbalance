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
#include <QtScript/QScriptValue>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtDesigner/QDesignerExportWidget>

#include "myitemdelegate.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"

class TApplication;
class DBFactory;
class FormGrid;
class MyItemDelegate;
struct FieldType;

class QDESIGNER_WIDGET_EXPORT TableView : public QTableView {
    Q_OBJECT

public:
    TableView(QWidget* = 0, FormGrid* = 0);
    ~TableView();

    virtual void                setFormGrid(FormGrid* par) { parent = par; }
    virtual void                setApp(TApplication*);
    virtual void                setTableModel(MySqlRelationalTableModel*);
    virtual void                setTagName(QString tag) { tagName = tag; }
    virtual bool                columnIsReadOnly();
    virtual void                selectNextColumn();         // Перемещает курсор в следующий столбец, разрешенный к редактированию
    virtual void                selectPreviousColumn();     // Перемещает курсор в предыдущий столбец, разрешенный к редактированию
    virtual void                setReadOnly(bool);
    virtual bool                setColumnsHeaders();
    virtual void                hideAllGridSections();
    virtual void                hideGridSection(QString);
    virtual void                showGridSection(QString);
    virtual void                showAllGridSections();

public slots:
    virtual void                selectRow(int = 0);

protected:
    virtual void                keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    virtual void                currentChanged(const QModelIndex &, const QModelIndex &);
    void                        focusInEvent(QFocusEvent*);

private:
    bool                        columnsHeadersSeted;
    int                         maxColumn;
    QString                     name;
    QString                     tagName;
    FormGrid*                   parent;
    QWidget*                    parentWidget;
    TApplication*               app;
    DBFactory*                  db;
    MySqlRelationalTableModel*  tableModel;
    QMap<int, QString>          columns;            // Список видимых столбцов и их порядок

    MyItemDelegate*             getColumnDelegate(FieldType);
};

#endif // TABLEVIEW_H
