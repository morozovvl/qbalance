#ifndef DOCPARAMETERS_H
#define DOCPARAMETERS_H

#include <QtGui>
#include <QMap>
#include <QList>
#include <QFrame>
#include <QString>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include "app.h"
#include "mycombobox.h"
#include "formgridsearch.h"

class TApplication;
class FormDocument;

class DocParameters : public QFrame {
    Q_OBJECT

public:
    DocParameters(QWidget* pwgt = 0);
    ~DocParameters();
    void addString(QString);
    void removeString(int);
    QStringList getKeys() { return dictList; }
    Dictionary* getDictionary(QString dictName) { return dictionaries->value(dictName); }
    void setDictionaries(QMap<QString, Dictionary*>* dicts) { dictionaries = dicts; }
    void setFocus();
    void setFormDocument(FormDocument* doc) { parentForm = doc; }
    void showText(QString);
    int count() { return strNum; }
    void setApp(TApplication* a) { app = a; }
    void setProgramIdFieldName(QString s) { programIdFieldName = s; }
    void setProgramNameFieldName(QString s) { programNameFieldName = s; }

public slots:
    void dictionaryButtonPressed();

private:
    TApplication* app;
    QString programIdFieldName;
    QString programNameFieldName;
    QMap<QString, Dictionary*>* dictionaries;
    int strNum;
    QGridLayout* gridLayout;
    QStringList parameters;
    QStringList dictList;
    FormDocument* parentForm;

};

#endif // DOCPARAMETERS_H
