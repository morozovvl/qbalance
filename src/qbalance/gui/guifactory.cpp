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
#include "guifactory.h"
#include "connectionform.h"
#include "mainwindow.h"
#include "calendarform.h"
#include "connectionform.h"
#include "passwordform.h"
#include "../kernel/app.h"


GUIFactory::GUIFactory(DBFactory *d)
{
    db = d;
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
            frm->open();
            frm->addLogin(db->getUserList());
            db->close();
            frm->exec();
            if (frm->selected())
            {   // Пользователь нажал кнопку "Ok"
                QString login = frm->getLogin();
                QString password = frm->getPassword();
                if (db->open(login, password))
                {
                    db->initDBFactory();
                    if (connForm->connectionName().size() > 0)
                        mainWindow->setWindowTitle(TApplication::exemplar()->applicationName() + " - " + connForm->connectionName() + "(" + TApplication::exemplar()->getConfigPrefix() + ") - " + login);
                }
                else
                {
                    showCriticalError(QObject::trUtf8("Неверно введен пароль."));
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
    if (calendar->selected()) {
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
    QMdiSubWindow* window = mainWindow->getWorkSpace()->activeSubWindow();
    QErrorMessage msgBox;
    msgBox.setParent(TApplication::exemplar()->activeWindow(), Qt::Dialog);
    msgBox.showMessage(errorText);
    mainWindow->setUpdatesEnabled(false);
    msgBox.exec();
    mainWindow->setUpdatesEnabled(true);
    if (window != 0)
        mainWindow->getWorkSpace()->setActiveSubWindow(window);
    return 0;
}

int GUIFactory::showCriticalError(QString errorText) {
    QMdiSubWindow* window = mainWindow->getWorkSpace()->activeSubWindow();
    QMessageBox msgBox;
    msgBox.setParent(TApplication::exemplar()->getMainWindow(), Qt::Dialog);
    msgBox.setWindowTitle(QObject::trUtf8("Критическая ошибка!"));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(errorText);
    mainWindow->setUpdatesEnabled(false);
    msgBox.exec();
    mainWindow->setUpdatesEnabled(true);
    if (window != 0)
        mainWindow->getWorkSpace()->setActiveSubWindow(window);
    return 0;
}

int GUIFactory::showMessage(QString message, QString question, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defButton) {
    QMessageBox msgBox;
    msgBox.setParent(TApplication::exemplar()->getMainWindow(), Qt::Dialog);
    msgBox.setWindowTitle(QObject::trUtf8("Внимание!"));
    msgBox.setText(message);
    if (question.size() > 0) {          // Если пользователю задан вопрос, то предусмотреть варианты ответа
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setInformativeText(question);
        msgBox.setStandardButtons(buttons);
        msgBox.setDefaultButton(defButton);
     }
    else {                              // Вопрос не задан, значит выведем только кнопку "Ok"
        msgBox.setIcon(QMessageBox::Information);
    }
    msgBox.setMinimumWidth(400);
    msgBox.setMinimumHeight(200);
//    msgBox.setWindowModality(Qt::ApplicationModal);
//    msgBox.show();
    return msgBox.exec();
}

int GUIFactory::showYesNo(QString question) {
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
}

void GUIFactory::setWindowTitle(QString title) {
    if (title.size() > 0)
        mainWindow->setWindowTitle(title);
}
