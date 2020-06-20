/*
  Copyright (c) 2011-2012 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  See the LICENSE file for more details.
*/

#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include <QtCore/QObject>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QTcpSocket>

#include "mimemessage.h"
#include "smtpexports.h"

class SMTP_EXPORT SmtpClient : public QObject
{
    Q_OBJECT
public:

    /* [0] Enumerations */

    enum AuthMethod
    {
        AuthPlain,
        AuthLogin
    };

    enum SmtpError
    {
        ConnectionTimeoutError,
        ResponseTimeoutError,
        SendDataTimeoutError,
        AuthenticationFailedError,
        ServerError,    // 4xx smtp error
        ClientError     // 5xx smtp error
    };

    enum ConnectionType
    {
        TcpConnection,
        SslConnection,
        TlsConnection       // STARTTLS
    };

    /* [0] --- */


    /* [1] Constructors and Destructors */

    SmtpClient(const QString & host = "localhost", int port = 25/*, ConnectionType ct = TcpConnection*/);

    ~SmtpClient();

    /* [1] --- */


    /* [2] Getters and Setters */

    virtual const QString& getHost() const;
    virtual void setHost(const QString &host);

    virtual int getPort() const;
    virtual void setPort(int port);

    virtual const QString& getName() const;
    virtual void setName(const QString &name);

    virtual ConnectionType getConnectionType() const;
    virtual void setConnectionType(ConnectionType ct);

    virtual const QString & getUser() const;
    virtual void setUser(const QString &user);

    virtual const QString & getPassword() const;
    virtual void setPassword(const QString &password);

    virtual SmtpClient::AuthMethod getAuthMethod() const;
    virtual void setAuthMethod(AuthMethod method);

    virtual const QString & getResponseText() const;
    virtual int getResponseCode() const;

    virtual int getConnectionTimeout() const;
    virtual void setConnectionTimeout(int msec);

    virtual int getResponseTimeout() const;
    virtual void setResponseTimeout(int msec);
    
    virtual int getSendMessageTimeout() const;
    virtual void setSendMessageTimeout(int msec);

    virtual QTcpSocket* getSocket();


    /* [2] --- */


    /* [3] Public methods */

    virtual bool connectToHost();

    virtual bool login();
    virtual bool login(const QString &user, const QString &password, AuthMethod method = AuthLogin);

    virtual bool sendMail(MimeMessage& email);

    virtual void quit();


    /* [3] --- */

protected:

    /* [4] Protected members */

    QTcpSocket *socket;

    QString host;
    int port;
    ConnectionType connectionType;
    QString name;

    QString user;
    QString password;
    AuthMethod authMethod;

    int connectionTimeout;
    int responseTimeout;
    int sendMessageTimeout;
    
    
    QString responseText;
    int responseCode;


    class ResponseTimeoutException {};
    class SendMessageTimeoutException {};

    /* [4] --- */


    /* [5] Protected methods */

    virtual void waitForResponse();

    virtual void sendMessage(const QString &text);

    /* [5] --- */

protected slots:

    /* [6] Protected slots */

    virtual void socketStateChanged(QAbstractSocket::SocketState state);
    virtual void socketError(QAbstractSocket::SocketError error);
    virtual void socketReadyRead();

    /* [6] --- */


signals:

    /* [7] Signals */

    virtual void smtpError(SmtpClient::SmtpError e);

    /* [7] --- */

};

#endif // SMTPCLIENT_H
