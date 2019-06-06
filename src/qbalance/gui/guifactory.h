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

#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QMessageBox>
    #include <QtGui/QErrorMessage>
    #include <QtGui/QDesktopWidget>
#else
    #include <QtWidgets/QMessageBox>
    #include <QtWidgets/QErrorMessage>
    #include <QtWidgets/QDesktopWidget>
#endif

#include <QtCore/QString>

class MainWindow;
class DBFactory;
class TApplication;

struct UserInfo;

class GUIFactory: public QObject {
    Q_OBJECT
public:
    GUIFactory();
    MainWindow* getMainWindow();
    QString getLastDbName();
    QString getLastHostName();
    int getLastPort();
    int openDB();
    void closeDB();
    void setPeriod();
    void setWindowTitle(QString);
    void show();
    void showMenus();
    int showError(QString);             // Сообщить пользователю об ошибке и вернуть его реакцию
    int showMessage(QString message, QString question = "",
                    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::StandardButton defButton = QMessageBox::No);      // Вывести сообщение пользователю и возможно задать вопрос
    int showYesNo(QString);
    virtual bool open();
    virtual void close();
private:
    DBFactory* db;
    MainWindow* mainWindow;
    QString lastHostName;
    QString lastDbName;
    int lastPort;
    TApplication* app;
};

#endif // GUIFACTORY_H
