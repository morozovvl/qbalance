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
    formX = 100;
    formY = 100;
    formW = 600;
    formH = 300;
    subWindow = 0;
}


void Dialog::setApp(TApplication* a)
{
    app = a;
}


void Dialog::keyPressEvent(QKeyEvent *e)
{
    emit keyPressed(e);
    QDialog::keyPressEvent(e);
}


void Dialog::show()
{
    if (!freeWindow)
    {
        subWindow = app->getMainWindow()->appendMdiWindow(this);
        if (subWindow != 0)
        {
            subWindow->setGeometry(formX, formY, formW, formH);
            subWindow->show();
        }
    }
    QDialog::show();
}


int Dialog::exec()
{
    if (!freeWindow)
    {
        setParent(app->getMainWindow(), Qt::Dialog);
    }
    return QDialog::exec();
}


void Dialog::hide()
{
    if (!freeWindow)
    {
        if (subWindow != 0)
        {
            formX = subWindow->x();
            formY = subWindow->y();
            formW = subWindow->width();
            formH = subWindow->height();
            app->getMainWindow()->removeMdiWindow(subWindow);
            subWindow = 0;
        }
    }
    QDialog::hide();
}


QWidget* Dialog::findChild(QString name)
{
    return QDialog::findChild<QWidget*>(name);
}

