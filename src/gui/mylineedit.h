#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QtGui>
#include <QLineEdit>
#include <QModelIndex>
#include "myitemdelegate.h"

class Essence;
class FormGrid;

class MyLineEdit : public QLineEdit {
    Q_OBJECT
public:
    MyLineEdit(DelegateTypes, QWidget*, QObject*, QModelIndex &);
    ~MyLineEdit();
public slots:
    void calculate();
private:
    DelegateTypes delegateType;
    Essence* parent;
    QObject* parentForm;
    QModelIndex index;
    bool calculated;
    QVariant oldValue;
};

#endif // MYLINEEDIT_H
