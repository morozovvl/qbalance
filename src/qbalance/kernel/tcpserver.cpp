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
#include "../bankterminal/bankterminal.h"


TcpServer::TcpServer(quint16 nPort, QObject *parent ):   QObject(parent)
{
    app = static_cast<TApplication*>(parent);
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


void TcpServer::open()
{
    driverFR = app->getDrvFR();
}


void TcpServer::close()
{
    driverFR = 0;
}


bool TcpServer::getPingOk()
{
    return pingOk;
}


void TcpServer::pingClient(QString host)
{
    pingOk = false;
    sendStringToClient(host, "*ping*");
//    app->startTimeOut(2000);                   // Ждем ответа в течение 2 сек
    QTime dieTime= QTime::currentTime().addMSecs(2000);
    while (QTime::currentTime() < dieTime)
    {
        if (pingOk)
            break;
        app->sleep(10);
    }
}


void TcpServer::sendStringToClient(QString host, QString str)
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
    clients.insert(pClientSocket->peerAddress().toString(), pClientSocket);       // Добавим клиента в список обслуживаемых
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    connect(pClientSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}


void TcpServer::slotDisconnected()
{
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());
    clients.remove(clientSocket->peerAddress().toString());         // Удалим клиента из списка обслуживаемых
    clientSocket->deleteLater();
}


void TcpServer::slotReadClient()
{
    QTcpSocket* pClientSocket = static_cast<QTcpSocket*>(sender());

    if (pClientSocket->isValid())
        processRequest(pClientSocket, QString(pClientSocket->readAll().data()).simplified());
}


void TcpServer::sendToClient(QTcpSocket* pSocket, QString str)
{
    if (pSocket->isValid())
    {
        QString s = QString(str).append("\r\n");
        pSocket->write(s.toAscii().data());
        app->debug(5, QString("To %1: %2").arg(pSocket->peerAddress().toString()).arg(str));
    }
}


void TcpServer::processRequest(QTcpSocket* pClientSocket, QString str)
{
    QString resStr = "Ok";

    app->debug(5, QString("From %1: %2").arg(pClientSocket->peerAddress().toString()).arg(str));

    if (driverFR != 0 /*nullptr*/ && str.left(4) == "=fr=" && app->drvFRisValid())
    {   // Если это запрос работы с фискальным регистратором и фискальный регистратор работает
        int length = str.length() - 4;
        QString lStr = str.right(length);
        QByteArray data;
        if (lStr.left(2) == ">>")   // Если получен запрос на запись данных в ФР
        {
            length -= 2;
            lStr = lStr.right(length);
            data.append(lStr);
            data = data.fromHex(data);
            qint64 result = driverFR->getSerialPort()->writeData(data.data(), data.count(), true);
            resStr = QString("%1").arg(result);
            sendToClient(pClientSocket, resStr);
        }
        else if (lStr.left(2) == "<<")  // Если получен запрос на чтение данных из ФР
        {
            length -= 2;
            lStr = lStr.right(length);
            int count = lStr.toInt();
            data.append(QByteArray(count, ' '));
            qint64 result = driverFR->getSerialPort()->readData(data.data(), count, true);
            if (result == 0)
                data.clear();
            resStr = QString("%1<<%2").arg(result).arg(data.toHex().data());
            sendToClient(pClientSocket, resStr);
        }
        else if (lStr.left(9) == "writeLog=")  // Если получен запрос на запись журнала
        {
            length -= 9;
            lStr = lStr.right(length);
            driverFR->getSerialPort()->writeLog(lStr, true);
            sendToClient(pClientSocket, resStr);
        }
    }
    else if (driverFR != 0 /*nullptr*/ && str.indexOf("driverFRisReady") == 0)
    {
        bool result = false;
        if (driverFR != 0 /*nullptr*/)
            result = driverFR->deviceIsReady();
        resStr = (result ? "true" : "false");
        sendToClient(pClientSocket, resStr);
    }
    else if (driverFR != 0 /*nullptr*/ && str.indexOf("isLockedDriverFR") == 0)
    {
        bool result = false;
        // Если драйвер ФР заблокировал сам клиент
        if (pClientSocket->peerAddress().toString() == driverFR->getLockedByHost())
            result = true;
        else
        {
            if (driverFR != 0 /*nullptr*/)
                result = driverFR->isLocked();
        }
        resStr = (result ? "true" : "false");
        sendToClient(pClientSocket, resStr);
    }
    else if (driverFR != 0 /*nullptr*/ && str.indexOf("setLockDriverFR(true)") == 0)
    {
        driverFR->setLock(true, pClientSocket->peerAddress().toString());
        sendToClient(pClientSocket, resStr);
    }
    else if (driverFR != 0 /*nullptr*/ && str.indexOf("setLockDriverFR(false)") == 0)
    {
        driverFR->setLock(false);
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
    else if (str.indexOf("app.exit") == 0)
    {
        sendToClient(pClientSocket, resStr);
        app->showMessageOnStatusBar("Получена команда завершить приложение. Приложение закроется через 10 секунд...", 10000);
        app->timeOut(10000);
        app->quit();
    }
    else if (str.indexOf("setDebugMode(") == 0)
    {
        str.replace("setDebugMode(", "");
        str.replace(")", "");
        app->setDebugMode(str.toInt());
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf("test") == 0)
    {
        sendToClient(pClientSocket, resStr);
    }
    else if (str.indexOf("*ping*Ok*") == 0)
    {
        pingOk = true;
    }
}

