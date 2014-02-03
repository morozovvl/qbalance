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
#include <QtScript/QScriptContextInfo>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>
#include "../kernel/app.h"
#include "tableview.h"
#include "formgrid.h"
#include "../kernel/table.h"
#include "mylineitemdelegate.h"
#include "mynumericitemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mydateitemdelegate.h"


TableView::TableView(QWidget* pwgt, FormGrid* par): QTableView(pwgt)
{
    parent = par;
    parentWidget = pwgt;
    name = "TableView";
    app = 0;
    db = 0;
    tableModel = 0;
    columnsHeadersSeted = false;
    if (verticalHeader()->minimumSectionSize() > 0)
        verticalHeader()->setDefaultSectionSize(verticalHeader()->minimumSectionSize());
}


TableView::~TableView()
{
    QItemSelectionModel *oldModel = selectionModel();
    delete oldModel;
}


void TableView::setApp(TApplication* a)
{
    app = a;
    db = app->getDBFactory();
}



void TableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QTableView::currentChanged(current, previous);
    if (parent != 0)
    {
        if ((current.row() != previous.row()) && tableModel->rowCount() > 0)
        {
            parent->showPhoto();
            parent->getParent()->afterRowChanged();
        }
    }
}


void TableView::keyPressEvent(QKeyEvent* event)
{
    event->setAccepted(false);
    parent->keyPressEvent(event);
    if (!event->isAccepted())
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
            connect(tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));
        }
    }
}


bool TableView::setColumnsHeaders()
{
    if (!columnsHeadersSeted)
    {   // Если заголовки столбцов еще не установлены
        QHeaderView* header = horizontalHeader();
        header->setSectionsMovable(true);
        header->setSortIndicatorShown(true);
        QList<FieldType>* fields = parent->getParent()->getColumnsProperties();
        db->getColumnsHeaders(tagName, fields);
        if (fields->count() > 0)
        {

            // Сначала скроем все столбцы
            for (int i = 0; i < header->count(); i++)
            {
                header->hideSection(i);
            }

            // Теперь покажем только те столбцы, у которых поле number в списке fields больше 0
            for (int i = 0; i < fields->count(); i++)
            {
                if (fields->at(i).number > 0)
                {
                    MyItemDelegate* delegate = getColumnDelegate(fields->at(i));
                    if (delegate != 0)
                    {
                       delegate->setFieldName(fields->at(i).column);
                       if (!fields->at(i).readOnly)
                       {
                           connect(delegate, SIGNAL(closeEditor(QWidget*)), parent, SLOT(calculate()));
                       }
                       delegate->setReadOnly(fields->at(i).readOnly);
                       setItemDelegateForColumn(i, delegate);
                    }
                    tableModel->setHeaderData(i, Qt::Horizontal, fields->at(i).header);
                    columns.insert(fields->at(i).number - 1, fields->at(i).column);
                    header->showSection(i);
                }
            }
            // Установим столбцы в соотвествующем порядке
            foreach (int i, columns.keys())
            {
                int fldIndex = tableModel->fieldIndex(columns.value(i));
                int visualIndex = header->visualIndex(fldIndex);
                header->moveSection(visualIndex, i);
                maxColumn = i;
            }
        }
        parent->readColumnsSettings();
        columnsHeadersSeted = true;
        return true;
    }
    return false;
}


void TableView::hideAllGridSections()
{
    setColumnsHeaders();

    foreach (int i, columns.keys())
    {
        horizontalHeader()->hideSection(horizontalHeader()->logicalIndex(i));
    }
}


void TableView::hideGridSection(QString columnName)
{
    setColumnsHeaders();

    foreach (int i, columns.keys())
    {
        if (columns.value(i) == columnName)
        {
            horizontalHeader()->hideSection(horizontalHeader()->logicalIndex(i));
            return;
        }
    }
}


void TableView::showGridSection(QString columnName)
{
    setColumnsHeaders();


    foreach (int i, columns.keys())
    {
        if (columns.value(i) == columnName)
        {
            horizontalHeader()->showSection(horizontalHeader()->logicalIndex(i));
            return;
        }
    }
}


void TableView::showAllGridSections()
{
    setColumnsHeaders();

    foreach (int i, columns.keys())
    {
        horizontalHeader()->showSection(horizontalHeader()->logicalIndex(i));
    }
}


