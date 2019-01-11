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

#include <QtCore/QByteArray>
#include <QtCore/QQueue>
#include <QtSerialPort/QSerialPort>
#include "../../qextserialport/src/qextserialport.h"

class TApplication;
class TcpClient;


class QMyExtSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    QMyExtSerialPort(const QString & name, QObject * parent = 0);
    ~QMyExtSerialPort();

    virtual bool open(OpenMode mode);
    virtual void close();
    qint64 writeData(const char *, qint64, bool = false);
    virtual qint64 writeData(QString, bool = false);
    virtual qint64 readData(char *, qint64, bool = false);
    virtual QByteArray readAll();

    virtual bool    isLockedDriverFR();
    virtual bool    isReadyDriverFR();
    virtual bool    setLock(bool lock);
    virtual void    setRemote(bool r);
    virtual void    setMyTimeout(int t);
    virtual void    setBaudRate(int rate);
//    virtual void    setTimeout(long timeOut);

    // Работа с TCP соединением
    virtual TcpClient* getTcpClient();

    // Работа с журналом
    virtual QString     getLog();
    virtual void        writeLog(QString = "", bool = false);

private slots:
    void        tryReceive();
private:
    bool                remote;
    bool                outLog;
    QString             log;
    TcpClient*          tcpClient;
    TApplication*       app;
    QQueue<unsigned char> buffer;
    bool                tryReceiveExit;
    int                 timeOut;
    static BaudRateType LineSpeedVal[7];

    void appendLog(bool, QString, bool = false);
};

#endif // QMYEXTSERIALPORT_H
