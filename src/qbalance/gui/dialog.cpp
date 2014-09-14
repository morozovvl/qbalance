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

#include <QPushButton>
#include "../kernel/app.h"
#include "dialog.h"


Dialog::Dialog(QWidget *parent, Qt::WindowFlags f):
    QDialog(parent, f)
{
    app = 0;
    form = 0;
    buttonOk = 0;
    isSelected = false;
}


Dialog::~Dialog()
{
}


void Dialog::setApp(TApplication* a)
{
    app = a;
    setParent(app->getMainWindow(), Qt::Dialog);
}


void Dialog::findCmdOk()
{
    buttonOk = (QPushButton*)this->findChild("buttonOk");
    if (buttonOk != 0)
    {
        connect(buttonOk, SIGNAL(clicked()), this, SLOT(cmdOk()));
    }
}


void Dialog::cmdOk()
{
    isSelected = true;
    if (form != 0)
        form->cmdOk();
    else
        accept();
}


bool Dialog::isFormSelected()
{
    if (form != 0)
        return form->isFormSelected();
    return isSelected;
}


void Dialog::showEvent(QShowEvent* event)
{
    isSelected = false;
    QDialog::showEvent(event);
    if (form != 0)
        form->activateWidget();
}


QObject* Dialog::findChild(QString name)
{
    QObject* widget = QDialog::findChild<QObject*>(name);
    return widget;
}


void Dialog::keyPressEvent(QKeyEvent *event)
{

    if (form != 0)                              // Если у формы есть владелец, то запустим его обработчик
        form->keyPressEvent(event);
}


