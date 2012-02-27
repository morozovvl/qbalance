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

#include <QModelIndex>
#include "dictionary.h"
#include "saldo.h"
#include "document.h"
#include "../engine/documentscriptengine.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../storage/documenttablemodel.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"


Document::Document(int oper, Documents* par)
: Essence()
, parent(par)
, operNumber(oper)
{
    DbFactory = TApplication::exemplar()->getDBFactory();
    lPrintable = true;
    tableName = DbFactory->getObjectName("проводки");
    tagName = QString("Документ%1").arg(oper);
    formTitle = TApplication::exemplar()->getDBFactory()->getTopersProperties(oper).value(TApplication::nameFieldName()).toString();
    idFieldName = "p1__" + TApplication::idFieldName();
    freePrv = 0;

    dictionaries = new Dictionaries();
    if (dictionaries->open())
    {
        dicts = dictionaries->getDictionaries();
    }

    QList<DictType> dictsList;  // Список справочников, которые будут присутствовать в документе
    DbFactory->getToperData(operNumber, &topersList);
    DbFactory->setToperDictAliases(&topersList, &dictsList);

    // Проверим, должна ли быть в документе только одна строка
    isSingleString = topersList.at(0).isSingleString;

    // Проверим, есть ли в документе "свободная" проводка
    for (int i = 0; i < topersList.count(); i++)
        if (topersList.at(i).freePrv)
        {
            freePrv = topersList.at(i).number;
            break;
        }


    // Создадим локальный для документа список справочников
    Dictionary* dict;
    for (int i = 0; i < dictsList.count(); i++)
    {
        if (dictsList.at(i).isSaldo)
        {
            Saldo* sal;
            if (dictsList.at(i).name.size() > 0 &&
                DbFactory->isSet(dictsList.at(i).name))
                   sal = dictionaries->getSaldo(dictsList.at(i).acc, dictsList.at(i).name, 1);
            else
                sal = dictionaries->getSaldo(dictsList.at(i).acc, dictsList.at(i).name, 0);
            if (sal != 0)
            {
                sal->setPrototypeName(dictsList.at(i).prototype);
                sal->setAutoSelect(true);               // автоматически нажимать кнопку Ok, если выбрана одна позиция
                sal->setQuan(true);
                sal->setConst(dictsList.at(i).isConst);
            }
        }
        else
        {
            if (dictsList.at(i).isConst)
            {
                dict = dictionaries->getDictionary(dictsList.at(i).name, 0);
                if (dict != 0)
                    dict->setConst(true);
            }
            else
                dict = dictionaries->getDictionary(dictsList.at(i).name, 1);
        }
    }

    foreach (QString dictName, dicts->keys())
    {
        dict = dicts->value(dictName);
        if (dict->isConst() || dict->isSet())
            dict->setMustShow(false); // Если справочник документа является постоянным или это набор, то не показывать его при добавлении новой записи в документ
        else
            dict->setMustShow(true);
    }

    QSqlRecord docProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties(tableName);
    lInsertable = docProperties.value("insertable").toBool();
    lDeleteable = docProperties.value("deleteable").toBool();
    lUpdateable = docProperties.value("updateable").toBool();
}

Document::~Document() {
}


bool Document::calculate(const QModelIndex& index) {
    bool lResult = Essence::calculate(index);
    if (lResult) {
        if (freePrv)    // Если есть "свободная" проводка
        {
            ((DocumentScriptEngine*)scriptEngine)->eventAfterCalculate();
            tableModel->submit(tableModel->index(0, 0));
        }
        selectCurrentRow();                     // Обновим содержимое строки
        calcItog();
    }
    else
    {
        if (((DocumentScriptEngine*)scriptEngine)->getScriptResult())
        {
            TApplication::exemplar()->showError(((DocumentScriptEngine*)scriptEngine)->getErrorMessage());
        }
    }
    return lResult;
}


