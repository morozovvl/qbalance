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
#include "formgrid.h"
#include "picture.h"
#include "tableview.h"
#include "../essence.h"
#include "../app.h"
#include "../mysqlrelationaltablemodel.h"
#include "../table.h"

FormGrid::FormGrid(QObject* parent/* = NULL*/)
: Form(parent)
, grdTable(NULL)
, tableModel(NULL)
, tableLayout(NULL)
, imageLayout(NULL)
, picture(NULL)
, buttonAdd(NULL)
, buttonDelete(NULL)
, buttonView(NULL)
, buttonRequery(NULL)
, buttonPrint(NULL)
{
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
        grdTable = new TableView(this, formWidget);
        grdTable->setApp(TApplication::exemplar());
        grdTable->setObjectName("tableView");
        grdTable->setModel(tableModel);
        grdTable->horizontalHeader()->setClickable(false);
        grdTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableLayout = new QHBoxLayout();
        tableLayout->setObjectName("tableLayout");
        tableLayout->addWidget(grdTable);
        if (vbxLayout != 0)
        {
            vbxLayout->insertLayout(0, tableLayout);
        }
    }
    else
    {   // Была загружена пользовательская форма
        tableLayout = (QHBoxLayout*)qFindChild<QHBoxLayout*>(formWidget, "tableLayout");
        grdTable = (TableView*)qFindChild<QTableWidget*>(formWidget, "tableView");
        if (grdTable != 0)
        {
            grdTable->setApp(TApplication::exemplar());
            grdTable->setParent(formWidget);
            grdTable->setFormGrid(this);
            grdTable->setModel(tableModel);
            grdTable->horizontalHeader()->setClickable(false);
            grdTable->setSelectionBehavior(QAbstractItemView::SelectRows);
            if (tableLayout != 0)
            {
                tableLayout->addWidget(grdTable);
            }
        }
    }

    if (parent != 0)
    {
        photoPath = parent->getPhotoPath();
    }
    if (photoPath.size() > 0)
    {                                // Если есть фотографии, то будем отображать их
        if (defaultForm)
        {
            picture = new Picture(formWidget);
            picture->setObjectName("picture");
        }
        else
        {
            picture = (Picture*)qFindChild<QFrame*>(formWidget, "picture");
        }
        if (picture != 0)
        {
            imageLayout = new QVBoxLayout();
            imageLayout->setObjectName("imageLayout");
            imageLayout->addWidget(picture, 1, Qt::AlignTop);
            if (tableLayout != 0)
            {
                tableLayout->addLayout(imageLayout);
            }
            if (grdTable != 0)
            {
                connect(grdTable, SIGNAL(rowChanged()), this, SLOT(showPhoto()));
            }
        }
    }

    // Подключим кнопку "Печать"
    if (parent != 0 && parent->isPrintable())
    {
        if (defaultForm)
        {
            buttonPrint = new QPushButton(tr("&Печать"));
            buttonPrint->setObjectName("buttonPrint");
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
            cmdButtonLayout->insertWidget(0, buttonPrint);
        }
        else
        {
            parent->setPrintable(false);
        }
    }
    // Подключим кнопку "Обновить"
    if (defaultForm)
    {
        buttonRequery = new QPushButton(tr("&Обновить"));
        buttonRequery->setObjectName("buttonRequery");
    }
    else
    {
        buttonRequery = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonRequery");
    }
    if (buttonRequery != 0)
    {
        connect(buttonRequery, SIGNAL(clicked()), this, SLOT(cmdRequery()));
        cmdButtonLayout->insertWidget(0, buttonRequery);
    }
    // Подключим кнопку "Просмотреть"
    if (parent != 0 && parent->isViewable())
    {
        if (defaultForm)
        {
            buttonView = new QPushButton(tr("&Просмотреть"));
            buttonView->setObjectName("buttonView");
        }
        else
        {
            buttonView = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonView");
        }
        if (buttonView != 0)
        {
            connect(buttonView, SIGNAL(clicked()), this, SLOT(cmdView()));
            cmdButtonLayout->insertWidget(0, buttonView);
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
            buttonDelete = new QPushButton(tr("&Удалить"));
            buttonDelete->setObjectName("buttonDelete");
        }
        else
        {
            buttonDelete = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonDelete");
        }
        if (buttonDelete != 0)
        {
            connect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
            cmdButtonLayout->insertWidget(0, buttonDelete);
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
            buttonAdd = new QPushButton(tr("&Добавить"));
            buttonAdd->setObjectName("buttonAdd");
        }
        else
        {
            buttonAdd = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonAdd");
        }
        if (buttonAdd != 0)
        {
            connect(buttonAdd, SIGNAL(clicked()), this, SLOT(cmdAdd()));
            cmdButtonLayout->insertWidget(0, buttonAdd);
        }
        else
        {
            parent->setInsertable(false);
        }
    }
}


void FormGrid::close()
{
    QItemSelectionModel* model = grdTable->selectionModel();
    delete model;
    if (defaultForm)
        delete grdTable;
    Form::close();
}


void FormGrid::show()
{
    Form::show();
    setShowFocus();
}


void FormGrid::cmdAdd()
{
    if (parent != 0 && parent->add())
        add();
}


void FormGrid::cmdDelete()
{
    if (parent != 0 && parent->remove())
        remove();
}


void FormGrid::cmdView()
{
    if (parent != 0)
        parent->view();
}


void FormGrid::showPhoto()
{
    if (picture && parent != 0)
    {
        QString photoFileName = photoPath + "/" + parent->getValue("код").toString().trimmed() + ".jpg";
        picture->show(photoFileName);
    }
}


