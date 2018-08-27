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

#ifndef UPDATES_H
#define UPDATES_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtNetwork/QFtp>
#include <QtNetwork/QUrlInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtXml/QDomDocument>


class TApplication;


class Updates : public QObject
{
    Q_OBJECT

private:
    TApplication*       app;
    QString             updatesPath;
    QString             serverBackupXMLFile;
    QNetworkAccessManager*  nwmanager;
    QMap<QString, QFile*> files;

    QStringList    prepareFilesList();
    QStringList         getFilesList();
    qulonglong calculateCRC32(QString);
    QString             osPath;

public:
    Updates(TApplication*, QObject *parent = 0);
    ~Updates();
    bool open();
    void close();
    void putTotalUpdates();
    void putUpdates();

private slots:
    void transmissionFinished(QNetworkReply*);
};

#endif // UPDATES_H
