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

#include <QtWidgets/QMdiArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMainWindow>
#include "guifactory.h"

class TApplication;
class Dialog;

class MainWindow:public QMainWindow {
      Q_OBJECT
public:
      MainWindow(GUIFactory*);
      ~MainWindow();
      virtual void open();
      virtual void close();
      QMdiArea* getWorkSpace() { return workSpace; }
      QStatusBar* getStatusBar() { return statusBar(); }
      virtual void showPeriod();
      virtual QMdiSubWindow* appendMdiWindow(QWidget*);                     // Добавляет новое окно во многооконный интерфейс
      virtual QMdiSubWindow* findMdiWindow(QWidget*);
      virtual void removeMdiWindow(QMdiSubWindow*);                         // Удаляет окно из многооконного интерфейса
      void  showMenus();

private slots:
      void showDictionaries();
      void showDocuments();
      void showProcesses();
      void showReports();
      void showQueries();
      void showConfigs();
      void showMessagesWindow();
      void saveCustomization();
      void saveFile();
      void beep();
      void printReportWithoutCleaning();
      void printReportWithCleaning();
      void continuePrint();
      void cancelCheck();
      void printEKLZReport();
      void printProcessedEKLZReport();
      void EKLZinterrupt();
      void printReturnSaleCheck();
      void terminalVerificationResults();
      void terminalControlRibbon();
      void newRecord();
      void deleteRecord();
      void about();
      void setPeriod();
      void closeEvent();
      void wikiQt();
      void vkQt();


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
      QMenu* serviceMenu;
      QMenu* frMenu;
      QMenu* terminalMenu;
      QMenu* infoMenu;
      QMenu* loadFileMenu;

      QToolBar* editToolBar;

      QAction* dictionariesAct;
      QAction* dictAct;
      QAction* operAct;
      QAction* processAct;
      QAction* reportAct;
      QAction* queryAct;
      QAction* configAct;
      QAction* newAct;
      QAction* deleteAct;
      QAction* aboutAct;
      QAction* aboutQtAct;
      QAction* wikiQtAct;
      QAction* vkQtAct;
      QAction* periodAct;
      QAction* showMessageWindow;
      QAction* saveCustomAct;
      QAction* loadScriptFileAct;
      QAction* loadReportFileAct;
      QAction* loadFormFileAct;
      QAction* saveFileAct;
      QAction* beepAct;
      QAction* printReportWithoutCleaningAct;
      QAction* printReportWithCleaningAct;
      QAction* continuePrintAct;
      QAction* cancelCheckAct;
      QAction* printEKLZReportAct;
      QAction* printProcessedEKLZReportAct;
      QAction* EKLZinterruptAct;
      QAction* printReturnSaleCheckAct;
      QAction* verificationResultsAct;
      QAction* controlRibbonAct;
      QAction* exitAct;


      QMdiArea* workSpace;

      TApplication* app;

/*
      QAction *operAct;
      QAction *reportAct;
      QAction *periodAct;
*/
};

#endif
