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

#include <QTreeWidgetItem>
#include <QFrame>
#include <QSizePolicy>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include "configform.h"
#include "../kernel/app.h"
#include "guifactory.h"
#include "mainwindow.h"

ConfigForm::ConfigForm(QObject* parent/* = 0*/): Form(parent)
{
    app = TApplication::exemplar();

    lnFrPortName = new QLineEdit();
    lnBoud = new QComboBox();
    lnPort = new QLineEdit();
    lnAddress = new QLineEdit();
    barCodePortName = new QLineEdit();
}


ConfigForm::~ConfigForm()
{
    delete lnFrPortName;
    delete lnBoud;
    delete lnPort;
    delete lnAddress;
}


bool ConfigForm::open(QWidget* pwgt) {
    if (Form::open(pwgt)) {
        formWidget->setWindowTitle(QObject::trUtf8("Настройки"));

        QTreeWidget* treeWidget = new QTreeWidget();
        QTreeWidgetItem* treeWidgetItem0 = 0;

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

        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList() << QObject::trUtf8("Картинки") << "40");
        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList() << QObject::trUtf8("Фискальный регистратор") << "50");
        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList() << QObject::trUtf8("Сканер штрих-кодов") << "60");
        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList() << QObject::trUtf8("Считыватель магнитных карт") << "70");

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
    currentItem = item->text(1).toInt();
    switch(currentItem) {
    case 10: dictAdd();
                break;
    case 11: dictProperties();
                break;
    case 12: dictPermissions();
                break;
    case 40: pictures();
                break;
    case 50: fr();
                break;
    case 60: barCode();
                break;
    case 70: cardReader();
                break;
    }
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
    lnEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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


void ConfigForm::pictures()
{
}


void ConfigForm::fr()
{
    QLayout* layout = frame->layout();
    if (layout != 0)
    {
        delete layout;
        frame->setLayout(0);
    }
    QGridLayout* vLayout = new QGridLayout();

    QLabel* lblPortName = new QLabel(QObject::trUtf8("COM порт:"));
    lblPortName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    lnFrPortName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(lblPortName, 0, 0, Qt::AlignLeft);
    vLayout->addWidget(lnFrPortName, 0, 1, Qt::AlignLeft);

    QLabel* lblBoud = new QLabel(QObject::trUtf8("Скорость:"));
    lblBoud->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    lnBoud->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lnBoud->addItem("2400");
    lnBoud->addItem("4800");
    lnBoud->addItem("9600");
    lnBoud->addItem("19200");
    lnBoud->addItem("38400");
    lnBoud->addItem("57600");
    lnBoud->addItem("115200");
    lnBoud->setCurrentIndex(app->getConfig()->frDriverBaudRate);

    vLayout->addWidget(lblBoud, 1, 0, Qt::AlignLeft);
    vLayout->addWidget(lnBoud, 1, 1, Qt::AlignLeft);

    QLabel* lblPort = new QLabel(QObject::trUtf8("Порт сервера ФР:"));
    lblPort->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    lnPort->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(lblPort, 2, 0, Qt::AlignLeft);
    vLayout->addWidget(lnPort, 2, 1, Qt::AlignLeft);

    QLabel* lblAddress = new QLabel(QObject::trUtf8("IP адрес сервера ФР:"));
    lblAddress->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    lnAddress->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(lblAddress, 3, 0, Qt::AlignLeft);
    vLayout->addWidget(lnAddress, 3, 1, Qt::AlignLeft);
    vLayout->setRowStretch(4, 1);

    frame->setLayout(vLayout);

    lnFrPortName->setText(app->getConfig()->frDriverPort);
    lnBoud->setCurrentIndex(app->getConfig()->frDriverBaudRate);
    lnPort->setText(QString("%1").arg(app->getConfig()->localPort));
    lnAddress->setText(app->getConfig()->remoteHost);
}


void ConfigForm::barCode()
{
    QLayout* layout = frame->layout();
    if (layout != 0)
    {
        delete layout;
        frame->setLayout(0);
    }
    QGridLayout* vLayout = new QGridLayout();

    QLabel* lblPortName = new QLabel(QObject::trUtf8("COM порт:"));
    lblPortName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    barCodePortName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vLayout->addWidget(lblPortName, 0, 0, Qt::AlignLeft);
    vLayout->addWidget(barCodePortName, 0, 1, Qt::AlignLeft);
    vLayout->setRowStretch(1, 1);

    frame->setLayout(vLayout);

    barCodePortName->setText(app->getConfig()->barCodeReaderPort);
}


void ConfigForm::cardReader()
{

}


void ConfigForm::cmdOk()
{
    switch(currentItem) {
    case 10: dictAdd();
                break;
    case 11: dictProperties();
                break;
    case 12: dictPermissions();
                break;
    case 40: pictures();
                break;
    case 50: app->getConfig()->frDriverPort = lnFrPortName->text();
             app->getConfig()->frDriverBaudRate = lnBoud->currentIndex();
             app->getConfig()->localPort = lnPort->text().toInt();
             app->getConfig()->remoteHost = lnAddress->text();
             break;
    case 60: app->getConfig()->barCodeReaderPort = barCodePortName->text();
             break;
    }
    Form::cmdOk();
}
