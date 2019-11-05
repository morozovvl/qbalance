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

#ifndef EMAILCLIENT_H
#define EMAILCLIENT_H

#include <QtCore/QObject>
#include "../../SMTPEmail/src/SmtpMime"
#include "../../SMTPEmail/src/smtpclient.h"
#include "../../SMTPEmail/src/mimemessage.h"

class EMailClient : public SmtpClient
{
    Q_OBJECT
public:
    explicit EMailClient(const QString & host = "localhost", int port = 25, ConnectionType ct = TcpConnection);
    virtual ~EMailClient();
    virtual bool    open();
    virtual void    close();

signals:

public slots:

};

Q_DECLARE_INTERFACE(EMailClient, "org.QBalance.EMailClient")

#endif // EMAILCLIENT_H
