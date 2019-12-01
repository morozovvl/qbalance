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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QMessageBox>
    #include <QtGui/QErrorMessage>
    #include <QtGui/QAbstractButton>
#else
    #include <QtWidgets/QMessageBox>
    #include <QtWidgets/QErrorMessage>
    #include <QtWidgets/QAbstractButton>
#endif

#include <QtCore/QString>
#include <QtCore/QProcess>
#include <QtSql/QSqlError>

#include <QtCore/QObject>
#include <QtCore/QIODevice>
#include <QtCore/QDir>
#include "guifactory.h"
#include "connectionform.h"
#include "mainwindow.h"
#include "calendarform.h"
#include "connectionform.h"
#include "passwordform.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"


GUIFactory::GUIFactory()
{
    db = nullptr;
    mainWindow = nullptr;
    app = TApplication::exemplar();
}


MainWindow* GUIFactory::getMainWindow()
{
    return mainWindow;
}


QString GUIFactory::getLastDbName()
{
    return lastDbName;
}


QString GUIFactory::getLastHostName()
{
    return lastHostName;
}


int GUIFactory::getLastPort()
{
    return lastPort;
}

int GUIFactory::openDB()
{
// Функция пытается создать соединение с БД. В случае удачи возвращает 0.
// В случае неудачи возвращает следующие коды ошибок:
//      -1: Пользователь нажал кнопку "Отмена"
//      -2: Ошибка соединения с сервером
//      -3: Неверно введен пароль
//      -4: Пользователь отказался от ввода пароля

    int returnCode = 0;     // По умолчанию будем считать, что удалось открыть БД
    QHash<int, UserInfo> users;
    int key = 0;

    app->setWriteDebug(false);
    db = app->getDBFactory();
    if (TApplication::host.size() > 0 &&
        TApplication::port != 0 &&
        TApplication::database.size() > 0 &&
        TApplication::username.size() > 0 &&
        TApplication::password.size() > 0)
    {
        returnCode = -1;
        db->setHostName(TApplication::host);
        db->setPort(TApplication::port);
        db->setDatabaseName(TApplication::database);
        if (db->open("test", "*"))
        {
            users = db->getUserList();
            foreach (key, users.keys())
            {
                if (users.value(key).loginName == TApplication::username ||
                    users.value(key).loginName + " " + users.value(key).userName == TApplication::username)
                {
                    app->setWriteDebug(true);
                    if (db->open(users.value(key).loginName, TApplication::password))
                    {
                        app->userid = users.value(key).id;
                        returnCode = 0;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        ConnectionForm* connForm = new ConnectionForm();
        connForm->open();
        connForm->initForm(db->getHostName(), db->getDatabaseName(), db->getPort());
        if (connForm->exec(db))
        {
            lastHostName = db->getHostName();
            lastDbName = db->getDatabaseName();
            lastPort = db->getPort();
            if (db->open("test", "*"))
            {
                bool formSelected;
                QString login, password;

                PassWordForm* frm = new PassWordForm(app->getMainWindow());
                users = db->getUserList();
                foreach (int key, users.keys())
                    frm->addLogin(QString(users.value(key).loginName + " " + users.value(key).userName).trimmed());
                db->close();
                frm->open();
                frm->exec();
                formSelected = frm->isFormSelected();
                login = frm->getLogin();
                password = frm->getPassword();
                frm->hide();
                frm->close();
                delete frm;

                if (formSelected)
                {   // Пользователь нажал кнопку "Ok"
                    QString userName;
                    foreach (key, users.keys())
                    {
                        if (QString("%1 %2").arg(users.value(key).loginName).arg(users.value(key).userName).trimmed() == login)
                        {
                            login = users.value(key).loginName.trimmed();
                            userName = users.value(key).userName.trimmed();
                            app->username = userName;
                            app->userid = users.value(key).id;
                            break;
                        }
                    }
                    app->setWriteDebug(true);
                    if (db->open(login, password))
                    {
                        app->password = password;
                    }
                    else
                    {
                        showError(QObject::trUtf8("Неверно введен пароль."));
                        returnCode = -3;
                    }
                }
                else
                    returnCode = -4;  //  Пользователь нажал кнопку "Отмена"
            }
            else
                returnCode = -2; // Ошибка соединения с сервером
        }
        else
            returnCode = -1;  //  Пользователь нажал кнопку "Отмена"
        connForm->close();
        delete connForm;
    }
    return returnCode;
}

void GUIFactory::closeDB() {
    if (db->isOpened())
        db->close();
}


void GUIFactory::setPeriod() {
    CalendarForm* calendar = new CalendarForm();
    calendar->open(mainWindow->centralWidget());
    calendar->setBeginDate(app->getBeginDate());
    calendar->setEndDate(app->getEndDate());
    calendar->exec();
    if (calendar->isFormSelected()) {
        app->setBeginDate(calendar->getBeginDate());
        app->setEndDate(calendar->getEndDate());
        app->getDBFactory()->setPeriod(calendar->getBeginDate(), calendar->getEndDate());
    }
    delete calendar;
}


void GUIFactory::show() {
    mainWindow->show();
}


void GUIFactory::showMenus()
{
    mainWindow->showMenus();
}


int GUIFactory::showError(QString errorText)
{
    Qt::WindowModality WidgetModality = Qt::WindowModal;
    QWidget* widget = app->activeWindow();
    if (widget == nullptr)
        widget = app->getMainWindow()->getWorkSpace()->activeSubWindow();

    if (widget != nullptr)
    {
        WidgetModality = widget->windowModality();
        widget->setWindowModality(Qt::NonModal);
    }

    QErrorMessage msgBox(mainWindow);
    msgBox.setParent(app->getMainWindow(), Qt::Dialog);
    msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.showMessage(errorText);
    msgBox.setWindowTitle("Ошибка!");
    msgBox.exec();

    if (widget != nullptr)
    {
        widget->setWindowModality(WidgetModality);
        widget->activateWindow();
    }
    return 0;
}


int GUIFactory::showMessage(QString message, QString question, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defButton) {
    int result = 0;
    QMdiSubWindow* window = nullptr;
    if (mainWindow != nullptr)
        window = mainWindow->getWorkSpace()->activeSubWindow();
    QMessageBox msgBox(window);
    msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.setParent(app->getMainWindow(), Qt::Dialog);
    msgBox.setWindowTitle(QObject::trUtf8("Внимание!"));
    msgBox.setText(message);
    if (question.size() > 0) {          // Если пользователю задан вопрос, то предусмотреть варианты ответа
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setInformativeText(question);
        msgBox.setStandardButtons(buttons);
        msgBox.setDefaultButton(defButton);
        QAbstractButton* buttonYes = msgBox.button(QMessageBox::Yes);
        buttonYes->setIcon(QIcon(":buttonOk"));
        QAbstractButton* buttonNo = msgBox.button(QMessageBox::No);
        buttonNo->setIcon(QIcon(":buttonCancel"));
     }
    else {                              // Вопрос не задан, значит выведем только кнопку "Ok"
        msgBox.setIcon(QMessageBox::Information);
    }
    msgBox.setMinimumWidth(400);
    msgBox.setMinimumHeight(200);
    msgBox.show();
    msgBox.activateWindow();
    msgBox.raise();
    result = msgBox.exec();
    if (window != nullptr)
        mainWindow->getWorkSpace()->setActiveSubWindow(window);
    return result;
}


int GUIFactory::showYesNo(QString question)
{
    return showMessage("", question);
}


bool GUIFactory::open() {
    mainWindow = new MainWindow(this);
    mainWindow->open();
    return true;
}

void GUIFactory::close() {
    mainWindow->close();
    delete mainWindow;
}

void GUIFactory::setWindowTitle(QString title) {
    if (title.size() > 0)
        mainWindow->setWindowTitle(title);
}
