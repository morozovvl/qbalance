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

#include <QDebug>
#include "dictionary.h"
#include "dictionaries.h"
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../gui/formgridsearch.h"
#include "../gui/searchparameters.h"
#include "../gui/docparameters.h"
#include "../storage/mysqlrelationaltablemodel.h"


Dictionary::Dictionary(QString name, QObject *parent): Essence(name, parent)
{
    prototypeName = name;
    formTitle = "";
    lPrintable = true;
    lCanShow = true;
    lMustShow = false;
    lIsConst = false;
    lAutoSelect = false;
    isDepend = false;
    ftsEnabled = false;
    lIsSaldo = false;
    lIsAutoLoaded = true;
    lsetIdEnabled = true;
    parentDict = 0;
    locked = false;
    getIdRefresh = true;

    if (parent != 0)
    {
        if (((Dictionaries*)parent)->getDocument() != 0)
            dictionaries = ((Dictionaries*)parent)->getDocument()->getDocDictionaries();
        else
            dictionaries = (Dictionaries*)parent;
    }
    else
        dictionaries = app->getDictionaries();

    QSqlRecord tableProperties = db->getDictionariesProperties(tableName);
    if (!tableProperties.isEmpty())
    {
        formTitle = tableProperties.value(db->getObjectName("доступ_к_справочникам.имя_в_форме")).toString().trimmed();
        if (app->isSA())
        {
            lSelectable = true;
            lInsertable = true;
            lDeleteable = true;
            lUpdateable = true;
        }
        else
        {
            lSelectable = tableProperties.value("selectable").toBool();
            lInsertable = tableProperties.value("insertable").toBool();
            lDeleteable = tableProperties.value("deleteable").toBool();
            lUpdateable = tableProperties.value("updateable").toBool();
        }
    }
    lIsSet = db->isSet(tableName);
    doSubmit = true;
    sqlCommand = "";
//    scriptEngineEnabled = false;
}


Dictionary::~Dictionary() {
}


