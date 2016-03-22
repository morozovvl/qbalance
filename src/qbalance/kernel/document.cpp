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
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QDebug>
#include "dictionary.h"
#include "saldo.h"
#include "document.h"
#include "../engine/documentscriptengine.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../gui/searchparameters.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"
#include "../gui/myprogressdialog.h"


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
    photoEnabled = false;
    quanAccount = false;
    singlePrv = false;
    locked = false;

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
    {
        if (topersList->at(i).freePrv)
        {
            freePrv = topersList->at(i).number;
            break;
        }
    }

    // Проверим есть ли количественный учет
    for (int i = 0; i < topersList->count(); i++)
    {
        if (topersList->at(i).dbQuan || topersList->at(i).crQuan)
            quanAccount = true;                     // Используется количественный учет
    }

    lInsertable = true;
    lDeleteable = true;
    lUpdateable = true;
    isDictionary = false;
    lIsDocument = true;
    addingFromQuery = false;
}


Document::~Document()
{
}


bool Document::calculate()
{
    if (!isCurrentCalculate && enabled)             // Если это не повторный вход в функцию и разрешено редактирование документа
    {
        isCurrentCalculate = true;
        if (Essence::calculate())
        {   // Если в вычислениях не было ошибки

            int row = getCurrentRow();
            // Начнем транзакцию
            // Сохраним в БД все столбцы. Будут сохраняться только те, в которых произошли изменения
            for (int i = 0; i < tableModel->record().count(); i++)
            {
                QString fieldName = tableModel->record().fieldName(i);
                QVariant oldValue = getOldValue(fieldName);
                QVariant newValue = getValue(fieldName);
                if (newValue != oldValue)    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
                    tableModel->submit(tableModel->index(row, i));
            }

            if (freePrv > 0)
            {   // Если существует "свободная" проводка, то сохраним изменения и в ней
                int freePrvRow = findFreePrv();
                for (int i = 0; i < tableModel->record().count(); i++)
                {
                    QString fieldName = tableModel->record().fieldName(i);
                    if (getValue(fieldName, freePrvRow) != oldValues0.value(fieldName))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
                        tableModel->submit(tableModel->index(freePrvRow, i));
                }
            }

            row = parent->getGrdTable()->currentIndex().row();
            for (int i = 0; i < parent->getTableModel()->record().count(); i++)
            {
                QString fieldName = parent->getTableModel()->record().fieldName(i);
                QVariant oldValue = parent->getOldValue(fieldName);
                QVariant newValue = parent->getValue(fieldName, row);
                if (newValue != oldValue)    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
                    parent->getTableModel()->submit(parent->getTableModel()->index(row, i));
            }
            calcItog();
            saveChanges();
            docModified = true;
        }
        else
        {
            db->clearCommands();
            restoreOldValues();
        }

        isCurrentCalculate = false;
    }
    return true;
}


void Document::saveChanges()
{
    if (form->getSubWindow()->widget()->isActiveWindow())
    {
        getParent()->setValue("ДАТА", QVariant(((FormDocument*)form)->getDateEdit()->date()));
        getParent()->setValue("НОМЕР", QVariant(((FormDocument*)form)->getNumberEdit()->text()));
    }
    QModelIndex index = getCurrentIndex();
    if (db->execCommands())
    {   // Если во время сохранения результатов ошибки не произошло
        // Запросим в БД содержимое текущей строки в документе и обновим содержимое строки в форме (на экране)
        updateCurrentRow();
        parent->updateCurrentRow();
    }
    else
    {   // Во время сохранения результатов произошла ошибка
        restoreOldValues();
        parent->restoreOldValues();
    }
    setCurrentIndex(index);
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

    parent->setValue("СУММА", itog);    // итог может быть не корректным
    showItog();
}


void Document::showItog()
{
    MyNumericEdit* itogWidget = (MyNumericEdit*)form->getFormWidget()->findChild("itogNumeric");
    if (itogWidget != 0)
        itogWidget->setValue(parent->getValue(db->getObjectName("документы.сумма")));
}


