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

#include <QLineEdit>
#include <QTableView>
#include <QtScript/QScriptContextInfo>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QDebug>
#include "../kernel/app.h"
#include "tableview.h"
#include "formgrid.h"
#include "../kernel/table.h"
#include "../engine/scriptengine.h"
#include "mylineitemdelegate.h"
#include "mynumericitemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mydateitemdelegate.h"
#include "../storage/dbfactory.h"


TableView::TableView(QWidget* pwgt, FormGrid* par): QTableView(pwgt)
{
    parent = par;
    parentWidget = pwgt;
    name = "TableView";
    app = 0;
    db = 0;
    essence = 0;
    picture = 0;
    tableModel = 0;
    fields = 0;
    columnsHeadersSeted = false;
    columns.clear();
    columnsSettingsReaded = false;

    if (verticalHeader()->minimumSectionSize() > 0)
        verticalHeader()->setDefaultSectionSize(verticalHeader()->minimumSectionSize());

    setFocusPolicy(Qt::StrongFocus);
}


TableView::~TableView()
{
    QItemSelectionModel *oldModel = selectionModel();
    delete oldModel;
}


void TableView::close()
{
    writeSettings();
}


void TableView::setEssence(Essence* ess)
{
    essence = ess;
    app = parent->getApp();
    db = app->getDBFactory();
    if (parent != 0)
    {
        fields = essence->getColumnsProperties();
        connect(essence, SIGNAL(photoLoaded()), this, SLOT(showPhoto()));

        tableModel = essence->getTableModel();

        QTableView::setModel(tableModel);

        connect(tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));

        essence->setGridTable(this);
        setReadOnly(essence->isReadOnly());
    }
}


void TableView::cmdDelete()
{
    QModelIndex index = currentIndex();      // Запомним, где стоял курсор перед удалением записи
    if (essence->remove())
    {
        int rowCount = tableModel->rowCount();
        if (rowCount > 0)
        {   // Если после удаления строки в таблице остались еще записи
            if (index.row() < rowCount)
                setCurrentIndex(index);
            else
                setCurrentIndex(index.sibling(index.row() - 1, index.column()));    // Если была удалена последняя строка
        }
        else
            showPhoto();
    }
    parent->setButtons();
    setFocus();
}


void TableView::cmdView()
{
    picture->hide();
    essence->view();
}


void TableView::cmdRequery()
{
//    app->showMessageOnStatusBar(tr("Загрузка с сервера данных из таблицы ") + essence->getTagName() + "...");
    essence->query();
//    app->showMessageOnStatusBar("");
    parent->setButtons();
    setFocus();
}


void TableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QTableView::currentChanged(current, previous);
    if (parent != 0)
    {
        if (current.row() >= 0 &&current.row() != previous.row() && tableModel->rowCount() > 0)
        {
            showPhoto();
            if (essence != 0)
                essence->afterRowChanged();
        }
    }
}


void TableView::keyPressEvent(QKeyEvent* event)
{
    if (app->readCardReader(event))
    {
        return;
    }
    if (parent != 0)
    {
        parent->keyPressEvent(event);
        if (!event->isAccepted())
        {
            if (event->modifiers() != Qt::ControlModifier)
            {
                switch (event->key())
                {
                    case Qt::Key_Return:
                        {
                            selectNextColumn();
                        }
                        break;
                    case Qt::Key_Enter:
                        {
                            selectNextColumn();
                        }
                        break;
                    case Qt::Key_Right:
                        {
                            selectNextColumn();
                        }
                        break;
                    case Qt::Key_Tab:
                        {
                            selectNextColumn();
                        }
                        break;
                    case Qt::Key_Backtab:
                        {
                            selectPreviousColumn();
                        }
                        break;
                    case Qt::Key_Left:
                        {
                            selectPreviousColumn();
                        }
                        break;
                    default:
                        QTableView::keyPressEvent(event);
                }
            }
            else
                QTableView::keyPressEvent(event);
        }
    }
    else
        QTableView::keyPressEvent(event);

}


