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

#include <QVariant>
#include "wizardoperation.h"
#include "mybuttonlineedititemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "../kernel/app.h"
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
             freeField = 9};


QString showAccounts()
{
    FormGrid* accForm = TApplication::exemplar()->getDictionaries()->getDictionary(TApplication::exemplar()->getDBFactory()->getObjectName("счета"))->getForm();
    accForm->getParent()->query();
    accForm->exec();
    if (accForm->selected())
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
    if (numeratorForm->selected())
    {
        return numeratorForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("нумераторы.имя")).toString();
    }
    return "";
}


WizardOperation::WizardOperation(): WizardForm()
{
    operName = new QLineEdit();
    fieldsTable = new QTableWidget();
    fldsTableChanged = false;
    docListFieldsTable = new QTableWidget();
    docListFldsTableChanged = false;
    headers = new QListWidget();
    docListHeaders = new QListWidget();
    chbSingleString = new QCheckBox();
    bleNumerator = new MyButtonLineEdit();
    bleNumerator->setFormOnPushButton(&showNumerators);
}


bool WizardOperation::open(QWidget* pwgt, int op/* = 0*/)
{
    if (op == 0)
        op = db->getNewToper();
    oper = op;
    return WizardForm::open(pwgt);
}


void WizardOperation::initFrames()
{
    // Добавим страницы мастера
    QVBoxLayout* layout = 0;
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
    layout1->addWidget(headers);
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
    layout1->addWidget(docListHeaders);
    layout1->addLayout(buttonLayout1);
    layout->addLayout(layout1);
    addFrame(layout, QObject::trUtf8("Порядок столбцов списка документов"));
}


