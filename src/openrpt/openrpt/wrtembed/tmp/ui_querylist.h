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
** Form generated from reading UI file 'querylist.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYLIST_H
#define UI_QUERYLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QueryList
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *labelQuery;
    QListWidget *lbQuerys;
    QVBoxLayout *vboxLayout1;
    QPushButton *btnClose;
    QFrame *Line1;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *QueryList)
    {
        if (QueryList->objectName().isEmpty())
            QueryList->setObjectName(QString::fromUtf8("QueryList"));
        QueryList->resize(447, 306);
        QueryList->setSizeGripEnabled(true);
        hboxLayout = new QHBoxLayout(QueryList);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(0);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        labelQuery = new QLabel(QueryList);
        labelQuery->setObjectName(QString::fromUtf8("labelQuery"));

        vboxLayout->addWidget(labelQuery);

        lbQuerys = new QListWidget(QueryList);
        lbQuerys->setObjectName(QString::fromUtf8("lbQuerys"));

        vboxLayout->addWidget(lbQuerys);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        btnClose = new QPushButton(QueryList);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        vboxLayout1->addWidget(btnClose);

        Line1 = new QFrame(QueryList);
        Line1->setObjectName(QString::fromUtf8("Line1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Line1->sizePolicy().hasHeightForWidth());
        Line1->setSizePolicy(sizePolicy);
        Line1->setFrameShape(QFrame::HLine);
        Line1->setFrameShadow(QFrame::Sunken);
        Line1->setFrameShape(QFrame::HLine);

        vboxLayout1->addWidget(Line1);

        btnAdd = new QPushButton(QueryList);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        vboxLayout1->addWidget(btnAdd);

        btnEdit = new QPushButton(QueryList);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));

        vboxLayout1->addWidget(btnEdit);

        btnDelete = new QPushButton(QueryList);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        vboxLayout1->addWidget(btnDelete);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);


        hboxLayout->addLayout(vboxLayout1);

#ifndef QT_NO_SHORTCUT
        labelQuery->setBuddy(lbQuerys);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lbQuerys, btnAdd);
        QWidget::setTabOrder(btnAdd, btnEdit);
        QWidget::setTabOrder(btnEdit, btnDelete);
        QWidget::setTabOrder(btnDelete, btnClose);

        retranslateUi(QueryList);
        QObject::connect(btnClose, SIGNAL(clicked()), QueryList, SLOT(accept()));

        QMetaObject::connectSlotsByName(QueryList);
    } // setupUi

    void retranslateUi(QDialog *QueryList)
    {
        QueryList->setWindowTitle(QApplication::translate("QueryList", "Query List", 0, QApplication::UnicodeUTF8));
        labelQuery->setText(QApplication::translate("QueryList", "Querys:", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("QueryList", "&Close", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("QueryList", "&Add", 0, QApplication::UnicodeUTF8));
        btnEdit->setText(QApplication::translate("QueryList", "&Edit", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("QueryList", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QueryList: public Ui_QueryList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYLIST_H