void Document::calcItog()
{
    double itog = 0;
    for (int i = 0; i < topersList.count(); i++)
    {
        QString sign = topersList.at(i).itog;
        if (sign == "+" || sign == "-") {
            double sum = 0;
            int col = tableModel->record().indexOf(QString("p%1__сумма").arg(topersList.at(i).number));
            for (int j = 0; j < tableModel->rowCount(); j++) {
                sum += tableModel->data(tableModel->index(j, col)).toDouble();
            }
            if (sign == "+")
                itog += sum;
            else
                itog -= sum;
        }
    }
    parent->setValue("сумма", itog);
    showItog();
}


void Document::showItog()
{
    MyNumericEdit* itogWidget = (MyNumericEdit*)qFindChild<QLineEdit*>(form->getForm(), "itogNumeric");
    if (itogWidget != 0)
        itogWidget->setValue(parent->getValue("сумма"));
}


bool Document::add()
{
    if (showNextDict())     // Показать все справочники, которые должны быть показаны перед добавлением новой записи
    {
        ((DocumentScriptEngine*)scriptEngine)->eventBeforeAddString();
        appendDocString();
        query();
        form->getGridTable()->selectRow(tableModel->rowCount() - 1);
        ((DocumentScriptEngine*)scriptEngine)->eventAfterAddString();
        return true;
    }
    return false;
}


bool Document::remove() {
    if (lDeleteable) {
        int strNum = getValue("p1__стр").toInt();
        if (Essence::remove()) {
            DbFactory->removeDocStr(docId, strNum);
            query();
            if (tableModel->rowCount() > 0 && freePrv)    // Если есть "свободная" проводка
            {
                ((DocumentScriptEngine*)scriptEngine)->eventAfterCalculate();
                tableModel->submit(tableModel->index(0, 0));
            }
            calcItog();
            return true;
        }
    }
    else
        showError(QString(QObject::trUtf8("Запрещено удалять строки в документах пользователю %2")).arg(TApplication::exemplar()->getLogin()));
    return false;
}


void Document::setValue(QString name, QVariant value, int row)
{   // Функция по-особому обрабатывает "свободные" проводки
    if (name.left(1) == "p")
    {
        int __pos = name.indexOf("__");
        int operNum = name.mid(1, __pos - 1).toInt();
        if (operNum == freePrv)     // Если мы хотим сохранить значение в свободной проводке
            Essence::setValue(name, value, 0);  // Т.к. свободная проводка находится всегда в первой строке документа
        else
            Essence::setValue(name, value, row);
        return;
    }
    Essence::setValue(name, value, row);
}


QVariant Document::getSumValue(QString name)
{
    double sum = 0;
    int col = tableModel->record().indexOf(name);
    for (int j = 0; j < tableModel->rowCount(); j++) {
        sum += tableModel->data(tableModel->index(j, col)).toDouble();
    }
    return QVariant(sum);
}



void Document::show()
{   // Перед открытием документа запрашивается его содержимое, а для постоянных справочников в документе устанавливаются их значения
    query();
    if (tableModel->rowCount() > 0) {
        Dictionary* dict;
        QString dictName;
        for (int i = 0; i < topersList.count(); i++)
        {
            int prvNumber = topersList.at(i).number;
            dictName = topersList.at(i).dbDictAlias;   // Получим имя справочника, который участвует в проводках бух.операции по дебету
            if (dicts->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = dicts->value(dictName);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("p%1__дбкод").arg(prvNumber)).toULongLong());
                }
            }
            dictName = topersList.at(i).crDictAlias;   // то же самое для справочников по кредиту проводок
            if (dicts->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = dicts->value(dictName);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("p%1__кркод").arg(prvNumber)).toULongLong());
                }
            }
        }
    }
    else
    {
        if (getIsSingleString())
        {   // Если в документе должна быть только одна строка, но нет ни одной, то добавим пустую строку
            appendDocString();
            query();
        }
    }
    Essence::show();
    getForm()->createUi();
}


