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

#include <QtGui/QApplication>
#include <QtSql/QSqlTableModel>
#include <QtCore/QStringList>
#include <QtGui/QAbstractItemView>
#include <QtCore/QModelIndex>
#include <QtCore/QRect>
#include <QtGui/QPalette>
#include <QtGui/QPixmap>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPainter>
#include <QtCore/QUrl>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtCore/QDebug>
#include <QtGui/QInputDialog>
#include "formgrid.h"
#include "picture.h"
#include "tableview.h"
#include "myitemdelegate.h"
#include "dialog.h"
#include "../kernel/dictionary.h"
#include "../kernel/app.h"
#include "../kernel/table.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../engine/scriptengine.h"


FormGrid::FormGrid(QObject* parent/* = 0*/)
: Form(parent)
{
    grdTable = 0;
    grdTables.clear();
    tableLayout = 0;
    imageLayout = 0;
    picture = 0;
    buttonAdd = 0;
    buttonDelete = 0;
    buttonView = 0;
    buttonRequery = 0;
    buttonQuery = 0;
    buttonPrint = 0;
    buttonLoad = 0;
    buttonSave = 0;
    leftPercent = true;
    rightPercent = true;
}


FormGrid::~FormGrid()
{
    if (defaultForm)
        delete grdTable;
}


void FormGrid::setLeftPercent(bool percent)
{
    leftPercent = percent;
}


bool FormGrid::isLeftPercent()
{
    return leftPercent;
}


void FormGrid::setRightPercent(bool percent)
{
    rightPercent = percent;
}


bool FormGrid::isRightPercent()
{
    return rightPercent;
}

QPushButton* FormGrid::getButtonAdd()
{
    return buttonAdd;
}


QPushButton* FormGrid::getButtonDelete()
{
    return buttonDelete;
}


QPushButton* FormGrid::getButtonView()
{
    return buttonView;
}


QPushButton* FormGrid::getButtonRequery()
{
    return buttonRequery;
}


QPushButton* FormGrid::getButtonQuery()
{
    return buttonQuery;
}


QPushButton* FormGrid::getButtonPrint()
{
    return buttonPrint;
}


QPushButton* FormGrid::getButtonLoad()
{
    return buttonLoad;
}


QPushButton* FormGrid::getButtonSave()
{
    return buttonSave;
}

Picture* FormGrid::getPicture()
{
    return picture;
}


QString FormGrid::getFilter()
{
    return "";
}    // Возвращает фильтр для поиска в справочнике


void FormGrid::close()
{
    if (grdTable != 0)
    {
        grdTable->close();
        delete grdTable;
        grdTable = 0;
    }
    Form::close();
}


