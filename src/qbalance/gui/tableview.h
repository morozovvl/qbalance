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


class TApplication;
class FormGrid;
class Essence;
class Picture;
class MyItemDelegate;
class MySqlRelationalTableModel;

struct FieldType;


class QDESIGNER_WIDGET_EXPORT TableView : public QTableView {
    Q_OBJECT

public:
    TableView();
    ~TableView();
    virtual void                open();
    virtual void                close();

    virtual void                setFormGrid(FormGrid* par);
    Q_INVOKABLE virtual void    setEssence(Essence*);
    virtual void                setPicture(Picture* pic);
    virtual bool                columnIsReadOnly();
    virtual void                selectNextColumn();         // Перемещает курсор в следующий столбец, разрешенный к редактированию
    virtual void                selectPreviousColumn();     // Перемещает курсор в предыдущий столбец, разрешенный к редактированию
    Q_INVOKABLE virtual void    setReadOnly(bool);
    virtual bool                setColumnsHeaders();
    Q_INVOKABLE virtual void    hideAllGridSections();
    virtual void                hideGridSection(QString);
    Q_INVOKABLE virtual void    showGridSection(QString);
    virtual void                showAllGridSections();
    virtual void                restoreCurrentIndex(QModelIndex);
    virtual QList<FieldType>*   getFields() { return &fields; }
    Q_INVOKABLE virtual void    clearColumnDefinitions();
    Q_INVOKABLE virtual void    appendColumnDefinition(int number, QString column, QString header = "", bool readOnly = false);
    virtual void                setCurrentFocus();
    virtual void                keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    Q_INVOKABLE virtual void    setColumnsDelegates();


public slots:
    virtual void                cmdAdd();
    virtual void                cmdDelete();
    virtual void                cmdView();
    virtual void                cmdRequery();

    virtual void                calculate();
    virtual void                showPhoto();

protected:
    virtual void                currentChanged(const QModelIndex &, const QModelIndex &);
    virtual void                focusInEvent(QFocusEvent*);

private:
    bool                        columnsHeadersSeted;
    int                         maxColumn;
    QString                     name;
    FormGrid*                   parent;
    TApplication*               app;
    Essence*                    essence;
    Picture*                    picture;
    MySqlRelationalTableModel*  tableModel;
    QHash<int, int>             columns;            // Список видимых столбцов и их порядок
    QList<FieldType>            fields;
    bool                        columnsSettingsReaded;

    virtual MyItemDelegate*     getColumnDelegate(FieldType);
    virtual void                readSettings();
    virtual void                writeSettings();
};

#endif // TABLEVIEW_H
