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

#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include "wizardoperation.h"
#include "mybuttonlineedititemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "formgridsearch.h"
#include "mybuttonlineedit.h"
#include "dialog.h"
#include "mysyntaxhighlighter.h"
#include "../kernel/app.h"
#include "../kernel/dictionaries.h"
#include "../kernel/documents.h"
#include "../storage/dbfactory.h"
#include "../engine/documentscriptengine.h"


enum fieldsEnums {debetField = 0,
             dbConstField = 1,
             dbVisible = 2,
             dbSalVisField = 3,
             creditField = 4,
             crConstField = 5,
             crVisible = 6,
             crSalVisField = 7,
             itogField = 8,
             freeField = 9,
             attrField = 10};


enum dictFieldsEnums {tableField = 0,
                      columnField = 1,
                      typeField = 2,
                      lengthField = 3,
                      precisionField = 4,
                      headerField = 5,
                      visibleField = 6,
                      editableField = 7};


QString showAccounts()
{
    FormGrid* accForm = TApplication::exemplar()->getDictionaries()->getDictionary(TApplication::exemplar()->getDBFactory()->getObjectName("счета"))->getForm();
    accForm->getParent()->query();
    accForm->exec();
    if (accForm->isFormSelected())
    {
        return accForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("счета.счет")).toString();
    }
    return "";
}


QString showNumerators()
{
    FormGrid* numeratorForm = TApplication::exemplar()->getDictionaries()->getDictionary(TApplication::exemplar()->getDBFactory()->getObjectName("нумераторы"))->getForm();
    numeratorForm->getParent()->query();
    numeratorForm->exec();
    if (numeratorForm->isFormSelected())
    {
        return numeratorForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("нумераторы.имя")).toString();
    }
    return "";
}


WizardOperation::WizardOperation(): WizardForm()
{
    operName = new QLineEdit();
    fieldsTable = new QTableWidget();
    if (fieldsTable->verticalHeader()->minimumSectionSize() > 0)
        fieldsTable->verticalHeader()->setDefaultSectionSize(fieldsTable->verticalHeader()->minimumSectionSize());
    fldsTableChanged = false;
    docListFieldsTable = new QTableWidget();
    if (docListFieldsTable->verticalHeader()->minimumSectionSize() > 0)
        docListFieldsTable->verticalHeader()->setDefaultSectionSize(docListFieldsTable->verticalHeader()->minimumSectionSize());
    docListFldsTableChanged = false;
    chbSingleString = new QCheckBox();
    bleNumerator = new MyButtonLineEdit();
    bleNumerator->setFormOnPushButton(&showNumerators);
}


WizardOperation::~WizardOperation()
{
}


bool WizardOperation::open(QWidget* pwgt, int op)
{
    if (op == 0)
        op = db->getNewToper();
    oper = op;
    return WizardForm::open(pwgt);
}


