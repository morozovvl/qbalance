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


GSMmodem::GSMmodem(QObject *parent) :  QObject(parent)
{
    app = 0 /*nullptr*/;
    serialPort = 0 /*nullptr*/;
}


GSMmodem::~GSMmodem()
{

}


bool GSMmodem::open()
{
    bool result = false;
    serialPort = app->getSerialPort(app->getConfigValue("GSMMODEM_PORT").toString());
    if (serialPort != 0 /*nullptr*/)
    {
        serialPort->setRemote(false);
        serialPort->setBaudRate(app->getConfigValue("GSMMODEM_BOUD_RATE").toInt());

#if  defined(Q_OS_LINUX)
            if (serialPort->open(QIODevice::ReadWrite) && serialPort->isOpen())
#elif   defined(Q_OS_WIN)
            if (serialPort->open(QIODevice::ReadWrite | QIODevice::Unbuffered) && serialPort->isOpen())
#endif
            {
                app->print("Найден GSM модем");
                app->print(processCommand("ATI"));
                result = true;
            }
            else
                app->print("GSM модем не найден");
    }
    return result;
}


void GSMmodem::close()
{
    if (serialPort != 0)
    {
        serialPort->close();
        delete serialPort;
    }
}


QString GSMmodem::processCommand(QString comm)
{
    int timeOut = app->getConfigValue("GSMMODEM_MAX_TIMEOUT").toInt() * 1000;
    QByteArray command;
    QString result;
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
    return result;
}


void GSMmodem::sendSMS(QString number, QString message)
{
    processCommand("AT+CMGF=1");
    processCommand("AT+CMGS=\"" + app->getConfigValue("GSMMODEM_PREFIX").toString() + number + "\"");
    processCommand(message + "\x1A");
}
