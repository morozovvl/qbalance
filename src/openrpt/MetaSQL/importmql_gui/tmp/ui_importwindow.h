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
** Form generated from reading UI file 'importwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTWINDOW_H
#define UI_IMPORTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImportWindow
{
public:
    QAction *helpContentsAction;
    QAction *helpIndexAction;
    QAction *helpAboutAction;
    QAction *fileExitAction;
    QAction *fileOpenAction;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *_schemaLit;
    QComboBox *_schema;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox1;
    QHBoxLayout *horizontalLayout;
    QListWidget *_reports;
    QVBoxLayout *vboxLayout;
    QPushButton *_add;
    QPushButton *_remove;
    QFrame *line1;
    QPushButton *_import;
    QSpacerItem *spacerItem;
    QPushButton *_selectAll;
    QGroupBox *groupBox2;
    QVBoxLayout *vboxLayout1;
    QTextEdit *_log;
    QMenuBar *MenuBar;
    QMenu *unnamed;
    QMenu *helpMenu;

    void setupUi(QMainWindow *ImportWindow)
    {
        if (ImportWindow->objectName().isEmpty())
            ImportWindow->setObjectName(QString::fromUtf8("ImportWindow"));
        ImportWindow->resize(600, 486);
        helpContentsAction = new QAction(ImportWindow);
        helpContentsAction->setObjectName(QString::fromUtf8("helpContentsAction"));
        helpIndexAction = new QAction(ImportWindow);
        helpIndexAction->setObjectName(QString::fromUtf8("helpIndexAction"));
        helpAboutAction = new QAction(ImportWindow);
        helpAboutAction->setObjectName(QString::fromUtf8("helpAboutAction"));
        fileExitAction = new QAction(ImportWindow);
        fileExitAction->setObjectName(QString::fromUtf8("fileExitAction"));
        fileOpenAction = new QAction(ImportWindow);
        fileOpenAction->setObjectName(QString::fromUtf8("fileOpenAction"));
        widget = new QWidget(ImportWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 10, -1, 10);
        _schemaLit = new QLabel(widget);
        _schemaLit->setObjectName(QString::fromUtf8("_schemaLit"));

        horizontalLayout_3->addWidget(_schemaLit);

        _schema = new QComboBox(widget);
        _schema->setObjectName(QString::fromUtf8("_schema"));

        horizontalLayout_3->addWidget(_schema);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        groupBox1 = new QGroupBox(widget);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        horizontalLayout = new QHBoxLayout(groupBox1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        _reports = new QListWidget(groupBox1);
        _reports->setObjectName(QString::fromUtf8("_reports"));
        _reports->setSelectionMode(QAbstractItemView::ExtendedSelection);

        horizontalLayout->addWidget(_reports);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        _add = new QPushButton(groupBox1);
        _add->setObjectName(QString::fromUtf8("_add"));

        vboxLayout->addWidget(_add);

        _remove = new QPushButton(groupBox1);
        _remove->setObjectName(QString::fromUtf8("_remove"));

        vboxLayout->addWidget(_remove);

        line1 = new QFrame(groupBox1);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        vboxLayout->addWidget(line1);

        _import = new QPushButton(groupBox1);
        _import->setObjectName(QString::fromUtf8("_import"));

        vboxLayout->addWidget(_import);

        spacerItem = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        _selectAll = new QPushButton(groupBox1);
        _selectAll->setObjectName(QString::fromUtf8("_selectAll"));

        vboxLayout->addWidget(_selectAll);


        horizontalLayout->addLayout(vboxLayout);


        verticalLayout->addWidget(groupBox1);

        groupBox2 = new QGroupBox(widget);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        vboxLayout1 = new QVBoxLayout(groupBox2);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        _log = new QTextEdit(groupBox2);
        _log->setObjectName(QString::fromUtf8("_log"));
        _log->setReadOnly(true);

        vboxLayout1->addWidget(_log);


        verticalLayout->addWidget(groupBox2);

        ImportWindow->setCentralWidget(widget);
        MenuBar = new QMenuBar(ImportWindow);
        MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
        MenuBar->setGeometry(QRect(0, 0, 600, 22));
        unnamed = new QMenu(MenuBar);
        unnamed->setObjectName(QString::fromUtf8("unnamed"));
        helpMenu = new QMenu(MenuBar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));
        ImportWindow->setMenuBar(MenuBar);
        QWidget::setTabOrder(_reports, _add);
        QWidget::setTabOrder(_add, _remove);
        QWidget::setTabOrder(_remove, _import);
        QWidget::setTabOrder(_import, _selectAll);
        QWidget::setTabOrder(_selectAll, _log);

        MenuBar->addAction(unnamed->menuAction());
        MenuBar->addAction(helpMenu->menuAction());
        unnamed->addAction(fileOpenAction);
        unnamed->addSeparator();
        unnamed->addAction(fileExitAction);
        helpMenu->addAction(helpContentsAction);
        helpMenu->addAction(helpIndexAction);
        helpMenu->addSeparator();
        helpMenu->addAction(helpAboutAction);

        retranslateUi(ImportWindow);
        QObject::connect(_selectAll, SIGNAL(clicked()), _reports, SLOT(selectAll()));

        QMetaObject::connectSlotsByName(ImportWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ImportWindow)
    {
        ImportWindow->setWindowTitle(QApplication::translate("ImportWindow", "MetaSQL Import Tool", 0, QApplication::UnicodeUTF8));
        helpContentsAction->setText(QApplication::translate("ImportWindow", "&Contents...", 0, QApplication::UnicodeUTF8));
        helpContentsAction->setIconText(QApplication::translate("ImportWindow", "Contents", 0, QApplication::UnicodeUTF8));
        helpContentsAction->setShortcut(QString());
        helpIndexAction->setText(QApplication::translate("ImportWindow", "&Index...", 0, QApplication::UnicodeUTF8));
        helpIndexAction->setIconText(QApplication::translate("ImportWindow", "Index", 0, QApplication::UnicodeUTF8));
        helpIndexAction->setShortcut(QString());
        helpAboutAction->setText(QApplication::translate("ImportWindow", "&About", 0, QApplication::UnicodeUTF8));
        helpAboutAction->setIconText(QApplication::translate("ImportWindow", "About", 0, QApplication::UnicodeUTF8));
        helpAboutAction->setShortcut(QString());
        fileExitAction->setText(QApplication::translate("ImportWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        fileExitAction->setIconText(QApplication::translate("ImportWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        fileOpenAction->setText(QApplication::translate("ImportWindow", "&Add", 0, QApplication::UnicodeUTF8));
        fileOpenAction->setIconText(QApplication::translate("ImportWindow", "&Add", 0, QApplication::UnicodeUTF8));
        _schemaLit->setText(QApplication::translate("ImportWindow", "Import into schema:", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("ImportWindow", "MetaSQL Files", 0, QApplication::UnicodeUTF8));
        _add->setText(QApplication::translate("ImportWindow", "&Add", 0, QApplication::UnicodeUTF8));
        _add->setShortcut(QApplication::translate("ImportWindow", "Alt+A", 0, QApplication::UnicodeUTF8));
        _remove->setText(QApplication::translate("ImportWindow", "Remove", 0, QApplication::UnicodeUTF8));
        _import->setText(QApplication::translate("ImportWindow", "&Import", 0, QApplication::UnicodeUTF8));
        _import->setShortcut(QApplication::translate("ImportWindow", "Alt+I", 0, QApplication::UnicodeUTF8));
        _selectAll->setText(QApplication::translate("ImportWindow", "Select All", 0, QApplication::UnicodeUTF8));
        groupBox2->setTitle(QApplication::translate("ImportWindow", "Messages", 0, QApplication::UnicodeUTF8));
        unnamed->setTitle(QApplication::translate("ImportWindow", "&File", 0, QApplication::UnicodeUTF8));
        helpMenu->setTitle(QApplication::translate("ImportWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImportWindow: public Ui_ImportWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTWINDOW_H
