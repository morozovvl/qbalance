#ifndef ADDDICTIONARYWIZARD_H
#define ADDDICTIONARYWIZARD_H

#include "wizardform.h"
#include "../storage/dbfactory.h"

class AddDictionaryWizard : public WizardForm
{
    Q_OBJECT
public:
    AddDictionaryWizard(bool = false);
    virtual bool open(QWidget* pwgt = NULL, QString = "");
protected:
    virtual void   initFrames();
    virtual bool   execute();
private:
    bool                addDictionary;
    QList<FieldType>    fields;                // Первоначальный список полей
    QString             table;
    QLineEdit*          tableName;              // Как таблица будет называться в БД
    QLineEdit*          tableMenuName;          // Как справочник будет называться в меню
    QCheckBox*          chbMenu;                // Справочник доступен в меню справочников
    QTableWidget*       fieldsTable;            // Список полей таблицы
    QListWidget*        headers;                // Заголовки колонок
    virtual void        getData();
private slots:
    void                addColumn();
    void                deleteColumn();
    void                headerUp();
    void                headerDown();
    virtual void        frameActivated(int);
};

#endif // ADDDICTIONARYWIZARD_H
