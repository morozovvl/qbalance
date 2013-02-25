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

#include <QtCore/QDate>
#include <QtGui/QMessageBox>
#include <QtCore/QObject>
#include <QtUiTools/QUiLoader>
#include <QtCore/QTextCodec>
#include <QtGui/QPushButton>
#include <QDebug>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "../gui/guifactory.h"
#include "../gui/passwordform.h"
#include "../gui/formgrid.h"
#include "../gui/mainwindow.h"
#include "../gui/configform.h"

QString TApplication::MaxSumMask       = "9999999999.99";
QFile*  TApplication::DebugFile        = new QFile(QDir::currentPath() + "/" + TApplication::debugFileName());
QTextStream* TApplication::DebugStream = new QTextStream(TApplication::DebugFile);
bool    TApplication::DebugMode        = false;
TApplication* TApplication::Exemplar   = NULL;

TApplication::TApplication(int & argc, char** argv)
    : QApplication(argc, argv)
{
    setOrganizationName("Enterprise");
    setApplicationName("QBalance");
    setApplicationVersion("0.0.1");

    db  = new DBFactory();
    gui = new GUIFactory(db);
//    globalParameters = new GlobalParameters(this);
    dictionaryList = 0;
    topersList = 0;
    driverFR = new DriverFR(this);
    driverFRisValid = false;

//    reportTemplateType = OOreportTemplate;   // модуль печати по умолчанию пока будет OOReportEngine, пока нет других
//    reportTemplateType = OpenRPTreportTemplate;
        reportTemplateType = OOXMLreportTemplate;

    if (!Exemplar)
    {
        Exemplar = this;
        TApplication::MaxSumMask = TApplication::MaxSumMask.replace(".", QApplication::keyboardInputLocale().decimalPoint());
    }
}

/*
TApplication::~TApplication()
{
    delete driverFR;
    delete gui;
    delete db;
}
*/

Documents* TApplication::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {
        Documents* doc = new Documents(opNumber);
        if (!doc->open())
            return NULL;
        documents.insert(operName, doc);
    }
    return documents[operName];
}


void TApplication::removeDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (documents.contains(operName)) {
        Documents* doc = documents.value(operName);
        doc->close();
        documents.remove(operName);
    }
}


Dictionaries* TApplication::getDictionaries()
{
    return dictionaryList;
}


QString TApplication::getReportTemplateExt()
{
    switch (getReportTemplateType())
    {
        case OOreportTemplate:
            return "ods";
        case OOUNOreportTemplate:
            return "ods";
        case OOXMLreportTemplate:
            return "ods";
        case OpenRPTreportTemplate:
            return "xml";
    }
    return "";
}


bool TApplication::open() {
    bool lResult = false;   // По умолчанию будем считать, что приложение открыть не удалось
    if (debugMode())
    {
        TApplication::debug("Program startup.\n");
    }
    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);
    if (gui->open()) {  // Попытаемся открыть графический интерфейс
        forever         // Будем бесконечно пытаться открыть базу, пока пользователь не откажется
        {
            int result = gui->openDB(); // Попытаемся открыть базу данных
            if (result == 0)
            {   // БД открыть удалось
                dictionaryList = new Dictionaries();
                topersList = new Topers();
                if (dictionaryList->open() && topersList->open())
                {   // Удалось открыть спосок справочников и типовых операций
                    db->getPeriod(beginDate, endDate);
                    gui->getMainWindow()->showPeriod();
                    if (driverFR->open(applicationDirPath() + "/plugins/libdrvfr"))
                        driverFRisValid = true;
                    lResult = true;     // Приложение удалось открыть
                    break;  // Выйдем из бесконечного цикла открытия БД
                }
            }
            else if (result == -2)
                {   // Произошла ошибка соединения с сервером
                if (gui->showMessage(QObject::trUtf8("Не удалось соединиться с базой данных (БД). Возможно БД отсутствует."),
                                     QObject::trUtf8("Попытаться создать новую БД?")) == QMessageBox::Yes)
                    // Попытаемся создать новую БД
                    db->createNewDBs(gui->getLastHostName(), gui->getLastDbName(), gui->getLastPort());
            }
            else if (result == -1)      // Пользователь нажал кнопку Отмена
                break;  // Выйдем из бесконечного цикла открытия БД
        }
    }
    return lResult;
}


