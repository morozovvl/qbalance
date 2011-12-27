#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <QtGui>
#include <QFrame>
#include <QVBoxLayout>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <QObject>
#include "mycombobox.h"
#include "formgridsearch.h"
#include "guifactory.h"

class TApplication;
class FormGridSearch;
struct sParam;

class SearchParameters : public QFrame {
    Q_OBJECT

public:
    SearchParameters(QWidget* parentWidget = 0);
    void close();
    void getParameters(QVector<sParam> &);              // Возвращает информацию о заданных параметрах поиска
    void setFieldsList(QStringList);
    void setFocus();
    void setFormGrid(FormGridSearch* par) { parentForm = par; }
    void setApp(TApplication* a) { app = a; }
    void setProgramIdFieldName(QString s) { programIdFieldName = s; }
    void setProgramNameFieldName(QString s) { programNameFieldName = s; }

signals:
    void requery();

public slots:
    void dictionaryButtonPressed();
    void comboBoxEnterPressed(QWidget*);

private:
    TApplication* app;
    QString programIdFieldName;
    QString programNameFieldName;
    QGridLayout* gridLayout;
    QStringList parameters;
    FormGridSearch* parentForm;
    void addString(QString, int);
    void removeString(int);
};

#endif // SEARCHPARAMETERS_H
