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
** Form generated from reading UI file 'paramlistedit.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMLISTEDIT_H
#define UI_PARAMLISTEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ParamListEdit
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *textLabel1;
    QListWidget *_list;
    QVBoxLayout *vboxLayout;
    QPushButton *_select;
    QPushButton *_cancel;
    QSpacerItem *spacer1;

    void setupUi(QDialog *ParamListEdit)
    {
        if (ParamListEdit->objectName().isEmpty())
            ParamListEdit->setObjectName(QString::fromUtf8("ParamListEdit"));
        ParamListEdit->resize(384, 256);
        horizontalLayout = new QHBoxLayout(ParamListEdit);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textLabel1 = new QLabel(ParamListEdit);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));

        verticalLayout->addWidget(textLabel1);

        _list = new QListWidget(ParamListEdit);
        _list->setObjectName(QString::fromUtf8("_list"));

        verticalLayout->addWidget(_list);


        horizontalLayout->addLayout(verticalLayout);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        _select = new QPushButton(ParamListEdit);
        _select->setObjectName(QString::fromUtf8("_select"));
        _select->setEnabled(false);

        vboxLayout->addWidget(_select);

        _cancel = new QPushButton(ParamListEdit);
        _cancel->setObjectName(QString::fromUtf8("_cancel"));

        vboxLayout->addWidget(_cancel);

        spacer1 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer1);


        horizontalLayout->addLayout(vboxLayout);

#ifndef QT_NO_SHORTCUT
        textLabel1->setBuddy(_list);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(_list, _select);
        QWidget::setTabOrder(_select, _cancel);

        retranslateUi(ParamListEdit);
        QObject::connect(_cancel, SIGNAL(clicked()), ParamListEdit, SLOT(reject()));
        QObject::connect(_select, SIGNAL(clicked()), ParamListEdit, SLOT(accept()));

        QMetaObject::connectSlotsByName(ParamListEdit);
    } // setupUi

    void retranslateUi(QDialog *ParamListEdit)
    {
        ParamListEdit->setWindowTitle(QApplication::translate("ParamListEdit", "List", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("ParamListEdit", "List:", 0, QApplication::UnicodeUTF8));
        _select->setText(QApplication::translate("ParamListEdit", "Select", 0, QApplication::UnicodeUTF8));
        _cancel->setText(QApplication::translate("ParamListEdit", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParamListEdit: public Ui_ParamListEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMLISTEDIT_H
