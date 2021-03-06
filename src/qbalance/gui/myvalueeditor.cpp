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
#include "myvalueeditor.h"
#include "../kernel/app.h"

MyValueEditor::MyValueEditor(ConfigEntry& val, ConfigForm* confForm, QWidget *parent): QWidget(parent)
{
    value = &val;
    widget = 0 /*nullptr*/;
    configForm = confForm;

    if (value->valueType == CONFIG_VALUE_BOUND)
    {
        widget = new QComboBox(this);
        static_cast<QComboBox*>(widget)->addItems(QStringList() << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" << "115200");
        static_cast<QComboBox*>(widget)->setCurrentIndex(value->value.toInt());
        connect (widget, SIGNAL(activated(int)), this, SLOT(editingFinished(int)));
    }
    else if (value->valueType == CONFIG_VALUE_BOOLEAN)
    {
        widget = new QCheckBox(this);
        static_cast<QCheckBox*>(widget)->setTristate(false);
        Qt::CheckState state = value->value.toBool() ? Qt::Checked : Qt::Unchecked;
        static_cast<QCheckBox*>(widget)->setCheckState(state);
        connect (widget, SIGNAL(stateChanged(int)), this, SLOT(editingFinished(int)));
    }
    else if (value->valueType == CONFIG_VALUE_LABELSIZE)
    {
        widget = new QComboBox(this);
        QStringList values;
        values << "30*20" << "43*25" << "57*40";
        static_cast<QComboBox*>(widget)->addItems(values);
        static_cast<QComboBox*>(widget)->setCurrentIndex(values.indexOf(value->value.toString()));
        connect (widget, SIGNAL(activated(int)), this, SLOT(editingFinished(int)));
    }
    else if (value->valueType == CONFIG_VALUE_PASSWORD)
    {
        widget = new QLineEdit(value->value.toString(), this);
        static_cast<QLineEdit*>(widget)->setEchoMode(QLineEdit::Password);
        connect (widget, SIGNAL(editingFinished()), this, SLOT(editingFinished()));
    }
    else if (value->valueType == CONFIG_VALUE_PUSHBUTTON)
    {
        widget = new QPushButton(value->value.toString(), this);
        connect (widget, SIGNAL(pressed()), configForm->signalMapper, SLOT(map()));
        configForm->signalMapper->setMapping(widget, value->name);
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
        value->value.setValue(static_cast<QLineEdit*>(widget)->text());
    }
    else if (value->valueType == CONFIG_VALUE_BOOLEAN)
    {
        value->value.setValue(val == Qt::Checked ? true : false);
    }
    else if (value->valueType == CONFIG_VALUE_LABELSIZE)
    {
        value->value.setValue(static_cast<QComboBox*>(widget)->currentText());
    }
    else if (value->valueType == CONFIG_VALUE_INTEGER)
    {
        value->value.setValue(static_cast<QLineEdit*>(widget)->text().toInt());
    }
    else if (value->valueType == CONFIG_VALUE_PASSWORD)
    {
        value->value.setValue(static_cast<QLineEdit*>(widget)->text());
    }
}