void FormGrid::createForm(QString fileName, QWidget* pwgt/* = 0*/)
{
    Form::createForm(fileName, pwgt);
    if (defaultForm)
    {   // Если форма создана автоматически
        grdTable = new TableView();
        tableLayout = new QVBoxLayout();
        tableLayout->setObjectName("tableLayout");
        tableLayout->addWidget(grdTable);
        if (vbxLayout != 0)
        {
            vbxLayout->insertLayout(0, tableLayout);
        }
        imageLayout = new QHBoxLayout();
        imageLayout->setObjectName("imageLayout");
        picture = new Picture(formWidget);
        picture->setObjectName("picture");
        picture->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        imageLayout->addWidget(picture);
        imageLayout->addStretch(1);
        if (vbxLayout != 0)
        {
            vbxLayout->insertLayout(1, imageLayout);
        }
    }
    else
    {   // Была загружена пользовательская форма
        tableLayout = (QVBoxLayout*)formWidget->findChild("tableLayout");
        grdTable = (TableView *)formWidget->findChild("tableView");
        picture = (Picture*)formWidget->findChild("picture");

        // Для всех картинок установим указатель на приложение
        foreach(QWidget* wid, formWidget->findChildren<QWidget*>())
        {
            if (QString(wid->metaObject()->className()).compare("Picture", Qt::CaseInsensitive) == 0)
                ((Picture*)wid)->setApp(app);
        }
    }

    if (picture != 0)
    {
        picture->setForm(this);
        picture->setApp(app);
        picture->hide();
    }

    // Подключим кнопку "Загрузить"
    if (parent != 0)
    {
        if (defaultForm)
        {
            buttonLoad = new QPushButton();
            buttonLoad->setObjectName("buttonLoad");
            cmdButtonLayout->insertWidget(0, buttonLoad);
        }
        else
        {
            if (formWidget != 0)
            {
                buttonLoad = (QPushButton*)formWidget->findChild("buttonLoad");
            }
        }
        if (buttonLoad != 0)
        {
            connect(buttonLoad, SIGNAL(clicked()), this, SLOT(cmdLoad()));
            buttonLoad->hide();
        }
    }

    // Подключим кнопку "Выгрузить"
    if (parent != 0)
    {
        if (defaultForm)
        {
            buttonSave = new QPushButton();
            buttonSave->setObjectName("buttonSave");
            cmdButtonLayout->insertWidget(0, buttonSave);
        }
        else
        {
            if (formWidget != 0)
            {
                buttonSave = (QPushButton*)formWidget->findChild("buttonSave");
            }
        }
        if (buttonSave != 0)
        {
            connect(buttonSave, SIGNAL(clicked()), this, SLOT(cmdSave()));
            buttonSave->hide();
        }
    }

    // Подключим кнопку "Печать"
    if (parent != 0 && parent->isPrintable())
    {
        if (defaultForm)
        {
            buttonPrint = new QPushButton();
            buttonPrint->setObjectName("buttonPrint");
            cmdButtonLayout->insertWidget(0, buttonPrint);
        }
        else
        {
            if (formWidget != 0)
            {
                buttonPrint = (QPushButton*)formWidget->findChild("buttonPrint");
            }
        }
        if (buttonPrint != 0)
        {
            connect(buttonPrint, SIGNAL(clicked()), this, SLOT(cmdPrint()));
        }
        else
        {
            parent->setPrintable(false);
        }
    }
    // Подключим кнопку "Обновить"
    if (defaultForm)
    {
        buttonRequery = new QPushButton();
        buttonRequery->setObjectName("buttonRequery");
        cmdButtonLayout->insertWidget(0, buttonRequery);
    }
    else
    {
        buttonRequery = (QPushButton*)formWidget->findChild("buttonRequery");
    }
    if (buttonRequery != 0)
    {
        connect(buttonRequery, SIGNAL(clicked()), this, SLOT(cmdRequery()));
    }
    // Подключим кнопку "Запрос"
    if (defaultForm)
    {
        buttonQuery = new QPushButton();
        buttonQuery->setObjectName("buttonQuery");
        cmdButtonLayout->insertWidget(0, buttonQuery);
    }
    else
    {
        buttonQuery = (QPushButton*)formWidget->findChild("buttonQuery");
    }
    if (buttonQuery != 0)
    {
        connect(buttonQuery, SIGNAL(clicked()), this, SLOT(cmdQuery()));
    }
    // Подключим кнопку "Просмотреть"
    if (parent != 0 && parent->isViewable())
    {
        if (defaultForm)
        {
            buttonView = new QPushButton();
            buttonView->setObjectName("buttonView");
            cmdButtonLayout->insertWidget(0, buttonView);
        }
        else
        {
            buttonView = (QPushButton*)formWidget->findChild("buttonView");
        }
        if (buttonView != 0)
        {
            connect(buttonView, SIGNAL(clicked()), this, SLOT(cmdView()));
        }
        else
        {
            parent->setViewable(false);
        }
    }
    // Подключим кнопку "Удалить"
    parent->setDeleteable(true);
    // Подключим кнопку "Добавить"
    parent->setInsertable(true);

    grdTables.append(grdTable);
}


void FormGrid::setButtonAdd(bool set)
{
    if (set)
    {
        if (parent != 0 && parent->isInsertable() && buttonAdd == 0)
        {
            if (defaultForm)
            {
                buttonAdd = new QPushButton();
                buttonAdd->setObjectName("buttonAdd");
                cmdButtonLayout->insertWidget(0, buttonAdd);
            }
            else
            {
                buttonAdd = (QPushButton*)formWidget->findChild("buttonAdd");
            }
            if (buttonAdd != 0)
            {
                connect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
                app->setIcons(formWidget);
            }
        }
    }
    else
    {
        if (!defaultForm)
            buttonAdd = (QPushButton*)formWidget->findChild("buttonAdd");
        if (parent != 0 && buttonAdd != 0)
        {
            buttonAdd->hide();
            cmdButtonLayout->removeWidget(buttonAdd);
            disconnect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
            if (defaultForm)
            {
                delete buttonAdd;
                buttonAdd = 0;
            }
        }
    }
}


void FormGrid::setButtonDelete(bool set)
{
    if (set)
    {
        if (parent != 0 && parent->isDeleteable() && buttonDelete == 0)
        {
            if (defaultForm)
            {
                buttonDelete = new QPushButton();
                buttonDelete->setObjectName("buttonDelete");
                cmdButtonLayout->insertWidget(0, buttonDelete);
            }
            else
            {
                buttonDelete = (QPushButton*)formWidget->findChild("buttonDelete");
            }
            if (buttonDelete != 0)
            {
                connect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
                app->setIcons(formWidget);
            }
        }
    }
    else
    {
        if (!defaultForm)
            buttonDelete = (QPushButton*)formWidget->findChild("buttonDelete");
        if (parent != 0 && buttonDelete != 0)
        {
            buttonDelete->hide();
            cmdButtonLayout->removeWidget(buttonDelete);
            disconnect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
            if (defaultForm)
            {
                delete buttonDelete;
                buttonDelete = 0;
            }
        }
    }
}


