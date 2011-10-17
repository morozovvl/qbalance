#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <QProcess>
#include <QObject>
#include <QIODevice>
#include <QDir>
#include "guifactory.h"
#include "connectionform.h"
#include "mainwindow.h"
#include "calendarform.h"
#include "connectionform.h"
#include "passwordform.h"
#include "../kernel/app.h"

int GUIFactory::openDB()
{
// Функция пытается создать соединение с БД. В случае удачи возвращает 0.
// В случае неудачи возвращает следующие коды ошибок:
//      -1: Пользователь нажал кнопку "Отмена"
//      -2: Ошибка соединения с сервером
//      -3: Неверно введен пароль
//      -4: Пользователь отказался от ввода пароля

    int returnCode = 0;     // По умолчанию будем считать, что удалось открыть БД
/*
    QString login = "sa";
    QString password = "123456";
    if (db->open(login, password))
    {
        mainWindow->setWindowTitle(programName + " - localhost - " + login);
    }
    else
        returnCode = -2;
*/
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
            PassWordForm frm;
            frm.open();
            frm.addLogin(db->getUserList());
            db->close();
            frm.exec();
            if (frm.selected())
            {   // Пользователь нажал кнопку "Ok"
                QString login = frm.getLogin();
                QString password = frm.getPassword();
                if (db->open(login, password))
                {
                    if (connForm->connectionName().size() > 0)
                        mainWindow->setWindowTitle(TApplication::exemplar()->applicationName() + " - " + connForm->connectionName() + " - " + login);
                }
                else
                {
                    showCriticalError(QObject::tr("Неверно введен пароль."));
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
    return returnCode;
}

void GUIFactory::closeDB() {
}

void GUIFactory::setPeriod() {
    CalendarForm* calendar = new CalendarForm();
    calendar->open(mainWindow->centralWidget());
    calendar->readSettings();
    calendar->setBeginDate(TApplication::exemplar()->getBeginDate());
    calendar->setEndDate(TApplication::exemplar()->getEndDate());
    calendar->exec();
    if (calendar->selected()) {
        TApplication::exemplar()->setBeginDate(calendar->getBeginDate());
        TApplication::exemplar()->setEndDate(calendar->getEndDate());
        TApplication::exemplar()->getDBFactory()->setPeriod(calendar->getBeginDate(), calendar->getEndDate());
    }
    calendar->writeSettings();
    delete calendar;
}

void GUIFactory::show() {
    mainWindow->show();
}

int GUIFactory::showError(QString errorText) {
    QErrorMessage msgBox(mainWindow->centralWidget());
    msgBox.setWindowTitle(QObject::tr("Ошибка!"));
    msgBox.showMessage(errorText);
//    msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.exec();
    return 0;
}

int GUIFactory::showCriticalError(QString errorText) {
    QMessageBox msgBox(mainWindow->centralWidget());
    msgBox.setWindowTitle(QObject::tr("Критическая ошибка!"));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(errorText);
//    msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.exec();
    return 0;
}

int GUIFactory::showMessage(QString message, QString question, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defButton) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(QObject::tr("Внимание!"));
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
    mainWindow = new MainWindow();
    mainWindow->open();
    return true;
}

void GUIFactory::close() {
    closeDB();
//    mainWindow->close();
}

void GUIFactory::setWindowTitle(QString title) {
    if (title.size() > 0)
        mainWindow->setWindowTitle(title);
}
