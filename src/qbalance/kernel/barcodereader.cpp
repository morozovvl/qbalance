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
#include "../../qextserialport/src/qextserialport.h"
#include "barcodereader.h"
#include "app.h"


BarCodeReader::BarCodeReader(QObject *parent, QString port) :
    QObject(parent)
{

    barCodeReaderComPort = new QextSerialPort(port, QextSerialPort::EventDriven);
    barCodeString = "";

    if (barCodeReaderComPort != 0)
    {
        barCodeReaderComPort->setBaudRate(BAUD9600);
        barCodeReaderComPort->setFlowControl(FLOW_OFF);
        barCodeReaderComPort->setParity(PAR_NONE);
        barCodeReaderComPort->setDataBits(DATA_8);
        barCodeReaderComPort->setStopBits(STOP_2);
        if (barCodeReaderComPort->open(QIODevice::ReadWrite))
            connect(barCodeReaderComPort, SIGNAL(readyRead()), this, SLOT(barCodeReadyRead()));

    }
}


BarCodeReader::~BarCodeReader()
{
    if (barCodeReaderComPort != 0)
        delete barCodeReaderComPort;
}


void BarCodeReader::barCodeReadyRead()
{
     if (barCodeReaderComPort->bytesAvailable())
     {
         QByteArray array = barCodeReaderComPort->readAll();
         QString readedPart = QString::fromLatin1(array);
         if (readedPart.right(1) == QString('\n'))
         {
             barCodeString.append(readedPart);
             QString bcString = barCodeString;
             barCodeString = "";
             TApplication::exemplar()->barCodeReadyRead(bcString);
         }
         else
             barCodeString.append(readedPart);
     }
}


