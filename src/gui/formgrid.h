#ifndef FORMGRID_H
#define FORMGRID_H

#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlIndex>
#include <QVariant>
#include <QItemDelegate>
#include "../kernel/essence.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "tableview.h"
#include "mynumericitemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mylineitemdelegate.h"
#include "form.h"
#include "picture.h"

class Picture;

class FormGrid : public Form {
    Q_OBJECT
public:
    explicit FormGrid(QObject* parent = NULL);
    Q_INVOKABLE virtual void close();
    QString getColumnHeader(QString);
    QVariant getValue(QString);
    QModelIndex getCurrentIndex() { return grdTable->currentIndex(); }
    void setCurrentIndex(QModelIndex index) { grdTable->setCurrentIndex(index); }
    TableView* getGridTable() { return grdTable; }
    virtual void setGridFocus();
//    virtual void setShowFocus();
    virtual void readSettings();
    virtual void writeSettings();

public slots:
    virtual void calculate();
    virtual void cmdAdd();
    virtual void cmdDelete();
    virtual void cmdView();
    virtual void cmdRequery(QString param = "") { query(param); }
    virtual void cmdPrint();
    virtual void showPhoto();
    Q_INVOKABLE virtual void show();

protected:
    TableView*                  grdTable;
    MySqlRelationalTableModel*  tableModel;
    QHBoxLayout*                tableLayout;
    QVBoxLayout*                imageLayout;
    Picture*                    picture;
    QPushButton*                buttonAdd;
    QPushButton*                buttonDelete;
    QPushButton*                buttonView;
    QPushButton*                buttonRequery;
    QPushButton*                buttonPrint;

    void showEvent(QShowEvent*);
    void showGridLine(int currentRow = 0);   // Подсвечивает первую (или текущую) строку Grid после обновления данных, если до этого ни одна строка не была подсвечена
    virtual void add();
    virtual void remove();
    virtual void query(QString param = "");
    virtual void createForm(QString, QWidget* pwgt = 0);
    virtual QDomElement createWidgetsStructure();

private:
    QString             photoPath;
    int getHeaderIndex(QString);
//    virtual void keyPressEvent(QKeyEvent*);

};

#endif // FORMGRID_H
