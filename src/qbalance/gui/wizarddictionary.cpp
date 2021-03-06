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
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include "wizarddictionary.h"
#include "../kernel/app.h"
#include "mybuttonlineedit.h"
#include "mybuttonlineedititemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mylineitemdelegate.h"
#include "formgridsearch.h"
#include "dialog.h"
#include "mysyntaxhighlighter.h"
#include "guifactory.h"
#include "../kernel/dictionaries.h"
#include "../kernel/saldo.h"
#include "../definitions.h"
#include "../engine/documentscriptengine.h"
#include "../storage/dbfactory.h"


enum dictFieldsEnums {tableField = 0,
                      columnField = 1,
                      typeField = 2,
                      lengthField = 3,
                      precisionField = 4,
                      headerField = 5,
                      visibleField = 6,
                      editableField = 7};


WizardDictionary* WizardDictionary::Exemplar   = 0 /*nullptr*/;


QString showTypesForm()
{
    FormGrid* typeForm = TApplication::exemplar()->getDictionaries()->getDictionary(TApplication::exemplar()->getDBFactory()->getObjectName("vw_types"))->getForm();
    typeForm->exec();
    if (typeForm->isFormSelected())
    {
        int length = typeForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("vw_types.длина")).toInt();
        QTableWidgetItem* item = WizardDictionary::exemplar()->fieldsTable.item(WizardDictionary::exemplar()->fieldsTable.currentRow(), 2);
        Qt::ItemFlags flags = item->flags();
        if (length < 0)
        {
            flags |= Qt::ItemIsSelectable;
            flags |= Qt::ItemIsEnabled;
        }
        else
        {
            flags &= (~Qt::ItemIsSelectable);
            flags &= (~Qt::ItemIsEnabled);
        }
        item->setFlags(flags);
        item->setText("");
        return typeForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("vw_types.тип")).toString();
    }
    return "";
}


WizardDictionary::WizardDictionary(bool addDict): WizardForm()
{
    tableName = 0 /*nullptr*/;
    tableMenuName = 0 /*nullptr*/;
    addDictionary = addDict;
    tableName = new QLineEdit();
    tableMenuName = new QLineEdit();
    tableFormName = new QLineEdit();
    chbMenu = new QCheckBox(formWidget);
    columnsRecordsExists = true;
    headers = new QListWidget(formWidget);
    if (!Exemplar)
    {
        Exemplar = this;
    }
}


WizardDictionary::~WizardDictionary()
{
}

WizardDictionary* WizardDictionary::exemplar()
{
    return Exemplar;
}


bool WizardDictionary::open(QWidget* pwgt, QString t/* = ""*/)
{
    table = t;
    return WizardForm::open(pwgt);
}