void TableView::restoreCurrentIndex(QModelIndex index)
{
    if (index.row() == -1 && index.column() == -1)
    {
        index = tableModel->index(0, 0);
        setCurrentIndex(index);
        selectNextColumn();
    }
    else
        setCurrentIndex(index);
}


bool TableView::setColumnsHeaders()
{
    if (!columnsHeadersSeted)
    {
        if (parent != 0)
        {
            // Если заголовки столбцов еще не установлены
            QHeaderView* header = horizontalHeader();

#if QT_VERSION >= 0x050000
            header->setSectionsMovable(true);
#else
            header->setMovable(true);
#endif
            header->setSortIndicatorShown(true);
            db->getColumnsHeaders(essence->getTagName(), fields);
            if (fields->count() > 0)
            {

                // Сначала скроем все столбцы
                for (int i = 0; i < header->count(); i++)
                    header->hideSection(i);

                setColumnsDelegates();

                // Установим столбцы в соотвествующем порядке
                foreach (int i, columns.keys())
                {
                    int fldIndex = tableModel->fieldIndex(columns.value(i));
                    int visualIndex = header->visualIndex(fldIndex);
                    header->moveSection(visualIndex, i);
                    maxColumn = i;
                }
            }
            readSettings();
            columnsHeadersSeted = true;
        }
        return true;
    }
    return false;
}


void    TableView::setColumnsDelegates()
{
    QHeaderView* header = horizontalHeader();
    // Теперь покажем только те столбцы, у которых поле number в списке fields больше 0
    for (int i = 0; i < fields->count(); i++)
    {
        if (fields->at(i).number > 0)
        {
            MyItemDelegate* delegate = getColumnDelegate(fields->at(i));
            if (delegate != 0)
            {
                delegate->setFieldName(fields->at(i).column);
                if (!fields->at(i).readOnly)
                {
                    connect(delegate, SIGNAL(closeEditor(QWidget*)), this, SLOT(calculate()));
                }
                delegate->setReadOnly(fields->at(i).readOnly);
                setItemDelegateForColumn(i, delegate);
            }
            tableModel->setHeaderData(i, Qt::Horizontal, fields->at(i).header);
            columns.insert(fields->at(i).number - 1, fields->at(i).column);
            header->showSection(i);
        }
    }
}


void TableView::hideAllGridSections()
{
    setColumnsHeaders();

    foreach (int i, columns.keys())
    {
        horizontalHeader()->hideSection(horizontalHeader()->logicalIndex(i));
    }
}


void TableView::hideGridSection(QString columnName)
{
    setColumnsHeaders();

    foreach (int i, columns.keys())
    {
        if (columns.value(i) == columnName)
        {
            horizontalHeader()->hideSection(horizontalHeader()->logicalIndex(i));
            return;
        }
    }
}


void TableView::showGridSection(QString columnName)
{
    setColumnsHeaders();


    foreach (int i, columns.keys())
    {
        if (columns.value(i) == columnName)
        {
            horizontalHeader()->showSection(horizontalHeader()->logicalIndex(i));
            return;
        }
    }
}


void TableView::showAllGridSections()
{
    setColumnsHeaders();

    foreach (int i, columns.keys())
    {
        horizontalHeader()->showSection(horizontalHeader()->logicalIndex(i));
    }
}


MyItemDelegate* TableView::getColumnDelegate(FieldType fld)
{
    if (fld.type.toUpper() == "NUMERIC" ||
        fld.type.toUpper() == "INTEGER")
    {     // для числовых полей зададим свой самодельный делегат
        MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(this, parent, fld.length, fld.precision);
        return (MyItemDelegate*)numericDelegate;
    } else if (fld.type.toUpper() == "BOOLEAN")
           {
                MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(this, parent);
                return (MyItemDelegate*)booleanDelegate;
           } else
           {
                if (fld.type.toUpper() == "CHARACTER" ||
                    fld.type.toUpper() == "CHARACTER VARYING" ||
                    fld.type.toUpper() == "TEXT")
                {
                    MyLineItemDelegate* textDelegate = new MyLineItemDelegate(this, parent);
                    textDelegate->setMaxLength(fld.length);
                    return (MyItemDelegate*)textDelegate;
                }
                else
                {
                    if (fld.type.toUpper() == "DATE" ||
                        fld.type.toUpper().left(9) == "TIMESTAMP")
                    {
                        MyDateItemDelegate* dateDelegate = new MyDateItemDelegate(this, parent);
                        return (MyItemDelegate*)dateDelegate;
                    }
                }
           }
    return 0;
}


