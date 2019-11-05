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

#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkSession>


class TApplication;

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(const QString& strHost, int nPort, QObject *parent = nullptr);
    virtual bool sendToServer(QString);
    virtual bool isValid();
    virtual QString     getResult();
    virtual bool        waitResult();
    virtual void logError();

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();
    void tryReceive();

private:
    TApplication*   app;
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;
    bool        connected;
    bool        resultReady;
    QString     hostName;
    int         port;

    QString     result;
};

#endif // TCPCLIENT_H
