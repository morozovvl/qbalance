/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#ifndef FORMGRID_H
#define FORMGRID_H

#include <QtGui/QTableView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlIndex>
#include <QtCore/QVariant>
#include <QtGui/QItemDelegate>
#include "../storage/mysqlrelationaltablemodel.h"
#include "form.h"
#include "picture.h"

class TableView;

class FormGrid : public Form {
    Q_OBJECT
public:
    FormGrid(QObject* parent = 0);
    ~FormGrid();
    Q_INVOKABLE virtual void close();
    QVariant getValue(QString);
    QModelIndex getCurrentIndex();
    void setCurrentIndex(QModelIndex index);
    void restoreCurrentIndex(QModelIndex);
    void setCalculateColumn(int column) { calculateColumn = column; }
    void selectRow(int = 0);
    virtual void setGridFocus();
    TableView* getGridTable() { return grdTable; }

    Q_INVOKABLE QPushButton* getButtonAdd() { return buttonAdd; }
    Q_INVOKABLE QPushButton* getButtonDelete() { return buttonDelete; }
    Q_INVOKABLE QPushButton* getButtonView() { return buttonView; }
    Q_INVOKABLE QPushButton* getButtonRequery() { return buttonRequery; }
    Q_INVOKABLE QPushButton* getButtonPrint() { return buttonPrint; }
    Q_INVOKABLE QPushButton* getButtonLoad() { return buttonLoad; }
    Q_INVOKABLE QPushButton* getButtonSave() { return buttonSave; }

    void setButtonAdd(bool);
    void setButtonDelete(bool);
    void setButtons();

    virtual void keyPressEvent(QKeyEvent*);
    Q_INVOKABLE virtual void setEnabled(bool);
    virtual void readColumnsSettings();
    virtual void activateWidget();

public slots:
    virtual void calculate();
    virtual void cmdAdd();
    virtual void cmdDelete();
    virtual void cmdView();
    virtual void cmdRequery();
    virtual void cmdPrint();
    virtual void cmdLoad();
    virtual void cmdSave();
    Q_INVOKABLE virtual void showPhoto();
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();


protected:
    TableView*                  grdTable;
    MySqlRelationalTableModel*  tableModel;
    QVBoxLayout*                tableLayout;
    QHBoxLayout*                imageLayout;
    Picture*                    picture;
    QPushButton*                buttonAdd;
    QPushButton*                buttonDelete;
    QPushButton*                buttonView;
    QPushButton*                buttonRequery;
    QPushButton*                buttonPrint;
    QPushButton*                buttonLoad;
    QPushButton*                buttonSave;

    virtual void createForm(QString, QWidget* pwgt = 0);
    void writeSettings();

private:
    int     calculateColumn;                    // Колонка, в которой был вызван редактор ячейки
    bool    columnsSettingsReaded;

};

#endif // FORMGRID_H
