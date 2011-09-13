#include <QDebug>
#include <QLineEdit>
#include <QTableView>
#include <QScriptContextInfo>
#include "tableview.h"
#include "formgrid.h"
#include "mynumericitemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mylineitemdelegate.h"
#include "../app.h"


TableView::TableView(FormGrid* par, QWidget* parentWidget/* = 0*/)
: QTableView(parentWidget)
, parent(NULL)
, app(NULL)
, tableModel(NULL)
{
    parent = par;
    name = "TableView";
    app = 0;
    columns.clear();
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
    columns.clear();
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
    if (isFieldExists(field))
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



void TableView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    QTableView::closeEditor(editor, hint);
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


bool TableView::isFieldExists(QString field)
{
    if (parent->getParent()->isFieldExists(field))
        return true;
    ScriptEngine* engine = parent->getScriptEngine();
    QScriptContext* context = engine->currentContext();
    QStringList list = context->backtrace();
    foreach (QString str, list)
    {
        int pos = str.mid(str.indexOf(" at ") + 4).toInt();
        if (pos > 0)
        {
            engine->showError(str + ": " + QString(QObject::tr("Не найдено поле %1.")).arg(field));
            break;
        }
    }
    return false;
}


void TableView::setModel(MySqlRelationalTableModel* model)
{
    if (model != 0)
    {
        columns.clear();
        tableModel = model;
        QItemSelectionModel *oldModel = selectionModel();
        QTableView::setModel(model);
        delete oldModel;
        if (app != 0)
        {
            app->getDBFactory()->getColumnsProperties(&columns, tableModel->tableName());
            setColumnsDelegates();
            setColumnsHeaders();
        }
    }
}


void TableView::setColumnsHeaders()
{
    QHeaderView* header = horizontalHeader();
    header->setMovable(true);
    header->setSortIndicatorShown(true);
//    connect(header, SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(sortIndicatorChanged(int, Qt::SortOrder)));
    QSqlQuery headers = app->getDBFactory()->getColumnsHeaders(tableModel->tableName());
    if (headers.size() > 0)
    {
        int i;                                                          // Если удалось прочитать описание столбцов, то установим столбцы в соответствии с описанием
        for (i = 0; i < app->getDBFactory()->getFieldsList(&columns).count(); i++)       // Скроем все столбцы
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
                k = tableModel->fieldIndex(columnName);
                header->showSection(k);
                tableModel->setHeaderData(k, Qt::Horizontal, rec.value("заголовок").toString().trimmed());
                header->moveSection(header->visualIndex(k), i);
                i++;
            } while (headers.next());
        }
    }
    else
    {
        QStringList fields = app->getDBFactory()->getFieldsList(&columns);
        for (int i = 0; i < fields.count(); i++)
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
    foreach (int fld, columns.keys())
    {
        if (columns.value(fld).type.toUpper() == "NUMERIC" ||
            columns.value(fld).type.toUpper() == "INTEGER")
        {     // для числовых полей зададим свой самодельный делегат
            MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(parent);
            numericDelegate->setLength(columns.value(fld).length);
            numericDelegate->setPrecision(columns.value(fld).precision);
            numericDelegate->setReadOnly(columns.value(fld).readOnly);
            setItemDelegateForColumn(fld, numericDelegate);
        } else if (columns.value(fld).type.toUpper() == "BOOLEAN")
            {
                MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(parent);
                booleanDelegate->setReadOnly(columns.value(fld).readOnly);
                setItemDelegateForColumn(fld, booleanDelegate);
            } else
            {
            if (columns.value(fld).type.toUpper() == "CHARACTER" ||
                columns.value(fld).type.toUpper() == "CHARACTER VARYING") {
                MyLineItemDelegate* textDelegate = new MyLineItemDelegate(parent);
                textDelegate->setReadOnly(columns.value(fld).readOnly);
                setItemDelegateForColumn(fld, textDelegate);
            }
        }
    }
}
