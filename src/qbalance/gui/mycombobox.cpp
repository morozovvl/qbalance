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

#include <QtCore/QtGlobal>

#include <QtGui/QComboBox>
#include <QtGui/QKeyEvent>
#include "mycombobox.h"
#include "searchparameters.h"


MyComboBox::MyComboBox(QWidget* parent): QComboBox(parent)
{
        searchParameters = 0 /*nullptr*/;
}


MyComboBox::~MyComboBox()
{
}


void MyComboBox::setSearchParameters(SearchParameters* sp)
{
    searchParameters = sp;
}


void MyComboBox::keyPressEvent(QKeyEvent* event) {
    if (event->modifiers() != Qt::ControlModifier && ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)))
        emit enterPressed(this);
    else
    {
        searchParameters->keyPressEvent(event);
        if (!event->isAccepted())
            QComboBox::keyPressEvent(event);
    }
}

