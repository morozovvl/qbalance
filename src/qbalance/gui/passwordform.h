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

#ifndef PASSWORDFORM_H
#define PASSWORDFORM_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>

#include "form.h"

class PassWordForm: public Form {
    Q_OBJECT
public:
        PassWordForm(QObject* parent = 0);
        ~PassWordForm();
        Q_INVOKABLE virtual bool open(QWidget* pwgt = 0);
        virtual void addLogin(QString);
        virtual void addLogin(QStringList);
        virtual QString getLogin() { return login; }
        QString getPassword() { return password; }
public slots:
        int exec();
        void cmdOk();

protected:
        void readSettings();
        void writeSettings();
private:
        QString login;
        QString password;
        QComboBox* LoginSelector;
        QLineEdit* PasswordEditor;
};

#endif
