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

#include <QtCore/QModelIndex>
#include <QtGui/QProgressBar>
#include <QtXml/QXmlStreamWriter>
#include <QtXml/QXmlStreamReader>
#include <QDebug>
#include "dictionary.h"
#include "saldo.h"
#include "document.h"
#include "../engine/documentscriptengine.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"


Document::Document(int oper, Documents* par): Essence()
{
    parent = par;
    operNumber = oper;
    lPrintable = true;
    tableName = db->getObjectName("проводки");
    tagName = QString("Документ%1").arg(oper);
    scriptFileName = TApplication::exemplar()->getScriptFileName(operNumber);
    idFieldName = "P1__" + db->getObjectName("код");
    freePrv = 0;
    setDoSubmit(false);                 // По умолчанию не будем обновлять записи в БД сразу, чтобы собрать обновления в транзакцию
    parent->setDoSubmit(true);          // Обновления в списке документов будем сохранять сразу

    // Подготовим структуру для хранения локальных справочников
    dictionaries = new Dictionaries();
    if (dictionaries->open())
    {
        dicts = dictionaries->getDictionaries();
    }
    QList<DictType> dictsList;  // Список справочников, которые будут присутствовать в документе

    db->getToperData(operNumber, &topersList);              // Получим список типовых операций
    db->getToperDictAliases(operNumber, &topersList, &dictsList);       // Получим имена справочников в проводках

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
                db->isSet(dictsList.at(i).name))
                   sal = dictionaries->getSaldo(dictsList.at(i).acc, 1);
            else
                sal = dictionaries->getSaldo(dictsList.at(i).acc, 0);
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
            dict->setPrototypeName(dictsList.at(i).name);
        }
    }

    // Определим, какие справочники показывать при добавлении новой строки в документ, а какие не показывать
    foreach (QString dictName, dicts->keys())
    {
        dict = dicts->value(dictName);
        if (dict->isConst() || dict->isSet() || dict->isDependent())
            dict->setMustShow(false); // Если справочник документа является постоянным или это набор или дочерний (вторичный) справочник,
                                      // то не показывать его при добавлении новой записи в документ
        else
            dict->setMustShow(true);
    }

/*
    QSqlRecord docProperties = db->getDictionariesProperties(tableName);    // просмотрим свойства таблицы "проводки"
    lInsertable = docProperties.value("insertable").toBool();               // можно ли вставлять новые проводки
    lDeleteable = docProperties.value("deleteable").toBool();               // можно ли удалять проводки
    lUpdateable = docProperties.value("updateable").toBool();               // можно ли изменять проводки
*/
    lInsertable = true;
    lDeleteable = true;
    lUpdateable = true;
}

Document::~Document()
{
}


bool Document::calculate(const QModelIndex& index)
{
    if (Essence::calculate(index))
    {   // Если в вычислениях не было ошибки

        ((DocumentScriptEngine*)scriptEngine)->eventAfterCalculate();
        saveChanges();
    }
    else
    {
        ((DocumentScriptEngine*)scriptEngine)->eventAfterCalculate();
        restoreOldValues();
    }
    return true;
}


void Document::saveChanges()
{
    int row = form->getCurrentIndex().row();

    // Начнем транзакцию
    // Сохраним в БД все столбцы. Будут сохраняться только те, в которых произошли изменения
    for (int i = 0; i < tableModel->record().count(); i++)
    {
        QString fieldName = tableModel->record().fieldName(i);
        if (getValue(fieldName) != getOldValue(fieldName))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
        {
            tableModel->submit(tableModel->index(row, i));
        }
    }

    if (freePrv > 0)
    {   // Если существует "свободная" проводка, то сохраним изменения и в ней
        int freePrvRow = findFreePrv();
        if (freePrvRow != row)
        {
            for (int i = 0; i < tableModel->record().count(); i++)
            {
                QString fieldName = tableModel->record().fieldName(i);
                if (getValue(fieldName, freePrvRow) != oldValues0.value(fieldName))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
                {
                    tableModel->submit(tableModel->index(freePrvRow, i));
                }
            }
        }
    }

    calcItog();

    if (db->execCommands())
    {   // Если во время сохранения результатов ошибки не произошло
        // Запросим в БД содержимое текущей строки в документе и обновим содержимое строки в форме (на экране)
        selectCurrentRow();
        saveOldValues();
    }
    else
    {   // Во время сохранения результатов произошла ошибка
        restoreOldValues();
    }
}