bool TableView::columnIsReadOnly()
{
    if (tableModel->rowCount() > 0)
    {
        QModelIndex index = currentIndex();
        if (index.row() == -1 && index.column() == -1)
            return true;
        int column = horizontalHeader()->visualIndex(index.column());
        int logicalIndex = horizontalHeader()->logicalIndex(column);
        if (!horizontalHeader()->isSectionHidden(logicalIndex))
        {
            MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(logicalIndex);
            if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
            {
                return false;
            }
        }
    }
    return true;
}


void TableView::selectNextColumn()
// Ищет следующую колонку для редактирования
{
    if (tableModel->rowCount() > 0)
    {
        QModelIndex index = currentIndex();
        if (!index.isValid())
            return;
        int column = horizontalHeader()->visualIndex(index.column());
        int oldColumn = column > 0 ? column : 0;
        int logicalIndex;
        QModelIndex newIndex;
        while (true)
        {
            column++;                       // Перейдем в следующий столбец
            logicalIndex = horizontalHeader()->logicalIndex(column);
            newIndex = index.sibling(index.row(), logicalIndex);
            if (!newIndex.isValid())
            {
                newIndex = index.sibling(index.row(), 0);
                if (!newIndex.isValid())
                {
                    setCurrentIndex(index);
                    break;
                }
                column = 0;
                logicalIndex = horizontalHeader()->logicalIndex(column);
            }

            if (!horizontalHeader()->isSectionHidden(logicalIndex))
            {
                MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(logicalIndex);
                if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
                {
                    setCurrentIndex(newIndex);
                    break;
                }
            }
            if (column == oldColumn)                            // Выход из бесконечного цикла в случае, если ни одного поля для редактирования не найдено
            {
                break;
            }
        }
    }
}


void TableView::selectPreviousColumn()
// Ищет предыдущую колонку для редактирования
{
    QModelIndex index = currentIndex();
    if (index.row() == -1 && index.column() == -1)
        return;
    int column = horizontalHeader()->visualIndex(index.column());
    int oldColumn = column > 0 ? column : 0;
    int logicalIndex;
    while (true)
    {
        column--;   // Перейдем в предыдущий столбец
        logicalIndex = horizontalHeader()->logicalIndex(column);
        QModelIndex newIndex = index.sibling(index.row(), logicalIndex);
        if (newIndex.row() == -1 && newIndex.column() == -1)
        {
            column = maxColumn;
            logicalIndex = horizontalHeader()->logicalIndex(column);
            newIndex = index.sibling(index.row(), logicalIndex);
            if (newIndex.row() == -1 && newIndex.column() == -1)
            {
                setCurrentIndex(index);
                break;
            }
        }
        if (!horizontalHeader()->isSectionHidden(logicalIndex))
        {
            setCurrentIndex(newIndex);
            MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(logicalIndex);
            if (delegate != 0 && !delegate->isReadOnly())    // Если эта колонка для редактирования
                break;
        }
        if (column == oldColumn)                            // Выход из бесконечного цикла в случае, если ни одного поля для редактирования не найдено
            break;
    }
}


