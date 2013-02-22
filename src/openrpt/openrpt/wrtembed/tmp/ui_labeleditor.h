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
** Form generated from reading UI file 'labeleditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELEDITOR_H
#define UI_LABELEDITOR_H

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

QT_BEGIN_NAMESPACE

class Ui_LabelEditor
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *TextLabel1;
    QLineEdit *tbText;
    QHBoxLayout *hboxLayout2;
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
    QGridLayout *gridLayout;
    QLineEdit *leHeight;
    QLineEdit *leWidth;
    QLabel *TextLabel2;
    QLabel *TextLabel4;
    QLabel *TextLabel1_3;
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

    void setupUi(QDialog *LabelEditor)
    {
        if (LabelEditor->objectName().isEmpty())
            LabelEditor->setObjectName(QString::fromUtf8("LabelEditor"));
        LabelEditor->resize(443, 447);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(1));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LabelEditor->sizePolicy().hasHeightForWidth());
        LabelEditor->setSizePolicy(sizePolicy);
        LabelEditor->setSizeGripEnabled(true);
        hboxLayout = new QHBoxLayout(LabelEditor);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        TextLabel1 = new QLabel(LabelEditor);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(1));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TextLabel1->sizePolicy().hasHeightForWidth());
        TextLabel1->setSizePolicy(sizePolicy1);

        hboxLayout1->addWidget(TextLabel1);

        tbText = new QLineEdit(LabelEditor);
        tbText->setObjectName(QString::fromUtf8("tbText"));

        hboxLayout1->addWidget(tbText);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        bgHAlign = new QGroupBox(LabelEditor);
        bgHAlign->setObjectName(QString::fromUtf8("bgHAlign"));
        sizePolicy1.setHeightForWidth(bgHAlign->sizePolicy().hasHeightForWidth());
        bgHAlign->setSizePolicy(sizePolicy1);
        vboxLayout1 = new QVBoxLayout(bgHAlign);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
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


        hboxLayout2->addWidget(bgHAlign);

        bgVAlign = new QGroupBox(LabelEditor);
        bgVAlign->setObjectName(QString::fromUtf8("bgVAlign"));
        sizePolicy1.setHeightForWidth(bgVAlign->sizePolicy().hasHeightForWidth());
        bgVAlign->setSizePolicy(sizePolicy1);
        vboxLayout2 = new QVBoxLayout(bgVAlign);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
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


        hboxLayout2->addWidget(bgVAlign);


        vboxLayout->addLayout(hboxLayout2);

        GroupBox1 = new QGroupBox(LabelEditor);
        GroupBox1->setObjectName(QString::fromUtf8("GroupBox1"));
        gridLayout = new QGridLayout(GroupBox1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        leHeight = new QLineEdit(GroupBox1);
        leHeight->setObjectName(QString::fromUtf8("leHeight"));

        gridLayout->addWidget(leHeight, 1, 3, 1, 1);

        leWidth = new QLineEdit(GroupBox1);
        leWidth->setObjectName(QString::fromUtf8("leWidth"));

        gridLayout->addWidget(leWidth, 0, 3, 1, 1);

        TextLabel2 = new QLabel(GroupBox1);
        TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));

        gridLayout->addWidget(TextLabel2, 1, 0, 1, 1);

        TextLabel4 = new QLabel(GroupBox1);
        TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));

        gridLayout->addWidget(TextLabel4, 1, 2, 1, 1);

        TextLabel1_3 = new QLabel(GroupBox1);
        TextLabel1_3->setObjectName(QString::fromUtf8("TextLabel1_3"));

        gridLayout->addWidget(TextLabel1_3, 0, 0, 1, 1);

        TextLabel3 = new QLabel(GroupBox1);
        TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));

        gridLayout->addWidget(TextLabel3, 0, 2, 1, 1);

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

        gridLayout->addWidget(TextLabel5, 2, 3, 1, 1);

        leYPos = new QLineEdit(GroupBox1);
        leYPos->setObjectName(QString::fromUtf8("leYPos"));

        gridLayout->addWidget(leYPos, 1, 1, 1, 1);

        leXPos = new QLineEdit(GroupBox1);
        leXPos->setObjectName(QString::fromUtf8("leXPos"));

        gridLayout->addWidget(leXPos, 0, 1, 1, 1);


        vboxLayout->addWidget(GroupBox1);

        TextLabel1_2 = new QLabel(LabelEditor);
        TextLabel1_2->setObjectName(QString::fromUtf8("TextLabel1_2"));
        sizePolicy1.setHeightForWidth(TextLabel1_2->sizePolicy().hasHeightForWidth());
        TextLabel1_2->setSizePolicy(sizePolicy1);

        vboxLayout->addWidget(TextLabel1_2);

        labelPreview = new QLabel(LabelEditor);
        labelPreview->setObjectName(QString::fromUtf8("labelPreview"));
        QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(7));
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
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        buttonOk = new QPushButton(LabelEditor);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        vboxLayout3->addWidget(buttonOk);

        buttonCancel = new QPushButton(LabelEditor);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        vboxLayout3->addWidget(buttonCancel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem);

        btnFont = new QPushButton(LabelEditor);
        btnFont->setObjectName(QString::fromUtf8("btnFont"));

        vboxLayout3->addWidget(btnFont);


        hboxLayout->addLayout(vboxLayout3);

        QWidget::setTabOrder(tbText, rbHAlignNone);
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

        retranslateUi(LabelEditor);
        QObject::connect(buttonOk, SIGNAL(clicked()), LabelEditor, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), LabelEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(LabelEditor);
    } // setupUi

    void retranslateUi(QDialog *LabelEditor)
    {
        LabelEditor->setWindowTitle(QApplication::translate("LabelEditor", "Properties (Label)", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("LabelEditor", "Text:", 0, QApplication::UnicodeUTF8));
        bgHAlign->setTitle(QApplication::translate("LabelEditor", "HAlign", 0, QApplication::UnicodeUTF8));
        rbHAlignNone->setText(QApplication::translate("LabelEditor", "None", 0, QApplication::UnicodeUTF8));
        rbHAlignLeft->setText(QApplication::translate("LabelEditor", "Left", 0, QApplication::UnicodeUTF8));
        rbHAlignCenter->setText(QApplication::translate("LabelEditor", "Center", 0, QApplication::UnicodeUTF8));
        rbHAlignRight->setText(QApplication::translate("LabelEditor", "Right", 0, QApplication::UnicodeUTF8));
        bgVAlign->setTitle(QApplication::translate("LabelEditor", "VAlign", 0, QApplication::UnicodeUTF8));
        rbVAlignNone->setText(QApplication::translate("LabelEditor", "None", 0, QApplication::UnicodeUTF8));
        rbVAlignTop->setText(QApplication::translate("LabelEditor", "Top", 0, QApplication::UnicodeUTF8));
        rbVAlignMiddle->setText(QApplication::translate("LabelEditor", "Middle", 0, QApplication::UnicodeUTF8));
        rbVAlignBottom->setText(QApplication::translate("LabelEditor", "Bottom", 0, QApplication::UnicodeUTF8));
        GroupBox1->setTitle(QApplication::translate("LabelEditor", "Position/Size", 0, QApplication::UnicodeUTF8));
        leHeight->setText(QApplication::translate("LabelEditor", "0.01", 0, QApplication::UnicodeUTF8));
        leWidth->setText(QApplication::translate("LabelEditor", "0.01", 0, QApplication::UnicodeUTF8));
        TextLabel2->setText(QApplication::translate("LabelEditor", "Y:", 0, QApplication::UnicodeUTF8));
        TextLabel4->setText(QApplication::translate("LabelEditor", "Height:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3->setText(QApplication::translate("LabelEditor", "X:", 0, QApplication::UnicodeUTF8));
        TextLabel3->setText(QApplication::translate("LabelEditor", "Width:", 0, QApplication::UnicodeUTF8));
        TextLabel5->setText(QApplication::translate("LabelEditor", "in inches", 0, QApplication::UnicodeUTF8));
        leYPos->setText(QApplication::translate("LabelEditor", "0.00", 0, QApplication::UnicodeUTF8));
        leXPos->setText(QApplication::translate("LabelEditor", "0.00", 0, QApplication::UnicodeUTF8));
        TextLabel1_2->setText(QApplication::translate("LabelEditor", "Preview:", 0, QApplication::UnicodeUTF8));
        labelPreview->setText(QApplication::translate("LabelEditor", "Preview Area", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("LabelEditor", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("LabelEditor", "Alt+O", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("LabelEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("LabelEditor", "Alt+C", 0, QApplication::UnicodeUTF8));
        btnFont->setText(QApplication::translate("LabelEditor", "&Font...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LabelEditor: public Ui_LabelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELEDITOR_H