bool WizardOperation::setData()
{
    QString opName = operName->text().trimmed();
    if (opName.size() == 0)
    {
        TApplication::exemplar()->getGUIFactory()->showError(QObject::trUtf8("Укажите наименование типовой операции."));
        return false;
    }
    if (prvTable->rowCount() == 0)
    {
        TApplication::exemplar()->getGUIFactory()->showError(QObject::trUtf8("В типовой операции должна быть хотя бы одна проводка."));
        return false;
    }
    if (headers->count() == 0)
    {
        TApplication::exemplar()->getGUIFactory()->showError(QObject::trUtf8("В документе должен отображаться хотя бы один столбец."));
        return false;
    }
    db->beginTransaction();
    int tableId = db->getDictionaryId(QString("Документ%1").arg(oper));
    if (tableId > 0) {
        // Сохраним таблицу проводок
        db->deleteToper(oper);
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

            dbAcc = "";
            item = prvTable->item(i, debetField);
            if (item != 0)
                dbAcc = item->text().trimmed();
            if (dbAcc.size() == 0)
            {
                TApplication::exemplar()->getGUIFactory()->showError(QString(QObject::trUtf8("Не указан дебетовый счет в проводке № %1")).arg(i+1));
                return false;
            }

            item = prvTable->item(i, dbConstField);
            if (item != 0)
                dbConstAcc = item->text().compare("true") == 0 ? true : false;

            item = prvTable->item(i, dbVisible);
            if (item != 0)
                dbVisib = item->text().compare("true") == 0 ? true : false;

            item = prvTable->item(i, dbSalVisField);
            if (item != 0)
                dbSalVisible = item->text().compare("true") == 0 ? true : false;

            crAcc = "";
            item = prvTable->item(i, creditField);
            if (item != 0)
                crAcc = item->text().trimmed();
            if (crAcc.size() == 0)
            {
                TApplication::exemplar()->getGUIFactory()->showError(QString(QObject::trUtf8("Не указан кредитовый счет в проводке № %1")).arg(i+1));
                return false;
            }

            item = prvTable->item(i, crConstField);
            if (item != 0)
                crConstAcc = item->text().compare("true") == 0 ? true : false;

            item = prvTable->item(i, crVisible);
            if (item != 0)
                crVisib = item->text().compare("true") == 0 ? true : false;

            item = prvTable->item(i, crSalVisField);
            if (item != 0)
                crSalVisible = item->text().compare("true") == 0 ? true : false;

            item = prvTable->item(i, freeField);
            if (item != 0)
                freePrv = item->text().compare("true") == 0 ? true : false;

            QString itog;
            if (prvTable->item(i, itogField) != 0)
                itog = prvTable->item(i, itogField)->text().trimmed();
            if (!db->addToperPrv(oper,
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
                            freePrv))
            {
                db->rollbackTransaction();
                return false;
            }
        }
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
        // Установим наименование полей документа
        for (int i = 0; i < headers->count(); i++)
        {
            for (int j = 0; j < fieldsTable->rowCount(); j++)
            {
                if (QString::compare(fieldsTable->item(j, 4)->text(), headers->item(i)->data(Qt::DisplayRole).toString()) == 0)
                {
                     if (!db->setTableColumnHeaderOrder(tableId, fieldsTable->item(j, 0)->text(), fieldsTable->item(j, 4)->text(), i + 1))
                     {
                             db->rollbackTransaction();
                             return false;
                     }
                }
            }
        }
        // Установим наименование полей списка документов
        tableId = db->getDictionaryId(QString("СписокДокументов%1").arg(oper));
        if (tableId)
        {
            for (int i = 0; i < docListHeaders->count(); i++)
            {
                for (int j = 0; j < docListFieldsTable->rowCount(); j++)
                {
                    if (QString::compare(docListFieldsTable->item(j, 4)->text(), docListHeaders->item(i)->data(Qt::DisplayRole).toString()) == 0)
                    {
                         if (!db->setTableColumnHeaderOrder(tableId, docListFieldsTable->item(j, 0)->text(), docListFieldsTable->item(j, 4)->text(), i + 1))
                         {
                                 db->rollbackTransaction();
                                 return false;
                         }
                    }
                }
            }
        }
        // Установим доступ к операции
        db->setToperPermition(oper, TApplication::exemplar()->getLogin().toLower(), true);
    }

    // Сохраним скрипты
    db->setFile(TApplication::exemplar()->getScriptFileName(oper), ScriptFileType, QByteArray().append(textEditor->toPlainText()));
    db->commitTransaction();
    return true;
}


