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
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "updates.h"
#include "app.h"
#include <QDebug>


Updates::Updates(TApplication* a, QObject *parent): QObject(parent)
{
    app = a;
    updatesPath = app->applicationDirPath() + "/";
    serverUpdateXMLFile = "updates.xml";
    nwmanager = new QNetworkAccessManager(app);
#if defined(Q_OS_LINUX)
    osPath = QString("/linux/%1").arg(QSysInfo::WordSize);
#elif defined(Q_OS_WIN)
    osPath = QString("/windows/%1").arg(QSysInfo::WordSize);
#endif
}


Updates::~Updates()
{
    delete nwmanager;
}


bool Updates::open()
{
    bool result = true;
    connect(nwmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transmissionFinished(QNetworkReply*)));
    return result;
}


void Updates::close()
{
    disconnect(nwmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transmissionFinished(QNetworkReply*)));
}


void Updates::putTotalUpdates()
{
    putUpdates(prepareTotalFilesList());
}


void Updates::putUpdates(QStringList filesList)
{
    if (app->getConfigValue("UPDATES_FTP_URL").toString().size() > 0)
    {
        app->print("Запущена выгрузка файлов на сервер FTP");
        foreach (QString fileName, filesList)
        {
            QFile* file = new QFile(app->applicationDirPath() + "/" + fileName);
            if (file->open(QIODevice::ReadOnly))
            {
                QNetworkRequest request = makeNetworkRequest("program" + osPath, fileName);
                nwmanager->put(request, file);
                files.insert(request.url().toString(), fileName);
            }
        }
    }
}


QNetworkRequest Updates::makeNetworkRequest(QString path, QString fileName)
{
    QString urlString = QString("ftp://%1/%2/%3").arg(app->getConfigValue("UPDATES_FTP_URL").toString()).arg(path).arg(fileName);
    QUrl url;
    url.setUrl(urlString);
    url.setUserName(app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT").toString());
    url.setPassword(app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT_PASSWORD").toString());
    url.setPort(21);
    return QNetworkRequest(url);
}


void Updates::getUpdates()
{
    QNetworkRequest request = makeNetworkRequest("program" + osPath, serverUpdateXMLFile);
    nwmanager->get(request);
    files.insert(request.url().toString(), serverUpdateXMLFile);
}


void Updates::transmissionFinished(QNetworkReply* reply)
{
    QString urlString = reply->url().toString();
    // Если это операция выгрузки на сервер
    if (reply->operation() == QNetworkAccessManager::PutOperation)
    {
        if (reply->error() == QNetworkReply::NoError)
            app->print(QString("Выгружен %1").arg(reply->url().toString(QUrl::RemoveScheme | QUrl::RemoveUserInfo | QUrl::RemovePassword | QUrl::RemovePort)));
        else
            app->print(QString("Ошибка(%1) %2").arg(reply->error()).arg(reply->url().toString(QUrl::RemoveScheme | QUrl::RemoveUserInfo | QUrl::RemovePassword | QUrl::RemovePort)));

        if (files.count() == 0)
            app->print("Выгрузка файлов на сервер FTP закончена.");
        else
            files.remove(urlString);
    }
    else if (reply->operation() == QNetworkAccessManager::GetOperation)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QFile file(files.value(urlString));
            if( file.open(QIODevice::WriteOnly) )
            {
                QByteArray content = reply->readAll();
                file.write(content); // пишем в файл
                file.close();

                putUpdates(prepareFilesList());
            }
            files.remove(urlString);
        }
    }
    reply->deleteLater();
}


QStringList Updates::prepareFilesList()
// Подготовить список обновляемых файлов, в которых произошли изменения
{
    QStringList result;
    QDomDocument        filesList;
    QFile* file = new QFile(app->applicationDirPath() + "/" + serverUpdateXMLFile);
    if (file->open(QIODevice::ReadOnly))
    {
        filesList.setContent(file);
        file->close();

        QDomNodeList list = filesList.firstChild().childNodes();
        for (int i = 0; i < list.count(); i++)
        {
            QDomElement element = list.at(i).toElement();
            QFileInfo fi(app->applicationDirPath() + "/" + element.attribute("file"));
            if (fi.isFile())
            {
                if ((QString("%1").arg(fi.size()) != element.attribute("size")) ||
                    (QString("%1").arg(fi.created().date().toString(app->dateFormat())) != element.attribute("date")) ||
                    (QString("%1").arg(fi.created().time().toString()) != element.attribute("time")) ||
                    (QString("%1").arg(calculateCRC32(fi.absoluteFilePath())) != element.attribute("crc32")))
                {
                    result.append(element.attribute("file"));
                    element.setAttribute("size", fi.size());
                    element.setAttribute("date", fi.created().date().toString(app->dateFormat()));
                    element.setAttribute("time", fi.created().time().toString());
                    element.setAttribute("crc32", calculateCRC32(fi.absoluteFilePath()));

                }
            }
        }
    }
    if (result.size() > 0)
    {
        QFile file(app->applicationDirPath() + "/" + serverUpdateXMLFile);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(filesList.toByteArray());
            file.close();
        }
    }
    return result;
}


