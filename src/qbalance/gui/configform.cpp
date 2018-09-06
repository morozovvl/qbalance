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

#include <QtGui/QTreeWidgetItem>
#include <QtGui/QFrame>
#include <QtGui/QSizePolicy>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>
#include "configform.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"
#include "guifactory.h"
#include "mainwindow.h"
#include "myvalueeditor.h"
#include "dialog.h"


ConfigForm::ConfigForm(QObject* parent/* = 0*/): Form(parent)
{
    app = TApplication::exemplar();
    configName = "ConfigForm";
    currentConfigGroup = "";
    signalMapper = new QSignalMapper(this);
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(buttonPressed(QString)));
}


ConfigForm::~ConfigForm()
{
    disconnect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(buttonPressed(QString)));
    delete signalMapper;
}


bool ConfigForm::open(QWidget* pwgt)
{
    if (Form::open(pwgt))
    {
        configs = *(app->getConfigs());

        formWidget->setWindowTitle(QObject::trUtf8("Настройки"));

        QTreeWidget* treeWidget = new QTreeWidget();
        QTreeWidgetItem* treeWidgetItem0 = 0;
/*
        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList(QObject::trUtf8("Справочники")));
        treeWidgetItem0->addChild(new QTreeWidgetItem(QStringList() << QObject::trUtf8("Создать") << "10"));
        treeWidgetItem0->addChild(new QTreeWidgetItem(QStringList() << QObject::trUtf8("Свойства") << "11"));
        treeWidgetItem0->addChild(new QTreeWidgetItem(QStringList() << QObject::trUtf8("Доступ") << "12"));

        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList(QObject::trUtf8("Операции")));
        treeWidgetItem0->addChild(new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Создать") << "20"));
        treeWidgetItem0->addChild(new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Свойства") << "21"));
        treeWidgetItem0->addChild(new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Доступ") << "22"));

        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList(QObject::trUtf8("Отчеты")));
        treeWidgetItem0->addChild(new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Создать") << "30"));
        treeWidgetItem0->addChild(new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Свойства") << "31"));
        treeWidgetItem0->addChild(new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Доступ") << "32"));
*/
        foreach (QString type, app->getConfigTypes())
        {
            treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList() << app->getConfigTypeName(type) << type);
        }

        connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(dispatch(QTreeWidgetItem*, int)));

        treeWidget->setHeaderHidden(true);
        treeWidget->setSortingEnabled(false);
        treeWidget->setFixedWidth(200);

        frame = new QFrame();
        frame->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addWidget(treeWidget);
        hLayout->addWidget(frame);
        QVBoxLayout* vbxLayout = (QVBoxLayout*)formWidget->findChild("vbxLayout");
        if (vbxLayout != 0) {
            vbxLayout->insertLayout(0, hLayout);
        }

//        app->setIcons(formWidget);
        return true;
    }
    return false;
}


void ConfigForm::dispatch(QTreeWidgetItem* item, int) {
    QString currentItem = item->text(1);
    if (currentItem == "10")
        dictAdd();
    else if (currentItem == "11")
        dictProperties();
    else if (currentItem == "12")
        dictPermissions();
    else if (app->getConfigTypes().contains(currentItem))
        showConfigGroup(currentItem);
}


void ConfigForm::dictAdd() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
    QGridLayout* vLayout = new QGridLayout();
    QLabel* lblTableName = new QLabel(QObject::trUtf8("Наименование таблицы:"));
    lblTableName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QLineEdit* lnEdit = new QLineEdit();
    lnEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(lblTableName, 0, 0, Qt::AlignRight);
    vLayout->addWidget(lnEdit, 0, 1, Qt::AlignRight);
    frame->setLayout(vLayout);
}


void ConfigForm::dictProperties() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
}


void ConfigForm::dictColumns() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
}


void ConfigForm::dictPermissions() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
}


void ConfigForm::cmdOk()
{
    configs["PASSWORD1"].value = "";    // Сотрем пароли, чтобы они не запомнились в конфигурации
    configs["PASSWORD2"].value = "";

    app->setConfigs(&configs);
    Form::cmdOk();
}


void ConfigForm::showConfigGroup(QString type)
{
    currentConfigGroup = type;
    QLayout* layout = frame->layout();
    if (layout != 0)
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
    QGridLayout* vLayout = new QGridLayout();

    int row = 0;
    foreach (QString name, app->getConfigNames(type))
    {
        if (type.size() == 0 || type == configs.value(name).type)
        {
            QString labelStr = configs[name].label.trimmed();
            QLabel* label = new QLabel(labelStr + (labelStr.size() > 0 ? ":" : ""));
            MyValueEditor* line = new MyValueEditor(configs[name], this);
            label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            line->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            vLayout->addWidget(label, row, 0, Qt::AlignRight);
            vLayout->addWidget(line->getEditor(), row, 1, Qt::AlignLeft);
            row++;
        }
    }
    vLayout->setRowStretch(row, 1);
    vLayout->setColumnStretch(1, 1);
    frame->setLayout(vLayout);
}


void ConfigForm::buttonPressed(QString type)
{
    if (type == "PASSWORD_BUTTON")
        changePassword();
    else if (type == "UPDATES_FTP_ALL_UPLOAD")
        ftpTotalUpload();
    else if (type == "UPDATES_FTP_UPLOAD")
        ftpUpload();
    else if (type == "UPDATES_FTP_LOAD")
        ftpLoad();
}


void ConfigForm::changePassword()
{
    QString password1 = configs["PASSWORD1"].value.toString();
    QString password2 = configs["PASSWORD2"].value.toString();

    if (password1 == password2)
    {
        if (password1.size() > 0)
        {
            app->getDBFactory()->changePassword(password1);
            cmdOk();
        }
        else
            app->showError("Пароль не должен быть нулевой длины");
    }
    else
        app->showError("Пароли не совпадают");
}


void ConfigForm::ftpUpload()
{
    if (app->getUpdates() != 0)
    {
        app->getUpdates()->updateModified(false);
        cmdOk();
    }
}


void ConfigForm::ftpTotalUpload()
{
    if (app->getUpdates() != 0)
    {
        app->getUpdates()->putTotalUpdates();
        cmdOk();
    }
}


void ConfigForm::ftpLoad()
{
    if (app->getUpdates() != 0)
    {
        app->getUpdates()->updateModified();
        cmdOk();
    }
}
