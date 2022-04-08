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


TcpClient::TcpClient(const QString& strHost, quint16 nPort, QObject *parent ):   QObject(parent)
{
    app = TApplication::exemplar();
    m_nNextBlockSize = 0;
    connected = false;
    hostName = strHost;
    port = nPort;
    m_pTcpSocket = new QTcpSocket(this);
    resultReady = false;
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
    if (hostName.size() > 0 && port > 0)
    {
        m_pTcpSocket->connectToHost(hostName, port);
        app->debug(5, QString("Устанавливаем соединение с хостом %1 и портом %2.").arg(hostName).arg(port));
        app->debug(5, QString("Статус сокета: %1.").arg(m_pTcpSocket->state()));
    }
}


QString TcpClient::getResult()
{
    return result;
}


void TcpClient::slotReadyRead()
{
    resultReady = false;

    if (m_pTcpSocket->isValid() && m_pTcpSocket->isReadable())
    {
        result = QString(m_pTcpSocket->readAll().data()).simplified();
        app->debug(5, QString("From %1: %2").arg(m_pTcpSocket->peerAddress().toString()).arg(result));

        if (result == "*ping*")
        {
            sendToServer("*ping*Ok*");
            result = "";
        }

        if (result.size() >= 0)
            resultReady = true;
    }
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


bool TcpClient::sendToServer(QString str, QString strHost, quint16 nPort, int timeOut)
{
    QString h = (strHost != "" ? strHost : hostName);
    quint16 p = (nPort > 0 ? nPort : port);
    int t = (timeOut > 0 ? timeOut : app->getConfigValue(MAX_NET_TIMEOUT).toInt());

    if (h.size() > 0 && p > 0)
    {
        if (!connected)
        {
            m_pTcpSocket->connectToHost(h, p);
            m_pTcpSocket->waitForConnected(t);
        }
        resultReady = false;                    // Результат запроса еще не готов

        QString s = QString(str).append("\r\n");
        m_pTcpSocket->write(s.toAscii().data());

        app->debug(5, QString("To %1: %2").arg(m_pTcpSocket->peerAddress().toString()).arg(str));
        return m_pTcpSocket->waitForReadyRead(t);      // Будем ждать ответа от сервера в течение 1 сек
    }
    return false;
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


bool TcpClient::waitResult()
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
            app->debug(5, QString("*** ЗАДЕРЖКА свыше %1 мс ***").arg(app->getConfigValue(MAX_NET_TIMEOUT).toInt()));
            break;
        }
        app->sleep(100);
    }
    return result;
}


void TcpClient::tryReceive()
{
    if (resultReady || !m_pTcpSocket->isValid())
        return;                    // Результат от сервера готов
    QTimer::singleShot(5, this, SLOT(tryReceive()));
}
