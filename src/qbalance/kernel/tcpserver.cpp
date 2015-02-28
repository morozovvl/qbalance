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

#include "tcpserver.h"
#include <QNetworkConfigurationManager>
#include "app.h"


TcpServer::TcpServer(int nPort, QObject *parent /* = 0*/):   QObject(parent)
{
    m_nNextBlockSize = 0;
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        TApplication::exemplar()->showMessageOnStatusBar(tr("Не запускается TcpServer: %1.").arg(m_ptcpServer->errorString()));
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}


void TcpServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}


void TcpServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_0);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }

        m_nNextBlockSize = 0;

        QString str;
        in >> str;

        processRequest(pClientSocket, str);
    }
}


void TcpServer::sendToClient(QTcpSocket* pSocket, QString str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    pSocket->write(arrBlock);
}


void    TcpServer::processRequest(QTcpSocket* pClientSocket, QString str)
{
    if (str.left(4) == "=fr=" && TApplication::exemplar()->drvFRisValid())
    {
        int length = str.length() - 4;
        QString lStr = str.right(length);
        QByteArray data;
        QMyExtSerialPort* serialPort = TApplication::exemplar()->getDrvFR()->getSerialPort();
        if (lStr.left(2) == ">>")
        {
            length -= 2;
            lStr = lStr.right(length);
            data.append(lStr);
            data = data.fromHex(data);
            qint64 result = serialPort->writeData(data.data(), data.count(), true);
            sendToClient(pClientSocket, QString("%1").arg(result));
        }
        else if (lStr.left(2) == "<<")
        {
            length -= 2;
            lStr = lStr.right(length);
            data.append(lStr);
            data = data.fromHex(data);
            qint64 result = serialPort->readData(data.data(), data.count(), true);
            sendToClient(pClientSocket, QString("%1<<%2").arg(result).arg(data.toHex().data()));
        }
    }
    else if (str.indexOf("driverFRisReady") == 0)
    {
        bool result = TApplication::exemplar()->getDrvFR()->getSerialPort()->isOpen();
        sendToClient(pClientSocket, (result ? "true" : "false"));
    }
    else if (str.indexOf("getApplicationPID") == 0)
    {
        qint64 pid = TApplication::exemplar()->getApplicationPID();
        sendToClient(pClientSocket, QString("%1").arg(pid));
    }
    else if (str.indexOf("isLockedDriverFR") == 0)
    {
        bool result = TApplication::exemplar()->getDrvFR()->isLocked();
        sendToClient(pClientSocket, (result ? "true" : "false"));
    }
    else if (str.indexOf("setLockDriverFR(true)") == 0)
    {
        bool result = false;
        if (!TApplication::exemplar()->getDrvFR()->isLocked())
            result = true;
        TApplication::exemplar()->getDrvFR()->setLock(true);
        sendToClient(pClientSocket, (result ? "true" : "false"));
    }
    else if (str.indexOf("setLockDriverFR(false)") == 0)
    {
        bool result = true;
        TApplication::exemplar()->getDrvFR()->setLock(false);
        sendToClient(pClientSocket, (result ? "true" : "false"));
    }
}

