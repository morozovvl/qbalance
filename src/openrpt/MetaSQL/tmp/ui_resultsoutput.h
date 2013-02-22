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
** Form generated from reading UI file 'resultsoutput.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTSOUTPUT_H
#define UI_RESULTSOUTPUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ResultsOutput
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *_table;

    void setupUi(QDialog *ResultsOutput)
    {
        if (ResultsOutput->objectName().isEmpty())
            ResultsOutput->setObjectName(QString::fromUtf8("ResultsOutput"));
        ResultsOutput->resize(620, 257);
        verticalLayout = new QVBoxLayout(ResultsOutput);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        _table = new QTableWidget(ResultsOutput);
        _table->setObjectName(QString::fromUtf8("_table"));
        _table->setContextMenuPolicy(Qt::CustomContextMenu);
        _table->setSelectionMode(QAbstractItemView::ContiguousSelection);

        verticalLayout->addWidget(_table);


        retranslateUi(ResultsOutput);

        QMetaObject::connectSlotsByName(ResultsOutput);
    } // setupUi

    void retranslateUi(QDialog *ResultsOutput)
    {
        ResultsOutput->setWindowTitle(QApplication::translate("ResultsOutput", "Results Output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ResultsOutput: public Ui_ResultsOutput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTSOUTPUT_H
