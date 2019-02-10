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

//#include <QtWidgets/QPrinter>
#include <QtWidgets/QTextEdit>
#include <QtSql/QSqlQuery>
#include <QSettings>
#include "messagewindow.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../storage/dbfactory.h"


MessageWindow::MessageWindow() : QObject()
{
    subWindow = 0;
    app = TApplication::exemplar();
    configName = "messagesWindow";
    textEditor = new QTextEdit();
    textEditor->setParent(subWindow);
    textEditor->setWindowTitle(QObject::trUtf8("Сообщения"));

    if (app->getMainWindow()->isVisible() && !app->isScriptMode())
    {
        if (subWindow == 0)
            subWindow = app->getMainWindow()->appendMdiWindow(textEditor);
    }

    readSettings();
    needShow = false;
}


MessageWindow::~MessageWindow()
{
    writeSettings();
    if (subWindow != 0)
    {
        app->getMainWindow()->removeMdiWindow(subWindow);
        subWindow = 0;
    }
    delete textEditor;
}


QTextEdit* MessageWindow::getTextEditor()
{
    return textEditor;
}


void MessageWindow::print(QString str)
{
    if (!app->isScriptMode())
    {
        textEditor->append(str);
        if (str.size() > 0)
            show();
    }
}


void MessageWindow::show()
{
    if (app->getMainWindow()->isVisible() && !app->isScriptMode())
    {
        if (subWindow != 0)
        {
            textEditor->show();
            subWindow->show();
            subWindow->raise();
        }
    }
    else
    {
        textEditor->show();
        subWindow->raise();
    }
    needShow = true;
}


void MessageWindow::hide()
{
    if (subWindow != 0)
    {
        subWindow->hide();
    }
    textEditor->hide();
}


void MessageWindow::readSettings()
{
    QHash<QString, int> settingValues;

    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    if (settings.status() == QSettings::NoError)
    {
        settings.beginGroup(configName);
        if (settings.contains("x") &&
            settings.contains("y") &&
            settings.contains("width") &&
            settings.contains("height") &&
            settings.value("width", 0).toInt() > 0 &&
            settings.value("height", 0).toInt() > 0)
        {
            settingValues.insert("x", settings.value("x").toInt());
            settingValues.insert("y", settings.value("y").toInt());
            settingValues.insert("width", settings.value("width").toInt());
            settingValues.insert("height", settings.value("height").toInt());
        }
        settings.endGroup();
    }
    if (settingValues.count() == 0)
        app->getDBFactory()->getConfig(configName, &settingValues);
    if (settingValues.count() == 0)
    {
        // Загрузим значения по умолчанию
        int defY = app->getMainWindow()->centralWidget()->height() * 0.6;
        int defHeight = app->getMainWindow()->centralWidget()->height() - defY;

        settingValues.insert("x", 0);
        settingValues.insert("y", defY);
        settingValues.insert("width", app->getMainWindow()->centralWidget()->width());
        settingValues.insert("height", defHeight);
    }

    int x = settingValues.value("x");
    int y = settingValues.value("y");
    int w = settingValues.value("width");
    int h = settingValues.value("height");

    if (subWindow != 0)
        subWindow->setGeometry(x, y, w, h);
    else
        textEditor->setGeometry(x, y, w, h);
}


void MessageWindow::writeSettings()
{
    // Сохраним данные локально, на компьютере пользователя
    int x, y, w, h;
    if (subWindow != 0)
    {
        x = subWindow->geometry().x();
        y = subWindow->geometry().y();
        w = subWindow->geometry().width();
        h = subWindow->geometry().height();
    }
    else
    {
        x = textEditor->geometry().x();
        y = textEditor->geometry().y();
        w = textEditor->geometry().width();
        h = textEditor->geometry().height();
    }

    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    settings.beginGroup(configName);
    settings.setValue("x", x);
    settings.setValue("y", y);
    settings.setValue("width", w);
    settings.setValue("height", h);
    settings.endGroup();

    // И если работает пользователь SA, то сохраним конфигурацию окна на сервере
    if (app->isSA() && app->getConfigValue("SAVE_FORM_CONFIG_TO_DB").toBool())
    {
        app->getDBFactory()->setConfig(configName, "x", QString("%1").arg(x));
        app->getDBFactory()->setConfig(configName, "y", QString("%1").arg(y));
        app->getDBFactory()->setConfig(configName, "width", QString("%1").arg(w));
        app->getDBFactory()->setConfig(configName, "height", QString("%1").arg(h));
    }
}


bool MessageWindow::isNeedShow()
{
    return needShow;
}


void MessageWindow::setNeedShow(bool need)
{
    needShow = need;
}
