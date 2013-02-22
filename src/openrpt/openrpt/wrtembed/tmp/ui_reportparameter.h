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
** Form generated from reading UI file 'reportparameter.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTPARAMETER_H
#define UI_REPORTPARAMETER_H

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
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportParameter
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QGridLayout *gridLayout;
    QLabel *_lblName;
    QLabel *_lblType;
    QLineEdit *_leName;
    QHBoxLayout *hboxLayout1;
    QComboBox *_cbType;
    QCheckBox *_active;
    QSpacerItem *spacerItem;
    QLineEdit *_leDefault;
    QLabel *_lblDefault;
    QVBoxLayout *vboxLayout1;
    QPushButton *_btnOk;
    QPushButton *_btnCancel;
    QSpacerItem *spacerItem1;
    QTabWidget *_tab;
    QWidget *description;
    QVBoxLayout *vboxLayout2;
    QTextEdit *_tbDescrip;
    QWidget *lists;
    QVBoxLayout *vboxLayout3;
    QGroupBox *_listType;
    QHBoxLayout *hboxLayout2;
    QRadioButton *_staticList;
    QRadioButton *_dynamicList;
    QStackedWidget *_stack;
    QWidget *WStackPage;
    QVBoxLayout *vboxLayout4;
    QLabel *_lblStatic;
    QHBoxLayout *hboxLayout3;
    QTreeWidget *_listValues;
    QVBoxLayout *vboxLayout5;
    QPushButton *_add;
    QPushButton *_edit;
    QSpacerItem *spacerItem2;
    QPushButton *_remove;
    QWidget *dynamic;
    QVBoxLayout *vboxLayout6;
    QLabel *_lblDynamic;
    QTextEdit *_dynamicQuery;

    void setupUi(QDialog *ReportParameter)
    {
        if (ReportParameter->objectName().isEmpty())
            ReportParameter->setObjectName(QString::fromUtf8("ReportParameter"));
        ReportParameter->resize(458, 362);
        vboxLayout = new QVBoxLayout(ReportParameter);
        vboxLayout->setSpacing(5);
        vboxLayout->setContentsMargins(5, 5, 5, 5);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _lblName = new QLabel(ReportParameter);
        _lblName->setObjectName(QString::fromUtf8("_lblName"));
        _lblName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_lblName, 0, 0, 1, 1);

        _lblType = new QLabel(ReportParameter);
        _lblType->setObjectName(QString::fromUtf8("_lblType"));
        _lblType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_lblType, 1, 0, 1, 1);

        _leName = new QLineEdit(ReportParameter);
        _leName->setObjectName(QString::fromUtf8("_leName"));

        gridLayout->addWidget(_leName, 0, 1, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        _cbType = new QComboBox(ReportParameter);
        _cbType->setObjectName(QString::fromUtf8("_cbType"));

        hboxLayout1->addWidget(_cbType);

        _active = new QCheckBox(ReportParameter);
        _active->setObjectName(QString::fromUtf8("_active"));

        hboxLayout1->addWidget(_active);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);


        gridLayout->addLayout(hboxLayout1, 1, 1, 1, 1);

        _leDefault = new QLineEdit(ReportParameter);
        _leDefault->setObjectName(QString::fromUtf8("_leDefault"));

        gridLayout->addWidget(_leDefault, 2, 1, 1, 1);

        _lblDefault = new QLabel(ReportParameter);
        _lblDefault->setObjectName(QString::fromUtf8("_lblDefault"));
        _lblDefault->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_lblDefault, 2, 0, 1, 1);


        hboxLayout->addLayout(gridLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        _btnOk = new QPushButton(ReportParameter);
        _btnOk->setObjectName(QString::fromUtf8("_btnOk"));

        vboxLayout1->addWidget(_btnOk);

        _btnCancel = new QPushButton(ReportParameter);
        _btnCancel->setObjectName(QString::fromUtf8("_btnCancel"));

        vboxLayout1->addWidget(_btnCancel);

        spacerItem1 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        vboxLayout1->addItem(spacerItem1);


        hboxLayout->addLayout(vboxLayout1);


        vboxLayout->addLayout(hboxLayout);

        _tab = new QTabWidget(ReportParameter);
        _tab->setObjectName(QString::fromUtf8("_tab"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(_tab->sizePolicy().hasHeightForWidth());
        _tab->setSizePolicy(sizePolicy);
        description = new QWidget();
        description->setObjectName(QString::fromUtf8("description"));
        vboxLayout2 = new QVBoxLayout(description);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        _tbDescrip = new QTextEdit(description);
        _tbDescrip->setObjectName(QString::fromUtf8("_tbDescrip"));

        vboxLayout2->addWidget(_tbDescrip);

        _tab->addTab(description, QString());
        lists = new QWidget();
        lists->setObjectName(QString::fromUtf8("lists"));
        vboxLayout3 = new QVBoxLayout(lists);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        _listType = new QGroupBox(lists);
        _listType->setObjectName(QString::fromUtf8("_listType"));
        hboxLayout2 = new QHBoxLayout(_listType);
        hboxLayout2->setSpacing(5);
        hboxLayout2->setContentsMargins(5, 5, 5, 5);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        _staticList = new QRadioButton(_listType);
        _staticList->setObjectName(QString::fromUtf8("_staticList"));
        _staticList->setChecked(true);

        hboxLayout2->addWidget(_staticList);

        _dynamicList = new QRadioButton(_listType);
        _dynamicList->setObjectName(QString::fromUtf8("_dynamicList"));

        hboxLayout2->addWidget(_dynamicList);


        vboxLayout3->addWidget(_listType);

        _stack = new QStackedWidget(lists);
        _stack->setObjectName(QString::fromUtf8("_stack"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_stack->sizePolicy().hasHeightForWidth());
        _stack->setSizePolicy(sizePolicy1);
        WStackPage = new QWidget();
        WStackPage->setObjectName(QString::fromUtf8("WStackPage"));
        vboxLayout4 = new QVBoxLayout(WStackPage);
        vboxLayout4->setSpacing(0);
        vboxLayout4->setContentsMargins(0, 0, 0, 0);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        _lblStatic = new QLabel(WStackPage);
        _lblStatic->setObjectName(QString::fromUtf8("_lblStatic"));

        vboxLayout4->addWidget(_lblStatic);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        _listValues = new QTreeWidget(WStackPage);
        _listValues->setObjectName(QString::fromUtf8("_listValues"));

        hboxLayout3->addWidget(_listValues);

        vboxLayout5 = new QVBoxLayout();
        vboxLayout5->setSpacing(6);
        vboxLayout5->setContentsMargins(0, 0, 0, 0);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        _add = new QPushButton(WStackPage);
        _add->setObjectName(QString::fromUtf8("_add"));

        vboxLayout5->addWidget(_add);

        _edit = new QPushButton(WStackPage);
        _edit->setObjectName(QString::fromUtf8("_edit"));
        _edit->setEnabled(false);

        vboxLayout5->addWidget(_edit);

        spacerItem2 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout5->addItem(spacerItem2);

        _remove = new QPushButton(WStackPage);
        _remove->setObjectName(QString::fromUtf8("_remove"));
        _remove->setEnabled(false);

        vboxLayout5->addWidget(_remove);


        hboxLayout3->addLayout(vboxLayout5);


        vboxLayout4->addLayout(hboxLayout3);

        _stack->addWidget(WStackPage);
        dynamic = new QWidget();
        dynamic->setObjectName(QString::fromUtf8("dynamic"));
        vboxLayout6 = new QVBoxLayout(dynamic);
        vboxLayout6->setSpacing(0);
        vboxLayout6->setContentsMargins(0, 0, 0, 0);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        _lblDynamic = new QLabel(dynamic);
        _lblDynamic->setObjectName(QString::fromUtf8("_lblDynamic"));

        vboxLayout6->addWidget(_lblDynamic);

        _dynamicQuery = new QTextEdit(dynamic);
        _dynamicQuery->setObjectName(QString::fromUtf8("_dynamicQuery"));

        vboxLayout6->addWidget(_dynamicQuery);

        _stack->addWidget(dynamic);

        vboxLayout3->addWidget(_stack);

        _tab->addTab(lists, QString());

        vboxLayout->addWidget(_tab);

#ifndef QT_NO_SHORTCUT
        _lblName->setBuddy(_leName);
        _lblType->setBuddy(_cbType);
        _lblDefault->setBuddy(_leDefault);
        _lblStatic->setBuddy(_listValues);
        _lblDynamic->setBuddy(_dynamicQuery);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(_leName, _cbType);
        QWidget::setTabOrder(_cbType, _active);
        QWidget::setTabOrder(_active, _leDefault);
        QWidget::setTabOrder(_leDefault, _tbDescrip);
        QWidget::setTabOrder(_tbDescrip, _tab);
        QWidget::setTabOrder(_tab, _staticList);
        QWidget::setTabOrder(_staticList, _listValues);
        QWidget::setTabOrder(_listValues, _add);
        QWidget::setTabOrder(_add, _edit);
        QWidget::setTabOrder(_edit, _remove);
        QWidget::setTabOrder(_remove, _dynamicList);
        QWidget::setTabOrder(_dynamicList, _dynamicQuery);
        QWidget::setTabOrder(_dynamicQuery, _btnOk);
        QWidget::setTabOrder(_btnOk, _btnCancel);

        retranslateUi(ReportParameter);
        QObject::connect(_btnOk, SIGNAL(clicked()), ReportParameter, SLOT(accept()));
        QObject::connect(_btnCancel, SIGNAL(clicked()), ReportParameter, SLOT(reject()));

        _tab->setCurrentIndex(0);
        _stack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ReportParameter);
    } // setupUi

    void retranslateUi(QDialog *ReportParameter)
    {
        ReportParameter->setWindowTitle(QApplication::translate("ReportParameter", "Parameter", 0, QApplication::UnicodeUTF8));
        _lblName->setText(QApplication::translate("ReportParameter", "Name:", 0, QApplication::UnicodeUTF8));
        _lblType->setText(QApplication::translate("ReportParameter", "Type:", 0, QApplication::UnicodeUTF8));
        _cbType->clear();
        _cbType->insertItems(0, QStringList()
         << QApplication::translate("ReportParameter", "String", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ReportParameter", "Integer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ReportParameter", "Double", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ReportParameter", "Bool", 0, QApplication::UnicodeUTF8)
        );
        _active->setText(QApplication::translate("ReportParameter", "Active", 0, QApplication::UnicodeUTF8));
        _lblDefault->setText(QApplication::translate("ReportParameter", "Default:", 0, QApplication::UnicodeUTF8));
        _btnOk->setText(QApplication::translate("ReportParameter", "&OK", 0, QApplication::UnicodeUTF8));
        _btnCancel->setText(QApplication::translate("ReportParameter", "&Cancel", 0, QApplication::UnicodeUTF8));
        _tab->setTabText(_tab->indexOf(description), QApplication::translate("ReportParameter", "Description", 0, QApplication::UnicodeUTF8));
        _listType->setTitle(QApplication::translate("ReportParameter", "List Type", 0, QApplication::UnicodeUTF8));
        _staticList->setText(QApplication::translate("ReportParameter", "Static", 0, QApplication::UnicodeUTF8));
        _dynamicList->setText(QApplication::translate("ReportParameter", "Dynamic", 0, QApplication::UnicodeUTF8));
        _lblStatic->setText(QApplication::translate("ReportParameter", "Static List Values:", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = _listValues->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ReportParameter", "Label", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ReportParameter", "Value", 0, QApplication::UnicodeUTF8));
        _add->setText(QApplication::translate("ReportParameter", "Add", 0, QApplication::UnicodeUTF8));
        _edit->setText(QApplication::translate("ReportParameter", "Edit", 0, QApplication::UnicodeUTF8));
        _remove->setText(QApplication::translate("ReportParameter", "Remove", 0, QApplication::UnicodeUTF8));
        _lblDynamic->setText(QApplication::translate("ReportParameter", "Dynamic List Query:", 0, QApplication::UnicodeUTF8));
        _tab->setTabText(_tab->indexOf(lists), QApplication::translate("ReportParameter", "Defined List", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReportParameter: public Ui_ReportParameter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTPARAMETER_H
