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

#include <QDebug>
#include "../kernel/app.h"
#include "dialog.h"


Dialog::Dialog(QWidget *parent):
    QDialog(parent)
{
    app = 0;
    freeWindow = false;
    subWindow = 0;
}


void Dialog::setApp(TApplication* a)
{
    app = a;
    setParent(app->getMainWindow(), Qt::Dialog);
}


void Dialog::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);

    form->keyPressEvent(event);
    if (!event->isAccepted())
        QDialog::keyPressEvent(event);
}


void Dialog::show()
{
    if (!freeWindow)
    {
        if (subWindow == 0)
            subWindow = app->getMainWindow()->appendMdiWindow(this);
        subWindow->show();
    }
    QDialog::show();
}


int Dialog::exec()
{
   return QDialog::exec();
}


void Dialog::hide()
{
    if (!freeWindow)
    {
        if (subWindow != 0)
        {
            subWindow->hide();
        }
    }
    QDialog::hide();
}


MyMdiSubWindow* Dialog::getSubWindow()
{
    if (app != 0 && !freeWindow)
    {
        if (subWindow == 0)
            subWindow = app->getMainWindow()->appendMdiWindow(this);
        return subWindow;
    }
    return 0;
}


QWidget* Dialog::findChild(QString name)
{
    QWidget* widget = QDialog::findChild<QWidget*>(name);
    if (widget == 0)
        app->showError(QString(QObject::trUtf8("Не найден объект %1")).arg(name));
    return widget;
}

