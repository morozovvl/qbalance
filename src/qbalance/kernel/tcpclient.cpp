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
#include <QTimer>
#include <QtNetwork/QNetworkConfigurationManager>


TcpClient::TcpClient(const QString& strHost, int nPort, QObject *parent ):   QObject(parent)
{
    app = TApplication::exemplar();
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
    app->debug(5, QString("Устанавливаем соединение с хостом %1 и портом %2.").arg(hostName).arg(port));
    app->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
}


QString TcpClient::getResult()
{
    return result;
}


void TcpClient::slotReadyRead()
{
    resultReady = false;
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
    app->debug(5, QString("From %1: %2").arg(m_pTcpSocket->peerAddress().toString()).arg(result));

    if (result == "*ping*")
    {
        sendToServer("*ping*Ok*");
        result = "";
    }

    if (result.size() > 0)
        resultReady = true;
}


void TcpClient::slotError(QAbstractSocket::SocketError error)
{
    app->debug(5, QString("Ошибка: %1: %2").arg(error).arg(m_pTcpSocket->errorString()));
    app->debug(5, QString("Соединение разорвано"));
    connected = false;
}


bool TcpClient::isValid()
{
    return connected;
}


void TcpClient::logError()
{
    app->debug(5, QString("Cоединение с хостом %1 и портом %2 не установлено.").arg(hostName).arg(port));
    app->debug(5, QString("Ошибка: %1").arg(m_pTcpSocket->errorString()));
    app->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
}


bool TcpClient::sendToServer(QString str)
{
    if (!connected)
    {
        m_pTcpSocket->connectToHost(hostName, port);
        m_pTcpSocket->waitForConnected(app->getConfigValue(MAX_NET_TIMEOUT).toInt());
    }
    resultReady = false;                    // Результат запроса еще не готов
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
    app->debug(5, QString("To %1: %2").arg(m_pTcpSocket->peerAddress().toString()).arg(str));
    return m_pTcpSocket->waitForReadyRead(app->getConfigValue(MAX_NET_TIMEOUT).toInt());      // Будем ждать ответа от сервера в течение 1 сек
}


void TcpClient::slotConnected()
{
    if (m_pTcpSocket->localAddress() != m_pTcpSocket->peerAddress())
    {
        connected = true;
        app->debug(5, "Соединение установлено.");
        app->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
    }
    else
    {
        connected = false;
        app->debug(5, "Не будем создавать соединение, т.к. сервер и клиент находятся на одном хосте");
    }
}


bool    TcpClient::waitResult()
{
//    slotReadyRead();
    bool result = false;
    tryReceive();
//    app->startTimeOut(app->getConfigValue(MAX_NET_TIMEOUT).toInt());                   // Ждем ответа в течение 10 сек
    QTime dieTime= QTime::currentTime().addMSecs(app->getConfigValue(MAX_NET_TIMEOUT).toInt());
    while (true)
    {
        if (resultReady)
        {
            result = true;                    // Результат от сервера готов
            break;
        }
        if (!m_pTcpSocket->isValid())
            break;
        if (QTime::currentTime() >= dieTime)
        {
            app->debug(5, "*** ЗАДЕРЖКА свыше 10 сек ***");
            break;
        }
        app->sleep(100);
    }
    return result;
}


void  TcpClient::tryReceive()
{
    if (resultReady || !m_pTcpSocket->isValid())
        return;                    // Результат от сервера готов
    QTimer::singleShot(5, this, SLOT(tryReceive()));
}
