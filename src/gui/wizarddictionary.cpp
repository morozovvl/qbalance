#include <QDebug>
#include <QMap>
#include <QVariant>
#include "wizarddictionary.h"
#include "../kernel/app.h"
#include "mybuttonlineedit.h"
#include "mybuttonlineedititemdelegate.h"
#include "mybooleanitemdelegate.h"
#include "mylineitemdelegate.h"
#include "../definitions.h"


WizardDictionary* WizardDictionary::Exemplar   = NULL;


QString showTypesForm()
{
    FormGrid* typeForm = TApplication::exemplar()->getDictionaries()->getDictionary(TApplication::exemplar()->getDBFactory()->getObjectName("vw_types"))->getForm();
    typeForm->exec();
    if (typeForm->selected())
    {
        int length = typeForm->getParent()->getValue(TApplication::exemplar()->getDBFactory()->getObjectName("vw_types.длина")).toInt();
        QTableWidgetItem* item = WizardDictionary::exemplar()->fieldsTable->item(WizardDictionary::exemplar()->fieldsTable->currentRow(), 2);
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
  , tableName(NULL)
  , tableMenuName(NULL)
{
    addDictionary = addDict;
    tableName = new QLineEdit();
    tableMenuName = new QLineEdit();
    tableFormName = new QLineEdit();
    db = TApplication::exemplar()->getDBFactory();
    chbMenu = new QCheckBox(formWidget);
    if (!Exemplar)
    {
        Exemplar = this;
    }
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

    QLabel* lblMenuTableName = new QLabel(QObject::trUtf8("Наименование в меню:"), formWidget);
    gridLayout->addWidget(lblMenuTableName, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(tableMenuName, 1, 1);

    QLabel* lblFormTableName = new QLabel(QObject::trUtf8("Наименование в форме:"), formWidget);
    gridLayout->addWidget(lblFormTableName, 2, 0, Qt::AlignRight);
    gridLayout->addWidget(tableFormName, 2, 1);

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
    layout->addWidget(fieldsTable);
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
}


void WizardDictionary::getData()
{

    if (table.size() == 0)
    {
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

        FieldType field;
        field.name = "код";
        field.type = "int4";
        field.length = 0;
        field.precision = 0;
        field.header = "Код";
        field.number = 1;
        fields.append(field);

        field.name = "имя";
        field.type = "character varying";
        field.length = 100;
        field.precision = 0;
        field.header = "Наименование";
        field.number = 2;
        fields.append(field);
    }
    else
    {   // Получим список полей таблицы
        db->getColumnsProperties(&fields, table);
        tableMenuName->setText(TApplication::exemplar()->getDictionaries()->getDictionaryTitle(table));
        QSqlRecord dictProperties = db->getDictionariesProperties(table);
        tableFormName->setText(dictProperties.value(__NAME_IN_FORM__).toString());
        if (dictProperties.value(db->getObjectName("vw_доступ_к_справочникам.меню")).toBool())
            chbMenu->setCheckState(Qt::Checked);
        else
            chbMenu->setCheckState(Qt::Unchecked);
        tableName->setEnabled(false);
    }
    fieldsTable = new QTableWidget(fields.count(), 6);
    // Если известно, с какой таблицей будем работать
    tableName->setText(table);
    // Создадим таблицу столбцов
    fieldsTable->setHorizontalHeaderLabels(QStringList() << QObject::trUtf8("Столбец")
                                                         << QObject::trUtf8("Тип")
                                                         << QObject::trUtf8("Длина")
                                                         << QObject::trUtf8("Точность")
                                                         << QObject::trUtf8("Заголовок")
                                                         << QObject::trUtf8("Видимость"));
    for (int i = 0; i < fields.count(); i++)
    {
        QTableWidgetItem* nameItem = new QTableWidgetItem(fields.value(i).name);
        fieldsTable->setItem(i, 0, nameItem);
        QTableWidgetItem* typeItem = new QTableWidgetItem(fields.value(i).type);
        fieldsTable->setItem(i, 1, typeItem);
        QTableWidgetItem* lengthItem = new QTableWidgetItem(QString("%1").arg(fields.value(i).length));
        fieldsTable->setItem(i, 2, lengthItem);
        QTableWidgetItem* precisionItem = new QTableWidgetItem(QString("%1").arg(fields.value(i).precision));
        fieldsTable->setItem(i, 3, precisionItem);
        QTableWidgetItem* headerItem = new QTableWidgetItem(fields.value(i).header);
        fieldsTable->setItem(i, 4, headerItem);
        QTableWidgetItem* visibleItem = new QTableWidgetItem(fields.value(i).number > 0 ? "true" : "false");
        fieldsTable->setItem(i, 5, visibleItem);
    }

    MyButtonLineEditItemDelegate* buttonEditDelegate = new MyButtonLineEditItemDelegate(getForm());
    fieldsTable->setItemDelegateForColumn(1, buttonEditDelegate);
    buttonEditDelegate->setFormOnPushButton(&showTypesForm);
    MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(getForm());
    fieldsTable->setItemDelegateForColumn(5, booleanDelegate);
}


bool WizardDictionary::execute()
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
    int tableId = db->getDictionaryId(tableName->text());
    if (tableId > 0) {
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
            if (fields.value(i).type.size() == 0)
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
        for (int i = 0; i < fieldsTable->rowCount(); i++)
        {
            QString fieldName = fieldsTable->item(i, 0)->text().trimmed();
            QString sType = fieldsTable->item(i, 1)->text();
            int nLength = fieldsTable->item(i, 2)->text().toInt();
            int nPrecision = fieldsTable->item(i, 3)->text().toInt();
            QString sHeader = fieldsTable->item(i, 4)->text().trimmed();
            QString length, precision;
            if (nPrecision > 0)
            { //f Если указана точность
                precision = QString(", %1").arg(nPrecision);
            }
            if (nLength > 0)
            {   // Если указана длина
                length = QString("(%1%2)").arg(nLength).arg(precision);
            }
            QString type = fieldsTable->item(i, 1)->text().trimmed();
            type = QString("%1%2").arg(type).arg(length);
            if (i < fields.count())
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
                // Проверим, изменил ли пользователь заголовок столбца
                if (QString::compare(sHeader, fields.value(i).header, Qt::CaseSensitive) != 0)
                {
                    if (fields.value(i).header.size() > 0)
                    {  // Если заголовок для этого столбца уже был
                        if (!db->updateColumnHeader(tableId, fieldName, sHeader))
                        {
                                db->rollbackTransaction();
                                return false;
                        }
                    }
                    else
                    {
                        if (!db->appendColumnHeader(tableId, fieldName, sHeader))
                        {
                                db->rollbackTransaction();
                                return false;
                        }
                    }
                }
            }
            else
            {   // Если мы добавляем новые поля
                if (!db->addTableColumn(tableName->text(), fieldName, type))
                {
                        db->rollbackTransaction();
                        return false;
                }
                if (sHeader.size() > 0)
                {
                    if (!db->appendColumnHeader(tableId, fieldName, sHeader))
                    {
                            db->rollbackTransaction();
                            return false;
                    }
                }
            }
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
                         if (!db->setTableColumnHeaderOrder(tableId, fieldsTable->item(j, 0)->text(), fieldsTable->item(j, 4)->text(), i + 1))
                         {
                                 db->rollbackTransaction();
                                 return false;
                         }
                    }
                }
            }
        }
    }
    db->commitTransaction();
    return true;
}