void Document::calcItog(bool forceSubmit)
{
    // сохраним те переменные, которые использовались в скриптах
    foreach (QString varName, variables.keys())
    {
        QVariant var = ((DocumentScriptEngine*)scriptEngine)->evaluate(varName).toVariant();
        saveVariable(varName, var);
    }

    double itog = 0;
    for (int i = 0; i < topersList.count(); i++)
    {
        QString sign = topersList.at(i).itog;
        if (sign == "+" || sign == "-")
        {
            double sum = 0;
            int col = tableModel->record().indexOf(QString("P%1__%2").arg(topersList.at(i).number)
                                                                     .arg(db->getObjectName("документы.сумма")));
            for (int j = 0; j < tableModel->rowCount(); j++)
            {
                sum += tableModel->data(tableModel->index(j, col)).toDouble();
            }
            if (sign == "+")
                itog += sum;
            else
                itog -= sum;
        }
    }

    if (forceSubmit)
    {
        parent->setForceSubmit(true);       // Итог документа будем обновлять принудительно, иначе после удаления последней строки в документе
        parent->setValue("сумма", itog);    // итог может быть не корректным
        parent->setForceSubmit(false);
    }
    else
        parent->setValue("сумма", itog);

    showItog();
}


void Document::showItog()
{
    MyNumericEdit* itogWidget = (MyNumericEdit*)qFindChild<QLineEdit*>(form->getForm(), "itogNumeric");
    if (itogWidget != 0)
        itogWidget->setValue(parent->getValue(db->getObjectName("документы.сумма")));
}


bool Document::add()
{
    prvValues.clear();
    if (showNextDict())     // Показать все справочники, которые должны быть показаны перед добавлением новой записи
    {
        scriptEngine->eventBeforeAddString();
        if (topersList.at(0).attributes && topersList.at(0).number == 0)
        {
            QString attrName = QString("%1%2").arg(db->getObjectName("атрибуты")).arg(operNumber);
            QString idFieldName = db->getObjectName("код");
            foreach (QString fieldName, db->getFieldsList(attrName))
            {
                if (fieldName.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    QString dictName = fieldName;
                    dictName.remove(0, 4);
                    prepareValue(fieldName, QVariant(dictionaries->getDictionary(dictName)->getId()));
                }
            }
        }
        appendDocString();
        query();
        form->selectRow(tableModel->rowCount() - 1);            // Установить фокус таблицы на последнюю, только что добавленную, запись

        saveOldValues();

        scriptEngine->eventAfterAddString();

        // Сохраним данные, которые изменились после работы события "EventAfterAddString"
        int row = form->getCurrentIndex().row();
        for (int i = 0; i < tableModel->record().count(); i++)
        {
            QString fieldName = tableModel->record().fieldName(i);
            if (getValue(fieldName) != getOldValue(fieldName))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
            {
                tableModel->submit(tableModel->index(row, i));
            }
        }
        db->execCommands();
        return true;
    }
    return false;
}


int Document::addFromQuery(int id)
{
    QSqlRecord data = db->getDocumentAddQuery(id);
    if (!data.isEmpty())
    {
        QSqlQuery queryData = db->execQuery(data.value(1).toString());
        QProgressBar progressBar(TApplication::exemplar()->getMainWindow());
        progressBar.setMaximum(queryData.size());
        progressBar.show();
        int i = 0;
        while (queryData.next())
        {
            QSqlRecord record = queryData.record();
            ((DocumentScriptEngine*)scriptEngine)->eventAppendFromQuery(data.value(0).toInt(), &record);
            i++;
            progressBar.setValue(i);
        }
        query();
        calcItog();
        return queryData.size();
    }
    return 0;
}


