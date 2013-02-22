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
** Form generated from reading UI file 'fieldeditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIELDEDITOR_H
#define UI_FIELDEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
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

class Ui_FieldEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *tbColumn;
    QLabel *TextLabel1_3;
    QLabel *TextLabel1;
    QueryComboBox *cbQuery;
    QCheckBox *_cbRTotal;
    QCheckBox *_cbSubTotal;
    QGroupBox *_gbFormat;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QRadioButton *_rbStringFormat;
    QLineEdit *_leRTotalFormat;
    QLabel *_lblRTotalExample;
    QHBoxLayout *hboxLayout1;
    QRadioButton *_rbBuiltinFormat;
    QComboBox *_cbBuiltinFormat;
    QGroupBox *GroupBox_Array;
    QGridLayout *_3;
    QLineEdit *leColumns;
    QLabel *TextLabel2_2;
    QLabel *TextLabel1_3_3;
    QLineEdit *leLines;
    QSpacerItem *horizontalSpacer;
    QLabel *TextLabel2_3;
    QLabel *TextLabel1_3_4;
    QLineEdit *leXSpacing;
    QLineEdit *leYSpacing;
    QCheckBox *_cbPageBreak;
    QCheckBox *_cbLeftToRight;
    QSpacerItem *horizontalSpacer_3;
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
    QCheckBox *_cbWordWrap;
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
    QSpacerItem *horizontalSpacer_2;
    QLabel *TextLabel1_2;
    QLabel *labelPreview;
    QVBoxLayout *vboxLayout3;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QSpacerItem *spacerItem;
    QPushButton *btnFont;

    void setupUi(QDialog *FieldEditor)
    {
        if (FieldEditor->objectName().isEmpty())
            FieldEditor->setObjectName(QString::fromUtf8("FieldEditor"));
        FieldEditor->resize(691, 712);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FieldEditor->sizePolicy().hasHeightForWidth());
        FieldEditor->setSizePolicy(sizePolicy);
        FieldEditor->setSizeGripEnabled(true);
        horizontalLayout = new QHBoxLayout(FieldEditor);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tbColumn = new QLineEdit(FieldEditor);
        tbColumn->setObjectName(QString::fromUtf8("tbColumn"));

        gridLayout->addWidget(tbColumn, 1, 1, 1, 1);

        TextLabel1_3 = new QLabel(FieldEditor);
        TextLabel1_3->setObjectName(QString::fromUtf8("TextLabel1_3"));

        gridLayout->addWidget(TextLabel1_3, 0, 0, 1, 1);

        TextLabel1 = new QLabel(FieldEditor);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TextLabel1->sizePolicy().hasHeightForWidth());
        TextLabel1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(TextLabel1, 1, 0, 1, 1);

        cbQuery = new QueryComboBox(FieldEditor);
        cbQuery->setObjectName(QString::fromUtf8("cbQuery"));

        gridLayout->addWidget(cbQuery, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        _cbRTotal = new QCheckBox(FieldEditor);
        _cbRTotal->setObjectName(QString::fromUtf8("_cbRTotal"));

        verticalLayout->addWidget(_cbRTotal);

        _cbSubTotal = new QCheckBox(FieldEditor);
        _cbSubTotal->setObjectName(QString::fromUtf8("_cbSubTotal"));
        _cbSubTotal->setEnabled(false);

        verticalLayout->addWidget(_cbSubTotal);

        _gbFormat = new QGroupBox(FieldEditor);
        _gbFormat->setObjectName(QString::fromUtf8("_gbFormat"));
        vboxLayout = new QVBoxLayout(_gbFormat);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        _rbStringFormat = new QRadioButton(_gbFormat);
        _rbStringFormat->setObjectName(QString::fromUtf8("_rbStringFormat"));
        _rbStringFormat->setChecked(true);

        hboxLayout->addWidget(_rbStringFormat);

        _leRTotalFormat = new QLineEdit(_gbFormat);
        _leRTotalFormat->setObjectName(QString::fromUtf8("_leRTotalFormat"));

        hboxLayout->addWidget(_leRTotalFormat);

        _lblRTotalExample = new QLabel(_gbFormat);
        _lblRTotalExample->setObjectName(QString::fromUtf8("_lblRTotalExample"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(_lblRTotalExample->sizePolicy().hasHeightForWidth());
        _lblRTotalExample->setSizePolicy(sizePolicy2);
        _lblRTotalExample->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout->addWidget(_lblRTotalExample);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        _rbBuiltinFormat = new QRadioButton(_gbFormat);
        _rbBuiltinFormat->setObjectName(QString::fromUtf8("_rbBuiltinFormat"));

        hboxLayout1->addWidget(_rbBuiltinFormat);

        _cbBuiltinFormat = new QComboBox(_gbFormat);
        _cbBuiltinFormat->setObjectName(QString::fromUtf8("_cbBuiltinFormat"));
        _cbBuiltinFormat->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(_cbBuiltinFormat->sizePolicy().hasHeightForWidth());
        _cbBuiltinFormat->setSizePolicy(sizePolicy3);

        hboxLayout1->addWidget(_cbBuiltinFormat);


        vboxLayout->addLayout(hboxLayout1);


        verticalLayout->addWidget(_gbFormat);

        GroupBox_Array = new QGroupBox(FieldEditor);
        GroupBox_Array->setObjectName(QString::fromUtf8("GroupBox_Array"));
        _3 = new QGridLayout(GroupBox_Array);
        _3->setSpacing(6);
        _3->setContentsMargins(11, 11, 11, 11);
        _3->setObjectName(QString::fromUtf8("_3"));
        leColumns = new QLineEdit(GroupBox_Array);
        leColumns->setObjectName(QString::fromUtf8("leColumns"));
        leColumns->setMaximumSize(QSize(16777215, 16777215));

        _3->addWidget(leColumns, 1, 1, 1, 1);

        TextLabel2_2 = new QLabel(GroupBox_Array);
        TextLabel2_2->setObjectName(QString::fromUtf8("TextLabel2_2"));

        _3->addWidget(TextLabel2_2, 1, 0, 1, 1);

        TextLabel1_3_3 = new QLabel(GroupBox_Array);
        TextLabel1_3_3->setObjectName(QString::fromUtf8("TextLabel1_3_3"));

        _3->addWidget(TextLabel1_3_3, 0, 0, 1, 1);

        leLines = new QLineEdit(GroupBox_Array);
        leLines->setObjectName(QString::fromUtf8("leLines"));
        leLines->setMaximumSize(QSize(16777215, 16777215));

        _3->addWidget(leLines, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _3->addItem(horizontalSpacer, 0, 2, 3, 1);

        TextLabel2_3 = new QLabel(GroupBox_Array);
        TextLabel2_3->setObjectName(QString::fromUtf8("TextLabel2_3"));

        _3->addWidget(TextLabel2_3, 0, 4, 1, 1);

        TextLabel1_3_4 = new QLabel(GroupBox_Array);
        TextLabel1_3_4->setObjectName(QString::fromUtf8("TextLabel1_3_4"));

        _3->addWidget(TextLabel1_3_4, 1, 4, 1, 1);

        leXSpacing = new QLineEdit(GroupBox_Array);
        leXSpacing->setObjectName(QString::fromUtf8("leXSpacing"));
        leXSpacing->setMaximumSize(QSize(16777215, 16777215));

        _3->addWidget(leXSpacing, 0, 5, 1, 1);

        leYSpacing = new QLineEdit(GroupBox_Array);
        leYSpacing->setObjectName(QString::fromUtf8("leYSpacing"));
        leYSpacing->setMaximumSize(QSize(16777215, 16777215));

        _3->addWidget(leYSpacing, 1, 5, 1, 1);

        _cbPageBreak = new QCheckBox(GroupBox_Array);
        _cbPageBreak->setObjectName(QString::fromUtf8("_cbPageBreak"));

        _3->addWidget(_cbPageBreak, 0, 7, 1, 1);

        _cbLeftToRight = new QCheckBox(GroupBox_Array);
        _cbLeftToRight->setObjectName(QString::fromUtf8("_cbLeftToRight"));

        _3->addWidget(_cbLeftToRight, 1, 7, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _3->addItem(horizontalSpacer_3, 0, 6, 1, 1);


        verticalLayout->addWidget(GroupBox_Array);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        bgHAlign = new QGroupBox(FieldEditor);
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

        bgVAlign = new QGroupBox(FieldEditor);
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


        verticalLayout->addLayout(hboxLayout2);

        _cbWordWrap = new QCheckBox(FieldEditor);
        _cbWordWrap->setObjectName(QString::fromUtf8("_cbWordWrap"));

        verticalLayout->addWidget(_cbWordWrap);

        GroupBox1 = new QGroupBox(FieldEditor);
        GroupBox1->setObjectName(QString::fromUtf8("GroupBox1"));
        gridLayout1 = new QGridLayout(GroupBox1);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        leHeight = new QLineEdit(GroupBox1);
        leHeight->setObjectName(QString::fromUtf8("leHeight"));

        gridLayout1->addWidget(leHeight, 1, 4, 1, 1);

        leWidth = new QLineEdit(GroupBox1);
        leWidth->setObjectName(QString::fromUtf8("leWidth"));

        gridLayout1->addWidget(leWidth, 0, 4, 1, 1);

        TextLabel2 = new QLabel(GroupBox1);
        TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));

        gridLayout1->addWidget(TextLabel2, 1, 0, 1, 1);

        TextLabel4 = new QLabel(GroupBox1);
        TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));

        gridLayout1->addWidget(TextLabel4, 1, 3, 1, 1);

        TextLabel1_3_2 = new QLabel(GroupBox1);
        TextLabel1_3_2->setObjectName(QString::fromUtf8("TextLabel1_3_2"));

        gridLayout1->addWidget(TextLabel1_3_2, 0, 0, 1, 1);

        TextLabel3 = new QLabel(GroupBox1);
        TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));

        gridLayout1->addWidget(TextLabel3, 0, 3, 1, 1);

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

        gridLayout1->addWidget(TextLabel5, 2, 4, 1, 1);

        leYPos = new QLineEdit(GroupBox1);
        leYPos->setObjectName(QString::fromUtf8("leYPos"));

        gridLayout1->addWidget(leYPos, 1, 1, 1, 1);

        leXPos = new QLineEdit(GroupBox1);
        leXPos->setObjectName(QString::fromUtf8("leXPos"));

        gridLayout1->addWidget(leXPos, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        verticalLayout->addWidget(GroupBox1);

        TextLabel1_2 = new QLabel(FieldEditor);
        TextLabel1_2->setObjectName(QString::fromUtf8("TextLabel1_2"));
        sizePolicy1.setHeightForWidth(TextLabel1_2->sizePolicy().hasHeightForWidth());
        TextLabel1_2->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(TextLabel1_2);

        labelPreview = new QLabel(FieldEditor);
        labelPreview->setObjectName(QString::fromUtf8("labelPreview"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelPreview->sizePolicy().hasHeightForWidth());
        labelPreview->setSizePolicy(sizePolicy4);
        labelPreview->setMinimumSize(QSize(0, 42));
        labelPreview->setFrameShape(QFrame::StyledPanel);
        labelPreview->setFrameShadow(QFrame::Sunken);
        labelPreview->setAlignment(Qt::AlignVCenter);

        verticalLayout->addWidget(labelPreview);


        horizontalLayout->addLayout(verticalLayout);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        buttonOk = new QPushButton(FieldEditor);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        vboxLayout3->addWidget(buttonOk);

        buttonCancel = new QPushButton(FieldEditor);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        vboxLayout3->addWidget(buttonCancel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem);

        btnFont = new QPushButton(FieldEditor);
        btnFont->setObjectName(QString::fromUtf8("btnFont"));

        vboxLayout3->addWidget(btnFont);


        horizontalLayout->addLayout(vboxLayout3);

        QWidget::setTabOrder(cbQuery, tbColumn);
        QWidget::setTabOrder(tbColumn, _cbRTotal);
        QWidget::setTabOrder(_cbRTotal, _rbStringFormat);
        QWidget::setTabOrder(_rbStringFormat, _leRTotalFormat);
        QWidget::setTabOrder(_leRTotalFormat, _rbBuiltinFormat);
        QWidget::setTabOrder(_rbBuiltinFormat, _cbBuiltinFormat);
        QWidget::setTabOrder(_cbBuiltinFormat, rbHAlignNone);
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

        retranslateUi(FieldEditor);
        QObject::connect(buttonOk, SIGNAL(clicked()), FieldEditor, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), FieldEditor, SLOT(reject()));
        QObject::connect(_cbRTotal, SIGNAL(toggled(bool)), _gbFormat, SLOT(setEnabled(bool)));
        QObject::connect(_rbStringFormat, SIGNAL(toggled(bool)), _leRTotalFormat, SLOT(setEnabled(bool)));
        QObject::connect(_rbStringFormat, SIGNAL(toggled(bool)), _lblRTotalExample, SLOT(setEnabled(bool)));
        QObject::connect(_rbBuiltinFormat, SIGNAL(toggled(bool)), _cbBuiltinFormat, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(FieldEditor);
    } // setupUi

    void retranslateUi(QDialog *FieldEditor)
    {
        FieldEditor->setWindowTitle(QApplication::translate("FieldEditor", "Properties (Field)", 0, QApplication::UnicodeUTF8));
        TextLabel1_3->setText(QApplication::translate("FieldEditor", "Query Source:", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("FieldEditor", "Column:", 0, QApplication::UnicodeUTF8));
        _cbRTotal->setText(QApplication::translate("FieldEditor", "Display as Running Total", 0, QApplication::UnicodeUTF8));
        _cbSubTotal->setText(QApplication::translate("FieldEditor", "Use Subtotal Value", 0, QApplication::UnicodeUTF8));
        _gbFormat->setTitle(QApplication::translate("FieldEditor", "Format", 0, QApplication::UnicodeUTF8));
        _rbStringFormat->setText(QApplication::translate("FieldEditor", "String Format ", 0, QApplication::UnicodeUTF8));
        _lblRTotalExample->setText(QApplication::translate("FieldEditor", "Example: %0.2f", 0, QApplication::UnicodeUTF8));
        _rbBuiltinFormat->setText(QApplication::translate("FieldEditor", "Built-in Locale Format", 0, QApplication::UnicodeUTF8));
        GroupBox_Array->setTitle(QApplication::translate("FieldEditor", "Array", 0, QApplication::UnicodeUTF8));
        leColumns->setText(QApplication::translate("FieldEditor", "1", 0, QApplication::UnicodeUTF8));
        TextLabel2_2->setText(QApplication::translate("FieldEditor", "Columns:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3_3->setText(QApplication::translate("FieldEditor", "Lines:", 0, QApplication::UnicodeUTF8));
        leLines->setText(QApplication::translate("FieldEditor", "1", 0, QApplication::UnicodeUTF8));
        TextLabel2_3->setText(QApplication::translate("FieldEditor", "H spacing:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3_4->setText(QApplication::translate("FieldEditor", "V spacing:", 0, QApplication::UnicodeUTF8));
        leXSpacing->setText(QApplication::translate("FieldEditor", "0", 0, QApplication::UnicodeUTF8));
        leYSpacing->setText(QApplication::translate("FieldEditor", "0", 0, QApplication::UnicodeUTF8));
        _cbPageBreak->setText(QApplication::translate("FieldEditor", "Page break", 0, QApplication::UnicodeUTF8));
        _cbLeftToRight->setText(QApplication::translate("FieldEditor", "Fill columns first", 0, QApplication::UnicodeUTF8));
        bgHAlign->setTitle(QApplication::translate("FieldEditor", "HAlign", 0, QApplication::UnicodeUTF8));
        rbHAlignNone->setText(QApplication::translate("FieldEditor", "None", 0, QApplication::UnicodeUTF8));
        rbHAlignLeft->setText(QApplication::translate("FieldEditor", "Left", 0, QApplication::UnicodeUTF8));
        rbHAlignCenter->setText(QApplication::translate("FieldEditor", "Center", 0, QApplication::UnicodeUTF8));
        rbHAlignRight->setText(QApplication::translate("FieldEditor", "Right", 0, QApplication::UnicodeUTF8));
        bgVAlign->setTitle(QApplication::translate("FieldEditor", "VAlign", 0, QApplication::UnicodeUTF8));
        rbVAlignNone->setText(QApplication::translate("FieldEditor", "None", 0, QApplication::UnicodeUTF8));
        rbVAlignTop->setText(QApplication::translate("FieldEditor", "Top", 0, QApplication::UnicodeUTF8));
        rbVAlignMiddle->setText(QApplication::translate("FieldEditor", "Middle", 0, QApplication::UnicodeUTF8));
        rbVAlignBottom->setText(QApplication::translate("FieldEditor", "Bottom", 0, QApplication::UnicodeUTF8));
        _cbWordWrap->setText(QApplication::translate("FieldEditor", "Word wrap", 0, QApplication::UnicodeUTF8));
        GroupBox1->setTitle(QApplication::translate("FieldEditor", "Position/Size", 0, QApplication::UnicodeUTF8));
        leHeight->setText(QApplication::translate("FieldEditor", "0.01", 0, QApplication::UnicodeUTF8));
        leWidth->setText(QApplication::translate("FieldEditor", "0.01", 0, QApplication::UnicodeUTF8));
        TextLabel2->setText(QApplication::translate("FieldEditor", "Y:", 0, QApplication::UnicodeUTF8));
        TextLabel4->setText(QApplication::translate("FieldEditor", "Height:", 0, QApplication::UnicodeUTF8));
        TextLabel1_3_2->setText(QApplication::translate("FieldEditor", "X:", 0, QApplication::UnicodeUTF8));
        TextLabel3->setText(QApplication::translate("FieldEditor", "Width:", 0, QApplication::UnicodeUTF8));
        TextLabel5->setText(QApplication::translate("FieldEditor", "in inches", 0, QApplication::UnicodeUTF8));
        leYPos->setText(QApplication::translate("FieldEditor", "0.00", 0, QApplication::UnicodeUTF8));
        leXPos->setText(QApplication::translate("FieldEditor", "0.00", 0, QApplication::UnicodeUTF8));
        TextLabel1_2->setText(QApplication::translate("FieldEditor", "Preview:", 0, QApplication::UnicodeUTF8));
        labelPreview->setText(QApplication::translate("FieldEditor", "Preview Area", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("FieldEditor", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("FieldEditor", "Alt+O", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("FieldEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("FieldEditor", "Alt+C", 0, QApplication::UnicodeUTF8));
        btnFont->setText(QApplication::translate("FieldEditor", "&Font...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FieldEditor: public Ui_FieldEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIELDEDITOR_H
