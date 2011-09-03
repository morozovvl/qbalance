#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableWidget>
#include <QWidget>
#include <QAbstractItemDelegate>
#include <QDebug>
#include <QScriptValue>
#include <QScriptContext>
#include <QScriptEngine>
#include "../mysqlrelationaltablemodel.h"
#include "../dbfactory.h"
//#include "app.h"

class App;
class FormGrid;

class TableView : public QTableWidget {
    Q_OBJECT
public:
    QMap<int, fldType> columns;
    TableView(FormGrid*, QWidget* parentWidget = 0);
    TableView(QWidget* parentWidget = 0);
    ~TableView();
    void setFormGrid(FormGrid* par) { parent = par; }
    Q_INVOKABLE QVariant getValue();
    Q_INVOKABLE void setModel(MySqlRelationalTableModel*);
    void setApp(App* a) { app = a; }
signals:
    void rowChanged();
protected slots:
    virtual void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
protected:
    QString name;
    FormGrid* parent;
    virtual void keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    virtual void currentChanged(const QModelIndex &, const QModelIndex &);
private:
    App* app;
    MySqlRelationalTableModel* tableModel;
    bool isFieldExists(QString);
    void setColumnsHeaders();
    void setColumnsDelegates();
private slots:
//    void sortIndicatorChanged(int, Qt::SortOrder);
};

#endif // TABLEVIEW_H
