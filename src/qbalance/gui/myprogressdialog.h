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

#include <QProgressDialog>

class MyProgressDialog : public QProgressDialog
{
    Q_OBJECT
public:
    MyProgressDialog(QString = "", QWidget* = 0);

public slots:
      //Slot that is called when cancel Button is Clicked
    void cancel() {;}

protected:
    void keyPressEvent(QKeyEvent*);
};

#endif // MYPROGRESSDIALOG_H
