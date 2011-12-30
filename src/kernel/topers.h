#ifndef TOPERS_H
#define TOPERS_H

#include <QString>
#include "dictionary.h"

class Topers : public Dictionary {
public:
    Topers(QObject *parent = 0);
    void cmdOk();
    Q_INVOKABLE virtual bool add();
//    Q_INVOKABLE virtual bool remove();
    Q_INVOKABLE virtual void view();
protected:
    virtual void setForm();
private:
    void addDocument(int);
    void removeDocument(int opNumber);
};

#endif // TOPERS_H
