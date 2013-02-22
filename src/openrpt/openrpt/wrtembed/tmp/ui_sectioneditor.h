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
** Form generated from reading UI file 'sectioneditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECTIONEDITOR_H
#define UI_SECTIONEDITOR_H

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
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SectionEditor
{
public:
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QCheckBox *cbReportHeader;
    QGroupBox *gbPageFooter;
    QGridLayout *gridLayout1;
    QCheckBox *cbFootEven;
    QCheckBox *cbFootFirst;
    QCheckBox *cbFootLast;
    QCheckBox *cbFootOdd;
    QCheckBox *cbFootAny;
    QCheckBox *cbReportFooter;
    QGroupBox *gbPageHeader;
    QGridLayout *gridLayout2;
    QCheckBox *cbHeadLast;
    QCheckBox *cbHeadOdd;
    QCheckBox *cbHeadFirst;
    QCheckBox *cbHeadEven;
    QCheckBox *cbHeadAny;
    QGroupBox *GroupBox3;
    QHBoxLayout *hboxLayout;
    QListWidget *lbSections;
    QVBoxLayout *vboxLayout1;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnRemove;
    QPushButton *btnMoveUp;
    QPushButton *brnMoveDown;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QPushButton *buttonOk;

    void setupUi(QDialog *SectionEditor)
    {
        if (SectionEditor->objectName().isEmpty())
            SectionEditor->setObjectName(QString::fromUtf8("SectionEditor"));
        SectionEditor->resize(615, 442);
        SectionEditor->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(SectionEditor);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbReportHeader = new QCheckBox(SectionEditor);
        cbReportHeader->setObjectName(QString::fromUtf8("cbReportHeader"));

        gridLayout->addWidget(cbReportHeader, 0, 0, 1, 1);

        gbPageFooter = new QGroupBox(SectionEditor);
        gbPageFooter->setObjectName(QString::fromUtf8("gbPageFooter"));
        gridLayout1 = new QGridLayout(gbPageFooter);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        cbFootEven = new QCheckBox(gbPageFooter);
        cbFootEven->setObjectName(QString::fromUtf8("cbFootEven"));

        gridLayout1->addWidget(cbFootEven, 1, 0, 1, 1);

        cbFootFirst = new QCheckBox(gbPageFooter);
        cbFootFirst->setObjectName(QString::fromUtf8("cbFootFirst"));

        gridLayout1->addWidget(cbFootFirst, 0, 0, 1, 1);

        cbFootLast = new QCheckBox(gbPageFooter);
        cbFootLast->setObjectName(QString::fromUtf8("cbFootLast"));

        gridLayout1->addWidget(cbFootLast, 0, 1, 1, 1);

        cbFootOdd = new QCheckBox(gbPageFooter);
        cbFootOdd->setObjectName(QString::fromUtf8("cbFootOdd"));

        gridLayout1->addWidget(cbFootOdd, 1, 1, 1, 1);

        cbFootAny = new QCheckBox(gbPageFooter);
        cbFootAny->setObjectName(QString::fromUtf8("cbFootAny"));

        gridLayout1->addWidget(cbFootAny, 2, 0, 1, 1);


        gridLayout->addWidget(gbPageFooter, 1, 1, 1, 1);

        cbReportFooter = new QCheckBox(SectionEditor);
        cbReportFooter->setObjectName(QString::fromUtf8("cbReportFooter"));

        gridLayout->addWidget(cbReportFooter, 0, 1, 1, 1);

        gbPageHeader = new QGroupBox(SectionEditor);
        gbPageHeader->setObjectName(QString::fromUtf8("gbPageHeader"));
        gridLayout2 = new QGridLayout(gbPageHeader);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        cbHeadLast = new QCheckBox(gbPageHeader);
        cbHeadLast->setObjectName(QString::fromUtf8("cbHeadLast"));

        gridLayout2->addWidget(cbHeadLast, 0, 1, 1, 1);

        cbHeadOdd = new QCheckBox(gbPageHeader);
        cbHeadOdd->setObjectName(QString::fromUtf8("cbHeadOdd"));

        gridLayout2->addWidget(cbHeadOdd, 1, 1, 1, 1);

        cbHeadFirst = new QCheckBox(gbPageHeader);
        cbHeadFirst->setObjectName(QString::fromUtf8("cbHeadFirst"));

        gridLayout2->addWidget(cbHeadFirst, 0, 0, 1, 1);

        cbHeadEven = new QCheckBox(gbPageHeader);
        cbHeadEven->setObjectName(QString::fromUtf8("cbHeadEven"));

        gridLayout2->addWidget(cbHeadEven, 1, 0, 1, 1);

        cbHeadAny = new QCheckBox(gbPageHeader);
        cbHeadAny->setObjectName(QString::fromUtf8("cbHeadAny"));

        gridLayout2->addWidget(cbHeadAny, 2, 0, 1, 1);


        gridLayout->addWidget(gbPageHeader, 1, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        GroupBox3 = new QGroupBox(SectionEditor);
        GroupBox3->setObjectName(QString::fromUtf8("GroupBox3"));
        hboxLayout = new QHBoxLayout(GroupBox3);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lbSections = new QListWidget(GroupBox3);
        lbSections->setObjectName(QString::fromUtf8("lbSections"));

        hboxLayout->addWidget(lbSections);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(1);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        btnAdd = new QPushButton(GroupBox3);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        vboxLayout1->addWidget(btnAdd);

        btnEdit = new QPushButton(GroupBox3);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));

        vboxLayout1->addWidget(btnEdit);

        btnRemove = new QPushButton(GroupBox3);
        btnRemove->setObjectName(QString::fromUtf8("btnRemove"));

        vboxLayout1->addWidget(btnRemove);

        btnMoveUp = new QPushButton(GroupBox3);
        btnMoveUp->setObjectName(QString::fromUtf8("btnMoveUp"));

        vboxLayout1->addWidget(btnMoveUp);

        brnMoveDown = new QPushButton(GroupBox3);
        brnMoveDown->setObjectName(QString::fromUtf8("brnMoveDown"));

        vboxLayout1->addWidget(brnMoveDown);


        hboxLayout->addLayout(vboxLayout1);


        vboxLayout->addWidget(GroupBox3);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);

        buttonOk = new QPushButton(SectionEditor);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout1->addWidget(buttonOk);


        vboxLayout->addLayout(hboxLayout1);

        QWidget::setTabOrder(cbReportHeader, cbReportFooter);
        QWidget::setTabOrder(cbReportFooter, cbHeadFirst);
        QWidget::setTabOrder(cbHeadFirst, cbHeadLast);
        QWidget::setTabOrder(cbHeadLast, cbHeadEven);
        QWidget::setTabOrder(cbHeadEven, cbHeadOdd);
        QWidget::setTabOrder(cbHeadOdd, cbHeadAny);
        QWidget::setTabOrder(cbHeadAny, cbFootFirst);
        QWidget::setTabOrder(cbFootFirst, cbFootLast);
        QWidget::setTabOrder(cbFootLast, cbFootEven);
        QWidget::setTabOrder(cbFootEven, cbFootOdd);
        QWidget::setTabOrder(cbFootOdd, cbFootAny);
        QWidget::setTabOrder(cbFootAny, lbSections);
        QWidget::setTabOrder(lbSections, btnAdd);
        QWidget::setTabOrder(btnAdd, btnEdit);
        QWidget::setTabOrder(btnEdit, btnRemove);
        QWidget::setTabOrder(btnRemove, btnMoveUp);
        QWidget::setTabOrder(btnMoveUp, brnMoveDown);
        QWidget::setTabOrder(brnMoveDown, buttonOk);

        retranslateUi(SectionEditor);
        QObject::connect(buttonOk, SIGNAL(clicked()), SectionEditor, SLOT(accept()));

        QMetaObject::connectSlotsByName(SectionEditor);
    } // setupUi

    void retranslateUi(QDialog *SectionEditor)
    {
        SectionEditor->setWindowTitle(QApplication::translate("SectionEditor", "Section Editor", 0, QApplication::UnicodeUTF8));
        cbReportHeader->setText(QApplication::translate("SectionEditor", "Report Header", 0, QApplication::UnicodeUTF8));
        gbPageFooter->setTitle(QApplication::translate("SectionEditor", "Page Footer", 0, QApplication::UnicodeUTF8));
        cbFootEven->setText(QApplication::translate("SectionEditor", "Even Page(s)", 0, QApplication::UnicodeUTF8));
        cbFootFirst->setText(QApplication::translate("SectionEditor", "First Page", 0, QApplication::UnicodeUTF8));
        cbFootLast->setText(QApplication::translate("SectionEditor", "Last Page", 0, QApplication::UnicodeUTF8));
        cbFootOdd->setText(QApplication::translate("SectionEditor", "Odd Page(s)", 0, QApplication::UnicodeUTF8));
        cbFootAny->setText(QApplication::translate("SectionEditor", "Any Page(s)", 0, QApplication::UnicodeUTF8));
        cbReportFooter->setText(QApplication::translate("SectionEditor", "Report Footer", 0, QApplication::UnicodeUTF8));
        gbPageHeader->setTitle(QApplication::translate("SectionEditor", "Page Header", 0, QApplication::UnicodeUTF8));
        cbHeadLast->setText(QApplication::translate("SectionEditor", "Last Page", 0, QApplication::UnicodeUTF8));
        cbHeadOdd->setText(QApplication::translate("SectionEditor", "Odd Page(s)", 0, QApplication::UnicodeUTF8));
        cbHeadFirst->setText(QApplication::translate("SectionEditor", "First Page", 0, QApplication::UnicodeUTF8));
        cbHeadEven->setText(QApplication::translate("SectionEditor", "Even Pages(s)", 0, QApplication::UnicodeUTF8));
        cbHeadAny->setText(QApplication::translate("SectionEditor", "Any Pages(s)", 0, QApplication::UnicodeUTF8));
        GroupBox3->setTitle(QApplication::translate("SectionEditor", "Detail Sections", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("SectionEditor", "&Add", 0, QApplication::UnicodeUTF8));
        btnEdit->setText(QApplication::translate("SectionEditor", "&Edit", 0, QApplication::UnicodeUTF8));
        btnRemove->setText(QApplication::translate("SectionEditor", "Delete", 0, QApplication::UnicodeUTF8));
        btnMoveUp->setText(QApplication::translate("SectionEditor", "Move &Up", 0, QApplication::UnicodeUTF8));
        brnMoveDown->setText(QApplication::translate("SectionEditor", "Move &Down", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("SectionEditor", "&Close", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("SectionEditor", "Alt+C", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SectionEditor: public Ui_SectionEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECTIONEDITOR_H
