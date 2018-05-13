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

#include <QtCore/QDebug>
#include "dictionary.h"
#include "dictionaries.h"
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../gui/formgridsearch.h"
#include "../gui/searchparameters.h"
#include "../gui/docparameters.h"
#include "../gui/picture.h"
#include "../gui/tableview.h"
#include "../gui/dialog.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"
#include "../engine/scriptengine.h"
#include "../engine/documentscriptengine.h"
#include "../engine/reportcontext.h"


Dictionary::Dictionary(QString name, QObject *parent): Essence(name, parent)
{
}


Dictionary::Dictionary(QObject *parent)
{
    Dictionary("", parent);
}


Dictionary::~Dictionary()
{
}


void Dictionary::postInitialize(QString name, QObject *parent)
{
    Essence::postInitialize(name, parent);

    prototypeName = name;
    formTitle = "";
    lPrintable = true;
    lCanShow = false;
    lMustShow = false;
    lIsConst = false;
    lAutoSelect = false;
    isDepend = false;
    ftsEnabled = false;
    lIsSaldo = false;
    lIsAutoLoaded = false;
    lsetIdEnabled = true;
    parentDict = 0;
    locked = false;
    getIdRefresh = true;
    parameters = 0;
    doSubmit = true;
    exact = true;
    lNameExist = false;
    isView = db->isView(tableName);
    lIsSet = db->isSet(tableName);

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
    if (isView)
    {
        lInsertable = false;
        lDeleteable = false;
        lUpdateable = false;
    }
}


void Dictionary::queryName(QString filter)
{
    query(QString("\"%1\".\"ИМЯ\" ILIKE '%" + filter + "%'").arg(tableName));
}


void Dictionary::setSorted(bool sorted)
{
    sortedTable = sorted;
}


void Dictionary::setAutoLoaded(bool al)
{
    lIsAutoLoaded = al;
}


bool Dictionary::isAutoLoaded()
{
    return lIsAutoLoaded;
}


bool Dictionary::canShow()
{
    return lCanShow;
}


void Dictionary::setCanShow(bool can)
{
    lCanShow = can;
}


bool Dictionary::isCanShow()
{
    return lCanShow;
}


bool Dictionary::isMustShow()
{
    return lMustShow;
}


bool Dictionary::isConst()
{
    return lIsConst;
}


bool Dictionary::isSet()
{
    return lIsSet;
}


bool Dictionary::isSaldo()
{
    return lIsSaldo;
}


void Dictionary::setIsSaldo(bool s)
{
    lIsSaldo = s;
}


void Dictionary::setAutoSelect(bool autoSelect)
{
    lAutoSelect = autoSelect;
}


QString Dictionary::objectName()
{
    return "Dictionary";
}


bool Dictionary::isDependent()
{
    return isDepend;
}


void Dictionary::setDependent(bool d)
{
    isDepend = d;
}


QString Dictionary::getPrototypeName()
{
    return prototypeName;
}


void Dictionary::setPrototypeName(QString prototype)
{
    prototypeName = prototype;
}


bool Dictionary::isFtsEnabled()
{
    return ftsEnabled;
}


QString Dictionary::getDictTitle()
{
    return dictTitle;
}


Dictionary* Dictionary::getParentDict()
{
    return parentDict;
}


void Dictionary::setParentDict(Dictionary* dict)
{
    parentDict = dict;
}


void Dictionary::setIdEnabled(bool e)
{
    lsetIdEnabled = e;
}


bool Dictionary::isLocked()
{
    return locked;
}


bool Dictionary::isPictureExist()
{
    return form->getPicture()->isPictureExist();
}


void Dictionary::setGetIdRefresh(bool val)
{
    getIdRefresh = val;
}


void Dictionary::setExact(bool e)
{
    exact = e;
}


bool Dictionary::getExact()
{
    return exact;
}


