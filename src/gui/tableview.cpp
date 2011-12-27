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


TableView::TableView(FormGrid* par, QWidget* pwgt/* = 0*/)
: QTableView(pwgt)
, parent(NULL)
, app(NULL)
, tableModel(NULL)
{
    parent = par;
    parentWidget = pwgt;
    name = "TableView";
    app = 0;
    columns = parent->getParent()->getColumnsProperties();
}


TableView::TableView(QWidget* parentWidget/* = 0*/)
: QTableView(parentWidget)
, parent(NULL)
, app(NULL)
, tableModel(NULL)
{
    parent = 0;
    name = "TableView";
    app = 0;
    columns = parent->getParent()->getColumnsProperties();
}


TableView::~TableView()
{
    QItemSelectionModel *oldModel = selectionModel();
    delete oldModel;
}


QVariant TableView::getValue()
{
    QScriptContext* context = parent->getScriptEngine()->currentContext();
    QString field = context->argument(0).toString();
    if (parent->getParent()->isFieldExists(field))
        return parent->getParent()->getValue(field, context->argument(1).toInteger() - 1);
    return QVariant();
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
        QItemSelectionModel *oldModel = selectionModel();
        QTableView::setModel(model);
        delete oldModel;
        if (app != 0)
        {
            setColumnsHeaders();
            setColumnsDelegates();
        }
    }
}


void TableView::setColumnsHeaders()
{
    QHeaderView* header = horizontalHeader();
    header->setMovable(true);
    header->setSortIndicatorShown(true);
    if (parent != 0) {
        QSqlQuery headers = TApplication::exemplar()->getDBFactory()->getColumnsHeaders(parent->getParent()->getTagName());
        if (headers.size() > 0)
        {   // Если удалось прочитать описание столбцов, то установим столбцы в соответствии с описанием
            int i;
            for (i = 0; i < tableModel->columnCount(); i++)       // Скроем все столбцы
                hideColumn(i);
            QString columnName;                 // Расположим их по порядку, как они идут в описании и дадим им правильные заголовки
            QSqlRecord rec;
            int k;
            i = 0;
            if (headers.first())
            {
                do
                {
                    rec = headers.record();
                    columnName = rec.value("столбец").toString().trimmed();
                    visibleColumns << columnName;
                    k = tableModel->fieldIndex(columnName);
                    header->showSection(k);
                    tableModel->setHeaderData(k, Qt::Horizontal, rec.value("заголовок").toString().trimmed());
                    header->moveSection(header->visualIndex(k), i);
                    i++;
                } while (headers.next());
            }
            return;
        }
    }
    QStringList fields = TApplication::exemplar()->getDBFactory()->getFieldsList(columns);
    for (int i = 0; i < fields.count(); i++)
    {
        tableModel->setHeaderData(i, Qt::Horizontal, fields.at(i));
    }
}

/*
void TableView::sortIndicatorChanged(int logicalIndex, Qt::SortOrder order) {
    tableModel->setSort(logicalIndex, order);
//    query();
}
*/

void TableView::setColumnsDelegates()
{
    foreach (int fld, columns->keys())
    {
        if (!columns->value(fld).readOnly && visibleColumns.contains(columns->value(fld).name))
        {
            if (columns->value(fld).type.toUpper() == "NUMERIC" ||
                columns->value(fld).type.toUpper() == "INTEGER")
            {     // для числовых полей зададим свой самодельный делегат
                MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(parentWidget);
                numericDelegate->setLength(columns->value(fld).length);
                numericDelegate->setPrecision(columns->value(fld).precision);
                numericDelegate->setReadOnly(columns->value(fld).readOnly);
                connect(numericDelegate, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate(QWidget*, QAbstractItemDelegate::EndEditHint)));
                setItemDelegateForColumn(fld, numericDelegate);
            } else if (columns->value(fld).type.toUpper() == "BOOLEAN")
                {
                    MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(parentWidget);
                    booleanDelegate->setReadOnly(columns->value(fld).readOnly);
                    connect(booleanDelegate, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate(QWidget*, QAbstractItemDelegate::EndEditHint)));
                    setItemDelegateForColumn(fld, booleanDelegate);
                } else
                {
                if (columns->value(fld).type.toUpper() == "CHARACTER" ||
                    columns->value(fld).type.toUpper() == "CHARACTER VARYING") {
                    MyLineItemDelegate* textDelegate = new MyLineItemDelegate(parentWidget);
                    textDelegate->setReadOnly(columns->value(fld).readOnly);
                    connect(textDelegate, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), parent, SLOT(calculate(QWidget*, QAbstractItemDelegate::EndEditHint)));
                    setItemDelegateForColumn(fld, textDelegate);
                }
            }
        }
    }
}