bool Document::remove() {
    if (lDeleteable) {
        int strNum;
        if (topersList.at(0).attributes && topersList.at(0).number == 0)
            strNum = getValue(db->getObjectName("атрибуты.стр")).toInt();
        else
            strNum = getValue(QString("P1__%1").arg(db->getObjectName("проводки.стр"))).toInt();
        if (Essence::remove()) {
            db->removeDocStr(docId, strNum);
            query();
            scriptEngine->eventAfterCalculate();
            calcItog(true);     // Принудительно обновим итог при удалении строки
            return true;
        }
    }
    else
        showError(QString(QObject::trUtf8("Запрещено удалять строки в документах пользователю %2")).arg(TApplication::exemplar()->getLogin()));
    return false;
}


void Document::saveVariable(QString name, QVariant value)
{
    if (variables.contains(name))
        variables.remove(name);
    variables.insert(name, value);
}


QVariant Document::restoreVariable(QString name)
{
    QVariant value(0);
    if (variables.contains(name))
        value = variables.value(name);
    return value;
}


void Document::saveVariablesToDB()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("variables");
    foreach (QString name, variables.keys())
    {
        xmlWriter.writeStartElement("variable");
        xmlWriter.writeAttribute("name", name);
        xmlWriter.writeAttribute("type", QString("%1").arg(variables.value(name).type()));
        xmlWriter.writeAttribute("value", variables.value(name).toString());
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    db->saveDocumentVariables(docId, xml);
}


void Document::restoreVariablesFromDB()
{
    variables.clear();
    QString xml = db->restoreDocumentVariables(docId);
    QXmlStreamReader xmlReader(xml);
    while (!xmlReader.atEnd())
    {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "variable")
        {
            QVariant val(xmlReader.attributes().value("value").toString());
            if (val.convert((QVariant::Type)QString(xmlReader.attributes().value("type").toString()).toInt()))
            {
                variables.insert(xmlReader.attributes().value("name").toString(), val);
            }
        }
        xmlReader.readNext();
    }
}


void Document::setValue(QString name, QVariant value, int row)
{   // Функция по-особому обрабатывает "свободные" проводки
    if (name.left(1) == "P")
    {
        int __pos = name.indexOf("__");
        int operNum = name.mid(1, __pos - 1).toInt();
        if (operNum == freePrv)     // Если мы хотим сохранить значение в свободной проводке
        {
            Essence::setValue(name, value, findFreePrv());
        }
        else
            Essence::setValue(name, value, row);
    }
    else
        Essence::setValue(name, value, row);
}


QVariant Document::getValue(QString name, int row)
{
    if (name.left(1) == "P")
    {
        int __pos = name.indexOf("__");
        int operNum = name.mid(1, __pos - 1).toInt();
        if (operNum == freePrv)     // Если мы хотим сохранить значение в свободной проводке
        {
            return Essence::getValue(name, findFreePrv());
        }
    }
    return Essence::getValue(name, row);
}


int Document::findFreePrv()
{
    QString idFieldName = QString("P%1__%2").arg(freePrv).arg(db->getObjectName("проводки.код"));
    for (int row = 0; row < tableModel->rowCount(); row++)
    {
        if (Essence::getValue(idFieldName, row).toInt() > 0)
            return row;
    }
    return 0;
}


void Document::saveOldValues()
{
    Essence::saveOldValues();
    if (freePrv > 0)
    {  // Если есть "свободная" проводка

        int freePrvRow = findFreePrv();
        oldValues0.clear();
        foreach (QString field, tableModel->getFieldsList())
        {
            oldValues0.insert(field.toUpper(), getValue(field, freePrvRow));
        }
    }
}



void Document::restoreOldValues()
{
    Essence::restoreOldValues();
    if (freePrv > 0)
    {
        foreach (QString fieldName, oldValues0.keys())
            setValue(fieldName, oldValues0.value(fieldName), 0);
    }
}



