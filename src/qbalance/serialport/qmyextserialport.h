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

#ifndef QMYEXTSERIALPORT_H
#define QMYEXTSERIALPORT_H

#include <QByteArray>
#include "../../qextserialport/src/qextserialport.h"
#include "../kernel/tcpclient.h"

class QMyExtSerialPort : public QextSerialPort
{
    Q_OBJECT
public:
    QMyExtSerialPort();
    QMyExtSerialPort(QueryMode mode = EventDriven, QObject * parent = 0): QextSerialPort(mode, parent) { ; }
    QMyExtSerialPort(const QString & name, QueryMode mode = EventDriven, QObject * parent = 0): QextSerialPort(name, mode, parent) { ; }
    QMyExtSerialPort(const PortSettings & settings, QueryMode mode = EventDriven, QObject * parent = 0): QextSerialPort(settings, mode, parent) { ; }
    QMyExtSerialPort(const QString & name, const PortSettings & settings, QueryMode mode = EventDriven, QObject * parent = 0): QextSerialPort(name, settings, mode, parent) { ; }
    ~QMyExtSerialPort();

    qint64 writeData(const char *, qint64, bool = false);
    qint64 readData(char *, qint64, bool = false);

    bool    isLockedDriverFR();
    bool    isReadyDriverFR();
    bool    isLocked() { return locked; }
    bool    setLock(bool lock);

    // Работа с TCP соединением
    void setTcpClient(QString, int);
    TcpClient* getTcpClient() { return tcpClient; }
    void closeTcpClient();

    // Работа с журналом
    QString     getLog() { return log; }
    void writeLog(QString = "");
private:
    static bool locked;
    bool outLog;
    QString log;
    static TcpClient* tcpClient;

    void appendLog(bool, QString);
};

#endif // QMYEXTSERIALPORT_H
