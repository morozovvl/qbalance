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

#ifndef BARCODEREADER_H
#define BARCODEREADER_H

#include <QObject>
#include "../../qextserialport/src/qextserialport.h"
//#include "../../qextserialport/src/qextserialport_p.h"


class QextSerialPort;

class BarCodeReader : public QObject
{
    Q_OBJECT
public:
    explicit BarCodeReader(QObject *parent = 0);
    ~BarCodeReader();
    
signals:
    
public slots:
    void                    barCodeReadyRead();

private:
    QextSerialPort*         barCodeReaderComPort;
    QString                 barCodeString;
};

#endif // BARCODEREADER_H
