#ifndef FORMDOCUMENT_H
#define FORMDOCUMENT_H

#include <QWidget>
#include "formgrid.h"
#include "numericedit.h"

class Document;
class DocParameters;

class FormDocument : public FormGrid {
public:
    FormDocument();
    Document* getParent() { return (Document*)parent; }
public slots:
    virtual void cmdOk();
protected:
    virtual void doShow();
    virtual void doHide();
    virtual void remove();
private:
    QDateEdit*      dateEdit;
    QLineEdit*      numberEdit;
    DocParameters*  parameters;
    NumericEdit*    itogNumeric;
    virtual void createForm(QString, QWidget* pwgt = 0);
    virtual QDomElement createWidgetsStructure();
};

#endif // FORMDOCUMENT_H
