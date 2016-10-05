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

#include <QtCore/QString>
#include <QtGui/QMessageBox>
#include <QtGui/QErrorMessage>
#include <QtCore/QProcess>

#include <QtCore/QObject>
#include <QtCore/QIODevice>
#include <QtCore/QDir>
#include <QtGui/QAbstractButton>
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
    db = 0;
    mainWindow = 0;
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

    db = TApplication::exemplar()->getDBFactory();
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
                    if (db->open(users.value(key).loginName, TApplication::password))
                    {
                        mainWindow->setWindowTitle(TApplication::exemplar()->applicationName() + " - " + "(" + TApplication::exemplar()->getConfigPrefix() + ") - " + users.value(key).loginName + " " + users.value(key).userName);
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
                PassWordForm* frm = new PassWordForm();
                users = db->getUserList();
                frm->open();
                foreach (int key, users.keys())
                    frm->addLogin(users.value(key).loginName + " " + users.value(key).userName);
                db->close();
                frm->exec();
                if (frm->isFormSelected())
                {   // Пользователь нажал кнопку "Ok"
                    QString login;
                    QString userName;
                    foreach (key, users.keys())
                    {
                        if (users.value(key).loginName + " " + users.value(key).userName == frm->getLogin())
                        {
                            login = users.value(key).loginName.trimmed();
                            userName = users.value(key).userName.trimmed();
                            TApplication::exemplar()->username = userName;
                            break;
                        }
                    }
                    QString password = frm->getPassword();
                    if (db->open(login, password))
                    {
                        TApplication::exemplar()->password = password;
                        if (connForm->connectionName().size() > 0)
                            mainWindow->setWindowTitle(TApplication::exemplar()->applicationName() + " - " + connForm->connectionName() + "(" + TApplication::exemplar()->getConfigPrefix() + ") - " + login + " " + userName);
                    }
                    else
                    {
                        showError(QObject::trUtf8("Неверно введен пароль."));
                        returnCode = -3;
                    }
                }
                else
                    returnCode = -4;  //  Пользователь нажал кнопку "Отмена"
                delete frm;
            }
            else
                returnCode = -2; // Ошибка соединения с сервером
        }
        else
            returnCode = -1;  //  Пользователь нажал кнопку "Отмена"
        connForm->close();
        delete connForm;
    }
    if (returnCode == 0)
    {
        db->initDBFactory();
        db->exec(QString("SELECT session_variables.set_value('%1', '%2');").arg("client_user_id").arg(QString("%1").arg(key)));
    }
    return returnCode;
}

void GUIFactory::closeDB() {
    db->close();
}


void GUIFactory::setPeriod() {
    CalendarForm* calendar = new CalendarForm();
    calendar->open(mainWindow->centralWidget());
    calendar->setBeginDate(TApplication::exemplar()->getBeginDate());
    calendar->setEndDate(TApplication::exemplar()->getEndDate());
    calendar->exec();
    if (calendar->isFormSelected()) {
        TApplication::exemplar()->setBeginDate(calendar->getBeginDate());
        TApplication::exemplar()->setEndDate(calendar->getEndDate());
        TApplication::exemplar()->getDBFactory()->setPeriod(calendar->getBeginDate(), calendar->getEndDate());
    }
    delete calendar;
}

void GUIFactory::show() {
    mainWindow->show();
}


int GUIFactory::showError(QString errorText) {
    QMdiSubWindow* window = 0;
    if (mainWindow != 0)
        window = mainWindow->getWorkSpace()->activeSubWindow();
    QErrorMessage msgBox(window);
    msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.setParent(TApplication::exemplar()->getMainWindow(), Qt::Dialog);
    msgBox.showMessage(errorText);
    msgBox.show();
    msgBox.activateWindow();
    msgBox.raise();
    msgBox.exec();
    if (window != 0)
        mainWindow->getWorkSpace()->setActiveSubWindow(window);
    return 0;
}


int GUIFactory::showMessage(QString message, QString question, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defButton) {
    int result = 0;
    QMdiSubWindow* window = 0;
    if (mainWindow != 0)
        window = mainWindow->getWorkSpace()->activeSubWindow();
    QMessageBox msgBox(window);
    msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.setParent(TApplication::exemplar()->getMainWindow(), Qt::Dialog);
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
    if (window != 0)
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
    msgBox.setVisible(false);
    msgBox.setWindowTitle(QObject::trUtf8("Ошибка!"));
    return true;
}

void GUIFactory::close() {
    closeDB();
    mainWindow->close();
    delete mainWindow;
}

void GUIFactory::setWindowTitle(QString title) {
    if (title.size() > 0)
        mainWindow->setWindowTitle(title);
}
