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
/* За основу взят исходный код отсюда: http://codeprogress.com/cpp/libraries/qt/QProgressDialogNoButton.php#.VPRf2R3V7eQ */

#ifndef MYPROGRESSDIALOG_H
#define MYPROGRESSDIALOG_H

#include <QtCore/QtGlobal>
#if QT_VERSION < 0x050000
    #include <QtGui/QProgressDialog>
#else
    #include <QtWidgets/QProgressDialog>
#endif

class MyProgressDialog : public QProgressDialog
{
    Q_OBJECT
public:
    MyProgressDialog(QString = "", QWidget* = 0 /*nullptr*/);
    ~MyProgressDialog();
    Q_INVOKABLE virtual void setTitle(QString);
    Q_INVOKABLE virtual bool isEscapeKeyPressed();
    Q_INVOKABLE virtual void setValue(int);

public slots:
      //Slot that is called when cancel Button is Clicked
    virtual void show();
    virtual void hide();

protected:
    virtual void keyPressEvent(QKeyEvent*);

private:
    bool    escapeKeyPressed;

};

#endif // MYPROGRESSDIALOG_H
