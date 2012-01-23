#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QSqlTableModel>
#include <QString>
#include <QMap>
#include "essence.h"
#include "dictionaries.h"
#include "../engine/documentscriptengine.h"


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
    Q_OBJECT
public:
    Document(int, Documents*);
    virtual ~Document();
    Q_INVOKABLE int getDocId() { return docId; }
    Documents* getParent() { return parent; }
    QMap<QString, Dictionary*>* getDictionaries() { return dicts; }
    Q_INVOKABLE Dictionary* getDictionary(QString dictName) { return dictionaries->getDictionary(dictName); }
    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove();
    Q_INVOKABLE virtual void show();
    virtual QString transformSelectStatement(QString string);
    void setDocId(int doc) { docId = doc; }
    virtual bool calculate(const QModelIndex &);
    virtual void setConstDictId(QString, QVariant);
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    virtual void setScriptEngine();
    DocumentScriptEngine* getScriptEngine();
    void getEventAfterAddString();
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
    QList<ToperType>                topersList;
    QString selectStatement;
    QHash<int, prvSaldo> saldo;                   // содержит остаток и сальдо по счетам, корреспондирующим в текущей строке документа
    virtual void setTableModel();
    bool showNextDict();
    void insertDocString();
    void selectCurrentRow();
};

#endif // DOCUMENT_H
