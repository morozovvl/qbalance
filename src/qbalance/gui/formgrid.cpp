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
    #include <QtGui/QApplication>
    #include <QtGui/QAbstractItemView>
    #include <QtGui/QHBoxLayout>
    #include <QtGui/QHeaderView>
    #include <QtGui/QPushButton>
    #include <QtGui/QInputDialog>
#else
    #include <QtWidgets/QApplication>
    #include <QtWidgets/QAbstractItemView>
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QHeaderView>
    #include <QtWidgets/QPushButton>
    #include <QtWidgets/QInputDialog>
#endif

#include <QtSql/QSqlTableModel>
#include <QtCore/QStringList>
#include <QtCore/QModelIndex>
#include <QtCore/QRect>
#include <QtGui/QPalette>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtCore/QUrl>
#include <QtCore/QDebug>
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


FormGrid::FormGrid(QObject* parent)
: Form(parent)
{
    grdTable = 0 /*nullptr*/;
    tableLayout = 0 /*nullptr*/;
    imageLayout = 0 /*nullptr*/;
    picture = 0 /*nullptr*/;
    buttonAdd = 0 /*nullptr*/;
    buttonDelete = 0 /*nullptr*/;
    buttonView = 0 /*nullptr*/;
    buttonRequery = 0 /*nullptr*/;
    buttonQuery = 0 /*nullptr*/;
    buttonPrint = 0 /*nullptr*/;
    buttonLoad = 0 /*nullptr*/;
    buttonSave = 0 /*nullptr*/;
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
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->close();
        delete grdTable;
        grdTable = 0 /*nullptr*/;
    }
    Form::close();
}


void FormGrid::createForm(QString fileName, QWidget* pwgt)
{
    Form::createForm(fileName, pwgt);
    if (defaultForm)
    {   // Если форма создана автоматически
        grdTable = new TableView();
        grdTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tableLayout = new QVBoxLayout();
        tableLayout->setObjectName("tableLayout");
        tableLayout->addWidget(grdTable);
        if (vbxLayout != 0 /*nullptr*/)
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
        if (vbxLayout != 0 /*nullptr*/)
        {
            vbxLayout->insertLayout(1, imageLayout);
        }
    }
    else
    {   // Была загружена пользовательская форма
        tableLayout = static_cast<QVBoxLayout*>(formWidget->findChild("tableLayout"));
        grdTable    = static_cast<TableView*>(formWidget->findChild("tableView"));
        picture     = static_cast<Picture*>(formWidget->findChild("picture"));

        // Для всех картинок установим указатель на приложение
        foreach(QWidget* wid, formWidget->findChildren<QWidget*>())
        {
            if (QString(wid->metaObject()->className()).compare("Picture", Qt::CaseInsensitive) == 0)
                static_cast<Picture*>(wid)->setApp(app);
        }
    }

    if (picture != 0 /*nullptr*/)
    {
        picture->setForm(this);
        picture->setApp(app);
        picture->hide();
    }

    // Подключим кнопку "Загрузить"
    if (parent != 0 /*nullptr*/)
    {
        if (defaultForm)
            buttonLoad = insertButton("buttonLoad");
        else if (formWidget != 0 /*nullptr*/)
            buttonLoad = static_cast<QPushButton*>(formWidget->findChild("buttonLoad"));

        if (buttonLoad != 0 /*nullptr*/)
        {
            connect(buttonLoad, SIGNAL(clicked()), this, SLOT(cmdLoad()));
            buttonLoad->hide();
        }
    }

    // Подключим кнопку "Выгрузить"
    if (parent != 0 /*nullptr*/)
    {
        if (defaultForm)
            buttonSave = insertButton("buttonSave");
        else if (formWidget != 0 /*nullptr*/)
            buttonSave = static_cast<QPushButton*>(formWidget->findChild("buttonSave"));

        if (buttonSave != 0 /*nullptr*/)
        {
            connect(buttonSave, SIGNAL(clicked()), this, SLOT(cmdSave()));
            buttonSave->hide();
        }
    }

    // Подключим кнопку "Печать"
    if (parent != 0 /*nullptr*/ && parent->isPrintable())
    {
        if (defaultForm)
            buttonPrint = insertButton("buttonPrint");
        else if (formWidget != 0 /*nullptr*/)
            buttonPrint = static_cast<QPushButton*>(formWidget->findChild("buttonPrint"));

        if (buttonPrint != 0 /*nullptr*/)
            connect(buttonPrint, SIGNAL(clicked()), this, SLOT(cmdPrint()));
        else
            parent->setPrintable(false);
    }

    // Подключим кнопку "Обновить"
    if (defaultForm)
        buttonRequery = insertButton("buttonRequery");
    else if (formWidget != 0 /*nullptr*/)
        buttonRequery = static_cast<QPushButton*>(formWidget->findChild("buttonRequery"));

    if (buttonRequery != 0 /*nullptr*/)
    {
        connect(buttonRequery, SIGNAL(clicked()), this, SLOT(cmdRequery()));
    }


    // Подключим кнопку "Просмотреть"
    if (parent != 0 /*nullptr*/)
    {
        if (parent->isViewable())
        {
            if (defaultForm)
                buttonView = insertButton("buttonView");
            else if (formWidget != 0 /*nullptr*/)
                buttonView = static_cast<QPushButton*>(formWidget->findChild("buttonView"));

            if (buttonView != 0 /*nullptr*/)
                connect(buttonView, SIGNAL(clicked()), this, SLOT(cmdView()));
            else
                parent->setViewable(false);
        }

        // Подключим кнопку "Удалить"
        parent->setDeleteable(parent->isDeleteable());
        // Подключим кнопку "Добавить"
        parent->setInsertable(parent->isInsertable());

    }

    grdTables.append(grdTable);

    if (vbxLayout != 0 /*nullptr*/)
        vbxLayout->setSpacing(1);

}


