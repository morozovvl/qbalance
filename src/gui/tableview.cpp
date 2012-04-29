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
#include <QDebug>
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
    tableModel = 0;
    columns = 0;
    if (verticalHeader()->minimumSectionSize() > 0)
        verticalHeader()->setDefaultSectionSize(verticalHeader()->minimumSectionSize());
}


TableView::~TableView()
{
    QItemSelectionModel *oldModel = selectionModel();
    delete oldModel;
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
    if (event->modifiers() == Qt::ControlModifier)
    {              // Были нажаты клавиши модификации
        if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))
        {   // и <Enter>
            parent->cmdOk();
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


void TableView::setModel(MySqlRelationalTableModel* model)
{
    if (model != 0)
    {
        tableModel = model;
        QTableView::setModel(tableModel);
        if (parent != 0)
        {
            // Прочитаем список доступных полей
            columns = parent->getParent()->getColumnsProperties();
            if (columns->count() > 0)
            {
                // Установим заголовки полей
                setColumnsHeaders();
                // и их делегаты
                setColumnsDelegates();
            }
        }
    }
}


void TableView::setColumnsHeaders()
{
    QHeaderView* header = horizontalHeader();
    DBFactory* db = TApplication::exemplar()->getDBFactory();
    header->setMovable(true);
    header->setSortIndicatorShown(true);
    QSqlQuery columnsHeaders = db->getColumnsHeaders(parent->getParent()->getTableName());
    // Сначала скроем все столбцы
    if (columnsHeaders.size() > 0)
    {
        for (int i = 0; i < tableModel->columnCount(); i++)
        {
            setColumnHidden(i, true);
        }
        for (columnsHeaders.first(); columnsHeaders.isValid(); columnsHeaders.next())
        {
            int number = columnsHeaders.record().value(db->getObjectName("vw_столбцы.номер")).toInt();
            if (number > 0)
            {
                int k;
                QString columnName = columnsHeaders.record().value(db->getObjectName("vw_столбцы.столбец")).toString();
                visibleColumns << columnName;
                k = tableModel->fieldIndex(columnName);
                header->showSection(k);
                tableModel->setHeaderData(k, Qt::Horizontal, columnsHeaders.record().value(db->getObjectName("vw_столбцы.заголовок")).toString());
                header->moveSection(header->visualIndex(k), number - 1);
            }
        }
    }
}


void TableView::setColumnsDelegates()
{
    for (int fld = 0; fld < columns->count(); fld++)
    {
        QString columnName;
        if (parent->getParent()->getTableName() == columns->at(fld).table)
            columnName = columns->at(fld).name;
        else
            columnName = columns->at(fld).table + "__" + columns->at(fld).name;
        if (visibleColumns.contains(columnName))
        {
            if (columns->at(fld).type.toUpper() == "NUMERIC" ||
                columns->at(fld).type.toUpper() == "INTEGER")
            {     // для числовых полей зададим свой самодельный делегат
                MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(parentWidget);
                numericDelegate->setLength(columns->at(fld).length);
                numericDelegate->setPrecision(columns->at(fld).precision);
                connect(numericDelegate, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate(QWidget*, QAbstractItemDelegate::EndEditHint)));
                numericDelegate->setReadOnly(columns->at(fld).readOnly);
                setItemDelegateForColumn(columns->at(fld).number - 1, numericDelegate);
            } else if (columns->at(fld).type.toUpper() == "BOOLEAN")
                {
                    MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(parentWidget);
                    connect(booleanDelegate, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate(QWidget*, QAbstractItemDelegate::EndEditHint)));
                    booleanDelegate->setReadOnly(columns->at(fld).readOnly);
                    setItemDelegateForColumn(columns->at(fld).number - 1, booleanDelegate);
                } else
                {
                if (columns->at(fld).type.toUpper() == "CHARACTER" ||
                    columns->at(fld).type.toUpper() == "CHARACTER VARYING") {
                    MyLineItemDelegate* textDelegate = new MyLineItemDelegate(parentWidget);
                    connect(textDelegate, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate(QWidget*, QAbstractItemDelegate::EndEditHint)));
                    textDelegate->setReadOnly(columns->at(fld).readOnly);
                    setItemDelegateForColumn(columns->at(fld).number - 1, textDelegate);
                }
            }
        }
    }
}