void WizardOperation::initFrames()
{
    // Добавим страницы мастера
    QVBoxLayout* layout = nullptr;
    layout = new QVBoxLayout();

    // 1-я страница
    QGridLayout* gridLayout = new QGridLayout();
    QLabel* lblOperName = new QLabel(QObject::trUtf8("Наименование операции:"), formWidget);
    gridLayout->addWidget(lblOperName, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(operName, 0, 1);
    QLabel* lblNumerator = new QLabel(QObject::trUtf8("Нумератор:"), formWidget);
    gridLayout->addWidget(lblNumerator, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(bleNumerator, 1, 1);
    QLabel* lblSingleString = new QLabel(QObject::trUtf8("В документе одна строка:"), formWidget);
    gridLayout->addWidget(lblSingleString, 2, 0, Qt::AlignRight);
    gridLayout->addWidget(chbSingleString, 2, 1);
    gridLayout->setColumnStretch(1, 1);

    layout->addLayout(gridLayout);
    layout->addStretch();
    addFrame(layout, QObject::trUtf8("Наименование операции"));

    // 2-я страница
    layout = new QVBoxLayout();
    // Добавим таблицу проводок
    layout->addWidget(prvTable);
    // Создадим кнопку "Добавить" проводку
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* button;
    button = new QPushButton(QObject::trUtf8("&Добавить"));
    button->setObjectName("buttonAdd");
    connect(button, SIGNAL(clicked()), this, SLOT(addPrv()));
    buttonLayout->addWidget(button);
    // Создадим кнопку "Удалить" проводку
    button = new QPushButton(QObject::trUtf8("&Удалить"));
    button->setObjectName("buttonDelete");
    connect(button, SIGNAL(clicked()), this, SLOT(deletePrv()));
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();
    // Добавим кнопки на форму
    layout->addLayout(buttonLayout);
    addFrame(layout, QObject::trUtf8("Список проводок"));

    // 3-я страница (список столбцов документа)
    layout = new QVBoxLayout();
    // Добавим таблицу проводок
    layout->addWidget(fieldsTable);
    addFrame(layout, QObject::trUtf8("Столбцы документа"));

    // 4-я страница
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
    layout1->addWidget(&headers);
    layout1->addLayout(buttonLayout1);
    layout->addLayout(layout1);
    addFrame(layout, QObject::trUtf8("Порядок столбцов документа"));

    // 5-я страница
    layout = new QVBoxLayout();
    layout->addWidget(textEditor);
    addFrame(layout, QObject::trUtf8("Скрипты"));

    // 6-я страница (список столбцов списка документов)
    layout = new QVBoxLayout();
    layout->addWidget(docListFieldsTable);
    addFrame(layout, QObject::trUtf8("Столбцы списка документов"));

    // 7-я страница
    layout = new QVBoxLayout();
    buttonLayout1 = new QVBoxLayout();
    button = new QPushButton();
    button->setObjectName("buttonUp");
    connect(button, SIGNAL(clicked()), this, SLOT(docListHeaderUp()));
    buttonLayout1->addWidget(button);
    button = new QPushButton();
    button->setObjectName("buttonDown");
    connect(button, SIGNAL(clicked()), this, SLOT(docListHeaderDown()));
    buttonLayout1->addWidget(button);
    layout1 = new QHBoxLayout();
    layout1->addWidget(&docListHeaders);
    layout1->addLayout(buttonLayout1);
    layout->addLayout(layout1);
    addFrame(layout, QObject::trUtf8("Порядок столбцов списка документов"));
}


bool WizardOperation::setData()
{   // Сохранение данных на сервере
    QString opName = operName->text().trimmed();
    if (opName.size() == 0)
    {
        TApplication::exemplar()->showError(QObject::trUtf8("Укажите наименование типовой операции."));
        return false;
    }
    if (prvTable->rowCount() == 0)
    {
        TApplication::exemplar()->showError(QObject::trUtf8("В типовой операции должна быть хотя бы одна проводка."));
        return false;
    }
    if (headers.count() == 0)
    {
        TApplication::exemplar()->showError(QObject::trUtf8("В документе должен отображаться хотя бы один столбец."));
        return false;
    }
    db->beginTransaction();
    int tableId = db->getDictionaryId(QString("Документ%1").arg(oper));
    if (tableId > 0) {
        // Сохраним таблицу проводок
        for (int i = 0; i < prvTable->rowCount(); i++)
        {
            QTableWidgetItem* item;
            QString dbAcc;
            bool dbConstAcc = false;
            bool dbVisib = false;
            bool dbSalVisible = false;
            QString crAcc;
            bool crConstAcc = false;
            bool crVisib = false;
            bool crSalVisible = false;
            bool freePrv = false;
            bool attribute = false;

            dbAcc = "";
            item = prvTable->item(i, debetField);
            if (item != nullptr)
                dbAcc = item->text().trimmed();

            item = prvTable->item(i, dbConstField);
            if (item != nullptr)
                dbConstAcc = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            item = prvTable->item(i, dbVisible);
            if (item != nullptr)
                dbVisib = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            item = prvTable->item(i, dbSalVisField);
            if (item != nullptr)
                dbSalVisible = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            crAcc = "";
            item = prvTable->item(i, creditField);
            if (item != nullptr)
                crAcc = item->text().trimmed();

            item = prvTable->item(i, crConstField);
            if (item != nullptr)
                crConstAcc = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            item = prvTable->item(i, crVisible);
            if (item != nullptr)
                crVisib = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            item = prvTable->item(i, crSalVisField);
            if (item != nullptr)
                crSalVisible = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            item = prvTable->item(i, freeField);
            if (item != nullptr)
                freePrv = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            item = prvTable->item(i, attrField);
            if (item != nullptr)
                attribute = item->text().compare(db->getTrueValue()) == 0 ? true : false;

            QString itog;
            if (prvTable->item(i, itogField) != nullptr)
                itog = prvTable->item(i, itogField)->text().trimmed();
            if (!db->addToperPrv(oper,
                                 i+1,
                                 opName,
                                 dbAcc,
                                 dbConstAcc,
                                 dbVisib,
                                 dbSalVisible,
                                 crAcc,
                                 crConstAcc,
                                 crVisib,
                                 crSalVisible,
                                 itog,
                                 freePrv,
                                 attribute))
            {
                db->rollbackTransaction();
                return false;
            }
        }
        db->deleteToper(oper, prvTable->rowCount() + 1);    // Если в базе остались еще записи о проводках более, чем нам нужно, то удалим их
        // Установим флажок одной строки в документе
        if (!db->setToperSignleString(oper, chbSingleString->isChecked()))
        {
            db->rollbackTransaction();
            return false;
        }
        // Установим нумератор для операции
        if (!db->setToperNumerator(oper, bleNumerator->value()))
        {
            db->rollbackTransaction();
            return false;
        }
        // Отсортируем наименование полей документа
        sortHeaders(&headers, &fields);

        // Установим наименование полей документа
        db->removeColumnHeaders(tableId);
        for (int i = 0; i < fields.count(); i++)
        {
            if (!db->appendColumnHeader(tableId, tableId, fields.value(i).name, fields.value(i).header, fields.value(i).number, fields.value(i).readOnly | fields.value(i).constReadOnly))
            {
                db->rollbackTransaction();
                return false;
            }
        }
        // Отсортируем наименование полей документа
        sortHeaders(&docListHeaders, &docListFields);
        // Установим наименование полей списка документов
        tableId = db->getDictionaryId(QString("СписокДокументов%1").arg(oper));
        if (tableId)
        {
            db->removeColumnHeaders(tableId);
            for (int i = 0; i < docListFields.count(); i++)
            {
               if (!db->appendColumnHeader(tableId, tableId, docListFields.value(i).name, docListFields.value(i).header, docListFields.value(i).number, docListFields.value(i).readOnly | docListFields.value(i).constReadOnly))
               {
                   db->rollbackTransaction();
                   return false;
               }
            }
        }
//        // Установим доступ к операции
//        db->setToperPermition(oper, TApplication::exemplar()->getLogin().toLower(), true);
    }

    // Сохраним скрипты
    QString scriptFile = TApplication::exemplar()->getScriptFileName(oper);
    ScriptEngine::removeScript(scriptFile);
    db->setFile(scriptFile, ScriptFileType, QByteArray().append(textEditor->toPlainText()));
    db->commitTransaction();
    db->clearUpdateNum();

    app->removeDocuments(oper);

    // Перезагрузим список столбцов
    db->loadSystemTables();

    return true;
}


void WizardOperation::getData()
{
    operName->setText(db->getTopersProperties(oper, "имя").toString());

    // Получим список проводок
    prvs = db->getToper(oper);

    // Установим флажок одной строки в документе
    chbSingleString->setCheckState(db->getToperSingleString(oper) ? Qt::Checked : Qt::Unchecked);

    // Установим нумератор
    bleNumerator->setValue(db->getToperNumerator(oper));

    // Создадим таблицу проводок
    prvTable = new QTableWidget((db->querySize(&prvs) > 0 ? db->querySize(&prvs) : 1), 11);
    if (prvTable->verticalHeader()->minimumSectionSize() > 0)
        prvTable->verticalHeader()->setDefaultSectionSize(prvTable->verticalHeader()->minimumSectionSize());
    prvTable->setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Дебет")
                                                      << QObject::trUtf8("Дб.постоянный")
                                                      << QObject::trUtf8("Дб.спр.видим")
                                                      << QObject::trUtf8("Дб.сал.видимо")
                                                      << QObject::trUtf8("Кредит")
                                                      << QObject::trUtf8("Кр.постоянный")
                                                      << QObject::trUtf8("Кр.спр.видим")
                                                      << QObject::trUtf8("Кр.сал.видимо")
                                                      << QObject::trUtf8("Итоги")
                                                      << QObject::trUtf8("Независим.")
                                                      << QObject::trUtf8("Атрибуты"));
    int i = 0;
    if (prvs.first())
    {
        do {
         QTableWidgetItem* item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.дбсчет")).toString());
         prvTable->setItem(i, debetField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.дбпост")).toString());
         prvTable->setItem(i, dbConstField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.дбвидим")).toString());
         prvTable->setItem(i, dbVisible, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.дбсалвидим")).toString());
         prvTable->setItem(i, dbSalVisField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.крсчет")).toString());
         prvTable->setItem(i, creditField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.крпост")).toString());
         prvTable->setItem(i, crConstField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.крвидим")).toString());
         prvTable->setItem(i, crVisible, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.крсалвидим")).toString());
         prvTable->setItem(i, crSalVisField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.итоги")).toString());
         prvTable->setItem(i, itogField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.независим")).toString());
         prvTable->setItem(i, freeField, item);
         item = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.атрибуты")).toString());
         prvTable->setItem(i, attrField, item);
         i++;
        } while (prvs.next());
     }
     MyButtonLineEditItemDelegate* dbEditDelegate = new MyButtonLineEditItemDelegate(getFormWidget());
     dbEditDelegate->setFormOnPushButton(&showAccounts);
     prvTable->setItemDelegateForColumn(debetField, dbEditDelegate);

     MyBooleanItemDelegate* boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(dbConstField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(dbSalVisField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(dbVisible, boolDelegate);

     MyButtonLineEditItemDelegate* crEditDelegate = new MyButtonLineEditItemDelegate(getFormWidget());
     crEditDelegate->setFormOnPushButton(&showAccounts);
     prvTable->setItemDelegateForColumn(creditField, crEditDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(crConstField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(crVisible, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(crSalVisField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(freeField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate(getFormWidget());
     prvTable->setItemDelegateForColumn(attrField, boolDelegate);

     // Получим список проводок и полей и заголовков формы документа
     topersList.clear();
     fields.clear();
     Documents::getDocumentSqlSelectStatement(oper, &topersList, &fields);
     db->getColumnsHeaders(QString("Документ%1").arg(oper), &fields);
     getFieldsTable(&fields, fieldsTable);
     sortHeadersList(fieldsTable, &headers);

     // Получим список полей и заголовков формы списка документов
     docListFields.clear();
     db->getColumnsProperties(&docListFields, db->getObjectName("документы"));
     db->getColumnsProperties(&docListFields, QString("%1%2").arg(db->getObjectName("докатрибуты")).arg(oper));
     db->getColumnsHeaders(QString("СписокДокументов%1").arg(oper), &docListFields);
     getFieldsTable(&docListFields, docListFieldsTable);
     sortHeadersList(docListFieldsTable, &docListHeaders);

     // Инициализируем текстовый редактор
     textEditor = new QTextEdit(formWidget);
     highlighter = new MySyntaxHighlighter(textEditor->document());
     QString scripts = QString(db->getFile(TApplication::exemplar()->getScriptFileName(oper), ScriptFileType));
     textEditor->setText(scripts);

     connect(prvTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(toperTableChanged()));
     connect(fieldsTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(fieldsTableChanged()));
     connect(docListFieldsTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(docListFieldsTableChanged()));

     prvTableChanged = false;
     fldsTableChanged = false;
     docListFldsTableChanged = false;
}


void WizardOperation::addPrv()
{
    prvTable->setRowCount(prvTable->rowCount() + 1);
    for (int i = 0; i < prvTable->columnCount(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("");
        prvTable->setItem(prvTable->rowCount() - 1, i, item);
    }
    prvTable->setCurrentCell(prvTable->rowCount() - 1, 0);
    prvTable->setFocus(Qt::OtherFocusReason);
}


void WizardOperation::deletePrv()
{
    if (prvTable->rowCount() > 0)
    {
        prvTable->removeRow(prvTable->currentRow());
    }
    prvTable->setFocus(Qt::OtherFocusReason);

}


void WizardOperation::showAccountForm()
{
}


void WizardOperation::headerUp()
{
    headers.setFocus(Qt::OtherFocusReason);
    int currentRow = headers.currentRow();
    if (currentRow > 0)
    {
        QListWidgetItem* item = headers.takeItem(currentRow);
        headers.insertItem(currentRow - 1, item);
        headers.setCurrentRow(currentRow - 1);
    }
}


void WizardOperation::headerDown()
{
    headers.setFocus(Qt::OtherFocusReason);
    int currentRow = headers.currentRow();
    if (currentRow < headers.count() - 1)
    {
        QListWidgetItem* item = headers.takeItem(currentRow);
        headers.insertItem(currentRow + 1, item);
        headers.setCurrentRow(currentRow + 1);
    }
}


void WizardOperation::docListHeaderUp()
{
    docListHeaders.setFocus(Qt::OtherFocusReason);
    int currentRow = docListHeaders.currentRow();
    if (currentRow > 0)
    {
        QListWidgetItem* item = docListHeaders.takeItem(currentRow);
        docListHeaders.insertItem(currentRow - 1, item);
        docListHeaders.setCurrentRow(currentRow - 1);
    }
}


void WizardOperation::docListHeaderDown()
{
    docListHeaders.setFocus(Qt::OtherFocusReason);
    int currentRow = docListHeaders.currentRow();
    if (currentRow < docListHeaders.count() - 1)
    {
        QListWidgetItem* item = docListHeaders.takeItem(currentRow);
        docListHeaders.insertItem(currentRow + 1, item);
        docListHeaders.setCurrentRow(currentRow + 1);
    }
}


void WizardOperation::toperTableChanged()
{
    prvTableChanged = true;
}


void WizardOperation::fieldsTableChanged()
{
    fldsTableChanged = true;
}


void WizardOperation::docListFieldsTableChanged()
{
    docListFldsTableChanged = true;
}


void WizardOperation::sortHeadersList(QTableWidget* fieldsTable, QListWidget* headers)
// Составляет список заголовки столбцов по порядку, который был записан в базе данных
// Затем добавляет в конец списка заголовки столбцов, которые пользователь обозначил показывать только что
// Затем готовит список заголовков столбцов к показу
{
    QList<int> list;
    int maxValue = 0;
    for (int i = 0; i < fieldsTable->rowCount(); i++)
    {
        if (fieldsTable->item(i, visibleField)->text() == "true")
        {
            int value = fieldsTable->item(i, visibleField)->data(Qt::UserRole).toInt();
            if (value > 0)
            {
                if (value > maxValue)
                    maxValue = value;
                list << value;
            }

        }
    }
    for (int i = 0; i < fieldsTable->rowCount(); i++)
    {
        if (fieldsTable->item(i, visibleField)->text() == "true")
        {
            int value = fieldsTable->item(i, visibleField)->data(Qt::UserRole).toInt();
            if (value == 0)
            {
                maxValue++;
                value = maxValue;
                fieldsTable->item(i, visibleField)->setData(Qt::UserRole, value);
                list << value;
            }

        }
    }
    qSort(list.begin(), list.end());

    headers->clear();
    for (int i = 0; i < list.count(); i++)
    {
        for (int j = 0; j < fieldsTable->rowCount(); j++)
        {
            if (list.at(i) == fieldsTable->item(j, visibleField)->data(Qt::UserRole).toInt())
            {
                QListWidgetItem* item = new QListWidgetItem(fieldsTable->item(j, headerField)->text(), headers);
                item->setData(Qt::UserRole, fieldsTable->item(j, columnField)->text());
                headers->addItem(item);
            }
        }
    }
}


void WizardOperation::sortHeaders(QListWidget* headers, QList<FieldType>* fields)
// Нумерует заголовки столбцов по порядку, заданному пользователем и готовит номера столбцов к сохранению
{
    for (int j = 0; j < fields->count(); j++)
    {
        FieldType field = fields->at(j);
        field.number = 0;
        fields->removeAt(j);
        fields->insert(j, field);
    }
    for (int i = 0; i < headers->count(); i++)
    {
        for (int j = 0; j < fields->count(); j++)
        {
            QString column = headers->item(i)->data(Qt::UserRole).toString();
            qDebug() << fields->at(j).column << column;
            if (fields->at(j).column == column)
            {
                FieldType field = fields->at(j);
                field.number = i + 1;
                field.header = headers->item(i)->text();
                fields->removeAt(j);
                fields->insert(j, field);
            }
        }
    }
}


void WizardOperation::getFieldsTable(QList<FieldType>* flds,  QTableWidget* fieldsTable)
{
    QStringList columnHeaders;
    columnHeaders << QObject::trUtf8("Таблица")
                  << QObject::trUtf8("Столбец")
                  << QObject::trUtf8("Тип")
                  << QObject::trUtf8("Длина")
                  << QObject::trUtf8("Точность")
                  << QObject::trUtf8("Заголовок")
                  << QObject::trUtf8("Видимость")
                  << QObject::trUtf8("Не изменять");

    // Создадим таблицу столбцов
    fieldsTable->setRowCount(flds->count());
    fieldsTable->setColumnCount(columnHeaders.count());
    fieldsTable->setHorizontalHeaderLabels(columnHeaders);

    for (int i = 0; i < flds->count(); i++)
    {
        QTableWidgetItem* item;

        item = new QTableWidgetItem(flds->at(i).table);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setData(Qt::UserRole, flds->at(i).table);
        fieldsTable->setItem(i, tableField, item);

        item = new QTableWidgetItem(flds->at(i).name);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setData(Qt::UserRole, flds->at(i).name);
        fieldsTable->setItem(i, columnField, item);

        item = new QTableWidgetItem(flds->at(i).type);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, typeField, item);

        item = new QTableWidgetItem(QString("%1").arg(flds->at(i).length));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, lengthField, item);

        item = new QTableWidgetItem(QString("%1").arg(flds->at(i).precision));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, precisionField, item);

        item = new QTableWidgetItem(flds->at(i).header);
        fieldsTable->setItem(i, headerField, item);

        item = new QTableWidgetItem(flds->at(i).number > 0 ? "true" : "false");
        item->setData(Qt::UserRole, flds->at(i).number);
        fieldsTable->setItem(i, visibleField, item);

        item = new QTableWidgetItem(flds->at(i).constReadOnly ? "true" : "false");
        if (flds->at(i).constReadOnly)
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        fieldsTable->setItem(i, editableField, item);
    }

    MyBooleanItemDelegate* booleanDelegate;
    booleanDelegate = new MyBooleanItemDelegate(getFormWidget());
    fieldsTable->setItemDelegateForColumn(visibleField, booleanDelegate);
    booleanDelegate = new MyBooleanItemDelegate(getFormWidget());
    fieldsTable->setItemDelegateForColumn(editableField, booleanDelegate);
}


void WizardOperation::frameActivated(int frameNumber)
{
    if (frameNumber == 4)
    {
        generateScripts();
    }
}


void WizardOperation::frameDeactivated(int frameNumber)
{
    if (frameNumber == 1)
    {
        if (prvTableChanged)
        {
            for (int i = 0; i < prvTable->rowCount(); i++)
            {
                ToperType toperT;
                QTableWidgetItem* item;
                toperT.number = i + 1;
                item = prvTable->item(i, debetField);
                if (item != nullptr)
                    toperT.dbAcc = item->text().trimmed();
                item = prvTable->item(i, dbConstField);
                if (item != nullptr)
                    toperT.dbConst = (QString(item->text()).compare(db->getTrueValue()) == 0) ? true : false;
                item = prvTable->item(i, dbSalVisField);
                if (item != nullptr)
                    toperT.dbSaldoVisible = (QString(item->text()).compare(db->getTrueValue()) == 0) ? true : false;
                item = prvTable->item(i, creditField);
                if (item != nullptr)
                    toperT.crAcc = item->text().trimmed();
                item = prvTable->item(i, crConstField);
                if (item != nullptr)
                    toperT.crConst = (QString(item->text()).compare(db->getTrueValue()) == 0) ? true : false;
                item = prvTable->item(i, itogField);
                item = prvTable->item(i, crSalVisField);
                if (item != nullptr)
                    toperT.crSaldoVisible = (QString(item->text()).compare(db->getTrueValue()) == 0) ? true : false;
                if (item != nullptr)
                    toperT.itog = item->text().trimmed();
                topersList.append(toperT);
            }
            QList<FieldType> flds;
            Documents::getDocumentSqlSelectStatement(oper, &topersList, &flds);
            getFieldsTable(&flds, fieldsTable);
            prvTableChanged = false;
        }

    }
    if (frameNumber == 2 && fldsTableChanged)
    {
        for (int i = 0; i < fieldsTable->rowCount(); i++)
        {
            for (int j = 0; j < fields.count(); j++)
            {
                QString column = fieldsTable->item(i, columnField)->data(Qt::UserRole).toString();
                if (fields.at(j).column == column)
                {
                    FieldType field = fields.at(j);
                    field.readOnly = fieldsTable->item(i, editableField)->text() == "true" ? true : false;
                    fields.removeAt(j);
                    fields.insert(j, field);
                }
            }
        }
        sortHeadersList(fieldsTable, &headers);
        fldsTableChanged = false;
    }
    if (frameNumber == 5 && docListFldsTableChanged)
    {
        for (int i = 0; i < docListFieldsTable->rowCount(); i++)
        {
            QString table = docListFieldsTable->item(i, tableField)->data(Qt::UserRole).toString();
            QString column = table.toUpper() + "__" + docListFieldsTable->item(i, columnField)->data(Qt::UserRole).toString();
            for (int j = 0; j < docListFields.count(); j++)
            {
                if (docListFields.at(j).table == table && docListFields.at(j).column == column)
                {
                    FieldType field = docListFields.at(j);
                    field.header = docListFieldsTable->item(i, headerField)->text();
                    field.readOnly = docListFieldsTable->item(i, editableField)->text() == db->getTrueValue() ? true : false;
                    docListFields.removeAt(j);
                    docListFields.insert(j, field);
                }
            }
        }
        sortHeadersList(docListFieldsTable, &docListHeaders);
        docListFldsTableChanged = false;
    }
}


void WizardOperation::generateScripts()
{
    // Проверим, нужно ли автоматически вставить скрипт вычисления цены или суммы при поступлении на счет, в котором ведется количественный учет
    QString scripts = textEditor->toPlainText();
    if (scripts.size() == 0)
    {
        DocumentScriptEngine engine((Essence*)(app->getDocuments(oper)->getDocument()));

        EventFunction func;
        QString script;
        QTextStream stream(&script, QIODevice::Text);
        // Создадим скрипт для вычисления цены и суммы при оприходовании количественных объектов учета
        if (topersList.count() == 1)
        {
            Dictionary* accDict = app->getDictionaries()->getDictionary(db->getObjectName("счета"));
            accDict->query(QString("%1='%2'").arg(db->getObjectNameCom("счета.счет")).arg(topersList.at(0).dbAcc));
            bool dbQuan = accDict->getValue(db->getObjectName("счета.количество")).toBool();
            accDict->query(QString("%1='%2'").arg(db->getObjectNameCom("счета.счет")).arg(topersList.at(0).crAcc));
            bool crQuan = accDict->getValue(db->getObjectName("счета.количество")).toBool();
            if (dbQuan && !crQuan)
            {
                stream.reset();
                stream << QObject::trUtf8("var кол = getValue(\"P1__КОЛ\");") << endl;
                stream << QObject::trUtf8("var цена = getValue(\"P1__ЦЕНА\");") << endl;
                stream << QObject::trUtf8("var сумма = getValue(\"P1__СУММА\");") << endl;
                stream << QObject::trUtf8("if (getCurrentFieldName() == \"P1__СУММА\" && кол != nullptr)") << endl;
                stream << QObject::trUtf8("   цена = сумма / кол;") << endl;
                stream << QObject::trUtf8("else") << endl;
                stream << QObject::trUtf8("   сумма = кол * цена;") << endl;
                stream << QObject::trUtf8("setValue(\"P1__КОЛ\", кол);") << endl;
                stream << QObject::trUtf8("setValue(\"P1__ЦЕНА\", цена);") << endl;
                stream << QObject::trUtf8("setValue(\"P1__СУММА\", сумма);");
                func.body = script;
                engine.appendEvent("EventCalcTable()", &func);
            }
        }

        // Скрипт для вывода значения постоянного справочника в комментарий
        int constDict = 0;
        QString constDictName;
        for (int i = 0; i < topersList.count(); i++)
        {
            if (topersList.at(i).dbConst)
            {
                constDict++;
                constDictName = topersList.at(i).dbDict;
            }
            if (topersList.at(i).crConst)
            {
                constDict++;
                constDictName = topersList.at(i).crDict;
            }
        }
        scripts = engine.getBlankScripts();
        textEditor->setText(scripts);
    }
}



