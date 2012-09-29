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

#include "tableview.h"
#include <QLineEdit>
#include <QTableView>
#include <QScriptContextInfo>
#include "../kernel/app.h"
#include "formgrid.h"
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
        // Сначала скроем все столбцы
        for (int i = 0; i < tableModel->columnCount(); i++)
        {
            setColumnHidden(i, true);
        }
        // Найдем наибольший номер видимой колонки
        int maxNumber = 0;
        for (int i = 0; i < fields->count(); i++)
        {
            if (fields->at(i).number > maxNumber)
                maxNumber = fields->at(i).number;
        }
        for (int j = 1; j <= maxNumber; j++)
        {
            for (int i = 0; i < fields->count(); i++)
            {
                if (fields->at(i).number == j)
                {
                    QString columnName = fields->at(i).column;
                    int k = fields->at(i).number - 1;
                    int l = tableModel->fieldIndex(columnName);
                    header->showSection(l);
                    MyItemDelegate* delegate = getColumnDelegate(fields->at(i));
                    if (delegate != 0)
                    {
                        connect(delegate, SIGNAL(closeEditor( QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate()));
                        delegate->setReadOnly(fields->at(i).readOnly);
                        setItemDelegateForColumn(l, delegate);
                    }
                    tableModel->setHeaderData(l, Qt::Horizontal, fields->at(i).header);
                    header->moveSection(l, k);
                    qDebug() << tagName << columnName << l << k << fields->at(i).header;
                }
            }
        }
/*
        for (int i = 0; i < fields->count(); i++)
        {
            if (fields->at(i).number > 0)
            {
                int k;
                QString columnName = fields->at(i).column;
                k = tableModel->fieldIndex(columnName);
                header->showSection(k);
                MyItemDelegate* delegate = getColumnDelegate(fields->at(i));
                if (delegate != 0)
                {
                    connect(delegate, SIGNAL(closeEditor( QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate()));
                    delegate->setReadOnly(fields->at(i).readOnly);
                    setItemDelegateForColumn(k, delegate);
                }
                tableModel->setHeaderData(k, Qt::Horizontal, fields->at(i).header);
                header->moveSection(header->visualIndex(k), fields->at(i).number - 1);
            }
        }
*/
    }
}


MyItemDelegate* TableView::getColumnDelegate(FieldType fld)
{
    if (fld.type.toUpper() == "NUMERIC" ||
        fld.type.toUpper() == "INTEGER")
    {     // для числовых полей зададим свой самодельный делегат
        MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(parentWidget, fld.length, fld.precision);
        return numericDelegate;
    } else if (fld.type.toUpper() == "BOOLEAN")
           {
                MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(parentWidget);
                return booleanDelegate;
           } else
           {
                if (fld.type.toUpper() == "CHARACTER" ||
                    fld.type.toUpper() == "CHARACTER VARYING")
                {
                    MyLineItemDelegate* textDelegate = new MyLineItemDelegate(parentWidget);
                    return textDelegate;
                }
                else
                    return 0;
           }
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
