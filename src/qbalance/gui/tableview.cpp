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
#include <QtCore/QDebug>

#include <QtScript/QScriptContextInfo>
//#include <QtCore/QEvent>
#include <QtSql/QSqlRelationalTableModel>
#include "../kernel/app.h"
#include "tableview.h"
#include "formgrid.h"
#include "picture.h"
#include "../kernel/dictionary.h"
#include "../engine/scriptengine.h"
#include "../storage/dbfactory.h"
#include "mylineitemdelegate.h"
#include "mynumericitemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mydateitemdelegate.h"



TableView::TableView(): QTableView()
{
    app = 0 /*nullptr*/;
    parent = 0 /*nullptr*/;
    tableModel = 0 /*nullptr*/;
    essence = 0 /*nullptr*/;
    picture = 0 /*nullptr*/;
    fieldCounter = 0;
    hideZero = false;   // По умолчанию нулевые значения будем показывать
    readOnly = false;
}


TableView::~TableView()
{
    QItemSelectionModel *oldModel = selectionModel();
    delete oldModel;
}


void TableView::setFormGrid(FormGrid* par)
{
    parent = par;
    setPicture(parent->getPicture());
    configName = parent->getConfigName();
}


void TableView::setConfigName(QString config)
{
    configName = config;
}


void TableView::setPicture(Picture* pic)
{
    picture = pic;
}


void TableView::open()
{
    name = "tableView";
    columnsHeadersSeted = false;
    columns.clear();
    columnsSettingsReaded = false;
    currentChangedScripts = true;

    if (verticalHeader()->minimumSectionSize() > 0)
        verticalHeader()->setDefaultSectionSize(verticalHeader()->minimumSectionSize());

    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setObjectName(name);

#if QT_VERSION >= 0x050000
    horizontalHeader()->setSectionsClickable(false);
#else
    horizontalHeader()->setClickable(false);
#endif

    setSelectionBehavior(QAbstractItemView::SelectRows);
}


void TableView::close()
{
    if (essence->isMenuMode())
        disconnect(this, SIGNAL(doubleClicked(QModelIndex)), essence, SLOT(cmdOk()));

    disconnect(tableModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));
    disconnect(essence, SIGNAL(photoLoaded()), this, SLOT(showPhoto()));

    writeSettings();
}


void TableView::setEssence(Essence* ess)
{
    open();
    essence = ess;
    parent = essence->getForm();
    app = essence->getApp();
    columnsProperties = essence->getColumnsProperties();
    tableModel = essence->getTableModel();
    QTableView::setModel(tableModel);

    connect(essence, SIGNAL(photoLoaded()), this, SLOT(showPhoto()));
    connect(tableModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));

    if (essence->isMenuMode())
        connect(this, SIGNAL(doubleClicked(QModelIndex)), essence, SLOT(cmdOk()));

//    setReadOnly(essence->isReadOnly());
    setFormGrid(essence->getForm());
}


void TableView::cmdAdd()
{
    QModelIndex index = currentIndex();      // Запомним, где стоял курсор
    essence->add();
    setCurrentFocus();
    selectColumn(index.column());
}


void TableView::cmdDelete()
{
    QModelIndex index = currentIndex();      // Запомним, где стоял курсор перед удалением записи
    if (essence->remove())
    {
        int rowCount = tableModel->rowCount();
        if (rowCount > 0)
        {   // Если после удаления строки в таблице остались еще записи
            if (index.row() == rowCount)
                selectRow(rowCount - 1);
        }
    }
}


void TableView::setCurrentFocus()
{
    currentChangedScripts = false;
    QModelIndex index = currentIndex();      // Запомним, где стоял курсор
//    int column = index.column() < 0 ? 0 : index.column();
    int row = index.row() < 0 ? 0 : index.row();
    selectNextColumn();
    int column = currentIndex().column();
    reset();
    setCurrentIndex(index.sibling(row, column));
    currentChangedScripts = true;
}


void TableView::cmdView()
{
    if (picture != 0 /*nullptr*/)
        picture->hide();
    essence->view();
}


void TableView::cmdRequery()
{
    essence->query();
    setFocus();
}


void TableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() != previous.row())
    {
        if (essence != 0 /*nullptr*/)
            essence->beforeRowChanged();
    }

    QTableView::currentChanged(current, previous);

    if (current.row() != previous.row()/* && currentChangedScripts*/)
    {
        if (essence != 0 /*nullptr*/)
        {
            essence->afterRowChanged();
            if (essence->isPhotoEnabled())
                showPhoto();
        }
    }
}


