#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include <QSqlQuery>
#include <QObject>
#include "dictionary.h"
#include "essence.h"

class Document;

class Documents : public Dictionary {
    Q_OBJECT
public:
    Documents(int, QObject *parent = 0);
    virtual ~Documents();
    virtual void show();
    virtual bool add();
    virtual bool remove();
    virtual void view();
    virtual void query(QString filter = "");
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
protected:
    virtual void setForm();
private:
    int operNumber;
    Document* currentDocument;
};

#endif // DOCUMENTS_H
