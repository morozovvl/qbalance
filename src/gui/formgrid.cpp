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
#include <QSqlTableModel>
#include <QStringList>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QRect>
#include <QPalette>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPainter>
#include <QUrl>
#include "formgrid.h"
#include "picture.h"
#include "tableview.h"
#include "myitemdelegate.h"
#include "../kernel/essence.h"
#include "../kernel/app.h"
#include "../kernel/table.h"
#include "../storage/mysqlrelationaltablemodel.h"

FormGrid::FormGrid(QObject* parent/* = NULL*/)
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
}


void FormGrid::createForm(QString fileName, QWidget* pwgt/* = 0*/)
{
    Form::createForm(fileName, pwgt);
    if (parent != 0)
    {
       tableModel = parent->getMyRelationalTableModel();
    }

     if (defaultForm)
     {   // Если форма создана автоматически
        grdTable = new TableView(formWidget, this);
        grdTable->setApp(TApplication::exemplar());
        grdTable->setTagName(getParent()->getTagName());
        grdTable->setObjectName("tableView");
        grdTable->setTableModel(tableModel);
        grdTable->horizontalHeader()->setClickable(false);
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
        tableLayout = (QVBoxLayout*)qFindChild<QVBoxLayout*>(formWidget, "tableLayout");
        grdTable = (TableView*)qFindChild<TableView*>(formWidget, "tableView");
        if (grdTable != 0)
        {
            grdTable->setApp(TApplication::exemplar());
            grdTable->setTagName(getParent()->getTagName());
            grdTable->setParent(formWidget);
            grdTable->setFormGrid(this);
            grdTable->setTableModel(tableModel);
            grdTable->horizontalHeader()->setClickable(false);
            grdTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        }
    }
    if (defaultForm)
    {
        picture = new Picture(formWidget);
        picture->setObjectName("picture");
        tableLayout->addWidget(picture);
    }
    else
    {
        picture = (Picture*)qFindChild<QFrame*>(formWidget, "picture");
    }
    picture->hide();
    if (picture != 0 && grdTable != 0)
    {
        connect(grdTable, SIGNAL(rowChanged()), this, SLOT(showPhoto()));
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
                buttonLoad = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonLoad");
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
                buttonSave = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonSave");
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
                buttonPrint = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonPrint");
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
        buttonRequery = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonRequery");
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
            buttonView = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonView");
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
    if (parent != 0 && parent->isDeleteable())
    {
        if (defaultForm)
        {
            buttonDelete = new QPushButton();
            buttonDelete->setObjectName("buttonDelete");
            cmdButtonLayout->insertWidget(0, buttonDelete);
        }
        else
        {
            buttonDelete = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonDelete");
        }
        if (buttonDelete != 0)
        {
            connect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
        }
        else
        {
            parent->setDeleteable(false);
        }
    }
    // Подключим кнопку "Добавить"
    if (parent != 0 && parent->isInsertable())
    {
        if (defaultForm)
        {
            buttonAdd = new QPushButton();
            buttonAdd->setObjectName("buttonAdd");
            cmdButtonLayout->insertWidget(0, buttonAdd);
        }
        else
        {
            buttonAdd = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonAdd");
        }
        if (buttonAdd != 0)
        {
            connect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
        }
        else
        {
            parent->setInsertable(false);
        }
    }
}


int FormGrid::exec()
{
    return Form::exec();
}


void FormGrid::show()
{
    QModelIndex index = getCurrentIndex();
    Form::show();
    restoreCurrentIndex(index);
}


void FormGrid::cmdAdd()
{
    if (parent != 0 && parent->add())
    {
        if (parent->getMyRelationalTableModel()->rowCount() > 0)
        {   // Если записей стало больше 0, то активируем кнопку "Удалить"
            if (buttonDelete != 0)
                buttonDelete->setDisabled(false);
        }
    }
    formWidget->activateWindow();
    getGridTable()->setFocus();
}


void FormGrid::cmdDelete()
{
    QModelIndex index = getCurrentIndex();      // Запомним, где стоял курсор перед удалением записи
    if (parent != 0 && parent->remove())
    {
        int rowCount = parent->getMyRelationalTableModel()->rowCount();
        if (rowCount > 0)
        {   // Если после удаления строки в таблице остались еще записи
            if (index.row() < rowCount)
                setCurrentIndex(index);
            else
                setCurrentIndex(index.sibling(index.row() - 1, index.column()));    // Если была удалена последняя строка
        }
        else
            if (buttonDelete != 0)
                buttonDelete->setDisabled(true);
    }
    formWidget->activateWindow();
    getGridTable()->setFocus();
}


void FormGrid::cmdView()
{
    picture->hide();
    if (parent != 0)
        parent->view();
    getGridTable()->setFocus();
}


void FormGrid::cmdRequery()
{
    QModelIndex index = getCurrentIndex();
    parent->query();
    restoreCurrentIndex(index);
    formWidget->activateWindow();
    getGridTable()->setFocus();
}


void FormGrid::showPhoto()
{
    if (picture && parent != 0)
    {
        QString photoFileName = parent->getPhotoFile(); // Получим имя фотографии
        if (photoFileName.size() > 0 && photoFileName.left(4) != "http")
        {   // Если локальный файл с фотографией существует и имя файла не является адресом в интернете (из интернета фотографию еще нужно скачать в локальный файл)
            if (QDir().exists(photoFileName))
                picture->setVisible(true);              // то включим просмотр фотографий
            else
                photoFileName = "";
        }
        picture->show(photoFileName);
    }
}


void FormGrid::calculate()
{
    QModelIndex index = getCurrentIndex();
    parent->setOldValue(((MyItemDelegate*)sender())->getOldValue());
    parent->calculate(getCurrentIndex());
    restoreCurrentIndex(index);
}


QVariant FormGrid::getValue(QString fieldName)
{
    if (lSelected && parent != 0)
        return parent->getValue(fieldName);
    return QVariant();
}


/*
// Пока не будем использовать
void FormGrid::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_F2) {
        cmdView();
    }
    else
        Form::keyPressEvent(event);
}
*/


void FormGrid::setGridFocus()
{
    formWidget->activateWindow();
    if (grdTable != 0)
        grdTable->setFocus();
}

void FormGrid::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);          // Просто избавимся от предупреждения о не используемой переменной
//    setShowFocus();
}

