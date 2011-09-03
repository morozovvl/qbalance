#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <QProcess>
#include <QObject>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "guifactory.h"
#include "connectionform.h"
#include "mainwindow.h"
#include "calendarform.h"
#include "connectionform.h"
#include "passwordform.h"
#include "../app.h"

extern QString programName;
extern bool programDebugMode;
extern QTextStream programDebugStream;
extern QString programLogTimeFormat;

int GUIFactory::openDB() {
/*
    QString login = "sa";
    QString password = "123456";
    if (db->open(login, password)) {
        mainWindow->setWindowTitle(programName + " - localhost - " + login);
        return 0;
    }
    return -2;
*/
    ConnectionForm* connForm = new ConnectionForm();
    connForm->open();
    connForm->initForm(db->getHostName(), db->getDatabaseName(), db->getPort());
    if (connForm->exec(db)) {
        lastHostName = db->getHostName();
        lastDbName = db->getDatabaseName();
        lastPort = db->getPort();
        if (db->open("test", "*")) {
            PassWordForm frm;
            frm.addLogin(db->getUserList());
            db->close();
            if (frm.exec()) {
                QString login = frm.getLogin();
                QString password = frm.getPassword();
                if (db->open(login, password)) {
                    if (connForm->connectionName().size() > 0)
                        mainWindow->setWindowTitle(programName + " - " + connForm->connectionName() + " - " + login);
                    connForm->close();
                    delete connForm;
                    return 0;
                }
                else {
                    showCriticalError(QObject::tr("Неверно введен пароль."));
                    connForm->close();
                    delete connForm;
                    return -1;
                    }
            }
        }
        else {
            connForm->close();
            delete connForm;
            return -1; // Ошибка соединения с сервером
        }
    }
    connForm->close();
    delete connForm;
    return -2;  //  Пользователь нажал кнопку "Отмена"
}

void GUIFactory::closeDB() {
}

void GUIFactory::setPeriod() {
    CalendarForm* calendar = new CalendarForm();
    calendar->open(mainWindow->centralWidget());
    calendar->readSettings();
    calendar->setBeginDate(app->getBeginDate());
    calendar->setEndDate(app->getEndDate());
    calendar->exec();
    if (calendar->selected()) {
        app->setBeginDate(calendar->getBeginDate());
        app->setEndDate(calendar->getEndDate());
        app->getDBFactory()->setPeriod(calendar->getBeginDate(), calendar->getEndDate());
    }
    calendar->writeSettings();
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

bool GUIFactory::doOpen() {
    mainWindow = new MainWindow();
    mainWindow->open();
    return true;
}

void GUIFactory::doClose() {
    closeDB();
//    mainWindow->close();
}

void GUIFactory::setWindowTitle(QString title) {
    if (title.size() > 0)
        mainWindow->setWindowTitle(title);
}
