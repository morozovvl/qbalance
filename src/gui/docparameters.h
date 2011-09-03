#ifndef DOCPARAMETERS_H
#define DOCPARAMETERS_H

#include <QtGui>
#include <QFrame>
#include <QVBoxLayout>
#include <QString>
#include <QList>
#include <QWidget>
#include <QObject>
#include <QMap>
#include <QStringList>
#include "mycombobox.h"
#include "formgridsearch.h"
#include "../app.h"

class App;
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
    void setApp(App* a) { app = a; }
    void setProgramIdFieldName(QString s) { programIdFieldName = s; }
    void setProgramNameFieldName(QString s) { programNameFieldName = s; }

public slots:
    void dictionaryButtonPressed();

private:
    App* app;
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
