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

#ifndef MYVALUEEDITOR_H
#define MYVALUEEDITOR_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QWidget>
    #include <QtGui/QLineEdit>
    #include <QtGui/QComboBox>
    #include <QtGui/QCheckBox>
    #include <QtGui/QPushButton>
#else
    #include <QtWidgets/QWidget>
    #include <QtWidgets/QLineEdit>
    #include <QtWidgets/QComboBox>
    #include <QtWidgets/QCheckBox>
    #include <QtWidgets/QPushButton>
#endif

#include "configform.h"

struct ConfigEntry;

class MyValueEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MyValueEditor(ConfigEntry&, ConfigForm*, QWidget *parent = 0 /*nullptr*/);
    ~MyValueEditor();
    QWidget* getEditor();

signals:

private slots:
    void editingFinished(int = 0);

private:
    ConfigEntry* value;
    QWidget* widget;
    QString stringValue;
    ConfigForm* configForm;
};

#endif // MYVALUEEDITOR_H
