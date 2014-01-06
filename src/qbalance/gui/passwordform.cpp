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

#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "passwordform.h"
#include "../kernel/app.h"

PassWordForm::PassWordForm(QObject* parent/* = 0*/) : Form(parent)
{
    appendToMdi = false;        // Не добавлять окно к многооконному интерфейсу, т.к. его к этому моменту еще не существует
}



PassWordForm::~PassWordForm()
{
}


bool PassWordForm::open(QWidget* pwgt/* = 0*/)
// Создает форму ввода пароля на основе формы с кнопками "Ок" и "Cancel"
{
    LoginSelector = new QComboBox();
    PasswordEditor = new QLineEdit();
    PasswordEditor->setEchoMode(QLineEdit::Password);

    QFormLayout* layout = new QFormLayout();

    layout->addRow(QObject::trUtf8("Логин:"), LoginSelector);
    layout->addRow(QObject::trUtf8("Пароль:"), PasswordEditor);

    if (Form::open(pwgt))
    {
        connect(PasswordEditor, SIGNAL(returnPressed()), this, SLOT(cmdOk()));
        QVBoxLayout* vbxLayout = (QVBoxLayout*)formWidget->findChild("vbxLayout");
        if (vbxLayout != 0)
            vbxLayout->insertLayout(0, layout);
        formWidget->setMinimumHeight(100);
        formWidget->setMinimumWidth(200);
        formWidget->setMaximumHeight(100);
        formWidget->setMaximumWidth(200);
        gotoCenter();
        return true;
    }
    return false;
}


int PassWordForm::exec()
{
    readSettings();
    PasswordEditor->setFocus();
    return Form::exec();
}


void PassWordForm::addLogin(QString login)
{
    LoginSelector->addItem(login);
    LoginSelector->setCurrentIndex(0);
    LoginSelector->repaint();
}


void PassWordForm::addLogin(QStringList list)
{
    LoginSelector->addItems(list);
    LoginSelector->setCurrentIndex(0);
    LoginSelector->repaint();
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
    QSettings settings;
    if (settings.status() == QSettings::NoError)
    {
        QString user = settings.value("defaultUser").toString();
        if (user.size() > 0)
            LoginSelector->setCurrentIndex(LoginSelector->findText(user));
    }
}

void PassWordForm::writeSettings()
{
    QSettings settings;
    if (settings.status() == QSettings::NoError)
        settings.setValue("defaultUser", login);
}
