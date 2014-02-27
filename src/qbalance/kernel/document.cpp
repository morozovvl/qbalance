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
#include <QProgressBar>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include "dictionary.h"
#include "saldo.h"
#include "document.h"
#include "../engine/documentscriptengine.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../gui/tableview.h"
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
    localDictsOpened = false;
    docModified = false;
    doSubmit = false;                 // По умолчанию не будем обновлять записи в БД сразу, чтобы собрать обновления в транзакцию

    // Подготовим структуру для хранения локальных справочников
    dictionaries = new Dictionaries();
    if (dictionaries->open())
    {
        dictionaries->setDocument(this);
    }

    topersList = parent->getTopersList();

    // Проверим, должна ли быть в документе только одна строка
    isSingleString = topersList->at(0).isSingleString;

    // Проверим, есть ли в документе "свободная" проводка
    for (int i = 0; i < topersList->count(); i++)
        if (topersList->at(i).freePrv)
        {
            freePrv = topersList->at(i).number;
            break;
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
    isDictionary = false;
}


Document::~Document()
{
}


bool Document::calculate(const QModelIndex& index)
{
    if (!isCurrentCalculate)
    {
        isCurrentCalculate = true;

        if (Essence::calculate(index))
        {   // Если в вычислениях не было ошибки

            calcItog();
            saveChanges();
            docModified = true;
        }
        else
        {
            restoreOldValues();
        }

        isCurrentCalculate = false;
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
        QVariant oldValue = getOldValue(fieldName);
        QVariant newValue = getValue(fieldName);
        if (newValue != oldValue)    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
        {
            tableModel->submit(tableModel->index(row, i));
        }
    }

    if (freePrv > 0)
    {   // Если существует "свободная" проводка, то сохраним изменения и в ней
        int freePrvRow = findFreePrv();
        for (int i = 0; i < tableModel->record().count(); i++)
        {
            QString fieldName = tableModel->record().fieldName(i);
            if (getValue(fieldName, freePrvRow) != oldValues0.value(fieldName))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
            {
                tableModel->submit(tableModel->index(freePrvRow, i));
            }
        }
    }

    row = parent->getForm()->getCurrentIndex().row();
    for (int i = 0; i < parent->getTableModel()->record().count(); i++)
    {
        QString fieldName = parent->getTableModel()->record().fieldName(i);
        QVariant oldValue = parent->getOldValue(fieldName);
        QVariant newValue = parent->getValue(fieldName, row);
        if (newValue != oldValue)    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
        {
            parent->getTableModel()->submit(parent->getTableModel()->index(row, i));
        }
    }

    if (db->execCommands())
    {   // Если во время сохранения результатов ошибки не произошло
        // Запросим в БД содержимое текущей строки в документе и обновим содержимое строки в форме (на экране)
        if (dictionaries->isSaldoExist())
        {
            if (compareSumValues())
                updateCurrentRow();
        }
        saveOldValues();
        parent->saveOldValues();
    }
    else
    {   // Во время сохранения результатов произошла ошибка
        restoreOldValues();
        parent->restoreOldValues();
    }
}


