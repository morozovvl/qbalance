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
    bool lResult = false;   // По умолчанию будем считать, что приложение открыть не удалось
    organizationName = "Enterprise";
    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);
    db = new DBFactory();
    gui = new GUIFactory(db);
    if (gui->open()) {  // Попытаемся открыть графический интерфейс
        forever         // Будем бесконечно пытаться открыть базу, пока пользователь не откажется
        {
            int result = gui->openDB(); // Попытаемся открыть базу данных
            if (result == 0)
            {   // БД открыть удалось
                dictionaryList = new Dictionaries;
                topersList = new Topers;
                if (dictionaryList->open() && topersList->open())
                {   // И удалось открыть спосок справочников и типовых операций
                    db->getPeriod(beginDate, endDate);
                    gui->getMainWindow()->showPeriod();
                    lResult = true;     // Приложение удалось открыть
                    break;  // Выйдем из бесконечного цикла открытия БД
                }
            }
            else if (result == -2)
                {   // Произошла ошибка соединения с сервером
                QString errorText = db->getErrorText();
                showError(errorText);
                if (gui->showMessage(QObject::tr("Не удалось соединиться с базой данных (БД). Возможно БД отсутствует."),
                                     QObject::tr("Попытаться создать новую БД?")) == QMessageBox::Yes)
                    // Попытаемся создать новую БД
                    db->createNewDB(gui->getLastHostName(), gui->getLastDbName(), gui->getLastPort());
            }
            else if (result == -1)      // Пользователь нажал кнопку Отмена
                break;  // Выйдем из бесконечного цикла открытия БД
        }
    }
    return lResult;
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

QString App::encoding()
{
    QString result("UTF-8");
#ifdef Q_OS_WIN32
    if (QSysInfo::windowsVersion() != QSysInfo::WV_WINDOWS7)
        result = "Windows-1251";
#endif
    return result;
}

QTextCodec* App::codec()
{
    return QTextCodec::codecForName(encoding().toLatin1());
}
