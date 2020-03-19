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
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtCore/QTimer>
#include <QtXml/QDomDocument>


class TApplication;
class DBFactory;


class Updates : public QObject
{
    Q_OBJECT

private:
    TApplication*           app;                       // Ссылка на основное приложение
    QString                 updatesPath;               // локальный каталог, в который будут загружаться обновления программы
    QString                 updatesDBPath;             // локальный каталог, в который загружаются обновления базы данных
    QString                 programUpdateXMLFile;      // XML файл для хранения списка файлов программы и их атрибутов в том состоянии, в котором они храняться на FTP сервере
    QString                 dbUpdateXMLFile;           // XML файл для хранения списка файлов базы данных (скриптов, форм, шаблонов) и их атрибутов, которые находятся на FTP сервере
    QNetworkAccessManager*  nwmanager;
    QMap<QString, QString>  files;
    QString                 osPath;                    // путь на FTP сервере для хранения соответствующих для данной ОС и ее битности файлов программы
    bool                    isGetUpdates;              // Флаг направления загрузки-выгрузки: если TRUE, то обновления выгружаются с FTP сервера на локальный компьютер
    int                     updatesCount;              // Счетчик загруженных/выгруженных файлов
    QTimer*                 timer;                     // Таймер, который считает время между проверками наличия обновлений
    bool                    updatesDownloaded;         // Если TRUE, то обновления загружены на локальный компьютер

    QHash<QString, QString> getProgramFilesList();      // Функция возвращает список файлов программы, которые необходимо проверять на наличие обновлений
    QHash<QString, QString> getDBFilesList();           // Функция возвращает список файлов базы данных (скриптов, форм, шаблонов), которые необходимо проверить на наличие обновлений
    QStringList         prepareFilesList(QString path, QString configFile, bool = false);           // Просматривает configFile (XML), сверяет с локальными файлами и возвращает список файлов, которые необходимо обновить
    QStringList         prepareTotalFilesList(QString configFile, QHash<QString, QString> list);    // Просматривает список list и по нему проверяет атрибуты файлов (контрольную сумму)
                                                                                                    // Сохраняет информацию в XML файле configFile
    qulonglong          calculateCRC32(QString);        // Подсчитывает контрольную сумму файла
    QNetworkRequest     makeNetworkRequest(QString path, QString fileName);     // Формирует запрос на FTP сервер для загрузки/выгрузки файла fileName
    bool                removeDir(const QString &);                             // Удаляет каталоги с вложенными подкаталогами

public:
    Updates(TApplication*, QObject *parent = 0 /*nullptr*/);
    ~Updates();
    bool    open();
    void    close();
    void    getUpdates(QString localPath, QString srvPath, QStringList filesList);      // Отправляет запрос на сервер FTP для выгрузки файлов в локальный каталог localPath по списку filesList
    void    putTotalUpdates();                                                          // Выгрузка всех обновляемых файлов на FTP сервер
    void    putUpdates(QString, QStringList);                                           // Выгрузка обновляемых файлов на сервер

private slots:
    void transmissionFinished(QNetworkReply*);

public slots:
    void    updateModified(bool = true);
};

#endif // UPDATES_H
