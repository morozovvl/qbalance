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
#include <QtNetwork/QAbstractNetworkCache>
#include "updates.h"
#include "app.h"
#include "../storage/dbfactory.h"
#include "dictionary.h"


Updates::Updates(TApplication* a, QObject *parent): QObject(parent)
{
    app = a;
    updatesDownloaded = false;
    updatesPath = "updates";
    programUpdateXMLFile = "updates.xml";
    updatesDBPath = "updates_db/" + app->getDBFactory()->getDatabaseName();
    dbUpdateXMLFile = "updates_db.xml";
    nwmanager = new QNetworkAccessManager();

    // Для правильного обновления программы необходимо различать операционную систему и ее битность
#if defined(Q_OS_LINUX)
    osPath = QString("/linux/%1/").arg(QSysInfo::WordSize);
#elif defined(Q_OS_WIN)
    osPath = QString("/windows/%1/").arg(QSysInfo::WordSize);
#endif

    isGetUpdates = false;
    updatesCount = 0;
    timer = nullptr;
    if (app->getConfigValue("UPDATES_FTP_TIMEOUT").toInt() > 0)     // Если задан период проверки на наличие обновлений
    {
        timer = new QTimer(this);
        timer->setSingleShot(false);
        timer->start(app->getConfigValue("UPDATES_FTP_TIMEOUT").toInt() * 60000);   // Период проверки задан в минутах
        connect(timer, SIGNAL(timeout()), this, SLOT(updateModified()));            // Будем периодически по таймеру проверять обновления
    }
}


Updates::~Updates()
{
    if (timer != nullptr)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(updateModified()));
        delete timer;
    }
    nwmanager->deleteLater();
}


bool Updates::open()
{
    bool result = true;
    connect(nwmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transmissionFinished(QNetworkReply*)));

    // Если задан период проверки обновлений, то сразу же после запуска программы проверим их
    if (app->getConfigValue("UPDATES_FTP_TIMEOUT").toInt() > 0)
        updateModified();
    return result;
}


void Updates::close()
{
    disconnect(nwmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transmissionFinished(QNetworkReply*)));
    nwmanager->deleteLater();
}


QHash<QString, QString> Updates::getProgramFilesList()
{
    QHash<QString, QString> list;

    // Составим список файлов программы, которые нужно обновлять вообще
    list.insert(programUpdateXMLFile, "");
    #if defined(Q_OS_LINUX)
        #define LIB_EXT "*.so*"
        list.insert(app->applicationName(), "");
    #elif defined(Q_OS_WIN)
        #define LIB_EXT "*.dll"
        list.insert(app->applicationName() + ".exe", "");
    #endif
    list.insert("resources.qrc", "");
    list.insert("plugins", LIB_EXT);
    list.insert("plugins/designer", LIB_EXT);
    list.insert("resources", "*.*");

    return list;
}


QHash<QString, QString> Updates::getDBFilesList()
{
    QHash<QString, QString> list;

    list.insert(updatesDBPath + "/" + dbUpdateXMLFile, "");
    list.insert(updatesDBPath, "*.sql");
/*
    list.insert(updatesDBPath, "*.js");
    list.insert(updatesDBPath, "*.qs");
    list.insert(updatesDBPath, "*.ui");
    list.insert(updatesDBPath, "*.ods");
*/
    return list;
}


