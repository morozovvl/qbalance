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

#include <QIntValidator>
#include <QLabel>
#include <QPushButton>
#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include "connectionform.h"
#include "../kernel/app.h"


ConnectionForm::ConnectionForm(QObject* parent/* = 0*/): Form(parent)
{
    appendToMdi = false;        // Не добавлять окно к многооконному интерфейсу
}


ConnectionForm::~ConnectionForm()
{
}


void ConnectionForm::initForm(QString hostName, QString dbName, int portNum, bool readSettings)
{
    formWidget->setApp(TApplication::exemplar());
    formWidget->setWindowTitle(QObject::trUtf8("Параметры соединения"));
    QGridLayout* ptopLayout = new QGridLayout();
    QLabel* plblConnection = new QLabel(QObject::trUtf8("Имя соединения:"));
    QLabel* plblHost = new QLabel(QObject::trUtf8("Адрес сервера:"));
    QLabel* plblPort = new QLabel(QObject::trUtf8("Номер порта:"));
    QLabel* plblDatabase = new QLabel(QObject::trUtf8("Наименование БД:"));
    pcmbConnection = new QComboBox();
    if (readSettings)
        pcmbConnection->setEditable(true);
    connect(pcmbConnection, SIGNAL(activated(int)), this, SLOT(connectionChanged(int)));
    ptxtHost = new QLineEdit(hostName);
    QString port;
    port.setNum(portNum);
    ptxtPort = new QLineEdit(port);
    QIntValidator* validator = new QIntValidator(1, 65535, this);        // Разрешенный диапазон портов
    ptxtPort->setValidator(validator);
    ptxtDatabase = new QLineEdit(dbName);
    ptopLayout->addWidget(plblConnection, 0, 0, Qt::AlignRight);
    ptopLayout->addWidget(plblHost, 1, 0, Qt::AlignRight);
    ptopLayout->addWidget(plblPort, 2, 0, Qt::AlignRight);
    ptopLayout->addWidget(plblDatabase, 3, 0, Qt::AlignRight);
    ptopLayout->addWidget(pcmbConnection, 0, 1);
    ptopLayout->addWidget(ptxtHost, 1, 1);
    ptopLayout->addWidget(ptxtPort, 2, 1);
    ptopLayout->addWidget(ptxtDatabase, 3, 1);
    QVBoxLayout* vbxLayout = (QVBoxLayout*)formWidget->findChild("vbxLayout");
    if (vbxLayout != 0)
    {
        vbxLayout->insertLayout(0, ptopLayout);
        QHBoxLayout* cmdButtonLayout = (QHBoxLayout*)formWidget->findChild("cmdButtonLayout");
        if (cmdButtonLayout != 0)
        {
            QPushButton* buttonDelete = new QPushButton();
            buttonDelete->setObjectName("buttonDelete");
            buttonDelete->setToolTip(trUtf8("Удалить настройки подключения"));
            connect(buttonDelete, SIGNAL(clicked()), this, SLOT(buttonDelete()));
            QPushButton* buttonSave = new QPushButton();
            buttonSave->setObjectName("buttonSave");
            buttonSave->setToolTip(trUtf8("Сохранить настройки подключения"));
            connect(buttonSave, SIGNAL(clicked()), this, SLOT(buttonSave()));
            cmdButtonLayout->insertWidget(0, buttonDelete);
            cmdButtonLayout->insertWidget(0, buttonSave);
        }
    }
    buttonOk->setToolTip(trUtf8("Подключиться к серверу"));
    buttonCancel->setToolTip(trUtf8("Не подключаться к серверу и выйти из программы"));
    formWidget->setMinimumHeight(200);
    formWidget->setMinimumWidth(350);
    formWidget->setMaximumHeight(200);
    formWidget->setMaximumWidth(350);
    if (readSettings)
        readConnectionsList();
    app->setIcons(formWidget);
}


int ConnectionForm::exec(DBFactory* d)
{
    bool lResult;
    db = d;
    readDefaultSettings();
    readSettings(pcmbConnection->itemText(pcmbConnection->currentIndex()));
    gotoCenter();
    lResult = Form::exec();
    db->setHostName(ptxtHost->text());
    db->setDatabaseName(ptxtDatabase->text());
    db->setPort(ptxtPort->text().toInt());
    return lResult;
}


void ConnectionForm::buttonSave()
{
    if (pcmbConnection->currentText().trimmed().size() > 0)
    {
        writeSettings();
        readConnectionsList();
    }
    else
        TApplication::exemplar()->showError(trUtf8("Укажите наименование соединения!"));
}


void ConnectionForm::buttonDelete()
{
    deleteSettings(pcmbConnection->currentText());
}

void ConnectionForm::cmdOk()
{
    db->setHostName(ptxtHost->text());
    db->setPort(ptxtPort->text().toInt());
    db->setDatabaseName(ptxtDatabase->text());
    writeDefaultSettings();
    Form::cmdOk();
}

void ConnectionForm::cmdCancel()
{
    db->close();
    Form::cmdCancel();
}

void ConnectionForm::connectionChanged(int index)
{
    readSettings(pcmbConnection->itemText(index));
}

void ConnectionForm::readConnectionsList()
{
    QSettings settings;
    if (settings.status() == QSettings::NoError)
    {
          settings.beginGroup(CONNECTION_GROUP_NAME);
          pcmbConnection->clear();
          foreach (QString connectionName, settings.childGroups())
              pcmbConnection->addItem(connectionName);
          readSettings(pcmbConnection->currentText());
    }
}

void ConnectionForm::readDefaultSettings()
{
    QSettings settings;
    if (settings.status() == QSettings::NoError)
    {
        QString connection = settings.value("defaultConnection").toString();
        if (connection.size() > 0)
            pcmbConnection->setCurrentIndex(pcmbConnection->findText(connection));
    }
}

void ConnectionForm::writeDefaultSettings()
{
    QSettings settings;
    if (settings.status() == QSettings::NoError)
    {
        settings.setValue("defaultConnection", pcmbConnection->currentText());
    }
}

void ConnectionForm::readSettings(QString connectionName)
{
    QSettings settings;
    if (connectionName.size() > 0 && settings.status() == QSettings::NoError)
    {
        settings.beginGroup(CONNECTION_GROUP_NAME);
        settings.beginGroup(connectionName);
        ptxtHost->setText(settings.value("hostName").toString());
        ptxtPort->setText(QString("%1").arg(settings.value("portName").toInt()));
        ptxtDatabase->setText(settings.value("dbName").toString());
        settings.endGroup();
        settings.endGroup();
    }
}

void ConnectionForm::writeSettings()
{
    Form::writeSettings();
    QSettings settings;
    if (settings.status() == QSettings::NoError)
    {
        settings.setValue("defaultConnection", pcmbConnection->currentText());
        settings.beginGroup(CONNECTION_GROUP_NAME);
        settings.beginGroup(pcmbConnection->currentText());
        settings.setValue("hostName", ptxtHost->text());
        settings.setValue("portName", ptxtPort->text().toInt());
        settings.setValue("dbName", ptxtDatabase->text());
        settings.endGroup();
        settings.endGroup();
    }
}

void ConnectionForm::deleteSettings(QString connectionName)
{
    QSettings settings;
    if (connectionName.size() > 0 && settings.status() == QSettings::NoError)
    {
          settings.beginGroup(CONNECTION_GROUP_NAME);
          settings.remove(connectionName);
          settings.endGroup();
          readConnectionsList();
    }
}

