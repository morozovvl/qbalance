#include "wizardoperation.h"
#include "mybuttonlineedititemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"


enum fields {debetField = 0,
             dbConstField = 1,
             creditField = 2,
             crConstField = 3,
             itogField = 4};


QString showAccounts()
{
    FormGrid* accForm = TApplication::exemplar()->getDictionaries()->getDictionary( TApplication::exemplar()->getDBFactory()->getObjectName("счета"))->getForm();
    accForm->getParent()->query();
    accForm->exec();
    if (accForm->selected())
    {
        return accForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("счета.счет")).toString();
    }
    return "";
}


WizardOperation::WizardOperation(bool addOp): WizardForm()
{
    addOperation = addOp;
}


bool WizardOperation::open(QWidget* pwgt, int op/* = 0*/)
{
    if (op == 0)
        op = TApplication::exemplar()->getDBFactory()->getNewToper();
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

    // 3-я страница
    layout = new QVBoxLayout();
    // Добавим таблицу проводок
    layout->addWidget(fieldsTable);
    addFrame(layout, QObject::trUtf8("Список столбцов"));

    // 4-я страница
    layout = new QVBoxLayout();
    headers = new QListWidget();
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

    // 5-я страница
    layout = new QVBoxLayout();
    layout->addWidget(textEditor);
    addFrame(layout, QObject::trUtf8("Скрипты"));
}


bool WizardOperation::execute()
{
    TApplication::exemplar()->getDBFactory()->beginTransaction();
    int tableId = TApplication::exemplar()->getDBFactory()->getDictionaryId(QString("Документ%1").arg(oper));
    if (tableId > 0) {
        // Сохраним проводки
        if (!savePrvTable())
        {
            TApplication::exemplar()->getDBFactory()->rollbackTransaction();
            return false;
        }
        // Установим наименование полей
        if (headers->count() > 0)
        {
            for (int i = 0; i < headers->count(); i++)
            {
                for (int j = 0; j < fieldsTable->rowCount(); j++)
                {
                    if (QString::compare(fieldsTable->item(j, 4)->text(), headers->item(i)->data(Qt::DisplayRole).toString()) == 0)
                    {
                         if (!TApplication::exemplar()->getDBFactory()->setTableColumnHeaderOrder(tableId, fieldsTable->item(j, 0)->text(), i + 1))
                         {
                                 TApplication::exemplar()->getDBFactory()->rollbackTransaction();
                                 return false;
                         }
                    }
                }
            }
        }
    }

    // Сохраним скрипты
    TApplication::exemplar()->getDBFactory()->setFile(QString("./scripts/формулы%1.qs").arg(oper), ScriptFileType, QByteArray().append(textEditor->toPlainText()));
    TApplication::exemplar()->getDBFactory()->commitTransaction();
    return true;
}


void WizardOperation::getData()
{
    operName = new QLineEdit();
    // Получим список проводок
    DBFactory* db = TApplication::exemplar()->getDBFactory();
    prvs = db->getToper(oper);

    // Создадим таблицу проводок
    prvTable = new QTableWidget((prvs.size() > 0 ? prvs.size() : 1), 5);
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

     // Создадим таблицу столбцов
     QMap<int, FieldType> flds;
     TApplication::exemplar()->getDBFactory()->getDocumentSqlSelectStatement(oper, &flds);

     fieldsTable = new QTableWidget(flds.count(), 6);
     fieldsTable->setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Столбец")
                                                          << QObject::trUtf8("Тип")
                                                          << QObject::trUtf8("Длина")
                                                          << QObject::trUtf8("Точность")
                                                          << QObject::trUtf8("Заголовок")
                                                          << QObject::trUtf8("Видимость"));
     for (int i = 0; i < flds.count(); i++)
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
         fields << flds.value(i);
     }

//     buttonEditDelegate->setFormOnPushButton(&showTypesForm);
     MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(getForm());
     fieldsTable->setItemDelegateForColumn(5, booleanDelegate);

     // Инициализируем текстовый редактор
     textEditor = new MyTextEdit(formWidget);
     highlighter = new MySyntaxHighlighter(textEditor->document());
     textEditor->setText(QString(TApplication::exemplar()->getDBFactory()->getFile(QString("./scripts/формулы%1.qs").arg(oper), ScriptFileType)));
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


void WizardOperation::frameActivated(int frameNumber)
{
    if (frameNumber == 3)
    {   // Если активизирован фрейм списка заголовков
        headers->clear();
        // Отсортируем колонки
        QList<int> headersOrder;
        for (int i = 0; i < fields.count(); i++)
        {
            if (fields.value(i).number > 0)
                headersOrder << fields.value(i).number;
        }
        qSort(headersOrder.begin(), headersOrder.end());
        for (int i = 0; i < headersOrder.count(); i++)
        {
            for (int j = 0; j < fields.count(); j++)
            {
                if (fieldsTable->item(j, 5)->text() == "true")
                {
                    if (fields.value(j).number == headersOrder.value(i))
                    {
                        if (fieldsTable->item(j, 4)->text().size() > 0)
                            headers->addItem(fieldsTable->item(j, 4)->text());
                        else
                            headers->addItem(fieldsTable->item(j, 0)->text());
                    }
                }
            }
        }
    }
}


bool WizardOperation::savePrvTable()
{  // Сохранить проводки
    if (TApplication::exemplar()->getDBFactory()->deleteToper(oper))
    {
        for (int i = 0; i < prvTable->rowCount(); i++)
        {
            QString dbAcc = prvTable->item(i, debetField) != 0 ? prvTable->item(i, debetField)->text().trimmed() : "";
            bool dbAccConst = prvTable->item(i, dbConstField) == 0 || prvTable->item(i, dbConstField)->text() == "false" ? false : true;
            QString crAcc = prvTable->item(i, creditField) != 0 ? prvTable->item(i, creditField)->text().trimmed() : "";
            bool crAccConst = (prvTable->item(i, crConstField) == 0 || prvTable->item(i, crConstField)->text() == "false" ? false : true);
            QString itog = prvTable->item(i, itogField) != 0 ? prvTable->item(i, itogField)->text() : "";
            qDebug() << dbAcc << dbAccConst << crAcc << crAccConst << itog;
            if (!TApplication::exemplar()->getDBFactory()->addToperPrv(oper, operName->text(),
                                                                  dbAcc,
                                                                  dbAccConst,
                                                                  crAcc,
                                                                  crAccConst,
                                                                  itog))
                return false;
        }
        return TApplication::exemplar()->getDBFactory()->createNewToperPermission(QString(oper), true);
    }
    return false;
}