void Document::setConstDictId(QString dName, QVariant id)
{
    if (tableModel->rowCount() > 0) {
        Dictionary* dict;
        QString dictName;
        for (int i = 0; i < topersList.count(); i++)
        {
            dictName = topersList.at(i).dbDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0) {
                dict = dicts->value(dictName);
                if (dict->isConst()) {
                    DbFactory->setConstDictId("дбкод", id, docId, operNumber, topersList.at(i).number);
                    dict->setId(id.toULongLong());
                }
            }
            dictName = topersList.at(i).crDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0) {
                dict = dicts->value(dictName);
                if (dict->isConst()) {
                    DbFactory->setConstDictId("кркод", id, docId, operNumber, topersList.at(i).number);
                    dict->setId(id.toULongLong());
                }
            }
        }
    }
}


bool Document::open()
{
    bool result = false;
    if (Essence::open()) {
        if (scriptEngine != 0)
        {
            result = ((DocumentScriptEngine*)scriptEngine)->open(TApplication::exemplar()->getScriptFileName(operNumber));
            if (result)
                ((DocumentScriptEngine*)scriptEngine)->evaluate();
            form->initFormEvent();
        }
    }
    return result;
}


void Document::close()
{
    foreach(QString dictName, dicts->keys()) {
        Dictionary* dict;
        dict = dicts->value(dictName);
        if (dict != 0)
            dict->close();
    }
    Essence::close();
}


void Document::setForm()
{
    form = new FormDocument();
    form->open(parentForm, (Document*)this);
    if (form->isDefaultForm())
    {
        QPushButton* button;
        button = form->getButtonOk();
        if (button != NULL)
            button->setToolTip(trUtf8("Закрыть документ"));
        button = form->getButtonAdd();
        if (button != NULL)
            button->setToolTip(trUtf8("Добавить строку в документ"));
        button = form->getButtonDelete();
        if (button != NULL)
            button->setToolTip(trUtf8("Удалить строку из документа"));
        button = form->getButtonRequery();
        if (button != NULL)
            button->setToolTip(trUtf8("Обновить документ (загрузить повторно с сервера)"));
        button = form->getButtonPrint();
        if (button != NULL)
            button->setToolTip(trUtf8("Распечатать документ"));
        button = form->getButtonSave();
        if (button != NULL)
            button->setToolTip(trUtf8("Экспорт документа"));
        button = form->getButtonLoad();
        if (button != NULL)
            button->setToolTip(trUtf8("Импорт документа"));
    }
}


void Document::setScriptEngine()
{
    scriptEngine = new DocumentScriptEngine(this);
}


DocumentScriptEngine* Document::getScriptEngine()
{
    return (DocumentScriptEngine*)scriptEngine;
}


QString Document::transformSelectStatement(QString string)
{   // Модифицирует команду SELECT... заменяя пустую секцию WHERE реальным фильтром с номером текущего документа
    // Вызывается перед каждым запросом содержимого табличной части документа
    QString whereClause = QString(" WHERE p%3.доккод=%1 AND p%3.опер=%2 AND p%3.номеропер=%3").arg(docId).arg(operNumber).arg(prv1);
    string.replace(" WHERE", whereClause);
    return string;
}


void Document::setTableModel()
{   // Генерирует заготовку запроса для получения данных для табличной части документа
    // Вызывается 1 раз
    tableModel = new DocumentTableModel();
    tableModel->setParent(this);
    tableModel->setTable(tableName);
    tableModel->setBlockUpdate(!isUpdateable());
    QList<ToperType> topersList;
    selectStatement = DbFactory->getDocumentSqlSelectStatement(operNumber, dictionaries, &topersList, &columnsProperties, &prv1);
    if (selectStatement.size() > 0)
    {
        tableModel->setSelectStatement(selectStatement);
        DbFactory->getColumnsRestrictions(tagName, &columnsProperties);

        // Соберем информацию об обновляемых полях таблицы "проводки"
        QStringList updateFields;
        updateFields << DbFactory->getObjectName("проводки.кол") << DbFactory->getObjectName("проводки.цена") << DbFactory->getObjectName("проводки.сумма");
        int columnCount = 0;
        int keyColumn   = 0;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            QString field = columnsProperties.value(i).name;
            field = field.mid(field.indexOf("__") + 2);
            if (field == DbFactory->getObjectName("проводки.код"))
            {// Если в списке полей встретилось поле ключа
                keyColumn = columnCount;                                    // Запомним номер столбца с ключом
            }
            if (updateFields.contains(field))
            {// Если поле входит в список сохраняемых полей
                tableModel->setUpdateInfo(columnCount, keyColumn, field);   // То сохраним информацию, необходимую для генерации команды сохранения этого поля (номер столбца поля, номер столбца ключа и имя поля)
            }
            columnCount++;      // Считаем столбцы
        }

        // Заполним модель пустыми данными. Это необходимо только в случае, если мы сами генерировали команду запроса для модели.
        int oldDocId = docId;
        docId = 0;
        query();
        docId = oldDocId;
    }
}


