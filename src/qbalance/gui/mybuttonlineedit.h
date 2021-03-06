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

#ifndef MYBUTTONLINEEDIT_H
#define MYBUTTONLINEEDIT_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QLineEdit>
    #include <QtGui/QPushButton>
#else
    #include <QtWidgets/QLineEdit>
    #include <QtWidgets/QPushButton>
#endif

//#include "form.h"

class MyButtonLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue)
public:
    MyButtonLineEdit(QWidget *parent = 0 /*nullptr*/);
    ~MyButtonLineEdit();
    QString value();
    void setValue(QString text);
    void setFormOnPushButton(QString (*form)());
protected:
//    virtual void paintEvent(QPaintEvent*);
private:
    QString         (*buttonForm)();
    QLineEdit*      lineEdit;
    QPushButton*    pushButton;
private slots:
    void            showForm();
};

#endif // MYBUTTONLINEEDIT_H
