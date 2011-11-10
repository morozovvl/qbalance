#ifndef ADDDICTIONARYWIZARD_H
#define ADDDICTIONARYWIZARD_H

#include "wizardform.h"

class AddDictionaryWizard : public WizardForm
{
public:
    AddDictionaryWizard();
    void           getData(QString);
protected:
    virtual void   initFrames();
    virtual bool   execute();
private:
    QLineEdit*      tableName;          // Как таблица будет называться в БД
    QLineEdit*      tableMenuName;      // Как справочник будет называться в меню
    QCheckBox*      chbMenu;            // Справочник доступен в меню справочников

};

#endif // ADDDICTIONARYWIZARD_H
