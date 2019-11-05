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

#include <QtCore/QtGlobal>

#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>
#include "../kernel/app.h"
#include "mainwindow.h"
#include "dialog.h"
#include "formgrid.h"
#include "../kernel/dictionary.h"
#include "../gui/messagewindow.h"
#include "../kernel/tcpclient.h"
#include "../storage/filetype.h"
#include "../storage/dbfactory.h"
#include "../driverfr/driverfr.h"


MainWindow::MainWindow(GUIFactory* par)
{
    parent = par;
    createStatusBar();
    workSpace = new QMdiArea(this);
    workSpace->setActivationOrder(QMdiArea::ActivationHistoryOrder);
    workSpace->setAttribute(Qt::WA_DeleteOnClose);
    app = TApplication::exemplar();
}


MainWindow::~MainWindow()
{
    delete workSpace;
}


void MainWindow::open()
{
    setCentralWidget(workSpace);
    readSettings();
}


void MainWindow::close()
{
    writeSettings();
}



void  MainWindow::showMenus()
{
    createActions();
    createMenus();
    createToolBars();
}


void MainWindow::closeApp()
{
    QMainWindow::close();
}


void MainWindow::showDictionaries()
{
    app->showDictionaries();
}


void MainWindow::showDocuments()
{
    app->showDocuments();
}


void MainWindow::showProcesses()
{
    QString fileName = app->getProcessFile("обработка", app->getMainWindow(), reportMenu->contentsRect());
    if (fileName.size() > 0)
    {
        app->runScript(fileName);
    }
}


void MainWindow::showReports()
{
    app->showReports();
}


void MainWindow::showQueries()
{
    QString fileName = app->getReportFile("запросы", false, app->getMainWindow(), reportMenu->contentsRect());
    app->printReport(fileName);
}


void MainWindow::showConfigs()
{
    app->showConfigs();
}


void MainWindow::newRecord()
{
}