bool Dictionary::add()
{
    if (!lInsertable)
    {
        app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено добавлять записи в справочник %1 пользователю %2")).arg(
                      app->getDictionaries()->getDictionaryTitle(tableName),
                      app->getLogin()));
        return false;
    }
    QHash<QString, QVariant> values;
    bool lAddDict = true;
    if (!isSet())
    {
        SearchParameters* parameters = (SearchParameters*)form->getFormWidget()->findChild("searchParameters");
        if (parameters != 0)
        {
            QVector<sParam> searchParameters = parameters->getParameters();
            if (searchParameters.size() > 0)
            {
                for (int i = 0; i < searchParameters.size(); i++) {
                    if (searchParameters[i].table == getTableName())
                        values.insert(searchParameters[i].field, searchParameters[i].value);
                    else
                    {
                        Dictionary* dict = dictionaries->getDictionary(searchParameters[i].table);
                        QString dictName = searchParameters[i].value.toString();
                        if (dictName.size() > 0)
                        {
                            dictName = dict->getName();
                            dict->query(QString("%1='%2'").arg(db->getObjectNameCom(searchParameters[i].table + "." + nameFieldName)).arg(dictName));
                            if (dict->getTableModel()->rowCount() == 1)
                            {
                                // Далее первый параметр такой хитрый с запросом к БД имени поля, т.к. searchParameters[i].table - всегда в нижнем регистре, а idFieldName - может быть и в верхнем и в нижнем
                                // поэтому настоящее имя поля код_<имя таблицы> получим путем запроса к БД
                                QString dictTableName = dictName;
                                QString dictFieldName = idFieldName.toLower() + "_" + searchParameters[i].table;
                                values.insert(db->getObjectName(QString("%1.%2").arg(dictTableName)
                                                                                .arg(dictFieldName)),
                                dict->getId(0));
                            }
                            else
                            {
                                TApplication::exemplar()->getGUIFactory()->showError(QString(QObject::trUtf8("Уточните, пожалуйста, значение связанного справочника %1.")).arg(dict->getFormTitle()));
                                lAddDict = false;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < fieldList.count(); i++)
        {       // Просмотрим список полей
            QString name = fieldList.at(i);
            if (name.left(4) == idFieldName + "_")
            {        // Если поле ссылается на другую таблицу
                name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                Dictionary* dict = dictionaries->getDictionary(name);
                if (dict != 0)                       // Если удалось открыть справочник
                    values.insert(fieldList.at(i), dict->getId());
            }
        }
    }
    if (lAddDict)
    {
        int strNum = db->insertDictDefault(getTableName(), &values);
        if (strNum >= 0)
        {
            int newRow = tableModel->rowCount();
            if (newRow == 0)
            {
                query();
                grdTable->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
            }
            else
            {
                int column = grdTable->currentIndex().column();
                tableModel->insertRow(newRow);
                grdTable->reset();
                grdTable->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
                updateCurrentRow(strNum);
                grdTable->selectionModel()->setCurrentIndex(grdTable->currentIndex().sibling(newRow, column), QItemSelectionModel::Select);
            }
            form->setButtons();
            grdTable->setFocus();
            return true;
        }
    }
    return false;
}


QString Dictionary::getSearchExpression(QString tName)
{
    QString result;
    QString tableName = tName;
    if (tableName.size() == 0)
        tableName = getTableName();
    SearchParameters* parameters = (SearchParameters*)form->getFormWidget()->findChild("searchParameters");
    if (parameters != 0)
    {
        QVector<sParam> searchParameters = parameters->getParameters();
        if (searchParameters.size() > 0)
        {
            for (int i = 0; i < searchParameters.size(); i++)
            {
                if (searchParameters[i].table == tableName)
                {
                    result = searchParameters[i].value.toString();
                    break;
                }
            }
        }
    }
    return result;
}


bool Dictionary::remove(bool noAsk)
{
    if (lDeleteable)
    {
        if (Essence::remove(noAsk)) {
            db->removeDictValue(tableName, getValue("КОД").toULongLong());
            query();
            return true;
        }
    }
    else
        app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено удалять записи из справочника %1 пользователю %2")).arg(
            app->getDictionaries()->getDictionaryTitle(tableName),
            app->getLogin()));
    return false;
}


void Dictionary::setValue(QString name, QVariant value, int row)
{
    Essence::setValue(name, value, row);
}


void Dictionary::setValue(qulonglong id, QString name, QVariant value)
{
    setId(id);
    Essence::setValue(name, value);
}


bool Dictionary::calculate() {
    if (!isCurrentCalculate)
    {
        isCurrentCalculate = true;
        if (Essence::calculate())
        {   // Если в вычислениях не было ошибки

            // Сохраним в БД все столбцы. Будут сохраняться только те, в которых произошли изменения
            int row = grdTable->currentIndex().row();

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

            if (db->execCommands())
            {   // Если во время работы скриптов ошибки не произошло
                // Запросим в БД содержимое текущей строки в документе и обновим содержимое строки в форме (на экране)
                updateCurrentRow();
                saveOldValues();
            }
            else
            {   // Во время работы скриптов произошла ошибка
                restoreOldValues();
            }
        }
        isCurrentCalculate = false;
    }
    return true;
}


qulonglong Dictionary::getId(int row, bool forceToRefresh)
{
    QVariant result = Essence::getId(row);
    if ((result.isNull() || forceToRefresh || getIdRefresh) && isSet() && !isSaldo())
    {
        // Если это набор, то продолжаем
        QString filter;
        QHash<QString, QVariant> values;
        for (int i = 0; i < fieldList.count(); i++)
        {       // Просмотрим список полей
            QString name = fieldList.at(i);
            if (name.left(4) == idFieldName + "_")
            {        // Если поле ссылается на другую таблицу
                QString field = db->getObjectNameCom(tableName + "." + name);
                if (filter.size() > 0)
                    filter.append(" AND ");
                filter.append(field + "=");

                name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                Dictionary* dict = dictionaries->getDictionary(name);
                if (dict != 0)                       // Если удалось открыть справочник
                {
                    qulonglong id = dict->getId();
                    if (id != 0)
                    {
                        filter.append(QString("%1").arg(id));
                        values.insert(field, QVariant(id));
                    }
                    else
                    {
                        app->showError(QString(QObject::trUtf8("Не определено значение справочника \"%1\"")).arg(name));
                        return result.toLongLong();
                    }
                }
                else
                    return result.toLongLong();
            }
        }
        if (filter.size() > 0)
        {
            query(filter);
            if (tableModel->rowCount() == 0)
            {
                db->insertDictDefault(tableName, &values);
                query(filter);
            }
            return Essence::getId(0);
        }
    }
    return result.toLongLong();
}


void Dictionary::setId(qulonglong id)
{
    if (lsetIdEnabled && getValue(idFieldName) != id)
    {
        Essence::setId(id);
        if (isSet())            // Если это набор, то переустановим связанные справочники
        {
            foreach (QString dictName, getChildDicts())
            {
                Dictionary* dict = dictionaries->getDictionary(dictName);
                if (!dict->isSet())
                {
                    qulonglong val = getValue(QString("%1_%2").arg(idFieldName).arg(dictName).toUpper(), 0).toULongLong();
                    if (val > 0)
                        dict->setId(val);
                }
            }
        }
    }
}


void Dictionary::setForm(QString formName)
{
    if (form != 0)
    {
        form->close();
        delete form;
    }
    closeScriptEngine();

    form = new FormGridSearch();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть справочник"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новую запись в справочнике (Ctrl+Ins)"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить запись из справочника (Ctrl+Del)"));
    if (isPrintable())
        form->appendToolTip("buttonPrint",      trUtf8("Распечатать выбранные записи из справочника (F4)"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить справочник (загрузить повторно с сервера) (F3)"));

    form->open(parentForm, this, formName.size() == 0 ? getTagName() : formName);
    openScriptEngine();
}


bool Dictionary::open(QString command)
{
    sqlCommand = command;
    dictTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName).trimmed();
    if (dictTitle.size() == 0)
        dictTitle = tableName;

    if (Essence::open())
    {
        prepareSelectCurrentRowCommand();
        // Откроем этот справочник
        fieldList = getFieldsList();

        // Проверим, имеется ли в справочнике полнотекстовый поиск
        foreach (QString fieldName, fieldList)
        {
            if (fieldName == "fts")
            {
                ftsEnabled = true;
                break;
            }
        }

        tableModel->setTestSelect(true);
        query();
        tableModel->setTestSelect(false);

        if (isFieldExists(nameFieldName))
            setPhotoNameField(nameFieldName);

        FieldType fld;
        int keyColumn   = 0;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            fld = columnsProperties.at(i);

            // Для основной таблицы сохраним информацию для обновления
            if (fld.table == columnsProperties.at(0).table)
            {
                if (fld.name == idFieldName)
                    keyColumn = i;
                tableModel->setUpdateInfo(fld.name, fld.table, fld.name, fld.type, fld.length, fld.precision, i, keyColumn);
            }
        }

        return true;
    }
    return false;
}


void Dictionary::setConst(bool isConst)
{
    lIsConst = isConst;
    if (dictionaries != 0 && dictionaries->getDocument() != 0)      // Если справочник является локальным к документу
    {                                                               // То на форме документа мы должны его переместить в строку параметров документа
        FormDocument* docForm = dictionaries->getDocument()->getForm();
        if (docForm != 0)
        {
            DocParameters* docPar = docForm->getDocParameters();
            if (isConst)
            {
                docPar->addString(prototypeName);
            }
        }
    }
}


QStringList Dictionary::getChildDicts()
{
    QStringList childrenList;
    if (isSet())
    {
        for (int i = 0; i < fieldList.count(); i++)
        {       // Просмотрим список полей
            QString name = fieldList.at(i);
            if (name.left(idFieldName.size() + 1) == idFieldName + "_")
            {        // Если поле ссылается на другую таблицу
                name.remove(0, idFieldName.size() + 1);     // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                childrenList.append(name);
            }
        }
    }
    return childrenList;
}


bool Dictionary::setTableModel(int)
{
    QString prefix = "документы";
    if (tableName.left(9) == prefix)
    {
        int oper = QString(tableName).replace(prefix, "").toInt();
        sqlCommand = QString("SELECT * FROM (SELECT * FROM %1 WHERE %2 = %3) %4").arg(db->getObjectNameCom("vw_спрдокументы"))
                                                                             .arg(db->getObjectNameCom("vw_спрдокументы.ОПЕР"))
                                                                             .arg(oper)
                                                                             .arg(tableName);
    }
    if (sqlCommand.size() == 0)
    {
        if (Essence::setTableModel(0))
        {
            tableModel->setSelectStatement(db->getDictionarySqlSelectStatement(tableName));
            db->getColumnsRestrictions(tableName, &columnsProperties);
            return true;
        }
    }
    else
    {
        tableModel = new MySqlRelationalTableModel("", this);
        tableModel->setSelectStatement(sqlCommand);
        db->getColumnsProperties(&columnsProperties, tableName, tableName);
        db->getColumnsRestrictions(tableName, &columnsProperties);
        return true;
    }
    return false;
}


void Dictionary::query(QString defaultFilter, bool exactlyDefaultFilter)
{
    QModelIndex index;
    qulonglong id = 0;

    if (tableModel->rowCount() > 0)
        id = getValue(idFieldName).toLongLong();

    if (grdTable != 0)
        index = grdTable->currentIndex();

    QString resFilter = defaultFilter;

    if (form != 0 && !exactlyDefaultFilter)
    {
        QString filter = form->getFilter();
        if (filter.size() > 0)
        {
            if (resFilter.size() > 0)
                resFilter.append(" AND " + filter);
            else
                resFilter = filter;
        }

        if (!isDocumentLoading())
        {
            if (scriptEngine != 0)
            {
                filter = scriptEngine->getFilter();
                if (filter.size() > 0)
                {
                    if (resFilter.size() > 0)
                        resFilter.append(" AND " + filter);
                    else
                        resFilter = filter;
                }
            }
        }
    }

    Essence::query(resFilter);

    if (tableModel->rowCount() > 0 && grdTable != 0)
    {
        if (index.row() > tableModel->rowCount() - 1)       // Если старая последняя запись исчезла
            grdTable->selectRow(tableModel->rowCount() - 1);    // то перейдем на новую последнюю
        else
        {
            if (index.row() < 0)
                grdTable->selectRow(0);
            else
            {
                if (id > 0)
                {
                    for (int i = 0; i < tableModel->rowCount(); i++)
                    {
                        if (getValue(idFieldName, i) == id)
                        {
                            grdTable->selectRow(i);
                            break;
                        }
                    }
                }
                else
                    grdTable->selectRow(index.row());
            }
        }
    }

    if (lAutoSelect && tableModel->rowCount() == 1)     // Если включен автоматический выбор позиции и позиция одна, то нажмем кнопку Ok (выберем позицию)
    {
        form->setAutoSelect(true);
    }
}


void Dictionary::setOrderClause()
{
    if (isSet())
    {
        QString sortOrder;
        QStringList tablesList;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            FieldType fld = columnsProperties.at(i);
            if (fld.table != tableName && !tablesList.contains(fld.table))
            {
                tablesList.append(fld.table);
                if (sortOrder.size() > 0)
                    sortOrder.append(",");
                sortOrder.append(QString("\"%1\".%2").arg(fld.table)
                                                     .arg(db->getObjectNameCom(fld.table + ".имя")));
            }
        }
        Table::setOrderClause(sortOrder);
    }
    else
    {
        if (tableName.left(9) != "документы")
            Table::setOrderClause(QString("\"%1\".%2").arg(tableName)
                                                     .arg(db->getObjectNameCom(tableName + ".имя")));
    }
}


void Dictionary::updateCurrentRow(int strNum)
{   // Делает запрос к БД по одной строке справочника. Изменяет в текущей модели поля, которые в БД отличаются от таковых в модели.
    // Применяется после работы формул для изменения полей в строке, которые косвенно изменились

    int str = strNum == 0 ? getId() : strNum;

    preparedSelectCurrentRow.bindValue(":value", str);

    Essence::updateCurrentRow();
}


void Dictionary::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->selectStatement();

    command.replace(" ORDER BY", QString(" %1 \"%2\".\"%3\"=:value ORDER BY").arg(command.contains("WHERE") ? "AND" : "WHERE")
                                                                                .arg(getTableName())
                                                                                .arg(db->getObjectName(getTableName() + "." + idFieldName)));

    preparedSelectCurrentRow.prepare(command);
}


void Dictionary::setMustShow(bool must)
{
    lMustShow = must;
}


void Dictionary::lock(bool toLock)
// Заблокировать все связанные справочники
{
    if (toLock)
    {
        if (isSet())
        {
            foreach (QString dictName, getChildDicts())
            {
                Dictionary* dict = dictionaries->getDictionary(dictName);
                dict->setId(getValue(idFieldName + "_" + dictName).toLongLong());
                dict->lock();
            }
        }
        locked = true;
    }
    else
        locked = false;
}