bool Document::showNextDict()
{  // функция решает, по каким справочникам нужно пробежаться при добавлении новой строки в документе
    bool anyShown = true;
    foreach (QString dictName, dicts->keys()) {
        Dictionary* dict = dicts->value(dictName);
        if (dict->isMustShow()) {
            dict->exec();
            if (dict->isFormSelected()) {
                if (dict->getTableModel()->rowCount() == 0) {       // Если в выбранном справочнике нет записей
                    anyShown = false;                               // то считать, что этот справочник не был показан и не давать добавить строчку в документ
                    break;
                }
                // Не будем показывать те справочники, у которых прототип совпадает
                foreach (QString dName, dicts->keys())
                {
                    if (dName != dictName &&
                        dict->getPrototypeName().size() > 0 &&
                        (dName == dict->getPrototypeName() ||
                        dicts->value(dName)->getPrototypeName() == dict->getPrototypeName())
                       )
                    {
                            Dictionary* dict = dicts->value(dName);
                            dict->setMustShow(false);
                            // Не будем показывать связанные справочники
                            QStringList fieldList = dict->getFieldsList();
                            for (int i = 0; i < fieldList.count(); i++) {           // Просмотрим список полей
                                QString fieldName = fieldList.at(i).toLower();
                                if (fieldName.left(4) == TApplication::idFieldName() + "_") {        // Если поле ссылается на другую таблицу
                                    Dictionary* dict = dictionaries->getDictionary(fieldName.remove(0, 4), 0, false);
                                    if (dict != 0)
                                        dict->setMustShow(false);
                                }
                            }
                    }
                }
            }
            else {
                anyShown = false;    // пользователь отказался от работы со справочниками. Прекратим процесс добавления записи
                break;
            }
        }
    }
    if (anyShown)
    {
        foreach (QString dictName, dicts->keys())
        {
            Dictionary* dict = dicts->value(dictName);
            if (dict != 0)
            {
                if (dict->isMustShow())
                {
                    foreach (QString dName, dicts->keys())
                    {
                        Dictionary* d = dicts->value(dName);
                        if (d != 0)
                        {
                            if (dName != dictName &&
                                dict->getPrototypeName().size() > 0 &&
                                (dName == dict->getPrototypeName() ||
                                d->getPrototypeName() == dict->getPrototypeName())
                               )
                            {
                                qulonglong id = dict->getId();
                                dicts->value(dName)->setId(id);
                            }
                        }
                    }
                }
            }

        }
    }
    return anyShown;
}


