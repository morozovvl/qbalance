#include <QSqlRecord>
#include <QSqlError>
#include <QScriptClass>
#include <QUuid>
#include <QDateTime>
#include "table.h"
#include "mysqlrelationaltablemodel.h"
#include "app.h"

Table::Table(QString name, QObject *parent)
: Custom(parent)
, tableModel(NULL)
{
    tableName = name.trimmed();
    tagName = tableName;
}

Table::~Table()
{
}

/*
QMap<int,fldType>* Table::getColumnsProperties() {
    return &columnsProperties;
}
*/
/*
void Table::addColumnProperties(QString name, QString type, int length, int precision, bool read) {
    int maxKey = 0;
    if (columnsProperties.count() > 0) {
        foreach (int i, columnsProperties.keys())
            if (i > maxKey)
                maxKey = i;
            maxKey++;
        }
    fldType fld;
    fld.name = name;
    fld.type = type;
    fld.length = length;
    fld.precision = precision;
    fld.readOnly = read;
    columnsProperties.insert(maxKey, fld);
}
*/

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

bool Table::doOpen()
{
    TApplication::exemplar()->getDBFactory()->getColumnsProperties(&columnsProperties, tableName);
    setTableModel();
    if (tableModel->lastError().type() == QSqlError::NoError)
    {
        return Custom::doOpen();
    }
    // Не удалось открыть таблицу, сообщим об ошибке
    QSqlError error = tableModel->lastError();
    TApplication::exemplar()->showError(error.text());
    return false;
}

void Table::doClose()
{
    tableModel->clear();
    delete tableModel;
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
