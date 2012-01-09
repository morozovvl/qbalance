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
    virtual bool   execute();
    virtual void    frameDeactivated(int frameNumber);
private:
    int             oper;               // Номер операции, с которой работает мастер
    bool            prvTableChanged;
    bool            fldsTableChanged;
    bool            docListFldsTableChanged;
    DBFactory*      db;
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
    void            getFieldsTable(QMap<int, FieldType>,  QTableWidget*, QList<FieldType>*);
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