void TApplication::close() {
    if (documents.count() > 0)
    {
        foreach(Documents* doc, documents)
        {
             doc->close();
        }
    }
    if (dictionaryList != 0)
    {
        dictionaryList->close();
        delete dictionaryList;
    }
    if (topersList != 0)
    {
        topersList->close();
        delete topersList;
    }
    if (gui != 0)
        gui->close();
    if (db != 0)
        db->close();
    if (debugMode())
    {
        TApplication::debug("Program shutdown.\n\n");
        TApplication::DebugFile->close();
    }
}


void TApplication::showMessageOnStatusBar(const QString &message, int timeout)
{
    gui->getMainWindow()->getStatusBar()->showMessage(message, timeout);
}


void TApplication::showConfigs() {
    ConfigForm* form = new ConfigForm();
    if (form->open(getMainWindow())) {
        form->exec();
        form->close();
    }
    delete form;
}


QString TApplication::getFormsPath(QString formName) {
    QString dir = applicationDirPath() + "/forms/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    dir += getConfigPrefix() + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + formName;
    return fileName;
}


QString TApplication::getReportsPath(QString reportName) {
    QString dir = applicationDirPath() + "/reports/" + getConfigPrefix() + "/";
    if (!QDir().exists(dir))
        QDir().mkdir(dir);
    QString fileName = dir + reportName;
    return fileName;
}


Dialog* TApplication::createForm(QString fileName)
{
    Dialog* formWidget = 0;
    QString path = getFormsPath();
    QString fName = fileName + ".ui";
    if (Essence::getFile(path, fName, FormFileType))
    {
        QFile file(path + fName);
        if (file.open(QIODevice::ReadOnly))
        {
            QUiLoader loader;
            loader.addPluginPath("./plugins/");
            formWidget = (Dialog*)loader.load(&file);
            file.close();
            if (QString::compare(formWidget->metaObject()->className(), "Dialog",  Qt::CaseSensitive) != 0)
            {
                showError(QString(QObject::tr("Загружаемая форма %1 должна иметь тип Dialog.")).arg(fileName));
                return 0;
            }
        }
    }
    return formWidget;
}


QString TApplication::encoding()
{
    QString result("UTF-8");
//#ifdef Q_OS_WIN32
//    if (QSysInfo::windowsVersion() != QSysInfo::WV_WINDOWS7)
//        result = "Windows-1251";
//#endif
    return result;
}


QTextCodec* TApplication::codec()
{
    return QTextCodec::codecForName(encoding().toLatin1());
}


bool TApplication::setDebugMode(const bool& value)
{
    bool result = true;
    if (value && !debugMode())
    {
        result = debugFile().open(QFile::WriteOnly | QFile::Append);
    }
    else if (!value && debugMode())
    {
        debugFile().close();
    }

    DebugMode = value;

    return result;
}


void TApplication::debug(const QString& value)
{
    if (debugMode())
    {
        TApplication::debugStream() << QDateTime::currentDateTime().toString(logTimeFormat()) << " " << value;
    }
}


TApplication* TApplication::exemplar()
{
    return Exemplar;
}


void TApplication::setIcons(QWidget* formWidget)
{
    QList<QPushButton*> widgets = qFindChildren<QPushButton*>(formWidget);
    for (int i = 0; i < widgets.size(); i++)
        widgets.at(i)->setIcon(QIcon(":" + widgets.at(i)->objectName()));
}


void TApplication::showError(QString error)
{
    gui->showError(error);
    debug("Error: " + error + "\n");
}


void TApplication::showCriticalError(QString error)
{
    gui->showCriticalError(error);
    debug("Error: " + error + "\n");
}
