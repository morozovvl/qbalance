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

#include <QtCore/QObject>
#include <QtCore/QTextStream>
#include <QtCore/QResource>
#include <QtUiTools/QUiLoader>
#include <QtCore/QTextCodec>
#include <QtCore/QList>
#include <QPushButton>
#include <QDesktopWidget>
#include <QDebug>
#include "form.h"
#include "../kernel/app.h"
#include "mainwindow.h"
#include "dialog.h"

class TApplication;

Form::Form(QObject* par/* = 0*/): QObject(par)
{
    parent = 0;
    formWidget = 0;
    cmdButtonLayout = 0;
    vbxLayout = 0;
    buttonOk = 0;
    buttonCancel = 0;
    appendToMdi = true;
    app = TApplication::exemplar();
    db = app->getDBFactory();
    freeWindow = false;
    subWindow = 0;
    autoSelect = false;
}


Form::~Form()
{
        toolTips.clear();
}


bool Form::open(QWidget* pwgt, Essence* par, QString fName)
{
    parent = par;
    fileName = fName;
    if (fileName.size() == 0)
        createForm("mainform", pwgt);
    else
        createForm(fileName, pwgt);
    app->setIcons(formWidget);
    readSettings();

    //  Установим подписи ко всем кнопкам
    foreach (QString key, toolTips.keys())
    {
        QPushButton* button = (QPushButton*)formWidget->findChild(key);
        if (button != 0 && button->toolTip().isEmpty())
            button->setToolTip(toolTips.value(key, ""));
    }
    return true;
}


void Form::close()
{
    writeSettings();
    if (subWindow != 0)
    {
        subWindow->setWidget(0);
        app->getMainWindow()->removeMdiWindow(subWindow);
    }
}


void Form::createForm(QString fileName, QWidget* pwgt)
{
    if (parent != 0)
    {
        configName = getParent()->getTagName();
    }
    else
    {
        configName = "Form";
    }
    setObjectName(configName);
    uiCreated = false;
    formWidget = 0;
    defaultForm = true;
    script = "";
    if (fileName != "mainform")
    {
        formWidget = app->createForm(fileName);
    }
    if (formWidget != 0)
    {   // Если была найдена нестандартная пользовательская форма
        formWidget->setApp(app);
        formWidget->setParent(pwgt);
        formWidget->setVisible(false);
        formWidget->setWindowFlags(Qt::Window | Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowContextHelpButtonHint);
        buttonOk = (QPushButton*)formWidget->findChild("buttonOk");
        buttonCancel = (QPushButton*)formWidget->findChild("buttonCancel");
        cmdButtonLayout = (QHBoxLayout*)formWidget->findChild("cmdButtonLayout");
        vbxLayout = (QVBoxLayout*)formWidget->findChild("vbxLayout");
        defaultForm = false;
    }
    else
    {   // Нужно создать стандартную форму
        formWidget = new Dialog(pwgt);
        formWidget->setApp(app);
        formWidget->setVisible(false);
        formWidget->setWindowFlags(Qt::Window | Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowContextHelpButtonHint);
        buttonOk = new QPushButton();
        buttonOk->setObjectName("buttonOk");
        buttonCancel = new QPushButton();
        buttonCancel->setObjectName("buttonCancel");

        cmdButtonLayout = new QHBoxLayout();
        cmdButtonLayout->setObjectName("cmdButtonLayout");
        cmdButtonLayout->addStretch(1);
        cmdButtonLayout->addWidget(buttonOk);
        cmdButtonLayout->addWidget(buttonCancel);

        vbxLayout = new QVBoxLayout();
        vbxLayout->setObjectName("vbxLayout");

        vbxLayout->addLayout(cmdButtonLayout);
        formWidget->setLayout(vbxLayout);
        if (buttonOk != 0)                  // Для стандартной формы соединяем нажатие кнопки "Ok" с обработчиком
        {                                   // Для нестандартной формы обработчик подключается во время загрузки формы
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(cmdOk()));
        }
    }
    if (buttonCancel != 0)
    {
        connect(buttonCancel, SIGNAL(clicked()), SLOT(cmdCancel()));
    }
    formWidget->setFocusPolicy(Qt::StrongFocus);
    freeWindow = !appendToMdi;

    if (parent != 0)
        formWidget->setForm(this);
}


void Form::cmdOk()
{
    lSelected = true;
    if (parent != 0)
    {
        parent->cmdOk();
        parent->hide();
    }
    else
        hide();
}


void Form::cmdCancel()
{
    lSelected = false;
    if (parent != 0)
    {
        parent->cmdCancel();
        parent->hide();
    }
    else
        hide();
}


int Form::exec()
{
    if (formWidget != 0)
    {
        lSelected = false;

        checkVisibility();

        getSubWindow();

        if (subWindow != 0)
        {
            subWindow->setWidget(0);
            formWidget->setGeometry(subWindow->x(), subWindow->y(), subWindow->width(), subWindow->height());

            formWidget->setParent(app->getMainWindow(), Qt::Dialog);
            if (!autoSelect)
                formWidget->exec();
            else
                cmdOk();
            autoSelect = false;

            subWindow->setGeometry(formWidget->x(), formWidget->y(), formWidget->width(), formWidget->height());
            subWindow->setWidget(formWidget);
        }
        else
        {
            if (!autoSelect)
                formWidget->exec();
            else
                cmdOk();
            autoSelect = false;
        }

        return lSelected;
    }
    return 0;
}


