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

#include <QDialog>
#include <QKeyEvent>
#include <QtDesigner/QDesignerExportWidget>
#include "../kernel/app.h"
#include "mymdisubwindow.h"
#include "form.h"

class MainWindow;


class QDESIGNER_WIDGET_EXPORT Dialog : public QDialog

{
    Q_OBJECT
public:

    Dialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~Dialog();
    Q_INVOKABLE QObject* findChild(QString);
    Q_INVOKABLE QString test() { return "test"; }
    Q_INVOKABLE bool isFormSelected();

    void setApp(TApplication*);
    void setForm(Form* f) { form = f; }
    Form* getForm() { return form; }
    void    findCmdOk();
    virtual void keyPressEvent(QKeyEvent*);

protected:
    virtual void showEvent(QShowEvent*);

private:
    TApplication*               app;
    Form*                       form;
    QPushButton*                buttonOk;
    bool                        isSelected;

private slots:
    void    cmdOk();
};

#endif // DIALOG_H