QStringList Updates::prepareTotalFilesList()
// Подготовить полный список обновляемых файлов
{
    QStringList result;
    QDomDocument        filesList;
    QHash<QString, QString> list;
    // Составим список файлов
#if defined(Q_OS_LINUX)
    #define LIB_EXT "*.so*"
    list.insert("qbalance", "");
#elif defined(Q_OS_WIN)
    #define LIB_EXT "*.dll"
    list.insert("qbalance.exe", "");
#endif
    list.insert(serverUpdateXMLFile, "");
    list.insert("resources.qrc", "");
    list.insert("plugins", LIB_EXT);
    list.insert("plugins/designer", LIB_EXT);
    list.insert("plugins/imageformats", LIB_EXT);
    list.insert("plugins/script", LIB_EXT);
    list.insert("plugins/sqldrivers", LIB_EXT);
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
                QString path = fileName.replace(fi.fileName(), "");
                if (path.size() > 0)
                    path += "/";
                f = filesList.createElement(fName.replace("/", "_"));
                f.setAttribute("path", path);
                f.setAttribute("file", fi.fileName());
                f.setAttribute("size", fi.size());
                f.setAttribute("date", fi.created().date().toString(app->dateFormat()));
                f.setAttribute("time", fi.created().time().toString());
                f.setAttribute("crc32", calculateCRC32(fi.absoluteFilePath()));
                root.appendChild(f);
                if (!result.contains(path + fi.fileName()))
                    result.append(path + fi.fileName());
            }
            else
            {
                foreach (QFileInfo fi, QDir(app->applicationDirPath() + "/" + fileName).entryInfoList(QStringList() << list.value(fileName)))
                {
                    if (fi.isFile())
                    {
                        QString fName = fileName + "/" + fi.fileName();
                        QString path = fileName.replace(fi.fileName(), "");
                        if (path.size() > 0)
                            path += "/";
                        f = filesList.createElement(fName.replace("/", "_"));
                        f.setAttribute("path", path);
                        f.setAttribute("file", fi.fileName());
                        f.setAttribute("size", fi.size());
                        f.setAttribute("date", fi.created().date().toString(app->dateFormat()));
                        f.setAttribute("time", fi.created().time().toString());
                        f.setAttribute("crc32", calculateCRC32(fi.absoluteFilePath()));
                        root.appendChild(f);
                        if (!result.contains(path + fi.fileName()))
                            result.append(path + fi.fileName());
                    }
                }
            }
        }
    }

    QFile file(updatesPath + serverUpdateXMLFile);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(filesList.toByteArray());
        file.close();
    }
    return result;
}


QStringList Updates::getFilesList()
// Составляет список файлов, в которых не сходится описание файлов на сервере и местных файлов
{
    QStringList files;
    QFile file(updatesPath + serverUpdateXMLFile);
    if (file.open(QIODevice::ReadOnly))
    {
        QString errMessage;
        QDomDocument        filesList;
        if (filesList.setContent(&file, true, &errMessage))
        {
            QDomNode n = filesList.documentElement().firstChild();
            while(!n.isNull())
            {
                 QDomElement e = n.toElement();
                 QFileInfo fi(app->applicationDirPath() + "/" + e.attribute("file"));
                 if (fi.isFile() && ((calculateCRC32(fi.absoluteFilePath()) != e.attribute("crc32").toULongLong())))
                 {
                     files.append(e.attribute("file"));
                 }
                 n = n.nextSibling();
            }
        }
        else
            app->print("Ошибка разбора файла описания обновлений");
        file.close();
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