void WizardOperation::getData()
{
    operName->setText(db->getTopersProperties(oper).value(db->getObjectName("vw_доступ_к_топер.имя")).toString());

    // Получим список проводок
    prvs = db->getToper(oper);

    // Установим флажок одной строки в документе
    chbSingleString->setCheckState(db->getToperSingleString(oper) ? Qt::Checked : Qt::Unchecked);

    // Установим нумератор
    bleNumerator->setValue(db->getToperNumerator(oper));

    // Создадим таблицу проводок
    prvTable = new QTableWidget((prvs.size() > 0 ? prvs.size() : 1), 10);
    connect(prvTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(toperTableChanged()));
    prvTable->setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Дебет")
                                                      << QObject::trUtf8("Дб.постоянный")
                                                      << QObject::trUtf8("Дб.спр.видим")
                                                      << QObject::trUtf8("Дб.сал.видимо")
                                                      << QObject::trUtf8("Кредит")
                                                      << QObject::trUtf8("Кр.постоянный")
                                                      << QObject::trUtf8("Кр.спр.видим")
                                                      << QObject::trUtf8("Кр.сал.видимо")
                                                      << QObject::trUtf8("Итоги")
                                                      << QObject::trUtf8("Независим."));
     for (int i = 0; i < prvs.size(); i++)
     {
         prvs.seek(i);
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
     }
     MyButtonLineEditItemDelegate* dbEditDelegate = new MyButtonLineEditItemDelegate();
     dbEditDelegate->setFormOnPushButton(&showAccounts);
     prvTable->setItemDelegateForColumn(debetField, dbEditDelegate);

     MyBooleanItemDelegate* boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(dbConstField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(dbSalVisField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(dbVisible, boolDelegate);

     MyButtonLineEditItemDelegate* crEditDelegate = new MyButtonLineEditItemDelegate();
     crEditDelegate->setFormOnPushButton(&showAccounts);
     prvTable->setItemDelegateForColumn(creditField, crEditDelegate);

     boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(crConstField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(crVisible, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(crSalVisField, boolDelegate);

     boolDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(freeField, boolDelegate);

     topersList.clear();
     QMap<int, FieldType> flds;
     db->getDocumentSqlSelectStatement(oper, TApplication::exemplar()->getDictionaries(), &topersList, &flds);
     getFieldsTable(flds, fieldsTable, &fields);
     sortHeaders(headers, &fields);
     db->getColumnsProperties(&flds, db->getObjectName("документы"), oper);
     getFieldsTable(flds, docListFieldsTable, &docListFields);
     sortHeaders(docListHeaders, &docListFields);

     // Инициализируем текстовый редактор
     textEditor = new MyTextEdit(formWidget);
     highlighter = new MySyntaxHighlighter(textEditor->document());
     QString scripts = QString(db->getFile(TApplication::exemplar()->getScriptFileName(oper), ScriptFileType));
     if (scripts.size() == 0)
     {
         DocumentScriptEngine engine;
         scripts = engine.getBlankScripts();
     }
     textEditor->setText(scripts);
     connect(fieldsTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(fieldsTableChanged()));
     connect(docListFieldsTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(docListFieldsTableChanged()));
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
    headers->setFocus(Qt::OtherFocusReason);
    int currentRow = headers->currentRow();
    if (currentRow > 0)
    {
        QListWidgetItem* item = headers->takeItem(currentRow);
        headers->insertItem(currentRow - 1, item);
        headers->setCurrentRow(currentRow - 1);
    }
}


void WizardOperation::headerDown()
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


void WizardOperation::docListHeaderUp()
{
    docListHeaders->setFocus(Qt::OtherFocusReason);
    int currentRow = docListHeaders->currentRow();
    if (currentRow > 0)
    {
        QListWidgetItem* item = docListHeaders->takeItem(currentRow);
        docListHeaders->insertItem(currentRow - 1, item);
        docListHeaders->setCurrentRow(currentRow - 1);
    }
}


void WizardOperation::docListHeaderDown()
{
    docListHeaders->setFocus(Qt::OtherFocusReason);
    int currentRow = docListHeaders->currentRow();
    if (currentRow < docListHeaders->count() - 1)
    {
        QListWidgetItem* item = docListHeaders->takeItem(currentRow);
        docListHeaders->insertItem(currentRow + 1, item);
        docListHeaders->setCurrentRow(currentRow + 1);
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


void WizardOperation::sortHeaders(QListWidget* headers, QList<FieldType>* fields) {
    headers->clear();
    // Отсортируем колонки
    QList<int> headersOrder;
    for (int i = 0; i < fields->count(); i++)
    {
        if (fields->value(i).number > 0)
            headersOrder << fields->value(i).number;
    }
    qSort(headersOrder.begin(), headersOrder.end());
    for (int i = 0; i < headersOrder.count(); i++)
    {
        for (int j = 0; j < fields->count(); j++)
        {
            if (fields->at(j).number == headersOrder.at(i))
            {
                headers->addItem(fields->at(j).header);
            }
        }
    }
}


void WizardOperation::getFieldsTable(QMap<int, FieldType> flds,  QTableWidget* fieldsTable, QList<FieldType>* fields)
{
    // Создадим таблицу столбцов
    fieldsTable->setRowCount(flds.count());
    fieldsTable->setColumnCount(6);

    fieldsTable->setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Столбец")
                                                         << QObject::trUtf8("Тип")
                                                         << QObject::trUtf8("Длина")
                                                         << QObject::trUtf8("Точность")
                                                         << QObject::trUtf8("Заголовок")
                                                         << QObject::trUtf8("Видимость"));
    foreach (int i, flds.keys())
    {
        QTableWidgetItem* item;
        item = new QTableWidgetItem(flds.value(i).name);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, 0, item);
        item = new QTableWidgetItem(flds.value(i).type);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, 1, item);
        item = new QTableWidgetItem(QString("%1").arg(flds.value(i).length));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, 2, item);
        item = new QTableWidgetItem(QString("%1").arg(flds.value(i).precision));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        fieldsTable->setItem(i, 3, item);
        item = new QTableWidgetItem(flds.value(i).header);
        fieldsTable->setItem(i, 4, item);
        item = new QTableWidgetItem(flds.value(i).number > 0 ? "true" : "false");
        fieldsTable->setItem(i, 5, item);
        (*fields) << flds.value(i);
    }

//     buttonEditDelegate->setFormOnPushButton(&showTypesForm);
    MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(getForm());
    fieldsTable->setItemDelegateForColumn(5, booleanDelegate);
}


void WizardOperation::frameDeactivated(int frameNumber)
{
    if (frameNumber == 1 && prvTableChanged)
    {
        for (int i = 0; i < prvTable->rowCount(); i++)
        {
            ToperType toperT;
            QTableWidgetItem* item;
            toperT.number = i + 1;
            item = prvTable->item(i, debetField);
            if (item != 0)
                toperT.dbAcc = item->text().trimmed();
            item = prvTable->item(i, dbConstField);
            if (item != 0)
                toperT.dbConst = (QString(item->text()).compare("true") == 0) ? true : false;
            item = prvTable->item(i, dbSalVisField);
            if (item != 0)
                toperT.dbSaldoVisible = (QString(item->text()).compare("true") == 0) ? true : false;
            item = prvTable->item(i, creditField);
            if (item != 0)
                toperT.crAcc = item->text().trimmed();
            item = prvTable->item(i, crConstField);
            if (item != 0)
                toperT.crConst = (QString(item->text()).compare("true") == 0) ? true : false;
            item = prvTable->item(i, itogField);
            item = prvTable->item(i, crSalVisField);
            if (item != 0)
                toperT.crSaldoVisible = (QString(item->text()).compare("true") == 0) ? true : false;
            if (item != 0)
                toperT.itog = item->text().trimmed();
            topersList.append(toperT);
        }
        QMap<int, FieldType> flds;
        db->getDocumentSqlSelectStatement(oper, TApplication::exemplar()->getDictionaries(), &topersList, &flds);
        getFieldsTable(flds, fieldsTable, &fields);
        prvTableChanged = false;
    }
    if (frameNumber == 2 && fldsTableChanged)
    {
        int num = 1;
        FieldType fieldT;
        fields.clear();
        for (int i = 0; i < fieldsTable->rowCount(); i++)
        {
            if (QString(fieldsTable->item(i, 5)->text()).compare("true") == 0)
            {
                fieldT.header = fieldsTable->item(i, 4)->text().trimmed();
                fieldT.number = num;
                fields.append(fieldT);
                num++;
            }
        }
        sortHeaders(headers, &fields);
        fldsTableChanged = false;
    }
    if (frameNumber == 5 && docListFldsTableChanged)
    {
        int num = 1;
        FieldType fieldT;
        docListFields.clear();
        for (int i = 0; i < docListFieldsTable->rowCount(); i++)
        {
            if (QString(docListFieldsTable->item(i, 5)->text()).compare("true") == 0)
            {
                fieldT.header = docListFieldsTable->item(i, 4)->text().trimmed();
                fieldT.number = num;
                docListFields.append(fieldT);
                num++;
            }
        }
        sortHeaders(docListHeaders, &docListFields);
        docListFldsTableChanged = false;
    }
}