int FormGrid::exec()
{
    if (grdTable != 0)
    {
        grdTable->setColumnsHeaders();
        grdTable->setCurrentFocus();
    }
    setButtons();
    showPhoto();
    return Form::exec();
}


void FormGrid::show()
{
    if (grdTable != 0)
    {
        grdTable->setColumnsHeaders();
        grdTable->setCurrentFocus();
    }
    setButtons();
    showPhoto();
    Form::show();
}


void FormGrid::activateWidget()
{
    if (grdTable != 0)
    {
        grdTable->setFocus();
    }
}


void FormGrid::cmdAdd()
{
    if (buttonAdd != 0 && buttonAdd->isVisible() && buttonAdd->isEnabled())
    {
        grdTable->cmdAdd();
        showPhoto();
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdDelete()
{
    if (buttonDelete != 0 && buttonDelete->isVisible() && buttonDelete->isEnabled())
    {
        grdTable->cmdDelete();
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdView()
{
    if (buttonView != 0 && buttonView->isVisible() && buttonView->isEnabled())
    {
        grdTable->cmdView();
    }
}


void FormGrid::cmdRequery()
{
    grdTable->cmdRequery();
    if (parent->getTableModel()->rowCount() == 0)
    {
        showPhoto();
        app->showMessageOnStatusBar(trUtf8("Ничего не найдено."));
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdQuery()
{
    if (buttonQuery != 0 && buttonQuery->isVisible() && buttonQuery->isEnabled())
    {
        parent->getScriptEngine()->eventQuery();
    }
    grdTable->setFocus();
}


void FormGrid::cmdPrint(bool autoPrint)
{
    if (buttonPrint != 0 && buttonPrint->isVisible() && buttonPrint->isEnabled())
    {
        QHBoxLayout* cmdButtonLayout = (QHBoxLayout*)formWidget->findChild("cmdButtonLayout");
        QString fileName = app->getReportFile(getParent()->getTagName(), autoPrint, formWidget, cmdButtonLayout->contentsRect());
        if (fileName.size() > 0)
            parent->print(fileName);
    }
    grdTable->setFocus();
}


void FormGrid::cmdLoad()
{
    if (buttonLoad != 0 && buttonLoad->isVisible() && buttonLoad->isEnabled())
    {
        parent->load();
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdSave()
{
    if (buttonSave != 0 && buttonSave->isVisible() && buttonSave->isEnabled())
    {
        parent->getScriptEngine()->eventExport(this);
    }
    grdTable->setFocus();
}


void FormGrid::showPhoto()
{
    grdTable->showPhoto();
}


void FormGrid::setButtons()
{
    if (parent != 0)
    {
        if (parent->getTableModel()->rowCount() > 0)
        {
            if (buttonAdd != 0)
                buttonAdd->setEnabled(parent->isInsertable());
            if (buttonDelete != 0)
                buttonDelete->setEnabled(parent->isDeleteable());
            if (buttonView != 0)
                buttonView->setEnabled(parent->isViewable());
            if (buttonPrint != 0)
                buttonPrint->setEnabled(true);
            if (buttonSave != 0)
                buttonSave->setEnabled(true);
        }
        else
        {
            if (buttonDelete != 0)
                buttonDelete->setEnabled(false);
            if (buttonView != 0)
                buttonView->setEnabled(false);
            if (buttonPrint != 0)
                buttonPrint->setEnabled(false);
            if (buttonSave != 0)
                buttonSave->setEnabled(false);
        }
    }
}


void FormGrid::setEnabled(bool enabled)
{
    buttonAdd->setEnabled(enabled);
    buttonDelete->setEnabled(enabled);
    if (grdTable != 0)
        grdTable->setReadOnly(!enabled);
}


void FormGrid::keyPressEvent(QKeyEvent *event)
{
    event->setAccepted(false);
    if (event->modifiers() == Qt::ControlModifier)
    {
        switch (event->key())
        {
            case Qt::Key_Insert:
                {
                    cmdAdd();
                    event->setAccepted(true);
                }
                break;
            case Qt::Key_Delete:
                {
                    cmdDelete();
                    event->setAccepted(true);
                }
                break;
        }
    }
    else
    {
        switch (event->key())
        {
            case Qt::Key_F2:
                {
                    cmdView();
                    event->setAccepted(true);
                }
                break;
            case Qt::Key_F3:
                {
                    cmdRequery();
                    event->setAccepted(true);
                }
                break;
            case Qt::Key_F4:
                {
                    cmdPrint(true);
                    event->setAccepted(true);
                }
                break;
        }
    }
    if (!event->isAccepted())
    {
        Form::keyPressEvent(event);
    }
}


TableView* FormGrid::getGrdTable()
{
    return grdTable;
}


void FormGrid::setGrdTable(TableView* gt)
{
    if (gt != 0)
    {
        if (defaultForm)
            delete grdTable;
        grdTable = gt;
    }
}

