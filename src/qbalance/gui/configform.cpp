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
#include "configform.h"
#include "../kernel/app.h"
#include "guifactory.h"
#include "mainwindow.h"

ConfigForm::ConfigForm(QObject* parent/* = 0*/): Form(parent)
{
}


ConfigForm::~ConfigForm()
{
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
        QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
        if (vbxLayout != 0) {
            vbxLayout->insertLayout(0, hLayout);
        }
        app->setIcons(formWidget);
        return true;
    }
    return false;
}


void ConfigForm::dispatch(QTreeWidgetItem* item, int) {
    switch(item->text(1).toInt()) {
    case 10: dictAdd();
                break;
    case 11: dictProperties();
                break;
    case 12: dictPermissions();
                break;
    case 40: pictures();
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
