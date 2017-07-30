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
#include <QtNetwork/QFtp>
#include <QtCore/QFile>
#include <QtXml/QDomDocument>

class TApplication;

typedef struct
{
    QFile*  file;
    QString remoteDir;
    QString remoteDirExists;
    QString remoteFileName;
    QString localFileName;
    bool    download;
} UpdateFileInfo;

class Updates : public QObject
{
    Q_OBJECT

private:
    TApplication*       app;
    QFtp*   ftp;
    QHash<int, UpdateFileInfo>  files;
    QString url;
    QDomDocument        filesList;
    QString             updatesPath;
    QString             serverBackupXMLFile;
    QString             serverBackupPath;
    bool                toUpload;
    bool                updatesFinished;
    bool                noNeedUpload;

    void    prepareFilesList();
    void    analizeFiles();
    QStringList         getFilesList();
    qulonglong calculateCRC32(QString);

public:
    explicit Updates(TApplication*, QObject *parent = 0);
    bool open(QString, bool = false);
    void close();

signals:

public slots:

private slots:
    void testState(int);
    void readUpdates();
    void putUpdates();
    void readFile(QString remoteDir, QString remoteFile, QString localFile);
    void uploadFile(QString, QString);
    void processCommand(int, bool);
};

#endif // UPDATES_H
