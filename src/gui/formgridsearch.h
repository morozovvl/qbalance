#ifndef FORMGRIDSEARCH_H
#define FORMGRIDSEARCH_H

#include <QWidget>
#include <QSqlTableModel>
#include <QShowEvent>
#include "formgrid.h"

class Dictionary;
class SearchParameters;
extern App* app;

struct sParam {
    QString field;
    QString table;
    QVariant value;
};

class FormGridSearch : public FormGrid {

public:
    Q_INVOKABLE virtual bool open(QWidget* pwgt = 0, Essence* par = 0);
    Q_INVOKABLE virtual void close();
    Dictionary* getParent() { return (Dictionary*)parent; }
    virtual void setShowFocus();
    SearchParameters* getSearchParameters() { return parameters; }

private:
    void query(QString param = "");
    SearchParameters* parameters;
    QVector<sParam> searchParameters;
    virtual QDomElement createWidgetsStructure();

};

#endif // FORMGRIDSEARCH_H
