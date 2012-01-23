#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>
#include <QString>
#include "essence.h"
#include "../gui/formgridsearch.h"

class TApplication;
class Dictionaries;

class Dictionary : public Essence {
    Q_OBJECT

public:
    Dictionary(QObject *parent = 0) { Dictionary("", parent); }
    Dictionary(QString name, QObject *parent = 0);
    ~Dictionary();
//    Q_INVOKABLE virtual bool open() { return open(0); }
    Q_INVOKABLE virtual bool open(int i = 0);                 // Открыть справочник. i - глубина вложения подсправочников (те, на которые может ссылаться этот справочник)

// Функции для работы с моделью данных
    virtual bool add();
    virtual bool remove();
    Q_INVOKABLE virtual qulonglong      getId(int row = -1);


// Функции для работы справочника в составе документа
// Используются в момент добавления новых записей в документ
// блокируют открытие связанных справочников и др.подобные функции
    bool canShow() { return lCanShow; }
    void setCanShow(bool can) { lCanShow = can; }
    bool isMustShow() { return lMustShow; }
    virtual void setMustShow(bool must) { lMustShow = must; }
    bool isConst() { return lIsConst; }
    bool isSet() { return lIsSet; }
    void setConst(bool con) { lIsConst = con; }
    void setAutoSelect(bool autoSelect) { lAutoSelect = autoSelect; }
    void setDictionaries(Dictionaries* dicts) { dictionaries = dicts; }     // Устанавливает указатель на список справочников,
                                                                            // которые будут блокироваться при добавлении записи в документ
    Dictionaries* getDictionaries() { return dictionaries; }

    virtual QString objectName() { return "Dictionary"; }
    int getDeep() { return dictDeep; }
    QString getPrototypeName() { return prototypeName; }
    void setPrototypeName(QString prototype) { prototypeName = prototype; }

protected:
    Dictionaries*   dictionaries;
    QString         prototypeName;          // Имя справочника - прототипа
    bool            lSelectable;
    bool            lIsSet;
    bool            lCanShow;
    bool            lMustShow;
    bool            lIsConst;
    bool            lAutoSelect;
    int             dictDeep;
    virtual void setForm();
private:
    QStringList     fieldList;
};

#endif // DICTIONARY_H
