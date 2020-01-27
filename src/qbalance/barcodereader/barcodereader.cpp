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
    lastTime = QTime::currentTime();
    isBarCode = false;
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


QString BarCodeReader::getBarCodeString()
{
    return barCodeString;
}


void BarCodeReader::testBarCode(QKeyEvent *event)
{
    QTime   time = QTime::currentTime();

/*
    if (time > lastTime.addMSecs(50))   // Прошло много времени с последнего нажатия, скорее всего это просто нажатие клавиши
    {
        barCodeString = str;            // Начнем читать буфер клавиатуры сначала
        isBarCode = false;              // И будем считать, что это не штрихкод
        qDebug() << "1" << barCodeString;
    }
    else
    {
        barCodeString += str.trimmed();     // Коды нажатий клавиш поступают быстро, будем копить в буфере нажатия
        if (!isBarCode)                     // Запланируем обработку последовательности нажатий как штрихкод
            QTimer::singleShot(timeOut, this, SLOT(barCodeReadyRead()));

        isBarCode = true;                   // Сейчас будем предполагать, что это штрихкод
        qDebug() << "2" << barCodeString;
    }

    lastTime = time;                        // Запомним время последнего нажатия
*/
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
    {
        QString bcString = barCodeString;
        app->barCodeReadyRead(bcString);
    }
}


