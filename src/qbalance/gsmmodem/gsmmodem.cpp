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

#include <QtCore/QTextCodec>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include "gsmmodem.h"
#include "../kernel/app.h"
#include "../kernel/tcpclient.h"



GSMmodem::GSMmodem(QObject *parent) :  QObject(parent)
{
    app = 0 /*nullptr*/;
    serialPort = 0 /*nullptr*/;
    remote = false;
}


GSMmodem::~GSMmodem()
{

}


bool GSMmodem::open()
{
    bool result = false;

    if (app->getConfigValue("GSMMODEM_USE_REMOTE").toBool())
    {
        TcpClient* tcpClient = app->getTcpClient();

        // а теперь поищем на удаленном, если TcpClient исправен
        if (tcpClient != 0 /*nullptr*/)
        {
            if (tcpClient->sendToServer(GSMMODEM_IS_READY,
                                        app->getConfigValue("GSMMODEM_REMOTE_HOST", "").toString(),
                                        app->getConfigValue("GSMMODEM_REMOTE_PORT", 0).toInt(),
                                        app->getConfigValue("GSMMODEM_MAX_TIMEOUT", 0).toInt())
                    && tcpClient->waitResult())
            {
                QString res = tcpClient->getResult();
                result = (res == "true" ? true : false);
                if (result)
                    remote = true;
            }
        }
    }
    else
    {
        serialPort = app->getSerialPort(app->getConfigValue("GSMMODEM_PORT").toString());
        if (serialPort != 0 /*nullptr*/)
        {
            serialPort->setBaudRate(app->getConfigValue("GSMMODEM_BOUD_RATE").toInt());

#if  defined(Q_OS_LINUX)
                if (serialPort->open(QIODevice::ReadWrite) && serialPort->isOpen())
#elif   defined(Q_OS_WIN)
                if (serialPort->open(QIODevice::ReadWrite | QIODevice::Unbuffered) && serialPort->isOpen())
#endif
                    result = true;
        }
    }
    if (result)
    {
        app->print("Найден GSM модем");
        if (process("ATI").size() == 0)
            app->print("Ответ на запрос от GSM модема не получен");
        app->print(process());
    }
    else
        app->print("GSM модем не найден");

    return result;
}


void GSMmodem::close()
{
    if (serialPort != 0 /*nullptr*/)
    {
        serialPort->close();
        delete serialPort;
    }
}


QString GSMmodem::process(QString comm)
{
    QString result;

    if (!remote)
    {
        int timeOut = app->getConfigValue("GSMMODEM_MAX_TIMEOUT").toInt();
        QByteArray command;
        char r;

        command.append(comm + "\r");
        serialPort->setMyTimeout(timeOut);

        QTime dieTime= QTime::currentTime().addMSecs(timeOut);
        serialPort->writeData(command.data(), command.size());

        while (true)
        {
            serialPort->readData(&r, 1);
            if (QTime::currentTime() >= dieTime)    // Время ожидания вышло, прекратим попытки
            {
                serialPort->writeLog(QString("Result:%1. Истек таймаут %2 мс").arg(result).arg(timeOut));
                break;
            }
            if (r == '\r' || r == '\n')
            {
                if (result.size() > 0)
                    break;
            }
            else
                result.append(QString(r));
        }
    }
    else
    {
        TcpClient* tcpClient = app->getTcpClient();

        // а теперь поищем на удаленном, если указан его IP
        if (tcpClient != 0 /*nullptr*/)
        {
            tcpClient->sendToServer(QString("%1 %2 ").arg(GSMMODEM_PROCESS).arg(comm),
                                    app->getConfigValue("GSMMODEM_REMOTE_HOST", "").toString(),
                                    app->getConfigValue("GSMMODEM_REMOTE_PORT", 0).toInt(),
                                    app->getConfigValue("GSMMODEM_MAX_TIMEOUT", 0).toInt());
            tcpClient->waitResult();
            result = tcpClient->getResult();
        }
    }

    return result.trimmed();
}


QString GSMmodem::sendSMS(QString number, QString message)
{
    QString result = "";
    process("AT+CMGF=1");
    process("AT+CMGS=\"" + app->getConfigValue("GSMMODEM_PREFIX").toString() + number + "\"");
    result = process(message + "\x1A");
    return result;
}


QString GSMmodem::processRemoteQuery(QString command)
{
    QString result = "";

    if (command.indexOf(GSMMODEM_PROCESS) == 0)
    {
        command.remove(GSMMODEM_PROCESS);
        command = command.trimmed();
        result = process(command);
    }
    return result;
}


