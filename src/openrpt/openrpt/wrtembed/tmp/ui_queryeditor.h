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
** Form generated from reading UI file 'queryeditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYEDITOR_H
#define UI_QUERYEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QueryEditor
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *hboxLayout;
    QLabel *labelName;
    QLineEdit *tbName;
    QGroupBox *_metasql;
    QGridLayout *gridLayout;
    QLabel *_mqlGroupLit;
    QComboBox *_mqlGroup;
    QLabel *_mqlNameLit;
    QComboBox *_mqlName;
    QVBoxLayout *vboxLayout;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QSpacerItem *spacerItem;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *labelQuery;
    QTextEdit *tbQuery;

    void setupUi(QDialog *QueryEditor)
    {
        if (QueryEditor->objectName().isEmpty())
            QueryEditor->setObjectName(QString::fromUtf8("QueryEditor"));
        QueryEditor->resize(497, 449);
        QueryEditor->setSizeGripEnabled(true);
        verticalLayout_3 = new QVBoxLayout(QueryEditor);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        labelName = new QLabel(QueryEditor);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        hboxLayout->addWidget(labelName);

        tbName = new QLineEdit(QueryEditor);
        tbName->setObjectName(QString::fromUtf8("tbName"));

        hboxLayout->addWidget(tbName);


        verticalLayout_2->addLayout(hboxLayout);

        _metasql = new QGroupBox(QueryEditor);
        _metasql->setObjectName(QString::fromUtf8("_metasql"));
        _metasql->setCheckable(true);
        _metasql->setChecked(false);
        gridLayout = new QGridLayout(_metasql);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _mqlGroupLit = new QLabel(_metasql);
        _mqlGroupLit->setObjectName(QString::fromUtf8("_mqlGroupLit"));
        _mqlGroupLit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_mqlGroupLit, 0, 0, 1, 1);

        _mqlGroup = new QComboBox(_metasql);
        _mqlGroup->setObjectName(QString::fromUtf8("_mqlGroup"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_mqlGroup->sizePolicy().hasHeightForWidth());
        _mqlGroup->setSizePolicy(sizePolicy);
        _mqlGroup->setEditable(true);

        gridLayout->addWidget(_mqlGroup, 0, 1, 1, 1);

        _mqlNameLit = new QLabel(_metasql);
        _mqlNameLit->setObjectName(QString::fromUtf8("_mqlNameLit"));
        _mqlNameLit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_mqlNameLit, 1, 0, 1, 1);

        _mqlName = new QComboBox(_metasql);
        _mqlName->setObjectName(QString::fromUtf8("_mqlName"));
        sizePolicy.setHeightForWidth(_mqlName->sizePolicy().hasHeightForWidth());
        _mqlName->setSizePolicy(sizePolicy);
        _mqlName->setEditable(true);

        gridLayout->addWidget(_mqlName, 1, 1, 1, 1);


        verticalLayout_2->addWidget(_metasql);


        horizontalLayout->addLayout(verticalLayout_2);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        btnOk = new QPushButton(QueryEditor);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setDefault(true);

        vboxLayout->addWidget(btnOk);

        btnCancel = new QPushButton(QueryEditor);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        vboxLayout->addWidget(btnCancel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);


        horizontalLayout->addLayout(vboxLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        frame = new QFrame(QueryEditor);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelQuery = new QLabel(frame);
        labelQuery->setObjectName(QString::fromUtf8("labelQuery"));

        verticalLayout->addWidget(labelQuery);

        tbQuery = new QTextEdit(frame);
        tbQuery->setObjectName(QString::fromUtf8("tbQuery"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        tbQuery->setFont(font);

        verticalLayout->addWidget(tbQuery);


        verticalLayout_3->addWidget(frame);

#ifndef QT_NO_SHORTCUT
        labelName->setBuddy(tbName);
        _mqlGroupLit->setBuddy(_mqlGroup);
        _mqlNameLit->setBuddy(_mqlName);
        labelQuery->setBuddy(tbQuery);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tbName, _metasql);
        QWidget::setTabOrder(_metasql, _mqlGroup);
        QWidget::setTabOrder(_mqlGroup, _mqlName);
        QWidget::setTabOrder(_mqlName, tbQuery);
        QWidget::setTabOrder(tbQuery, btnOk);
        QWidget::setTabOrder(btnOk, btnCancel);

        retranslateUi(QueryEditor);
        QObject::connect(btnOk, SIGNAL(clicked()), QueryEditor, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), QueryEditor, SLOT(reject()));
        QObject::connect(_metasql, SIGNAL(toggled(bool)), tbQuery, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(QueryEditor);
    } // setupUi

    void retranslateUi(QDialog *QueryEditor)
    {
        QueryEditor->setWindowTitle(QApplication::translate("QueryEditor", "Query Editor", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("QueryEditor", "Name:", 0, QApplication::UnicodeUTF8));
        _metasql->setTitle(QApplication::translate("QueryEditor", "Load MetaSQL from Database", 0, QApplication::UnicodeUTF8));
        _mqlGroupLit->setText(QApplication::translate("QueryEditor", "Group:", 0, QApplication::UnicodeUTF8));
        _mqlNameLit->setText(QApplication::translate("QueryEditor", "Name:", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("QueryEditor", "&OK", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("QueryEditor", "&Cancel", 0, QApplication::UnicodeUTF8));
        labelQuery->setText(QApplication::translate("QueryEditor", "Query:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QueryEditor: public Ui_QueryEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYEDITOR_H