bool Dictionary::add()
{
    bool result = false;

    if (!lInsertable)
    {
        app->showError(QString(QObject::trUtf8("Запрещено добавлять записи в справочник %1 пользователю %2")).arg(
                      app->getDictionaries()->getDictionaryTitle(tableName),
                      app->getLogin()));
        return result;
    }

    if (scriptEngineEnabled && scriptEngine != 0)
        result = scriptEngine->eventBeforeAddString();

    if (result)
    {
        QHash<QString, QVariant> values;
        result = true;
        if (!isSet())
        {
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
                                dict->query(parameters->getFilter(searchParameters[i].table));
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
                                    app->showError(QString(QObject::trUtf8("Уточните, пожалуйста, значение связанного справочника %1.")).arg(dict->getFormTitle()));
                                    result = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (result)
        {
            result = false;
            if (!isSet())
            {
                int strNum = db->insertDictDefault(getTableName(), &values);
                if (strNum >= 0)
                {
                    int newRow = tableModel->rowCount();
                    tableModel->insertRow(newRow);
                    setCurrentRow(newRow);
                    updateCurrentRow(strNum);
                    result = true;
                }
            }
            else
            {
                int strNum = getId(0, true);
                if (strNum > 0)
                {
                    updateCurrentRow(strNum);
                    result = true;
                }
            }
            if (grdTable != 0)
                grdTable->setCurrentFocus();
        }
    }
    return result;
}


QString Dictionary::getSearchExpression(QString tName)
{
    QString result;
    QString tableName = tName;
    if (tableName.size() == 0)
        tableName = getTableName();
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
    bool canRemove = true;
    if (lDeleteable)
    {
        if (Essence::remove(noAsk)) {
            if (scriptEngineEnabled && scriptEngine != 0)
                canRemove = scriptEngine->eventBeforeDeleteString();

            if (canRemove)
            {
                if (db->removeDictValue(tableName, getValue("КОД").toULongLong()))
                {
                    query();
                    return true;
                }
                app->showError(QString(QObject::trUtf8("Не удалось удалить строку")));
            }
        }
    }
    else
        app->showError(QString(QObject::trUtf8("Запрещено удалять записи из справочника %1 пользователю %2")).arg(
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


bool Dictionary::calculate(bool update) {
    bool lResult = false;
    if (Essence::calculate())
    {   // Если в вычислениях не было ошибки
        if (update)
        {
            saveChanges();
        }
        lResult = true;
    }
    return lResult;
}


qulonglong Dictionary::getId(int row, bool forceToRefresh)
{
    qulonglong result = Essence::getId(row);
    if ((result == 0 || forceToRefresh || getIdRefresh) && lIsSet)
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
                name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                Dictionary* dict = dictionaries->getDictionary(name);
                if (dict != 0)                       // Если удалось открыть справочник
                {
                    qulonglong id = dict->getId();
                    if (dict->getExact())
                    {
                        if (id != 0)
                        {
                            if (filter.size() > 0)
                                filter.append(" AND ");
                            filter.append(QString("%1.%2=%3").arg(db->getObjectNameCom(tableName)).arg(field).arg(id));
                            values.insert(field, QVariant(id));
                        }
                        else
                        {
                            return result;
                        }
                    }
                }
                else
                    return result;
            }
        }
        if (filter.size() > 0)
        {
            query(filter);
            if (tableModel->rowCount() == 0 && isSet() && !isView)
                result = db->insertDictDefault(tableName, &values);
            else
                result = Essence::getId(0);
        }
    }
    return result;
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
        lock(true);
    }
}


