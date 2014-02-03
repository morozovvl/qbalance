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

#include <QApplication>
#include <QtSql/QSqlTableModel>
#include <QtCore/QStringList>
#include <QAbstractItemView>
#include <QtCore/QModelIndex>
#include <QtCore/QRect>
#include <QPalette>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPainter>
#include <QtCore/QUrl>
#include <QHeaderView>
#include <QPushButton>
#include <QInputDialog>
#include <QDebug>
#include "formgrid.h"
#include "picture.h"
#include "tableview.h"
#include "myitemdelegate.h"
#include "../kernel/essence.h"
#include "../kernel/app.h"
#include "../kernel/table.h"
#include "../storage/mysqlrelationaltablemodel.h"


FormGrid::FormGrid(QObject* parent/* = 0*/)
: Form(parent)
{
    grdTable = 0;
    tableModel = 0;
    tableLayout = 0;
    imageLayout = 0;
    picture = 0;
    buttonAdd = 0;
    buttonDelete = 0;
    buttonView = 0;
    buttonRequery = 0;
    buttonPrint = 0;
    buttonLoad = 0;
    buttonSave = 0;
    columnsSettingsReaded = false;
}


FormGrid::~FormGrid()
{
}


void FormGrid::close()
{
    writeSettings();
    if (defaultForm)
    {
        if (grdTable != 0)
        {
            delete grdTable;
        }
    }
    Form::close();
}


void FormGrid::createForm(QString fileName, QWidget* pwgt/* = 0*/)
{
    Form::createForm(fileName, pwgt);
    if (parent != 0)
    {
       tableModel = parent->getTableModel();
    }

     if (defaultForm)
     {   // Если форма создана автоматически
        grdTable = new TableView(formWidget, this);
        grdTable->setApp(app);
        grdTable->setTagName(getParent()->getTagName());
        grdTable->setObjectName("tableView");
        grdTable->setTableModel(tableModel);
        grdTable->horizontalHeader()->setSectionsClickable(false);
        grdTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableLayout = new QVBoxLayout();
        tableLayout->setObjectName("tableLayout");
        tableLayout->addWidget(grdTable);
        if (vbxLayout != 0)
        {
            vbxLayout->insertLayout(0, tableLayout);
        }
    }
    else
    {   // Была загружена пользовательская форма
        tableLayout = (QVBoxLayout*)formWidget->findChild("tableLayout");
        grdTable = (TableView*)formWidget->findChild("tableView");
        if (grdTable != 0)
        {
            grdTable->setApp(app);
            grdTable->setTagName(getParent()->getTagName());
            grdTable->setParent(formWidget);
            grdTable->setFormGrid(this);
            grdTable->setTableModel(tableModel);
            grdTable->horizontalHeader()->setSectionsClickable(false);
            grdTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        }
    }
    if (defaultForm)
    {
        imageLayout = new QHBoxLayout();
        imageLayout->setObjectName("imageLayout");
        picture = new Picture(formWidget);
        picture->setObjectName("picture");
        imageLayout->addWidget(picture);
        imageLayout->addStretch(1);
        if (vbxLayout != 0)
        {
            vbxLayout->insertLayout(1, imageLayout);
        }
    }
    else
    {
        picture = (Picture*)formWidget->findChild("picture");
    }
    if (picture != 0)
    {
        picture->setForm(this);
        picture->setApp(app);
        picture->hide();
        if (grdTable != 0)
        {
            connect(parent, SIGNAL(photoLoaded()), this, SLOT(showPhoto()));
        }
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
    setButtonDelete(true);
    // Подключим кнопку "Добавить"
    setButtonAdd(true);
    if (parent != 0 && grdTable != 0)
        grdTable->setReadOnly(parent->isReadOnly());
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
            else
            {
                parent->setInsertable(false);
            }
        }
    }
    else
    {
        if (!defaultForm)
            buttonAdd = (QPushButton*)formWidget->findChild("buttonAdd");
        if (parent != 0 && buttonAdd != 0)
        {
            cmdButtonLayout->removeWidget(buttonAdd);
            disconnect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
            if (defaultForm)
            {
                delete buttonAdd;
                buttonAdd = 0;
            }
            parent->setInsertable(false);
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
            else
            {
                parent->setDeleteable(false);
            }
        }
    }
    else
    {
        if (!defaultForm)
            buttonDelete = (QPushButton*)formWidget->findChild("buttonDelete");
        if (parent != 0 && buttonDelete != 0)
        {
            cmdButtonLayout->removeWidget(buttonDelete);
            disconnect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
            if (defaultForm)
            {
                delete buttonDelete;
                buttonDelete = 0;
            }
            parent->setDeleteable(false);
        }
    }
}


