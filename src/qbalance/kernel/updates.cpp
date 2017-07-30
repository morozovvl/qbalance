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

#include "updates.h"
#include "app.h"
#include <QDebug>


Updates::Updates(TApplication* a, QObject *parent): QObject(parent)
{
    ftp = 0;
    app = a;
    updatesPath = app->getUpdatesPath();
    serverBackupPath = QString("/%1/%2/%3").arg(app->applicationName()).arg(app->OSType()).arg(app->applicationVersion());
    serverBackupXMLFile = "/backup.xml";
    toUpload = true;
    updatesFinished = false;
    noNeedUpload = false;
}


bool Updates::open(QString u, bool upload)
{
    bool result = false;
    url = u;
    if (url.size() > 0)
    {
        result = true;
        toUpload = upload;
        ftp = new QFtp(parent());
        ftp->connectToHost(url);
        ftp->login("ftpclient", "123");
        connect(ftp, SIGNAL(stateChanged(int)), this, SLOT(testState(int)));
        connect(ftp, SIGNAL(commandFinished(int, bool)), this, SLOT(processCommand(int, bool)));
    }
    return result;
}


void Updates::close()
{
    if (url.size() > 0)
    {
        disconnect(ftp, SIGNAL(commandFinished(int, bool)), this, SLOT(processCommand(int, bool)));
        disconnect(ftp, SIGNAL(stateChanged(int)), this, SLOT(testState(int)));
        ftp->close();
        delete ftp;
    }
}


void Updates::testState(int state)
{
    if (state == QFtp::LoggedIn)
    {
        if (toUpload)
            putUpdates();
        else
            readUpdates();
    }
}


void Updates::readUpdates()
{
    readFile(serverBackupPath, serverBackupXMLFile, updatesPath + serverBackupXMLFile);
}


void Updates::putUpdates()
{
    if (!QDir().exists(updatesPath + serverBackupXMLFile))
        readFile(serverBackupPath, serverBackupXMLFile, updatesPath + serverBackupXMLFile);
    else
        analizeFiles();
}


void Updates::readFile(QString remoteDir, QString remoteFile, QString localFile)
{
//    QDir().remove(localFile);
    QFile* file = new QFile(localFile);
    if (file->open(QFile::WriteOnly))
    {
        int id = ftp->get(remoteFile, file);
        qDebug() << id << localFile << "started";
        UpdateFileInfo fi;
        fi.file = file;
        fi.remoteDir = remoteDir;
        fi.remoteFileName = remoteFile;
        fi.localFileName = localFile;
        fi.download = true;

        files.insert(id, fi);
    }
}


void Updates::uploadFile(QString remoteFile, QString localFile)
{
    QFile* file = new QFile(localFile);
    if (file->open(QFile::ReadOnly))
    {
        int id = ftp->put(file, remoteFile);

        UpdateFileInfo fi;
        fi.file = file;
        fi.remoteFileName = remoteFile;
        fi.localFileName = localFile;
        fi.download = false;

        files.insert(id, fi);
    }
}


void Updates::processCommand(int id, bool error)
{
//    if (!error)
//    {
        qDebug() << id << files.value(id).localFileName << "completed";
        if (files.contains(id))
        {
            QFile* file = files.value(id).file;
            file->close();
            delete file;
            if (QFileInfo(files.value(id).localFileName).size() == 0)
                QDir().remove(files.value(id).localFileName);
            else
            {
                QString message;
                if (files.value(id).download)
                    message += QString(QString(QObject::trUtf8("Загружено с FTP сервера ")));
                else
                    message += QString(QString(QObject::trUtf8("Выгружено на FTP сервер ")));
                message += QString(QString(QObject::trUtf8("обновление файла: %1")).arg(files.value(id).remoteFileName));
//            app->showMessageOnStatusBar(message);
                app->print(message);
            }

            files.remove(id);
        }
        if (files.count() == 0)     // Все обновления загружены
        {
            if (updatesFinished)
            {
                if (!noNeedUpload)
                {
                    if (toUpload)
                    {
                        if (!QDir().exists(updatesPath + serverBackupXMLFile))
                            prepareFilesList();
                        else
                            app->showMessage("Завершена выгрузка обновлений");
                    }
                    else
                        app->showMessage("Завершена загрузка обновлений");
                }
            }
            analizeFiles();
        }
/*
    }
    else
    {
//        app->showMessageOnStatusBar(QObject::trUtf8("Не удалось загрузить обновление программы с сервера FTP"));
        files.clear();
    }
*/
}