QVariant Document::getSumValue(QString name)
{   // Возвращает сумму полей <name> всех строк документа
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
                dict->setScriptEngineEnabled(false);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.дбкод"))).toULongLong());
                    showParameterText(dictName);
                }
            }
            dictName = topersList.at(i).crDictAlias;   // то же самое для справочников по кредиту проводок
            if (dicts->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = dicts->value(dictName);
                dict->setScriptEngineEnabled(false);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.кркод"))).toULongLong());
                    showParameterText(dictName);
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
    restoreVariablesFromDB();   // Загрузим переменные для этого экземпляра документа
    parent->saveOldValues();    // Запомним старые значения текущей строки списка документов
    Essence::show();
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
                    db->setConstDictId(db->getObjectName("проводки.дбкод"), id, docId, operNumber, topersList.at(i).number);
                    dict->setId(id.toULongLong());
                }
            }
            dictName = topersList.at(i).crDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0) {
                dict = dicts->value(dictName);
                if (dict->isConst()) {
                    db->setConstDictId(db->getObjectName("проводки.кркод"), id, docId, operNumber, topersList.at(i).number);
                    dict->setId(id.toULongLong());
                }
            }
        }
    }
}


void Document::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->getSelectStatement();
    if (topersList.at(0).attributes && topersList.at(0).number == 0)
    {   // Если в типовой операции нет проводок, а есть только таблица атрибутов
        command.replace(" WHERE ", QString(" WHERE a.%1=:value AND ").arg(db->getObjectName("атрибуты.стр")));
    }
    else
    {
        command.replace(" WHERE ", QString(" WHERE p1.%1=:value AND ").arg(db->getObjectName("проводки.стр")));
    }
    preparedSelectCurrentRow.prepare(command);
}


bool Document::open()
{
    return Essence::open();
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

    // Установим тултипы (подписи к кнопкам)
    form->appendToolTip("buttonOk",     trUtf8("Закрыть документ"));
    form->appendToolTip("buttonAdd",    trUtf8("Добавить строку в документ"));
    form->appendToolTip("buttonQueryAdd", trUtf8("Добавить строки в документ из запроса"));
    form->appendToolTip("buttonDelete", trUtf8("Удалить строку из документа"));
    form->appendToolTip("buttonRequery", trUtf8("Обновить документ (загрузить повторно с сервера)"));
    form->appendToolTip("buttonPrint", trUtf8("Распечатать документ"));
    form->appendToolTip("buutonSave", trUtf8("Экспорт документа"));
    form->appendToolTip("buttonLoad", trUtf8("Импорт документа"));

    form->open(parentForm, (Document*)this, QString("Документ%1").arg(operNumber));
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
    QString whereClause;
    if (string.contains(" WHERE p"))
    {
        whereClause = QString(" WHERE p%3.%4=%1 AND p%3.%5=%2 AND p%3.%6=%3").arg(docId)
                                                                             .arg(operNumber)
                                                                             .arg(prv1)
                                                                             .arg(db->getObjectNameCom("проводки.доккод"))
                                                                             .arg(db->getObjectNameCom("проводки.опер"))
                                                                             .arg(db->getObjectNameCom("проводки.номеропер"));
        string.replace(" WHERE p", whereClause);
    }
    else
    {
        if (string.contains(" WHERE a"))
        {
            whereClause = QString(" WHERE a.%1=%2").arg(db->getObjectNameCom("проводки.доккод"))
                                                   .arg(docId);
            string.replace(" WHERE a", whereClause);
        }
    }
    return string;
}


void Document::setTableModel()
{   // Генерирует заготовку запроса для получения данных для табличной части документа
    // Вызывается 1 раз
    tableModel = new MySqlRelationalTableModel();
    tableModel->setParent(this);
    tableModel->setTable(tableName);
//    tableModel->setReadOnly(!isUpdateable());
    QList<ToperType> topersList;
    selectStatement = db->getDocumentSqlSelectStatement(operNumber, dictionaries, &topersList, &columnsProperties, &prv1);
    if (selectStatement.size() > 0)
    {
        tableModel->setSelectStatement(selectStatement);
        db->getColumnsRestrictions(tagName, &columnsProperties);

        int columnCount = 0;
        int keyColumn   = 0;
        QString attrName = QString("атрибуты%1").arg(operNumber);
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            QString field = columnsProperties.value(i).name;
            if (topersList.at(0).attributes && topersList.at(0).number == 0)
            {
                if (field == db->getObjectName("атрибуты.код").toUpper())
                    // Если в списке полей встретилось поле ключа
                    keyColumn = columnCount;                                    // Запомним номер столбца с ключом
            }
            else
            {
                field = field.mid(field.indexOf("__") + 2);
                if (field == db->getObjectName("проводки.код").toUpper())
                    // Если в списке полей встретилось поле ключа
                    keyColumn = columnCount;                                    // Запомним номер столбца с ключом
            }
            if (!columnsProperties.value(i).constReadOnly)
                // Если поле входит в список сохраняемых полей
                tableModel->setUpdateInfo(columnsProperties.value(i).name, columnsProperties.value(i).table, field, columnCount, keyColumn);
            // Создадим список атрибутов документа, которые могут добавляться при добавлении новой строки документа
            if (columnsProperties.value(i).table == attrName)
                attrFields.append(columnsProperties.value(i).column);
            columnCount++;      // Считаем столбцы
        }
    }
}


