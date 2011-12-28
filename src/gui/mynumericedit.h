#ifndef NUMERICEDIT_H
#define NUMERICEDIT_H

#include <QtGui>
#include <QLineEdit>
#include <QVariant>
#include <QWidget>
#include <QAbstractItemDelegate>

class MyNumericEdit : public QLineEdit {
    Q_OBJECT
public:
//    explicit MyNumericEdit(QWidget *parent = 0);
    MyNumericEdit(QWidget *parent = 0);
    void setValue(QVariant);
    QVariant getValue() { return value; }
private:
    QVariant value;
};

#endif // NUMERICEDIT_H