void Updates::prepareFilesList()
{
    // Составим список файлов
    filesList.clear();
    QHash<QString, QString> list;
    list.insert("qbalance", "");
    list.insert("recources.qrc", "");
    list.insert("plugins", "*.so*");
    list.insert("plugins/designer", "*.so*");
    list.insert("plugins/imageformats", "*.so*");
    list.insert("plugins/script", "*.so*");
    list.insert("plugins/sqldrivers", "*.so*");
    list.insert("resources", "*.*");
    QDomElement f;
    QDomElement root = filesList.createElement("root");
    filesList.appendChild(root);
    foreach (QString fileName, list.keys())
    {
        if (QDir(app->applicationDirPath()).exists(fileName))
        {
            QFileInfo fi(app->applicationDirPath() + "/" + fileName);
            if (fi.isFile())
            {
                QString fName = fileName;
                f = filesList.createElement(fName.replace("/", "_"));
                f.setAttribute("file", fileName);
                f.setAttribute("size", fi.size());
                f.setAttribute("date", fi.created().date().toString("dd.MM.yyyy"));
                f.setAttribute("time", fi.created().time().toString());
                f.setAttribute("crc32", calculateCRC32(fi.absoluteFilePath()));
                root.appendChild(f);
            }
            else
            {
                foreach (QFileInfo fi, QDir(app->applicationDirPath() + "/" + fileName).entryInfoList(QStringList() << list.value(fileName)))
                {
                    if (fi.isFile())
                    {
                        QString fName = fileName + "/" + fi.fileName();
                        QString fName1 = fName;
                        f = filesList.createElement(fName.replace("/", "_"));
                        f.setAttribute("file", fName1);
                        f.setAttribute("size", fi.size());
                        f.setAttribute("date", fi.created().date().toString("dd.MM.yyyy"));
                        f.setAttribute("time", fi.created().time().toString());
                        f.setAttribute("crc32", calculateCRC32(fi.absoluteFilePath()));
                        root.appendChild(f);
                    }
                }
            }
        }
    }
    QFile file(updatesPath + serverBackupXMLFile);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(filesList.toByteArray());
        file.close();
    }
}


void Updates::analizeFiles()
{
//    if (!updatesFinished)
//    {
        QStringList filesList = getFilesList();
        if (toUpload)
        {
            if (filesList.size() > 0)
            {
                foreach (QString file, filesList)
                {
                    uploadFile(serverBackupPath + "/" + file, app->applicationDirPath() + "/" + file);
                }
                uploadFile(serverBackupPath + serverBackupXMLFile, updatesPath + serverBackupXMLFile);
            }
            else if (!QDir().exists(updatesPath + serverBackupXMLFile))
            {
                uploadFile(serverBackupPath + serverBackupXMLFile, updatesPath + serverBackupXMLFile);
            }
            else
                noNeedUpload = true;

        }
        else
        {
            if (filesList.size() > 0)
            {
                foreach (QString file, filesList)
                {
                    readFile(serverBackupPath, "/" + file, updatesPath + "/" + file);
                }
            }
            else
                noNeedUpload = true;
        }
        updatesFinished = true;
//    }
}


QStringList Updates::getFilesList()
{
    QStringList files;
    QFile file(updatesPath + serverBackupXMLFile);
    if (file.open(QIODevice::ReadOnly))
    {
        QString errMessage;
        if (filesList.setContent(&file, true, &errMessage))
        {
            file.close();
            QDomNode n = filesList.documentElement().firstChild();
            while(!n.isNull())
            {
                 QDomElement e = n.toElement();
                 QFileInfo fi(app->applicationDirPath() + "/" + e.attribute("file"));
                 if (fi.isFile() && ((calculateCRC32(fi.absoluteFilePath()) != e.attribute("crc32").toULongLong()) || (noNeedUpload == false)))
                 {
                     files.append(e.attribute("file"));
                 }
                 n = n.nextSibling();
            }
        }
        else
            qDebug() << errMessage;
    }
    return files;
}


qulonglong Updates::calculateCRC32(QString fileName)
{
    qulonglong result = 0;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        result = app->calculateCRC32(&data);
        file.close();
    }
    return result;
}