void FormGrid::setButtonAdd(bool set)
{
    if (set)
    {
        if (parent != 0 /*nullptr*/ && parent->isInsertable() && buttonAdd == 0 /*nullptr*/)
        {
            if (defaultForm)
                buttonAdd = insertButton("buttonAdd");
            else
                buttonAdd = static_cast<QPushButton*>(formWidget->findChild("buttonAdd"));

            if (buttonAdd != 0 /*nullptr*/)
            {
                connect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
                app->setIcons(formWidget);
            }
        }
    }
    else
    {
        if (!defaultForm)
            buttonAdd = static_cast<QPushButton*>(formWidget->findChild("buttonAdd"));
        if (parent != 0 /*nullptr*/ && buttonAdd != 0 /*nullptr*/)
        {
            buttonAdd->hide();
            cmdButtonLayout->removeWidget(buttonAdd);
            disconnect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
            if (defaultForm)
            {
                delete buttonAdd;
                buttonAdd = 0 /*nullptr*/;
            }
        }
    }
}


void FormGrid::setButtonDelete(bool set)
{
    if (set)
    {
        if (parent != 0 /*nullptr*/ && parent->isDeleteable() && buttonDelete == 0 /*nullptr*/)
        {
            if (defaultForm)
                buttonDelete = insertButton("buttonDelete");
            else
                buttonDelete = static_cast<QPushButton*>(formWidget->findChild("buttonDelete"));

            if (buttonDelete != 0 /*nullptr*/)
            {
                connect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
                app->setIcons(formWidget);
            }
        }
    }
    else
    {
        if (!defaultForm)
            buttonDelete = static_cast<QPushButton*>(formWidget->findChild("buttonDelete"));
        if (parent != 0 /*nullptr*/ && buttonDelete != 0 /*nullptr*/)
        {
            buttonDelete->hide();
            cmdButtonLayout->removeWidget(buttonDelete);
            disconnect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
            if (defaultForm)
            {
                delete buttonDelete;
                buttonDelete = 0 /*nullptr*/;
            }
        }
    }
}


int FormGrid::exec()
{
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->setColumnsHeaders();
        grdTable->setCurrentFocus();
    }
    setButtons();
    return Form::exec();
}


