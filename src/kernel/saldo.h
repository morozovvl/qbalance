#ifndef SALDO_H
#define SALDO_H

#include "dictionary.h"

class Saldo : public Dictionary {
public:
    Saldo(QString, QString, QObject *parent = 0);
    virtual QString transformSelectStatement(QString);
    virtual QString objectName() { return "Saldo"; }
    void setQuan(bool q) { quan = q; }
    virtual void setLock(bool);
    virtual void setMustShow(bool);
    Q_INVOKABLE virtual bool open(int = 0);
private:
    QString account;
    QString dictionaryName;
    bool quan;
};

#endif // SALDO_H