void FormGrid::cmdPrint()
{
    QDir dir = QDir(REPORT_DIR);
    QString ext = "." + TApplication::exemplar()->getReportTemplateExt();
    QStringList files = dir.entryList(QStringList(getConfigName() + ".*" + ext), QDir::Files, QDir::Name);
    QStringList reports;
    QMenu* menu = new QMenu(formWidget);
    QAction* newReportAct = menu->addAction(QObject::trUtf8("Создать новый отчет..."));
    if (files.size() > 0)
    {
        menu->addSeparator();
        for (int i = 0; i < files.size(); i++)
        {
            QString file = files.at(i);
            file.remove(getConfigName() + ".", Qt::CaseInsensitive);
            file.remove(ext, Qt::CaseInsensitive);
            reports << file;
            menu->addAction(file);
        }
    }
    QHBoxLayout* cmdButtonLayout = qFindChild<QHBoxLayout*>(formWidget, "cmdButtonLayout");
    if (cmdButtonLayout != 0)
    {
        QAction* action = menu->exec(formWidget->mapToGlobal(QPoint(cmdButtonLayout->contentsRect().x() + 100, cmdButtonLayout->contentsRect().y()-menu->height())));
        if (action > 0)
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
                    parent->print(REPORT_DIR + getConfigName() + "." + reportName);
            }
            else
                parent->print(REPORT_DIR + getConfigName() + "." + action->text());
        }
    }
    formWidget->activateWindow();
    getGridTable()->setFocus();
}


