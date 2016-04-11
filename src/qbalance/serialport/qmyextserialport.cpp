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
#include <QtCore/QDebug>
#include <QtNetwork/QHostInfo>
#include <QtCore/QBuffer>
#include "../kernel/app.h"
#include "qmyextserialport.h"


TcpClient* QMyExtSerialPort::tcpClient = 0;
BaudRateType QMyExtSerialPort::LineSpeedVal[7] = {BAUD2400, BAUD4800, BAUD9600, BAUD19200, BAUD38400, BAUD57600, BAUD115200};


QMyExtSerialPort::QMyExtSerialPort(const QString& name, QueryMode mode, QObject* parent): QextSerialPort(name, mode, parent)
{
    remote = false;
    outLog = false;
    log = "";
    app = TApplication::exemplar();
    tryReceiveExit = false;
    timeOut = 10000;
}


QMyExtSerialPort::~QMyExtSerialPort()
{
    if (tcpClient != 0)
        tcpClient->deleteLater();
}


bool QMyExtSerialPort::open(OpenMode mode)
{
    setFlowControl(FLOW_OFF);
    setParity(PAR_NONE);
    setDataBits(DATA_8);
    setStopBits(STOP_2);
    bool result = QextSerialPort::open(mode);
    return result;
}


void QMyExtSerialPort::close()
{
    QextSerialPort::close();
}


void QMyExtSerialPort::tryReceive()
{
    QByteArray result = QextSerialPort::readAll();
    if (result.size() > 0)
    {
        for (int i = 0; i < result.size(); i++)
            buffer.enqueue(result.at(i));
    }
    if (!tryReceiveExit)
        QTimer::singleShot(5, this, SLOT(tryReceive()));
}


qint64 QMyExtSerialPort::readData(char* data, qint64 maxSize, bool fromRemote)
{
    qint64 result = -1;
    if (!remote)
    {
        tryReceiveExit = false;                     // Запустим цикл опроса данных в процедуре tryReceive() по таймауту
        app->startTimeOut(timeOut);                    // Ждем ответа в течение ...
        tryReceive();
        while (true)
        {
            if (buffer.size() >= maxSize)
            {
                for (int i = 0; i < maxSize; i++)
                    data[i] = buffer.dequeue();
                result = maxSize;
                break;
            }
            if (app->isTimeOut())
            {
                writeLog(QString("*** ЗАДЕРЖКА свыше %1 сек ***").arg(timeOut/1000));
                break;
            }
            app->sleep(10);
        }
        tryReceiveExit = true;              // Не будем больше постоянно опрашивать COM порт
        appendLog(false, QByteArray(data, maxSize).toHex().data(), fromRemote);
    }
    else if (tcpClient != 0 && tcpClient->isValid() && !fromRemote)
    {
        QString command = QString("=fr=<<%1").arg(maxSize);
        if (tcpClient->sendToServer(command))
        {
            if (tcpClient->waitResult())
            {
                QString res = tcpClient->getResult();
                int pos = res.indexOf("<<");
                result = res.left(pos).toLongLong();
                if (result > 0)
                {
                    QByteArray arr;
                    res.remove(0, pos + 2);
                    arr.append(QByteArray::fromHex(QByteArray().append(res)));
                    memcpy(data, arr.data(), maxSize);
                    appendLog(false, QByteArray(data, maxSize).toHex().data(), fromRemote);
                }
            }
        }
    }
    return result;
}


qint64 QMyExtSerialPort::writeData(const char * data, qint64 maxSize, bool fromRemote)
{
    qint64 result = -1;
    if (!remote)
    {
        result = QextSerialPort::writeData(data, maxSize);
        appendLog(true, QByteArray(data, maxSize).toHex().data(), fromRemote);
    }
    else if (tcpClient != 0 && tcpClient->isValid() && !fromRemote)
    {
        if (tcpClient->sendToServer("=fr=>>" + QString(QByteArray(data, maxSize).toHex().data())))
        {
            if (tcpClient->waitResult())
            {
                QString res = tcpClient->getResult();
                result = res.toLongLong();
                appendLog(true, QByteArray(data, maxSize).toHex().data(), fromRemote);
            }
        }
    }
    return result;
}


bool QMyExtSerialPort::isReadyDriverFR()
{
    bool result = false;
    if (tcpClient != 0 && tcpClient->isValid())
    {
        if (tcpClient->sendToServer("driverFRisReady") && tcpClient->waitResult())
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
    if (remote && tcpClient != 0 && tcpClient->isValid())
    {
        if (tcpClient->sendToServer("isLockedDriverFR") && tcpClient->waitResult())
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
    if (remote && tcpClient != 0 && tcpClient->isValid())
    {
        QString command;
        if (lock)
            command = "setLockDriverFR(true)";
        else
            command = "setLockDriverFR(false)";
        if (tcpClient->sendToServer(command) && tcpClient->waitResult())
        {
            QString res = tcpClient->getResult();
            locked = (res == "Ok" ? true : false);
        }
    }
    return locked;
}


void QMyExtSerialPort::setTcpClient(QString host, int port)
{
    tcpClient = new TcpClient(host, port);
}


void QMyExtSerialPort::appendLog(bool out, QString str, bool fromRemote)
{
    if (out != outLog)           // Журнал был для исходящих команд
    {
        writeLog("", fromRemote);         // Запишем предыдущий журнал
        outLog = out;
    }


    // Удалим лидирующие нули
    while (str.length() > 0)
    {
        if (str.left(2) == "00" && log.size() == 0)
            str.remove(0, 2);
        else
            break;
    }


    while (str.length() > 0)
    {
        QString s = str.left(40) + " ";
        str.remove(0, 40);
        for (int i = s.length() / 2 - 1; i > 0; i--)
            s.insert(i*2, " ");
        log.append(s);
    }
}


void QMyExtSerialPort::writeLog(QString str, bool fromRemote)
{
    if (remote && tcpClient != 0 && tcpClient->isValid())
    {
        tcpClient->sendToServer(QString("=fr=writeLog=%1").arg(str));
    }
    // Если задана строка, то запишем ее в журнал
    if (str.size() > 0)
        app->debug(4, (fromRemote ? "remote " : "") + str);
    else
    {
        if (log.length() > 0)
        {
            if (!outLog)
                app->debug(4, QDateTime::currentDateTime().toString(app->logTimeFormat()) + (fromRemote ? " remote" : "") + " <- " + log, true);
            else
                app->debug(4, QDateTime::currentDateTime().toString(app->logTimeFormat()) + (fromRemote ? " remote" : "") + " -> " + log, true);
        }
        // Очистим журнал
        log = "";
    }
}


void QMyExtSerialPort::closeTcpClient()
{
    delete tcpClient;
    tcpClient = 0;
}
