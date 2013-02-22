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
** Form generated from reading UI file 'crosstabeditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROSSTABEDITOR_H
#define UI_CROSSTABEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include "querycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_CrossTabEditor
{
public:
    QGridLayout *gridLayout_9;
    QLabel *TextLabel1_3;
    QueryComboBox *cbQuery;
    QGroupBox *m_tablePropertiesGroupBox;
    QGridLayout *gridLayout_7;
    QGroupBox *m_TableCellMarginsGroupBox;
    QGridLayout *gridLayout_4;
    QLabel *m_cellLeftMarginLabel;
    QDoubleSpinBox *m_cellLeftMarginDoubleSpinBox;
    QLabel *m_cellRightMarginLabel;
    QDoubleSpinBox *m_cellRightMarginDoubleSpinBox;
    QLabel *m_cellTopMarginLabel;
    QDoubleSpinBox *m_cellTopMarginDoubleSpinBox;
    QLabel *m_cellBottomMarginLabel;
    QDoubleSpinBox *m_cellBottomMarginDoubleSpinBox;
    QGroupBox *m_tableWrappingPolicyGroupBox;
    QGridLayout *gridLayout_5;
    QRadioButton *m_wrapRowsFirstRadioButton;
    QRadioButton *m_wrapColumnsFirstRadioButton;
    QGroupBox *m_tableDisplayHeaderGroupBox;
    QGridLayout *gridLayout_6;
    QCheckBox *m_tableDisplayColumnHeaderCheckBox;
    QCheckBox *m_tableDisplayRowHeaderCheckBox;
    QPushButton *btnFont;
    QGridLayout *gridLayout_8;
    QGroupBox *columnQueryGroupBox;
    QGridLayout *gridLayout;
    QLabel *columnQueryColumnTextLabel;
    QLineEdit *columnQueryLineEdit;
    QLabel *columnQueryHAlignTextLabel;
    QComboBox *columnQueryHAlignComboBox;
    QLabel *columnQueryVAlignTextLabel;
    QComboBox *columnQueryVAlignComboBox;
    QGroupBox *rowQueryGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *rowQueryColumnTextLabel;
    QLineEdit *rowQueryLineEdit;
    QLabel *rowQueryHAlignTextLabel;
    QComboBox *rowQueryHAlignComboBox;
    QLabel *rowQueryVAlignTextLabel;
    QComboBox *rowQueryVAlignComboBox;
    QGroupBox *valueQueryGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *valueQueryColumnTextLabel;
    QLineEdit *valueQueryLineEdit;
    QLabel *valueQueryHAlignTextLabel;
    QComboBox *valueQueryHAlignComboBox;
    QLabel *valueQueryVAlignTextLabel;
    QComboBox *valueQueryVAlignComboBox;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *CrossTabEditor)
    {
        if (CrossTabEditor->objectName().isEmpty())
            CrossTabEditor->setObjectName(QString::fromUtf8("CrossTabEditor"));
        CrossTabEditor->resize(551, 497);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CrossTabEditor->sizePolicy().hasHeightForWidth());
        CrossTabEditor->setSizePolicy(sizePolicy);
        CrossTabEditor->setSizeGripEnabled(true);
        gridLayout_9 = new QGridLayout(CrossTabEditor);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        TextLabel1_3 = new QLabel(CrossTabEditor);
        TextLabel1_3->setObjectName(QString::fromUtf8("TextLabel1_3"));

        gridLayout_9->addWidget(TextLabel1_3, 0, 0, 1, 1);

        cbQuery = new QueryComboBox(CrossTabEditor);
        cbQuery->setObjectName(QString::fromUtf8("cbQuery"));

        gridLayout_9->addWidget(cbQuery, 0, 1, 1, 2);

        m_tablePropertiesGroupBox = new QGroupBox(CrossTabEditor);
        m_tablePropertiesGroupBox->setObjectName(QString::fromUtf8("m_tablePropertiesGroupBox"));
        gridLayout_7 = new QGridLayout(m_tablePropertiesGroupBox);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        m_TableCellMarginsGroupBox = new QGroupBox(m_tablePropertiesGroupBox);
        m_TableCellMarginsGroupBox->setObjectName(QString::fromUtf8("m_TableCellMarginsGroupBox"));
        gridLayout_4 = new QGridLayout(m_TableCellMarginsGroupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_cellLeftMarginLabel = new QLabel(m_TableCellMarginsGroupBox);
        m_cellLeftMarginLabel->setObjectName(QString::fromUtf8("m_cellLeftMarginLabel"));

        gridLayout_4->addWidget(m_cellLeftMarginLabel, 0, 0, 1, 1);

        m_cellLeftMarginDoubleSpinBox = new QDoubleSpinBox(m_TableCellMarginsGroupBox);
        m_cellLeftMarginDoubleSpinBox->setObjectName(QString::fromUtf8("m_cellLeftMarginDoubleSpinBox"));
        m_cellLeftMarginDoubleSpinBox->setSingleStep(0.01);
        m_cellLeftMarginDoubleSpinBox->setValue(0.02);

        gridLayout_4->addWidget(m_cellLeftMarginDoubleSpinBox, 0, 1, 1, 1);

        m_cellRightMarginLabel = new QLabel(m_TableCellMarginsGroupBox);
        m_cellRightMarginLabel->setObjectName(QString::fromUtf8("m_cellRightMarginLabel"));

        gridLayout_4->addWidget(m_cellRightMarginLabel, 0, 2, 1, 1);

        m_cellRightMarginDoubleSpinBox = new QDoubleSpinBox(m_TableCellMarginsGroupBox);
        m_cellRightMarginDoubleSpinBox->setObjectName(QString::fromUtf8("m_cellRightMarginDoubleSpinBox"));
        m_cellRightMarginDoubleSpinBox->setSingleStep(0.01);
        m_cellRightMarginDoubleSpinBox->setValue(0.02);

        gridLayout_4->addWidget(m_cellRightMarginDoubleSpinBox, 0, 3, 1, 1);

        m_cellTopMarginLabel = new QLabel(m_TableCellMarginsGroupBox);
        m_cellTopMarginLabel->setObjectName(QString::fromUtf8("m_cellTopMarginLabel"));

        gridLayout_4->addWidget(m_cellTopMarginLabel, 1, 0, 1, 1);

        m_cellTopMarginDoubleSpinBox = new QDoubleSpinBox(m_TableCellMarginsGroupBox);
        m_cellTopMarginDoubleSpinBox->setObjectName(QString::fromUtf8("m_cellTopMarginDoubleSpinBox"));
        m_cellTopMarginDoubleSpinBox->setSingleStep(0.01);
        m_cellTopMarginDoubleSpinBox->setValue(0.02);

        gridLayout_4->addWidget(m_cellTopMarginDoubleSpinBox, 1, 1, 1, 1);

        m_cellBottomMarginLabel = new QLabel(m_TableCellMarginsGroupBox);
        m_cellBottomMarginLabel->setObjectName(QString::fromUtf8("m_cellBottomMarginLabel"));

        gridLayout_4->addWidget(m_cellBottomMarginLabel, 1, 2, 1, 1);

        m_cellBottomMarginDoubleSpinBox = new QDoubleSpinBox(m_TableCellMarginsGroupBox);
        m_cellBottomMarginDoubleSpinBox->setObjectName(QString::fromUtf8("m_cellBottomMarginDoubleSpinBox"));
        m_cellBottomMarginDoubleSpinBox->setSingleStep(0.01);
        m_cellBottomMarginDoubleSpinBox->setValue(0.02);

        gridLayout_4->addWidget(m_cellBottomMarginDoubleSpinBox, 1, 3, 1, 1);


        gridLayout_7->addWidget(m_TableCellMarginsGroupBox, 0, 0, 1, 1);

        m_tableWrappingPolicyGroupBox = new QGroupBox(m_tablePropertiesGroupBox);
        m_tableWrappingPolicyGroupBox->setObjectName(QString::fromUtf8("m_tableWrappingPolicyGroupBox"));
        gridLayout_5 = new QGridLayout(m_tableWrappingPolicyGroupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_wrapRowsFirstRadioButton = new QRadioButton(m_tableWrappingPolicyGroupBox);
        m_wrapRowsFirstRadioButton->setObjectName(QString::fromUtf8("m_wrapRowsFirstRadioButton"));
        m_wrapRowsFirstRadioButton->setChecked(true);

        gridLayout_5->addWidget(m_wrapRowsFirstRadioButton, 0, 0, 1, 1);

        m_wrapColumnsFirstRadioButton = new QRadioButton(m_tableWrappingPolicyGroupBox);
        m_wrapColumnsFirstRadioButton->setObjectName(QString::fromUtf8("m_wrapColumnsFirstRadioButton"));

        gridLayout_5->addWidget(m_wrapColumnsFirstRadioButton, 1, 0, 1, 1);


        gridLayout_7->addWidget(m_tableWrappingPolicyGroupBox, 0, 1, 1, 1);

        m_tableDisplayHeaderGroupBox = new QGroupBox(m_tablePropertiesGroupBox);
        m_tableDisplayHeaderGroupBox->setObjectName(QString::fromUtf8("m_tableDisplayHeaderGroupBox"));
        gridLayout_6 = new QGridLayout(m_tableDisplayHeaderGroupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        m_tableDisplayColumnHeaderCheckBox = new QCheckBox(m_tableDisplayHeaderGroupBox);
        m_tableDisplayColumnHeaderCheckBox->setObjectName(QString::fromUtf8("m_tableDisplayColumnHeaderCheckBox"));
        m_tableDisplayColumnHeaderCheckBox->setChecked(true);

        gridLayout_6->addWidget(m_tableDisplayColumnHeaderCheckBox, 0, 0, 1, 1);

        m_tableDisplayRowHeaderCheckBox = new QCheckBox(m_tableDisplayHeaderGroupBox);
        m_tableDisplayRowHeaderCheckBox->setObjectName(QString::fromUtf8("m_tableDisplayRowHeaderCheckBox"));
        m_tableDisplayRowHeaderCheckBox->setChecked(true);

        gridLayout_6->addWidget(m_tableDisplayRowHeaderCheckBox, 1, 0, 1, 1);


        gridLayout_7->addWidget(m_tableDisplayHeaderGroupBox, 1, 0, 1, 1);

        btnFont = new QPushButton(m_tablePropertiesGroupBox);
        btnFont->setObjectName(QString::fromUtf8("btnFont"));

        gridLayout_7->addWidget(btnFont, 1, 1, 1, 1);


        gridLayout_9->addWidget(m_tablePropertiesGroupBox, 1, 0, 1, 3);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        columnQueryGroupBox = new QGroupBox(CrossTabEditor);
        columnQueryGroupBox->setObjectName(QString::fromUtf8("columnQueryGroupBox"));
        gridLayout = new QGridLayout(columnQueryGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        columnQueryColumnTextLabel = new QLabel(columnQueryGroupBox);
        columnQueryColumnTextLabel->setObjectName(QString::fromUtf8("columnQueryColumnTextLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(columnQueryColumnTextLabel->sizePolicy().hasHeightForWidth());
        columnQueryColumnTextLabel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(columnQueryColumnTextLabel, 0, 0, 1, 1);

        columnQueryLineEdit = new QLineEdit(columnQueryGroupBox);
        columnQueryLineEdit->setObjectName(QString::fromUtf8("columnQueryLineEdit"));

        gridLayout->addWidget(columnQueryLineEdit, 0, 1, 1, 1);

        columnQueryHAlignTextLabel = new QLabel(columnQueryGroupBox);
        columnQueryHAlignTextLabel->setObjectName(QString::fromUtf8("columnQueryHAlignTextLabel"));
        sizePolicy1.setHeightForWidth(columnQueryHAlignTextLabel->sizePolicy().hasHeightForWidth());
        columnQueryHAlignTextLabel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(columnQueryHAlignTextLabel, 1, 0, 1, 1);

        columnQueryHAlignComboBox = new QComboBox(columnQueryGroupBox);
        columnQueryHAlignComboBox->setObjectName(QString::fromUtf8("columnQueryHAlignComboBox"));

        gridLayout->addWidget(columnQueryHAlignComboBox, 1, 1, 1, 1);

        columnQueryVAlignTextLabel = new QLabel(columnQueryGroupBox);
        columnQueryVAlignTextLabel->setObjectName(QString::fromUtf8("columnQueryVAlignTextLabel"));
        sizePolicy1.setHeightForWidth(columnQueryVAlignTextLabel->sizePolicy().hasHeightForWidth());
        columnQueryVAlignTextLabel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(columnQueryVAlignTextLabel, 2, 0, 1, 1);

        columnQueryVAlignComboBox = new QComboBox(columnQueryGroupBox);
        columnQueryVAlignComboBox->setObjectName(QString::fromUtf8("columnQueryVAlignComboBox"));

        gridLayout->addWidget(columnQueryVAlignComboBox, 2, 1, 1, 1);


        gridLayout_8->addWidget(columnQueryGroupBox, 0, 1, 1, 1);

        rowQueryGroupBox = new QGroupBox(CrossTabEditor);
        rowQueryGroupBox->setObjectName(QString::fromUtf8("rowQueryGroupBox"));
        gridLayout_2 = new QGridLayout(rowQueryGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rowQueryColumnTextLabel = new QLabel(rowQueryGroupBox);
        rowQueryColumnTextLabel->setObjectName(QString::fromUtf8("rowQueryColumnTextLabel"));
        sizePolicy1.setHeightForWidth(rowQueryColumnTextLabel->sizePolicy().hasHeightForWidth());
        rowQueryColumnTextLabel->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(rowQueryColumnTextLabel, 0, 0, 1, 1);

        rowQueryLineEdit = new QLineEdit(rowQueryGroupBox);
        rowQueryLineEdit->setObjectName(QString::fromUtf8("rowQueryLineEdit"));

        gridLayout_2->addWidget(rowQueryLineEdit, 0, 1, 1, 1);

        rowQueryHAlignTextLabel = new QLabel(rowQueryGroupBox);
        rowQueryHAlignTextLabel->setObjectName(QString::fromUtf8("rowQueryHAlignTextLabel"));
        sizePolicy1.setHeightForWidth(rowQueryHAlignTextLabel->sizePolicy().hasHeightForWidth());
        rowQueryHAlignTextLabel->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(rowQueryHAlignTextLabel, 1, 0, 1, 1);

        rowQueryHAlignComboBox = new QComboBox(rowQueryGroupBox);
        rowQueryHAlignComboBox->setObjectName(QString::fromUtf8("rowQueryHAlignComboBox"));

        gridLayout_2->addWidget(rowQueryHAlignComboBox, 1, 1, 1, 1);

        rowQueryVAlignTextLabel = new QLabel(rowQueryGroupBox);
        rowQueryVAlignTextLabel->setObjectName(QString::fromUtf8("rowQueryVAlignTextLabel"));
        sizePolicy1.setHeightForWidth(rowQueryVAlignTextLabel->sizePolicy().hasHeightForWidth());
        rowQueryVAlignTextLabel->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(rowQueryVAlignTextLabel, 2, 0, 1, 1);

        rowQueryVAlignComboBox = new QComboBox(rowQueryGroupBox);
        rowQueryVAlignComboBox->setObjectName(QString::fromUtf8("rowQueryVAlignComboBox"));

        gridLayout_2->addWidget(rowQueryVAlignComboBox, 2, 1, 1, 1);


        gridLayout_8->addWidget(rowQueryGroupBox, 1, 0, 1, 1);

        valueQueryGroupBox = new QGroupBox(CrossTabEditor);
        valueQueryGroupBox->setObjectName(QString::fromUtf8("valueQueryGroupBox"));
        gridLayout_3 = new QGridLayout(valueQueryGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        valueQueryColumnTextLabel = new QLabel(valueQueryGroupBox);
        valueQueryColumnTextLabel->setObjectName(QString::fromUtf8("valueQueryColumnTextLabel"));
        sizePolicy1.setHeightForWidth(valueQueryColumnTextLabel->sizePolicy().hasHeightForWidth());
        valueQueryColumnTextLabel->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(valueQueryColumnTextLabel, 0, 0, 1, 1);

        valueQueryLineEdit = new QLineEdit(valueQueryGroupBox);
        valueQueryLineEdit->setObjectName(QString::fromUtf8("valueQueryLineEdit"));

        gridLayout_3->addWidget(valueQueryLineEdit, 0, 1, 1, 1);

        valueQueryHAlignTextLabel = new QLabel(valueQueryGroupBox);
        valueQueryHAlignTextLabel->setObjectName(QString::fromUtf8("valueQueryHAlignTextLabel"));
        sizePolicy1.setHeightForWidth(valueQueryHAlignTextLabel->sizePolicy().hasHeightForWidth());
        valueQueryHAlignTextLabel->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(valueQueryHAlignTextLabel, 1, 0, 1, 1);

        valueQueryHAlignComboBox = new QComboBox(valueQueryGroupBox);
        valueQueryHAlignComboBox->setObjectName(QString::fromUtf8("valueQueryHAlignComboBox"));

        gridLayout_3->addWidget(valueQueryHAlignComboBox, 1, 1, 1, 1);

        valueQueryVAlignTextLabel = new QLabel(valueQueryGroupBox);
        valueQueryVAlignTextLabel->setObjectName(QString::fromUtf8("valueQueryVAlignTextLabel"));
        sizePolicy1.setHeightForWidth(valueQueryVAlignTextLabel->sizePolicy().hasHeightForWidth());
        valueQueryVAlignTextLabel->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(valueQueryVAlignTextLabel, 2, 0, 1, 1);

        valueQueryVAlignComboBox = new QComboBox(valueQueryGroupBox);
        valueQueryVAlignComboBox->setObjectName(QString::fromUtf8("valueQueryVAlignComboBox"));

        gridLayout_3->addWidget(valueQueryVAlignComboBox, 2, 1, 1, 1);


        gridLayout_8->addWidget(valueQueryGroupBox, 1, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 2, 0, 1, 4);

        buttonOk = new QPushButton(CrossTabEditor);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        gridLayout_9->addWidget(buttonOk, 3, 2, 1, 1);

        buttonCancel = new QPushButton(CrossTabEditor);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        gridLayout_9->addWidget(buttonCancel, 3, 3, 1, 1);

        QWidget::setTabOrder(cbQuery, columnQueryLineEdit);
        QWidget::setTabOrder(columnQueryLineEdit, btnFont);
        QWidget::setTabOrder(btnFont, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);

        retranslateUi(CrossTabEditor);
        QObject::connect(buttonOk, SIGNAL(clicked()), CrossTabEditor, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), CrossTabEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(CrossTabEditor);
    } // setupUi

    void retranslateUi(QDialog *CrossTabEditor)
    {
        CrossTabEditor->setWindowTitle(QApplication::translate("CrossTabEditor", "Properties (Field)", 0, QApplication::UnicodeUTF8));
        TextLabel1_3->setText(QApplication::translate("CrossTabEditor", "Query Source:", 0, QApplication::UnicodeUTF8));
        m_tablePropertiesGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Table properties", 0, QApplication::UnicodeUTF8));
        m_TableCellMarginsGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Table cell margins (inches)", 0, QApplication::UnicodeUTF8));
        m_cellLeftMarginLabel->setText(QApplication::translate("CrossTabEditor", "Left:", 0, QApplication::UnicodeUTF8));
        m_cellRightMarginLabel->setText(QApplication::translate("CrossTabEditor", "Right:", 0, QApplication::UnicodeUTF8));
        m_cellTopMarginLabel->setText(QApplication::translate("CrossTabEditor", "Top:", 0, QApplication::UnicodeUTF8));
        m_cellBottomMarginLabel->setText(QApplication::translate("CrossTabEditor", "Bottom:", 0, QApplication::UnicodeUTF8));
        m_tableWrappingPolicyGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Wrapping policy", 0, QApplication::UnicodeUTF8));
        m_wrapRowsFirstRadioButton->setText(QApplication::translate("CrossTabEditor", "First display all rows", 0, QApplication::UnicodeUTF8));
        m_wrapColumnsFirstRadioButton->setText(QApplication::translate("CrossTabEditor", "First display all columns", 0, QApplication::UnicodeUTF8));
        m_tableDisplayHeaderGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Display header", 0, QApplication::UnicodeUTF8));
        m_tableDisplayColumnHeaderCheckBox->setText(QApplication::translate("CrossTabEditor", "Display column header on each part", 0, QApplication::UnicodeUTF8));
        m_tableDisplayRowHeaderCheckBox->setText(QApplication::translate("CrossTabEditor", "Display row header on each part", 0, QApplication::UnicodeUTF8));
        btnFont->setText(QApplication::translate("CrossTabEditor", "&Font...", 0, QApplication::UnicodeUTF8));
        columnQueryGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Column query source", 0, QApplication::UnicodeUTF8));
        columnQueryColumnTextLabel->setText(QApplication::translate("CrossTabEditor", "Column query column:", 0, QApplication::UnicodeUTF8));
        columnQueryHAlignTextLabel->setText(QApplication::translate("CrossTabEditor", "Horizontal alignment:", 0, QApplication::UnicodeUTF8));
        columnQueryHAlignComboBox->clear();
        columnQueryHAlignComboBox->insertItems(0, QStringList()
         << QApplication::translate("CrossTabEditor", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Center", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Right", 0, QApplication::UnicodeUTF8)
        );
        columnQueryVAlignTextLabel->setText(QApplication::translate("CrossTabEditor", "Vertical alignment:", 0, QApplication::UnicodeUTF8));
        columnQueryVAlignComboBox->clear();
        columnQueryVAlignComboBox->insertItems(0, QStringList()
         << QApplication::translate("CrossTabEditor", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Top", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Center", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Bottom", 0, QApplication::UnicodeUTF8)
        );
        rowQueryGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Row query source", 0, QApplication::UnicodeUTF8));
        rowQueryColumnTextLabel->setText(QApplication::translate("CrossTabEditor", "Row query column:", 0, QApplication::UnicodeUTF8));
        rowQueryHAlignTextLabel->setText(QApplication::translate("CrossTabEditor", "Horizontal alignment:", 0, QApplication::UnicodeUTF8));
        rowQueryHAlignComboBox->clear();
        rowQueryHAlignComboBox->insertItems(0, QStringList()
         << QApplication::translate("CrossTabEditor", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Center", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Right", 0, QApplication::UnicodeUTF8)
        );
        rowQueryVAlignTextLabel->setText(QApplication::translate("CrossTabEditor", "Vertical alignment:", 0, QApplication::UnicodeUTF8));
        rowQueryVAlignComboBox->clear();
        rowQueryVAlignComboBox->insertItems(0, QStringList()
         << QApplication::translate("CrossTabEditor", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Top", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Center", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Bottom", 0, QApplication::UnicodeUTF8)
        );
        valueQueryGroupBox->setTitle(QApplication::translate("CrossTabEditor", "Value query source", 0, QApplication::UnicodeUTF8));
        valueQueryColumnTextLabel->setText(QApplication::translate("CrossTabEditor", "Value query column:", 0, QApplication::UnicodeUTF8));
        valueQueryHAlignTextLabel->setText(QApplication::translate("CrossTabEditor", "Horizontal alignment:", 0, QApplication::UnicodeUTF8));
        valueQueryHAlignComboBox->clear();
        valueQueryHAlignComboBox->insertItems(0, QStringList()
         << QApplication::translate("CrossTabEditor", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Center", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Right", 0, QApplication::UnicodeUTF8)
        );
        valueQueryVAlignTextLabel->setText(QApplication::translate("CrossTabEditor", "Vertical alignment:", 0, QApplication::UnicodeUTF8));
        valueQueryVAlignComboBox->clear();
        valueQueryVAlignComboBox->insertItems(0, QStringList()
         << QApplication::translate("CrossTabEditor", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Top", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Center", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CrossTabEditor", "Bottom", 0, QApplication::UnicodeUTF8)
        );
        buttonOk->setText(QApplication::translate("CrossTabEditor", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("CrossTabEditor", "Alt+O", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("CrossTabEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("CrossTabEditor", "Alt+C", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CrossTabEditor: public Ui_CrossTabEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROSSTABEDITOR_H