void FormGrid::cmdLoad()
{
    getScriptEngine()->eventImport(this);
}


void FormGrid::cmdSave()
{
    getScriptEngine()->eventExport(this);
}


void FormGrid::showGridLine(int currentRow)
{
    if (parent->getTableModel()->rowCount() > 0)
    {                      // Если есть что показывать
        if ((currentRow >= 0) && (currentRow < parent->getTableModel()->rowCount()))
            grdTable->selectRow(currentRow);
        else
          grdTable->selectRow(0);
    }
}


void FormGrid::readSettings()
{
    Form::readSettings();
    if (grdTable != 0)
    {
        QSettings settings;
        if (settings.status() == QSettings::NoError)
        {
            settings.beginGroup(configName);
            int columnCount = settings.beginReadArray("grid");
            int i = 0;
            while (i < columnCount)
            {
                settings.setArrayIndex(i);
                int width = settings.value("width", 100).toInt();
                grdTable->setColumnWidth(i, (width == 0 ? 50: width));
                i++;
            }
            settings.endArray();
            settings.endGroup();
        }
    }
}


void FormGrid::writeSettings()
{
    Form::writeSettings();
    if (grdTable != 0)
    {
        QSettings settings;
        int columnCount = grdTable->model()->columnCount();
        settings.beginGroup(configName);
        settings.beginWriteArray("grid", columnCount);
        int i = 0;
        while (i < columnCount)
        {
            settings.setArrayIndex(i);
            settings.setValue("width", grdTable->columnWidth(i));
            i++;
        }
        settings.endArray();
        settings.endGroup();
    }
}


QDomElement FormGrid::createWidgetsStructure()
{
    QDomDocument* doc = new QDomDocument();
    QDomElement vboxLayout = Form::createWidgetsStructure();
    QDomElement item, layout;
    for (int i = 0; vboxLayout.childNodes().count(); i++)
    {
        item = vboxLayout.childNodes().at(i).firstChildElement("widget");
        if (!item.isNull()) {
           layout = item.firstChildElement("layout");
            if (!layout.isNull() && layout.attribute("name").compare("cmdButtonLayout", Qt::CaseSensitive) == 0)
            {
                if (buttonPrint != 0)
                {
                    item = doc->createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonPrint));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonRequery != 0)
                {
                    item = doc->createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonRequery));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonView != 0)
                {
                    item = doc->createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonView));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonDelete != 0)
                {
                    item = doc->createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonDelete));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonAdd != 0)
                {
                    item = doc->createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonAdd));
                    layout.insertBefore(item, QDomNode());
                }
                break;
            }
        }
    }
    if (tableLayout != 0)
    {
        QDomElement widget, hlayout;
        hlayout = doc->createElement("layout");
        hlayout.setAttribute("class", "QVBoxLayout");
        hlayout.setAttribute("name", tableLayout->objectName());
        if (grdTable != 0)
        {
            widget = doc->createElement("widget");
            widget.setAttribute("class", grdTable->metaObject()->className());
            widget.setAttribute("name", grdTable->objectName());
            item = doc->createElement("item");
            item.appendChild(widget);
            hlayout.appendChild(item);
        }
        if (picture != 0)
        {
            widget = doc->createElement("widget");
            widget.setAttribute("class", picture->metaObject()->className());
            widget.setAttribute("name", picture->objectName());
            item = doc->createElement("item");
            item.appendChild(widget);
            hlayout.appendChild(item);
        }
        item = doc->createElement("item");
        item.appendChild(hlayout);
        vboxLayout.insertBefore(item, QDomNode());
    }
    delete doc;
    return vboxLayout;
}


void FormGrid::restoreCurrentIndex(QModelIndex index)
{
    if (index.row() == -1 && index.column() == -1)
    {
        index = getParent()->getTableModel()->index(0, 0);
        setCurrentIndex(index);
        grdTable->selectNextColumn();
    }
    else
        setCurrentIndex(index);
    getGridTable()->setFocus();
}
