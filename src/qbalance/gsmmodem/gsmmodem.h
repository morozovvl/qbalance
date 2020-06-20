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


#ifndef GSMMODEM_H
#define GSMMODEM_H

#include <QtCore/QObject>
#include "../serialport/qmyextserialport.h"

class TApplication;

class GSMmodem : public QObject
{
    Q_OBJECT
public:
    explicit GSMmodem(QObject *parent = 0 /*nullptr*/);
    ~GSMmodem();
    virtual void setApp(TApplication* a) { app = a; }

    virtual bool open();
    virtual void close();

    virtual void sendSMS(QString, QString);

private:
    TApplication* app;
    QMyExtSerialPort*         serialPort;

    QString processCommand(QString);

};

Q_DECLARE_INTERFACE(GSMmodem, "org.QBalance.GSMmodem")

#endif // GSMMODEM_H
