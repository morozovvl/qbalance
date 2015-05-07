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

#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QtGui/QTextEdit>
#include "mainwindow.h"

class TApplication;

class MessageWindow : public QObject
{
    Q_OBJECT
public:
    explicit MessageWindow();
    ~MessageWindow();
    QTextEdit* getTextEditor() { return textEditor; }

public slots:
    void print(QString = "");
    void show();

private:
    QTextEdit*      textEditor;
    MyMdiSubWindow* subWindow;
    TApplication*    app;

    void readSettings();
    void writeSettings();
};


#endif // MESSAGEWINDOW_H