bool FormGrid::calculate()
{
    QModelIndex index = getCurrentIndex();
    bool result = parent->calculate(index);
    setCurrentIndex(index);
    FormGrid::setShowFocus();
    return result;
}


QString FormGrid::getColumnHeader(QString columnName)
{
    return tableModel->headerData(tableModel->fieldIndex(columnName), Qt::Horizontal).toString();
}


QVariant FormGrid::getValue(QString fieldName)
{
    if (lSelected && parent != 0)
        return parent->getValue(fieldName);
    return QVariant();
}


int FormGrid::getHeaderIndex(QString headName)
{
    QHeaderView* header = grdTable->horizontalHeader();
    for (int i = 0; tableModel->columnCount(); i++)
    {
        if (tableModel->headerData(i, Qt::Horizontal) == headName)
            return header->visualIndex(i);
    }
    return -1;
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


void FormGrid::setShowFocus()
{
    setGridFocus();
}


void FormGrid::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);          // Просто избавимся от предупреждения о не используемой переменной
    setShowFocus();
}


void FormGrid::cmdPrint()
{
    QDir dir = QDir(REPORT_DIR);
    QStringList files = dir.entryList(QStringList(getConfigName() + ".*.ods"), QDir::Files, QDir::Name);
    QStringList reports;
    QMenu* menu = new QMenu(formWidget);
    QAction* newReportAct = menu->addAction(QObject::tr("Создать новый отчет..."));
    if (files.size() > 0)
    {
        menu->addSeparator();
        for (int i = 0; i < files.size(); i++)
        {
            QString file = files.at(i);
            file.remove(getConfigName() + ".", Qt::CaseInsensitive);
            file.remove(".ods", Qt::CaseInsensitive);
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
                reportName = QInputDialog::getText(formWidget, tr("Создать новый отчет"),
                                              tr("Наименование отчета:"), QLineEdit::Normal,
                                              reportName, &ok);
                if (ok && !reportName.isEmpty())
                    parent->print(REPORT_DIR + getConfigName() + "." + reportName);
            }
            else
                parent->print(REPORT_DIR + getConfigName() + "." + action->text());
        }
    }
    FormGrid::setShowFocus();
}


void FormGrid::add()
{
    QModelIndex index = getCurrentIndex();      // Запомним, где стоял курсор перед удалением записи
    cmdRequery();
    if (parent->getIdFieldName().size() > 0)
    {         // Если существует ключевое поле
       int maxIndex = 0;
       qulonglong maxValue = 0;
       for (int i = 0; i < parent->getMyRelationalTableModel()->rowCount(); i++)
       {
          qulonglong value = parent->getId(i);
          if (value > maxValue)
          {
              maxValue = value;
              maxIndex = i;
          }
       }
       grdTable->selectRow(maxIndex);   // установим курсор на последнюю добавленную запись
    }
    setCurrentIndex(index.sibling(getCurrentIndex().row(), index.column()));    // Поставим курсор на новую строку в старой колонке
    if (parent->getMyRelationalTableModel()->rowCount() > 0)
    {   // Если записей стало больше 0, то активируем кнопку "Удалить"
        if (buttonDelete != 0)
            buttonDelete->setDisabled(false);
    }
}


void FormGrid::remove()
{
    QModelIndex index = getCurrentIndex();      // Запомним, где стоял курсор перед удалением записи
    cmdRequery();
    int rowCount = parent->getMyRelationalTableModel()->rowCount();
    if (rowCount > 0)
    {   // Если после удаления строки в таблице остались еще записи
        if (index.row() < (rowCount - 1))
            setCurrentIndex(index);
        else
            setCurrentIndex(index.sibling(index.row() - 1, index.column()));    // Если была удалена последняя строка
    }
    else
        if (buttonDelete != 0)
            buttonDelete->setDisabled(true);
}


void FormGrid::query(QString param)
{
    QModelIndex index = getCurrentIndex();
    parent->query(param);
    setCurrentIndex(index);
    FormGrid::setShowFocus();
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
                grdTable->setColumnWidth(i, (width == 0 ? 10: width));
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
    QDomDocument doc;
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
                    item = doc.createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonPrint));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonRequery != 0)
                {
                    item = doc.createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonRequery));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonView != 0)
                {
                    item = doc.createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonView));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonDelete != 0)
                {
                    item = doc.createElement("item");
                    item.appendChild(createPushButtonElement((QWidget*)buttonDelete));
                    layout.insertBefore(item, QDomNode());
                }
                if (buttonAdd != 0)
                {
                    item = doc.createElement("item");
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
        hlayout = doc.createElement("layout");
        hlayout.setAttribute("class", "QHBoxLayout");
        hlayout.setAttribute("name", tableLayout->objectName());
        if (grdTable != 0)
        {
            widget = doc.createElement("widget");
            widget.setAttribute("class", grdTable->metaObject()->className());
            widget.setAttribute("name", grdTable->objectName());
            item = doc.createElement("item");
            item.appendChild(widget);
            hlayout.appendChild(item);
        }
        if (picture != 0)
        {
            widget = doc.createElement("widget");
            widget.setAttribute("class", picture->metaObject()->className());
            widget.setAttribute("name", picture->objectName());
            item = doc.createElement("item");
            item.appendChild(widget);
            hlayout.appendChild(item);
        }
        item = doc.createElement("item");
        item.appendChild(hlayout);
        vboxLayout.insertBefore(item, QDomNode());
    }
    return vboxLayout;
}