void FormGrid::show()
{
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->setColumnsHeaders();
        grdTable->setCurrentFocus();
    }
    setButtons();
    Form::show();
}


void FormGrid::activateWidget()
{
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->setFocus();
    }
}


void FormGrid::cmdAdd()
{
    if (buttonAdd != 0 /*nullptr*/ && buttonAdd->isVisible() && buttonAdd->isEnabled())
    {
        grdTable->cmdAdd();
    }
    grdTable->setFocus();
    setButtons();
    showPhoto();
}


void FormGrid::cmdDelete()
{
    if (buttonDelete != 0 /*nullptr*/ && buttonDelete->isVisible() && buttonDelete->isEnabled())
    {
        grdTable->cmdDelete();
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdView()
{
    if (buttonView != 0 /*nullptr*/ && buttonView->isVisible() && buttonView->isEnabled())
    {
        grdTable->cmdView();
    }
}


void FormGrid::cmdRequery()
{
    grdTable->cmdRequery();
    if (parent->rowCount() == 0)
    {
        app->showMessageOnStatusBar(trUtf8("Ничего не найдено."));
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdQuery()
{
    if (buttonQuery != 0 /*nullptr*/ && buttonQuery->isVisible() && buttonQuery->isEnabled())
    {
        parent->getScriptEngine()->eventQuery();
    }
    grdTable->setFocus();
}


void FormGrid::cmdPrint(bool autoPrint)
{
    if (buttonPrint != 0 /*nullptr*/ && buttonPrint->isVisible() && buttonPrint->isEnabled())
    {
        QHBoxLayout* cmdButtonLayout = static_cast<QHBoxLayout*>(formWidget->findChild("cmdButtonLayout"));
        QString fileName = app->getReportFile(getParent()->getTagName(), autoPrint, formWidget, cmdButtonLayout->contentsRect());
        if (fileName.size() > 0)
            parent->print(fileName);
    }
    grdTable->setFocus();
}


void FormGrid::cmdLoad()
{
    if (buttonLoad != 0 /*nullptr*/ && buttonLoad->isVisible() && buttonLoad->isEnabled())
    {
        parent->load();
    }
    grdTable->setFocus();
    setButtons();
}


void FormGrid::cmdSave()
{
    if (buttonSave != 0 /*nullptr*/ && buttonSave->isVisible() && buttonSave->isEnabled())
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
    if (parent != 0 /*nullptr*/)
    {
        if (parent->rowCount() > 0)
        {
            if (buttonAdd != 0 /*nullptr*/)
                buttonAdd->setEnabled(parent->isInsertable() && enabled);
            if (buttonDelete != 0 /*nullptr*/)
                buttonDelete->setEnabled(parent->isDeleteable() && enabled);
            if (buttonView != 0 /*nullptr*/)
                buttonView->setEnabled(parent->isViewable());
            if (buttonPrint != 0 /*nullptr*/)
                buttonPrint->setEnabled(true);
            if (buttonSave != 0 /*nullptr*/)
                buttonSave->setEnabled(true);
        }
        else
        {
            if (buttonAdd != 0 /*nullptr*/)
                buttonAdd->setEnabled(enabled);
            if (buttonDelete != 0 /*nullptr*/)
                buttonDelete->setEnabled(false);
            if (buttonView != 0 /*nullptr*/)
                buttonView->setEnabled(false);
            if (buttonPrint != 0 /*nullptr*/)
                buttonPrint->setEnabled(false);
            if (buttonSave != 0 /*nullptr*/)
                buttonSave->setEnabled(false);
        }
    }
}


void FormGrid::setEnabled(bool enabled)
{
    Form::setEnabled(enabled);
    if (buttonAdd != 0 /*nullptr*/)
        buttonAdd->setEnabled(enabled);
    if (buttonDelete != 0 /*nullptr*/)
        buttonDelete->setEnabled(enabled);
    if (grdTable != 0 /*nullptr*/)
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
    if (gt != 0 /*nullptr*/)
    {
        if (defaultForm)
            delete grdTable;
        grdTable = gt;
    }
}

