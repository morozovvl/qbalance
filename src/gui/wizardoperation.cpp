#include <QVariant>
#include "wizardoperation.h"
#include "mybuttonlineedititemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"
#include "../engine/documentscriptengine.h"


enum fieldsEnums {debetField = 0,
             dbConstField = 1,
             creditField = 2,
             crConstField = 3,
             itogField = 4};


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


WizardOperation::WizardOperation(): WizardForm()
{
    fieldsTable = new QTableWidget();
    fldsTableChanged = false;
    docListFieldsTable = new QTableWidget();
    docListFldsTableChanged = false;
    db = TApplication::exemplar()->getDBFactory();
    headers = new QListWidget();
    docListHeaders = new QListWidget();
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
    gridLayout->addWidget(operName, 0, 1, Qt::AlignLeft);
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


bool WizardOperation::execute()
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
            QString crAcc;
            bool crConstAcc = false;
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
            QString itog = prvTable->item(i, itogField)->text().trimmed();
            if (!db->addToperPrv(oper,
                            opName,
                            dbAcc,
                            dbConstAcc,
                            crAcc,
                            crConstAcc,
                            itog))
            {
                db->rollbackTransaction();
                return false;
            }
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
    }

    // Сохраним скрипты
    db->setFile(QString("./scripts/формулы%1.qs").arg(oper), ScriptFileType, QByteArray().append(textEditor->toPlainText()));
    db->commitTransaction();
    return true;
}


void WizardOperation::getData()
{
    operName = new QLineEdit();
    operName->setText(db->getTopersProperties(oper).value(db->getObjectName("vw_доступ_к_топер.имя")).toString());

    // Получим список проводок
    prvs = db->getToper(oper);

    // Создадим таблицу проводок
    prvTable = new QTableWidget((prvs.size() > 0 ? prvs.size() : 1), 5);
    connect(prvTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(toperTableChanged()));
    prvTable->setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Дебет")
                                                      << QObject::trUtf8("Дб.постоянный")
                                                      << QObject::trUtf8("Кредит")
                                                      << QObject::trUtf8("Кр.постоянный")
                                                      << QObject::trUtf8("Итоги"));
     for (int i = 0; i < prvs.size(); i++)
     {
         prvs.seek(i);
         QTableWidgetItem* debetItem = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.дбсчет")).toString());
         prvTable->setItem(i, debetField, debetItem);
         QTableWidgetItem* dbConstItem = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.дбпост")).toString());
         prvTable->setItem(i, dbConstField, dbConstItem);
         QTableWidgetItem* creditItem = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.крсчет")).toString());
         prvTable->setItem(i, creditField, creditItem);
         QTableWidgetItem* crConstItem = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.крпост")).toString());
         prvTable->setItem(i, crConstField, crConstItem);
         QTableWidgetItem* itogItem = new QTableWidgetItem(prvs.record().value(db->getObjectName("топер.итоги")).toString());
         prvTable->setItem(i, itogField, itogItem);
     }
     MyButtonLineEditItemDelegate* dbEditDelegate = new MyButtonLineEditItemDelegate();
     dbEditDelegate->setFormOnPushButton(&showAccounts);
     prvTable->setItemDelegateForColumn(debetField, dbEditDelegate);

     MyBooleanItemDelegate* dbConstBooleanDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(dbConstField, dbConstBooleanDelegate);

     MyButtonLineEditItemDelegate* crEditDelegate = new MyButtonLineEditItemDelegate();
     crEditDelegate->setFormOnPushButton(&showAccounts);
     prvTable->setItemDelegateForColumn(creditField, crEditDelegate);

     MyBooleanItemDelegate* crConstBooleanDelegate = new MyBooleanItemDelegate();
     prvTable->setItemDelegateForColumn(crConstField, crConstBooleanDelegate);

     topersList.clear();
     QMap<int, FieldType> flds;
     db->getDocumentSqlSelectStatement(oper, &topersList, &flds);
     getFieldsTable(flds, fieldsTable, &fields);
     sortHeaders(headers, &fields);
     db->getColumnsProperties(&flds, db->getObjectName("документы"), oper);
     getFieldsTable(flds, docListFieldsTable, &docListFields);
     sortHeaders(docListHeaders, &docListFields);

     // Инициализируем текстовый редактор
     textEditor = new MyTextEdit(formWidget);
     highlighter = new MySyntaxHighlighter(textEditor->document());
     QString scripts = QString(db->getFile(QString("./scripts/формулы%1.qs").arg(oper), ScriptFileType));
     if (scripts.size() == 0)
     {
        // создадим пустой скрипт с событиями
        QTextStream stream(&scripts, QIODevice::Text);
        QList<EventFunction>* events = DocumentScriptEngine::getEventsList();
        for (int i = 0; i < events->count(); i++)
        {
            stream << events->at(i).keyWord << " " << events->at(i).name << endl;
            stream << events->at(i).begin << " " << events->at(i).comment << endl;
            stream << QObject::trUtf8("// Здесь Вы можете вставить свой код") << endl;
            stream << events->at(i).end << endl;
            stream << endl << endl;
        }
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
    qDebug() << "showAccountForm()";
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
        QTableWidgetItem* nameItem = new QTableWidgetItem(flds.value(i).name);
        fieldsTable->setItem(i, 0, nameItem);
        QTableWidgetItem* typeItem = new QTableWidgetItem(flds.value(i).type);
        fieldsTable->setItem(i, 1, typeItem);
        QTableWidgetItem* lengthItem = new QTableWidgetItem(QString("%1").arg(flds.value(i).length));
        fieldsTable->setItem(i, 2, lengthItem);
        QTableWidgetItem* precisionItem = new QTableWidgetItem(QString("%1").arg(flds.value(i).precision));
        fieldsTable->setItem(i, 3, precisionItem);
        QTableWidgetItem* headerItem = new QTableWidgetItem(flds.value(i).header);
        fieldsTable->setItem(i, 4, headerItem);
        QTableWidgetItem* visibleItem = new QTableWidgetItem(flds.value(i).number > 0 ? "true" : "false");
        fieldsTable->setItem(i, 5, visibleItem);
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
            item = prvTable->item(i, creditField);
            if (item != 0)
                toperT.crAcc = item->text().trimmed();
            item = prvTable->item(i, crConstField);
            if (item != 0)
                toperT.crConst = (QString(item->text()).compare("true") == 0) ? true : false;
            item = prvTable->item(i, itogField);
            if (item != 0)
                toperT.itog = item->text().trimmed();
            topersList.append(toperT);
        }
        QMap<int, FieldType> flds;
        db->getDocumentSqlSelectStatement(oper, &topersList, &flds);
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


