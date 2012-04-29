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

#ifndef WIZARDOPERATION_H
#define WIZARDOPERATION_H

#include "wizarddictionary.h"
#include "mytextedit.h"
#include "mysyntaxhighlighter.h"
#include "mybuttonlineedit.h"

class WizardOperation : public WizardForm
{
    Q_OBJECT
public:
    WizardOperation();
    bool open(QWidget* pwgt = NULL, int oper = 0);
protected:
    virtual void   initFrames();
    virtual bool   setData();
    virtual void    frameDeactivated(int frameNumber);
private:
    int             oper;               // Номер операции, с которой работает мастер
    bool            prvTableChanged;
    bool            fldsTableChanged;
    bool            docListFldsTableChanged;
    QSqlQuery       prvs;               // Проводки
    QLineEdit*      operName;              // Как будет называться операция
    QCheckBox*      chbSingleString;      // В документе можно создать только одну строку
    MyButtonLineEdit*   bleNumerator;     // Нумератор операции
    QTableWidget*   prvTable;             // Список проводок операции
    QTableWidget*   fieldsTable;
    QTableWidget*   docListFieldsTable;
    MyTextEdit*     textEditor;
    MySyntaxHighlighter* highlighter;
    QListWidget*        headers;          // Заголовки колонок документа
    QListWidget*        docListHeaders;   // Заголовки колонок списка документов
    QList<FieldType>    fields;           // Первоначальный список полей
    QList<FieldType>    docListFields;    // Первоначальный список полей
    QList<ToperType> topersList;
    virtual void    getData();
    friend QString  showAccounts();
    void            getFieldsTable(QList<FieldType>,  QTableWidget*, QList<FieldType>*);
private slots:
    void            addPrv();
    void            deletePrv();
    void            headerUp();
    void            headerDown();
    void            docListHeaderUp();
    void            docListHeaderDown();
    void            showAccountForm();
    void            toperTableChanged();
    void            fieldsTableChanged();
    void            docListFieldsTableChanged();
    void            sortHeaders(QListWidget*, QList<FieldType>*);
};

#endif // WIZARDOPERATION_H
