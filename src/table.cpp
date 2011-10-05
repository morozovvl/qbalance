#include <QSqlRecord>
#include <QSqlError>
#include <QScriptClass>
#include <QUuid>
#include <QDateTime>
#include "table.h"
#include "mysqlrelationaltablemodel.h"
#include "app.h"

Table::Table(QString name, QObject *parent)
: QObject(parent)
, tableModel(NULL)
{
    opened = false;
    tableName = name.trimmed();
    tagName = tableName;
}

Table::~Table()
{
}


QMap<int, FieldType>* Table::getColumnsProperties()
{
    return &columnsProperties;
}


bool Table::relationsIsEmpty()
{
    return tableModel->relationsIsEmpty();
}

void Table::query(QString filter)
{
    tableModel->setFilter(filter);
    tableModel->select();
    TApplication::debug(" Query: " + tableModel->selectStatement() + "\n");
}

bool Table::open()
{
    TApplication::exemplar()->getDBFactory()->getColumnsProperties(&columnsProperties, tableName);
    setTableModel();
    if (tableModel->lastError().type() == QSqlError::NoError)
    {
        opened = true;
    }
    else
    {// Не удалось открыть таблицу, сообщим об ошибке
        QSqlError error = tableModel->lastError();
        TApplication::exemplar()->showError(error.text());
    }
    return opened;
}

void Table::close()
{
    tableModel->clear();
    delete tableModel;
    opened = false;
}

void Table::setTableModel()
{
    tableModel = new MySqlRelationalTableModel();
    tableModel->setParent(this);
    tableModel->setTable(tableName);
}

QStringList Table::getFieldsList()
{
    return TApplication::exemplar()->getDBFactory()->getFieldsList(&columnsProperties);
/*
    QStringList fieldList;
    foreach (int i, columnsProperties.keys())
        fieldList << columnsProperties.value(i).name;
    return fieldList;
*/
}

