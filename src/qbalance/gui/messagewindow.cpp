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

#include <QtGui/QTextEdit>
#include "messagewindow.h"
#include "../kernel/app.h"

MessageWindow::MessageWindow() :
    QObject()
{
    subWindow = 0;
    textEditor = new QTextEdit();
    textEditor->setParent(subWindow);
    textEditor->setWindowTitle(QObject::trUtf8("Сообщения"));
}


MessageWindow::~MessageWindow()
{
    TApplication::exemplar()->getMainWindow()->removeMdiWindow(subWindow);
    subWindow = 0;
    delete textEditor;
}


void MessageWindow::print(QString str)
{
    textEditor->append(str);
    show();
}


void MessageWindow::show()
{
    if (subWindow == 0)
        subWindow = TApplication::exemplar()->getMainWindow()->appendMdiWindow(textEditor);

    if (subWindow != 0)
    {
        textEditor->show();
        subWindow->show();
    }
}
