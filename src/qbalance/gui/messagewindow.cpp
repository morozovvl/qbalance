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

#include <QtGui/QTextEdit>
#include <QtSql/QSqlQuery>
#include "messagewindow.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../storage/dbfactory.h"


MessageWindow::MessageWindow() :
    QObject()
{
    subWindow = 0;
    app = TApplication::exemplar();
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
    QString configName = "messagesWindow";
    QHash<QString, int> settingValues;

    // Загрузим значения по умолчанию
    int defY = app->getMainWindow()->centralWidget()->height() * 0.6;
    int defHeight = app->getMainWindow()->centralWidget()->height() - defY;

    settingValues.insert("x", 0);
    settingValues.insert("y", defY);
    settingValues.insert("width", app->getMainWindow()->centralWidget()->width());
    settingValues.insert("height", defHeight);


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
            settingValues.remove("x");
            settingValues.insert("x", settings.value("x").toInt());
            settingValues.remove("y");
            settingValues.insert("y", settings.value("y").toInt());
            settingValues.remove("width");
            settingValues.insert("width", settings.value("width").toInt());
            settingValues.remove("height");
            settingValues.insert("height", settings.value("height").toInt());

        }
        else
        {
            // Если локальные значения координат и размеров окна прочитать не удалось, попытаемся загрузить их с сервера
//            app->showMessageOnStatusBar(tr("Загрузка с сервера геометрии окна справочника ") + configName + "...");
            QSqlQuery config = app->getDBFactory()->getConfig();
            config.first();
            while (config.isValid())
            {
                if (config.record().value("group").toString() == configName)
                {
                    settingValues.remove(config.record().value("name").toString());
                    settingValues.insert(config.record().value("name").toString(), config.record().value("value").toInt());
                }
                config.next();
            }
//            app->showMessageOnStatusBar("");
        }
        settings.endGroup();

        int x = settingValues.value("x");
        int y = settingValues.value("y");
        int w = settingValues.value("width");
        int h = settingValues.value("height");

        if (subWindow != 0)
            subWindow->setGeometry(x, y, w, h);
        else
            textEditor->setGeometry(x, y, w, h);
    }
}


void MessageWindow::writeSettings()
{
    QString configName = "messagesWindow";
    // Сохраним данные локально, на компьютере пользователя
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    settings.beginGroup(configName);
    if (subWindow != 0)
    {
        settings.setValue("x", subWindow->x());
        settings.setValue("y", subWindow->y());
        settings.setValue("width", subWindow->frameGeometry().width());
        settings.setValue("height", subWindow->frameGeometry().height());
    }
    else
    {
        settings.setValue("x", textEditor->x());
        settings.setValue("y", textEditor->y());
        settings.setValue("width", textEditor->frameGeometry().width());
        settings.setValue("height", textEditor->frameGeometry().height());
    }
    settings.endGroup();

    // И если работает пользователь SA, то сохраним конфигурацию окна на сервере
    if (app->isSA() && app->getConfigValue("SAVE_FORM_CONFIG_TO_DB").toBool())
    {
//        app->showMessageOnStatusBar(tr("Сохранение на сервере геометрии окна справочника ") + configName + "...");
        if (subWindow != 0)
        {
            app->getDBFactory()->setConfig(configName, "x", QString("%1").arg(subWindow->geometry().x()));
            app->getDBFactory()->setConfig(configName, "y", QString("%1").arg(subWindow->geometry().y()));
            app->getDBFactory()->setConfig(configName, "width", QString("%1").arg(subWindow->geometry().width()));
            app->getDBFactory()->setConfig(configName, "height", QString("%1").arg(subWindow->geometry().height()));
        }
        else
        {
            app->getDBFactory()->setConfig(configName, "x", QString("%1").arg(textEditor->geometry().x()));
            app->getDBFactory()->setConfig(configName, "y", QString("%1").arg(textEditor->geometry().y()));
            app->getDBFactory()->setConfig(configName, "width", QString("%1").arg(textEditor->geometry().width()));
            app->getDBFactory()->setConfig(configName, "height", QString("%1").arg(textEditor->geometry().height()));
        }
//        app->showMessageOnStatusBar("");
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
