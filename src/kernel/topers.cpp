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
        TApplication::exemplar()->removeDocuments(opNumber);
    }
}


bool Topers::add()
{
    WizardOperation wizard;
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
    int operNumber = getValue("опер").toInt();
    WizardOperation wizard;
    wizard.open(TApplication::exemplar()->getMainWindow(), operNumber);
    wizard.getForm()->setWindowTitle(QObject::trUtf8("Свойства операции"));
    wizard.exec();
    wizard.close();
    if (wizard.getResult())
    {
        removeDocument(operNumber);
    }
}


void Topers::setForm()
{
    Dictionary::setForm();
    if (form->isDefaultForm())
    {
        QPushButton* button;
        button = form->getButtonPrint();
        if (button != NULL)
            button->hide();
        button = form->getButtonOk();
        if (button != NULL)
            button->setToolTip(trUtf8("Открыть список документов"));
        button = form->getButtonCancel();
        if (button != NULL)
            button->setToolTip(trUtf8("Закрыть список типовых операций"));
        button = form->getButtonAdd();
        if (button != NULL)
            button->setToolTip(trUtf8("Создать новую типовую операцию"));
        button = form->getButtonDelete();
        if (button != NULL)
            button->setToolTip(trUtf8("Удалить типовую операцию"));
        button = form->getButtonView();
        if (button != NULL)
            button->setToolTip(trUtf8("Свойства типовой операции"));
        button = form->getButtonRequery();
        if (button != NULL)
            button->setToolTip(trUtf8("Обновить список типовых операций (загрузить повторно с сервера)"));
    }
}


bool Topers::remove()
{
    int operNumber = getValue("опер").toInt();
    if (TApplication::exemplar()->getDBFactory()->deleteAllToperInfo(operNumber))
    {   // если удалось удалить типовую операцию
        return true;
    }
    return false;
}

