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
    virtual bool add();
    virtual bool remove();
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
    virtual QString objectName() { return "Dictionary"; }
    void setDictionaries(Dictionaries* dicts) { dictionaries = dicts; }
    int getDeep() { return dictDeep; }

    Q_INVOKABLE virtual bool open() { return open(0); }
    Q_INVOKABLE virtual bool open(int i) { return doOpen(i); }          // Открыть справочник. i - глубина вложения подсправочников (те, на которые может ссылаться этот справочник)
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
    virtual bool doOpen(int);
};

#endif // DICTIONARY_H
