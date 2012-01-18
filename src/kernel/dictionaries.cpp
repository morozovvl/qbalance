#include <QString>
#include "dictionaries.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/wizarddictionary.h"


Dictionaries::Dictionaries(QObject *parent): Dictionary("vw_доступ_к_справочникам", parent) {
    dictionariesProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties();
    lInsertable = TApplication::exemplar()->isSA();     // Если работает пользователь SA, то можно добавить новый справочник
    lViewable = TApplication::exemplar()->isSA();       // Если работает пользователь SA, то можно просмотреть свойства справочника
    lDeleteable = TApplication::exemplar()->isSA();       // Если работает пользователь SA, то можно попытаться удалить справочник
    lUpdateable = false;
    lPrintable = false;
}

Dictionary* Dictionaries::getDictionary(QString dictName) {
    if (!dictionaries.contains(dictName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        if (!addDictionary(dictName, 0))
            return 0;
    }
    return dictionaries[dictName];
}


Saldo* Dictionaries::getSaldo(QString acc, QString dictName) {
    QString alias = "saldo" + acc;
    if (!dictionaries.contains(alias)) {             // Если справочник с таким именем не существует, то попробуем его создать
        if (!addSaldo(acc, dictName))
            return 0;
    }
    return (Saldo*)dictionaries[alias];
}


bool Dictionaries::addDictionary(QString dictName, int deep) {
    if (!dictionaries.contains(dictName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict;
        dict = new Dictionary(dictName, this);
        if (dict->open(deep)) {
            dictionaries.insert(dictName, dict);
            dict->setDictionaries(this);
            return true;
        }
    }
    return false;
}

bool Dictionaries::addSaldo(QString acc, QString dictName) {
    QString alias = "saldo" + acc;
    if (!dictionaries.contains(alias)) {
        Saldo* saldo = new Saldo(acc, dictName);
        if (saldo->open()) {
            dictionaries.insert(alias, saldo);
            saldo->setDictionaries(this);
            return true;
        }
    }
    return false;
}


void Dictionaries::removeDictionary(QString dictName) {
    if (dictionaries.contains(dictName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict = getDictionary(dictName);
        dict->close();
        dictionaries.remove(dictName);
    }
}


QString Dictionaries::getDictionaryTitle(QString dictName) {
    return TApplication::exemplar()->getDBFactory()->getDictionariesProperties(dictName).value(TApplication::nameFieldName()).toString();
}


bool Dictionaries::add()
{
    WizardDictionary wizard(true);
    wizard.open(TApplication::exemplar()->getMainWindow());
    wizard.getForm()->setWindowTitle(QObject::trUtf8("Новый справочник"));
    wizard.exec();
    wizard.close();
    if (wizard.getResult())
    {   // Если удалось создать справочник, то обновим список справочников
        dictionariesProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties();
        return true;
    }
    return false;
}


void Dictionaries::view()
{
    QString dictName = getValue("таблица").toString().trimmed();
    WizardDictionary wizard;
    wizard.open(TApplication::exemplar()->getMainWindow(), dictName);
    wizard.getForm()->setWindowTitle(QObject::trUtf8("Свойства справочника"));
    wizard.exec();
    wizard.close();
    if (wizard.getResult())
    {
        removeDictionary(dictName);
    }
}


bool Dictionaries::remove()
{
    if (Essence::remove())
    {
        if (TApplication::exemplar()->getDBFactory()->removeDictionary(getValue("таблица").toString().trimmed()))
        {   // если удалось удалить справочник, то обновим список справочников
            dictionariesProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties();
            return true;
        }
    }
    return false;
}


bool Dictionaries::open() {
    if (Essence::open()) {
        initForm();
        // formTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName);
        return true;
    }
    return false;
}


void Dictionaries::close() {
    foreach(Dictionary* dict, dictionaries) {
        dict->getForm()->writeSettings();
    }
    Essence::close();
}


void Dictionaries::query(QString filter) {
    if (filter.size() > 0)
        filter += " and ";
    filter += "меню=true";
    Essence::query(filter);
}


void Dictionaries::cmdOk() {
    Dictionary::cmdOk();
    QString dictName = getValue("таблица").toString().trimmed();
    if (dictName.size() > 0) {
        TApplication::exemplar()->getDictionaries()->addDictionary(dictName, 1);
        Dictionary* dict = TApplication::exemplar()->getDictionaries()->getDictionary(dictName);         // Откроем справочник и подсправочники 1-го уровня
        if (dict != 0)
            dict->show();
    }
}


void Dictionaries::setForm()
{
    Dictionary::setForm();
    if (form->isDefaultForm())
    {
        QPushButton* button;
        button = form->getButtonOk();
        if (button != NULL)
            button->setToolTip(trUtf8("Открыть справочник"));
        button = form->getButtonCancel();
        if (button != NULL)
            button->setToolTip(trUtf8("Закрыть список справочников"));;
        button = form->getButtonAdd();
        if (button != NULL)
            button->setToolTip(trUtf8("Создать новый справочник"));
        button = form->getButtonDelete();
        if (button != NULL)
            button->setToolTip(trUtf8("Удалить справочник"));
        button = form->getButtonView();
        if (button != NULL)
            button->setToolTip(trUtf8("Просмотреть свойства справочника"));
        button = form->getButtonRequery();
        if (button != NULL)
            button->setToolTip(trUtf8("Обновить список справочников (загрузить повторно с сервера)"));
    }
}