bool Document::add()
{
    bool result = false;

    if (getIsSingleString())
        result = true;
    else
    {
        if (checkConstDicts())
        {
            result = true;

            if (scriptEngineEnabled && scriptEngine != 0)
                result = scriptEngine->eventBeforeAddString();

            if (result)
                result = showNextDict();
            else
                result = false;
        }
    }

    if (result)
    {
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
        appendDocString();
        setCurrentRow(tableModel->rowCount());
    }
    return result;
}


int Document::addFromQuery(QString queryName)
{
    if (queryName.size() > 0 && checkConstDicts())
    {
        QSqlRecord record;
        QSqlQuery queryData;
        if (db->getDictionariesProperties(queryName).value(db->getObjectName("доступ_к_справочникам.меню")).toBool())
        {
            Dictionary* dict = app->getDictionaries()->getDictionary(queryName);
            if (dict != 0)
            {
                dict->exec();
                if (dict->isFormSelected())
                {
                    queryData = dict->getTableModel()->query();
                }
                else
                    return 0;       // Пользователь решил выйти
            }
        }
        if (!queryData.first())
        {
            if (db->isTableExists(queryName))
            {
                queryData = db->execQuery(QString("SELECT * FROM %1;").arg(queryName));
            }
        }
        if (queryData.first())
        {
            addingFromQuery = true;
            MyProgressDialog* progressDialog;
            progressDialog = app->getMyProgressDialog(trUtf8("Ожидайте окончания работы запроса..."));
            progressDialog->resize(600, progressDialog->height());
            progressDialog->setMaximum(queryData.size());
            progressDialog->show();

            int i = 0;
            db->beginTransaction();
            do {
                record = queryData.record();
                ((DocumentScriptEngine*)scriptEngine)->eventAppendFromQuery(queryName, &record);
                i++;
                progressDialog->setValue(i);
            } while (queryData.next());
            calcItog();
            saveChanges();
            db->commitTransaction();
            progressDialog->hide();
            delete progressDialog;
            query();
            addingFromQuery = false;
            return queryData.size();
        }
        else
            ((DocumentScriptEngine*)scriptEngine)->eventAppendFromQuery(queryName, &record);
    }
    return 0;
}


void Document::load()
{
    if (checkConstDicts())
        Essence::load();
}


bool Document::checkConstDicts()
{
    foreach (QString dictName, getDictionariesList()->keys())
    {
        Dictionary* dict = getDictionary(dictName);
        if (dict->isConst())
        {
            if (dictName.left(9) == "документы" && dictName.size() > 9)
                dict->setId(getParent()->getId());
            if (dict->getId() == 0 && dict->getExact())
            {
                if (!getIsSingleString())
                {
                    app->showError(QString(QObject::trUtf8("Не определено значение постоянного справочника \"%1\"")).arg(dictName));
                    return false;
                }
            }
        }
    }
    return true;
}


bool Document::remove(bool noAsk)
{
    if (lDeleteable)
    {
        if (scriptEngineEnabled && scriptEngine != 0)
            scriptEngine->eventBeforeDeleteString();

        int strNum = getValue(QString("P1__%1").arg(db->getObjectName("проводки.стр"))).toInt();
        if (Essence::remove(noAsk))
        {
            if (db->removeDocStr(docId, strNum))
            {
                query();
                calcItog();

                if (scriptEngineEnabled && scriptEngine != 0)
                    scriptEngine->eventAfterDeleteString();

                saveChanges();     // Принудительно обновим итог при удалении строки
                return true;
            }
            app->showError(QString(QObject::trUtf8("Не удалось удалить строку")));
        }
    }
    else
        app->showError(QString(QObject::trUtf8("Запрещено удалять строки в документах пользователю %2")).arg(app->getLogin()));
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
//            Essence::setValue(name, value, findFreePrv());
            QString fieldName = name.mid(__pos + 2);
            QString command = QString("UPDATE проводки SET %1 = %2 WHERE ДОККОД = %3 AND НОМЕРОПЕР = %4;").arg(fieldName).arg(value.toString()).arg(getDocId()).arg(freePrv);
            db->exec(command);
        }
        else
            Essence::setValue(name, value, row);
    }
    else
    {
        if (row == -1)
            row = getCurrentRow();
        Essence::setValue(name, value, row);
    }
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
//            result = Essence::getValue(name, findFreePrv());
            QString fieldName = name.mid(__pos + 2);
            QString command = QString("SELECT %1 FROM проводки WHERE ДОККОД = %2 AND НОМЕРОПЕР = %3 LIMIT 1;").arg(fieldName).arg(getDocId()).arg(freePrv);
            result = db->getValue(command);
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
    QModelIndex index = getCurrentIndex();      // Запомним, где стоял курсор
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
    setCurrentIndex(index);
}