void TableView::showPhoto()
{
    if (picture != 0 && essence != 0)
    {
        if (tableModel->rowCount() > 0)
        {
            QString photoFileName = essence->getPhotoFile(); // Получим имя фотографии
            if (photoFileName.size() > 0 && photoFileName.left(4) != "http")
            {   // Если локальный файл с фотографией существует и имя файла не является адресом в интернете (из интернета фотографию еще нужно скачать в локальный файл)
                if (QDir().exists(photoFileName))
                    picture->setVisibility(true);              // то включим просмотр фотографий
                else
                    photoFileName = "";
                if (essence->getPhotoNameField().size() > 0)
                    picture->setPhotoWindowTitle(essence->getValue(essence->getPhotoNameField()).toString().trimmed());
            }
            picture->show(photoFileName);
        }
    }
}


void TableView::calculate()
{
    setUpdatesEnabled(false);
    if (!essence->calculate())
        reset();
    else
        repaint();
    selectNextColumn();       // Передвинуть курсор на следующую колонку
    setUpdatesEnabled(true);
}


void TableView::setReadOnly(bool ro)
{
    if (parent != 0 && fields != 0)
    {
        db->getColumnsHeaders(essence->getTagName(), fields);
        for (int i = 0; i < fields->count(); i++)
        {
            MyItemDelegate* delegate = (MyItemDelegate*)itemDelegateForColumn(i);
            if (delegate != 0)
            {
                if (ro)
                    delegate->setReadOnly(ro);
                else
                    delegate->setReadOnly(fields->at(i).readOnly);
            }
        }
        repaint();
    }
}


void TableView::focusInEvent(QFocusEvent* event)
{
    QTableView::focusInEvent(event);
    if (columnIsReadOnly())
        selectNextColumn();
}


void TableView::readSettings()
// Считывает сохраненную информацию о ширине столбцов при открытии формы с таблицей
{
    QSettings settings;
    bool readedFromEnv = true;  // Предположим, что удастся прочитать конфигурацию из окружения
    parent->readSettings();

    if (settings.status() == QSettings::NoError)
    {
        settings.beginGroup(parent->getConfigName());
        int columnCount = settings.beginReadArray("grid");
        if (columnCount > 0)
        {
            for (int i = 0; i < columnCount; i++)
            {
                settings.setArrayIndex(i);
                int width = settings.value("width", 100).toInt();
                if (width == 0)
                    width = 100;
                setColumnWidth(i, width);
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
        QHash<QString, int> values;

        app->showMessageOnStatusBar(tr("Загрузка с сервера ширины столбцов справочника ") + parent->getConfigName() + "...");
        config = db->getConfig();
        config.first();
        while (config.isValid())
        {
            if (config.record().value("group").toString() == parent->getConfigName())
            {
                values.insert(config.record().value("name").toString(), config.record().value("value").toInt());
            }
            config.next();
        }
        int i = 0;
        while (true)
        {
            QString name = QString("grid/%1/width").arg(i);
            if (values.contains(name))
            {
                int width = values.value(name);
                setColumnWidth(i, width);
            }
            else
                break;
            i++;
        }
        app->showMessageOnStatusBar("");
    }
    columnsSettingsReaded = true;
}


void TableView::writeSettings()
{
    if (columnsSettingsReaded)
    {
        QSettings settings;
        int columnCount = tableModel->columnCount();
        if (columnCount > 0)
        {
            settings.beginGroup(parent->getConfigName());
            settings.beginWriteArray("grid", columnCount);
            for (int i = 0; i < columnCount; i++)
            {
                int width = columnWidth(i);
                settings.setArrayIndex(i);
                settings.setValue("width", width);
            }
            settings.endArray();
            settings.endGroup();

            // Если работает пользователь SA, то сохраним конфигурацию окна на сервере
            if (app->isSA() && app->getSaveFormConfigToDb())
            {
                app->showMessageOnStatusBar(tr("Сохранение на сервере ширины столбцов справочника ") + parent->getConfigName() + "...");
                for (int i = 0; i < columnCount; i++)
                {
                    int width = columnWidth(i);
                    if (width > 0)
                        db->setConfig(parent->getConfigName(), QString("grid/%1/width").arg(i), QString("%1").arg(width));
                }
                app->showMessageOnStatusBar("");
            }
        }
    }
}

