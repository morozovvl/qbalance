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

#ifndef CARDCODEREADER_H
#define CARDCODEREADER_H

#include <QtCore/QObject>
#include <QtGui/QKeyEvent>
#include "../serialport/qmyextserialport.h"

class CardCodeReader : public QObject
{
    Q_OBJECT
public:
    explicit CardCodeReader(QObject *parent = nullptr);
    virtual bool open();
    virtual void close();
    virtual void setApp(TApplication* a);
    ~CardCodeReader();
    virtual void readCardReader(QKeyEvent*);

    
public slots:

signals:
    void cardCodeReaded(QString);

private:
    TApplication*           app;
    QString                 cardReaderCode;
    QString                 crPrefix;
};

Q_DECLARE_INTERFACE(CardCodeReader, "org.QBalance.CardCodeReader")

#endif // CARDCODEREADER_H
