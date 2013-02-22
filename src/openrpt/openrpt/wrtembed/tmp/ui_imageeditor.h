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
** Form generated from reading UI file 'imageeditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEEDITOR_H
#define UI_IMAGEEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "querycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_ImageEditor
{
public:
    QGridLayout *gridLayout;
    QGroupBox *ButtonGroup1;
    QHBoxLayout *hboxLayout;
    QRadioButton *rbClip;
    QRadioButton *rbStretch;
    QCheckBox *cbStatic;
    QGroupBox *gbStatic;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *frmPreview;
    QPushButton *btnLoad;
    QVBoxLayout *vboxLayout;
    QGroupBox *gbDynamic;
    QGridLayout *gridLayout1;
    QLineEdit *tbColumn;
    QLabel *TextLabel1;
    QLabel *TextLabel1_3;
    QueryComboBox *cbQuery;
    QGroupBox *GroupBox1;
    QGridLayout *gridLayout2;
    QLineEdit *leHeight;
    QLineEdit *leWidth;
    QLabel *TextLabel2;
    QLabel *TextLabel4;
    QLabel *TextLabel1_3_2;
    QLabel *TextLabel3;
    QLabel *TextLabel5;
    QLineEdit *leYPos;
    QLineEdit *leXPos;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *ImageEditor)
    {
        if (ImageEditor->objectName().isEmpty())
            ImageEditor->setObjectName(QString::fromUtf8("ImageEditor"));
        ImageEditor->resize(568, 408);
        gridLayout = new QGridLayout(ImageEditor);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ButtonGroup1 = new QGroupBox(ImageEditor);
        ButtonGroup1->setObjectName(QString::fromUtf8("ButtonGroup1"));
        hboxLayout = new QHBoxLayout(ButtonGroup1);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        rbClip = new QRadioButton(ButtonGroup1);
        rbClip->setObjectName(QString::fromUtf8("rbClip"));

        hboxLayout->addWidget(rbClip);

        rbStretch = new QRadioButton(ButtonGroup1);
        rbStretch->setObjectName(QString::fromUtf8("rbStretch"));

        hboxLayout->addWidget(rbStretch);


        gridLayout->addWidget(ButtonGroup1, 0, 0, 1, 2);

        cbStatic = new QCheckBox(ImageEditor);
        cbStatic->setObjectName(QString::fromUtf8("cbStatic"));
        cbStatic->setChecked(true);

        gridLayout->addWidget(cbStatic, 1, 0, 1, 2);

        gbStatic = new QGroupBox(ImageEditor);
        gbStatic->setObjectName(QString::fromUtf8("gbStatic"));
        verticalLayout_2 = new QVBoxLayout(gbStatic);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(gbStatic);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 159, 215));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frmPreview = new QLabel(scrollAreaWidgetContents);
        frmPreview->setObjectName(QString::fromUtf8("frmPreview"));

        verticalLayout->addWidget(frmPreview);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        btnLoad = new QPushButton(gbStatic);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnLoad->sizePolicy().hasHeightForWidth());
        btnLoad->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnLoad);


        gridLayout->addWidget(gbStatic, 2, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gbDynamic = new QGroupBox(ImageEditor);
        gbDynamic->setObjectName(QString::fromUtf8("gbDynamic"));
        gbDynamic->setEnabled(false);
        gridLayout1 = new QGridLayout(gbDynamic);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        tbColumn = new QLineEdit(gbDynamic);
        tbColumn->setObjectName(QString::fromUtf8("tbColumn"));

        gridLayout1->addWidget(tbColumn, 1, 1, 1, 1);

        TextLabel1 = new QLabel(gbDynamic);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TextLabel1->sizePolicy().hasHeightForWidth());
        TextLabel1->setSizePolicy(sizePolicy1);

        gridLayout1->addWidget(TextLabel1, 1, 0, 1, 1);

        TextLabel1_3 = new QLabel(gbDynamic);
        TextLabel1_3->setObjectName(QString::fromUtf8("TextLabel1_3"));

        gridLayout1->addWidget(TextLabel1_3, 0, 0, 1, 1);

        cbQuery = new QueryComboBox(gbDynamic);
        cbQuery->setObjectName(QString::fromUtf8("cbQuery"));

        gridLayout1->addWidget(cbQuery, 0, 1, 1, 1);


        vboxLayout->addWidget(gbDynamic);

        GroupBox1 = new QGroupBox(ImageEditor);
        GroupBox1->setObjectName(QString::fromUtf8("GroupBox1"));
        gridLayout2 = new QGridLayout(GroupBox1);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        leHeight = new QLineEdit(GroupBox1);
        leHeight->setObjectName(QString::fromUtf8("leHeight"));

        gridLayout2->addWidget(leHeight, 1, 3, 1, 1);

        leWidth = new QLineEdit(GroupBox1);
        leWidth->setObjectName(QString::fromUtf8("leWidth"));

        gridLayout2->addWidget(leWidth, 0, 3, 1, 1);

        TextLabel2 = new QLabel(GroupBox1);
        TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));

        gridLayout2->addWidget(TextLabel2, 1, 0, 1, 1);

        TextLabel4 = new QLabel(GroupBox1);
        TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));

        gridLayout2->addWidget(TextLabel4, 1, 2, 1, 1);

        TextLabel1_3_2 = new QLabel(GroupBox1);
        TextLabel1_3_2->setObjectName(QString::fromUtf8("TextLabel1_3_2"));

        gridLayout2->addWidget(TextLabel1_3_2, 0, 0, 1, 1);

        TextLabel3 = new QLabel(GroupBox1);
        TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));

        gridLayout2->addWidget(TextLabel3, 0, 2, 1, 1);

        TextLabel5 = new QLabel(GroupBox1);
        TextLabel5->setObjectName(QString::fromUtf8("TextLabel5"));
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica [Cronyx]"));
        font.setPointSize(6);
        font.setBold(false);
        font.setItalic(true);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        TextLabel5->setFont(font);
        TextLabel5->setTextFormat(Qt::AutoText);
        TextLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(TextLabel5, 2, 3, 1, 1);

        leYPos = new QLineEdit(GroupBox1);
        leYPos->setObjectName(QString::fromUtf8("leYPos"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leYPos->sizePolicy().hasHeightForWidth());
        leYPos->setSizePolicy(sizePolicy2);
        leYPos->setMinimumSize(QSize(0, 0));

        gridLayout2->addWidget(leYPos, 1, 1, 1, 1);

        leXPos = new QLineEdit(GroupBox1);
        leXPos->setObjectName(QString::fromUtf8("leXPos"));
        sizePolicy2.setHeightForWidth(leXPos->sizePolicy().hasHeightForWidth());
        leXPos->setSizePolicy(sizePolicy2);
        leXPos->setMinimumSize(QSize(0, 0));

        gridLayout2->addWidget(leXPos, 0, 1, 1, 1);


        vboxLayout->addWidget(GroupBox1);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        buttonOk = new QPushButton(ImageEditor);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout1->addWidget(buttonOk);

        buttonCancel = new QPushButton(ImageEditor);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout1->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout->addLayout(vboxLayout, 2, 1, 1, 1);

        QWidget::setTabOrder(rbClip, rbStretch);
        QWidget::setTabOrder(rbStretch, cbStatic);
        QWidget::setTabOrder(cbStatic, btnLoad);
        QWidget::setTabOrder(btnLoad, cbQuery);
        QWidget::setTabOrder(cbQuery, tbColumn);
        QWidget::setTabOrder(tbColumn, leXPos);
        QWidget::setTabOrder(leXPos, leWidth);
        QWidget::setTabOrder(leWidth, leYPos);
        QWidget::setTabOrder(leYPos, leHeight);
        QWidget::setTabOrder(leHeight, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);

        retranslateUi(ImageEditor);
        QObject::connect(buttonOk, SIGNAL(clicked()), ImageEditor, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), ImageEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImageEditor);
    } // setupUi

    void retranslateUi(QDialog *ImageEditor)
    {
        ImageEditor->setWindowTitle(QApplication::translate("ImageEditor", "Image Editor", 0, QApplication::UnicodeUTF8));
        ButtonGroup1->setTitle(QApplication::translate("ImageEditor", "Resize Mode", 0, QApplication::UnicodeUTF8));
        rbClip->setText(QApplication::translate("ImageEditor", "Clip", 0, QApplication::UnicodeUTF8));
        rbStretch->setText(QApplication::translate("ImageEditor", "Stretch", 0, QApplication::UnicodeUTF8));
        cbStatic->setText(QApplication::translate("ImageEditor", "Static Image", 0, QApplication::UnicodeUTF8));
        gbStatic->setTitle(QApplication::translate("ImageEditor", "Static", 0, QApplication::UnicodeUTF8));
        frmPreview->setText(QString());
        btnLoad->setText(QApplication::translate("ImageEditor", "&Load...", 0, QApplication::UnicodeUTF8));
        gbDynamic->setTitle(QApplication::translate("ImageEditor", "Database", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("ImageEditor", "Column:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3->setText(QApplication::translate("ImageEditor", "Query Source:", 0, QApplication::UnicodeUTF8));
        GroupBox1->setTitle(QApplication::translate("ImageEditor", "Position/Size", 0, QApplication::UnicodeUTF8));
        leHeight->setText(QApplication::translate("ImageEditor", "0.01", 0, QApplication::UnicodeUTF8));
        leWidth->setText(QApplication::translate("ImageEditor", "0.01", 0, QApplication::UnicodeUTF8));
        TextLabel2->setText(QApplication::translate("ImageEditor", "Y:", 0, QApplication::UnicodeUTF8));
        TextLabel4->setText(QApplication::translate("ImageEditor", "Height:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3_2->setText(QApplication::translate("ImageEditor", "X:", 0, QApplication::UnicodeUTF8));
        TextLabel3->setText(QApplication::translate("ImageEditor", "Width:", 0, QApplication::UnicodeUTF8));
        TextLabel5->setText(QApplication::translate("ImageEditor", "in inches", 0, QApplication::UnicodeUTF8));
        leYPos->setText(QApplication::translate("ImageEditor", "0.00", 0, QApplication::UnicodeUTF8));
        leXPos->setText(QApplication::translate("ImageEditor", "0.00", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("ImageEditor", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("ImageEditor", "Alt+O", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("ImageEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("ImageEditor", "Alt+C", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageEditor: public Ui_ImageEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEEDITOR_H