int FormGrid::exec()
{
    if (grdTable != 0)
    {
        grdTable->setColumnsHeaders();
    }
    setButtons();
    return Form::exec();
}


void FormGrid::show()
{
    QModelIndex index = getCurrentIndex();
    restoreCurrentIndex(index);
    if (grdTable != 0)
    {
        grdTable->setColumnsHeaders();
        showPhoto();
    }
    setButtons();
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
        QModelIndex index = getCurrentIndex();      // Запомним, где стоял курсор
        if (parent != 0 && parent->add())
        {
            int rowCount = parent->getTableModel()->rowCount();
            setCurrentIndex(index.sibling(rowCount - 1, index.column()));    // Если была удалена последняя строка
            if (rowCount > 0)
            {   // Если записей стало больше 0, то активируем кнопку "Удалить"
                if (buttonDelete != 0)
                    buttonDelete->setDisabled(false);
            }
            setButtons();
            setGridFocus();

            showPhoto();
        }
    }
}


void FormGrid::cmdDelete()
{
    if (buttonDelete != 0 && buttonDelete->isVisible() && buttonDelete->isEnabled())
    {
        QModelIndex index = getCurrentIndex();      // Запомним, где стоял курсор перед удалением записи
        if (parent != 0 && parent->remove())
        {
            int rowCount = parent->getTableModel()->rowCount();
            if (rowCount > 0)
            {   // Если после удаления строки в таблице остались еще записи
                if (index.row() < rowCount)
                    setCurrentIndex(index);
                else
                    setCurrentIndex(index.sibling(index.row() - 1, index.column()));    // Если была удалена последняя строка
            }
            else
            {
                if (buttonDelete != 0)
                    buttonDelete->setDisabled(true);
                picture->setVisibility(false);             // Строк в документе (справочнике) больше нет, выключим просмотр фотографий
            }
        }
        setButtons();
        setGridFocus();
    }
}


void FormGrid::cmdView()
{
    if (buttonView != 0 && buttonView->isVisible() && buttonView->isEnabled())
    {
        picture->hide();
        if (parent != 0)
            parent->view();
    }
}


void FormGrid::cmdRequery()
{
    app->showMessageOnStatusBar(tr("Загрузка с сервера данных из таблицы ") + parent->getTagName() + "...");
    parent->query();
    app->showMessageOnStatusBar("");
    setButtons();
    setGridFocus();
}


void FormGrid::cmdPrint()
{
    if (buttonPrint != 0 && buttonPrint->isVisible() && buttonPrint->isEnabled())
    {
        QDir dir = QDir(app->getReportsPath());
        QString ext = "." + app->getReportTemplateExt();
        // Получим список локальных шаблонов отчетов
        QStringList files = dir.entryList(QStringList(getParent()->getTagName() + ".*" + ext), QDir::Files, QDir::Name);
        // И шаблоны с сервера
        QStringList fs = db->getFilesList(getParent()->getTagName(), ReportTemplateFileType);
        foreach (QString f, fs)
        {
            if (!files.contains(f))
                files << f;
        }

        QStringList reports;
        QMenu* menu = new QMenu(formWidget);
        QAction* newReportAct = new QAction(this);
        if (app->isSA())
            menu->addAction(QObject::trUtf8("Создать новый отчет..."));
        if (files.count() > 0)
        {
            if (app->isSA())
                menu->addSeparator();
            for (int i = 0; i < files.size(); i++)
            {
                QString file = files.at(i);
                QString oldFile = file;
                file.remove(getParent()->getTagName() + ".", Qt::CaseInsensitive);      // Уберем префикс файла
                if (file != oldFile)
                {
                    file.remove(ext, Qt::CaseInsensitive);                                  // И его суффикс
                    reports << file;                                                        // Оставшуюся часть (название отчета) поместим в меню
                    menu->addAction(file);
                }
            }
        }
        QHBoxLayout* cmdButtonLayout = (QHBoxLayout*)formWidget->findChild("cmdButtonLayout");
        if (cmdButtonLayout != 0)
        {
            QAction* action = menu->exec(formWidget->mapToGlobal(QPoint(cmdButtonLayout->contentsRect().x() + 100, cmdButtonLayout->contentsRect().y()-menu->height())));
            if (action != 0)
            {
                if (action == newReportAct)
                {
                    QString reportName;                         // Создадим имя отчета по умолчанию
                    int i = 1;
                    do
                    {
                        reportName = QString("Отчет%1").arg(i++);
                    } while (reports.contains(reportName));
                    bool ok;
                    reportName = QInputDialog::getText(formWidget, QObject::trUtf8("Создать новый отчет"),
                                                  QObject::trUtf8("Наименование отчета:"), QLineEdit::Normal,
                                                  reportName, &ok);
                    if (ok && !reportName.isEmpty())
                        parent->print(getParent()->getTagName() + "." + reportName + "." + app->getReportTemplateExt());
                }
                else
                    parent->print(getParent()->getTagName() + "." + action->text() + "." + app->getReportTemplateExt());
            }
        }
        setGridFocus();
    }
}


