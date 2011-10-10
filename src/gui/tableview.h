#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QWidget>
#include <QAbstractItemDelegate>
#include <QDebug>
#include <QScriptValue>
#include <QScriptContext>
#include <QScriptEngine>
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"

class TApplication;
class FormGrid;

class TableView : public QTableView {
    Q_OBJECT
public:
    QMap<int, FieldType>*   columns;
    TableView(FormGrid*, QWidget* parentWidget = 0);
    TableView(QWidget* parentWidget = 0);
    ~TableView();
    void setFormGrid(FormGrid* par) { parent = par; }
    Q_INVOKABLE QVariant getValue();
    Q_INVOKABLE void setModel(MySqlRelationalTableModel*);
    void setApp(TApplication* a) { app = a; }
signals:
    void rowChanged();
protected:
    QString         name;
    FormGrid*       parent;
    virtual void keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    virtual void currentChanged(const QModelIndex &, const QModelIndex &);
private:
    TApplication*               app;
    MySqlRelationalTableModel*  tableModel;
    bool isFieldExists(QString);
    void setColumnsHeaders();
    void setColumnsDelegates();
private slots:
//    void sortIndicatorChanged(int, Qt::SortOrder);
};

#endif // TABLEVIEW_H
