#ifndef NUMERICEDIT_H
#define NUMERICEDIT_H

#include <QtGui>
#include <QLineEdit>
#include <QVariant>
#include <QWidget>
#include <QAbstractItemDelegate>

class NumericEdit : public QLineEdit {
    Q_OBJECT
public:
//    explicit NumericEdit(QWidget *parent = 0);
    NumericEdit(QWidget *parent = 0);
    void setValue(QVariant);
    QVariant getValue() { return value; }
private:
    QVariant value;
};

#endif // NUMERICEDIT_H
