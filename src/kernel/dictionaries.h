#ifndef DICTIONARIES_H
#define DICTIONARIES_H

#include <QSqlQuery>
#include "dictionary.h"

class Dictionaries : public Dictionary {
    Q_OBJECT
public:
    QMap<QString, Dictionary*> dictionaries;                    // Объекты справочников
    Dictionaries(QObject *parent = 0);
    virtual Dictionary* getDictionary(QString);
    Q_INVOKABLE virtual void addDictionary(QString, int = 0);
    Q_INVOKABLE virtual void removeDictionary(QString);
    virtual QVariant getDictionaryProperty(QString, QString);
    QString getDictionaryTitle(QString);
    bool isMember(QString dictName) { return dictionaries.contains(dictName); }
    void query(QString);
    QMap<QString, Dictionary*>* getDictionaries() { return &dictionaries; }
    virtual void cmdOk();
    Q_INVOKABLE virtual bool add();        // Добавление справочника
    Q_INVOKABLE virtual bool remove();     // Удаление справочника
    Q_INVOKABLE virtual void view();       // Исправление свойств справочника
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
private:
    QSqlQuery dictionariesProperties;
};

//Q_DECLARE_METATYPE(Dictionaries)

#endif // DICTIONARIES_H
