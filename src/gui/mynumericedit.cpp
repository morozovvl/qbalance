#include <QVariant>
#include <QLocale>
#include <QDebug>
#include "mynumericedit.h"

MyNumericEdit::MyNumericEdit(QWidget *parent): QLineEdit(parent) {
    setAlignment(Qt::AlignRight);
    setValue(0);
}

void MyNumericEdit::setValue(QVariant val) {
    value = val;
    QLocale locale;
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    QString text = locale.toString(value.toDouble(), 'f', 2);
    setText(text);
}