void Document::appendDocString()
{
    Dictionary* dict;
    QString dictName, parameter;
    qulonglong dbId, crId;
    // Просмотрим все проводки типовой операции
    for (int i = 0; i < topersList.count(); i++)
    {
        dbId = 0;
        dictName = topersList.at(i).dbDictAlias;
        if (dictName.size() > 0)    // Если у текущей проводки указан дебетовый справочник
        {
            dict = dicts->value(dictName);
            dbId = dict->getId();   // То получим код текущего значения справочника
        }
        crId = 0;
        dictName = topersList.at(i).crDictAlias;
        if (dictName.size() > 0)    // У текущей проводки указан кредитовый справочник
        {
            dict = dicts->value(dictName);
            crId = dict->getId();   // Получим код текущего значения кредитового справочника
        }
        // Добавим параметры проводки <ДбКод, КрКод, Кол, Цена, Сумма> в список параметров
        parameter.append(QString("%1,%2,").arg(dbId).arg(crId));
        QString value;
        value = prvValues.value(QString("p%1__кол").arg(i+1)).toString();
        parameter.append(value.size() > 0 ? value : "0").append(",");
        value = prvValues.value(QString("p%1__цена").arg(i+1)).toString();
        parameter.append(value.size() > 0 ? value : "0").append(",");
        value = prvValues.value(QString("p%1__сумма").arg(i+1)).toString();
        parameter.append(value.size() > 0 ? value : "0").append(",");
    }
    // Добавим строку в документ с параметрами всех проводок операции
    DbFactory->addDocStr(operNumber, docId, parameter);
    prvValues.clear();
}


void Document::selectCurrentRow()
{   // Делает запрос к БД по одной строке документа. Изменяет в текущей модели поля, которые в БД отличаются от таковых в модели.
    // Применяется после работы формул для изменения полей в строке, которые косвенно изменились (например сальдо).
    QString command = tableModel->getSelectStatement();
    command.replace(" WHERE ", QString(" WHERE p1.стр=%1 AND ").arg(getValue("p1__стр").toInt()));
    QSqlQuery query = TApplication::exemplar()->getDBFactory()->execQuery(command);
    if (query.first())
    {
        for (int i = 0; i < query.record().count(); i++)
        {
            QString fieldName = query.record().fieldName(i);
            QVariant value = query.record().value(fieldName);
            if (value != getValue(fieldName))
                setValue(fieldName, value);
        }
    }
}


void Document::preparePrintValues(ReportScriptEngine* reportEngine)
{
    Essence::preparePrintValues(reportEngine);
    // Зарядим постоянные справочники
    foreach (QString dictName, dicts->keys())
    {
        Dictionary* dict = dicts->value(dictName);
        if (dict->isConst())
        {   // Нам нужны только постоянные справочники
            foreach(QString field, dict->getFieldsList())
            {
                if (field.left(4) != TApplication::exemplar()->getDBFactory()->getIdFieldPrefix())       // Если поле не является ссылкой на другой справочник
                {
                    reportEngine->getReportContext()->setValue(QString("%1.%2").arg(dictName).arg(field), dict->getValue(field));
                }
            }
        }
    }
    // Зарядим реквизиты документа
    QStringList enabledFields;
    enabledFields << "дата" << "датавремя" << "номер" << "комментарий" << "сумма";
    foreach(QString field, getParent()->getFieldsList())
    {
        if (enabledFields.contains(field))
        {
            reportEngine->getReportContext()->setValue(QString("%1.%2").arg(getParent()->getTableName()).arg(field), getParent()->getValue(field));
        }
    }
    // Зарядим таблицу проводок
    enabledFields.clear();
    enabledFields << "кол" << "цена" << "сумма";     // список полей таблицы "проводки", которые актуальны при печати документа
    for (int i = 0; i < getTableModel()->rowCount(); i++)
    {
        QSqlRecord rec = getTableModel()->record(i);
        foreach(QString field, getFieldsList())
        {
            if (field.at(0) == 'p' && field.at(1).isDigit())      // если в списке полей встретилось поле, начинающееся с "p<цифра>...",
            {   // т.е. это поле из таблицы "проводки"
                QString fld = field.section("__", 1);               // проверим, актуально ли это поле для печати
                if (enabledFields.contains(fld))
                {
                    reportEngine->getReportContext()->setValue(QString("таблица%1.%2").arg(i+1).arg(field), rec.value(field));
                }
            }
            else
            {
                reportEngine->getReportContext()->setValue(QString("таблица%1.%2").arg(i+1).arg(field), rec.value(field));
            }
        }
    }
}


