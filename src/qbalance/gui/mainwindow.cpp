/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QtGui/QMenuBar>
#include <QtGui/QMdiSubWindow>
#include <QDebug>
#include "../kernel/app.h"
#include "mainwindow.h"
#include "dialog.h"


MainWindow::MainWindow(GUIFactory* par) {
    parent = par;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    workSpace = new QMdiArea(this);
}

MainWindow::~MainWindow() {
    delete workSpace;
}

void MainWindow::open() {
    setCentralWidget(workSpace);
    readSettings();
    statusBar()->showMessage("");
}

void MainWindow::closeEvent() {
    writeSettings();
    close();
}

void MainWindow::showDictionaries() {
    TApplication::exemplar()->showDictionaries();
}

void MainWindow::showDocuments() {
    TApplication::exemplar()->showDocuments();
}

void MainWindow::showReports() {
    TApplication::exemplar()->showReports();
}

void MainWindow::showConfigs() {
    TApplication::exemplar()->showConfigs();
}

void MainWindow::newRecord() {
}

void MainWindow::deleteRecord() {
}

void MainWindow::about()
{
      QMessageBox::about(this, QObject::trUtf8("About Application"),
            QObject::trUtf8("The <b>Application</b> example demonstrates how to "
                  "write modern GUI applications using Qt, with a menu bar, "
                  "toolbars, and a status bar."));
}

void MainWindow::createActions()
{
      dictionariesAct = new QAction(this);
      dictionariesAct->setShortcut(QObject::trUtf8("Ctrl+N"));
      dictionariesAct->setStatusTip(QObject::trUtf8("Открыть список справочников"));
      connect(dictionariesAct, SIGNAL(triggered()), this, SLOT(showDictionaries()));

      newAct = new QAction(QIcon(":buttonAdd"), "", this);
      newAct->setShortcut(QObject::trUtf8("Ctrl+N"));
      newAct->setStatusTip(QObject::trUtf8("Добавить новую запись"));
      connect(newAct, SIGNAL(triggered()), this, SLOT(newRecord()));

      deleteAct = new QAction(QIcon(":buttonDelete"), "", this);
      deleteAct->setShortcut(QObject::trUtf8("Ctrl+D"));
      deleteAct->setStatusTip(QObject::trUtf8("Удалить запись"));
      connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteRecord()));

      periodAct = new QAction(QIcon(":buttonCalendar"), "", this);
      periodAct->setStatusTip(QObject::trUtf8("Установить рабочий период"));
      periodAct->setToolTip(QObject::trUtf8("Текущий рабочий период"));
      QFont periodFont;
      periodFont.setBold(true);
      periodAct->setFont(periodFont);
      showPeriod();
      connect(periodAct, SIGNAL(triggered()), this, SLOT(setPeriod()));
}

void MainWindow::createMenus()
{
    dictAct = menuBar()->addAction(QObject::trUtf8("&Справочники"));
    connect(dictAct, SIGNAL(triggered()), this, SLOT(showDictionaries()));

    operAct = menuBar()->addAction(QObject::trUtf8("&Операции"));
    connect(operAct, SIGNAL(triggered()), this, SLOT(showDocuments()));

    reportAct = menuBar()->addAction(QObject::trUtf8("&Отчеты"));
    connect(reportAct, SIGNAL(triggered()), this, SLOT(showReports()));

    configAct = menuBar()->addAction(QObject::trUtf8("&Настройки"));
    connect(configAct, SIGNAL(triggered()), this, SLOT(showConfigs()));

    infoMenu = menuBar()->addMenu(QObject::trUtf8("&Помощь"));

//    aboutAct = infoMenu->addAction(QObject::trUtf8("О &программе..."));
//    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = infoMenu->addAction(QObject::trUtf8("О &библиотеке Qt..."));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    exitAct = menuBar()->addAction(QObject::trUtf8("&Выход"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(closeEvent()));
}

void MainWindow::createToolBars()
{
      editToolBar = addToolBar(QObject::trUtf8("Edit"));
//      editToolBar->addAction(newAct);
//      editToolBar->addAction(deleteAct);
      editToolBar->addAction(periodAct);
      editToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::createStatusBar()
{
//      statusBar()->showMessage(QObject::trUtf8("Готово"));
}

void MainWindow::setPeriod() {
    TApplication::exemplar()->setPeriod();
    showPeriod();
}

void MainWindow::showPeriod() {
    QString period;
    period = TApplication::exemplar()->getBeginDate().toString("dd.MM.yyyy") + " - " + TApplication::exemplar()->getEndDate().toString("dd.MM.yyyy");
    periodAct->setIconText(period);
}

void MainWindow::readSettings() {
      QSettings settings;
      if (settings.status() == QSettings::NoError) {
          settings.beginGroup("mainwindow");
          move(settings.value("x", 100).toInt(), settings.value("y", 100).toInt());
          resize(settings.value("width", 400).toInt(), settings.value("height", 200).toInt());
          settings.endGroup();
      }
}

void MainWindow::writeSettings()
{
      QSettings settings;
      settings.beginGroup("mainwindow");
      settings.setValue("x", pos().x());
      settings.setValue("y", pos().y());
      settings.setValue("width", size().width());
      settings.setValue("height", size().height());
      settings.endGroup();
}


QMdiSubWindow* MainWindow::appendMdiWindow(QWidget* dialogWidget)
{
    if (dialogWidget != 0)
    {
        // Сначала попытаемся найти окно QMdiSubWindow, в котором виджет dialogWidget отображался ранее
        foreach (QMdiSubWindow *subWindow, workSpace->subWindowList()) {
            Dialog* widget = qobject_cast<Dialog*>(subWindow->widget());
            if (widget == dialogWidget)
                return subWindow;
        }
        // Такой виджет видимо ранее не отображался, поэтому создадим новое окно
        QMdiSubWindow* subWindow = new QMdiSubWindow(workSpace);
        subWindow->hide();
        subWindow->setWidget(dialogWidget);
        return workSpace->addSubWindow(subWindow);
    }
    return 0;
}


void MainWindow::removeMdiWindow(QMdiSubWindow* subWindow)
{
    if (subWindow != 0)
    {
        workSpace->setActiveSubWindow(subWindow);
        subWindow->setWidget(0);    // Обнулим указатель на виджет, чтобы при удалении подокна оно одновременно не удалило и виджет
        workSpace->removeSubWindow(subWindow);
    }

}
