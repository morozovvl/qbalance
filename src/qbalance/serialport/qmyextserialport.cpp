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


bool QMyExtSerialPort::logWrite = true;
QString QMyExtSerialPort::log = "";


qint64 QMyExtSerialPort::writeData(const char * data, qint64 maxSize)
{
    if (isOpen())
    {
        if (!logWrite)          // Журнал был для входящих команд
        {
            writeLog();         // Запишем предыдущий журнал
            logWrite = true;    // Теперь будем писать журнал для исходящих команд
        }
        log.append(QByteArray(data).toHex().data());
        qint64 result = QextSerialPort::writeData(data, maxSize);
        return result;
    }
    return -1;
}


qint64 QMyExtSerialPort::readData(char * data, qint64 maxSize)
{
    if (isOpen())
    {
        if (logWrite)           // Журнал был для исходящих команд
        {
            writeLog();         // Запишем предыдущий журнал
            logWrite = false;   // Далее будем писать журнал для входящих команд
        }
        qint64 result = QextSerialPort::readData(data, maxSize);
        log.append(QByteArray(data).toHex().data());
        return result;
    }
    return -1;
}


void QMyExtSerialPort::writeLog(QString str)
{
    // Запишем журнал
    if (str.size() > 0)
        TApplication::debug(4, str);
    else
    {
        if (!logWrite)
            TApplication::debug(4, " <-- " + log);
        else
            TApplication::debug(4, " --> " + log);
        // Очистим журнал
        log = "";
    }
}
