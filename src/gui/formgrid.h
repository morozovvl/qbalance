#ifndef FORMGRID_H
#define FORMGRID_H

#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlIndex>
#include <QVariant>
#include <QItemDelegate>
#include "../essence.h"
#include "../mysqlrelationaltablemodel.h"
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
    Q_INVOKABLE virtual bool open(QWidget* pwgt = 0, Essence* par = 0);
    Q_INVOKABLE virtual void close();
    QString getColumnHeader(QString);
    QVariant getValue(QString);
    QModelIndex getCurrentIndex() { return grdTable->currentIndex(); }
    void setCurrentIndex(QModelIndex index) { grdTable->setCurrentIndex(index); }
    int getCurrentRowIndex();
    TableView* getGridTable() { return grdTable; }
    virtual void setGridFocus();
    virtual void setShowFocus();
    virtual void readSettings();
    virtual void writeSettings();


public slots:
    virtual void cmdAdd();
    virtual void cmdDelete();
    virtual void cmdView();
    virtual void cmdRequery(QString param = "") { query(param); }
    virtual void cmdPrint();
    virtual void showPhoto();

protected:
    TableView* grdTable;
    MySqlRelationalTableModel* tableModel;

    QHBoxLayout* tableLayout;
    QVBoxLayout* imageLayout;
    Picture* picture;
    QPushButton* buttonAdd;
    QPushButton* buttonDelete;
    QPushButton* buttonView;
    QPushButton* buttonRequery;
    QPushButton* buttonPrint;

    void showEvent(QShowEvent*);
    void showGridLine(int currentRow = 0);   // Подсвечивает первую (или текущую) строку Grid после обновления данных, если до этого ни одна строка не была подсвечена
    virtual void doShow();
    virtual void add();
    virtual void remove();
    virtual void query(QString param = "");
    virtual QDomElement createWidgetsStructure();

private:
    QString photoPath;
    int getHeaderIndex(QString);
//    virtual void keyPressEvent(QKeyEvent*);

};

#endif // FORMGRID_H
