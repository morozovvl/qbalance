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


#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QKeyEvent>
#include <QtGui/QMdiSubWindow>
#include <QtDesigner/QDesignerExportWidget>
#include "../kernel/app.h"

class MainWindow;


class QDESIGNER_WIDGET_EXPORT Dialog : public QDialog

{
    Q_OBJECT
public:
    int     formX, formY, formW, formH;

    Dialog(QWidget *parent = 0);

    Q_INVOKABLE void show();
    Q_INVOKABLE int exec();
    Q_INVOKABLE void hide();
    Q_INVOKABLE QWidget* findChild(QString);

    void setFreeWindow(bool free) { freeWindow = free; }
    void setApp(TApplication*);


public slots:

signals:
    void keyPressed(QKeyEvent *e);

private:
    TApplication*                   app;
    QMdiSubWindow*  subWindow;
    bool    freeWindow;         // По умолчанию окно не является свободным, я является частью Mdi интерфейса
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // DIALOG_H
