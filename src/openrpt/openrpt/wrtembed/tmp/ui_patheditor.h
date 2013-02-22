/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2011 by OpenMFG, LLC
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
** Form generated from reading UI file 'patheditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHEDITOR_H
#define UI_PATHEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PathEditor
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *_lblWidth;
    QSpinBox *_sbWidth;
    QGroupBox *_gbStyle;
    QGridLayout *gridLayout;
    QRadioButton *_rbSolidStyle;
    QRadioButton *_rbDashedStyle;
    QRadioButton *_rbDottedStyle;
    QVBoxLayout *vboxLayout1;
    QPushButton *_btnAccept;
    QPushButton *_btnCancel;
    QSpacerItem *spacerItem;
    QPushButton *_btnColor;

    void setupUi(QDialog *PathEditor)
    {
        if (PathEditor->objectName().isEmpty())
            PathEditor->setObjectName(QString::fromUtf8("PathEditor"));
        PathEditor->resize(248, 161);
        hboxLayout = new QHBoxLayout(PathEditor);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        _lblWidth = new QLabel(PathEditor);
        _lblWidth->setObjectName(QString::fromUtf8("_lblWidth"));

        hboxLayout1->addWidget(_lblWidth);

        _sbWidth = new QSpinBox(PathEditor);
        _sbWidth->setObjectName(QString::fromUtf8("_sbWidth"));

        hboxLayout1->addWidget(_sbWidth);


        vboxLayout->addLayout(hboxLayout1);

        _gbStyle = new QGroupBox(PathEditor);
        _gbStyle->setObjectName(QString::fromUtf8("_gbStyle"));
        gridLayout = new QGridLayout(_gbStyle);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _rbSolidStyle = new QRadioButton(_gbStyle);
        _rbSolidStyle->setObjectName(QString::fromUtf8("_rbSolidStyle"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/OpenRPT/images/line_solid.png"), QSize(), QIcon::Normal, QIcon::Off);
        _rbSolidStyle->setIcon(icon);
        _rbSolidStyle->setIconSize(QSize(80, 16));

        gridLayout->addWidget(_rbSolidStyle, 0, 0, 1, 1);

        _rbDashedStyle = new QRadioButton(_gbStyle);
        _rbDashedStyle->setObjectName(QString::fromUtf8("_rbDashedStyle"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/OpenRPT/images/line_dashed.png"), QSize(), QIcon::Normal, QIcon::Off);
        _rbDashedStyle->setIcon(icon1);
        _rbDashedStyle->setIconSize(QSize(80, 16));

        gridLayout->addWidget(_rbDashedStyle, 1, 0, 1, 1);

        _rbDottedStyle = new QRadioButton(_gbStyle);
        _rbDottedStyle->setObjectName(QString::fromUtf8("_rbDottedStyle"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/OpenRPT/images/line_dotted.png"), QSize(), QIcon::Normal, QIcon::Off);
        _rbDottedStyle->setIcon(icon2);
        _rbDottedStyle->setIconSize(QSize(80, 16));

        gridLayout->addWidget(_rbDottedStyle, 2, 0, 1, 1);


        vboxLayout->addWidget(_gbStyle);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        _btnAccept = new QPushButton(PathEditor);
        _btnAccept->setObjectName(QString::fromUtf8("_btnAccept"));

        vboxLayout1->addWidget(_btnAccept);

        _btnCancel = new QPushButton(PathEditor);
        _btnCancel->setObjectName(QString::fromUtf8("_btnCancel"));

        vboxLayout1->addWidget(_btnCancel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);

        _btnColor = new QPushButton(PathEditor);
        _btnColor->setObjectName(QString::fromUtf8("_btnColor"));

        vboxLayout1->addWidget(_btnColor);


        hboxLayout->addLayout(vboxLayout1);

        QWidget::setTabOrder(_btnColor, _btnAccept);
        QWidget::setTabOrder(_btnAccept, _btnCancel);

        retranslateUi(PathEditor);
        QObject::connect(_btnAccept, SIGNAL(clicked()), PathEditor, SLOT(accept()));
        QObject::connect(_btnCancel, SIGNAL(clicked()), PathEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(PathEditor);
    } // setupUi

    void retranslateUi(QDialog *PathEditor)
    {
        PathEditor->setWindowTitle(QApplication::translate("PathEditor", "Stroke properties", 0, QApplication::UnicodeUTF8));
        _lblWidth->setText(QApplication::translate("PathEditor", "Width:", 0, QApplication::UnicodeUTF8));
        _gbStyle->setTitle(QApplication::translate("PathEditor", "Style", 0, QApplication::UnicodeUTF8));
        _rbSolidStyle->setText(QString());
        _rbDashedStyle->setText(QString());
        _rbDottedStyle->setText(QString());
        _btnAccept->setText(QApplication::translate("PathEditor", "&OK", 0, QApplication::UnicodeUTF8));
        _btnCancel->setText(QApplication::translate("PathEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        _btnColor->setText(QApplication::translate("PathEditor", "Color...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PathEditor: public Ui_PathEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATHEDITOR_H
