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
** Form generated from reading UI file 'reportproperties.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTPROPERTIES_H
#define UI_REPORTPROPERTIES_H

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
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "querycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_ReportProperties
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *_tab;
    QWidget *tab1;
    QVBoxLayout *vboxLayout1;
    QGridLayout *gridLayout;
    QLabel *_lblTitle;
    QLineEdit *_leTitle;
    QLineEdit *_leName;
    QLabel *_lblName;
    QLabel *_lblDescrip;
    QTextEdit *_leDescription;
    QWidget *tab2;
    QVBoxLayout *vboxLayout2;
    QCheckBox *_cbBgEnable;
    QTabWidget *_tabBg;
    QWidget *tab21;
    QVBoxLayout *vboxLayout3;
    QGroupBox *_gbBgSource;
    QHBoxLayout *hboxLayout;
    QRadioButton *_rbBgStatic;
    QRadioButton *_rbBgDynamic;
    QGroupBox *_gbBgDynamic;
    QGridLayout *gridLayout1;
    QLineEdit *_leBgColumn;
    QLabel *_lblBgColumn;
    QLabel *_lblBgQuery;
    QueryComboBox *_cbBgQuery;
    QGroupBox *_gbBgOpacity;
    QHBoxLayout *hboxLayout1;
    QLabel *_lblBgOpacityNone;
    QVBoxLayout *vboxLayout4;
    QSlider *_slBgOpacity;
    QLabel *_lblBgOpacity;
    QLabel *_lblBgOpacityFull;
    QSpacerItem *spacerItem;
    QWidget *tab22;
    QVBoxLayout *vboxLayout5;
    QGroupBox *_gbBgResizeMode;
    QHBoxLayout *hboxLayout2;
    QRadioButton *_rbBgClip;
    QRadioButton *_rbBgStretch;
    QHBoxLayout *hboxLayout3;
    QVBoxLayout *vboxLayout6;
    QHBoxLayout *hboxLayout4;
    QGroupBox *_gbBgHAlign;
    QVBoxLayout *vboxLayout7;
    QRadioButton *_rbBgHAlignLeft;
    QRadioButton *_rbBgHAlignCenter;
    QRadioButton *_rbBgHAlignRight;
    QGroupBox *_gbBgVAlign;
    QVBoxLayout *vboxLayout8;
    QRadioButton *_rbBgVAlignTop;
    QRadioButton *_rbBgVAlignMiddle;
    QRadioButton *_rbBgVAlignBottom;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout9;
    QGroupBox *_gbBgBounds;
    QVBoxLayout *vboxLayout10;
    QGridLayout *gridLayout2;
    QLabel *_lblBgY;
    QLabel *_lblBgWidth;
    QLabel *_lblBgX;
    QLineEdit *_leBgHeight;
    QLabel *_lblBgHeight;
    QLineEdit *_leBgY;
    QLineEdit *_leBgX;
    QLineEdit *_leBgWidth;
    QLabel *_lblBoundsInInches;
    QSpacerItem *spacerItem2;
    QWidget *tab23;
    QVBoxLayout *vboxLayout11;
    QGroupBox *_gbStatic;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *_pixmap;
    QPushButton *_btnLoad;
    QWidget *tab3;
    QVBoxLayout *vboxLayout12;
    QHBoxLayout *hboxLayout5;
    QCheckBox *_cbWmStatic;
    QLineEdit *_leWmText;
    QGroupBox *_gbWmDynamic;
    QGridLayout *gridLayout3;
    QLineEdit *_leWmColumn;
    QLabel *_lblWmColumn;
    QLabel *_lblWmQuery;
    QueryComboBox *_cbWmQuery;
    QCheckBox *_cbWmUseBest;
    QGroupBox *_gbWmFont;
    QHBoxLayout *hboxLayout6;
    QLineEdit *_leWmFont;
    QPushButton *_btnWmChangeFont;
    QGroupBox *_gbWmOpacity;
    QHBoxLayout *hboxLayout7;
    QLabel *_lblWmOpacityNone;
    QVBoxLayout *vboxLayout13;
    QSlider *_slWmOpacity;
    QLabel *_lblWmOpacity;
    QLabel *_lblWmOpacityFull;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout8;
    QSpacerItem *spacerItem4;
    QPushButton *_btnAccept;
    QPushButton *_btnCancel;

    void setupUi(QDialog *ReportProperties)
    {
        if (ReportProperties->objectName().isEmpty())
            ReportProperties->setObjectName(QString::fromUtf8("ReportProperties"));
        ReportProperties->resize(549, 481);
        vboxLayout = new QVBoxLayout(ReportProperties);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        _tab = new QTabWidget(ReportProperties);
        _tab->setObjectName(QString::fromUtf8("_tab"));
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        vboxLayout1 = new QVBoxLayout(tab1);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _lblTitle = new QLabel(tab1);
        _lblTitle->setObjectName(QString::fromUtf8("_lblTitle"));

        gridLayout->addWidget(_lblTitle, 1, 0, 1, 1);

        _leTitle = new QLineEdit(tab1);
        _leTitle->setObjectName(QString::fromUtf8("_leTitle"));

        gridLayout->addWidget(_leTitle, 1, 1, 1, 1);

        _leName = new QLineEdit(tab1);
        _leName->setObjectName(QString::fromUtf8("_leName"));

        gridLayout->addWidget(_leName, 0, 1, 1, 1);

        _lblName = new QLabel(tab1);
        _lblName->setObjectName(QString::fromUtf8("_lblName"));

        gridLayout->addWidget(_lblName, 0, 0, 1, 1);


        vboxLayout1->addLayout(gridLayout);

        _lblDescrip = new QLabel(tab1);
        _lblDescrip->setObjectName(QString::fromUtf8("_lblDescrip"));

        vboxLayout1->addWidget(_lblDescrip);

        _leDescription = new QTextEdit(tab1);
        _leDescription->setObjectName(QString::fromUtf8("_leDescription"));

        vboxLayout1->addWidget(_leDescription);

        _tab->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        vboxLayout2 = new QVBoxLayout(tab2);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        _cbBgEnable = new QCheckBox(tab2);
        _cbBgEnable->setObjectName(QString::fromUtf8("_cbBgEnable"));

        vboxLayout2->addWidget(_cbBgEnable);

        _tabBg = new QTabWidget(tab2);
        _tabBg->setObjectName(QString::fromUtf8("_tabBg"));
        tab21 = new QWidget();
        tab21->setObjectName(QString::fromUtf8("tab21"));
        vboxLayout3 = new QVBoxLayout(tab21);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        _gbBgSource = new QGroupBox(tab21);
        _gbBgSource->setObjectName(QString::fromUtf8("_gbBgSource"));
        hboxLayout = new QHBoxLayout(_gbBgSource);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        _rbBgStatic = new QRadioButton(_gbBgSource);
        _rbBgStatic->setObjectName(QString::fromUtf8("_rbBgStatic"));
        _rbBgStatic->setChecked(true);

        hboxLayout->addWidget(_rbBgStatic);

        _rbBgDynamic = new QRadioButton(_gbBgSource);
        _rbBgDynamic->setObjectName(QString::fromUtf8("_rbBgDynamic"));

        hboxLayout->addWidget(_rbBgDynamic);


        vboxLayout3->addWidget(_gbBgSource);

        _gbBgDynamic = new QGroupBox(tab21);
        _gbBgDynamic->setObjectName(QString::fromUtf8("_gbBgDynamic"));
        _gbBgDynamic->setEnabled(false);
        gridLayout1 = new QGridLayout(_gbBgDynamic);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        _leBgColumn = new QLineEdit(_gbBgDynamic);
        _leBgColumn->setObjectName(QString::fromUtf8("_leBgColumn"));

        gridLayout1->addWidget(_leBgColumn, 1, 1, 1, 1);

        _lblBgColumn = new QLabel(_gbBgDynamic);
        _lblBgColumn->setObjectName(QString::fromUtf8("_lblBgColumn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_lblBgColumn->sizePolicy().hasHeightForWidth());
        _lblBgColumn->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(_lblBgColumn, 1, 0, 1, 1);

        _lblBgQuery = new QLabel(_gbBgDynamic);
        _lblBgQuery->setObjectName(QString::fromUtf8("_lblBgQuery"));

        gridLayout1->addWidget(_lblBgQuery, 0, 0, 1, 1);

        _cbBgQuery = new QueryComboBox(_gbBgDynamic);
        _cbBgQuery->setObjectName(QString::fromUtf8("_cbBgQuery"));

        gridLayout1->addWidget(_cbBgQuery, 0, 1, 1, 1);


        vboxLayout3->addWidget(_gbBgDynamic);

        _gbBgOpacity = new QGroupBox(tab21);
        _gbBgOpacity->setObjectName(QString::fromUtf8("_gbBgOpacity"));
        hboxLayout1 = new QHBoxLayout(_gbBgOpacity);
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(11, 11, 11, 11);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        _lblBgOpacityNone = new QLabel(_gbBgOpacity);
        _lblBgOpacityNone->setObjectName(QString::fromUtf8("_lblBgOpacityNone"));
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica [Cronyx]"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        _lblBgOpacityNone->setFont(font);
        _lblBgOpacityNone->setAlignment(Qt::AlignCenter);

        hboxLayout1->addWidget(_lblBgOpacityNone);

        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setSpacing(6);
        vboxLayout4->setContentsMargins(0, 0, 0, 0);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        _slBgOpacity = new QSlider(_gbBgOpacity);
        _slBgOpacity->setObjectName(QString::fromUtf8("_slBgOpacity"));
        _slBgOpacity->setMaximum(255);
        _slBgOpacity->setValue(25);
        _slBgOpacity->setOrientation(Qt::Horizontal);
        _slBgOpacity->setTickInterval(25);

        vboxLayout4->addWidget(_slBgOpacity);

        _lblBgOpacity = new QLabel(_gbBgOpacity);
        _lblBgOpacity->setObjectName(QString::fromUtf8("_lblBgOpacity"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Helvetica [Cronyx]"));
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        _lblBgOpacity->setFont(font1);
        _lblBgOpacity->setAlignment(Qt::AlignCenter);

        vboxLayout4->addWidget(_lblBgOpacity);


        hboxLayout1->addLayout(vboxLayout4);

        _lblBgOpacityFull = new QLabel(_gbBgOpacity);
        _lblBgOpacityFull->setObjectName(QString::fromUtf8("_lblBgOpacityFull"));
        _lblBgOpacityFull->setFont(font);
        _lblBgOpacityFull->setAlignment(Qt::AlignCenter);

        hboxLayout1->addWidget(_lblBgOpacityFull);


        vboxLayout3->addWidget(_gbBgOpacity);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem);

        _tabBg->addTab(tab21, QString());
        tab22 = new QWidget();
        tab22->setObjectName(QString::fromUtf8("tab22"));
        vboxLayout5 = new QVBoxLayout(tab22);
        vboxLayout5->setSpacing(6);
        vboxLayout5->setContentsMargins(0, 0, 0, 0);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        _gbBgResizeMode = new QGroupBox(tab22);
        _gbBgResizeMode->setObjectName(QString::fromUtf8("_gbBgResizeMode"));
        hboxLayout2 = new QHBoxLayout(_gbBgResizeMode);
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(11, 11, 11, 11);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        _rbBgClip = new QRadioButton(_gbBgResizeMode);
        _rbBgClip->setObjectName(QString::fromUtf8("_rbBgClip"));
        _rbBgClip->setChecked(true);

        hboxLayout2->addWidget(_rbBgClip);

        _rbBgStretch = new QRadioButton(_gbBgResizeMode);
        _rbBgStretch->setObjectName(QString::fromUtf8("_rbBgStretch"));

        hboxLayout2->addWidget(_rbBgStretch);


        vboxLayout5->addWidget(_gbBgResizeMode);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        vboxLayout6 = new QVBoxLayout();
        vboxLayout6->setSpacing(6);
        vboxLayout6->setContentsMargins(0, 0, 0, 0);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        _gbBgHAlign = new QGroupBox(tab22);
        _gbBgHAlign->setObjectName(QString::fromUtf8("_gbBgHAlign"));
        sizePolicy.setHeightForWidth(_gbBgHAlign->sizePolicy().hasHeightForWidth());
        _gbBgHAlign->setSizePolicy(sizePolicy);
        vboxLayout7 = new QVBoxLayout(_gbBgHAlign);
        vboxLayout7->setSpacing(6);
        vboxLayout7->setContentsMargins(11, 11, 11, 11);
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        _rbBgHAlignLeft = new QRadioButton(_gbBgHAlign);
        _rbBgHAlignLeft->setObjectName(QString::fromUtf8("_rbBgHAlignLeft"));
        _rbBgHAlignLeft->setChecked(true);

        vboxLayout7->addWidget(_rbBgHAlignLeft);

        _rbBgHAlignCenter = new QRadioButton(_gbBgHAlign);
        _rbBgHAlignCenter->setObjectName(QString::fromUtf8("_rbBgHAlignCenter"));

        vboxLayout7->addWidget(_rbBgHAlignCenter);

        _rbBgHAlignRight = new QRadioButton(_gbBgHAlign);
        _rbBgHAlignRight->setObjectName(QString::fromUtf8("_rbBgHAlignRight"));

        vboxLayout7->addWidget(_rbBgHAlignRight);


        hboxLayout4->addWidget(_gbBgHAlign);

        _gbBgVAlign = new QGroupBox(tab22);
        _gbBgVAlign->setObjectName(QString::fromUtf8("_gbBgVAlign"));
        sizePolicy.setHeightForWidth(_gbBgVAlign->sizePolicy().hasHeightForWidth());
        _gbBgVAlign->setSizePolicy(sizePolicy);
        vboxLayout8 = new QVBoxLayout(_gbBgVAlign);
        vboxLayout8->setSpacing(6);
        vboxLayout8->setContentsMargins(11, 11, 11, 11);
        vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
        _rbBgVAlignTop = new QRadioButton(_gbBgVAlign);
        _rbBgVAlignTop->setObjectName(QString::fromUtf8("_rbBgVAlignTop"));
        _rbBgVAlignTop->setChecked(true);

        vboxLayout8->addWidget(_rbBgVAlignTop);

        _rbBgVAlignMiddle = new QRadioButton(_gbBgVAlign);
        _rbBgVAlignMiddle->setObjectName(QString::fromUtf8("_rbBgVAlignMiddle"));

        vboxLayout8->addWidget(_rbBgVAlignMiddle);

        _rbBgVAlignBottom = new QRadioButton(_gbBgVAlign);
        _rbBgVAlignBottom->setObjectName(QString::fromUtf8("_rbBgVAlignBottom"));

        vboxLayout8->addWidget(_rbBgVAlignBottom);


        hboxLayout4->addWidget(_gbBgVAlign);


        vboxLayout6->addLayout(hboxLayout4);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout6->addItem(spacerItem1);


        hboxLayout3->addLayout(vboxLayout6);

        vboxLayout9 = new QVBoxLayout();
        vboxLayout9->setSpacing(6);
        vboxLayout9->setContentsMargins(0, 0, 0, 0);
        vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
        _gbBgBounds = new QGroupBox(tab22);
        _gbBgBounds->setObjectName(QString::fromUtf8("_gbBgBounds"));
        vboxLayout10 = new QVBoxLayout(_gbBgBounds);
        vboxLayout10->setSpacing(6);
        vboxLayout10->setContentsMargins(11, 11, 11, 11);
        vboxLayout10->setObjectName(QString::fromUtf8("vboxLayout10"));
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        _lblBgY = new QLabel(_gbBgBounds);
        _lblBgY->setObjectName(QString::fromUtf8("_lblBgY"));
        _lblBgY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(_lblBgY, 1, 0, 1, 1);

        _lblBgWidth = new QLabel(_gbBgBounds);
        _lblBgWidth->setObjectName(QString::fromUtf8("_lblBgWidth"));
        _lblBgWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(_lblBgWidth, 2, 0, 1, 1);

        _lblBgX = new QLabel(_gbBgBounds);
        _lblBgX->setObjectName(QString::fromUtf8("_lblBgX"));
        _lblBgX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(_lblBgX, 0, 0, 1, 1);

        _leBgHeight = new QLineEdit(_gbBgBounds);
        _leBgHeight->setObjectName(QString::fromUtf8("_leBgHeight"));

        gridLayout2->addWidget(_leBgHeight, 3, 1, 1, 1);

        _lblBgHeight = new QLabel(_gbBgBounds);
        _lblBgHeight->setObjectName(QString::fromUtf8("_lblBgHeight"));
        _lblBgHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(_lblBgHeight, 3, 0, 1, 1);

        _leBgY = new QLineEdit(_gbBgBounds);
        _leBgY->setObjectName(QString::fromUtf8("_leBgY"));

        gridLayout2->addWidget(_leBgY, 1, 1, 1, 1);

        _leBgX = new QLineEdit(_gbBgBounds);
        _leBgX->setObjectName(QString::fromUtf8("_leBgX"));

        gridLayout2->addWidget(_leBgX, 0, 1, 1, 1);

        _leBgWidth = new QLineEdit(_gbBgBounds);
        _leBgWidth->setObjectName(QString::fromUtf8("_leBgWidth"));

        gridLayout2->addWidget(_leBgWidth, 2, 1, 1, 1);


        vboxLayout10->addLayout(gridLayout2);

        _lblBoundsInInches = new QLabel(_gbBgBounds);
        _lblBoundsInInches->setObjectName(QString::fromUtf8("_lblBoundsInInches"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Helvetica [Cronyx]"));
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setItalic(true);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        _lblBoundsInInches->setFont(font2);
        _lblBoundsInInches->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        vboxLayout10->addWidget(_lblBoundsInInches);


        vboxLayout9->addWidget(_gbBgBounds);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout9->addItem(spacerItem2);


        hboxLayout3->addLayout(vboxLayout9);


        vboxLayout5->addLayout(hboxLayout3);

        _tabBg->addTab(tab22, QString());
        tab23 = new QWidget();
        tab23->setObjectName(QString::fromUtf8("tab23"));
        vboxLayout11 = new QVBoxLayout(tab23);
        vboxLayout11->setSpacing(6);
        vboxLayout11->setContentsMargins(0, 0, 0, 0);
        vboxLayout11->setObjectName(QString::fromUtf8("vboxLayout11"));
        _gbStatic = new QGroupBox(tab23);
        _gbStatic->setObjectName(QString::fromUtf8("_gbStatic"));
        verticalLayout_2 = new QVBoxLayout(_gbStatic);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(_gbStatic);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 493, 272));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        _pixmap = new QLabel(scrollAreaWidgetContents);
        _pixmap->setObjectName(QString::fromUtf8("_pixmap"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_pixmap->sizePolicy().hasHeightForWidth());
        _pixmap->setSizePolicy(sizePolicy1);
        _pixmap->setScaledContents(true);
        _pixmap->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(_pixmap);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        _btnLoad = new QPushButton(_gbStatic);
        _btnLoad->setObjectName(QString::fromUtf8("_btnLoad"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(_btnLoad->sizePolicy().hasHeightForWidth());
        _btnLoad->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(_btnLoad);


        vboxLayout11->addWidget(_gbStatic);

        _tabBg->addTab(tab23, QString());

        vboxLayout2->addWidget(_tabBg);

        _tab->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QString::fromUtf8("tab3"));
        vboxLayout12 = new QVBoxLayout(tab3);
        vboxLayout12->setSpacing(6);
        vboxLayout12->setContentsMargins(0, 0, 0, 0);
        vboxLayout12->setObjectName(QString::fromUtf8("vboxLayout12"));
        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        _cbWmStatic = new QCheckBox(tab3);
        _cbWmStatic->setObjectName(QString::fromUtf8("_cbWmStatic"));
        _cbWmStatic->setChecked(true);

        hboxLayout5->addWidget(_cbWmStatic);

        _leWmText = new QLineEdit(tab3);
        _leWmText->setObjectName(QString::fromUtf8("_leWmText"));

        hboxLayout5->addWidget(_leWmText);


        vboxLayout12->addLayout(hboxLayout5);

        _gbWmDynamic = new QGroupBox(tab3);
        _gbWmDynamic->setObjectName(QString::fromUtf8("_gbWmDynamic"));
        _gbWmDynamic->setEnabled(false);
        gridLayout3 = new QGridLayout(_gbWmDynamic);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        _leWmColumn = new QLineEdit(_gbWmDynamic);
        _leWmColumn->setObjectName(QString::fromUtf8("_leWmColumn"));

        gridLayout3->addWidget(_leWmColumn, 1, 1, 1, 1);

        _lblWmColumn = new QLabel(_gbWmDynamic);
        _lblWmColumn->setObjectName(QString::fromUtf8("_lblWmColumn"));
        sizePolicy.setHeightForWidth(_lblWmColumn->sizePolicy().hasHeightForWidth());
        _lblWmColumn->setSizePolicy(sizePolicy);

        gridLayout3->addWidget(_lblWmColumn, 1, 0, 1, 1);

        _lblWmQuery = new QLabel(_gbWmDynamic);
        _lblWmQuery->setObjectName(QString::fromUtf8("_lblWmQuery"));

        gridLayout3->addWidget(_lblWmQuery, 0, 0, 1, 1);

        _cbWmQuery = new QueryComboBox(_gbWmDynamic);
        _cbWmQuery->setObjectName(QString::fromUtf8("_cbWmQuery"));

        gridLayout3->addWidget(_cbWmQuery, 0, 1, 1, 1);


        vboxLayout12->addWidget(_gbWmDynamic);

        _cbWmUseBest = new QCheckBox(tab3);
        _cbWmUseBest->setObjectName(QString::fromUtf8("_cbWmUseBest"));
        _cbWmUseBest->setChecked(true);

        vboxLayout12->addWidget(_cbWmUseBest);

        _gbWmFont = new QGroupBox(tab3);
        _gbWmFont->setObjectName(QString::fromUtf8("_gbWmFont"));
        _gbWmFont->setEnabled(false);
        hboxLayout6 = new QHBoxLayout(_gbWmFont);
        hboxLayout6->setSpacing(6);
        hboxLayout6->setContentsMargins(11, 11, 11, 11);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        _leWmFont = new QLineEdit(_gbWmFont);
        _leWmFont->setObjectName(QString::fromUtf8("_leWmFont"));
        _leWmFont->setReadOnly(true);

        hboxLayout6->addWidget(_leWmFont);

        _btnWmChangeFont = new QPushButton(_gbWmFont);
        _btnWmChangeFont->setObjectName(QString::fromUtf8("_btnWmChangeFont"));

        hboxLayout6->addWidget(_btnWmChangeFont);


        vboxLayout12->addWidget(_gbWmFont);

        _gbWmOpacity = new QGroupBox(tab3);
        _gbWmOpacity->setObjectName(QString::fromUtf8("_gbWmOpacity"));
        hboxLayout7 = new QHBoxLayout(_gbWmOpacity);
        hboxLayout7->setSpacing(6);
        hboxLayout7->setContentsMargins(11, 11, 11, 11);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        _lblWmOpacityNone = new QLabel(_gbWmOpacity);
        _lblWmOpacityNone->setObjectName(QString::fromUtf8("_lblWmOpacityNone"));
        _lblWmOpacityNone->setFont(font);
        _lblWmOpacityNone->setAlignment(Qt::AlignCenter);

        hboxLayout7->addWidget(_lblWmOpacityNone);

        vboxLayout13 = new QVBoxLayout();
        vboxLayout13->setSpacing(6);
        vboxLayout13->setContentsMargins(0, 0, 0, 0);
        vboxLayout13->setObjectName(QString::fromUtf8("vboxLayout13"));
        _slWmOpacity = new QSlider(_gbWmOpacity);
        _slWmOpacity->setObjectName(QString::fromUtf8("_slWmOpacity"));
        _slWmOpacity->setMaximum(255);
        _slWmOpacity->setValue(25);
        _slWmOpacity->setOrientation(Qt::Horizontal);
        _slWmOpacity->setTickInterval(25);

        vboxLayout13->addWidget(_slWmOpacity);

        _lblWmOpacity = new QLabel(_gbWmOpacity);
        _lblWmOpacity->setObjectName(QString::fromUtf8("_lblWmOpacity"));
        _lblWmOpacity->setFont(font1);
        _lblWmOpacity->setAlignment(Qt::AlignCenter);

        vboxLayout13->addWidget(_lblWmOpacity);


        hboxLayout7->addLayout(vboxLayout13);

        _lblWmOpacityFull = new QLabel(_gbWmOpacity);
        _lblWmOpacityFull->setObjectName(QString::fromUtf8("_lblWmOpacityFull"));
        _lblWmOpacityFull->setFont(font);
        _lblWmOpacityFull->setAlignment(Qt::AlignCenter);

        hboxLayout7->addWidget(_lblWmOpacityFull);


        vboxLayout12->addWidget(_gbWmOpacity);

        spacerItem3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout12->addItem(spacerItem3);

        _tab->addTab(tab3, QString());

        vboxLayout->addWidget(_tab);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        spacerItem4 = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacerItem4);

        _btnAccept = new QPushButton(ReportProperties);
        _btnAccept->setObjectName(QString::fromUtf8("_btnAccept"));

        hboxLayout8->addWidget(_btnAccept);

        _btnCancel = new QPushButton(ReportProperties);
        _btnCancel->setObjectName(QString::fromUtf8("_btnCancel"));

        hboxLayout8->addWidget(_btnCancel);


        vboxLayout->addLayout(hboxLayout8);

        QWidget::setTabOrder(_tab, _leName);
        QWidget::setTabOrder(_leName, _leTitle);
        QWidget::setTabOrder(_leTitle, _leDescription);
        QWidget::setTabOrder(_leDescription, _cbBgEnable);
        QWidget::setTabOrder(_cbBgEnable, _tabBg);
        QWidget::setTabOrder(_tabBg, _rbBgStatic);
        QWidget::setTabOrder(_rbBgStatic, _cbBgQuery);
        QWidget::setTabOrder(_cbBgQuery, _leBgColumn);
        QWidget::setTabOrder(_leBgColumn, _slBgOpacity);
        QWidget::setTabOrder(_slBgOpacity, _rbBgClip);
        QWidget::setTabOrder(_rbBgClip, _rbBgHAlignLeft);
        QWidget::setTabOrder(_rbBgHAlignLeft, _rbBgVAlignTop);
        QWidget::setTabOrder(_rbBgVAlignTop, _leBgX);
        QWidget::setTabOrder(_leBgX, _leBgY);
        QWidget::setTabOrder(_leBgY, _leBgWidth);
        QWidget::setTabOrder(_leBgWidth, _leBgHeight);
        QWidget::setTabOrder(_leBgHeight, _btnLoad);
        QWidget::setTabOrder(_btnLoad, _cbWmStatic);
        QWidget::setTabOrder(_cbWmStatic, _leWmText);
        QWidget::setTabOrder(_leWmText, _cbWmQuery);
        QWidget::setTabOrder(_cbWmQuery, _leWmColumn);
        QWidget::setTabOrder(_leWmColumn, _cbWmUseBest);
        QWidget::setTabOrder(_cbWmUseBest, _leWmFont);
        QWidget::setTabOrder(_leWmFont, _btnWmChangeFont);
        QWidget::setTabOrder(_btnWmChangeFont, _slWmOpacity);
        QWidget::setTabOrder(_slWmOpacity, _btnAccept);
        QWidget::setTabOrder(_btnAccept, _btnCancel);

        retranslateUi(ReportProperties);
        QObject::connect(_btnAccept, SIGNAL(clicked()), ReportProperties, SLOT(accept()));
        QObject::connect(_btnCancel, SIGNAL(clicked()), ReportProperties, SLOT(reject()));
        QObject::connect(_cbWmStatic, SIGNAL(toggled(bool)), _gbWmDynamic, SLOT(setDisabled(bool)));
        QObject::connect(_cbWmStatic, SIGNAL(toggled(bool)), _leWmText, SLOT(setEnabled(bool)));
        QObject::connect(_cbWmUseBest, SIGNAL(toggled(bool)), _gbWmFont, SLOT(setDisabled(bool)));
        QObject::connect(_cbBgEnable, SIGNAL(toggled(bool)), _tabBg, SLOT(setEnabled(bool)));
        QObject::connect(_rbBgStatic, SIGNAL(toggled(bool)), _gbBgDynamic, SLOT(setDisabled(bool)));
        QObject::connect(_rbBgStatic, SIGNAL(toggled(bool)), _gbStatic, SLOT(setEnabled(bool)));

        _tab->setCurrentIndex(0);
        _tabBg->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ReportProperties);
    } // setupUi

    void retranslateUi(QDialog *ReportProperties)
    {
        ReportProperties->setWindowTitle(QApplication::translate("ReportProperties", "Report Properties", 0, QApplication::UnicodeUTF8));
        _lblTitle->setText(QApplication::translate("ReportProperties", "Title:", 0, QApplication::UnicodeUTF8));
        _lblName->setText(QApplication::translate("ReportProperties", "Name:", 0, QApplication::UnicodeUTF8));
        _lblDescrip->setText(QApplication::translate("ReportProperties", "Description:", 0, QApplication::UnicodeUTF8));
        _tab->setTabText(_tab->indexOf(tab1), QApplication::translate("ReportProperties", "Info", 0, QApplication::UnicodeUTF8));
        _cbBgEnable->setText(QApplication::translate("ReportProperties", "Enable Background Image", 0, QApplication::UnicodeUTF8));
        _gbBgSource->setTitle(QApplication::translate("ReportProperties", "Source", 0, QApplication::UnicodeUTF8));
        _rbBgStatic->setText(QApplication::translate("ReportProperties", "Static", 0, QApplication::UnicodeUTF8));
        _rbBgDynamic->setText(QApplication::translate("ReportProperties", "Dynamic", 0, QApplication::UnicodeUTF8));
        _gbBgDynamic->setTitle(QApplication::translate("ReportProperties", "Database", 0, QApplication::UnicodeUTF8));
        _lblBgColumn->setText(QApplication::translate("ReportProperties", "Column:", 0, QApplication::UnicodeUTF8));
        _lblBgQuery->setText(QApplication::translate("ReportProperties", "Query Source:", 0, QApplication::UnicodeUTF8));
        _gbBgOpacity->setTitle(QApplication::translate("ReportProperties", "Opacity", 0, QApplication::UnicodeUTF8));
        _lblBgOpacityNone->setText(QApplication::translate("ReportProperties", "0%\n"
"(transparent)", 0, QApplication::UnicodeUTF8));
        _lblBgOpacity->setText(QApplication::translate("ReportProperties", "10%", 0, QApplication::UnicodeUTF8));
        _lblBgOpacityFull->setText(QApplication::translate("ReportProperties", "100%\n"
"(opaque)", 0, QApplication::UnicodeUTF8));
        _tabBg->setTabText(_tabBg->indexOf(tab21), QApplication::translate("ReportProperties", "General", 0, QApplication::UnicodeUTF8));
        _gbBgResizeMode->setTitle(QApplication::translate("ReportProperties", "Resize Mode", 0, QApplication::UnicodeUTF8));
        _rbBgClip->setText(QApplication::translate("ReportProperties", "Clip", 0, QApplication::UnicodeUTF8));
        _rbBgStretch->setText(QApplication::translate("ReportProperties", "Stretch", 0, QApplication::UnicodeUTF8));
        _gbBgHAlign->setTitle(QApplication::translate("ReportProperties", "HAlign", 0, QApplication::UnicodeUTF8));
        _rbBgHAlignLeft->setText(QApplication::translate("ReportProperties", "Left", 0, QApplication::UnicodeUTF8));
        _rbBgHAlignCenter->setText(QApplication::translate("ReportProperties", "Center", 0, QApplication::UnicodeUTF8));
        _rbBgHAlignRight->setText(QApplication::translate("ReportProperties", "Right", 0, QApplication::UnicodeUTF8));
        _gbBgVAlign->setTitle(QApplication::translate("ReportProperties", "VAlign", 0, QApplication::UnicodeUTF8));
        _rbBgVAlignTop->setText(QApplication::translate("ReportProperties", "Top", 0, QApplication::UnicodeUTF8));
        _rbBgVAlignMiddle->setText(QApplication::translate("ReportProperties", "Middle", 0, QApplication::UnicodeUTF8));
        _rbBgVAlignBottom->setText(QApplication::translate("ReportProperties", "Bottom", 0, QApplication::UnicodeUTF8));
        _gbBgBounds->setTitle(QApplication::translate("ReportProperties", "Bounds", 0, QApplication::UnicodeUTF8));
        _lblBgY->setText(QApplication::translate("ReportProperties", "Y:", 0, QApplication::UnicodeUTF8));
        _lblBgWidth->setText(QApplication::translate("ReportProperties", "Width:", 0, QApplication::UnicodeUTF8));
        _lblBgX->setText(QApplication::translate("ReportProperties", "X:", 0, QApplication::UnicodeUTF8));
        _leBgHeight->setText(QApplication::translate("ReportProperties", "11.0", 0, QApplication::UnicodeUTF8));
        _lblBgHeight->setText(QApplication::translate("ReportProperties", "Height:", 0, QApplication::UnicodeUTF8));
        _leBgY->setText(QApplication::translate("ReportProperties", "0.0", 0, QApplication::UnicodeUTF8));
        _leBgX->setText(QApplication::translate("ReportProperties", "0.0", 0, QApplication::UnicodeUTF8));
        _leBgWidth->setText(QApplication::translate("ReportProperties", "8.5", 0, QApplication::UnicodeUTF8));
        _lblBoundsInInches->setText(QApplication::translate("ReportProperties", "in inches", 0, QApplication::UnicodeUTF8));
        _tabBg->setTabText(_tabBg->indexOf(tab22), QApplication::translate("ReportProperties", "Layout", 0, QApplication::UnicodeUTF8));
        _gbStatic->setTitle(QApplication::translate("ReportProperties", "Choose Image", 0, QApplication::UnicodeUTF8));
        _btnLoad->setText(QApplication::translate("ReportProperties", "Load...", 0, QApplication::UnicodeUTF8));
        _tabBg->setTabText(_tabBg->indexOf(tab23), QApplication::translate("ReportProperties", "Static Image", 0, QApplication::UnicodeUTF8));
        _tab->setTabText(_tab->indexOf(tab2), QApplication::translate("ReportProperties", "Background", 0, QApplication::UnicodeUTF8));
        _cbWmStatic->setText(QApplication::translate("ReportProperties", "Static Text", 0, QApplication::UnicodeUTF8));
        _gbWmDynamic->setTitle(QApplication::translate("ReportProperties", "Database", 0, QApplication::UnicodeUTF8));
        _lblWmColumn->setText(QApplication::translate("ReportProperties", "Column:", 0, QApplication::UnicodeUTF8));
        _lblWmQuery->setText(QApplication::translate("ReportProperties", "Query Source:", 0, QApplication::UnicodeUTF8));
        _cbWmUseBest->setText(QApplication::translate("ReportProperties", "Use best font", 0, QApplication::UnicodeUTF8));
        _gbWmFont->setTitle(QApplication::translate("ReportProperties", "Font", 0, QApplication::UnicodeUTF8));
        _leWmFont->setText(QApplication::translate("ReportProperties", "Arial", 0, QApplication::UnicodeUTF8));
        _btnWmChangeFont->setText(QApplication::translate("ReportProperties", "Change...", 0, QApplication::UnicodeUTF8));
        _gbWmOpacity->setTitle(QApplication::translate("ReportProperties", "Opacity", 0, QApplication::UnicodeUTF8));
        _lblWmOpacityNone->setText(QApplication::translate("ReportProperties", "0%\n"
"(transparent)", 0, QApplication::UnicodeUTF8));
        _lblWmOpacity->setText(QApplication::translate("ReportProperties", "10%", 0, QApplication::UnicodeUTF8));
        _lblWmOpacityFull->setText(QApplication::translate("ReportProperties", "100%\n"
"(opaque)", 0, QApplication::UnicodeUTF8));
        _tab->setTabText(_tab->indexOf(tab3), QApplication::translate("ReportProperties", "Watermark", 0, QApplication::UnicodeUTF8));
        _btnAccept->setText(QApplication::translate("ReportProperties", "&OK", 0, QApplication::UnicodeUTF8));
        _btnCancel->setText(QApplication::translate("ReportProperties", "&Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReportProperties: public Ui_ReportProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTPROPERTIES_H
