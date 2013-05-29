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

#include <QtGui/QPushButton>
#include "../kernel/app.h"
#include "dialog.h"


Dialog::Dialog(QWidget *parent, Qt::WindowFlags f):
    QDialog(parent, f)
{
    app = 0;
    form = 0;
    buttonOk = 0;
}


void Dialog::setApp(TApplication* a)
{
    app = a;
    setParent(app->getMainWindow(), Qt::Dialog);
}


void Dialog::findCmdOk()
{
    buttonOk = qFindChild<QPushButton*>(this, "buttonOk");
    if (buttonOk != 0)
    {
        connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
        connect(buttonOk, SIGNAL(clicked()), this, SIGNAL(cmdOkPressed()));
    }
}


void Dialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    if (form != 0)
        form->activateWidget();
}


QWidget* Dialog::findChild(QString name)
{
    QWidget* widget = QDialog::findChild<QWidget*>(name);
    if (widget == 0)
        app->showError(QString(QObject::trUtf8("Не найден объект %1")).arg(name));
    return widget;
}


void Dialog::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            emit cmdOkPressed();
            accept();
            return;
        }
    }
    if (form != 0)
        form->keyPressEvent(event);
    else
        QDialog::keyPressEvent(event);
}