void FormGrid::cmdLoad()
{
    if (buttonLoad != 0 && buttonLoad->isVisible() && buttonLoad->isEnabled())
    {
        parent->getScriptEngine()->eventImport(this);
    }
}


void FormGrid::cmdSave()
{
    if (buttonSave != 0 && buttonSave->isVisible() && buttonSave->isEnabled())
    {
        parent->getScriptEngine()->eventExport(this);
    }
}


void FormGrid::setButtons()
{
    if (parent != 0)
    {
        if (parent->getTableModel()->rowCount() > 0)
        {
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


void FormGrid::showPhoto()
{
    if (picture != 0 && parent != 0)
    {
        if (parent->getTableModel()->rowCount() > 0)
        {
            QString photoFileName = parent->getPhotoFile(); // Получим имя фотографии
            if (photoFileName.size() > 0 && photoFileName.left(4) != "http")
            {   // Если локальный файл с фотографией существует и имя файла не является адресом в интернете (из интернета фотографию еще нужно скачать в локальный файл)
                if (QDir().exists(photoFileName))
                    picture->setVisibility(true);              // то включим просмотр фотографий
                else
                    photoFileName = "";
            }
            if (parent->getPhotoNameField().size() > 0)
                picture->setPhotoWindowTitle(parent->getValue(parent->getPhotoNameField()).toString().trimmed());
            picture->show(photoFileName);
        }
        else
            picture->setVisibility(false);
    }
}


void FormGrid::calculate()
{
    grdTable->setUpdatesEnabled(false);
    QModelIndex index = getCurrentIndex();
    if (!parent->calculate(index))
        grdTable->reset();
    else
        grdTable->repaint();
    grdTable->selectNextColumn();       // Передвинуть курсор на следующую колонку
    grdTable->setUpdatesEnabled(true);
}


QVariant FormGrid::getValue(QString fieldName)
{
    if (lSelected && parent != 0)
        return parent->getValue(fieldName);
    return QVariant();
}


QModelIndex FormGrid::getCurrentIndex()
{
    QModelIndex index;
    if (grdTable != 0)
    {
        index = grdTable->currentIndex();
    }
    return index;
}


void FormGrid::setCurrentIndex(QModelIndex index)
{
    if (grdTable != 0)
        grdTable->setCurrentIndex(index);
}


void FormGrid::setGridFocus()
{
    activateSubWindow();
    if (grdTable != 0)
    {
        grdTable->setFocus();
    }
}


void FormGrid::selectRow(int row)
{
    grdTable->selectRow(row);
}


void FormGrid::keyPressEvent(QKeyEvent *event)
{
    Form::keyPressEvent(event);
    if (event->modifiers() == Qt::ControlModifier)
    {
        switch (event->key())
        {
            case Qt::Key_Insert:
                {
                    cmdAdd();
                    event->accept();
                }
                break;
            case Qt::Key_Delete:
                {
                    cmdDelete();
                    event->accept();
                }
                break;
        }
    }
    else
    {
        switch (event->key())
        {
            case Qt::Key_Return:
                {
                    grdTable->selectNextColumn();
                    event->accept();
                }
                break;
            case Qt::Key_Enter:
                {
                    grdTable->selectNextColumn();
                    event->accept();
                }
                break;
            case Qt::Key_Right:
                {
                    grdTable->selectNextColumn();
                    event->accept();
                }
                break;
            case Qt::Key_Tab:
                {
                    grdTable->selectNextColumn();
                    event->accept();
                }
                break;
            case Qt::Key_Left:
                {
                    grdTable->selectPreviousColumn();
                    event->accept();
                }
                break;
            case Qt::Key_F2:
                {
                    cmdView();
                    event->accept();
                }
                break;
        }
    }
}


void FormGrid::readColumnsSettings()
// Считывает сохраненную информацию о ширине столбцов при открытии формы с таблицей
{
    bool readedFromEnv = true;  // Предположим, что удастся прочитать конфигурацию из окружения
    Form::readSettings();
    if (grdTable != 0)
    {
        QSettings settings;
        if (settings.status() == QSettings::NoError)
        {
            settings.beginGroup(configName);
            int columnCount = settings.beginReadArray("grid");
            if (columnCount > 0)
            {
                for (int i = 0; i < columnCount; i++)
                {
                    settings.setArrayIndex(i);
                    int width = settings.value("width", 100).toInt();
                    if (width == 0)
                        width = 100;
                    grdTable->setColumnWidth(i, width);
                }
            }
            else
                readedFromEnv = false;
            settings.endArray();
            settings.endGroup();
        }
        if (!readedFromEnv)
        {
            // Если информация о ширине столбца отстутствует в окружении программы, попытаемся прочитать ее из базы
            QSqlQuery config;
            QMap<QString, int> values;

            app->showMessageOnStatusBar(tr("Загрузка с сервера ширины столбцов справочника ") + configName + "...");
            config = db->getConfig();
            config.first();
            while (config.isValid())
            {
                if (config.record().value("group").toString() == configName)
                {
                    values.insert(config.value(0).toString(), config.value(1).toInt());
                }
                config.next();
            }
            int i = 0;
            while (true)
            {
                QString name = QString("grid/%1/width").arg(i);
                if (values.contains(name))
                {
                    int width = values.value(name, 100);
                    grdTable->setColumnWidth(i, width);
                }
                else
                    break;
                i++;
            }
            app->showMessageOnStatusBar("");
        }
        columnsSettingsReaded = true;
    }
}


void FormGrid::writeSettings()
{
    if (columnsSettingsReaded)
    {
        if (grdTable != 0)
        {
            QSettings settings;
//            int columnCount = grdTable->model()->columnCount();
            int columnCount = tableModel->columnCount();
            if (columnCount > 0)
            {
                settings.beginGroup(configName);
                settings.beginWriteArray("grid", columnCount);
                for (int i = 0; i < columnCount; i++)
                {
                    int width = grdTable->columnWidth(i);
                    settings.setArrayIndex(i);
                    settings.setValue("width", width);

                }
                settings.endArray();
                settings.endGroup();

                // Если работает пользователь SA, то сохраним конфигурацию окна на сервере
                if (app->getSaveFormConfigToDb())
                {
                    app->showMessageOnStatusBar(tr("Сохранение на сервере ширины столбцов справочника ") + configName + "...");
                    for (int i = 0; i < columnCount; i++)
                    {
                        int width = grdTable->columnWidth(i);
                        db->setConfig(configName, QString("grid/%1/width").arg(i), QString("%1").arg(width));
                    }
                    app->showMessageOnStatusBar("");
                }
            }
        }
    }
}


void FormGrid::restoreCurrentIndex(QModelIndex index)
{
    if (index.row() == -1 && index.column() == -1)
    {
        index = getParent()->getTableModel()->index(0, 0);
        setCurrentIndex(index);
        if (grdTable != 0)
            grdTable->selectNextColumn();
    }
    else
        setCurrentIndex(index);
}


void FormGrid::setEnabled(bool enabled)
{
    buttonAdd->setEnabled(enabled);
    buttonDelete->setEnabled(enabled);
    if (grdTable != 0)
        grdTable->setReadOnly(!enabled);
}