void Document::setCurrentRow(int row)
{
    Essence::setCurrentRow(row);
    saveOldValues();
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
    int docId = getDocId();
    app->debug(1, "");
    app->debug(1, QString("Opened document %1").arg(docId));
    docModified = false;
    loadDocument();
    Essence::show();
    if (locked || !db->lockDocument(docId))
    {
        setEnabled(false);
    }
    else
        locked = true;
}


void Document::hide()
{
    int docId = getDocId();
    Essence::hide();
    app->debug(1, QString("Closed document %1").arg(docId));
    if (locked)
    {
        db->unlockDocument(docId);
        setEnabled(true);
        locked = false;
    }
}


void Document::loadDocument()
{   // Перед открытием документа запрашивается его содержимое, а для постоянных справочников в документе устанавливаются их значения
    if (!localDictsOpened)
    {
        localDictsOpened = true;
    }
    query();
    Dictionary* dict;
    QString dictName;
    QString idFieldName = db->getObjectName("код");
    // Установим значения постоянных справочников, участвующих в проводках
    if (topersList->count() == 1)
        singlePrv = true;                           // В операции используется простая проводка

    for (int i = 0; i < topersList->count(); i++)
    {
        int prvNumber = topersList->at(i).number;
        dictName = topersList->at(i).dbDictAlias;   // Получим имя справочника, который участвует в проводках бух.операции по дебету
        if (getDictionariesList()->contains(dictName))
        {   // если этот справочник открыт в локальных справочниках документа...
            dict = getDictionaries()->getDictionary(dictName);
            dict->setCanShow(true);
            if (dict->isConst())
            {   // ... и помечен как "постоянный"
                // то установим его значение, которое актуально для всего документа
                qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.дбкод")), 0).toULongLong();
                if (val > 0)
                {
                    dict->setId(val);
                    dict->setMustShow(false);
                    if (!(dictName.left(9) == "документы" && dictName.size() > 9))
                        showParameterText(dictName);
                }
            }
            // Проверим связанные справочники этого справочника, если он набор
            foreach (QString dictName, dict->getChildDicts())
            {
                Dictionary* childDict = getDictionariesList()->value(dictName);
                childDict->setCanShow(true);
                if (childDict != 0)
                {
                    if (childDict->isConst())
                    {
                        // Установим сначала значение основного справочника
                        qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.дбкод")), 0).toULongLong();
                        if (val > 0)
                        {
                            dict->setId(val);
                            dict->setMustShow(false);
                            // А затем установим значение связанного справочника
                            val = dict->getValue(QString("%1_%2").arg(idFieldName).arg(dictName).toUpper(), 0).toULongLong();
                            if (val > 0)
                            {
                                childDict->setId(val);
                                childDict->setMustShow(false);
                                if (!(dictName.left(9) == "документы" && dictName.size() > 9))
                                    showParameterText(dictName);
                            }
                        }
                    }
                }
            }
        }
        dictName = topersList->at(i).crDictAlias;   // то же самое для справочников по кредиту проводок
        if (getDictionariesList()->contains(dictName))
        {   // если этот справочник открыт в локальных справочниках документа...
            dict = getDictionariesList()->value(dictName);
            dict->setCanShow(true);
            if (dict->isConst())
            {   // ... и помечен как "постоянный"
                // то установим его значение, которое актуально для всего документа
                qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.кркод")), 0).toULongLong();
                if (val > 0)
                {
                    dict->setId(val);
                    dict->setMustShow(false);
                    if (!(dictName.left(9) == "документы" && dictName.size() > 9))
                        showParameterText(dictName);
                }
            }
            // Проверим связанные справочники этого справочника, если он набор
            foreach (QString dictName, dict->getChildDicts())
            {
                Dictionary* childDict = getDictionariesList()->value(dictName);
                if (childDict != 0 && childDict->isConst())
                {
                    // Установим сначала значение основного справочника
                    qulonglong val = getValue(QString("P%1__%2").arg(prvNumber).arg(db->getObjectName("проводки.кркод")), 0).toULongLong();
                    if (val > 0)
                    {
                        dict->setId(val);
                        dict->setMustShow(false);
                        // А затем установим значение связанного справочника
                        val = dict->getValue(QString("%1_%2").arg(idFieldName).arg(dictName).toUpper(), 0).toULongLong();
                        if (val > 0)
                        {
                            childDict->setId(val);
                            childDict->setMustShow(false);
                            if (!(dictName.left(9) == "документы" && dictName.size() > 9))
                                showParameterText(dictName);
                        }
                    }
                }
            }
        }
    }
    if (getIsSingleString() && getRowCount() == 0)
    {   // Если в документе должна быть только одна строка, но нет ни одной, то добавим пустую строку
        add();
    }
    restoreVariablesFromDB();   // Загрузим переменные для этого экземпляра документа
    parent->saveOldValues();    // Запомним старые значения текущей строки списка документов

    // Решить, какие справочники показывать при добавлении новой строки
    foreach (QString dictName, getDictionariesList()->keys())
    {
        Dictionary* dict = getDictionariesList()->value(dictName);
        if (!dict->isConst())
        {
            if (!dict->isSet() && dict->canShow())
            {
                dict->setMustShow(true);
            }
            if(dict->isSaldo() && dict->canShow())
            {
                dict->setMustShow(true);
            }
        }
    }

}


