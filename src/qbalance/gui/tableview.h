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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QHeaderView>
    #include <QtGui/QTableView>
    #include <QtGui/QAbstractItemDelegate>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QHeaderView>
    #include <QtWidgets/QTableView>
    #include <QtWidgets/QAbstractItemDelegate>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtScript/QScriptValue>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include "../storage/dbfactory.h"


class TApplication;
class FormGrid;
class Essence;
class Picture;
class MyItemDelegate;
class MySqlRelationalTableModel;

struct FieldType;


class TableView : public QTableView {
    Q_OBJECT

public:
    TableView();
    ~TableView();
    virtual void                open();
    Q_INVOKABLE virtual void    close();

    virtual void                setFormGrid(FormGrid* par);
    Q_INVOKABLE virtual void    setEssence(Essence*);
    virtual void                setPicture(Picture* pic);
    virtual bool                columnIsReadOnly();
    virtual void                selectNextColumn();         // Перемещает курсор в следующий столбец, разрешенный к редактированию
    virtual void                selectPreviousColumn();     // Перемещает курсор в предыдущий столбец, разрешенный к редактированию
    Q_INVOKABLE virtual void    setReadOnly(bool);
    Q_INVOKABLE virtual bool    isReadOnly();
    Q_INVOKABLE virtual void    setColumnsHeaders();
    Q_INVOKABLE virtual void    hideAllGridSections();
    virtual void                hideGridSection(QString);
    Q_INVOKABLE virtual void    showGridSection(QString);
    virtual void                showAllGridSections();
    virtual void                restoreCurrentIndex(QModelIndex);
    virtual QList<FieldType>*   getFields() { return columnsProperties; }
    Q_INVOKABLE virtual void    clearColumnDefinitions();
    Q_INVOKABLE virtual void    appendColumnDefinition(int number, QString column, QString header = "", bool readOnly = true, int length = 0, int precision = 0);
    Q_INVOKABLE virtual void    appendColumnDefinition(QString column, QString header = "", bool readOnly = true, int length = 0, int precision = 0);
    virtual void                setCurrentFocus();
    virtual void                keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
    Q_INVOKABLE virtual int     getColumnsCount();
    virtual void                setCurrentChangedScripts(bool);
    Q_INVOKABLE virtual void    setConfigName(QString);         // Используется в скриптах
    virtual void                setApp(TApplication*);
    Q_INVOKABLE virtual void    setHideZero(bool = true);


public slots:
    virtual void                cmdAdd();
    virtual void                cmdDelete();
    virtual void                cmdView();
    virtual void                cmdRequery();

    virtual void                showPhoto();

protected:
    virtual void                currentChanged(const QModelIndex &, const QModelIndex &);
    virtual void                focusInEvent(QFocusEvent*);

private:
    bool                        columnsHeadersSeted;
    int                         maxColumn;
    QString                     name;
    QString                     configName;
    FormGrid*                   parent;
    TApplication*               app;
    Essence*                    essence;
    Picture*                    picture;
    MySqlRelationalTableModel*  tableModel;
    QHash<int, int>             columns;            // Список видимых столбцов и их порядок
    QList<FieldType>*           columnsProperties;
    bool                        columnsSettingsReaded;
    bool                        currentChangedScripts;
    int                         fieldCounter;
    bool                        hideZero;
    bool                        readOnly;

    virtual MyItemDelegate*     getColumnDelegate(FieldType);
    virtual void                readSettings();
    virtual void                writeSettings();
};

#endif // TABLEVIEW_H
