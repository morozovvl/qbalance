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
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError()));
    resultReady = false;
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
    resultReady = true;
}


void TcpClient::slotError()
{
    TApplication::exemplar()->showMessageOnStatusBar(tr("Ошибка соединения: %1.").arg(m_pTcpSocket->errorString()));
}


QString TcpClient::sendToServer(QString str)
{
    resultReady = false;                    // Результат запроса еще не готов
    result = "";
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
    m_pTcpSocket->waitForReadyRead(1000);
    return result;
}


void TcpClient::slotConnected()
{
    connected = true;
}


bool    TcpClient::waitResult()
{
    for (int i = 0; i < 200; i++)           // Будем проверять ответ от сервера не дольше 10 сек
    {
        if (resultReady)
            return true;                    // Результат от сервера готов
        TApplication::exemplar()->timeOut(50);
    }
    return false;
}