void Dictionary::setForm(QString formName)
{
    if (form != 0 && form->isDefaultForm())
    {
        if (form->getGrdTable() != 0)
        {
            grdTable->close();
            delete grdTable;
            grdTable = 0;
        }
        form->close();
        delete form;
        form = 0;
    }

    form = new FormGridSearch();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть справочник"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новую запись в справочнике (Ctrl+Ins)"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить запись из справочника (Ctrl+Del)"));
    if (isPrintable())
        form->appendToolTip("buttonPrint",      trUtf8("Распечатать выбранные записи из справочника (F4)"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить справочник (загрузить повторно с сервера) (F3)"));
    form->appendToolTip("buttonQuery",    trUtf8("Выполнить запрос"));

    form->open(parentForm, this, formName.size() == 0 ? getTagName() : formName);
    parameters = (SearchParameters*)form->getFormWidget()->findChild("searchParameters");

    grdTable = form->getGrdTable();
    if (grdTable != 0)
        grdTable->setEssence(this);
}


bool Dictionary::open(QString command, QString tName)
{
    if (tName == "undefined")
        tName = "";

    sqlCommand = command;

    if (tName.size() > 0)
        queryTableName = tName;

    if (tagName.size() == 0)
    {
        tagName = tName;
        if (sqlCommand.size() == 0)
            return true;
    }

    if (dictTitle.size() == 0)
        dictTitle = tagName;

    if (Essence::open())
    {
        if (tableName.size() > 0)
        {
            // Откроем этот справочник
            fieldList = getFieldsList();
            // Проверим, имеется ли в справочнике полнотекстовый поиск
            foreach (QString fieldName, fieldList)
            {
                if (fieldName == "fts")
                {
                    ftsEnabled = true;
                }
                if (fieldName.toUpper() == "ИМЯ")
                {
                    lNameExist = true;
                }
            }

            setOrderClause();

            prepareSelectCurrentRowCommand();

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

            reportScriptEngine = new DocumentScriptEngine(0, this);
            reportScriptEngine->setReportContext(&printValues);
            reportScriptEngine->getReportContext()->setScriptEngine(reportScriptEngine);
        }
        return true;
    }
    return false;
}


void Dictionary::close()
{
    Essence::close();
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
        if (tableName.size() > 0)
        {
            if (Essence::setTableModel(0))
            {
                tableModel->setSelectStatement(db->getDictionarySqlSelectStatement(tableName));
                db->getColumnsRestrictions(tableName, &columnsProperties);
                return true;
            }
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
    }

    if (!isDocumentLoading())
    {
        if (scriptEngine != 0)
        {
            resFilter = scriptEngine->getFilter(resFilter);
        }
    }

    Essence::query(resFilter);

    if (tableModel->rowCount() > 0 && grdTable != 0)
    {
        QModelIndex index = getCurrentIndex();

        if (index.row() > tableModel->rowCount() - 1)       // Если старая последняя запись исчезла
            grdTable->selectRow(tableModel->rowCount() - 1);    // то перейдем на новую последнюю
        else
        {
            if (index.row() < 0)
            {
                grdTable->selectRow(0);
            }
            else
                grdTable->selectRow(index.row());
        }
    }

    if (tableModel->rowCount() == 1)     // Если включен автоматический выбор позиции и позиция одна, то нажмем кнопку Ok (выберем позицию)
    {
        if (lAutoSelect)
            form->cmdOk();
    }

}


void Dictionary::setOrderClause(QString sOrder)
{
    if (!sortedTable)
    {
        Table::setOrderClause("");
        return;
    }
    if (sOrder.size() > 0)
    {
        Table::setOrderClause(sOrder);
        return;
    }
    if (lIsSet)
    {
        QString sortOrder;
        QStringList tablesList;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            FieldType fld = columnsProperties.at(i);
            if (fld.table != tableName && !tablesList.contains(fld.table) && fld.table.left(9) != "документы" && fld.table.left(11) != "докатрибуты")
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
        if (tableName.left(9) != "документы" && tableName.size() > 0 && lNameExist)
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


void Dictionary::preparePrintValues()
{
    if (reportScriptEngine != 0)
    {
        if (parameters != 0)
        {
            QVector<sParam> searchParameters = parameters->getParameters();
            if (searchParameters.size() > 0)
            {
                for (int i = 0; i < searchParameters.size(); i++)
                {
                    if (searchParameters[i].value.toString().size() > 0)
                        reportScriptEngine->getReportContext()->setValue(searchParameters[i].table, searchParameters[i].value);
                }
            }
        }
        Essence::preparePrintValues();
    }
}


void Dictionary::setMustShow(bool must)
{
    lMustShow = must;
}


void Dictionary::lock(bool toLock)
// Заблокировать все связанные справочники
{
    if (isSet())
    {
        if (rowCount() == 0)
            getId();
        foreach (QString dictName, getChildDicts())
        {
            Dictionary* dict = dictionaries->getDictionary(dictName);
            if (toLock)
            {
                qlonglong id = getValue(idFieldName + "_" + dictName).toLongLong();
                dict->setId(id);
            }
            dict->lock(toLock);
        }
    }
    locked = toLock;
}


void Dictionary::setSqlCommand(QString command)
{
    if (opened)
        close();
    open(command);
}


