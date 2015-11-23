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

#include "tcpclient.h"
#include "app.h"
#include <QNetworkConfigurationManager>


TcpClient::TcpClient(const QString& strHost, int nPort, QObject *parent /* = 0*/):   QObject(parent)
{
    m_nNextBlockSize = 0;
    connected = false;
    hostName = strHost;
    port = nPort;
    m_pTcpSocket = new QTcpSocket(this);
    resultReady = false;
    m_pTcpSocket->connectToHost(hostName, port);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
    TApplication::exemplar()->debug(5, QString("Устанавливаем соединение с хостом %1 и портом %2.").arg(hostName).arg(port));
    TApplication::exemplar()->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
}


void TcpClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    for(;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_pTcpSocket->bytesAvailable() < (int)sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        m_nNextBlockSize = 0;

        QString str;
        in >> str;

        result = str;
    }
    TApplication::exemplar()->debug(5, QString("From %1: %2").arg(m_pTcpSocket->peerAddress().toString()).arg(result));

    if (result == "*ping*")
    {
        sendToServer("*ping*Ok*");
        result = "";
    }

    resultReady = true;
}


void TcpClient::slotError(QAbstractSocket::SocketError error)
{
    TApplication::exemplar()->debug(5, QString("Ошибка: %1: %2").arg(error).arg(m_pTcpSocket->errorString()));
    TApplication::exemplar()->debug(5, QString("Соединение разорвано"));
    connected = false;
}


bool TcpClient::isValid()
{
    return connected;
}


void TcpClient::logError()
{
    TApplication::exemplar()->debug(5, QString("Cоединение с хостом %1 и портом %2 не установлено.").arg(hostName).arg(port));
    TApplication::exemplar()->debug(5, QString("Ошибка: %1").arg(m_pTcpSocket->errorString()));
    TApplication::exemplar()->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
}

bool TcpClient::sendToServer(QString str)
{
    if (connected)
    {
        resultReady = false;                    // Результат запроса еще не готов
        QByteArray arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << quint16(0) << str;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        m_pTcpSocket->write(arrBlock);
        TApplication::exemplar()->debug(5, QString("To %1: %2").arg(m_pTcpSocket->peerAddress().toString()).arg(str));
        return m_pTcpSocket->waitForReadyRead(1000);
    }
    return false;
}


void TcpClient::slotConnected()
{
    if (m_pTcpSocket->localAddress() != m_pTcpSocket->peerAddress())
    {
        connected = true;
        TApplication::exemplar()->debug(5, "Соединение установлено.");
        TApplication::exemplar()->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
    }
    else
    {
        connected = false;
        TApplication::exemplar()->debug(5, "Не будем создавать TCP клиент, т.к. TCP сервер находится на этом же хосте");
    }
}


bool    TcpClient::waitResult()
{
    for (int i = 0; i < 10; i++)
    {
        if (resultReady)
            return true;                    // Результат от сервера готов
        TApplication::exemplar()->timeOut(50);
    }
    return false;
}

