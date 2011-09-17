#include <QString>
#include "app.h"
#include "dictionaries.h"
#include "gui/formgridsearch.h"
#include "gui/mainwindow.h"

Dictionaries::Dictionaries(QObject *parent): Dictionary("vw_доступ_к_справочникам", parent) {
    dictionariesProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties();
    lInsertable = false;                    // Список справочников нельзя редактировать
    lDeleteable = false;
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


bool Dictionaries::doOpen() {
    if (Essence::doOpen()) {
        initForm();
        formTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName);
        return true;
    }
    return false;
}

void Dictionaries::doClose() {
    foreach(Dictionary* dict, dictionaries) {
        dict->getForm()->writeSettings();
    }
    Essence::doClose();
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
