#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include <QSqlQuery>
#include <QObject>
#include "dictionary.h"

class Document;

class Documents : public Dictionary {
public:
    Documents(int, QObject *parent = 0);
    virtual ~Documents();
    bool open() { return doOpen(); }
    virtual void show();
    virtual bool add();
    virtual bool remove();
    virtual void view();
    virtual void query(QString filter = "");
    virtual QSqlQuery getColumnsHeaders();
    int getCurrentRow() { return currentRow; }
protected:
    virtual bool doOpen();
    virtual void doClose();
    virtual void setForm();
private:
    int operNumber;
    int currentRow;
    Document* currentDocument;
};

#endif // DOCUMENTS_H
