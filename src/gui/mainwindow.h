#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class TApplication;

class MainWindow:public QMainWindow {
      Q_OBJECT
public:
      MainWindow();
      ~MainWindow();
      void open();
      QMdiArea* getWorkspace() { return workSpace; }
      void showPeriod();

private slots:
      void showDictionaries();
      void showDocuments();
      void showReports();
      void showConfigs();
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

      QMenu* dictMenu;
      QMenu* operMenu;
      QMenu* reportMenu;
      QMenu* infoMenu;

      QToolBar* editToolBar;

      QAction* dictionariesAct;
      QAction* dictAct;
      QAction* operAct;
      QAction* reportAct;
      QAction* configAct;
      QAction* newAct;
      QAction* deleteAct;
      QAction* aboutAct;
      QAction* aboutQtAct;
      QAction* periodAct;
      QAction* exitAct;
      QMdiArea* workSpace;

/*
      QAction *operAct;
      QAction *reportAct;
      QAction *periodAct;
*/
};

#endif
