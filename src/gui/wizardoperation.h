#ifndef WIZARDOPERATION_H
#define WIZARDOPERATION_H

#include "wizarddictionary.h"
#include "mytextedit.h"
#include "mysyntaxhighlighter.h"

class WizardOperation : public WizardForm
{
    Q_OBJECT
public:
    WizardOperation();
    bool open(QWidget* pwgt = NULL, int oper = 0);
protected:
    virtual void   initFrames();
    virtual bool   execute();
    virtual void    frameDeactivated(int frameNumber);
private:
    int             oper;               // Номер операции, с которой работает мастер
    bool            prvTableChanged;
    bool            fldsTableChanged;
    DBFactory*      db;
    QSqlQuery       prvs;               // Проводки
    QLineEdit*      operName;              // Как будет называться операция
    QTableWidget*   prvTable;             // Список проводок операции
    QTableWidget*   fieldsTable;
    MyTextEdit*     textEditor;
    MySyntaxHighlighter* highlighter;
    QListWidget*        headers;          // Заголовки колонок
    QList<FieldType>    fields;           // Первоначальный список полей
    QList<ToperType> topersList;
    virtual void    getData();
    friend QString  showAccounts();
    void            getFieldsTable();
private slots:
    void            addPrv();
    void            deletePrv();
    void            headerUp();
    void            headerDown();
    void            showAccountForm();
    void            toperTableChanged();
    void            fieldsTableChanged();
};

#endif // WIZARDOPERATION_H
