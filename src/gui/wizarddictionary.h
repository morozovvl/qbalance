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

#ifndef WIZARDDICTIONARY_H
#define WIZARDDICTIONARY_H

#include "wizardform.h"
#include "mytextedit.h"
#include "mysyntaxhighlighter.h"
#include "../storage/dbfactory.h"


class WizardDictionary : public WizardForm
{
    Q_OBJECT
public:
    WizardDictionary(bool = false);
    virtual bool open(QWidget* pwgt = NULL, QString = "");
    static WizardDictionary* exemplar();

protected:
    virtual void   initFrames();
    virtual bool   setData();
private:
    bool                addDictionary;
    bool                columnsRecordsExists;
    QList<FieldType>    fields;                // Первоначальный список полей
    QString             table;
    QLineEdit*          tableName;              // Как таблица будет называться в БД
    QLineEdit*          tableMenuName;          // Как справочник будет называться в меню
    QLineEdit*          tableFormName;          // Как справочник будет называться в форме
    QCheckBox*          chbMenu;                // Справочник доступен в меню справочников
    QTableWidget        fieldsTable;            // Список полей таблицы
    QListWidget         headers;                // Заголовки колонок
    MyTextEdit*         textEditor;
    MySyntaxHighlighter* highlighter;
    virtual void        getData();
    friend QString      showTypesForm();
    static WizardDictionary*    Exemplar;
    virtual void        frameActivated(int);
    virtual void        frameDeactivated(int);

private slots:
    void                addColumn();
    void                deleteColumn();
    void                headerUp();
    void                headerDown();
};

#endif // WIZARDDICTIONARY_H
