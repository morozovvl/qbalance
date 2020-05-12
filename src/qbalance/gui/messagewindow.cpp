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

#if QT_VERSION < 0x050000
    #include <QtGui/QTextEdit>
#else
    #include <QtWidgets/QTextEdit>
#endif

#include <QtSql/QSqlQuery>
#include <QSettings>
#include "messagewindow.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../storage/dbfactory.h"


MessageWindow::MessageWindow() : QObject()
{
    subWindow = 0 /*nullptr*/;
    app = TApplication::exemplar();
    configName = "messagesWindow";
    textEditor = new QTextEdit();
    textEditor->setParent(subWindow);
    textEditor->setWindowTitle(QObject::trUtf8("Сообщения"));

    if (app->getMainWindow()->isVisible() && !app->isScriptMode())
    {
        if (subWindow == 0 /*nullptr*/)
            subWindow = app->getMainWindow()->appendMdiWindow(textEditor);
    }

    readSettings();
    needShow = false;
}


MessageWindow::~MessageWindow()
{
    writeSettings();
    if (subWindow != 0 /*nullptr*/)
    {
        app->getMainWindow()->removeMdiWindow(subWindow);
        subWindow = 0 /*nullptr*/;
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
        if (subWindow != 0 /*nullptr*/)
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
    if (subWindow != 0 /*nullptr*/)
    {
        subWindow->hide();
    }
    textEditor->hide();
}


void MessageWindow::readSettings()
{
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    settings.beginGroup(configName);
    int defY = qRound(app->getMainWindow()->centralWidget()->height() * 0.6);
    int defHeight = app->getMainWindow()->centralWidget()->height() - defY;

    int x = settings.value("x", 0).toInt();
    int y = settings.value("y", defY).toInt();
    int w = settings.value("width", app->getMainWindow()->centralWidget()->width()).toInt();
    int h = settings.value("height", defHeight).toInt();

    settings.endGroup();

    if (subWindow != 0 /*nullptr*/)
        subWindow->setGeometry(x, y, w, h);
    else
        textEditor->setGeometry(x, y, w, h);
}


void MessageWindow::writeSettings()
{
    // Сохраним данные локально, на компьютере пользователя
    int x, y, w, h;

    if (subWindow != 0 /*nullptr*/)
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
}


bool MessageWindow::isNeedShow()
{
    return needShow;
}


void MessageWindow::setNeedShow(bool need)
{
    needShow = need;
}