MyItemDelegate* TableView::getColumnDelegate(FieldType fld)
{
    if (fld.type.toUpper() == "NUMERIC" ||
        fld.type.toUpper() == "INTEGER")
    {     // для числовых полей зададим свой самодельный делегат
        MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(parentWidget, parent, fld.length, fld.precision);
        return (MyItemDelegate*)numericDelegate;
    } else if (fld.type.toUpper() == "BOOLEAN")
           {
                MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(parentWidget, parent);
                return (MyItemDelegate*)booleanDelegate;
           } else
           {
                if (fld.type.toUpper() == "CHARACTER" ||
                    fld.type.toUpper() == "CHARACTER VARYING" ||
                    fld.type.toUpper() == "TEXT")
                {
                    MyLineItemDelegate* textDelegate = new MyLineItemDelegate(parentWidget, parent);
                    textDelegate->setMaxLength(fld.length);
                    return (MyItemDelegate*)textDelegate;
                }
                else
                {
                    if (fld.type.toUpper() == "DATE" ||
                        fld.type.toUpper().left(9) == "TIMESTAMP")
                    {
                        MyDateItemDelegate* dateDelegate = new MyDateItemDelegate(parentWidget, parent);
                        return (MyItemDelegate*)dateDelegate;
                    }
                }
           }
    return 0;
}


bool TableView::columnIsReadOnly()
{
    if (tableModel->rowCount() > 0)
    {
        QModelIndex index = currentIndex();
        if (index.row() == -1 && index.column() == -1)
            return true;
        int column = horizontalHeader()->visualIndex(index.column());
        int logicalIndex = horizontalHeader()->logicalIndex(column);
        if (!horizontalHeader()->isSectionHidden(logicalIndex))
        {
            MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(logicalIndex);
            if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
            {
                return false;
            }
        }
    }
    return true;
}


void TableView::selectNextColumn()
// Ищет следующую колонку для редактирования
{
    if (tableModel->rowCount() > 0)
    {
        QModelIndex index = currentIndex();
        if (index.row() == -1 && index.column() == -1)
            return;
        int column = horizontalHeader()->visualIndex(index.column());
        int oldColumn = column > 0 ? column : 0;
        int logicalIndex;
        QModelIndex newIndex;
        while (true)
        {
            column++;                       // Перейдем в следующий столбец
            logicalIndex = horizontalHeader()->logicalIndex(column);
            newIndex = index.sibling(index.row(), logicalIndex);
            if (newIndex.row() == -1 && newIndex.column() == -1)
            {
                newIndex = index.sibling(index.row(), 0);
                if (newIndex.row() == -1 && newIndex.column() == -1)
                {
                    setCurrentIndex(index);
                    break;
                }
                column = 0;
                logicalIndex = horizontalHeader()->logicalIndex(column);
            }

            if (!horizontalHeader()->isSectionHidden(logicalIndex))
            {
                MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(logicalIndex);
                if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
                {
                    setCurrentIndex(newIndex);
                    break;
                }
            }
            if (column == oldColumn)                            // Выход из бесконечного цикла в случае, если ни одного поля для редактирования не найдено
            {
                break;
            }
        }
    }
}


void TableView::selectPreviousColumn()
// Ищет предыдущую колонку для редактирования
{
    QModelIndex index = currentIndex();
    if (index.row() == -1 && index.column() == -1)
        return;
    int column = horizontalHeader()->visualIndex(index.column());
    int oldColumn = column > 0 ? column : 0;
    int logicalIndex;
    while (true)
    {
        column--;   // Перейдем в предыдущий столбец
        logicalIndex = horizontalHeader()->logicalIndex(column);
        QModelIndex newIndex = index.sibling(index.row(), logicalIndex);
        if (newIndex.row() == -1 && newIndex.column() == -1)
        {
            column = maxColumn;
            logicalIndex = horizontalHeader()->logicalIndex(column);
            newIndex = index.sibling(index.row(), logicalIndex);
            if (newIndex.row() == -1 && newIndex.column() == -1)
            {
                setCurrentIndex(index);
                break;
            }
        }
        if (!horizontalHeader()->isSectionHidden(logicalIndex))
        {
            setCurrentIndex(newIndex);
            MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(logicalIndex);
            if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
                break;
        }
        if (column == oldColumn)                            // Выход из бесконечного цикла в случае, если ни одного поля для редактирования не найдено
            break;
    }
}


void TableView::selectRow(int row)
{
    QTableView::selectRow(row);
}


void TableView::setReadOnly(bool ro)
{
    QList<FieldType>* fields = parent->getParent()->getColumnsProperties();
    db->getColumnsHeaders(tagName, fields);
    if (fields->count() > 0)
    {
        for (int i = 0; i < fields->count(); i++)
        {
            if (fields->at(i).number > 0)
            {
                MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(tableModel->fieldIndex(fields->at(i).column));
                if (delegate != 0)
                {
                    delegate->setReadOnly(fields->at(i).readOnly || ro);
                }
            }
        }
    }
}


void TableView::focusInEvent(QFocusEvent* event)
{
    QTableView::focusInEvent(event);
    if (columnIsReadOnly())
        selectNextColumn();
}