void Form::show()
{
    if (formWidget != 0)
    {
        lSelected = false;

        checkVisibility();

        if (getSubWindow() != 0)
        {
            if (!autoSelect)
                subWindow->show();
            else
                cmdOk();
            autoSelect = false;
        }

        formWidget->show();
    }
}


MyMdiSubWindow* Form::getSubWindow()
{
    if (app != 0 && !freeWindow)
    {
        if (subWindow == 0)
            subWindow = app->getMainWindow()->appendMdiWindow(formWidget);
        return subWindow;
    }
    return 0;
}


void Form::activateSubWindow()
{
    app->getMainWindow()->getWorkSpace()->setActiveSubWindow(subWindow);
}


void Form::checkVisibility()
{
    // Проверим, не уползло ли окно за пределы видимости. Если оно за пределами видимости, то вернем его
    if (getSubWindow() != 0)
    {
        int x = getSubWindow()->x();
        int y = getSubWindow()->y();
        int w = getSubWindow()->width();
        int h = getSubWindow()->height();
        if (x >= app->getMainWindow()->centralWidget()->width())        // Если координата X уползла за пределы видимости
        {
            if (w > app->getMainWindow()->centralWidget()->width())     // Если ширина окна превышает ширину центрального виджета
                w = app->getMainWindow()->centralWidget()->width();
            x = (app->getMainWindow()->centralWidget()->width() - w) / 2;   // Разместим окно посередине
            if (x < 0)
                x = 0;
        }
        if (y >= app->getMainWindow()->centralWidget()->height())        // Если координата Y уползла за пределы видимости
        {
            if (h > app->getMainWindow()->centralWidget()->height())     // Если высота окна превышает высоту центрального виджета
                h = app->getMainWindow()->centralWidget()->height();
            y = (app->getMainWindow()->centralWidget()->height() - h) / 2;   // Разместим окно посередине
            if (y < 0)
                y = 0;
        }
        getSubWindow()->setGeometry(x, y, w, h);
    }
}


void Form::hide()
{
    if (formWidget != 0)
    {
        if (!freeWindow)
        {
            if (subWindow != 0)
            {
                subWindow->hide();
            }
        }
        formWidget->hide();
    }
}


void Form::gotoCenter()
{   // Переместить форму в центр родительского виджета
    if (formWidget != 0)
    {
        QRect rect;
        if (formWidget->parentWidget() != 0)
            rect = formWidget->parentWidget()->geometry();
        else
            rect = app->desktop()->screen()->geometry();

        int x = (rect.width() - formWidget->width()) / 2;
        int y = (rect.height() - formWidget->height()) / 2;

        formWidget->move(x, y);
    }
}


void Form::appendToolTip(QString name, QString value)
{
    if (toolTips.contains(name))
        toolTips.remove(name);
    toolTips.insert(name, value);
}


void Form::setButtonsSignals()
{
    QList<QPushButton*> allButtons = formWidget->findChildren<QPushButton*>();
    foreach (QPushButton* button, allButtons)
    {
        connect(button, SIGNAL(clicked()), SLOT(buttonPressedSignalSend()));
    }
}


void Form::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
                cmdOk();
                event->accept();
        }
    }
    else
    {
        if (event->key() == Qt::Key_Escape)
        {
            cmdCancel();
            event->accept();
        }
    }
}


void Form::readSettings()
{
    // Установим координаты и размеры окна
    QWidget* widget;
    widget = getSubWindow();
    if (widget == 0)
        widget = formWidget;

    QMap<QString, int> settingValues;
    // Попытаемся сначала прочитать локальные значения координат окна и размеров на компьютере пользователя
    QSettings settings;
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
        else
        {
            // Если локальные значения координат и размеров окна прочитать не удалось, попытаемся загрузить их с сервера
            app->showMessageOnStatusBar(tr("Загрузка с сервера геометрии окна справочника ") + configName + "...");
            QSqlQuery config = db->getConfig();
            config.first();
            while (config.isValid())
            {
                if (config.record().value("group").toString() == configName)
                {
                    settingValues.remove(config.value(0).toString());
                    settingValues.insert(config.value(0).toString(), config.value(1).toInt());
                }
                config.next();
            }
            app->showMessageOnStatusBar("");
        }
        settings.endGroup();

        int x = settingValues.value("x", 0);
        int y = settingValues.value("y", 0);
        int w = settingValues.value("width", 400);
        int h = settingValues.value("height", 200);

        widget->setGeometry(x, y, w, h);
    }
}


void Form::writeSettings()
{
    // Сохраним координаты и размеры окна
    QWidget* widget;
    widget = (QWidget*)getSubWindow();
    if (widget == 0)
        widget = (QWidget*)formWidget;

    // Сохраним данные локально, на компьютере пользователя
    QSettings settings;
    settings.beginGroup(configName);
    settings.setValue("x", widget->x());
    settings.setValue("y", widget->y());
    settings.setValue("width", widget->frameGeometry().width());
    settings.setValue("height", widget->frameGeometry().height());
    settings.endGroup();

    // И если работает пользователь SA, то сохраним конфигурацию окна на сервере
    if (app->getSaveFormConfigToDb())
    {
        app->showMessageOnStatusBar(tr("Сохранение на сервере геометрии окна справочника ") + configName + "...");
        db->setConfig(configName, "x", QString("%1").arg(formWidget->geometry().x()));
        db->setConfig(configName, "y", QString("%1").arg(formWidget->geometry().y()));
        db->setConfig(configName, "width", QString("%1").arg(formWidget->geometry().width()));
        db->setConfig(configName, "height", QString("%1").arg(formWidget->geometry().height()));
        app->showMessageOnStatusBar("");
    }
}

