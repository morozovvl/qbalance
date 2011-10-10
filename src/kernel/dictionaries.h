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
private:
    QSqlQuery dictionariesProperties;
    virtual bool doOpen();
    virtual void doClose();
};

//Q_DECLARE_METATYPE(Dictionaries)

#endif // DICTIONARIES_H
