#include <QString>
#include "app.h"
#include "dictionaries.h"
#include "gui/formgridsearch.h"
#include "gui/mainwindow.h"

extern App* app;
extern QString programNameFieldName;

Dictionaries::Dictionaries(QObject *parent): Dictionary("vw_доступ_к_справочникам", parent) {
    dictionariesProperties = app->getDBFactory()->getDictionariesProperties();
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
    if (dictionariesProperties.first()) {
        do {
            QSqlRecord rec = dictionariesProperties.record();
            if (rec.field("таблица").value().toString().trimmed().toUpper() == dictName.trimmed().toUpper())
                return rec.field(property).value().toString().trimmed();
        } while (dictionariesProperties.next());
    }
    return "";
}

QString Dictionaries::getDictionaryTitle(QString dictName) {
    QString title = getDictionaryProperty(dictName, programNameFieldName).toString();
    if (title.size() > 0)
        return title;
    return getDictionaryProperty(dictName, "таблица").toString();
}

bool Dictionaries::doOpen() {
    configName = formTitle;
    if (Essence::doOpen()) {
        initForm();
        formTitle = app->getDictionaries()->getDictionaryTitle(tableName);
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
        app->getDictionaries()->addDictionary(dictName, 1);
        Dictionary* dict = app->getDictionaries()->getDictionary(dictName);         // Откроем справочник и подсправочники 1-го уровня
        if (dict != 0)
            dict->show();
    }
}