void Updates::putTotalUpdates()
{
    if (app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT_PASSWORD").toString().size() > 0)
    {
        app->print("");
        app->print("Запущена выгрузка всех файлов на сервер FTP");

        // Выгрузим все обновления программы
//        if (app->getConfigValue("UPDATES_FTP_PROGRAM").toBool())
//            putUpdates("program" + osPath, prepareTotalFilesList(programUpdateXMLFile, getProgramFilesList()));

        // Выгрузим все обновления базы данных
        if (app->getConfigValue("UPDATES_FTP_DB").toBool())
        {
            // Сохраним все скрипты, формы и шаблоны отчетов
            Dictionary* dict = app->getDictionary("файлы");
            dict->setFieldsList(QStringList() << "КОД" << "ИМЯ" << "ТИП");
            dict->query();
            for (int i = 0; i < dict->rowCount(); i++)
            {
                QString fileName = dict->getValue("ИМЯ", i).toString();
                if (fileName.size() > 0)
                {
                    QByteArray templateFile = app->getDBFactory()->getFile(fileName, dict->getValue("ТИП", i).toInt());
                    app->saveFile(app->getPath(fileName, dict->getValue("ТИП", i).toInt(), updatesDBPath), &templateFile);

                    app->print("Копирование " + fileName);
                }
            }
//            putUpdates("", prepareTotalFilesList(updatesDBPath + "/" + dbUpdateXMLFile, getDBFilesList()));
        }
    }
}


void Updates::getUpdates(QString localPath, QString srvPath, QStringList filesList)
{
    if (app->getConfigValue("UPDATES_FTP_URL").toString().size() > 0)
    {
        foreach (QString fileName, filesList)
        {
            QNetworkRequest request = makeNetworkRequest(srvPath, fileName);
            nwmanager->get(request);
            files.insert(request.url().toString(), localPath + "/" + fileName);
        }
    }
}


void Updates::putUpdates(QString path, QStringList filesList)
{
    if (app->getConfigValue("UPDATES_FTP_URL").toString().size() > 0)
    {
        isGetUpdates = false;
        foreach (QString fileName, filesList)
        {
            QFile* file = new QFile(app->applicationDataDirPath() + "/" + fileName);
            if (file->open(QIODevice::ReadOnly))
            {
                QNetworkRequest request = makeNetworkRequest(path, fileName);
                nwmanager->put(request, file);
                files.insert(request.url().toString(), fileName);
            }
        }
    }
}


QNetworkRequest Updates::makeNetworkRequest(QString path, QString fileName)
{
    QString urlString = QString("ftp://%1/%2%3").arg(app->getConfigValue("UPDATES_FTP_URL").toString()).arg(path).arg(fileName);
    QUrl url;
    url.setUrl(urlString);
    if (isGetUpdates)       // Если получаем обновления, то получаем их как обычный пользователь
    {
        url.setUserName(app->getConfigValue("UPDATES_FTP_CLIENT").toString());
        url.setPassword(app->getConfigValue("UPDATES_FTP_CLIENT_PASSWORD").toString());
    }
    else                    // Если выгружаем обновления на сервер, то устанавливаем соответствующий логин и пароль
    {
        url.setUserName(app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT").toString());
        url.setPassword(app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT_PASSWORD").toString());
    }
    url.setPort(app->getConfigValue("UPDATES_FTP_PORT").toInt());
    return QNetworkRequest(url);
}


void Updates::updateModified(bool getUpdates)
// getUpdates:
// true - загрузка с сервера
// false - выгрузка на сервер
{
    QNetworkRequest request;

    isGetUpdates = getUpdates;

    if (isGetUpdates)
    {
        // Если есть пароль администратора FTP сервера и загрузка обновлений еще не произведена
        if (app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT_PASSWORD").toString().size() == 0 && !updatesDownloaded)
        {
            removeDir(app->applicationDataDirPath() + "/" + updatesPath);
            updatesCount = 0;

            request = makeNetworkRequest("program" + osPath, programUpdateXMLFile);
            nwmanager->get(request);
            files.insert(request.url().toString(), programUpdateXMLFile);

            if (app->isSA())    // Обновления базы данных загружаем только в случае, если мы под учеткой SA
            {
                request = makeNetworkRequest(updatesDBPath + "/", dbUpdateXMLFile);
                nwmanager->get(request);
                files.insert(request.url().toString(), updatesDBPath + "/" + dbUpdateXMLFile);
            }
        }
    }
    else
    {
        if (app->getConfigValue("UPDATES_FTP_ADMIN_CLIENT_PASSWORD").toString().size() > 0)
        {
            app->print("");
            app->print("Запущена выгрузка обновленных файлов на сервер FTP");

            if (app->getConfigValue("UPDATES_FTP_PROGRAM").toBool())
            {
                request = makeNetworkRequest("program" + osPath, programUpdateXMLFile);
                nwmanager->get(request);
                files.insert(request.url().toString(), programUpdateXMLFile);
            }

            if (app->getConfigValue("UPDATES_FTP_DB").toBool())
            {
                request = makeNetworkRequest(updatesDBPath + "/", dbUpdateXMLFile);
                nwmanager->get(request);
                files.insert(request.url().toString(), updatesDBPath + "/" + dbUpdateXMLFile);
            }
        }
    }
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
        {
//            app->print(QString("Ошибка (%1) %2").arg(reply->error()).arg(reply->url().toString()));
            app->print(QString("Ошибка (%1) %2").arg(reply->error()).arg(reply->url().toString(QUrl::RemoveScheme | QUrl::RemoveUserInfo | QUrl::RemovePassword | QUrl::RemovePort)));
        }

        files.remove(urlString);

        if (files.count() == 0)
            app->print("Выгрузка файлов на сервер FTP закончена.");
    }
    else if (reply->operation() == QNetworkAccessManager::GetOperation)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QString fileName = app->applicationDataDirPath() + "/" + files.value(urlString);
            QDir().mkpath(QFileInfo(fileName).absolutePath());
            QFile file(fileName);
            if( file.open(QIODevice::WriteOnly) )
            {
                QByteArray content = reply->readAll();
                file.write(content); // пишем в файл
                file.close();
            }

            files.remove(urlString);

            // Обработку загрузок начнем только если все файлы загружены
            if (files.count() == 0)
            {
                // Составим список файлов, которые нужно загрузить или выгрузить
                QStringList filesList = prepareFilesList("", programUpdateXMLFile);
                if (filesList.count() > 0)
                {
                    // Загрузим обновления
                    if (isGetUpdates)
                    {
                        updatesCount += filesList.count();  // Подсчитаем количество обновленных файлов
                        getUpdates(updatesPath, "program" + osPath, filesList);              // Загрузим обновления
                        app->showMessageOnStatusBar(QString("Найдены обновления файлов программы: %1. Загрузка...").arg(filesList.count()));
                    }
                    else if (app->getConfigValue("UPDATES_FTP_PROGRAM").toBool())
                        // Выгрузим обновления, если разрешено
                    {
                        putUpdates("program" + osPath, filesList);              // Выгрузим обновления на сервер
                    }
                }

                // Добавим список обновлений базы данных, которые нужно загрузить или выгрузить. В том числе те, которых еще нет в списке
                QStringList filesList1 = prepareFilesList(updatesDBPath, dbUpdateXMLFile, true);
                if (filesList1.count() > 0)
                {
                    // Загрузим обновления
                    if (isGetUpdates)
                    {
                        // Уберем те обновления, которые загружать уже не нужно
                        for (int i = 1; i <= app->getConst("Last_DB_Update").toInt(); i++)
                        {
                            filesList1.removeAll(QString("%1/%2.sql").arg(updatesDBPath).arg(i));
                        }

                        updatesCount += filesList1.count();  // Подсчитаем количество обновленных файлов
                        getUpdates("", "", filesList1);              // Загрузим обновления
                        app->showMessageOnStatusBar(QString("Найдены обновления базы данных: %1. Загрузка...").arg(filesList1.count()));
                    }
                    // Выгрузим обновления, если разрешено
                    else if (app->getConfigValue("UPDATES_FTP_DB").toBool())
                    {
                        // Обновим описание файлов
                        prepareTotalFilesList(updatesDBPath + "/" + dbUpdateXMLFile, getDBFilesList());

                        putUpdates("", filesList1);              // Выгрузим обновления на сервер
                    }
                }

                // Если все обновления проверены и загружены, то сообщим об этом пользователю
                if (filesList.count() == 0 && filesList1.count() == 0 && updatesCount > 0)
                {
                    updatesDownloaded = true;
                    app->showMessage(QString("Обновлено файлов - %1. Необходимо перезапустить программу.").arg(updatesCount));
                }
            }
        }
        else
        {
//            app->print(QString("Ошибка (%1) %2").arg(reply->error()).arg(reply->url().toString()));
            app->print(QString("Ошибка (%1) %2").arg(reply->error()).arg(reply->url().toString(QUrl::RemoveScheme | QUrl::RemoveUserInfo | QUrl::RemovePassword | QUrl::RemovePort)));
        }
    }
    reply->close();
    reply->deleteLater();
}


QStringList Updates::prepareFilesList(QString path, QString configFile, bool getUnprocessedFiles)
// Подготовить список обновляемых файлов, в которых произошли изменения
{
    QStringList result;
    QDomDocument filesList;
    QStringList dirFilesList;
    QString     configFileName;

    configFileName.append(app->applicationDirPath() + "/");
    if (path.size() > 0)
        configFileName.append(path + "/");
    configFileName.append(configFile);

    // Сначала составим полный список файлов в каталоге
    foreach (QFileInfo fi, QDir(app->applicationDirPath() + "/" + path).entryInfoList())
    {
        if (fi.isFile() && fi.fileName() != configFile)
        {
            dirFilesList.append(path + "/" + fi.fileName());
        }
    }

    // Перепроверим описание файлов
    QFile file(configFileName);
    if (file.open(QIODevice::ReadOnly))
    {
        filesList.setContent(&file);

        QDomNodeList list = filesList.firstChild().childNodes();
        for (int i = 0; i < list.count(); i++)
        {
            QDomElement element = list.at(i).toElement();
            if (element.attribute("file") != configFile || !isGetUpdates)
            {
                QString fileName = app->applicationDirPath() + "/" + element.attribute("path") + element.attribute("file");
                QFile fi(fileName);
                if (fi.exists())
                {
                    if ((QString("%1").arg(fi.size()) != element.attribute("size")) ||
                        (QString("%1").arg(calculateCRC32(fileName)) != element.attribute("crc32")))
                    {
                        element.setAttribute("size", fi.size());
                        element.setAttribute("crc32", calculateCRC32(fileName));
                        result.append(element.attribute("path") + element.attribute("file"));
                    }
                }
                else
                {
                    result.append(element.attribute("path") + element.attribute("file"));
                }
            }

            // Обработанные файлы исключим из списка
            dirFilesList.removeAll(element.attribute("path") + element.attribute("file"));
        }
        file.close();
    }

    // Сохраним файл списка обновлений
    QFile file1(configFileName);
    if (file1.open(QIODevice::WriteOnly))
    {
        file1.write(filesList.toByteArray());
        file1.close();
    }

    // Если в список включать не обработанные файлы
    if (getUnprocessedFiles)
        result.append(dirFilesList);

    return result;
}


QStringList Updates::prepareTotalFilesList(QString configFile, QHash<QString, QString> list)
// Подготовить полный список обновляемых файлов
{
    QStringList result;
    QDomDocument        filesList;
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
                f = filesList.createElement(fName.replace("/", "_"));
                f.setAttribute("path", path);
                f.setAttribute("file", fi.fileName());
                f.setAttribute("size", fi.size());
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
                        f.setAttribute("crc32", calculateCRC32(fi.absoluteFilePath()));
                        root.appendChild(f);
                        if (!result.contains(path + fi.fileName()))
                            result.append(path + fi.fileName());
                    }
                }
            }
        }
    }

    QFile file(app->applicationDirPath() + "/" + configFile);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(filesList.toByteArray());
        file.close();
    }

    return result;
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


bool Updates::removeDir(const QString & dirName)
{
    bool result = false;
    QDir dir(dirName);

    if (dir.exists())
    {
        foreach (QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if (info.isDir())
                result = removeDir(info.absoluteFilePath());
            else
                result = QFile::remove(info.absoluteFilePath());

            if (!result)
                return result;
        }
        QDir().rmdir(dirName);
    }
    return result;
}


