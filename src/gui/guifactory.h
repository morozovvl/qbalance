#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include "../kernel/custom.h"
#include "../storage/dbfactory.h"
#include <QString>
#include <QMessageBox>
#include <QDesktopWidget>

class TApplication;
class MainWindow;

class GUIFactory: public Custom {
public:
    GUIFactory(DBFactory *d) { db = d; }
    MainWindow* getMainWindow() { return mainWindow; }
    QString getLastDbName() { return lastDbName; }
    QString getLastHostName() { return lastHostName; }
    int getLastPort() { return lastPort; }
    int openDB();
    void closeDB();
    void setPeriod();
    void setWindowTitle(QString);
    void show();
    int showError(QString);             // Сообщить пользователю об ошибке и вернуть его реакцию
    int showCriticalError(QString);
    int showMessage(QString message, QString question = "",
                    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::StandardButton defButton = QMessageBox::No);      // Вывести сообщение пользователю и возможно задать вопрос
    int showYesNo(QString);
private:
    DBFactory* db;
    MainWindow* mainWindow;
    QString lastHostName;
    QString lastDbName;
    int lastPort;
    bool doOpen();
    void doClose();
};

#endif // GUIFACTORY_H
