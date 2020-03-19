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
    app = 0 /*nullptr*/;
    serialPort = 0 /*nullptr*/;
    barCodeString = "";
    lastTime = QTime::currentTime();
    barCodeSymsEntered = 0;
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
    if (app != 0 /*nullptr*/)
    {
        timeOut = to;
        serialPort = app->getSerialPort(port);
        if (serialPort != 0 /*nullptr*/)
        {
            serialPort->setBaudRate(rate);
            if (serialPort->open(QIODevice::ReadWrite))
            {
                connect(serialPort, SIGNAL(readyRead()), this, SLOT(barCodeReadyRead()));
                result = true;
            }
        }
    }
    return result;
}


void BarCodeReader::close()
{
    serialPort->close();
    if (serialPort != 0 /*nullptr*/)
        delete serialPort;
}


QString BarCodeReader::getBarCodeString()
{
    QString result = barCodeString;
    barCodeString = "";
    return result;
}


bool BarCodeReader::testBarCode(QString str)
{
    bool result = false;
    QTime   time = QTime::currentTime();

    if (time <= lastTime.addMSecs(10) || (str.size() > 1))   // Прошло много времени с последнего нажатия, скорее всего это просто нажатие клавиши
    {
        barCodeString += str.trimmed();     // Коды нажатий клавиш поступают быстро, будем копить в буфере нажатия
        result = true;                   // Сейчас будем предполагать, что это штрихкод
        QTimer::singleShot(50, this, SLOT(testBarCode()));
    }
    else if (barCodeString.size() > 0)
    {
        app->barCodeReadyRead(getBarCodeString());
    }
    lastTime = time;                        // Запомним время последнего нажатия
    return result;
}


void BarCodeReader::barCodeReadyRead()
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
        app->barCodeReadyRead(barCodeString);
}


