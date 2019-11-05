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

#include "emailclient.h"


EMailClient::EMailClient(const QString & host, int port, ConnectionType ct) : SmtpClient(host, port, ct)
{
}


EMailClient::~EMailClient()
{

}


bool EMailClient::open()
{
    return true;
}


void EMailClient::close()
{

}


//int EMailClient::sendMail()
//{

//    SmtpClient* smtp = new SmtpClient("smtp.gmail.com", 465/*, SmtpClient::SslConnection*/);

    // We need to set the username (your email address) and password
    // for smtp authentification.

//    smtp->setUser("ip5540726@gmail.com");
//    smtp->setPassword("mva10031974");

/*
    // Now we create a MimeMessage object. This is the email.

    MimeMessage message;

    EmailAddress sender("ip5540726@gmail.com", "Your Name");
    message.setSender(&sender);

    EmailAddress to("MorozovVladimir@mail.ru", "Recipient's Name");
    message.addRecipient(&to);

    message.setSubject("mailclient for Qt - Demo");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText("Hi,\nThis is a simple email message.\n");

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    if (!smtp->connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
        return -1;
    }

    if (!smtp->login()) {
        qDebug() << "Failed to login!" << endl;
        return -2;
    }

    if (!smtp->sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        return -3;
    }
*/

//    smtp->quit();

/*
    delete smtp;

    return 0;
*/
//}
