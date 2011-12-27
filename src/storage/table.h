#ifndef TABLE_H
#define TABLE_H

#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QMap>
#include "dbfactory.h"
#include "mysqlrelationaltablemodel.h"

class TApplication;
class MySqlRelationalTableModel;
struct FieldType;

class Table : public QObject {
    Q_OBJECT

public:
    Table(QString table = "", QObject *parent = 0);
    ~Table();
    virtual bool relationsIsEmpty();
    QMap<int, FieldType>* getColumnsProperties();
    MySqlRelationalTableModel* getMyRelationalTableModel() { return tableModel; }
    QSqlTableModel* getTableModel() { return (QSqlTableModel*)tableModel; }
    virtual QString transformSelectStatement(QString string) { return string; }

    Q_INVOKABLE QStringList getFieldsList();
    Q_INVOKABLE QString getFieldName(int);
    Q_INVOKABLE QString getTableName() { return tableName; }
    QString getTagName() { return tagName; }
    Q_INVOKABLE virtual void query(QString filter = "");

    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    Q_INVOKABLE bool isOpened() { return opened; }

protected:
    bool                        opened;
    QString                     tableName;
    QString                     tagName;            // Тэг, на основе которого будут создаваться имена конфигураций форм и создаваться список полей табличной части
    MySqlRelationalTableModel*  tableModel;
    QMap<int, FieldType>        columnsProperties;
    virtual void setTableModel();
};

#endif // TABLE_H
