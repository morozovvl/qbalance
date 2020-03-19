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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QTableView>
    #include <QtGui/QItemDelegate>
#else
    #include <QtWidgets/QTableView>
    #include <QtWidgets/QItemDelegate>
#endif

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlIndex>
#include <QtCore/QVariant>
#include <QtCore/QPointer>
#include "../storage/mysqlrelationaltablemodel.h"
#include "form.h"

class TableView;
class Picture;

class FormGrid : public Form {
    Q_OBJECT
public:
    FormGrid(QObject* parent = 0 /*nullptr*/);
    ~FormGrid();
    virtual void close();
    Q_INVOKABLE virtual void    setLeftPercent(bool percent);
    Q_INVOKABLE virtual bool    isLeftPercent();
    Q_INVOKABLE virtual void    setRightPercent(bool percent);
    Q_INVOKABLE virtual bool    isRightPercent();

    Q_INVOKABLE QPushButton* getButtonAdd();
    Q_INVOKABLE QPushButton* getButtonDelete();
    Q_INVOKABLE QPushButton* getButtonView();
    Q_INVOKABLE QPushButton* getButtonRequery();
    Q_INVOKABLE QPushButton* getButtonQuery();
    Q_INVOKABLE QPushButton* getButtonPrint();
    Q_INVOKABLE QPushButton* getButtonLoad();
    Q_INVOKABLE QPushButton* getButtonSave();

    void setButtonAdd(bool);
    void setButtonDelete(bool);
    virtual void setButtons();

    Q_INVOKABLE virtual void setEnabled(bool);
    virtual void activateWidget();
    virtual void keyPressEvent(QKeyEvent*);
    Q_INVOKABLE virtual Picture* getPicture();
    virtual QString getFilter();    // Возвращает фильтр для поиска в справочнике
    TableView* getGrdTable();
    void setGrdTable(TableView*);

public slots:
    virtual void cmdAdd();
    virtual void cmdDelete();
    virtual void cmdView();
    virtual void cmdRequery();
    virtual void cmdQuery();
    virtual void cmdPrint(bool = false);
    virtual void cmdLoad();
    virtual void cmdSave();
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void showPhoto();


protected:
    TableView*                  grdTable;
    QList<TableView*>           grdTables;
    QVBoxLayout*                tableLayout;
    QHBoxLayout*                imageLayout;
    Picture*                    picture;
    QPushButton*                buttonAdd;
    QPushButton*                buttonDelete;
    QPushButton*                buttonView;
    QPushButton*                buttonRequery;
    QPushButton*                buttonQuery;
    QPushButton*                buttonPrint;
    QPushButton*                buttonLoad;
    QPushButton*                buttonSave;

    virtual void createForm(QString, QWidget* pwgt = 0 /*nullptr*/);

private:
    bool    leftPercent;
    bool    rightPercent;

};

#endif // FORMGRID_H
