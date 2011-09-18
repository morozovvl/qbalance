#ifndef TABLE_H
#define TABLE_H

#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QMap>
#include "custom.h"
#include "dbfactory.h"

class TApplication;

class MySqlRelationalTableModel;

class Table : public Custom {
    Q_OBJECT

public:
    Table(QString table = "", QObject *parent = 0);
    ~Table();
    virtual bool relationsIsEmpty();
//    void addColumnProperties(QString, QString, int, int, bool readOnly = false);
//    QSqlRecord getColumnsProperties(int);
//    QSqlRecord getColumnsProperties(QString);
    MySqlRelationalTableModel* getMyRelationalTableModel() { return tableModel; }
    QSqlTableModel* getTableModel() { return (QSqlTableModel*)tableModel; }
    virtual QString transformSelectStatement(QString string) { return string; }

    Q_INVOKABLE QStringList getFieldsList();
    Q_INVOKABLE QString getTableName() { return tableName; }
    Q_INVOKABLE virtual void query(QString filter = "");

protected:
    MySqlRelationalTableModel* tableModel;
//    QStringList fieldList;
    QMap<int, FieldType> columnsProperties;
    virtual bool doOpen();
    virtual void doClose();
    virtual void setTableModel();
    QString tableName;
};

#endif // TABLE_H
