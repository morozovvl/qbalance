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
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include "myvalueeditor.h"
#include "../kernel/app.h"

MyValueEditor::MyValueEditor(ConfigEntry& val, QWidget *parent): QWidget(parent)
{
    value = &val;
    widget = 0;

    if (value->valueType == CONFIG_VALUE_BOUND)
    {
        widget = new QComboBox(this);
        ((QComboBox*)widget)->addItems(QStringList() << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" << "115200");
        ((QComboBox*)widget)->setCurrentIndex(value->value.toInt());
        connect (widget, SIGNAL(activated(int)), this, SLOT(editingFinished(int)));
    }
    else if (value->valueType == CONFIG_VALUE_BOOLEAN)
    {
        widget = new QCheckBox(this);
        ((QCheckBox*)widget)->setTristate(false);
        Qt::CheckState state = value->value.toBool() ? Qt::Checked : Qt::Unchecked;
        ((QCheckBox*)widget)->setCheckState(state);
        connect (widget, SIGNAL(stateChanged(int)), this, SLOT(editingFinished(int)));
    }
    else if (value->valueType == CONFIG_VALUE_LABELSIZE)
    {
        widget = new QComboBox(this);
        QStringList values;
        values << "30*20" << "43*25" << "57*40";
        ((QComboBox*)widget)->addItems(values);
        ((QComboBox*)widget)->setCurrentIndex(values.indexOf(value->value.toString()));
        connect (widget, SIGNAL(activated(int)), this, SLOT(editingFinished(int)));
    }
    else
    {
        widget = new QLineEdit(value->value.toString(), this);
        connect (widget, SIGNAL(editingFinished()), this, SLOT(editingFinished()));
    }
}


MyValueEditor::~MyValueEditor()
{
    delete widget;
}


QWidget* MyValueEditor::getEditor()
{
    return widget;
}


void MyValueEditor::editingFinished(int val)
{
    if (value->valueType == CONFIG_VALUE_BOUND)
    {
        value->value.setValue(val);
    }
    else if (value->valueType == CONFIG_VALUE_STRING)
    {
        value->value.setValue(((QLineEdit*)widget)->text());
    }
    else if (value->valueType == CONFIG_VALUE_BOOLEAN)
    {
        value->value.setValue(val == Qt::Checked ? true : false);
    }
    else if (value->valueType == CONFIG_VALUE_LABELSIZE)
    {
        value->value.setValue(((QComboBox*)widget)->currentText());
    }
}


