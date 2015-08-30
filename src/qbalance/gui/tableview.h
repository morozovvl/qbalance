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

#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QtGui/QTableView>
#include <QtGui/QWidget>
#include <QtGui/QAbstractItemDelegate>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtDesigner/QDesignerExportWidget>

#include "myitemdelegate.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"


class TApplication;
class DBFactory;
class FormGrid;
class Essence;
class Picture;
class MyItemDelegate;
struct FieldType;


class QDESIGNER_WIDGET_EXPORT TableView : public QTableView {
    Q_OBJECT

public:
    TableView(QWidget*, FormGrid* = 0);
    ~TableView();
    virtual void                close();

    virtual void                setFormGrid(FormGrid* par) { parent = par; }
    virtual void                setParentWidget(QWidget* widget) { parentWidget = widget; }
    virtual void                setEssence(Essence*);
    virtual void                setPicture(Picture* pic) { picture = pic; }
    virtual bool                columnIsReadOnly();
    virtual void                selectNextColumn();         // Перемещает курсор в следующий столбец, разрешенный к редактированию
    virtual void                selectPreviousColumn();     // Перемещает курсор в предыдущий столбец, разрешенный к редактированию
    virtual void                setReadOnly(bool);
    virtual bool                setColumnsHeaders();
    virtual void                hideAllGridSections();
    virtual void                hideGridSection(QString);
    virtual void                showGridSection(QString);
    virtual void                showAllGridSections();
    virtual void                restoreCurrentIndex(QModelIndex);
    virtual QList<FieldType>*   getFields() { return &fields; }
    Q_INVOKABLE virtual void    appendColumnDefinition(int number, QString column, QString header = "", bool readOnly = false);


public slots:
    virtual void                cmdAdd();
    virtual void                cmdDelete();
    virtual void                cmdView();
    virtual void                cmdRequery();

    virtual void                calculate();
    virtual void                showPhoto();

protected:
    virtual void                keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    virtual void                currentChanged(const QModelIndex &, const QModelIndex &);
    void                        focusInEvent(QFocusEvent*);

private:
    bool                        columnsHeadersSeted;
    int                         maxColumn;
    QString                     name;
    FormGrid*                   parent;
    QWidget*                    parentWidget;
    TApplication*               app;
    DBFactory*                  db;
    Essence*                    essence;
    Picture*                    picture;
    MySqlRelationalTableModel*  tableModel;
    QHash<int, int>             columns;            // Список видимых столбцов и их порядок
    QList<FieldType>            fields;
    bool                        columnsSettingsReaded;

    MyItemDelegate*             getColumnDelegate(FieldType);
    void                        setColumnsDelegates();
    void                        readSettings();
    void                        writeSettings();
};

#endif // TABLEVIEW_H
