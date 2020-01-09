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
#include "barcodereader.h"
#include "../kernel/app.h"


BarCodeReader::BarCodeReader(QObject *parent) :
    QObject(parent)
{
    app = nullptr;
    serialPort = nullptr;
    barCodeString = "";
}


BarCodeReader::~BarCodeReader()
{
}


void BarCodeReader::setApp(TApplication* a)
{
    app = a;
}


bool BarCodeReader::open(QString port, int rate, int to)
{
    bool result = false;
    if (app != nullptr)
    {
        timeOut = to;
        serialPort = app->getSerialPort(port);
        if (serialPort != nullptr)
        {
            serialPort->setBaudRate(rate);
            if (serialPort->open(QIODevice::ReadWrite))
            {
                connect(serialPort, SIGNAL(readyRead()), this, SLOT(barCodeReadyRead()));
            }
            result = true;
        }
    }
    return result;
}


void BarCodeReader::close()
{
    serialPort->close();
    if (serialPort != nullptr)
        delete serialPort;
}


bool BarCodeReader::barCodeReadyRead(QString str)
{
    bool result = false;

    if (str.size() == 0)
    {
        if (serialPort->bytesAvailable())   // Если доступен сканер для COM порта, читаем с него
        {
            QString readedPart;
            do
            {
                readedPart = QString::fromLatin1(serialPort->readAll());
                barCodeString.append(readedPart);
                app->sleep(timeOut);
            } while (serialPort->bytesAvailable());
        }

        if (barCodeString.size() > 0)
        {
            QString bcString = barCodeString;
            barCodeString = "";
            app->barCodeReadyRead(bcString);
            result = true;
        }
    }
    else
    {
        if (str.size() > 1 || barCodeString.size() > 0)
        {
            barCodeString += str.trimmed();
            QTimer::singleShot(timeOut, this, SLOT(barCodeReadyRead()));
            result = true;
        }
    }

    return result;
}


