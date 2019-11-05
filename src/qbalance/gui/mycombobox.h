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

#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QWidget>
    #include <QtGui/QComboBox>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QWidget>
    #include <QtWidgets/QComboBox>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif


class SearchParameters;

class MyComboBox : public QComboBox {
   Q_OBJECT
public:
    MyComboBox(QWidget* parent = nullptr);
    ~MyComboBox();
    virtual void setSearchParameters(SearchParameters* sp);

signals:
    void enterPressed(QWidget*);

private:
    void keyPressEvent(QKeyEvent*);     // Перехват нажатия клавиши Enter - для перехода с одного ComboBox на другой

    SearchParameters*   searchParameters;
};

#endif // MYCOMBOBOX_H
