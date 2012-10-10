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

#include <QLineEdit>
#include <QTableView>
#include <QScriptContextInfo>
#include "../kernel/app.h"
#include "tableview.h"
#include "formgrid.h"
#include "../kernel/table.h"
#include "mylineitemdelegate.h"
#include "mynumericitemdelegate.h"
#include "mybooleanitemdelegate.h"


TableView::TableView(QWidget* pwgt, FormGrid* par): QTableView(pwgt)
{
    parent = par;
    parentWidget = pwgt;
    name = "TableView";
    app = 0;
    db = 0;
    tableModel = 0;
    if (verticalHeader()->minimumSectionSize() > 0)
        verticalHeader()->setDefaultSectionSize(verticalHeader()->minimumSectionSize());
}


TableView::~TableView()
{
    QItemSelectionModel *oldModel = selectionModel();
    delete oldModel;
}


void    TableView::setApp(TApplication* a)
{
    app = a;
    db = app->getDBFactory();
}



void TableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QTableView::currentChanged(current, previous);
    if (parent != 0)
    {
        if (current.row() != previous.row())
            emit rowChanged();
    }
}


void TableView::keyPressEvent(QKeyEvent* event)
{
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))
    {
        if (event->modifiers() == Qt::ControlModifier)
        {              // Были нажаты клавиши модификации
                       // и <Enter>
            parent->cmdOk();
            return;
        }
        else
        {
//            selectNextColumn();
            return;
        }
    }
    else
    {
        if (event->key() == Qt::Key_F2)
        {
            parent->cmdView();
            return;
        }
    }
    QTableView::keyPressEvent(event);
}


void TableView::setTableModel(MySqlRelationalTableModel* model)
{
    if (model != 0)
    {
        tableModel = model;
        QTableView::setModel(tableModel);
        if (parent != 0)
        {
            // Установим заголовки и делегаты полей
            setColumnsHeaders();
            connect(tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));
        }
    }
}


void TableView::setColumnsHeaders()
{
    QHeaderView* header = horizontalHeader();
    header->setMovable(true);
    header->setSortIndicatorShown(true);
    QList<FieldType>* fields = parent->getParent()->getColumnsProperties();
    db->getColumnsHeaders(tagName, fields);
    if (fields->count() > 0)
    {
        QMap<int, QString> columns;
        for (int i = 0; i < fields->count(); i++)
        {
            int logicalIndex = tableModel->fieldIndex(fields->at(i).column);
            if (fields->at(i).number > 0)
            {
                columns.insert(fields->at(i).number - 1, fields->at(i).column);
                MyItemDelegate* delegate = getColumnDelegate(fields->at(i));
                if (delegate != 0)
                {
                    connect(delegate, SIGNAL(closeEditor( QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate()));
                    delegate->setReadOnly(fields->at(i).readOnly);
                    setItemDelegateForColumn(logicalIndex, delegate);
                }
                tableModel->setHeaderData(logicalIndex, Qt::Horizontal, fields->at(i).header);
            }
            else
            {
                header->hideSection(logicalIndex);
            }
        }
        // Установим порядок столбцов
        foreach (int i, columns.keys())
        {
            int logicalIndex = tableModel->fieldIndex(columns.value(i));
            int oldIndex = header->visualIndex(logicalIndex);
            header->moveSection(oldIndex, i);
        }
    }
}


MyItemDelegate* TableView::getColumnDelegate(FieldType fld)
{
    if (fld.type.toUpper() == "NUMERIC" ||
        fld.type.toUpper() == "INTEGER")
    {     // для числовых полей зададим свой самодельный делегат
        MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(parentWidget, fld.length, fld.precision);
        return (MyItemDelegate*)numericDelegate;
    } else if (fld.type.toUpper() == "BOOLEAN")
           {
                MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(parentWidget);
                return (MyItemDelegate*)booleanDelegate;
           } else
           {
                if (fld.type.toUpper() == "CHARACTER" ||
                    fld.type.toUpper() == "CHARACTER VARYING")
                {
                    MyLineItemDelegate* textDelegate = new MyLineItemDelegate(parentWidget);
                    return (MyItemDelegate*)textDelegate;
                }
           }
    return 0;
}


void TableView::selectNextColumn()
// Ищет следующую колонку для редактирования
{
    QModelIndex index = currentIndex();
    int column = index.column();
    while (true)
    {
        column++;   // Перейдем в следующий столбец
        QModelIndex newIndex = index.sibling(index.row(), column);
        if (newIndex.row() == -1 && newIndex.column() == -1)
            break;
        if (!horizontalHeader()->isSectionHidden(column))
        {
            setCurrentIndex(newIndex);
            MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(column);
            if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
                break;
        }
    }
}
