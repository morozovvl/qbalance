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
    layout->addWidget(textEditor);
    addFrame(layout, QObject::trUtf8("Скрипты"));
}


bool WizardOperation::execute()
{
    TApplication::exemplar()->getDBFactory()->setFile(QString("./scripts/формулы%1.qs").arg(oper), ScriptFileType, QByteArray().append(textEditor->toPlainText()));
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
    qDebug() << "deletePrv()";
}


void WizardOperation::showAccountForm()
{
    qDebug() << "showAccountForm()";
}


QString showDictionary()
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


