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
** Form generated from reading UI file 'mqledit.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQLEDIT_H
#define UI_MQLEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MQLEdit
{
public:
    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *filePrintAction;
    QAction *fileExitAction;
    QAction *editUndoAction;
    QAction *editRedoAction;
    QAction *editCutAction;
    QAction *editCopyAction;
    QAction *editPasteAction;
    QAction *editFindAction;
    QAction *helpContentsAction;
    QAction *helpIndexAction;
    QAction *helpAboutAction;
    QAction *fileDatabaseAction;
    QAction *fileDatabaseConnectAction;
    QAction *fileDatabaseDisconnectAction;
    QAction *fileUnnamedAction;
    QAction *viewParameter_ListAction;
    QAction *viewLog_OutputAction;
    QAction *viewResultsAction;
    QAction *toolsParse_QueryAction;
    QAction *toolsExecute_QueryAction;
    QAction *viewExecuted_SQLAction;
    QAction *fileDatabaseOpenAction;
    QAction *fileDatabaseSaveAsAction;
    QAction *toolsTest_ModeAction;
    QAction *searchForParametersAction;
    QVBoxLayout *verticalLayout;
    QMenuBar *MenuBar;
    QMenu *ToolsMenu;
    QMenu *helpMenu;
    QMenu *ViewMenu;
    QMenu *editMenu;
    QMenu *fileMenu;
    QToolBar *toolBar;
    QVBoxLayout *vboxLayout;
    QTextEdit *_text;

    void setupUi(QWidget *MQLEdit)
    {
        if (MQLEdit->objectName().isEmpty())
            MQLEdit->setObjectName(QString::fromUtf8("MQLEdit"));
        MQLEdit->resize(800, 600);
        fileNewAction = new QAction(MQLEdit);
        fileNewAction->setObjectName(QString::fromUtf8("fileNewAction"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/document_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileNewAction->setIcon(icon);
        fileOpenAction = new QAction(MQLEdit);
        fileOpenAction->setObjectName(QString::fromUtf8("fileOpenAction"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/folder_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileOpenAction->setIcon(icon1);
        fileSaveAction = new QAction(MQLEdit);
        fileSaveAction->setObjectName(QString::fromUtf8("fileSaveAction"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/diskette_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileSaveAction->setIcon(icon2);
        fileSaveAsAction = new QAction(MQLEdit);
        fileSaveAsAction->setObjectName(QString::fromUtf8("fileSaveAsAction"));
        filePrintAction = new QAction(MQLEdit);
        filePrintAction->setObjectName(QString::fromUtf8("filePrintAction"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/printer_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        filePrintAction->setIcon(icon3);
        fileExitAction = new QAction(MQLEdit);
        fileExitAction->setObjectName(QString::fromUtf8("fileExitAction"));
        editUndoAction = new QAction(MQLEdit);
        editUndoAction->setObjectName(QString::fromUtf8("editUndoAction"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/undo_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        editUndoAction->setIcon(icon4);
        editRedoAction = new QAction(MQLEdit);
        editRedoAction->setObjectName(QString::fromUtf8("editRedoAction"));
        editCutAction = new QAction(MQLEdit);
        editCutAction->setObjectName(QString::fromUtf8("editCutAction"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/scissors_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        editCutAction->setIcon(icon5);
        editCopyAction = new QAction(MQLEdit);
        editCopyAction->setObjectName(QString::fromUtf8("editCopyAction"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/copy_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        editCopyAction->setIcon(icon6);
        editPasteAction = new QAction(MQLEdit);
        editPasteAction->setObjectName(QString::fromUtf8("editPasteAction"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/paste_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        editPasteAction->setIcon(icon7);
        editFindAction = new QAction(MQLEdit);
        editFindAction->setObjectName(QString::fromUtf8("editFindAction"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("image9"), QSize(), QIcon::Normal, QIcon::Off);
        editFindAction->setIcon(icon8);
        helpContentsAction = new QAction(MQLEdit);
        helpContentsAction->setObjectName(QString::fromUtf8("helpContentsAction"));
        helpIndexAction = new QAction(MQLEdit);
        helpIndexAction->setObjectName(QString::fromUtf8("helpIndexAction"));
        helpAboutAction = new QAction(MQLEdit);
        helpAboutAction->setObjectName(QString::fromUtf8("helpAboutAction"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/help_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpAboutAction->setIcon(icon9);
        fileDatabaseAction = new QAction(MQLEdit);
        fileDatabaseAction->setObjectName(QString::fromUtf8("fileDatabaseAction"));
        fileDatabaseConnectAction = new QAction(MQLEdit);
        fileDatabaseConnectAction->setObjectName(QString::fromUtf8("fileDatabaseConnectAction"));
        fileDatabaseDisconnectAction = new QAction(MQLEdit);
        fileDatabaseDisconnectAction->setObjectName(QString::fromUtf8("fileDatabaseDisconnectAction"));
        fileUnnamedAction = new QAction(MQLEdit);
        fileUnnamedAction->setObjectName(QString::fromUtf8("fileUnnamedAction"));
        viewParameter_ListAction = new QAction(MQLEdit);
        viewParameter_ListAction->setObjectName(QString::fromUtf8("viewParameter_ListAction"));
        viewLog_OutputAction = new QAction(MQLEdit);
        viewLog_OutputAction->setObjectName(QString::fromUtf8("viewLog_OutputAction"));
        viewResultsAction = new QAction(MQLEdit);
        viewResultsAction->setObjectName(QString::fromUtf8("viewResultsAction"));
        toolsParse_QueryAction = new QAction(MQLEdit);
        toolsParse_QueryAction->setObjectName(QString::fromUtf8("toolsParse_QueryAction"));
        toolsExecute_QueryAction = new QAction(MQLEdit);
        toolsExecute_QueryAction->setObjectName(QString::fromUtf8("toolsExecute_QueryAction"));
        viewExecuted_SQLAction = new QAction(MQLEdit);
        viewExecuted_SQLAction->setObjectName(QString::fromUtf8("viewExecuted_SQLAction"));
        fileDatabaseOpenAction = new QAction(MQLEdit);
        fileDatabaseOpenAction->setObjectName(QString::fromUtf8("fileDatabaseOpenAction"));
        fileDatabaseSaveAsAction = new QAction(MQLEdit);
        fileDatabaseSaveAsAction->setObjectName(QString::fromUtf8("fileDatabaseSaveAsAction"));
        toolsTest_ModeAction = new QAction(MQLEdit);
        toolsTest_ModeAction->setObjectName(QString::fromUtf8("toolsTest_ModeAction"));
        toolsTest_ModeAction->setCheckable(true);
        toolsTest_ModeAction->setChecked(true);
        searchForParametersAction = new QAction(MQLEdit);
        searchForParametersAction->setObjectName(QString::fromUtf8("searchForParametersAction"));
        verticalLayout = new QVBoxLayout(MQLEdit);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        MenuBar = new QMenuBar(MQLEdit);
        MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
        ToolsMenu = new QMenu(MenuBar);
        ToolsMenu->setObjectName(QString::fromUtf8("ToolsMenu"));
        helpMenu = new QMenu(MenuBar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));
        ViewMenu = new QMenu(MenuBar);
        ViewMenu->setObjectName(QString::fromUtf8("ViewMenu"));
        editMenu = new QMenu(MenuBar);
        editMenu->setObjectName(QString::fromUtf8("editMenu"));
        fileMenu = new QMenu(MenuBar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));

        verticalLayout->addWidget(MenuBar);

        toolBar = new QToolBar(MQLEdit);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(toolBar);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        _text = new QTextEdit(MQLEdit);
        _text->setObjectName(QString::fromUtf8("_text"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        _text->setFont(font);

        vboxLayout->addWidget(_text);


        verticalLayout->addLayout(vboxLayout);


        MenuBar->addAction(fileMenu->menuAction());
        MenuBar->addAction(editMenu->menuAction());
        MenuBar->addAction(ViewMenu->menuAction());
        MenuBar->addAction(ToolsMenu->menuAction());
        MenuBar->addAction(helpMenu->menuAction());
        ToolsMenu->addAction(toolsParse_QueryAction);
        ToolsMenu->addAction(toolsExecute_QueryAction);
        ToolsMenu->addSeparator();
        ToolsMenu->addAction(toolsTest_ModeAction);
        ToolsMenu->addSeparator();
        ToolsMenu->addAction(searchForParametersAction);
        helpMenu->addAction(helpContentsAction);
        helpMenu->addAction(helpIndexAction);
        helpMenu->addSeparator();
        helpMenu->addAction(helpAboutAction);
        ViewMenu->addAction(viewParameter_ListAction);
        ViewMenu->addAction(viewLog_OutputAction);
        ViewMenu->addAction(viewResultsAction);
        ViewMenu->addAction(viewExecuted_SQLAction);
        editMenu->addAction(editUndoAction);
        editMenu->addAction(editRedoAction);
        editMenu->addSeparator();
        editMenu->addAction(editCutAction);
        editMenu->addAction(editCopyAction);
        editMenu->addAction(editPasteAction);
        editMenu->addSeparator();
        editMenu->addAction(editFindAction);
        fileMenu->addAction(fileNewAction);
        fileMenu->addAction(fileOpenAction);
        fileMenu->addAction(fileSaveAction);
        fileMenu->addAction(fileSaveAsAction);
        fileMenu->addSeparator();
        fileMenu->addAction(fileDatabaseConnectAction);
        fileMenu->addAction(fileDatabaseDisconnectAction);
        fileMenu->addAction(fileDatabaseOpenAction);
        fileMenu->addAction(fileDatabaseSaveAsAction);
        fileMenu->addSeparator();
        fileMenu->addAction(filePrintAction);
        fileMenu->addSeparator();
        fileMenu->addAction(fileExitAction);
        toolBar->addAction(fileNewAction);
        toolBar->addAction(fileOpenAction);
        toolBar->addAction(fileSaveAction);
        toolBar->addSeparator();
        toolBar->addAction(editUndoAction);
        toolBar->addSeparator();
        toolBar->addAction(editCutAction);
        toolBar->addAction(editCopyAction);
        toolBar->addAction(editPasteAction);
        toolBar->addAction(helpAboutAction);

        retranslateUi(MQLEdit);
        QObject::connect(editUndoAction, SIGNAL(activated()), _text, SLOT(undo()));
        QObject::connect(editRedoAction, SIGNAL(activated()), _text, SLOT(redo()));
        QObject::connect(editCutAction, SIGNAL(activated()), _text, SLOT(cut()));
        QObject::connect(editCopyAction, SIGNAL(activated()), _text, SLOT(copy()));
        QObject::connect(editPasteAction, SIGNAL(activated()), _text, SLOT(paste()));

        QMetaObject::connectSlotsByName(MQLEdit);
    } // setupUi

    void retranslateUi(QWidget *MQLEdit)
    {
        MQLEdit->setWindowTitle(QApplication::translate("MQLEdit", "[*]MetaSQL Editor", 0, QApplication::UnicodeUTF8));
        fileNewAction->setText(QApplication::translate("MQLEdit", "&New", 0, QApplication::UnicodeUTF8));
        fileNewAction->setIconText(QApplication::translate("MQLEdit", "New", 0, QApplication::UnicodeUTF8));
        fileNewAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        fileOpenAction->setText(QApplication::translate("MQLEdit", "&Open...", 0, QApplication::UnicodeUTF8));
        fileOpenAction->setIconText(QApplication::translate("MQLEdit", "Open", 0, QApplication::UnicodeUTF8));
        fileOpenAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        fileSaveAction->setText(QApplication::translate("MQLEdit", "&Save", 0, QApplication::UnicodeUTF8));
        fileSaveAction->setIconText(QApplication::translate("MQLEdit", "Save", 0, QApplication::UnicodeUTF8));
        fileSaveAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        fileSaveAsAction->setText(QApplication::translate("MQLEdit", "Save &As... (File)", 0, QApplication::UnicodeUTF8));
        fileSaveAsAction->setIconText(QApplication::translate("MQLEdit", "Save As", 0, QApplication::UnicodeUTF8));
        fileSaveAsAction->setShortcut(QString());
        filePrintAction->setText(QApplication::translate("MQLEdit", "&Print...", 0, QApplication::UnicodeUTF8));
        filePrintAction->setIconText(QApplication::translate("MQLEdit", "Print", 0, QApplication::UnicodeUTF8));
        filePrintAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        fileExitAction->setText(QApplication::translate("MQLEdit", "E&xit", 0, QApplication::UnicodeUTF8));
        fileExitAction->setIconText(QApplication::translate("MQLEdit", "Exit", 0, QApplication::UnicodeUTF8));
        fileExitAction->setShortcut(QString());
        editUndoAction->setText(QApplication::translate("MQLEdit", "&Undo", 0, QApplication::UnicodeUTF8));
        editUndoAction->setIconText(QApplication::translate("MQLEdit", "Undo", 0, QApplication::UnicodeUTF8));
        editUndoAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        editRedoAction->setText(QApplication::translate("MQLEdit", "&Redo", 0, QApplication::UnicodeUTF8));
        editRedoAction->setIconText(QApplication::translate("MQLEdit", "Redo", 0, QApplication::UnicodeUTF8));
        editRedoAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+Y", 0, QApplication::UnicodeUTF8));
        editCutAction->setText(QApplication::translate("MQLEdit", "&Cut", 0, QApplication::UnicodeUTF8));
        editCutAction->setIconText(QApplication::translate("MQLEdit", "Cut", 0, QApplication::UnicodeUTF8));
        editCutAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        editCopyAction->setText(QApplication::translate("MQLEdit", "C&opy", 0, QApplication::UnicodeUTF8));
        editCopyAction->setIconText(QApplication::translate("MQLEdit", "Copy", 0, QApplication::UnicodeUTF8));
        editCopyAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        editPasteAction->setText(QApplication::translate("MQLEdit", "&Paste", 0, QApplication::UnicodeUTF8));
        editPasteAction->setIconText(QApplication::translate("MQLEdit", "Paste", 0, QApplication::UnicodeUTF8));
        editPasteAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        editFindAction->setText(QApplication::translate("MQLEdit", "&Find...", 0, QApplication::UnicodeUTF8));
        editFindAction->setIconText(QApplication::translate("MQLEdit", "Find", 0, QApplication::UnicodeUTF8));
        editFindAction->setShortcut(QApplication::translate("MQLEdit", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        helpContentsAction->setText(QApplication::translate("MQLEdit", "&Contents...", 0, QApplication::UnicodeUTF8));
        helpContentsAction->setIconText(QApplication::translate("MQLEdit", "Contents", 0, QApplication::UnicodeUTF8));
        helpContentsAction->setShortcut(QString());
        helpIndexAction->setText(QApplication::translate("MQLEdit", "&Index...", 0, QApplication::UnicodeUTF8));
        helpIndexAction->setIconText(QApplication::translate("MQLEdit", "Index", 0, QApplication::UnicodeUTF8));
        helpIndexAction->setShortcut(QString());
        helpAboutAction->setText(QApplication::translate("MQLEdit", "&About", 0, QApplication::UnicodeUTF8));
        helpAboutAction->setIconText(QApplication::translate("MQLEdit", "About", 0, QApplication::UnicodeUTF8));
        helpAboutAction->setShortcut(QString());
        fileDatabaseAction->setText(QApplication::translate("MQLEdit", "Database", 0, QApplication::UnicodeUTF8));
        fileDatabaseAction->setIconText(QApplication::translate("MQLEdit", "Database", 0, QApplication::UnicodeUTF8));
        fileDatabaseConnectAction->setText(QApplication::translate("MQLEdit", "Connect to Database...", 0, QApplication::UnicodeUTF8));
        fileDatabaseConnectAction->setIconText(QApplication::translate("MQLEdit", "Connect...", 0, QApplication::UnicodeUTF8));
        fileDatabaseDisconnectAction->setText(QApplication::translate("MQLEdit", "Disconnect From Database", 0, QApplication::UnicodeUTF8));
        fileDatabaseDisconnectAction->setIconText(QApplication::translate("MQLEdit", "Disconnect", 0, QApplication::UnicodeUTF8));
        fileUnnamedAction->setText(QApplication::translate("MQLEdit", "Unnamed", 0, QApplication::UnicodeUTF8));
        fileUnnamedAction->setIconText(QApplication::translate("MQLEdit", "Unnamed", 0, QApplication::UnicodeUTF8));
        viewParameter_ListAction->setText(QApplication::translate("MQLEdit", "Parameter List...", 0, QApplication::UnicodeUTF8));
        viewParameter_ListAction->setIconText(QApplication::translate("MQLEdit", "Parameter List...", 0, QApplication::UnicodeUTF8));
        viewLog_OutputAction->setText(QApplication::translate("MQLEdit", "Log Output...", 0, QApplication::UnicodeUTF8));
        viewLog_OutputAction->setIconText(QApplication::translate("MQLEdit", "Log Output...", 0, QApplication::UnicodeUTF8));
        viewResultsAction->setText(QApplication::translate("MQLEdit", "Results...", 0, QApplication::UnicodeUTF8));
        viewResultsAction->setIconText(QApplication::translate("MQLEdit", "Results...", 0, QApplication::UnicodeUTF8));
        toolsParse_QueryAction->setText(QApplication::translate("MQLEdit", "Parse Query", 0, QApplication::UnicodeUTF8));
        toolsParse_QueryAction->setIconText(QApplication::translate("MQLEdit", "Parse Query", 0, QApplication::UnicodeUTF8));
        toolsExecute_QueryAction->setText(QApplication::translate("MQLEdit", "Execute Query", 0, QApplication::UnicodeUTF8));
        toolsExecute_QueryAction->setIconText(QApplication::translate("MQLEdit", "Execute Query", 0, QApplication::UnicodeUTF8));
        viewExecuted_SQLAction->setText(QApplication::translate("MQLEdit", "Executed SQL...", 0, QApplication::UnicodeUTF8));
        viewExecuted_SQLAction->setIconText(QApplication::translate("MQLEdit", "Executed SQL...", 0, QApplication::UnicodeUTF8));
        fileDatabaseOpenAction->setText(QApplication::translate("MQLEdit", "Open... (Database)", 0, QApplication::UnicodeUTF8));
        fileDatabaseSaveAsAction->setText(QApplication::translate("MQLEdit", "Save As... (Database)", 0, QApplication::UnicodeUTF8));
        toolsTest_ModeAction->setText(QApplication::translate("MQLEdit", "Test Mode", 0, QApplication::UnicodeUTF8));
        searchForParametersAction->setText(QApplication::translate("MQLEdit", "Search For Parameters", 0, QApplication::UnicodeUTF8));
        ToolsMenu->setTitle(QApplication::translate("MQLEdit", "&Tools", 0, QApplication::UnicodeUTF8));
        helpMenu->setTitle(QApplication::translate("MQLEdit", "&Help", 0, QApplication::UnicodeUTF8));
        ViewMenu->setTitle(QApplication::translate("MQLEdit", "&View", 0, QApplication::UnicodeUTF8));
        editMenu->setTitle(QApplication::translate("MQLEdit", "&Edit", 0, QApplication::UnicodeUTF8));
        fileMenu->setTitle(QApplication::translate("MQLEdit", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MQLEdit: public Ui_MQLEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQLEDIT_H
