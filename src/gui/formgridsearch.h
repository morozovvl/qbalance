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
    explicit FormGridSearch(QObject* parent = NULL);
    Q_INVOKABLE virtual void close();
    Dictionary* getParent() { return (Dictionary*)parent; }
    virtual void setShowFocus();
    SearchParameters* getSearchParameters() { return parameters; }

private:
    SearchParameters*   parameters;
    QVector<sParam>     searchParameters;
    void query(QString param = "");
    virtual void createForm(QString, QWidget* pwgt = 0);
    virtual QDomElement createWidgetsStructure();

};

#endif // FORMGRIDSEARCH_H
