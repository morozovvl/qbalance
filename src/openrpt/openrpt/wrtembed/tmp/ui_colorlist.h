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
** Form generated from reading UI file 'colorlist.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORLIST_H
#define UI_COLORLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ColorList
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *_lbColors;
    QVBoxLayout *vboxLayout;
    QPushButton *_btnClose;
    QFrame *_line1;
    QPushButton *_btnAdd;
    QPushButton *_btnEdit;
    QPushButton *_btnDelete;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *ColorList)
    {
        if (ColorList->objectName().isEmpty())
            ColorList->setObjectName(QString::fromUtf8("ColorList"));
        ColorList->resize(330, 222);
        horizontalLayout = new QHBoxLayout(ColorList);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        _lbColors = new QListWidget(ColorList);
        _lbColors->setObjectName(QString::fromUtf8("_lbColors"));

        horizontalLayout->addWidget(_lbColors);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        _btnClose = new QPushButton(ColorList);
        _btnClose->setObjectName(QString::fromUtf8("_btnClose"));

        vboxLayout->addWidget(_btnClose);

        _line1 = new QFrame(ColorList);
        _line1->setObjectName(QString::fromUtf8("_line1"));
        _line1->setFrameShape(QFrame::HLine);
        _line1->setFrameShadow(QFrame::Sunken);
        _line1->setFrameShape(QFrame::HLine);

        vboxLayout->addWidget(_line1);

        _btnAdd = new QPushButton(ColorList);
        _btnAdd->setObjectName(QString::fromUtf8("_btnAdd"));

        vboxLayout->addWidget(_btnAdd);

        _btnEdit = new QPushButton(ColorList);
        _btnEdit->setObjectName(QString::fromUtf8("_btnEdit"));

        vboxLayout->addWidget(_btnEdit);

        _btnDelete = new QPushButton(ColorList);
        _btnDelete->setObjectName(QString::fromUtf8("_btnDelete"));

        vboxLayout->addWidget(_btnDelete);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);


        horizontalLayout->addLayout(vboxLayout);

        QWidget::setTabOrder(_btnAdd, _btnEdit);
        QWidget::setTabOrder(_btnEdit, _btnDelete);
        QWidget::setTabOrder(_btnDelete, _btnClose);
        QWidget::setTabOrder(_btnClose, _lbColors);

        retranslateUi(ColorList);
        QObject::connect(_btnClose, SIGNAL(clicked()), ColorList, SLOT(accept()));

        QMetaObject::connectSlotsByName(ColorList);
    } // setupUi

    void retranslateUi(QDialog *ColorList)
    {
        ColorList->setWindowTitle(QApplication::translate("ColorList", "Color Definitions", 0, QApplication::UnicodeUTF8));
        _btnClose->setText(QApplication::translate("ColorList", "&Close", 0, QApplication::UnicodeUTF8));
        _btnAdd->setText(QApplication::translate("ColorList", "&Add", 0, QApplication::UnicodeUTF8));
        _btnEdit->setText(QApplication::translate("ColorList", "&Edit", 0, QApplication::UnicodeUTF8));
        _btnDelete->setText(QApplication::translate("ColorList", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ColorList: public Ui_ColorList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORLIST_H
