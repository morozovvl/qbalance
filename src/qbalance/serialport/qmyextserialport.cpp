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
#include <QDebug>
#include "../kernel/app.h"
#include "qmyextserialport.h"


TcpClient* QMyExtSerialPort::tcpClient = 0;

QMyExtSerialPort::QMyExtSerialPort()
{
    outLog = false;
    log = "";
}


QMyExtSerialPort::~QMyExtSerialPort()
{
    if (tcpClient != 0)
        delete tcpClient;
}


qint64 QMyExtSerialPort::writeData(const char * data, qint64 maxSize, bool fromServer)
{
    qint64 result = -1;
    if (isOpen())
    {
        result = QextSerialPort::writeData(data, maxSize);
        appendLog(true, QByteArray(data, maxSize).toHex().data());
    }
    else if (tcpClient != 0 && tcpClient->isValid() && !fromServer)
    {
        result = tcpClient->sendToServer("=fr=>>" + QString(QByteArray(data, maxSize).toHex().data())).toLongLong();
        if (tcpClient->waitResult())
        {
            QString res = tcpClient->getResult();
            result = res.toLongLong();
            appendLog(true, QByteArray(data, maxSize).toHex().data());
        }
    }
    return result;
}


qint64 QMyExtSerialPort::readData(char * data, qint64 maxSize, bool fromServer)
{
    qint64 result = -1;
    if (isOpen())
    {
        result = QextSerialPort::readData(data, maxSize);
        appendLog(false, QByteArray(data, maxSize).toHex().data());
    }
    else if (tcpClient != 0 && tcpClient->isValid() && !fromServer)
    {
        QByteArray arr;
        arr.fill(' ', maxSize);
        tcpClient->sendToServer("=fr=<<" + QString(arr.toHex().data())).toLongLong();
        if (tcpClient->waitResult())
        {
            QString res = tcpClient->getResult();
            int pos = res.indexOf("<<");
            result = res.left(pos).toLongLong();
            res.remove(0, pos + 2);
            arr = QByteArray::fromHex(QByteArray().append(res));
            strncpy(data, arr.data(), maxSize);
            appendLog(false, QByteArray(data, maxSize).toHex().data());
        }
    }
    return result;
}


bool QMyExtSerialPort::isReadyDriverFR()
{
    bool result = false;
    if (tcpClient != 0 && tcpClient->isValid())
    {
        tcpClient->sendToServer("driverFRisReady");
        if (tcpClient->waitResult())
        {
            QString res = tcpClient->getResult();
            result = (res == "true" ? true : false);
        }
    }
    return result;
}



bool QMyExtSerialPort::isLockedDriverFR()
{
    bool result = false;
    if (!isOpen() && tcpClient != 0 && tcpClient->isValid())
    {
        tcpClient->sendToServer("isLockedDriverFR");
        if (tcpClient->waitResult())
        {
            QString res = tcpClient->getResult();
            result = (res == "true" ? true : false);
        }
    }
    return result;
}


bool QMyExtSerialPort::setLock(bool lock)
{
    bool locked = false;
    if (!isOpen() && tcpClient != 0 && tcpClient->isValid())
    {
        if (lock)
            tcpClient->sendToServer("setLockDriverFR(true)");
        else
            tcpClient->sendToServer("setLockDriverFR(false)");
        if (tcpClient->waitResult())
        {
            QString res = tcpClient->getResult();
            locked = (res == "true" ? true : false);
        }
    }
    return locked;
}


void QMyExtSerialPort::setTcpClient(QString host, int port)
{
    tcpClient = new TcpClient(host, port);
}


void QMyExtSerialPort::appendLog(bool out, QString str)
{
    if (out != outLog)           // Журнал был для исходящих команд
    {
        writeLog();         // Запишем предыдущий журнал
        outLog = out;
    }
    log.append(str);
}


void QMyExtSerialPort::writeLog(QString str)
{
    // Запишем журнал
    if (str.size() > 0)
        TApplication::debug(4, str);
    else
    {
        if (!outLog)
            TApplication::debug(4, " <-- " + log);
        else
            TApplication::debug(4, " --> " + log);
        // Очистим журнал
        log = "";
    }
}


void QMyExtSerialPort::closeTcpClient()
{
    delete tcpClient;
    tcpClient = 0;
}
