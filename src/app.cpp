#include <QDate>
#include <QMessageBox>
#include <QObject>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "gui/guifactory.h"
#include "gui/passwordform.h"
#include "gui/formgrid.h"
#include "gui/mainwindow.h"

App::App(QApplication* appl) {
    organizationName = "Enterprise";
    application = appl;
    appl->setOrganizationName(organizationName);
    appl->setApplicationName(organizationName);
}

Documents* App::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Documents* doc = new Documents(opNumber);
        if (!doc->open())
            return NULL;
        documents.insert(operName, doc);
    }
    return documents[operName];
}

bool App::doOpen() {
    organizationName = "Enterprise";
    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);
    db = new DBFactory();
    gui = new GUIFactory(db);
    if (gui->open()) {               // Попытаемся создать графический интерфейс
        while (true) {
            int result = gui->openDB();
            if (result == 0) {  // Попытаемся открыть базу данных
                dictionaryList = new Dictionaries;
                topersList = new Topers;
                if (dictionaryList->open() && topersList->open()) {
                        db->getPeriod(beginDate, endDate);
                        gui->getMainWindow()->showPeriod();
                        return true;
                    }
                else
                    break;
            }
            else if (result == -1) {
                QString errorText = db->getErrorText();
                showError(errorText);
//                if (errorText.contains(QString("database \"%1\" does not exist").arg(gui->getLastDbName())))
                    if (gui->showMessage(QObject::tr("Не удалось соединиться с базой данных (БД). Возможно БД отсутствует."), QObject::tr("Попытаться создать новую БД?")) == QMessageBox::Yes) {
                        if (!db->createNewDB(gui->getLastHostName(), gui->getLastDbName(), gui->getLastPort()))
                            break;  // не удалось создать новую базу данных
                    }
            }
            else if (result == -2)      // Пользователь нажал кнопку Отмена
                break;
/*
            else {                   // База данных скорее всего отсутствует, спросим: надо ли ее создать?
                if (db->isError()) {
                    if (gui->showMessage(QObject::tr("База данных скорее всего отсутствует."), QObject::tr("Создать новую базу данных?")) == QMessageBox::Yes) {
                        if (!gui->createNewDB())
                            break;  // не удалось создать новую базу данных
                    }
                    else
                        break;      // пользователь отказался создавать базу данных
                }
                else
                    break;           // Выйдем из диалога не создавая базы данных
            }
*/
        }
    }
    return false;
}

void App::doClose() {
    foreach(Documents* doc, documents) {
        doc->close();
    }
    dictionaryList->close();
    delete dictionaryList;
    topersList->close();
    delete topersList;
    gui->close();
    delete gui;
    db->close();
    delete db;
}

QString App::getFormsPath(QString formName) {
    QString fileName = getHomePath() + "/forms" + "/" + formName;
    return fileName;
}

