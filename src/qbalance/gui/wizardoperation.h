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

//#include <QtWidgets/QPrinter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListWidget>
#include <QtSql/QSqlQuery>
#include "wizardform.h"


class MyButtonLineEdit;
class MySyntaxHighlighter;

struct ToperType;
struct FieldType;

class WizardOperation : public WizardForm
{
    Q_OBJECT
public:
    WizardOperation();
    ~WizardOperation();
    virtual bool open(QWidget* pwgt = 0, int oper = 0);
protected:
    virtual void   initFrames();
    virtual bool   setData();
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
    QTextEdit*      textEditor;
    MySyntaxHighlighter* highlighter;
    QListWidget        headers;          // Заголовки колонок документа
    QListWidget        docListHeaders;   // Заголовки колонок списка документов
    QList<FieldType>    fields;           // Первоначальный список полей
    QList<FieldType>    docListFields;    // Первоначальный список полей
    QList<ToperType> topersList;
    virtual void    getData();
    friend QString  showAccounts();
    void            getFieldsTable(QList<FieldType>*,  QTableWidget*);
    virtual void    frameActivated(int);
    virtual void    frameDeactivated(int);
    void            generateScripts();

private slots:
    void            addPrv();
    void            deletePrv();
    void            headerUp();
    void            headerDown();
    void            docListHeaderUp();
    void            docListHeaderDown();
    void            showAccountForm();
    void            sortHeadersList(QTableWidget*, QListWidget*);
    void            sortHeaders(QListWidget*, QList<FieldType>*);
    void            toperTableChanged();
    void            fieldsTableChanged();
    void            docListFieldsTableChanged();

};

#endif // WIZARDOPERATION_H
