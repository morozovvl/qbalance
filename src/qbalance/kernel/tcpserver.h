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

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QNetworkSession>

class TApplication;

class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer(int nPort, QObject *parent = 0);
    virtual void    pingClient(QString);
    virtual bool    getPingOk();

public slots:
    void    sendToClient(QString, QString);
    void    slotDisconnected();

private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

private slots:
    void    slotNewConnection();
    void    slotReadClient();

private:
    TApplication*   app;
    bool            pingOk;
    QHash<QString, QTcpSocket*>      clients;           // Список обслуживаемых клиентов
    void    sendToClient(QTcpSocket*, QString);
    void    processRequest(QTcpSocket*, QString);

};

#endif // TCPSERVER_H