void Document::setConstDictId(QString dName, QVariant id)
{
    if (tableModel->rowCount() > 0)
    {
        int currentRow = getCurrentRow();
        bool submit = doSubmit;
        doSubmit = true;
        Dictionary* dict;
        QString dictName;
        for (int i = 0; i < topersList->count(); i++)
        {
            dictName = topersList->at(i).dbDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0)
            {
                dict = getDictionariesList()->value(dictName);
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
                Dictionary* constDict = getDictionariesList()->value(dName);
                if (constDict->isConst())
                {
                    Dictionary* parentDict = constDict->getParentDict();
                    if (parentDict != 0 && parentDict->getPrototypeName() == dictName)
                    {
                        constDict->setIdEnabled(false);
                        dict = getDictionariesList()->value(dictName);
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
                dict = getDictionariesList()->value(dictName);
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
                Dictionary* constDict = getDictionariesList()->value(dName);
                if (constDict->isConst())
                {
                    Dictionary* parentDict = constDict->getParentDict();
                    if (parentDict != 0 && parentDict->getPrototypeName() == dictName)
                    {
                        constDict->setIdEnabled(false);
                        dict = getDictionariesList()->value(dictName);
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
        grdTable->selectRow(currentRow);
        grdTable->setFocus();
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
        return true;
    }
    return false;
}


void Document::close()
{
    Essence::close();
    dictionaries->close();
    delete dictionaries;
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
    form->appendToolTip("buttonAdd",    trUtf8("Добавить строку в документ (Ctrl+Ins)"));
    form->appendToolTip("buttonQueryAdd", trUtf8("Добавить строки в документ из запроса"));
    form->appendToolTip("buttonDelete", trUtf8("Удалить строку из документа (Ctrl+Del)"));
    form->appendToolTip("buttonRequery", trUtf8("Обновить документ (загрузить повторно с сервера) (F3)"));
    if (isPrintable())
        form->appendToolTip("buttonPrint", trUtf8("Распечатать документ (F4)"));
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
        QList<DictType> dictsList;
        db->getToperDictAliases(operNumber, topersList, &dictsList);
        for (int i = 0; i < dictsList.count(); i++)
        {
            if (dictsList.at(i).isSaldo)
            {
                Saldo* saldo = dictionaries->getSaldo(dictsList.at(i).acc);
                SearchParameters* searchParameters = saldo->getForm()->getSearchParameters();
                if (searchParameters != 0)
                    searchParameters->setDictionaries(dictionaries);
                saldo->setAutoLoaded(true);
                Dictionary* dict = dictionaries->getDictionary(dictsList.at(i).prototype);
                dict->setAutoLoaded(true);
            }
            else
            {
                Dictionary* dict = dictionaries->getDictionary(dictsList.at(i).name);
                if (dictsList.at(i).isConst)
                    dict->setConst(true);
                SearchParameters* searchParameters = dict->getForm()->getSearchParameters();
                if (searchParameters != 0)
                    searchParameters->setDictionaries(dictionaries);
                dict->setAutoLoaded(true);
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
                tableModel->setUpdateInfo(columnsProperties.value(i).name, columnsProperties.value(i).table, field, columnsProperties.value(i).type, columnsProperties.value(i).length, columnsProperties.value(i).precision, columnCount, keyColumn);
            // Создадим список атрибутов документа, которые могут добавляться при добавлении новой строки документа
            if (columnsProperties.value(i).table == attrName)
            {
                QString fieldName = columnsProperties.value(i).column;
                attrFields.append(fieldName);
                QString idFieldName = db->getObjectName("код");
                if (fieldName.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    QString dictName = fieldName;
                    dictName.remove(0, 4);
                    Dictionary* dict = dictionaries->getDictionary(dictName);
                    dict->setAutoLoaded(true);
                }
            }
            columnCount++;      // Считаем столбцы
        }
        return true;
    }
    app->showError(QString(QObject::trUtf8("Не существует таблица <%1>")).arg(tableName));
    return false;
}


bool Document::showNextDict()
{  // функция решает, по каким справочникам нужно пробежаться при добавлении новой строки в документ
    bool anyShown = true;
    Dictionary* dict;
    QStringList lockedDicts;
    for (int i = 0; i < dictionaries->dictionariesNamesList.count(); i++)
    {
        QString dictName = dictionaries->dictionariesNamesList.at(i);
        dict = getDictionariesList()->value(dictName);
        if (dict->isMustShow() && !dict->isLocked())
        {                       // покажем те справочники, которые можно показывать
            dict->exec();
            if (dict->isFormSelected())
            {               // Если в справочнике была нажата кнопка "Ок"
                dict->lock();
                lockedDicts.append(dictName);
                anyShown = true;
                if (dict->getTableModel()->rowCount() == 0)
                {       // Если в выбранном справочнике нет записей
                    break;
                }
            }
            else
            {
                anyShown = false;
                break;      // Пользователь отказался от дальнейшей работы со справочниками
            }
        }
    }
    if (anyShown && scriptEngineEnabled && scriptEngine != 0)
        anyShown = scriptEngine->eventAfterShowNextDicts();

    foreach(QString dictName, lockedDicts)
        dictionaries->getDictionary(dictName)->lock(false);

    return anyShown;
}


bool Document::prepareValue(QString name, Dictionary* dict)
{
    if (!prvValues.contains(name))
    {
        qulonglong id;
        if (dict->isSaldo())
            id = ((Saldo*)dict)->getId();
        else
            id = dict->getId();
        if (id != 0 || !dict->getExact())
        {
            prvValues.insert(name, QVariant(id));
            return true;
        }
    }
    return false;
}


bool Document::prepareValue(QString name, QVariant val)
{
    if (!prvValues.contains(name))
    {
        prvValues.insert(name, val);
        return true;
    }
    return false;
}


int Document::appendDocString()
{
    int result = 0;
    QString dictName, parameter;
    qulonglong dbId, crId;
    float quan = 0, price = 0, sum = 0;

    foreach (QString dictName, getDictionariesList()->keys())
    {
        Dictionary* dict = dictionaries->getDictionary(dictName);
        if (dict->isAutoLoaded())
            prepareValue(dictName, dict);
    }

    // Просмотрим все проводки типовой операции
    for (int i = 0; i < topersList->count(); i++)
    {
        QString prefix = QString("P%1__").arg(i + 1);
        QString fldName;
        dbId = 0;                                   // эти параметры могут быть заданы заранее в скриптах
        crId = 0;                                   // если скрипты решают, какие коды позиций справочников задавать
        fldName = prefix + "ДБКОД";
        if (prvValues.keys().contains(fldName))
            dbId = prvValues.value(fldName).toInt();
        dictName = topersList->at(i).dbDictAlias;
        if (dbId == 0 && dictName.size() > 0)           // если скриптами не задан код и есть справочник
        {
            dbId = prvValues.value(dictName).toInt();
            if (dbId == 0 && !getIsSingleString())
                return result;
        }
        fldName = prefix + "КРКОД";
        if (prvValues.keys().contains(fldName))
            crId = prvValues.value(fldName).toInt();
        dictName = topersList->at(i).crDictAlias;
        if (crId == 0 && dictName.size() > 0)
        {
            crId = prvValues.value(dictName).toInt();
            if (crId == 0 && !getIsSingleString())
                return result;
        }
        fldName = prefix + "КОЛ";
        if (prvValues.keys().contains(fldName))
            quan = prvValues.value(fldName).toFloat();
        fldName = prefix + "ЦЕНА";
        if (prvValues.keys().contains(fldName))
            price = prvValues.value(fldName).toFloat();
        fldName = prefix + "СУММА";
        if (prvValues.keys().contains(fldName))
            sum = prvValues.value(fldName).toFloat();
        // Добавим параметры проводки <ДбКод, КрКод, Кол, Цена, Сумма> в список параметров
        parameter.append(QString("%1,%2,%3,%4,%5,").arg(dbId).arg(crId).arg(quan).arg(price).arg(sum));
     }
    // Добавим строку в документ с параметрами всех проводок операции
    result = db->addDocStr(operNumber, docId, parameter);
    QString attrList;
    foreach (QString attr, attrFields)
    {
        if (prvValues.keys().contains(attr))
        {
            if (attrList.size() > 0)
                attrList = attrList + ", ";
            QVariant val = prvValues.value(attr);
            QString value;
            if (val.type() == QVariant::String)
                value = QString("'%1'").arg(val.toString());
            else
                value = val.toString();
            attrList.append(QString("%1=%2").arg(attr).arg(value));
        }
    }
    if (attrList.size() > 0)
    {
        db->saveDocAttribute(operNumber, docId, attrList);
    }

    prvValues.clear();

    if (result > 0)                         // Если строка была добавлена
    {
        int newRow = tableModel->rowCount();
        if (newRow == 0)                    // Если это первая строка в документе
        {
            query();
        }
        else
        {
            tableModel->insertRow(newRow);
        }
        setCurrentRow(newRow);
        updateCurrentRow(result);
        if (getScriptEngine() != 0 && !addingFromQuery)
        {
            saveOldValues();
            getScriptEngine()->eventAfterAddString();
            saveOldValues();
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


void Document::preparePrintValues()
{
    if (reportScriptEngine != 0)
    {
        // Зарядим постоянные справочники
        foreach (QString dictName, getDictionariesList()->keys())
        {
            if (!(dictName.left(9) == "документы" && dictName.size() > 9))
            {
                Dictionary* dict = getDictionariesList()->value(dictName);
                QString idFieldName = db->getObjectName("код") + "_";
                foreach(QString field, dict->getFieldsList())
                {
                    if (field.left(4) != idFieldName)       // Если поле не является ссылкой на другой справочник
                        reportScriptEngine->getReportContext()->setValue(QString("%1.%2").arg(dictName).arg(field).toLower(), dict->getValue(field));
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
            reportScriptEngine->getReportContext()->setValue(QString("документ.%1").arg(fieldName).toLower(), value);
        }

        foreach(QString varName, variables.keys())
        {
            reportScriptEngine->getReportContext()->setValue(QString("документ.%1").arg(varName).toLower(), variables.value(varName));
        }

        Essence::preparePrintValues();
    }
}


void Document::setEnabled(bool en)
{
    Essence::setEnabled(en);
    form->setEnabled(en);
}


void Document::setDate(QString date)
{
    QString field = db->getObjectName("документы.дата");
    parent->setValue(field, QVariant(date));
    getForm()->getDateEdit()->setDate(parent->getValue(field).toDate());
    getForm()->getDateEdit()->repaint();
}


QString Document::getDate()
{
    QString field = db->getObjectName("документы.дата");
    return parent->getValue(field).toDate().toString("dd.MM.yyyy");
}


void Document::setNumber(QString number)
{
    QString field = db->getObjectName("документы.номер");
    parent->setValue(field, QVariant(number));
    getForm()->getNumberEdit()->repaint();
    getForm()->getNumberEdit()->setText(getParent()->getValue(field).toString());

}


QString Document::getNumber()
{
    QString field = db->getObjectName("документы.номер");
    return parent->getValue(field).toString();
}


void Document::showParameterText(QString dictName)
{
    getForm()->showParameterText(dictName);
}
