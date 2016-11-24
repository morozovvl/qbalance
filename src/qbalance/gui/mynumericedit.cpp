/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QtCore/QVariant>
#include <QtCore/QLocale>
#include <QtGui/QKeyEvent>
#include "mynumericedit.h"

MyNumericEdit::MyNumericEdit(QWidget *parent): QLineEdit(parent) {
    decimals = 2;
    setAlignment(Qt::AlignRight);
    setValue(0);
}


QVariant MyNumericEdit::getValue()
{
    return value;
}


void MyNumericEdit::setValue(QVariant val) {
    value = val;
    QLocale locale;
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    QString text = locale.toString(value.toDouble(), 'f', decimals);
    setText(text);
}


void MyNumericEdit::setDecimals(int dec)
{
    decimals = dec;
}