bool Document::showNextDict()
{  // функция решает, по каким справочникам нужно пробежаться при добавлении новой строки в документ
    bool anyShown = false;
    Dictionary* dict;
    QString dictName;
    for (int i = 0; i < topersList.count(); i++)
    {
        dictName = topersList.at(i).dbDictAlias;   // Получим имя справочника, который участвует в проводках бух.операции по дебету
        if (dictName.size() > 0 && dicts->contains(dictName))
        {
            dict = dicts->value(dictName);
            if (dict->isMustShow())
            {                       // покажем те справочники, которые можно показывать
                dict->exec();
                if (dict->isFormSelected())
                {               // Если в справочнике была нажата кнопка "Ок"
                    anyShown = true;
                    if (dict->getTableModel()->rowCount() == 0)
                    {       // Если в выбранном справочнике нет записей
                        break;
                    }
                    hideOtherLinkedDicts(dict);     // Скроем все связанные с этим справочником другие справочники и установим для них правильные текущие идентификаторы
                }
                else
                {
                    anyShown = false;
                    break;      // Пользователь отказался от дальнейшей работы со справочниками
                }
            }
            prepareValue(dict->getPrototypeName(), QVariant(dict->getId()));
        }
        dictName = topersList.at(i).crDictAlias;   // то же самое для справочников по кредиту проводок
        if (dictName.size() > 0 && dicts->contains(dictName))
        {
            dict = dicts->value(dictName);
            if (dict->isMustShow())
            {                       // покажем те справочники, которые можно показывать
                dict->exec();
                if (dict->isFormSelected())
                {               // Если в справочнике была нажата кнопка "Ок"
                    anyShown = true;
                    if (dict->getTableModel()->rowCount() == 0)
                    {       // Если в выбранном справочнике нет записей
                        break;
                    }
                    hideOtherLinkedDicts(dict);     // Скроем все связанные с этим справочником другие справочники и установим для них правильные текущие идентификаторы
                }
                else
                {
                    anyShown = false;
                    break;      // Пользователь отказался от дальнейшей работы со справочниками
                }
            }
            prepareValue(dict->getPrototypeName(), QVariant(dict->getId()));
        }
    }
    return anyShown;
}


void Document::prepareValue(QString name, QVariant value)
{
    if (!prvValues.contains(name))
        prvValues.insert(name, value);
}


void Document::hideOtherLinkedDicts(Dictionary* dict)
{
    // Не будем показывать те справочники-прототипы, у которых аналог уже был показан
    foreach (QString dName, dicts->keys())
    {
        if (dName == dict->getPrototypeName())        // Если справочники называются по-разному, но являются прототипами
        {
            Dictionary* d = dicts->value(dName);
            if (d != dict)                              // Исходный справочник трогать нельзя
                d->setMustShow(false);
        }
    }
    // Если это набор или прототип является набором, то не будем показывать связанные справочники
    if (dict->isSet() ||
            (dict->getPrototypeName().size() > 0 && dicts->value(dict->getPrototypeName())->isSet()))
    {
        for (int i = 0; i < dict->getFieldsList().count(); i++)
        {       // Просмотрим список полей
            QString fieldName = dict->getFieldsList().at(i);
            QString name = fieldName;
            if (name.left(4) == dict->getIdFieldName() + "_")
            {        // Если поле ссылается на другую таблицу
                name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                Dictionary* d = dicts->value(name);
                d->setMustShow(false);
                d->setId(dict->getValue(fieldName).toInt());
            }
        }
    }
}


