#include <QString>
#include "topers.h"
#include "../kernel/app.h"
#include "../kernel/documents.h"
#include "../gui/formgridsearch.h"
#include "../gui/wizardoperation.h"
#include "../gui/mainwindow.h"


Topers::Topers(QObject *parent): Dictionary("vw_доступ_к_топер", parent) {
    lInsertable = TApplication::exemplar()->isSA();     // Если работает пользователь SA, то можно добавить операцию
    lViewable = TApplication::exemplar()->isSA();       // Если работает пользователь SA, то можно просмотреть свойства операции
    lDeleteable = TApplication::exemplar()->isSA();       // Если работает пользователь SA, то можно попытаться удалить операцию
}


void Topers::cmdOk() {
    addDocument(getValue("опер").toInt());
}


void Topers::addDocument(int opNumber) {
    if (opNumber > 0) {
        Documents* doc = TApplication::exemplar()->getDocuments(opNumber);
        if (doc != NULL) {
            doc->show();
        }
    }
}


void Topers::removeDocument(int opNumber) {
    if (opNumber > 0) {
/*
        Documents* doc = TApplication::exemplar()->getDocuments(opNumber);
        doc->close();
        TApplication::exemplar()->documents.remove()
    if (dictionaries.contains(dictName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict = getDictionary(dictName);
        dict->close();
        dictionaries.remove(dictName);
*/
    }
}



bool Topers::add()
{
    WizardOperation wizard(true);
    wizard.open(TApplication::exemplar()->getMainWindow());
    wizard.getForm()->setWindowTitle(QObject::trUtf8("Новая операция"));
    wizard.exec();
    wizard.close();
    if (wizard.getResult())
    {   // Если удалось создать операцию, то обновим список операций
        return true;
    }
    return false;
}


void Topers::view()
{
    WizardOperation wizard;
    wizard.open(TApplication::exemplar()->getMainWindow(), getValue("опер").toInt());
    wizard.getForm()->setWindowTitle(QObject::trUtf8("Свойства операции"));
    wizard.exec();
    wizard.close();
    if (wizard.selected())
    {
//        removeDictionary(dictName);
    }
}


/*
bool Topers::remove()
{
    if (TApplication::exemplar()->getDBFactory()->removeDictionary(getValue("таблица").toString().trimmed()))
    {   // если удалось удалить справочник, то обновим список справочников
        dictionariesProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties();
        return true;
    }
    return false;
}
*/

