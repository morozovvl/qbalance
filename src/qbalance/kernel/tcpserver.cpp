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

#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QTcpSocket>
#include "tcpserver.h"
#include "app.h"
#include "../driverfr/driverfr.h"
#include "../bankterminal/bankterminal.h"


TcpServer::TcpServer(int nPort, QObject *parent /* = 0*/):   QObject(parent)
{
    app = (TApplication*)parent;
    m_nNextBlockSize = 0;
    pingOk = false;
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        app->debug(5, QString(tr("Не запускается TcpServer: %1.\n")).arg(m_ptcpServer->errorString()));
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}


bool TcpServer::getPingOk()
{
    return pingOk;
}


void TcpServer::pingClient(QString host)
{
    pingOk = false;
    sendToClient(host, "*ping*");
    app->startTimeOut(2000);                   // Ждем ответа в течение 2 сек
    while (!app->isTimeOut())
    {
        slotReadClient();
        if (pingOk)
            break;
        app->sleep(10);
    }
}


void TcpServer::sendToClient(QString host, QString str)
{
    if (clients.contains(host))                     // Если клиент находится в списке обслуживаемых
    {
        if (clients.value(host)->isValid())         // и слот рабочий
            sendToClient(clients.value(host), str);
    }
}


void TcpServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}


void TcpServer::slotDisconnected()
{
    QTcpSocket* clientSocket = ((QTcpSocket*)sender());
    clients.remove(clientSocket->peerAddress().toString());         // Удалим клиента из списка обслуживаемых
    clientSocket->deleteLater();
}


void TcpServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_0);
    clients.insert(pClientSocket->peerAddress().toString(), pClientSocket);       // Добавим клиента в список обслуживаемых
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
    app->debug(5, QString("To %1: %2").arg(pSocket->peerAddress().toString()).arg(str));
}


void TcpServer::processRequest(QTcpSocket* pClientSocket, QString str)
{
    QString resStr;
    app->debug(5, QString("From %1: %2").arg(pClientSocket->peerAddress().toString()).arg(str));
    if (str.left(4) == "=fr=" && app->drvFRisValid())
    {   // Если это запрос работы с фискальным регистратором и фискальный регистратор работает
        int length = str.length() - 4;
        QString lStr = str.right(length);
        QByteArray data;
        QMyExtSerialPort* serialPort = app->getDrvFR()->getSerialPort();
        if (lStr.left(2) == ">>")   // Если получен запрос на запись данных в ФР
        {
            length -= 2;
            lStr = lStr.right(length);
            data.append(lStr);
            data = data.fromHex(data);
            qint64 result = serialPort->writeData(data.data(), data.count(), true);
            resStr = QString("%1").arg(result);
            sendToClient(pClientSocket, resStr);
        }
        else if (lStr.left(2) == "<<")  // Если получен запрос на чтение данных из ФР
        {
            length -= 2;
            lStr = lStr.right(length);
            int count = lStr.toInt();
            data.append(QByteArray(count, ' '));
            qint64 result = serialPort->readData(data.data(), count, true);
            if (result == 0)
                data.clear();
            resStr = QString("%1<<%2").arg(result).arg(data.toHex().data());
            sendToClient(pClientSocket, resStr);
        }
        else if (lStr.left(9) == "writeLog=")  // Если получен запрос на запись журнала
        {
            length -= 9;
            lStr = lStr.right(length);
            serialPort->writeLog(lStr, true);
            resStr = "Ok";
            sendToClient(pClientSocket, resStr);
        }
    }
    else if (str.indexOf("driverFRisReady") == 0)
    {
        bool result = app->getDrvFR()->deviceIsReady();
        resStr = (result ? "true" : "false");
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf(BANK_TERMINAL_PREFIX) == 0)
    {
        if (str.indexOf(BANK_TERMINAL_IS_READY) == 0)
        {
            bool result = app->bankTerminalIsValid();
            resStr = (result ? "true" : "false");
        }
        else
            resStr = app->getBankTerminal()->processRemoteQuery(str);
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf("isLockedDriverFR") == 0)
    {
        bool result = false;
        // Если драйвер ФР заблокировал сам клиент
        if (pClientSocket->peerAddress().toString() == app->getDrvFR()->getLockedByHost())
            result = true;
        else
            result = app->getDrvFR()->isLocked();
        resStr = (result ? "true" : "false");
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf("setLockDriverFR(true)") == 0)
    {
        app->getDrvFR()->setLock(true, pClientSocket->peerAddress().toString());
        resStr = "Ok";
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf("setLockDriverFR(false)") == 0)
    {
        app->getDrvFR()->setLock(false);
        resStr = "Ok";
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf("app.exit") == 0)
    {
        resStr = "Ok";
        sendToClient(pClientSocket, resStr);
        app->showMessageOnStatusBar("Получена команда завершить приложение. Приложение закроется через 10 секунд...", 10000);
        app->timeOut(10000);
        app->quit();
    }
    else if (str.indexOf("*ping*Ok*") == 0)
    {
        pingOk = true;
    }
    else if (str.indexOf("setDebugMode(") == 0)
    {
        str.replace("setDebugMode(", "");
        str.replace(")", "");
        app->setDebugMode(str);
        resStr = "Ok";
        sendToClient(pClientSocket, resStr);
    }
}

