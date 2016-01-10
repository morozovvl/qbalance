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

#ifndef BANKTERMINAL_H
#define BANKTERMINAL_H

#include <QtCore/QObject>
#include <QDebug>
//#include "../kernel/app.h"

class TApplication;

class BankTerminal : public QObject
{
    Q_OBJECT
public:
    explicit BankTerminal(QObject *parent = 0);
    virtual bool open();
    virtual void close();
    virtual void setApp(TApplication* a) { app = a; }
    Q_INVOKABLE virtual void test() { qDebug() << "Ok"; }

private:
    TApplication* app;
};

Q_DECLARE_INTERFACE(BankTerminal, "org.QBalance.BankTerminal")

#endif // BANKTERMINAL_H