void WizardDictionary::initFrames()
{
    // Добавим страницы мастера
    QVBoxLayout* layout = new QVBoxLayout();
    // 1-я страница
    QGridLayout* gridLayout = new QGridLayout();
    QLabel* lblTableName = new QLabel(QObject::trUtf8("Наименование на сервере:"), formWidget);
    gridLayout->addWidget(lblTableName, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(tableName, 0, 1);

    QLabel* lblFormTableName = new QLabel(QObject::trUtf8("Наименование в форме:"), formWidget);
    gridLayout->addWidget(lblFormTableName, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(tableFormName, 1, 1);

    QLabel* lblMenuTableName = new QLabel(QObject::trUtf8("Наименование в меню:"), formWidget);
    gridLayout->addWidget(lblMenuTableName, 2, 0, Qt::AlignRight);
    gridLayout->addWidget(tableMenuName, 2, 1);

    QLabel* lblMenu = new QLabel(QObject::trUtf8("Доступен в меню:"), formWidget);
    gridLayout->addWidget(lblMenu, 3, 0, Qt::AlignRight);
    gridLayout->addWidget(chbMenu, 3, 1);
    gridLayout->setColumnStretch(1, 1);

    layout->addLayout(gridLayout);
    layout->addStretch();
    addFrame(layout, QObject::trUtf8("Наименование справочника"));

    // 2-я страница
    layout = new QVBoxLayout();
    // Добавим таблицу столбцов
    layout->addWidget(&fieldsTable);
    // Создадим кнопку "Добавить" столбец
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* button;
    button = new QPushButton(QObject::trUtf8("&Добавить"));
    button->setObjectName("buttonAdd");
    connect(button, SIGNAL(clicked()), this, SLOT(addColumn()));
    buttonLayout->addWidget(button);
    // Создадим кнопку "Удалить" столбец
    button = new QPushButton(QObject::trUtf8("&Удалить"));
    button->setObjectName("buttonDelete");
    connect(button, SIGNAL(clicked()), this, SLOT(deleteColumn()));
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();
    // Добавим кнопки на форму
    layout->addLayout(buttonLayout);
    addFrame(layout, QObject::trUtf8("Список столбцов"));

    // 3-я страница
    layout = new QVBoxLayout();
    QVBoxLayout* buttonLayout1 = new QVBoxLayout();
    button = new QPushButton();
    button->setObjectName("buttonUp");
    connect(button, SIGNAL(clicked()), this, SLOT(headerUp()));
    buttonLayout1->addWidget(button);
    button = new QPushButton();
    button->setObjectName("buttonDown");
    connect(button, SIGNAL(clicked()), this, SLOT(headerDown()));
    buttonLayout1->addWidget(button);
    QHBoxLayout* layout1 = new QHBoxLayout();
    layout1->addWidget(headers);
    layout1->addLayout(buttonLayout1);
    layout->addLayout(layout1);
    addFrame(layout, QObject::trUtf8("Порядок столбцов"));

    // 4-я страница
    layout = new QVBoxLayout();
    layout->addWidget(textEditor);
    addFrame(layout, QObject::trUtf8("Скрипты"));
}


void WizardDictionary::getData()
{
    if (table.size() == 0)
    {   // Если имя справочника не задано, т.е. это может быть новый справочник
        // то создадим новый справочник с именем <справочник<n>>
        for (int i = 1; true; i++)
        {
            table = QString("справочник%1").arg(i);
            if (!db->isTableExists(table))
            {
                break;
            }
        }
        QString menuName = table;
        menuName.replace(0, 1, menuName.left(1).toUpper());   // Первую букву названия справочника переведем в верхний регистр
        tableMenuName->setText(menuName);
        tableFormName->setText(menuName);
        tableName->setEnabled(true);
        chbMenu->setCheckState(Qt::Checked);

        // Создадим первых два поля справочника - "код" и "имя"
        FieldType field;
        field.table = table;
        field.name = "КОД";
        field.column = field.name;
        field.type = "int4";
        field.length = 0;
        field.precision = 0;
        field.header = "Код";
        field.number = 1;
        field.readOnly = true;
        fields.append(field);

        field.table = table;
        field.name = "ИМЯ";
        field.column = field.name;
        field.type = "character varying";
        field.length = 100;
        field.precision = 0;
        field.header = "Наименование";
        field.number = 2;
        field.readOnly = false;
        fields.append(field);
    }
    else
    {
        // Получим список полей таблицы
        db->getColumnsProperties(&fields, table);
        if (fields.count() == 0)
        {
            if (table.left(5).toLower() == "saldo")
            {
                QString acc = table;
                acc.replace("saldo", "");
                if (app->getDictionaries()->addSaldo(acc))
                {
                    fields.append(*app->getDictionaries()->getSaldo(acc)->getColumnsProperties());
                }
            }
        }
        // Прочитаем данные о заголовках столбцов
        db->getColumnsHeaders(table, &fields);

        QSqlRecord dictProperties = db->getDictionariesProperties(table);
        tableName->setText(dictProperties.value(db->getObjectName("справочники.имя")).toString().trimmed());
        tableMenuName->setText(dictProperties.value(db->getObjectName("справочники.имя_в_списке")).toString().trimmed());
        tableFormName->setText(dictProperties.value(db->getObjectName("справочники.имя_в_форме")).toString().trimmed());
        if (dictProperties.value(db->getObjectName("доступ_к_справочникам.меню")).toBool())
            chbMenu->setCheckState(Qt::Checked);
        else
            chbMenu->setCheckState(Qt::Unchecked);
        tableName->setEnabled(false);
    }
    // Запишем порядок вывода столбцов
    for (int i = 0; i < fields.count(); i++)
        columnsOrder.insert(fields.at(i).table + "__" + fields.at(i).name, fields.at(i).number);

    fieldsTable.setRowCount(fields.count());
    fieldsTable.setColumnCount(8);
    if (fieldsTable.verticalHeader()->minimumSectionSize() > 0)
        fieldsTable.verticalHeader()->setDefaultSectionSize(fieldsTable.verticalHeader()->minimumSectionSize());

    // Если известно, с какой таблицей будем работать
    tableName->setText(table);
    // Создадим таблицу столбцов
    fieldsTable.setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Таблица")
                                                         << QObject::trUtf8("Столбец")
                                                         << QObject::trUtf8("Тип")
                                                         << QObject::trUtf8("Длина")
                                                         << QObject::trUtf8("Точность")
                                                         << QObject::trUtf8("Заголовок")
                                                         << QObject::trUtf8("Видимость")
                                                         << QObject::trUtf8("Не изменять"));
    QString idField = "__" + db->getObjectName("код");
    for (int i = 0; i < fields.count(); i++)
    {
        QTableWidgetItem* tableItem = new QTableWidgetItem(fields.value(i).table);
        QTableWidgetItem* columnItem = new QTableWidgetItem(fields.value(i).name);
        QTableWidgetItem* typeItem = new QTableWidgetItem(fields.value(i).type);
        QTableWidgetItem* lengthItem = new QTableWidgetItem(QString("%1").arg(fields.value(i).length));
        QTableWidgetItem* precisionItem = new QTableWidgetItem(QString("%1").arg(fields.value(i).precision));
        QTableWidgetItem* headerItem = new QTableWidgetItem(fields.value(i).header);
        QTableWidgetItem* visibleItem = new QTableWidgetItem(fields.value(i).number > 0 ? "true" : "false");
        QTableWidgetItem* editableItem = new QTableWidgetItem(fields.value(i).readOnly ? "true" : "false");

        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        if (QString::compare(fields.value(i).table, tableName->text()) != 0)
        {
            columnItem->setFlags(columnItem->flags() & ~Qt::ItemIsEditable);
            typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
            lengthItem->setFlags(lengthItem->flags() & ~Qt::ItemIsEditable);
            precisionItem->setFlags(precisionItem->flags() & ~Qt::ItemIsEditable);
        }
        if (fields.value(i).column == fields.value(i).table + idField)
        {
            tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
            columnItem->setFlags(columnItem->flags() & ~Qt::ItemIsEditable);
            typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
            lengthItem->setFlags(lengthItem->flags() & ~Qt::ItemIsEditable);
            precisionItem->setFlags(precisionItem->flags() & ~Qt::ItemIsEditable);
            headerItem->setFlags(headerItem->flags() & ~Qt::ItemIsEditable);
            visibleItem->setFlags(visibleItem->flags() & ~Qt::ItemIsEditable);
            visibleItem->setText("false");
            editableItem->setFlags(editableItem->flags() & ~Qt::ItemIsEditable);
//            editableItem->setText("false");
        }
        fieldsTable.setItem(i, tableField, tableItem);
        fieldsTable.setItem(i, columnField, columnItem);
        fieldsTable.setItem(i, typeField, typeItem);
        fieldsTable.setItem(i, lengthField, lengthItem);
        fieldsTable.setItem(i, precisionField, precisionItem);
        fieldsTable.setItem(i, headerField, headerItem);
        fieldsTable.setItem(i, visibleField, visibleItem);
        fieldsTable.setItem(i, editableField, editableItem);
    }

    MyButtonLineEditItemDelegate* buttonEditDelegate = new MyButtonLineEditItemDelegate(getFormWidget());
    fieldsTable.setItemDelegateForColumn(typeField, buttonEditDelegate);
    buttonEditDelegate->setFormOnPushButton(&showTypesForm);
    MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(getFormWidget());
    fieldsTable.setItemDelegateForColumn(visibleField, booleanDelegate);
    MyBooleanItemDelegate* booleanDelegate1 = new MyBooleanItemDelegate(getFormWidget());
    fieldsTable.setItemDelegateForColumn(editableField, booleanDelegate1);

    // Инициализируем текстовый редактор
    textEditor = new QTextEdit(formWidget);
    highlighter = new MySyntaxHighlighter(textEditor->document());
    QString scripts = QString(db->getFile(table + ".qs", ScriptFileType));
    if (scripts.size() == 0)
    {
        DocumentScriptEngine engine;
        scripts = engine.getBlankScripts();
    }
    textEditor->setText(scripts);
}


bool WizardDictionary::setData()
{   // Сохранение данных на сервере
    tableName->setText(tableName->text().trimmed());
    tableMenuName->setText(tableMenuName->text().trimmed());
    db->beginTransaction();
    if (addDictionary)
    {   // Если нужно, то создадим новый справочник
        if (!db->createNewDictionary(tableName->text(), tableMenuName->text(), chbMenu->isChecked()))
        {
            db->rollbackTransaction();
            return false;
        }
    }
    // Получим код справочника, с которым работаем
    int mainTableId = db->getDictionaryId(tableName->text());
    if (mainTableId > 0) {
        // Установим пользовательские наименования справочника
        if (!db->setTableGuiName(tableName->text(), tableMenuName->text(), tableFormName->text()))
        {
           db->rollbackTransaction();
           return false;
        }
        // Удалим поля, помеченные к удалению
        int i = 0;
        while (i < fields.count())
        {
            if (fields.value(i).type.size() == 0 && oldColumnsList.contains(fields.at(i).table + "__" + fields.at(i).column))
            {
                if (!db->dropTableColumn(tableName->text(), fields.value(i).name))
                {
                        db->rollbackTransaction();
                        return false;
                }
                fields.removeAt(i);
            }
            else
                i++;
        }
        // Прошерстим список полей, сравним с исходным. Если что изменялось, то меняем и в БД
        db->removeColumnHeaders(mainTableId);
        for (int i = 0; i < fieldsTable.rowCount(); i++)
        {
            QString tName = fieldsTable.item(i, tableField)->text().trimmed();
            QString fieldName = fieldsTable.item(i, columnField)->text().trimmed().toUpper();
            QString sType = fieldsTable.item(i, typeField)->text();
            int nLength = fieldsTable.item(i, lengthField)->text().toInt();
            int nPrecision = fieldsTable.item(i, precisionField)->text().toInt();
            QString sHeader = fieldsTable.item(i, headerField)->text().trimmed();
            QString length, precision;
            if (nPrecision > 0)          // Если указана точность
                precision = QString(", %1").arg(nPrecision);
            if (nLength > 0)           // Если указана длина
                length = QString("(%1%2)").arg(nLength).arg(precision);
            QString type = fieldsTable.item(i, typeField)->text().trimmed();
            type = QString("%1%2").arg(type).arg(length);

            // Если мы работаем со старыми полями, т.е. теми, которые уже были в таблице
            if (oldColumnsList.contains(tName + "__" + fieldName))
            {   // Если мы просматриваем поля таблицы, которые уже были
                if (QString::compare(fieldName, fields.value(i).name) != 0)
                {   // Если пользователь изменил наименование поля
                    if (!db->renameTableColumn(tableName->text(), fields.value(i).name, fieldName))
                    {
                        db->rollbackTransaction();
                        return false;
                    }
                }
                if (QString::compare(sType, fields.value(i).type, Qt::CaseInsensitive) != 0 ||
                    nLength != fields.value(i).length ||
                    nPrecision != fields.value(i).precision)
                {   // Если изменились тип, длина или точность
                    if (!db->alterTableColumn(tableName->text(), fieldName, type))
                    {
                        db->rollbackTransaction();
                        return false;
                    }
                }
                if (fields.value(i).number > 0)
                {
                    int tableId = tableName->text() == fields.value(i).table ?  mainTableId : db->getDictionaryId(fields.value(i).table);
                    if (!db->appendColumnHeader(mainTableId,
                                                tableId,
                                                fields.value(i).column,
                                                sHeader,
                                                fields.value(i).number,
                                                fields.value(i).readOnly))
                    {
                        db->rollbackTransaction();
                        return false;
                    }
                }
            }
            else
            {   // Если мы добавляем новые поля
                if (fields.at(i).table == tableName->text() && type.size() > 0)
                {
                    if (!db->addTableColumn(tableName->text(), fieldName, type))
                    {
                        db->rollbackTransaction();
                        return false;
                    }
                }
                if (sHeader.size() > 0)
                {
                    if (!db->appendColumnHeader(mainTableId, mainTableId, fieldName, sHeader, fields.value(i).number + 1, fields.value(i).readOnly))
                    {
                        db->rollbackTransaction();
                        return false;
                    }
                }
            }
        }
    }
    // Сохраним скрипты
    QString scriptFile = table + ".qs";
    ScriptEngine::removeScript(scriptFile);
    db->setFile(scriptFile, ScriptFileType, QByteArray().append(textEditor->toPlainText()));
    db->commitTransaction();
    db->clearUpdateNum();   // Очистим нумерацию, чтобы информация об обновлениях скидывалась в новый файл

    if (app->getDictionaries()->getDictionariesList()->contains(table))
        app->getDictionaries()->removeDictionary(table);

    // Перезагрузим список столбцов
    db->reloadDictionariesPermitions();

    return true;
}


void WizardDictionary::addColumn()
{
    fieldsTable.setRowCount(fieldsTable.rowCount() + 1);
    for (int i = 0; i < fieldsTable.columnCount(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("");
        fieldsTable.setItem(fieldsTable.rowCount() - 1, i, item);
    }
    fieldsTable.setCurrentCell(fieldsTable.rowCount() - 1, 1);
    fieldsTable.setFocus(Qt::OtherFocusReason);
    fieldsTable.item(fieldsTable.currentRow(), 0)->setText(table);
}


void WizardDictionary::deleteColumn()
{
    QString tableName = fieldsTable.item(fieldsTable.currentRow(), tableField)->text().trimmed();
    QString fieldName = fieldsTable.item(fieldsTable.currentRow(), columnField)->text().trimmed().toUpper();
    if (fieldName != "КОД")
    {
        if (app->showYesNo(QObject::trUtf8("Удалить столбец? Вы уверены?")) == QMessageBox::Yes)
        {
            fieldsTable.removeRow(fieldsTable.currentRow());
            for (int i = 0; i < fields.count(); i++)
            {
                if (fields.value(i).table == tableName && fields.value(i).column == fieldName)
                {
                    FieldType fld;
                    fld = fields.value(i);
                    fld.type = "";
                    fields.removeAt(i);
                    fields.insert(i, fld);
                }
            }
            if (fieldName.left(4) == "КОД_")
            {
                tableName = fieldName.remove("КОД_", Qt::CaseInsensitive).toLower();
                for (int i = fieldsTable.rowCount() - 1; i >= 0 ; i--)
                {
                    if (fieldsTable.item(i, tableField)->text().trimmed() == tableName)
                    {
                        fieldsTable.removeRow(i);
                        for (int i = 0; i < fields.count(); i++)
                        {
                            if (fields.value(i).table == tableName)
                            {
                                FieldType fld;
                                fld = fields.value(i);
                                fld.type = "";
                                fields.removeAt(i);
                                fields.insert(i, fld);
                            }
                        }
                    }
                }
            }
            fieldsTable.setFocus(Qt::OtherFocusReason);
            saveOrder();
        }
    }
}


void WizardDictionary::headerUp()
{
    headers->setFocus(Qt::OtherFocusReason);
    int currentRow = headers->currentRow();
    if (currentRow > 0)
    {
        QListWidgetItem* item = headers->takeItem(currentRow);
        headers->insertItem(currentRow - 1, item);
        headers->setCurrentRow(currentRow - 1);
    }
}


void WizardDictionary::headerDown()
{
    headers->setFocus(Qt::OtherFocusReason);
    int currentRow = headers->currentRow();
    if (currentRow < headers->count() - 1)
    {
        QListWidgetItem* item = headers->takeItem(currentRow);
        headers->insertItem(currentRow + 1, item);
        headers->setCurrentRow(currentRow + 1);
    }
}


void WizardDictionary::fieldNameChanged()
{

}


void WizardDictionary::frameActivated(int frameNumber)
{
    if (frameNumber == 1)
    {
        oldColumnsList.clear();
        for (int i = 0; i < fields.count(); i++)
        {
            oldColumnsList.append(fields.at(i).table + "__" + fields.at(i).name.toUpper());
        }
    }
    if (frameNumber == 2)
    {   // Если активизирован фрейм списка заголовков
        headers->clear();
        for (int i = 0; i < fieldsTable.rowCount(); i++)
        {
            for (int j = 0; j < fieldsTable.rowCount(); j++)
            {
                if (fieldsTable.item(j, visibleField)->text() == "true")
                {
                    QString columnName = fieldsTable.item(j, tableField)->text() + "__" + fieldsTable.item(j, columnField)->text().toUpper();
                    int number;
                    if (j + 1 > fields.count())
                    {           // Для новых полей
                        number = fieldsTable.rowCount();    // Поля будут идти последними в списке полей
                    }
                    else
                        number = (fields.at(j).number == 0 ? fields.count() : fields.at(j).number);
                    if (number == i + 1)
                    {
                        QListWidgetItem* item = new QListWidgetItem(fieldsTable.item(j, headerField)->text(), headers);
                        item->setData(Qt::UserRole, QVariant(columnName));
                        headers->addItem(item);
                    }
                }
            }
        }
    }
}


void WizardDictionary::frameDeactivated(int frameNumber)
{
    if (frameNumber == 0)
    {
        if (table != tableName->text())
        {
            QString oldTable = table;
            table = tableName->text();
            for (int i = 0; i < fieldsTable.rowCount(); i++)
            {
                fieldsTable.item(i, tableField)->setText(table);
            }
            for (int i = 0; i < fields.count(); i++)
            {
                if (fields.value(i).table == oldTable)
                {
                    FieldType fld;
                    fld = fields.value(i);
                    fld.table = table;
                    fields.removeAt(i);
                    fields.insert(i, fld);
                }
            }
        }
    }
    if (frameNumber == 1)
    {
        saveFields();
    }
    if (frameNumber == 2)
    {   // Если был закрыт фрейм со списком порядка столбцов
        // Сохраним порядок расположения столбцов
        saveOrder();
        saveFields();
    }
}


void WizardDictionary::saveFields()
{
    fields.clear();
    for (int i = 0; i < fieldsTable.rowCount(); i++)
    {
        FieldType field;
        field.table = fieldsTable.item(i, tableField)->text();
        field.name = fieldsTable.item(i, columnField)->text().toUpper();
        field.column = field.name;
        field.type = fieldsTable.item(i, typeField)->text();
        field.length = fieldsTable.item(i, lengthField)->text().toInt();
        field.precision = fieldsTable.item(i, precisionField)->text().toInt();
        field.header = fieldsTable.item(i, headerField)->text();
        field.number = columnsOrder.value(field.table + "__" + field.name);
        field.readOnly = fieldsTable.item(i, editableField)->text() == "true" ? true : false;
        fields.append(field);
    }
}


void WizardDictionary::saveOrder()
{
    if (headers->count() > 0)
    {
        columnsOrder.clear();
        for (int i = 0; i < headers->count(); i++)
        {
            QString column = headers->item(i)->data(Qt::UserRole).toString();
            columnsOrder.insert(column, i + 1);
        }
        for (int j = 0; j < fields.count(); j++)
        {
            FieldType field = fields.at(j);
            QString column = QString(field.table + "__" + field.name.toUpper());
            if (columnsOrder.contains(column))
                field.number = columnsOrder.value(column);
            else
                field.number = 0;
            fields.removeAt(j);
            fields.insert(j, field);
        }
    }
}
