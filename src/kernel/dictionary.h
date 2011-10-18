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
    Q_INVOKABLE virtual bool open() { return open(0); }
    Q_INVOKABLE virtual bool open(int i);                 // Открыть справочник. i - глубина вложения подсправочников (те, на которые может ссылаться этот справочник)

// Функции для работы с моделью данных
    virtual bool add();
    virtual bool remove();

// Функции для работы справочника в составе документа
// Используются в момент добавления новых записей в документ
// блокируют открытие связанных справочников и др.подобные функции
    bool canShow() { return lCanShow; }
    void setCanShow(bool can) { lCanShow = can; }
    bool isMustShow() { return lMustShow; }
    virtual void setMustShow(bool must) { lMustShow = must; }
    bool isLocked() { return lIsLocked; }
    virtual void setLock(bool);
    void unlock() { lIsLocked = false; }
    bool isConst() { return lIsConst; }
    bool isSet() { return lIsSet; }
    void setConst(bool con) { lIsConst = con; }
    void setAutoSelect(bool autoSelect) { lAutoSelect = autoSelect; }
    bool isAutoAdd() { return lAutoAdd; }
    void setAutoAdd(bool add) { lAutoAdd = add; }
    void setDictionaries(Dictionaries* dicts) { dictionaries = dicts; }     // Устанавливает указатель на список справочников,
                                                                            // которые будут блокироваться при добавлении записи в документ

    virtual QString objectName() { return "Dictionary"; }
    int getDeep() { return dictDeep; }

protected:
    Dictionaries* dictionaries;
    bool lIsSet;
    bool lCanShow;
    bool lMustShow;
    bool lIsLocked;
    bool lIsConst;
    bool lAutoSelect;
    bool lAutoAdd;
    int dictDeep;
    virtual void setForm();
};

#endif // DICTIONARY_H