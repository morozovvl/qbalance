#include <QString>
#include "dictionaries.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/adddictionarywizard.h"


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
        return 0;
    }
    return dictionaries[dictName];
}

void Dictionaries::addDictionary(QString dictName, int deep) {
    if (!dictionaries.contains(dictName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict = new Dictionary(dictName, this);
        if (dict->open(deep)) {
            dictionaries.insert(dictName, dict);
            dict->setDictionaries(this);
        }
    }
}

void Dictionaries::removeDictionary(QString dictName) {
    if (dictionaries.contains(dictName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict = getDictionary(dictName);
        dict->close();
        dictionaries.remove(dictName);
    }
}


QVariant Dictionaries::getDictionaryProperty(QString dictName, QString property) {
    QVariant result;

    for (dictionariesProperties.first(); result.isNull() && dictionariesProperties.isValid(); dictionariesProperties.next()) {
        QSqlRecord record = dictionariesProperties.record();
        if (record.field("таблица").value().toString().trimmed().toUpper() == dictName.trimmed().toUpper())
            result = record.field(property).value().toString().trimmed();
    }
    return result;
}

QString Dictionaries::getDictionaryTitle(QString dictName) {
    QString title = getDictionaryProperty(dictName, TApplication::nameFieldName()).toString();
    if (!title.isEmpty())
        return title;
    return getDictionaryProperty(dictName, "таблица").toString();
}


bool Dictionaries::add()
{
    AddDictionaryWizard wizard;
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
    AddDictionaryWizard wizard;
    wizard.open(TApplication::exemplar()->getMainWindow());
    wizard.getForm()->setWindowTitle(QObject::trUtf8("Свойства справочника"));
    wizard.getData(getValue("таблица").toString().trimmed());
    wizard.exec();
    wizard.close();
}


bool Dictionaries::remove()
{
    if (TApplication::exemplar()->getDBFactory()->removeDictionary(getValue("таблица").toString().trimmed()))
    {   // если удалось удалить справочник, то обновим список справочников
        dictionariesProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties();
        return true;
    }
    return false;
}


bool Dictionaries::open() {
    if (Essence::open()) {
        initForm();
        formTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName);
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
