#ifndef PASSWORDFORM_H
#define PASSWORDFORM_H

#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>

#include "form.h"

class PassWordForm: public Form {
public:
        PassWordForm(QObject* parent = NULL);
        Q_INVOKABLE virtual bool open(QWidget* pwgt = 0);
        void addLogin(QString);
        void addLogin(QStringList);
        QString getLogin() { return login; }
        QString getPassword() { return password; }
protected:
        virtual int doExec();
        virtual void readSettings();
        virtual void writeSettings();
private:
        QString login;
        QString password;
        QComboBox* pcmbLogin;
        QLineEdit* ptxtPassword;
        void cmdOk();
};

#endif
