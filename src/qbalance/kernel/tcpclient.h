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

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkSession>


class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(const QString& strHost, int nPort, QObject *parent = 0);
    QString sendToServer(QString);
    bool isValid() { return connected; }
    QString     getResult() { return result; }
    bool        waitResult();

private slots:
    void slotReadyRead();
    void slotError();
    void slotConnected();

private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;
    bool        connected;
    bool        resultReady;

    QString     result;
};

#endif // TCPCLIENT_H