void Document::calcItog()
{
    // сохраним те переменные, которые использовались в скриптах
    foreach (QString varName, variables.keys())
    {
        QVariant var = ((DocumentScriptEngine*)scriptEngine)->evaluate(varName).toVariant();
        saveVariable(varName, var);
    }

    double itog = 0;
    for (int i = 0; i < topersList->count(); i++)
    {
        QString sign = topersList->at(i).itog;
        if (sign == "+" || sign == "-")
        {
            double sum = 0;
            int col = tableModel->record().indexOf(QString("P%1__%2").arg(topersList->at(i).number)
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

    parent->setValue("сумма", itog);    // итог может быть не корректным
    showItog();
}


void Document::showItog()
{
    MyNumericEdit* itogWidget = (MyNumericEdit*)form->getFormWidget()->findChild("itogNumeric");
    if (itogWidget != 0)
        itogWidget->setValue(parent->getValue(db->getObjectName("документы.сумма")));
}


void Document::openLocalDictionaries()
{
    Dictionary* dict;
    QList<DictType> dictsList;
    db->getToperDictAliases(operNumber, topersList, &dictsList);
    // Определим, какие справочники показывать при добавлении новой строки в документ, а какие не показывать
    for (int i = 0; i < dictsList.count(); i++)
    {
        if (dictsList.at(i).isSaldo)
        {
            Saldo* sal;
            sal = dictionaries->getSaldo(dictsList.at(i).acc);
            if (sal != 0)
            {
                sal->setPrototypeName(dictsList.at(i).prototype);
                sal->setAutoSelect(true);               // автоматически нажимать кнопку Ok, если выбрана одна позиция
                sal->setQuan(true);
                sal->setConst(dictsList.at(i).isConst);
                if (sal->isConst() || sal->isSet())
                    sal->setMustShow(false); // Если справочник документа является постоянным или это набор
                                              // то не показывать его при добавлении новой записи в документ
                else
                    sal->setMustShow(true);
            }
        }
        else
        {
            dict = dictionaries->getDictionary(dictsList.at(i).name, 1);
            if (dict != 0)
            {
                if (!dict->isConst())
                {
                   dict->setPrototypeName(dictsList.at(i).name);
                   if (dict->isSet())
                       dict->setMustShow(false); // Если справочник документа является набором
                                                // то не показывать его при добавлении новой записи в документ
                   else
                       dict->setMustShow(true);
                }
                else
                    dict->setMustShow(false);                   // Сначала сделаем невидимым при добавлении проводки сам справочник
            }
        }
    }
    // Установим "родителей" локальных справочников
    for (int i = 0; i < dictsList.count(); i++)
    {
        if (!dictsList.at(i).isSaldo)
        {
            dict = dictionaries->getDictionary(dictsList.at(i).name);
            if (dict->isSet())
            {
                foreach (QString dictName, dict->getChildDicts())
                {
                    Dictionary* childDict = dictionaries->getDictionary(dictName);
                    if (childDict != 0)
                        childDict->setParentDict(dict);
                }
            }
        }
    }
}


bool Document::add()
{
    prvValues.clear();

    if (!getIsSingleString())
    {
        foreach (QString dictName, dictionaries->getDictionaries()->keys())
        {
            Dictionary* dict = dictionaries->getDictionary(dictName);
            if (dict->isConst() && dict->getId() == 0)
            {
                app->showError(QString(QObject::trUtf8("Не определено значение постоянного справочника \"%1\"")).arg(dictName));
                return false;
            }
        }
    }

    if (showNextDict())     // Показать все справочники, которые должны быть показаны перед добавлением новой записи
    {
        scriptEngine->eventBeforeAddString();
        if (topersList->at(0).attributes && topersList->at(0).number == 0)
        {
            QString attrName = QString("%1%2").arg(db->getObjectName("атрибуты")).arg(operNumber);
            QString idFieldName = db->getObjectName("код");
            foreach (QString fieldName, db->getFieldsList(attrName))
            {
                if (fieldName.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    QString dictName = fieldName;
                    dictName.remove(0, 4);
                    if (!prepareValue(fieldName, dictionaries->getDictionary(dictName)))
                        return false;
                }
            }
        }

        for (int i = 0; i < topersList->count(); i++)
        {
            QString dictName = topersList->at(i).dbDictAlias;
            if (dictName.size() > 0 && getDictionaries()->contains(dictName))
            {
                prepareValue(dictName, dictionaries->getDictionary(dictName));
                dictName = dictionaries->getDictionary(dictName)->getPrototypeName();
                prepareValue(dictName, dictionaries->getDictionary(dictName));
            }
            dictName = topersList->at(i).crDictAlias;
            if (dictName.size() > 0 && getDictionaries()->contains(dictName))
            {
                prepareValue(dictName, dictionaries->getDictionary(dictName));
                dictName = dictionaries->getDictionary(dictName)->getPrototypeName();
                prepareValue(dictName, dictionaries->getDictionary(dictName));
            }
         }

       int strNum = appendDocString();

        if (strNum > 0)
        {

            int newRow = tableModel->rowCount();
            if (newRow == 0)
            {
                query();
                form->selectRow(0);            // Установить фокус таблицы на последнюю, только что добавленную, запись
            }
            else
            {
                tableModel->insertRow(newRow);
                form->getGridTable()->reset();
                form->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
                updateCurrentRow(strNum);
            }


            if (getScriptEngine() != 0)
            {
                getScriptEngine()->eventAfterAddString();
                saveChanges();
            }

            return true;
        }
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


bool Document::remove()
{
    if (lDeleteable)
    {
        scriptEngine->eventBeforeDeleteString();
        int strNum = getValue(QString("P1__%1").arg(db->getObjectName("проводки.стр"))).toInt();
        if (Essence::remove())
        {
            if (db->removeDocStr(docId, strNum))
            {
                query();
                calcItog();
                scriptEngine->eventAfterDeleteString();
                saveChanges();     // Принудительно обновим итог при удалении строки
                return true;
            }
            app->getGUIFactory()->showError(QString(QObject::trUtf8("Не удалось удалить строку")));
        }
    }
    else
        app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено удалять строки в документах пользователю %2")).arg(app->getLogin()));
    return false;
}


void Document::saveVariable(QString n, QVariant value)
{
    QString name = n.toUpper();
    if (variables.contains(name))
        variables.remove(name);
    variables.insert(name, value);
}


QVariant Document::restoreVariable(QString n)
{
    QString name = n.toUpper();
    QVariant value(0);
    if (variables.contains(name))
        value = variables.value(name);
    return value;
}


void Document::saveVariablesToDB()
{
    if (variables.size() > 0)
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
}


void Document::restoreVariablesFromDB()
{
    variables.clear();
    QString xml = db->restoreDocumentVariables(docId);
    if (xml.size() > 0)
    {
        QXmlStreamReader xmlReader(xml);
        while (!xmlReader.atEnd())
        {
            if (xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "variable")
            {
                QVariant val(xmlReader.attributes().value("value").toString());
                if (val.convert((QVariant::Type)QString(xmlReader.attributes().value("type").toString()).toInt()))
                {
                    variables.insert(xmlReader.attributes().value("name").toString().toUpper(), val);
                }
            }
            xmlReader.readNext();
        }
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
    QVariant result;
    if (name.left(1) == "P")
    {
        int __pos = name.indexOf("__");
        int operNum = name.mid(1, __pos - 1).toInt();
        if (operNum == freePrv)     // Если мы хотим получить значение из свободной проводки
        {
            result = Essence::getValue(name, findFreePrv());
        }
        else
            result = Essence::getValue(name, row);
    }
    else
        result = Essence::getValue(name, row);
    return result;
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
    parent->saveOldValues();
}


void Document::restoreOldValues()
{
    Essence::restoreOldValues();
    if (freePrv > 0)
    {
        foreach (QString fieldName, oldValues0.keys())
            setValue(fieldName, oldValues0.value(fieldName), 0);
    }
    parent->restoreOldValues();
}


bool Document::compareSumValues()
{
    for (int i = 0; i < topersList->count(); i++)
    {
        QString field = QString("P%1__%2").arg(topersList->at(i).number)
                                          .arg(db->getObjectName("документы.сумма"));
        QVariant oldValue = oldValues.value(field);
        QVariant newValue = getValue(field);
        if (newValue != oldValue)
            return true;
    }
    return false;
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
{
    docModified = false;
    loadDocument();
    Essence::show();
}


void Document::loadDocument()
{   // Перед открытием документа запрашивается его содержимое, а для постоянных справочников в документе устанавливаются их значения
    if (!localDictsOpened)
    {
        openLocalDictionaries();
        localDictsOpened = true;
    }
    query();
    if (tableModel->rowCount() > 0) {
        Dictionary* dict;
        QString dictName;
        QString idFieldName = db->getObjectName("код");
        // Установим значения постоянных справочников, участвующих в проводках
        for (int i = 0; i < topersList->count(); i++)
        {
            int prvNumber = topersList->at(i).number;
            dictName = topersList->at(i).dbDictAlias;   // Получим имя справочника, который участвует в проводках бух.операции по дебету
            if (getDictionaries()->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = getDictionaries()->value(dictName);
                dict->setScriptEngineEnabled(false);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.дбкод")), 0).toULongLong();
                    if (val > 0)
                    {
                        dict->setId(val);
                        showParameterText(dictName);
                    }
                }
                // Проверим связанные справочники этого справочника, если он набор
                foreach (QString dictName, dict->getChildDicts())
                {
                    Dictionary* childDict = getDictionaries()->value(dictName);
                    if (childDict != 0)
                    {
                        if (childDict->isConst())
                        {
                            // Установим сначала значение основного справочника
                            qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.дбкод")), 0).toULongLong();
                            if (val > 0)
                            {
                                dict->setId(val);
                                // А затем установим значение связанного справочника
                                val = dict->getValue(QString("%1_%2").arg(idFieldName).arg(dictName).toUpper(), 0).toULongLong();
                                if (val > 0)
                                {
                                    childDict->setId(val);
                                    showParameterText(dictName);
                                }
                            }
                        }
                    }
                }
            }
            dictName = topersList->at(i).crDictAlias;   // то же самое для справочников по кредиту проводок
            if (getDictionaries()->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = getDictionaries()->value(dictName);
                dict->setScriptEngineEnabled(false);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.кркод")), 0).toULongLong();
                    if (val > 0)
                    {
                        dict->setId(val);
                        showParameterText(dictName);
                    }
                }
                // Проверим связанные справочники этого справочника, если он набор
                foreach (QString dictName, dict->getChildDicts())
                {
                    Dictionary* childDict = getDictionaries()->value(dictName);
                    if (childDict->isConst())
                    {
                        // Установим сначала значение основного справочника
                        qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.кркод")), 0).toULongLong();
                        if (val > 0)
                        {
                            dict->setId(val);
                            // А затем установим значение связанного справочника
                            val = dict->getValue(QString("%1_%2").arg(idFieldName).arg(dictName).toUpper(), 0).toULongLong();
                            if (val > 0)
                            {
                                childDict->setId(val);
                                showParameterText(dictName);
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (getIsSingleString())
        {   // Если в документе должна быть только одна строка, но нет ни одной, то добавим пустую строку
            add();
        }
    }
    restoreVariablesFromDB();   // Загрузим переменные для этого экземпляра документа
    parent->saveOldValues();    // Запомним старые значения текущей строки списка документов
}


void Document::setConstDictId(QString dName, QVariant id)
{
    if (tableModel->rowCount() > 0)
    {
        int currentRow = form->getGridTable()->currentIndex().row();
        bool submit = doSubmit;
        doSubmit = true;
        Dictionary* dict;
        QString dictName;
        for (int i = 0; i < topersList->count(); i++)
        {
            dictName = topersList->at(i).dbDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0)
            {
                dict = getDictionaries()->value(dictName);
                if (dict->isConst())
                {
                    db->setConstDictId(db->getObjectName("проводки.дбкод"), id, docId, operNumber, topersList->at(i).number);
                    for (int r = 0; r < tableModel->rowCount(); r++)
                    {
                        setValue(QString("P%1__%2").arg(topersList->at(i).number).arg(db->getObjectName("проводки.дбкод")), id, r);
                    }
                }
            }
            else
            {
                // Если справочник, в котором мы устанавливаем идентификатор, является постоянным
                // и у него имеется "родитель"-набор, который задействован в проводке
                Dictionary* constDict = getDictionaries()->value(dName);
                if (constDict->isConst())
                {
                    Dictionary* parentDict = constDict->getParentDict();
                    if (parentDict != 0 && parentDict->getPrototypeName() == dictName)
                    {
                        constDict->setIdEnabled(false);
                        dict = getDictionaries()->value(dictName);
                        for (int r = 0; r < tableModel->rowCount(); r++)
                        {
                            qulonglong id = getValue(QString("P%1__%2").arg(topersList->at(i).number).arg(db->getObjectName("проводки.дбкод")), r).toULongLong();
                            dict->setId(id);
                            id = dict->getId();
                            setValue(QString("P%1__%2").arg(topersList->at(i).number).arg(db->getObjectName("проводки.дбкод")), id, r);
                        }
                        constDict->setIdEnabled(true);
                    }
                }
            }
            dictName = topersList->at(i).crDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0)
            {
                dict = getDictionaries()->value(dictName);
                if (dict->isConst())
                {
                    db->setConstDictId(db->getObjectName("проводки.кркод"), id, docId, operNumber, topersList->at(i).number);
                    for (int r = 0; r < tableModel->rowCount(); r++)
                    {
                        setValue(QString("P%1__%2").arg(topersList->at(i).number).arg(db->getObjectName("проводки.кркод")), id, r);
                    }
                }
            }
            else
            {
                // Если справочник, в котором мы устанавливаем идентификатор, является постоянным
                // и у него имеется "родитель"-набор, который задействован в проводке
                Dictionary* constDict = getDictionaries()->value(dName);
                if (constDict->isConst())
                {
                    Dictionary* parentDict = constDict->getParentDict();
                    if (parentDict != 0 && parentDict->getPrototypeName() == dictName)
                    {
                        constDict->setIdEnabled(false);
                        dict = getDictionaries()->value(dictName);
                        for (int r = 0; r < tableModel->rowCount(); r++)
                        {
                            qulonglong id = getValue(QString("P%1__%2").arg(topersList->at(i).number).arg(db->getObjectName("проводки.кркод")), r).toULongLong();
                            dict->setId(id);
                            id = dict->getId();
                            setValue(QString("P%1__%2").arg(topersList->at(i).number).arg(db->getObjectName("проводки.кркод")), id, r);
                        }
                        constDict->setIdEnabled(true);
                    }
                }
            }
        }
        db->execCommands();
        doSubmit = submit;
        query();
        form->selectRow(currentRow);
        form->getGridTable()->setFocus();
        saveOldValues();
    }
}


void Document::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->selectStatement();
    if (topersList->at(0).attributes && topersList->at(0).number == 0)
    {   // Если в типовой операции нет проводок, а есть только таблица атрибутов
        command.replace(" WHERE ", QString(" WHERE a.%1=:value AND ").arg(db->getObjectNameCom("атрибуты.стр")));
    }
    else
    {
        command.replace(" WHERE ", QString(" WHERE p1.%1=:str AND ").arg(db->getObjectNameCom("проводки.стр")));
    }
    preparedSelectCurrentRow.prepare(command);
}


bool Document::open()
{
    if (operNumber > 0 && Essence::open())
    {
        initForm();
        evaluateEngine();
        initFormEvent(form);

        return true;
    }
    return false;
}


void Document::close()
{
    dictionaries->close();
    delete dictionaries;
    Essence::close();
}


void Document::setForm(QString formName)
{
    if (form != 0)
    {
        form->close();
        delete form;
    }

    form = new FormDocument();

    // Установим тултипы (подписи к кнопкам)
    form->appendToolTip("buttonOk",     trUtf8("Закрыть документ"));
    form->appendToolTip("buttonAdd",    trUtf8("Добавить строку в документ"));
    form->appendToolTip("buttonQueryAdd", trUtf8("Добавить строки в документ из запроса"));
    form->appendToolTip("buttonDelete", trUtf8("Удалить строку из документа"));
    form->appendToolTip("buttonRequery", trUtf8("Обновить документ (загрузить повторно с сервера)"));
    if (isPrintable())
        form->appendToolTip("buttonPrint", trUtf8("Распечатать документ"));
    form->appendToolTip("buttonSave", trUtf8("Экспорт документа"));
    form->appendToolTip("buttonLoad", trUtf8("Импорт документа"));

    form->open(parentForm, (Document*)this, formName.size() == 0 ? QString("Документ%1").arg(operNumber) : formName);
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
    if (string.contains(" WHERE p)"))
    {
        whereClause = QString(" WHERE p%3.%4=%1 AND p%3.%5=%2 AND p%3.%6=%3)").arg(docId)
                                                                             .arg(operNumber)
                                                                             .arg(prv1)
                                                                             .arg(db->getObjectNameCom("проводки.доккод"))
                                                                             .arg(db->getObjectNameCom("проводки.опер"))
                                                                             .arg(db->getObjectNameCom("проводки.номеропер"));
        string.replace(" WHERE p)", whereClause);
    }
    else
    {
        if (string.contains(" WHERE a)"))
        {
            whereClause = QString(" WHERE a.%1=%2)").arg(db->getObjectNameCom("проводки.доккод"))
                                                   .arg(docId);
            string.replace(" WHERE a)", whereClause);
        }
    }
    return string;
}


bool Document::setTableModel(int)
{   // Генерирует заготовку запроса для получения данных для табличной части документа
    // Вызывается 1 раз
    tableModel = new MySqlRelationalTableModel(tableName, this);
    selectStatement = db->getDocumentSqlSelectStatement(operNumber, topersList, &columnsProperties, &prv1);
    if (columnsProperties.size() > 0)
    {
        tableModel->setSelectStatement(selectStatement);
        db->getColumnsRestrictions(tagName, &columnsProperties);

        // Откроем постоянные справочники
        Dictionary* dict;
        QList<DictType> dictsList;
        db->getToperDictAliases(operNumber, topersList, &dictsList);
        for (int i = 0; i < dictsList.count(); i++)
        {
            if (dictsList.at(i).isConst)
            {
                dict = dictionaries->getDictionary(dictsList.at(i).name, 0);
                if (dict != 0)
                {
                    dict->setConst(true);
                    dict->setMustShow(false); // Если справочник документа является постоянным или это набор
                }
            }
        }

        int columnCount = 0;
        int keyColumn   = 0;
        QString attrName = QString("атрибуты%1").arg(operNumber);
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            QString field = columnsProperties.value(i).name;
            if (topersList->at(0).attributes && topersList->at(0).number == 0)
            {
                if (field == db->getObjectName("атрибуты.код").toUpper())
                    // Если в списке полей встретилось поле ключа
                    keyColumn = columnCount;                                    // Запомним номер столбца с ключом
            }
            else
            {
                if (field.contains("__"))
                    field = field.mid(field.indexOf("__") + 2);
                if (field == db->getObjectName("проводки.код").toUpper())
                    // Если в списке полей встретилось поле ключа
                    keyColumn = columnCount;                                    // Запомним номер столбца с ключом
            }
            if (!columnsProperties.value(i).constReadOnly)
                // Если поле входит в список сохраняемых полей
                tableModel->setUpdateInfo(columnsProperties.value(i).name, columnsProperties.value(i).table, field, columnsProperties.value(i).type, columnsProperties.value(i).length, columnCount, keyColumn);
            // Создадим список атрибутов документа, которые могут добавляться при добавлении новой строки документа
            if (columnsProperties.value(i).table == attrName)
                attrFields.append(columnsProperties.value(i).column);
            columnCount++;      // Считаем столбцы
        }
        return true;
    }
    app->showError(QString(QObject::trUtf8("Не существует таблица %1")).arg(tableName));
    return false;
}


bool Document::showNextDict()
{  // функция решает, по каким справочникам нужно пробежаться при добавлении новой строки в документ
    bool anyShown = true;
    Dictionary* dict;
    foreach (QString dictName, getDictionaries()->keys())
    {
        dict = getDictionaries()->value(dictName);
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
                prepareValue(dictName, dict);
                prepareValue(dict->getPrototypeName(), dict);
            }
            else
            {
                anyShown = false;
                break;      // Пользователь отказался от дальнейшей работы со справочниками
            }
        }
    }
    return anyShown;
}


bool Document::prepareValue(QString name, Dictionary* dict)
{
    if (!prvValues.contains(name))
    {
        qulonglong id = dict->getId();
        if (id != 0)
        {
            prvValues.insert(name, QVariant(id));
            return true;
        }
    }
    return false;
}


int Document::appendDocString()
{
    int result = 0;
    QString dictName, parameter;
    qulonglong dbId, crId;
    // Просмотрим все проводки типовой операции
    for (int i = 0; i < topersList->count(); i++)
    {
        dbId = 0;
        crId = 0;
        dictName = topersList->at(i).dbDictAlias;
        if (dictName.size() > 0)
        {
            dbId = prvValues.value(dictName).toInt();
            if (dbId == 0 && !getIsSingleString())
                return result;
        }
        dictName = topersList->at(i).crDictAlias;
        if (dictName.size() > 0)
        {
            crId = prvValues.value(dictName).toInt();
            if (crId == 0 && !getIsSingleString())
                return result;
        }
        // Добавим параметры проводки <ДбКод, КрКод, Кол, Цена, Сумма> в список параметров
        parameter.append(QString("%1,%2,0,0,0,").arg(dbId).arg(crId));
     }
    // Добавим строку в документ с параметрами всех проводок операции
    result = db->addDocStr(operNumber, docId, parameter);
    foreach (QString attr, attrFields)
    {
        if (prvValues.keys().contains(attr))
        {
            db->saveDocAttribute(operNumber, docId, attr, prvValues.value(attr));
        }
    }
    return result;
}


void Document::updateCurrentRow(int strNum)
{   // Делает запрос к БД по одной строке документа. Изменяет в текущей модели поля, которые в БД отличаются от таковых в модели.
    // Применяется после работы формул для изменения полей в строке, которые косвенно изменились (например сальдо).

    if (topersList->at(0).attributes && topersList->at(0).number == 0)
    {   // Если в типовой операции нет проводок, а есть только таблица атрибутов
        preparedSelectCurrentRow.bindValue(":value", getValue(db->getObjectName("атрибуты.стр")).toInt());
    }
    else
    {
        int str = strNum == 0 ? getValue(QString("P1__%1").arg(db->getObjectName("проводки.стр"))).toInt() : strNum;
        preparedSelectCurrentRow.bindValue(":str", str);
    }

    Essence::updateCurrentRow();
}


void Document::preparePrintValues(ReportScriptEngine* reportEngine)
{
    // Зарядим постоянные справочники
    foreach (QString dictName, getDictionaries()->keys())
    {
        Dictionary* dict = getDictionaries()->value(dictName);
        if (dict->isConst())
        {   // Нам нужны только постоянные справочники
            QString idFieldName = db->getObjectName("код") + "_";
            foreach(QString field, dict->getFieldsList())
            {
                if (field.left(4) != idFieldName)       // Если поле не является ссылкой на другой справочник
                {
                    reportEngine->getReportContext()->setValue(QString("%1.%2").arg(dictName).arg(field).toLower(), dict->getValue(field));
                }
            }
        }
    }
    // Зарядим реквизиты документа
    foreach(QString field, getParent()->getFieldsList())
    {
        QVariant value = getParent()->getValue(field);
        QString fieldName = field;
        if (fieldName.contains(getParent()->getAttrPrefix()))
            fieldName.remove(getParent()->getAttrPrefix());
        reportEngine->getReportContext()->setValue(QString("документ.%1").arg(fieldName).toLower(), value);
    }

    foreach(QString varName, variables.keys())
    {
        reportEngine->getReportContext()->setValue(QString("документ.%1").arg(varName).toLower(), variables.value(varName));
    }

    Essence::preparePrintValues(reportEngine);
}


void Document::cmdOk()
{
    saveChanges();
}


void Document::cmdCancel()
{
    db->clearCommands();        // Отменим все изменения
    restoreOldValues();         // Восстановим старые значения
}


void Document::setEnabled(bool en)
{
    Essence::setEnabled(en);
    form->setEnabled(en);
}
