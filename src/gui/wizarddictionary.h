#ifndef WIZARDDICTIONARY_H
#define WIZARDDICTIONARY_H

#include "wizardform.h"
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
    DBFactory*          db;
    QList<FieldType>    fields;                // Первоначальный список полей
    QString             table;
    QLineEdit*          tableName;              // Как таблица будет называться в БД
    QLineEdit*          tableMenuName;          // Как справочник будет называться в меню
    QLineEdit*          tableFormName;          // Как справочник будет называться в форме
    QCheckBox*          chbMenu;                // Справочник доступен в меню справочников
    QTableWidget*       fieldsTable;            // Список полей таблицы
    QListWidget*        headers;                // Заголовки колонок
    virtual void        getData();
    friend QString      showTypesForm();
    static WizardDictionary*    Exemplar;

private slots:
    void                addColumn();
    void                deleteColumn();
    void                headerUp();
    void                headerDown();
    virtual void        frameActivated(int);
};

#endif // WIZARDDICTIONARY_H
