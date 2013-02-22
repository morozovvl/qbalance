/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2012 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
*/

/********************************************************************************
** Form generated from reading UI file 'loginOptions.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINOPTIONS_H
#define UI_LOGINOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_loginOptions
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QLineEdit *_database;
    QLabel *_databaseLit;
    QVBoxLayout *vboxLayout1;
    QLineEdit *_server;
    QHBoxLayout *hboxLayout1;
    QLineEdit *_port;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout2;
    QLabel *_serverLit;
    QLabel *_portLit;
    QLabel *_driverLit;
    QComboBox *_driver;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout3;
    QVBoxLayout *vboxLayout4;
    QPushButton *_close;
    QPushButton *_save;
    QSpacerItem *spacerItem2;

    void setupUi(QDialog *loginOptions)
    {
        if (loginOptions->objectName().isEmpty())
            loginOptions->setObjectName(QString::fromUtf8("loginOptions"));
        loginOptions->resize(380, 129);
        hboxLayout = new QHBoxLayout(loginOptions);
        hboxLayout->setSpacing(5);
        hboxLayout->setContentsMargins(5, 5, 5, 5);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(0);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(5);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _database = new QLineEdit(loginOptions);
        _database->setObjectName(QString::fromUtf8("_database"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_database->sizePolicy().hasHeightForWidth());
        _database->setSizePolicy(sizePolicy);
        _database->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(_database, 1, 1, 1, 1);

        _databaseLit = new QLabel(loginOptions);
        _databaseLit->setObjectName(QString::fromUtf8("_databaseLit"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_databaseLit->sizePolicy().hasHeightForWidth());
        _databaseLit->setSizePolicy(sizePolicy1);
        _databaseLit->setMinimumSize(QSize(0, 25));
        _databaseLit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_databaseLit, 1, 0, 1, 1);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(0);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        _server = new QLineEdit(loginOptions);
        _server->setObjectName(QString::fromUtf8("_server"));
        sizePolicy.setHeightForWidth(_server->sizePolicy().hasHeightForWidth());
        _server->setSizePolicy(sizePolicy);
        _server->setMinimumSize(QSize(0, 25));

        vboxLayout1->addWidget(_server);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(0);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        _port = new QLineEdit(loginOptions);
        _port->setObjectName(QString::fromUtf8("_port"));
        sizePolicy.setHeightForWidth(_port->sizePolicy().hasHeightForWidth());
        _port->setSizePolicy(sizePolicy);
        _port->setMinimumSize(QSize(0, 25));
        _port->setMaximumSize(QSize(80, 32767));

        hboxLayout1->addWidget(_port);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);


        vboxLayout1->addLayout(hboxLayout1);


        gridLayout->addLayout(vboxLayout1, 2, 1, 1, 1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(0);
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        _serverLit = new QLabel(loginOptions);
        _serverLit->setObjectName(QString::fromUtf8("_serverLit"));
        sizePolicy1.setHeightForWidth(_serverLit->sizePolicy().hasHeightForWidth());
        _serverLit->setSizePolicy(sizePolicy1);
        _serverLit->setMinimumSize(QSize(0, 25));
        _serverLit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        vboxLayout2->addWidget(_serverLit);

        _portLit = new QLabel(loginOptions);
        _portLit->setObjectName(QString::fromUtf8("_portLit"));
        sizePolicy1.setHeightForWidth(_portLit->sizePolicy().hasHeightForWidth());
        _portLit->setSizePolicy(sizePolicy1);
        _portLit->setMinimumSize(QSize(0, 25));
        _portLit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        vboxLayout2->addWidget(_portLit);


        gridLayout->addLayout(vboxLayout2, 2, 0, 1, 1);

        _driverLit = new QLabel(loginOptions);
        _driverLit->setObjectName(QString::fromUtf8("_driverLit"));
        sizePolicy1.setHeightForWidth(_driverLit->sizePolicy().hasHeightForWidth());
        _driverLit->setSizePolicy(sizePolicy1);
        _driverLit->setMinimumSize(QSize(0, 25));
        _driverLit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_driverLit, 0, 0, 1, 1);

        _driver = new QComboBox(loginOptions);
        _driver->setObjectName(QString::fromUtf8("_driver"));

        gridLayout->addWidget(_driver, 0, 1, 1, 1);


        vboxLayout->addLayout(gridLayout);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem1);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(0);
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setSpacing(5);
        vboxLayout4->setContentsMargins(0, 0, 0, 0);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        _close = new QPushButton(loginOptions);
        _close->setObjectName(QString::fromUtf8("_close"));

        vboxLayout4->addWidget(_close);

        _save = new QPushButton(loginOptions);
        _save->setObjectName(QString::fromUtf8("_save"));
        _save->setAutoDefault(true);
        _save->setDefault(true);

        vboxLayout4->addWidget(_save);


        vboxLayout3->addLayout(vboxLayout4);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem2);


        hboxLayout->addLayout(vboxLayout3);

#ifndef QT_NO_SHORTCUT
        _databaseLit->setBuddy(_database);
        _serverLit->setBuddy(_server);
        _portLit->setBuddy(_port);
        _driverLit->setBuddy(_database);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(_driver, _database);
        QWidget::setTabOrder(_database, _server);
        QWidget::setTabOrder(_server, _port);
        QWidget::setTabOrder(_port, _save);
        QWidget::setTabOrder(_save, _close);

        retranslateUi(loginOptions);
        QObject::connect(_close, SIGNAL(clicked()), loginOptions, SLOT(reject()));

        QMetaObject::connectSlotsByName(loginOptions);
    } // setupUi

    void retranslateUi(QDialog *loginOptions)
    {
        loginOptions->setWindowTitle(QApplication::translate("loginOptions", "Login Options", 0, QApplication::UnicodeUTF8));
        _databaseLit->setText(QApplication::translate("loginOptions", "&Database:", 0, QApplication::UnicodeUTF8));
        _serverLit->setText(QApplication::translate("loginOptions", "S&erver:", 0, QApplication::UnicodeUTF8));
        _portLit->setText(QApplication::translate("loginOptions", "&Port:", 0, QApplication::UnicodeUTF8));
        _driverLit->setText(QApplication::translate("loginOptions", "Driver:", 0, QApplication::UnicodeUTF8));
        _driver->clear();
        _driver->insertItems(0, QStringList()
         << QApplication::translate("loginOptions", "PostgreSQL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("loginOptions", "ODBC", 0, QApplication::UnicodeUTF8)
        );
        _close->setText(QApplication::translate("loginOptions", "&Cancel", 0, QApplication::UnicodeUTF8));
        _save->setText(QApplication::translate("loginOptions", "&Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginOptions: public Ui_loginOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINOPTIONS_H
