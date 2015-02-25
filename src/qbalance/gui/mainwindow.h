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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMdiArea>
#include <QtGui/QStatusBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QMainWindow>
#include "guifactory.h"
#include "mymdisubwindow.h"

class TApplication;
class Dialog;

class MainWindow:public QMainWindow {
      Q_OBJECT
public:
      MainWindow(GUIFactory*);
      ~MainWindow();
      virtual void open();
      QMdiArea* getWorkSpace() { return workSpace; }
      QStatusBar* getStatusBar() { return statusBar(); }
      virtual void showPeriod();
      virtual MyMdiSubWindow* appendMdiWindow(QWidget*);                     // Добавляет новое окно во многооконный интерфейс
      virtual MyMdiSubWindow* findMdiWindow(QWidget*);
      virtual void removeMdiWindow(MyMdiSubWindow*);                         // Удаляет окно из многооконного интерфейса

private slots:
      void showDictionaries();
      void showDocuments();
      void showProcesses();
      void showReports();
      void showConfigs();
      void showMessagesWindow();
      void saveCustomization();
      void printReportWithoutCleaning();
      void printReportWithCleaning();
      void cancelCheck();
      void printEKLZReport();
      void newRecord();
      void deleteRecord();
      void about();
      void setPeriod();
      void closeEvent();

private:
      void createActions();
      void createMenus();
      void createToolBars();
      void createStatusBar();
      void readSettings();
      void writeSettings();

//      bool maybeSave();
//      void loadFile(const QString &fileName);
//      bool saveFile(const QString &fileName);
//      void setCurrentFile(const QString &fileName);
//      QString strippedName(const QString &fullFileName);

      GUIFactory* parent;
      QMenu* dictMenu;
      QMenu* operMenu;
      QMenu* reportMenu;
      QMenu* infoMenu;

      QToolBar* editToolBar;

      QAction* dictionariesAct;
      QAction* dictAct;
      QAction* operAct;
      QAction* processAct;
      QAction* reportAct;
      QAction* configAct;
      QAction* newAct;
      QAction* deleteAct;
      QAction* aboutAct;
      QAction* aboutQtAct;
      QAction* periodAct;
      QAction* showMessageWindow;
      QAction* saveCustomAct;
      QAction* printReportWithoutCleaningAct;
      QAction* printReportWithCleaningAct;
      QAction* cancelCheckAct;
      QAction* printEKLZReportAct;
      QAction* exitAct;
      QMdiArea* workSpace;

/*
      QAction *operAct;
      QAction *reportAct;
      QAction *periodAct;
*/
};

#endif
