#ifndef FORMDOCUMENT_H
#define FORMDOCUMENT_H

#include <QWidget>
#include "formgrid.h"
#include "mynumericedit.h"

class Document;
class DocParameters;

class FormDocument : public FormGrid {
public:
    FormDocument();
    Document* getParent() { return (Document*)parent; }
    void parametersChangedEvent();
public slots:
    virtual void cmdOk();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void hide();
protected:
    virtual void remove();
private:
    QDateEdit*      dateEdit;
    QLineEdit*      numberEdit;
    DocParameters*  parameters;
    MyNumericEdit*    itogNumeric;
    virtual void createForm(QString, QWidget* pwgt = 0);
    virtual QDomElement createWidgetsStructure();
};

#endif // FORMDOCUMENT_H
