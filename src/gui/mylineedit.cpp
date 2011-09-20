#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QSqlQueryModel>
#include "mylineedit.h"
#include "myitemdelegate.h"
#include "form.h"
#include "formgrid.h"
#include "../essence.h"

MyLineEdit::MyLineEdit(DelegateTypes type, QWidget* par, QObject* parForm, QModelIndex &idx): QLineEdit(par) {
    delegateType = type;
    setAlignment(Qt::AlignRight);
    parentForm = parForm;
    parent = ((FormGrid*)parentForm)->getParent();
    index = idx;
    oldValue = parent->getMyRelationalTableModel()->data(index);
// Уберем, пока не разберемся со скриптами
//    parent->setOldCalculateProperties(index);
    calculated = false;
}

MyLineEdit::~MyLineEdit() {
    calculate();
}

void MyLineEdit::calculate() {
    if (text().toDouble() != oldValue.toDouble()) {
        parent->getMyRelationalTableModel()->setData(index, QVariant(text().toDouble()));
// Уберем, пока не разберемся со скриптами
//        calculated = parent->calculate(index);
    }
}

