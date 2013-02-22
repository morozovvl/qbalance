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
** Form generated from reading UI file 'logoutput.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGOUTPUT_H
#define UI_LOGOUTPUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_LogOutput
{
public:
    QHBoxLayout *hboxLayout;
    QTextEdit *_log;

    void setupUi(QDialog *LogOutput)
    {
        if (LogOutput->objectName().isEmpty())
            LogOutput->setObjectName(QString::fromUtf8("LogOutput"));
        LogOutput->resize(600, 185);
        hboxLayout = new QHBoxLayout(LogOutput);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        _log = new QTextEdit(LogOutput);
        _log->setObjectName(QString::fromUtf8("_log"));

        hboxLayout->addWidget(_log);


        retranslateUi(LogOutput);

        QMetaObject::connectSlotsByName(LogOutput);
    } // setupUi

    void retranslateUi(QDialog *LogOutput)
    {
        LogOutput->setWindowTitle(QApplication::translate("LogOutput", "Log Output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogOutput: public Ui_LogOutput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGOUTPUT_H
