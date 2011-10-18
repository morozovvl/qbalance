#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QSqlTableModel>
#include <QString>
#include <QMap>
#include "essence.h"
#include "dictionaries.h"


class TApplication;
class Documents;
class DocumentTableModel;

struct prvSaldo {
    double  dbQuan;
    double  dbSaldo;
    double  crQuan;
    double  crSaldo;
};

class Document : public Essence {
public:
    Document(int, Documents*);
    virtual ~Document();
    int getDocId() { return docId; }
    Documents* getParent() { return parent; }
    QMap<QString, Dictionary*>* getDictionaries() { return dicts; }
    virtual bool add();
    virtual bool remove();
    virtual void show();
    virtual QString transformSelectStatement(QString string);
    void setDocId(int doc) { docId = doc; }
    virtual bool calculate(const QModelIndex &);
    virtual void setOldCalculateProperties(const QModelIndex &);
    virtual void setConstDictId(QString, QVariant);
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
protected:
    virtual void setForm();
    virtual void preparePrintValues(QMap<QString, QVariant>*);     // Готовит значения для печати
private:
    QMap<QString, Dictionary*>*     dicts;              // Объекты справочников
    Dictionaries*                   dictionaries;       // Объекты справочников
    Documents*                      parent;
    DBFactory*                      DbFactory;
    int operNumber;
    int docId;
    int prv1;
    QSqlTableModel toper;
    QString selectStatement;
    QHash<int, prvSaldo> saldo;                   // содержит остаток и сальдо по счетам, корреспондирующим в текущей строке документа
    virtual void setTableModel();
    bool showNextDict();
    void unlock();
    void insertDocString();
    virtual void getCalculateProperties(const QModelIndex &);
};

#endif // DOCUMENT_H