void TableView::keyPressEvent(QKeyEvent* event)
{

    event->setAccepted(false);

    if (!event->isAccepted())
        app->readCardReader(event);

    if (parent != 0 /*nullptr*/ && !event->isAccepted())
    {
        if (event->modifiers() != Qt::ControlModifier)
        {
            switch (event->key())
            {
                case Qt::Key_Return:
                    {
                        if (essence->isMenuMode())
                            essence->cmdOk();
                        else
                            selectNextColumn();
                        event->setAccepted(true);
                    }
                    break;
                case Qt::Key_Enter:
                    {
                        selectNextColumn();
                        event->setAccepted(true);
                    }
                    break;
                case Qt::Key_Right:
                    {
                        selectNextColumn();
                        event->setAccepted(true);
                    }
                    break;
                case Qt::Key_Tab:
                    {
                        selectNextColumn();
                        event->setAccepted(true);
                    }
                    break;
                case Qt::Key_Backtab:
                    {
                        selectPreviousColumn();
                        event->setAccepted(true);
                    }
                    break;
                case Qt::Key_Left:
                    {
                        selectPreviousColumn();
                        event->setAccepted(true);
                    }
                    break;
            }
        }

        if (!event->isAccepted())
            parent->keyPressEvent(event);

    }
    if (!event->isAccepted())
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


void TableView::setColumnsHeaders()
{
    if (parent != 0 /*nullptr*/)
    {
        if (!columnsHeadersSeted)
        {
            app->getDBFactory()->getColumnsHeaders(essence->getTagName(), columnsProperties);
            if (columnsProperties->count() > 0)
            {
                QHeaderView* header = horizontalHeader();

#if QT_VERSION >= 0x050000
                header->setSectionsMovable(true);
#else
                header->setMovable(true);
#endif

                header->setSortIndicatorShown(true);

                // Составим список столбцов, у которых поле number в списке fields больше 0
                for (int i = 0; i < columnsProperties->count(); i++)
                {
                    if (columnsProperties->at(i).number > 0)
                    {
                        MyItemDelegate* delegate = getColumnDelegate(columnsProperties->at(i));
                        if (delegate != 0 /*nullptr*/)
                        {
                            delegate->setFieldName(columnsProperties->at(i).column);
                            setItemDelegateForColumn(i, delegate);
                        }
                        columns.insert(columnsProperties->at(i).number - 1, i);
                        fieldCounter++;
                    }
                }

                // Сделаем столбцы из этого списка первыми
                int i;
                for (i = 0;; i++)
                {
                    if (columns.contains(i))
                    {
                        int fldIndex = tableModel->fieldIndex(columnsProperties->at(columns.value(i)).column);
                        int visualIndex = header->visualIndex(fldIndex);
                        header->moveSection(visualIndex, i);
                        header->showSection(visualIndex);
                        tableModel->setHeaderData(fldIndex, Qt::Horizontal, columnsProperties->at(columns.value(i)).header);
                    }
                    else
                        break;
                }

                // Остальные столбцы скроем
                for (; i < header->count(); i++)
                {
                    header->hideSection(header->logicalIndex(i));
                }

                // Найдем индекс крайнего справа столбца
                for (i = 0;; i++)
                {
                    if (horizontalHeader()->logicalIndex(i) < 0)
                        break;
                    maxColumn = i;
                }

                setReadOnly(readOnly);
            }
            readSettings();

            columnsHeadersSeted = true;
        }
    }
}


void TableView::hideAllGridSections()
{
    foreach (int i, columns.keys())
    {
        horizontalHeader()->hideSection(horizontalHeader()->logicalIndex(i));
    }
}


void TableView::hideGridSection(QString columnName)
{
    foreach (int i, columns.keys())
    {
        if (columnsProperties->at(columns.value(i)).column == columnName)
        {
            horizontalHeader()->hideSection(horizontalHeader()->logicalIndex(i));
            return;
        }
    }
}


void TableView::showGridSection(QString columnName)
{
    foreach (int i, columns.keys())
    {
        if (columnsProperties->at(columns.value(i)).column == columnName)
        {
            horizontalHeader()->showSection(horizontalHeader()->logicalIndex(i));
            return;
        }
    }
}


void TableView::showAllGridSections()
{
    foreach (int i, columns.keys())
    {
        horizontalHeader()->showSection(horizontalHeader()->logicalIndex(i));
    }
}


MyItemDelegate* TableView::getColumnDelegate(FieldType fld)
{
    MyItemDelegate* result = 0 /*nullptr*/;
    if (fld.type.toUpper() == "NUMERIC" || fld.type.toUpper() == "INTEGER")
    {     // для числовых полей зададим свой самодельный делегат
        MyNumericItemDelegate* numericDelegate = new MyNumericItemDelegate(this, parent, fld.length, fld.precision);
        numericDelegate->setHideZero(hideZero);
        result = static_cast<MyItemDelegate*>(numericDelegate);
    } else if (fld.type.toUpper() == "BOOLEAN")
    {
        MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(this, parent);
        result = static_cast<MyItemDelegate*>(booleanDelegate);
    } else
    {
        if (fld.type.toUpper() == "CHARACTER" || fld.type.toUpper() == "CHARACTER VARYING" || fld.type.toUpper() == "TEXT")
        {
            MyLineItemDelegate* textDelegate = new MyLineItemDelegate(this, parent);
            textDelegate->setMaxLength(fld.length);
            result = static_cast<MyItemDelegate*>(textDelegate);
        }
        else
        {
            if (fld.type.toUpper() == "DATE" || fld.type.toUpper().left(9) == "TIMESTAMP")
            {
                MyDateItemDelegate* dateDelegate = new MyDateItemDelegate(this, parent);
                result = static_cast<MyItemDelegate*>(dateDelegate);
            }
        }
    }

    return result;
}


bool TableView::columnIsReadOnly()
{
    if (tableModel != 0 /*nullptr*/ && tableModel->rowCount() > 0)
    {
        QModelIndex index = currentIndex();
        if (!index.isValid())
            return true;
        int column = horizontalHeader()->visualIndex(index.column());
        int logicalIndex = horizontalHeader()->logicalIndex(column);
        if (!horizontalHeader()->isSectionHidden(logicalIndex))
        {
            MyItemDelegate* delegate = static_cast<MyItemDelegate*>(itemDelegateForColumn(logicalIndex));
            if (delegate != 0 /*nullptr*/ && !delegate->isReadOnly())    // Если эта колонка для редактирования
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
    if (tableModel != 0 /*nullptr*/ && tableModel->rowCount() > 0)
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
            if (column < 0)
                column = 0;
            else
                column++;                       // Перейдем в следующий столбец
            logicalIndex = horizontalHeader()->logicalIndex(column);
            newIndex = index.sibling(index.row(), logicalIndex);
            if (!newIndex.isValid())
            {
                newIndex = index.sibling(index.row(), 0);
                if (!newIndex.isValid())
                {
                    setCurrentIndex(index);
                }
                column = -1;
            }

            if (!horizontalHeader()->isSectionHidden(logicalIndex))
            {
                MyItemDelegate* delegate = static_cast<MyItemDelegate*>(itemDelegateForColumn(logicalIndex));
                if (delegate != 0 /*nullptr*/ && !delegate->isReadOnly())    // Если эта колонка для редактирования
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
    if (!index.isValid())
        return;
    int column = horizontalHeader()->visualIndex(index.column());
    int oldColumn = column > 0 ? column : 0;
    int logicalIndex;
    while (true)
    {
        if (column > 0)
            column--;   // Перейдем в предыдущий столбец
        else
            column = maxColumn;
        logicalIndex = horizontalHeader()->logicalIndex(column);
        QModelIndex newIndex = index.sibling(index.row(), logicalIndex);
        if (!newIndex.isValid())
        {
            newIndex = index.sibling(index.row(), column);
            if (!newIndex.isValid())
            {
                setCurrentIndex(index);
                break;
            }
            logicalIndex = horizontalHeader()->logicalIndex(column);
        }
        if (!horizontalHeader()->isSectionHidden(logicalIndex))
        {
            setCurrentIndex(newIndex);
            MyItemDelegate* delegate = static_cast<MyItemDelegate*>(itemDelegateForColumn(logicalIndex));
            if (delegate != 0 /*nullptr*/ && !delegate->isReadOnly())    // Если эта колонка для редактирования
                break;
        }
        if (column == oldColumn)                            // Выход из бесконечного цикла в случае, если ни одного поля для редактирования не найдено
            break;
    }
}


void TableView::showPhoto()
{
    QString photoFileName = "";
    if (picture != 0 /*nullptr*/ && essence != 0 /*nullptr*/)
    {
        if (tableModel->rowCount() > 0)
        {
            photoFileName = essence->getPhotoFile(); // Получим имя фотографии
            if (photoFileName.size() > 0 && photoFileName.left(4) != "http")
            {   // Если локальный файл с фотографией существует и имя файла не является адресом в интернете (из интернета фотографию еще нужно скачать в локальный файл)
                if (QDir().exists(photoFileName))
                    picture->setVisibility(true);              // то включим просмотр фотографий
                if (essence->getPhotoNameField().size() > 0)
                    picture->setPhotoWindowTitle(essence->getValue(essence->getPhotoNameField()).toString().trimmed());
            }
        }
        picture->show(photoFileName);
    }
}


void TableView::setReadOnly(bool ro)
{
    readOnly = ro;

    for (int i = 0; i < columnsProperties->count(); i++)
    {
        MyItemDelegate* itemDelegate = static_cast<MyItemDelegate*>(itemDelegateForColumn(i));
        if (itemDelegate != 0 /*nullptr*/)
            itemDelegate->setReadOnly(readOnly || columnsProperties->at(i).readOnly);
    }
}


bool TableView::isReadOnly()
{
    return readOnly;
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
    QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
    bool readedFromEnv = true;  // Предположим, что удастся прочитать конфигурацию из окружения

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
        // Если информация о ширине столбца отсутствует в окружении программы, попытаемся прочитать ее из базы
        QHash<QString, int> values;
        app->getDBFactory()->getConfig(configName, &values);
        for (int i = 0; i < values.count(); i++)
        {
            int width = values.value(QString("grid/%1/width").arg(i));
            setColumnWidth(i, width);
        }
        app->showMessageOnStatusBar("");
    }
    columnsSettingsReaded = true;
}


void TableView::writeSettings()
{
    if (columnsSettingsReaded)
    {
        QSettings settings(app->getConfigFileName(), QSettings::IniFormat);
        int columnCount = tableModel->columnCount();
        if (columnCount > 0)
        {
            settings.beginGroup(configName);

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
            if (app->isSA() && app->getConfigValue("SAVE_FORM_CONFIG_TO_DB").toBool())
            {
                app->showMessageOnStatusBar(tr("Сохранение на сервере ширины столбцов справочника ") + configName + "...");
                for (int i = 0; i < columnCount; i++)
                {
                    int width = columnWidth(i);
                    app->getDBFactory()->setConfig(configName, QString("grid/%1/width").arg(i), QString("%1").arg(width));
                }
                app->showMessageOnStatusBar("");
            }
        }
    }
}


void TableView::appendColumnDefinition(int, QString column, QString header, bool readOnly, int length, int precision)
{
    for (int i = 0; i < columnsProperties->count(); i++)
    {
        if (columnsProperties->at(i).table.toUpper() == parent->getParent()->getQueryTableName().toUpper() &&
            columnsProperties->at(i).column.toUpper() == column.toUpper()    )
        {
            fieldCounter++;
            FieldType field = columnsProperties->at(i);
            field.number = fieldCounter;
            field.header = header;
            field.readOnly = readOnly;
            if (length > 0)
                field.length = length;
            if (precision > 0)
                field.precision = precision;
            columnsProperties->removeAt(i);
            columnsProperties->insert(i, field);
            columnsHeadersSeted = false;
            break;
        }
    }
}


void TableView::appendColumnDefinition(QString column, QString header, bool readOnly, int length, int precision)
{
    appendColumnDefinition(0, column, header, readOnly, length, precision);
}


void TableView::clearColumnDefinitions()
{
    for (int i = 0; i < columnsProperties->count(); i++)
    {
        FieldType field = columnsProperties->at(i);
        field.number = 0;
        field.header = "";
        field.readOnly = false;
        columnsProperties->removeAt(i);
        columnsProperties->insert(i, field);
    }
    fieldCounter = 0;
    columnsHeadersSeted = false;
}


int TableView::getColumnsCount()
{
    return columnsProperties->count();
}


void TableView::setCurrentChangedScripts(bool c)
{
    currentChangedScripts = c;
}


void TableView::setApp(TApplication* a)
{
    app = a;
}


void TableView::setHideZero(bool hide)
{
    hideZero = hide;
}