void WizardDictionary::addColumn()
{
    fieldsTable->setRowCount(fieldsTable->rowCount() + 1);
    for (int i = 0; i < fieldsTable->columnCount(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("");
        fieldsTable->setItem(fieldsTable->rowCount() - 1, i, item);
    }
    fieldsTable->setCurrentCell(fieldsTable->rowCount() - 1, 0);
    fieldsTable->setFocus(Qt::OtherFocusReason);
}


void WizardDictionary::deleteColumn()
{
    if (fieldsTable->rowCount() > 1)
    {   // Можно удалять все столбцы, кроме первого (КОД)
        FieldType fld = fields.value(fieldsTable->currentRow());
        fld.type = "";  // пометим колонку к удалению
        fields.removeAt(fieldsTable->currentRow());
        fields.insert(fieldsTable->currentRow(), fld);
        fieldsTable->removeRow(fieldsTable->currentRow());
    }
    fieldsTable->setFocus(Qt::OtherFocusReason);
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


void WizardDictionary::frameActivated(int frameNumber)
{
    if (frameNumber == 2)
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
        for (int i = 0; i < fields.count(); i++)
        {
            for (int j = 0; j < fieldsTable->rowCount(); j++)
            {
                if (fieldsTable->item(j, 5)->text() == "true")
                {
                    if (j < fields.count())
                    {
                        if (QString::compare(fieldsTable->item(j, 0)->text().trimmed(), fields.value(i).name) == 0)
                        {
                            headers->addItem(fieldsTable->item(j, 4)->text());
                        }
                    }
                    else
                    {
                        headers->addItem(fieldsTable->item(j, 4)->text());
                    }
                }
            }
        }
    }
}
