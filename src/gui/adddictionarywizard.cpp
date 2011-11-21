#include <QDebug>
#include <QMap>
#include <QVariant>
#include "adddictionarywizard.h"
#include "../kernel/app.h"
#include "mybuttonlineedit.h"
#include "mybuttonlineedititemdelegate.h"

AddDictionaryWizard::AddDictionaryWizard(bool addDict): WizardForm()
  , tableName(NULL)
  , tableMenuName(NULL)
{
    addDictionary = addDict;
}


bool AddDictionaryWizard::open(QWidget* pwgt, QString t/* = ""*/)
{
    table = t;
    return WizardForm::open(pwgt);
}


void AddDictionaryWizard::initFrames()
{
    // Добавим страницы мастера
    QVBoxLayout* layout = 0;
    layout = new QVBoxLayout();
    // 1-я страница
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
    QLabel* lblTableName = new QLabel(QObject::trUtf8("Наименование на сервере:"), formWidget);
    gridLayout->addWidget(lblTableName, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(tableName, 0, 1, Qt::AlignLeft);

    QLabel* lblMenuTableName = new QLabel(QObject::trUtf8("Наименование в меню:"), formWidget);
    gridLayout->addWidget(lblMenuTableName, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(tableMenuName, 1, 1, Qt::AlignLeft);

    QLabel* lblMenu = new QLabel(QObject::trUtf8("Доступен в меню:"), formWidget);
    chbMenu = new QCheckBox(formWidget);
    gridLayout->addWidget(lblMenu, 2, 0, Qt::AlignRight);
    gridLayout->addWidget(chbMenu, 2, 1, Qt::AlignLeft);
    gridLayout->setColumnStretch(1, 1);

    layout->addLayout(gridLayout);
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


void AddDictionaryWizard::getData()
{
    if (table.size() > 0)
    {   // Если известно, с какой таблицей будем работать
        tableName = new QLineEdit();
        tableName->setText(table);
        tableName->setEnabled(false);
        tableMenuName = new QLineEdit();
        tableMenuName->setText(TApplication::exemplar()->getDictionaries()->getDictionaryTitle(table));
        // Получим список полей таблицы
        TApplication::exemplar()->getDBFactory()->getColumnsProperties(&fields, table);
        // Создадим таблицу столбцов
        fieldsTable = new QTableWidget(fields.count(), 6);
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

        MyButtonLineEditItemDelegate* buttonEditDelegate = new MyButtonLineEditItemDelegate();
        fieldsTable->setItemDelegateForColumn(1, buttonEditDelegate);
        MyBooleanItemDelegate* booleanDelegate = new MyBooleanItemDelegate(formWidget);
        fieldsTable->setItemDelegateForColumn(5, booleanDelegate);

        // Создадим список заголовков столбцов
    }
}


bool AddDictionaryWizard::execute()
{   // Сохранение данных на сервере
    tableName->setText(tableName->text().trimmed());
    tableMenuName->setText(tableMenuName->text().trimmed());
    TApplication::exemplar()->getDBFactory()->beginTransaction();
    if (addDictionary)
    {   // Если нужно, то создадим новый справочник
        if (!TApplication::exemplar()->getDBFactory()->createNewDictionary(tableName->text(),
                                                                           tableMenuName->text(),
                                                                           chbMenu->isChecked()))
        {
            TApplication::exemplar()->getDBFactory()->rollbackTransaction();
            return false;
        }
    }
    // Удалим поля, помеченные к удалению
    int i = 0;
    while (i < fields.count())
    {
        if (fields.value(i).type.size() == 0)
        {
            TApplication::exemplar()->getDBFactory()->dropTableColumn(tableName->text(),
                                                                      fields.value(i).name);
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
        QString type = QString("%1%2").arg(fieldsTable->item(i, 1)->text().trimmed()).arg(length);
        if (i < fields.count())
        {   // Если мы просматриваем поля таблицы, которые уже были
            if (QString::compare(fieldName, fields.value(i).name) != 0)
            {   // Если пользователь изменил наименование поля
                TApplication::exemplar()->getDBFactory()->renameTableColumn(tableName->text(),
                                                                            fields.value(i).name,
                                                                            fieldName);
            }
            if (QString::compare(sType, fields.value(i).type, Qt::CaseInsensitive) != 0 ||
                nLength != fields.value(i).length ||
                nPrecision != fields.value(i).precision)
            {   // Если изменились тип, длина или точность
                TApplication::exemplar()->getDBFactory()->alterTableColumn(tableName->text(),
                                                                           fieldName,
                                                                           type);
            }
            // Проверим, изменил ли пользователь заголовок столбца
            if (QString::compare(sHeader, fields.value(i).header, Qt::CaseSensitive) != 0)
            {
                if (fields.value(i).header.size() > 0)
                {  // Если заголовок для этого столбца уже был
                    TApplication::exemplar()->getDBFactory()->updateColumnHeader(tableName->text(),
                                                                                 fieldName,
                                                                                 sHeader);
                }
                else
                {
                    TApplication::exemplar()->getDBFactory()->appendColumnHeader(tableName->text(),
                                                                                 fieldName,
                                                                                 sHeader);
                }
            }
        }
        else
        {   // Если мы добавляем новые поля
            TApplication::exemplar()->getDBFactory()->addTableColumn(tableName->text(),
                                                                       fieldName,
                                                                       type);
            if (sHeader.size() > 0)
            {
                TApplication::exemplar()->getDBFactory()->appendColumnHeader(tableName->text(),
                                                                             fieldName,
                                                                             sHeader);
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
                     TApplication::exemplar()->getDBFactory()->setTableColumnHeaderOrder(tableName->text(), fieldsTable->item(j, 0)->text(), i + 1);
                }
            }
        }
    }

    TApplication::exemplar()->getDBFactory()->commitTransaction();
    return true;
}


void AddDictionaryWizard::addColumn()
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


void AddDictionaryWizard::deleteColumn()
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


void AddDictionaryWizard::headerUp()
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


void AddDictionaryWizard::headerDown()
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


void AddDictionaryWizard::frameActivated(int frameNumber)
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
