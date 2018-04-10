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

#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "passwordform.h"
#include "../kernel/app.h"
#include "dialog.h"

PassWordForm::PassWordForm(QObject* parent/* = 0*/) : Form(parent)
{
    appendToMdi = false;        // Не добавлять окно к многооконному интерфейсу, т.к. его к этому моменту еще не существует

    LoginSelector = new QComboBox();
//    LoginSelector->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    PasswordEditor = new QLineEdit();
    PasswordEditor->setEchoMode(QLineEdit::Password);
}



PassWordForm::~PassWordForm()
{
}


QString PassWordForm::getLogin()
{
    return login;
}


QString PassWordForm::getPassword()
{
    return password;
}


bool PassWordForm::open(QWidget* pwgt/* = 0*/)
// Создает форму ввода пароля на основе формы с кнопками "Ок" и "Cancel"
{
    QFormLayout* layout = new QFormLayout();

    layout->addRow(QObject::trUtf8("Пользователь:"), LoginSelector);
    layout->addRow(QObject::trUtf8("Пароль:"), PasswordEditor);
    if (Form::open(pwgt))
    {
        setFormTitle(QObject::trUtf8("Логин и пароль"));

        connect(PasswordEditor, SIGNAL(returnPressed()), this, SLOT(cmdOk()));
        QVBoxLayout* vbxLayout = (QVBoxLayout*)formWidget->findChild("vbxLayout");
        if (vbxLayout != 0)
            vbxLayout->insertLayout(0, layout);
        formWidget->setMinimumHeight(100);
        formWidget->setMinimumWidth(500);
        formWidget->setMaximumHeight(100);
        formWidget->setMaximumWidth(500);
        gotoCenter();
        return true;
    }
    return false;
}


int PassWordForm::exec()
{
    PasswordEditor->setFocus();
    return Form::exec();
}


void PassWordForm::addLogin(QString login)
{
    LoginSelector->addItem(login);
    LoginSelector->itemText(LoginSelector->currentIndex());
}


void PassWordForm::addLogin(QStringList list)
{
    LoginSelector->addItems(list);
    LoginSelector->itemText(LoginSelector->currentIndex());
}


void PassWordForm::cmdOk()
{
    Form::cmdOk();
    login = LoginSelector->currentText();
    password = PasswordEditor->text();
    writeSettings();
}


void PassWordForm::readSettings()
{
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    if (settings.status() == QSettings::NoError)
    {
        QString user = settings.value("defaultUser").toString();
        if (user.size() > 0)
        {
            LoginSelector->setCurrentIndex(LoginSelector->findText(user));
        }
    }
}

void PassWordForm::writeSettings()
{
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    if (settings.status() == QSettings::NoError)
    {
        settings.setValue("defaultUser", LoginSelector->currentText());
    }
}
