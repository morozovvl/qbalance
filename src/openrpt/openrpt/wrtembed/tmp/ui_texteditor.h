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
** Form generated from reading UI file 'texteditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITOR_H
#define UI_TEXTEDITOR_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "querycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_TextEditor
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QueryComboBox *cbQuery;
    QLabel *TextLabel1_4;
    QLineEdit *tbBottompad;
    QLineEdit *tbColumn;
    QLabel *TextLabel1_3;
    QLabel *TextLabel1;
    QHBoxLayout *hboxLayout1;
    QGroupBox *bgHAlign;
    QVBoxLayout *vboxLayout1;
    QRadioButton *rbHAlignNone;
    QRadioButton *rbHAlignLeft;
    QRadioButton *rbHAlignCenter;
    QRadioButton *rbHAlignRight;
    QGroupBox *bgVAlign;
    QVBoxLayout *vboxLayout2;
    QRadioButton *rbVAlignNone;
    QRadioButton *rbVAlignTop;
    QRadioButton *rbVAlignMiddle;
    QRadioButton *rbVAlignBottom;
    QGroupBox *GroupBox1;
    QGridLayout *gridLayout1;
    QLineEdit *leHeight;
    QLineEdit *leWidth;
    QLabel *TextLabel2;
    QLabel *TextLabel4;
    QLabel *TextLabel1_3_2;
    QLabel *TextLabel3;
    QLabel *TextLabel5;
    QLineEdit *leYPos;
    QLineEdit *leXPos;
    QLabel *TextLabel1_2;
    QLabel *labelPreview;
    QVBoxLayout *vboxLayout3;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QSpacerItem *spacerItem;
    QPushButton *btnFont;

    void setupUi(QDialog *TextEditor)
    {
        if (TextEditor->objectName().isEmpty())
            TextEditor->setObjectName(QString::fromUtf8("TextEditor"));
        TextEditor->resize(402, 506);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextEditor->sizePolicy().hasHeightForWidth());
        TextEditor->setSizePolicy(sizePolicy);
        TextEditor->setSizeGripEnabled(true);
        hboxLayout = new QHBoxLayout(TextEditor);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cbQuery = new QueryComboBox(TextEditor);
        cbQuery->setObjectName(QString::fromUtf8("cbQuery"));

        gridLayout->addWidget(cbQuery, 0, 1, 1, 1);

        TextLabel1_4 = new QLabel(TextEditor);
        TextLabel1_4->setObjectName(QString::fromUtf8("TextLabel1_4"));

        gridLayout->addWidget(TextLabel1_4, 2, 0, 1, 1);

        tbBottompad = new QLineEdit(TextEditor);
        tbBottompad->setObjectName(QString::fromUtf8("tbBottompad"));

        gridLayout->addWidget(tbBottompad, 2, 1, 1, 1);

        tbColumn = new QLineEdit(TextEditor);
        tbColumn->setObjectName(QString::fromUtf8("tbColumn"));

        gridLayout->addWidget(tbColumn, 1, 1, 1, 1);

        TextLabel1_3 = new QLabel(TextEditor);
        TextLabel1_3->setObjectName(QString::fromUtf8("TextLabel1_3"));

        gridLayout->addWidget(TextLabel1_3, 0, 0, 1, 1);

        TextLabel1 = new QLabel(TextEditor);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TextLabel1->sizePolicy().hasHeightForWidth());
        TextLabel1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(TextLabel1, 1, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        bgHAlign = new QGroupBox(TextEditor);
        bgHAlign->setObjectName(QString::fromUtf8("bgHAlign"));
        sizePolicy1.setHeightForWidth(bgHAlign->sizePolicy().hasHeightForWidth());
        bgHAlign->setSizePolicy(sizePolicy1);
        vboxLayout1 = new QVBoxLayout(bgHAlign);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        rbHAlignNone = new QRadioButton(bgHAlign);
        rbHAlignNone->setObjectName(QString::fromUtf8("rbHAlignNone"));

        vboxLayout1->addWidget(rbHAlignNone);

        rbHAlignLeft = new QRadioButton(bgHAlign);
        rbHAlignLeft->setObjectName(QString::fromUtf8("rbHAlignLeft"));

        vboxLayout1->addWidget(rbHAlignLeft);

        rbHAlignCenter = new QRadioButton(bgHAlign);
        rbHAlignCenter->setObjectName(QString::fromUtf8("rbHAlignCenter"));

        vboxLayout1->addWidget(rbHAlignCenter);

        rbHAlignRight = new QRadioButton(bgHAlign);
        rbHAlignRight->setObjectName(QString::fromUtf8("rbHAlignRight"));

        vboxLayout1->addWidget(rbHAlignRight);


        hboxLayout1->addWidget(bgHAlign);

        bgVAlign = new QGroupBox(TextEditor);
        bgVAlign->setObjectName(QString::fromUtf8("bgVAlign"));
        sizePolicy1.setHeightForWidth(bgVAlign->sizePolicy().hasHeightForWidth());
        bgVAlign->setSizePolicy(sizePolicy1);
        vboxLayout2 = new QVBoxLayout(bgVAlign);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        rbVAlignNone = new QRadioButton(bgVAlign);
        rbVAlignNone->setObjectName(QString::fromUtf8("rbVAlignNone"));

        vboxLayout2->addWidget(rbVAlignNone);

        rbVAlignTop = new QRadioButton(bgVAlign);
        rbVAlignTop->setObjectName(QString::fromUtf8("rbVAlignTop"));

        vboxLayout2->addWidget(rbVAlignTop);

        rbVAlignMiddle = new QRadioButton(bgVAlign);
        rbVAlignMiddle->setObjectName(QString::fromUtf8("rbVAlignMiddle"));

        vboxLayout2->addWidget(rbVAlignMiddle);

        rbVAlignBottom = new QRadioButton(bgVAlign);
        rbVAlignBottom->setObjectName(QString::fromUtf8("rbVAlignBottom"));

        vboxLayout2->addWidget(rbVAlignBottom);


        hboxLayout1->addWidget(bgVAlign);


        vboxLayout->addLayout(hboxLayout1);

        GroupBox1 = new QGroupBox(TextEditor);
        GroupBox1->setObjectName(QString::fromUtf8("GroupBox1"));
        gridLayout1 = new QGridLayout(GroupBox1);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setHorizontalSpacing(6);
        gridLayout1->setVerticalSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        leHeight = new QLineEdit(GroupBox1);
        leHeight->setObjectName(QString::fromUtf8("leHeight"));

        gridLayout1->addWidget(leHeight, 1, 3, 1, 1);

        leWidth = new QLineEdit(GroupBox1);
        leWidth->setObjectName(QString::fromUtf8("leWidth"));

        gridLayout1->addWidget(leWidth, 0, 3, 1, 1);

        TextLabel2 = new QLabel(GroupBox1);
        TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));

        gridLayout1->addWidget(TextLabel2, 1, 0, 1, 1);

        TextLabel4 = new QLabel(GroupBox1);
        TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));

        gridLayout1->addWidget(TextLabel4, 1, 2, 1, 1);

        TextLabel1_3_2 = new QLabel(GroupBox1);
        TextLabel1_3_2->setObjectName(QString::fromUtf8("TextLabel1_3_2"));

        gridLayout1->addWidget(TextLabel1_3_2, 0, 0, 1, 1);

        TextLabel3 = new QLabel(GroupBox1);
        TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));

        gridLayout1->addWidget(TextLabel3, 0, 2, 1, 1);

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

        gridLayout1->addWidget(TextLabel5, 2, 3, 1, 1);

        leYPos = new QLineEdit(GroupBox1);
        leYPos->setObjectName(QString::fromUtf8("leYPos"));

        gridLayout1->addWidget(leYPos, 1, 1, 1, 1);

        leXPos = new QLineEdit(GroupBox1);
        leXPos->setObjectName(QString::fromUtf8("leXPos"));

        gridLayout1->addWidget(leXPos, 0, 1, 1, 1);


        vboxLayout->addWidget(GroupBox1);

        TextLabel1_2 = new QLabel(TextEditor);
        TextLabel1_2->setObjectName(QString::fromUtf8("TextLabel1_2"));
        sizePolicy1.setHeightForWidth(TextLabel1_2->sizePolicy().hasHeightForWidth());
        TextLabel1_2->setSizePolicy(sizePolicy1);

        vboxLayout->addWidget(TextLabel1_2);

        labelPreview = new QLabel(TextEditor);
        labelPreview->setObjectName(QString::fromUtf8("labelPreview"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelPreview->sizePolicy().hasHeightForWidth());
        labelPreview->setSizePolicy(sizePolicy2);
        labelPreview->setMinimumSize(QSize(0, 42));
        labelPreview->setFrameShape(QFrame::StyledPanel);
        labelPreview->setFrameShadow(QFrame::Sunken);
        labelPreview->setAlignment(Qt::AlignVCenter);

        vboxLayout->addWidget(labelPreview);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        buttonOk = new QPushButton(TextEditor);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        vboxLayout3->addWidget(buttonOk);

        buttonCancel = new QPushButton(TextEditor);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        vboxLayout3->addWidget(buttonCancel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem);

        btnFont = new QPushButton(TextEditor);
        btnFont->setObjectName(QString::fromUtf8("btnFont"));

        vboxLayout3->addWidget(btnFont);


        hboxLayout->addLayout(vboxLayout3);

        QWidget::setTabOrder(cbQuery, tbColumn);
        QWidget::setTabOrder(tbColumn, tbBottompad);
        QWidget::setTabOrder(tbBottompad, rbHAlignNone);
        QWidget::setTabOrder(rbHAlignNone, rbHAlignLeft);
        QWidget::setTabOrder(rbHAlignLeft, rbHAlignCenter);
        QWidget::setTabOrder(rbHAlignCenter, rbHAlignRight);
        QWidget::setTabOrder(rbHAlignRight, rbVAlignNone);
        QWidget::setTabOrder(rbVAlignNone, rbVAlignTop);
        QWidget::setTabOrder(rbVAlignTop, rbVAlignMiddle);
        QWidget::setTabOrder(rbVAlignMiddle, rbVAlignBottom);
        QWidget::setTabOrder(rbVAlignBottom, leXPos);
        QWidget::setTabOrder(leXPos, leWidth);
        QWidget::setTabOrder(leWidth, leYPos);
        QWidget::setTabOrder(leYPos, leHeight);
        QWidget::setTabOrder(leHeight, btnFont);
        QWidget::setTabOrder(btnFont, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);

        retranslateUi(TextEditor);
        QObject::connect(buttonOk, SIGNAL(clicked()), TextEditor, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), TextEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(TextEditor);
    } // setupUi

    void retranslateUi(QDialog *TextEditor)
    {
        TextEditor->setWindowTitle(QApplication::translate("TextEditor", "Properties (Text)", 0, QApplication::UnicodeUTF8));
        TextLabel1_4->setText(QApplication::translate("TextEditor", "Bottom Padding:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3->setText(QApplication::translate("TextEditor", "Query Source:", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("TextEditor", "Column:", 0, QApplication::UnicodeUTF8));
        bgHAlign->setTitle(QApplication::translate("TextEditor", "HAlign", 0, QApplication::UnicodeUTF8));
        rbHAlignNone->setText(QApplication::translate("TextEditor", "None", 0, QApplication::UnicodeUTF8));
        rbHAlignLeft->setText(QApplication::translate("TextEditor", "Left", 0, QApplication::UnicodeUTF8));
        rbHAlignCenter->setText(QApplication::translate("TextEditor", "Center", 0, QApplication::UnicodeUTF8));
        rbHAlignRight->setText(QApplication::translate("TextEditor", "Right", 0, QApplication::UnicodeUTF8));
        bgVAlign->setTitle(QApplication::translate("TextEditor", "VAlign", 0, QApplication::UnicodeUTF8));
        rbVAlignNone->setText(QApplication::translate("TextEditor", "None", 0, QApplication::UnicodeUTF8));
        rbVAlignTop->setText(QApplication::translate("TextEditor", "Top", 0, QApplication::UnicodeUTF8));
        rbVAlignMiddle->setText(QApplication::translate("TextEditor", "Middle", 0, QApplication::UnicodeUTF8));
        rbVAlignBottom->setText(QApplication::translate("TextEditor", "Bottom", 0, QApplication::UnicodeUTF8));
        GroupBox1->setTitle(QApplication::translate("TextEditor", "Position/Size", 0, QApplication::UnicodeUTF8));
        leHeight->setText(QApplication::translate("TextEditor", "0.01", 0, QApplication::UnicodeUTF8));
        leWidth->setText(QApplication::translate("TextEditor", "0.01", 0, QApplication::UnicodeUTF8));
        TextLabel2->setText(QApplication::translate("TextEditor", "Y:", 0, QApplication::UnicodeUTF8));
        TextLabel4->setText(QApplication::translate("TextEditor", "Height:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3_2->setText(QApplication::translate("TextEditor", "X:", 0, QApplication::UnicodeUTF8));
        TextLabel3->setText(QApplication::translate("TextEditor", "Width:", 0, QApplication::UnicodeUTF8));
        TextLabel5->setText(QApplication::translate("TextEditor", "in inches", 0, QApplication::UnicodeUTF8));
        leYPos->setText(QApplication::translate("TextEditor", "0.00", 0, QApplication::UnicodeUTF8));
        leXPos->setText(QApplication::translate("TextEditor", "0.00", 0, QApplication::UnicodeUTF8));
        TextLabel1_2->setText(QApplication::translate("TextEditor", "Preview:", 0, QApplication::UnicodeUTF8));
        labelPreview->setText(QApplication::translate("TextEditor", "Preview Area", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("TextEditor", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("TextEditor", "Alt+O", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("TextEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("TextEditor", "Alt+C", 0, QApplication::UnicodeUTF8));
        btnFont->setText(QApplication::translate("TextEditor", "&Font...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TextEditor: public Ui_TextEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITOR_H
