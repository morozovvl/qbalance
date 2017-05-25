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
}


void Updates::open(QString u)
{
    url = u;
    if (url.size() > 0)
    {
        ftp = new QFtp(parent());
        ftp->connectToHost(url, 21);
        ftp->login();
        connect(ftp, SIGNAL(stateChanged(int)), this, SLOT(testState(int)));
        connect(ftp, SIGNAL(commandFinished(int, bool)), this, SLOT(processCommand(int, bool)));

        prepareFilesList();
    }
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
        readUpdates();
}


void Updates::readUpdates()
{
    readFile("backup", "/home/vladimir/backup");
}


void Updates::readFile(QString remoteFile, QString localFile)
{
    QFile*  file = new QFile(localFile);
    if (file->open(QFile::WriteOnly))
    {
        int id = ftp->get(remoteFile, file);
        files.insert(id, file);
    }
}


void Updates::processCommand(int id, bool error)
{
    if (!error)
    {
        if (files.contains(id))
        {
            QFile* file = files.value(id);
            file->close();
            files.remove(id);
        }
    }
    else
    {
        app->showMessageOnStatusBar(QObject::trUtf8("Не удалось загрузить обновление программы с сервера FTP"));
    }
}


void Updates::prepareFilesList()
{
    // Составим список файлов
    QStringList list;
    list.append("qbalance");
    list.append("plugins/designer/libplugins.so");
    list.append("plugins/designer/libplugins.so.1");
    list.append("plugins/designer/libplugins.so.1.0");
    list.append("plugins/designer/libplugins.so.1.0.0");

    QDomElement f;
    foreach (QString fileName, list)
    {
        f = filesList.createElement(fileName);
        QFileInfo fi(fileName);
        f.setAttribute("size", fi.size());
        f.setAttribute("date", fi.created().date().toString());
        f.setAttribute("time", fi.created().time().toString());
        filesList.appendChild(f);
    }
    QFile file("/home/vladimir/backup.xml");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(filesList.toByteArray());
    }
    file.close();
}