void Document::appendDocString()
{
    QString dictName, parameter;
    qulonglong dbId, crId;
    // Просмотрим все проводки типовой операции
    for (int i = 0; i < topersList.count(); i++)
    {
        dbId = 0;
        crId = 0;
        dictName = topersList.at(i).dbDictAlias;
        if (dictName.size() > 0 && dicts->contains(dictName))
        {
            dbId = prvValues.value(dicts->value(dictName)->getPrototypeName()).toInt();
        }
        dictName = topersList.at(i).crDictAlias;
        if (dictName.size() > 0 && dicts->contains(dictName))
        {
            crId = prvValues.value(dicts->value(dictName)->getPrototypeName()).toInt();
        }
        // Добавим параметры проводки <ДбКод, КрКод, Кол, Цена, Сумма> в список параметров
        parameter.append(QString("%1,%2,0,0,0,").arg(dbId).arg(crId));
/*
        QString value;
        value = prvValues.value(QString("P%1__%2").arg(i+1).arg(db->getObjectName("проводки.кол"))).toString();
        parameter.append(value.size() > 0 ? value : "0").append(",");
        value = prvValues.value(QString("P%1__%2").arg(i+1).arg(db->getObjectName("проводки.цена"))).toString();
        parameter.append(value.size() > 0 ? value : "0").append(",");
        value = prvValues.value(QString("P%1__%2").arg(i+1).arg(db->getObjectName("проводки.сумма"))).toString();
        parameter.append(value.size() > 0 ? value : "0").append(",");
*/
     }
    // Добавим строку в документ с параметрами всех проводок операции
    db->addDocStr(operNumber, docId, parameter);
    foreach (QString attr, attrFields)
    {
        if (prvValues.keys().contains(attr))
        {
            db->saveDocAttribute(operNumber, docId, attr, prvValues.value(attr));
        }
    }
}


void Document::selectCurrentRow()
{   // Делает запрос к БД по одной строке документа. Изменяет в текущей модели поля, которые в БД отличаются от таковых в модели.
    // Применяется после работы формул для изменения полей в строке, которые косвенно изменились (например сальдо).

    if (topersList.at(0).attributes && topersList.at(0).number == 0)
    {   // Если в типовой операции нет проводок, а есть только таблица атрибутов
        preparedSelectCurrentRow.bindValue(":value", getValue(db->getObjectName("атрибуты.стр")).toInt());
    }
    else
    {
        preparedSelectCurrentRow.bindValue(":value", getValue(QString("P1__%1").arg(db->getObjectName("проводки.стр"))).toInt());
    }

    Essence::selectCurrentRow();
}


void Document::preparePrintValues(ReportScriptEngine* reportEngine)
{
    // Зарядим постоянные справочники
    foreach (QString dictName, dicts->keys())
    {
        Dictionary* dict = dicts->value(dictName);
        if (dict->isConst())
        {   // Нам нужны только постоянные справочники
            foreach(QString field, dict->getFieldsList())
            {
                if (field.left(4) != db->getIdFieldPrefix())       // Если поле не является ссылкой на другой справочник
                {
                    reportEngine->getReportContext()->setValue(QString("%1.%2").arg(dictName).arg(field).toLower(), dict->getValue(field));
                }
            }
        }
    }
    // Зарядим реквизиты документа
    QStringList enabledFields;
    enabledFields << db->getObjectName("документы.дата")
                  << db->getObjectName("документы.датавремя")
                  << db->getObjectName("документы.номер")
                  << db->getObjectName("документы.комментарий")
                  << db->getObjectName("документы.сумма");
    foreach(QString field, getParent()->getFieldsList())
    {
        if (enabledFields.contains(field))
        {
            reportEngine->getReportContext()->setValue(QString("документ.%1").arg(field).toLower(), getParent()->getValue(field));
        }
    }

    foreach(QString varName, variables.keys())
    {
        reportEngine->getReportContext()->setValue(QString("документ.%1").arg(varName).toLower(), variables.value(varName));
    }

    Essence::preparePrintValues(reportEngine);
}


void Document::cmdOk()
{
    getParent()->getForm()->setGridFocus();
}


void Document::cmdCancel()
{
    getParent()->getForm()->setGridFocus();
}