void MainWindow::deleteRecord()
{
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
/*
      dictionariesAct = new QAction(this);
      dictionariesAct->setShortcut(QObject::trUtf8("Ctrl+N"));
      dictionariesAct->setStatusTip(QObject::trUtf8("Открыть список справочников"));
      connect(dictionariesAct, SIGNAL(triggered()), this, SLOT(showDictionaries()));
*/
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

    processAct = menuBar()->addAction(QObject::trUtf8("&Обработки"));
    connect(processAct, SIGNAL(triggered()), this, SLOT(showProcesses()));

    reportMenu = menuBar()->addMenu(QObject::trUtf8("&Отчеты"));

    reportAct = reportMenu->addAction(QObject::trUtf8("&Отчеты"));
    connect(reportAct, SIGNAL(triggered()), this, SLOT(showReports()));

    queryAct = reportMenu->addAction(QObject::trUtf8("&Запросы"));
    connect(queryAct, SIGNAL(triggered()), this, SLOT(showQueries()));

    serviceMenu = menuBar()->addMenu(QObject::trUtf8("&Сервис"));
    frMenu = serviceMenu->addMenu(QObject::trUtf8("&Фискальный регистратор"));

    beepAct = frMenu->addAction(QObject::trUtf8("Сигнал"));
    connect(beepAct, SIGNAL(triggered()), this, SLOT(beep()));

    printReportWithoutCleaningAct = frMenu->addAction(QObject::trUtf8("Снять отчет без гашения"));
    connect(printReportWithoutCleaningAct, SIGNAL(triggered()), this, SLOT(printReportWithoutCleaning()));

    printReportWithCleaningAct = frMenu->addAction(QObject::trUtf8("Снять отчет с гашением"));
    connect(printReportWithCleaningAct, SIGNAL(triggered()), this, SLOT(printReportWithCleaning()));

    continuePrintAct = frMenu->addAction(QObject::trUtf8("Продолжить печать"));
    connect(continuePrintAct, SIGNAL(triggered()), this, SLOT(continuePrint()));

    cancelCheckAct = frMenu->addAction(QObject::trUtf8("Отмена чека"));
    connect(cancelCheckAct, SIGNAL(triggered()), this, SLOT(cancelCheck()));

    printEKLZReportAct = frMenu->addAction(QObject::trUtf8("Снять отчет ЭКЛЗ за последнюю не закрытую смену"));
    connect(printEKLZReportAct, SIGNAL(triggered()), this, SLOT(printEKLZReport()));

    printProcessedEKLZReportAct = frMenu->addAction(QObject::trUtf8("Снять обработанный отчет ЭКЛЗ за смену"));
    connect(printProcessedEKLZReportAct, SIGNAL(triggered()), this, SLOT(printProcessedEKLZReport()));

    EKLZinterruptAct = frMenu->addAction(QObject::trUtf8("Прекращение ЭКЛЗ"));
    connect(EKLZinterruptAct, SIGNAL(triggered()), this, SLOT(EKLZinterrupt()));

    printReturnSaleCheckAct = frMenu->addAction(QObject::trUtf8("Возврат продажи"));
    connect(printReturnSaleCheckAct, SIGNAL(triggered()), this, SLOT(printReturnSaleCheck()));

    terminalMenu = serviceMenu->addMenu(QObject::trUtf8("&Банковский терминал"));

    verificationResultsAct = terminalMenu->addAction(QObject::trUtf8("Сверка итогов"));
    connect(verificationResultsAct, SIGNAL(triggered()), this, SLOT(terminalVerificationResults()));

    controlRibbonAct = terminalMenu->addAction(QObject::trUtf8("Контрольная лента"));
    connect(controlRibbonAct, SIGNAL(triggered()), this, SLOT(terminalControlRibbon()));

    showMessageWindow = serviceMenu->addAction(QObject::trUtf8("Показать окно сообщений"));
    connect(showMessageWindow, SIGNAL(triggered()), this, SLOT(showMessagesWindow()));

    if (app->isSA())
    {
//        saveCustomAct = serviceMenu->addAction(QObject::trUtf8("Сохранить кастомизацию"));
//        connect(saveCustomAct, SIGNAL(triggered()), this, SLOT(saveCustomization()));

        loadFileMenu = serviceMenu->addMenu(QObject::trUtf8("Загрузить файл на сервер"));

        loadScriptFileAct = loadFileMenu->addAction(QObject::trUtf8("Загрузить файл со скриптами"));
        connect(loadScriptFileAct, SIGNAL(triggered()), app, SLOT(loadScriptFile()));

        loadReportFileAct = loadFileMenu->addAction(QObject::trUtf8("Загрузить файл с шаблоном отчета"));
        connect(loadReportFileAct, SIGNAL(triggered()), app, SLOT(loadReportFile()));

        loadFormFileAct = loadFileMenu->addAction(QObject::trUtf8("Загрузить файл с пользовательской формой"));
        connect(loadFormFileAct, SIGNAL(triggered()), app, SLOT(loadFormFile()));

        saveFileAct = serviceMenu->addAction(QObject::trUtf8("Выгрузить файл с сервера"));
        connect(saveFileAct, SIGNAL(triggered()), this, SLOT(saveFile()));
    }

    configAct = menuBar()->addAction(QObject::trUtf8("&Настройки"));
    connect(configAct, SIGNAL(triggered()), this, SLOT(showConfigs()));

    infoMenu = menuBar()->addMenu(QObject::trUtf8("&Помощь"));

//    aboutAct = infoMenu->addAction(QObject::trUtf8("О &программе..."));
//    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    wikiQtAct = infoMenu->addAction(QObject::trUtf8("Wiki проекта"));
    connect(wikiQtAct, SIGNAL(triggered()), this, SLOT(wikiQt()));

    vkQtAct = infoMenu->addAction(QObject::trUtf8("Группа ВКонтакте"));
    connect(vkQtAct, SIGNAL(triggered()), this, SLOT(vkQt()));

    aboutQtAct = infoMenu->addAction(QObject::trUtf8("О &библиотеке Qt..."));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    exitAct = menuBar()->addAction(QObject::trUtf8("&Выход"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(closeApp()));
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

void MainWindow::setPeriod()
{
    app->setPeriod();
    showPeriod();
}


void MainWindow::showPeriod()
{
    QString period;
    period = app->getBeginDate().toString(app->dateFormat()) + " - " + app->getEndDate().toString(app->dateFormat());
    periodAct->setIconText(period);
}


void MainWindow::showMessagesWindow()
{
    app->getMessageWindow()->show();
}


void MainWindow::saveCustomization()
{
     app->saveCustomization();
}


void MainWindow::saveFile()
{
    Dictionary* dict = app->getDictionary("файлы");
//    dict->query("ТИП = 0");
    dict->exec();
    if (dict->isFormSelected())
    {
        QString fileName = dict->getName();
//        QByteArray templateFile = app->getDBFactory()->getFile(fileName, ScriptFileType);
        QByteArray templateFile = app->getDBFactory()->getFile(fileName, dict->getValue("ТИП").toInt());
        app->saveFile(app->getPath(fileName, dict->getValue("ТИП").toInt()), &templateFile);
    }
}

void MainWindow::beep()
{
    app->runScript("beep.js");
}


void MainWindow::printReportWithoutCleaning()
{
    app->runScript("printReportWithoutCleaning.js");
}


void MainWindow::printReportWithCleaning()
{
    app->runScript("printReportWithCleaning.js");
}


void MainWindow::continuePrint()
{
    app->runScript("continuePrint.js");
}


void MainWindow::cancelCheck()
{
    app->runScript("cancelCheck.js");
}


void MainWindow::printEKLZReport()
{
    app->runScript("printEKLZReport.js");
}


void MainWindow::printProcessedEKLZReport()
{
    app->runScript("printEKLZReportProcessed.js");
}


void MainWindow::EKLZinterrupt()
{
    app->runScript("EKLZinterrupt.js");
}


void MainWindow::printReturnSaleCheck()
{
    app->runScript("printReturnSaleCheck.js");
}


void MainWindow::terminalVerificationResults()
{
    app->runScript("verificateResults.js");
}


void MainWindow::terminalControlRibbon()
{
    app->runScript("controlRibbon.js");
}


void MainWindow::readSettings()
{
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    if (settings.status() == QSettings::NoError)
    {
        settings.beginGroup("mainwindow");
        int x = settings.value("x", pos().x()).toInt();
        int y = settings.value("y", pos().y()).toInt();
        int w = settings.value("width", size().width()).toInt();
        int h = settings.value("height", size().height()).toInt();
        move(x, y);
        resize(w, h);
        settings.endGroup();
    }
}


void MainWindow::writeSettings()
{
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    settings.beginGroup("mainwindow");
    settings.setValue("x", pos().x());
    settings.setValue("y", pos().y());
    settings.setValue("width", size().width());
    settings.setValue("height", size().height());
    settings.endGroup();
}


QMdiSubWindow* MainWindow::appendMdiWindow(QWidget* dialogWidget)
{
    if (dialogWidget != nullptr)
    {
        // Сначала попытаемся найти окно QMdiSubWindow, в котором виджет dialogWidget отображался ранее
        foreach (QMdiSubWindow *subWindow, workSpace->subWindowList()) {
            Dialog* widget = qobject_cast<Dialog*>(subWindow->widget());
            if (widget == dialogWidget)
                return subWindow;
        }

        // Такой виджет видимо ранее не отображался, поэтому создадим новое окно
        QMdiSubWindow* subWindow = new QMdiSubWindow(this);         // POSSIBLY MEMORY LEAK
        subWindow->hide();
        subWindow->setWidget(dialogWidget);
        return workSpace->addSubWindow(subWindow, Qt::Window);
    }
    return nullptr;
}


QMdiSubWindow* MainWindow::findMdiWindow(QWidget* dialogWidget)
{
    if (dialogWidget != nullptr)
    {
        foreach (QMdiSubWindow *subWindow, workSpace->subWindowList()) {
            Dialog* widget = qobject_cast<Dialog*>(subWindow->widget());
            if (widget == dialogWidget)
                return subWindow;
        }
    }
    return nullptr;
}


void MainWindow::removeMdiWindow(QMdiSubWindow* subWindow)
{
    if (subWindow != nullptr)
    {
        workSpace->setActiveSubWindow(subWindow);
        subWindow->setWidget(nullptr);    // Обнулим указатель на виджет, чтобы при удалении подокна оно одновременно не удалило и виджет
        workSpace->removeSubWindow(subWindow);
        delete subWindow;
    }

}


void MainWindow::wikiQt()
{
    QDesktopServices::openUrl(QUrl("https://github.com/morozovvl/qbalance/wiki"));
}


void MainWindow::vkQt()
{
    QDesktopServices::openUrl(QUrl("https://vk.com/qbalance"));
}
