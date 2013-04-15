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
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/searchparameters.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../engine/formscriptengine.h"



Dictionary::Dictionary(QString name, QObject *parent): Essence(name, parent)
{
    formTitle = "";
    lPrintable = true;
    lCanShow = true;
    lMustShow = false;
    lIsConst = false;
    lAutoSelect = false;
    isDepend = false;
    ftsEnabled = false;
    sortOrder = "";
    dictionaries = TApplication::exemplar()->getDictionaries();
    if (TApplication::exemplar()->isSA())
    {
        lSelectable = true;
        lInsertable = true;
        lDeleteable = true;
        lUpdateable = true;
    }
    else
    {
        QSqlRecord tableProperties = db->getDictionariesProperties(tableName);
        if (!tableProperties.isEmpty())
        {
            formTitle = tableProperties.value(db->getObjectName("имя")).toString().trimmed();
            lSelectable = tableProperties.value("selectable").toBool();
            lInsertable = tableProperties.value("insertable").toBool();
            lDeleteable = tableProperties.value("deleteable").toBool();
            lUpdateable = tableProperties.value("updateable").toBool();
        }
    }
    lIsSet = db->isSet(tableName);
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
    QMap<QString, QVariant> values;
    bool lAddDict = true;
    if (!isSet())
    {
        SearchParameters* parameters = (SearchParameters*)qFindChild<QFrame*>(form->getForm(), "searchParameters");
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
                        if (searchParameters[i].value.toString().size() > 0)
                        {
                            Dictionary* dict = dictionaries->getDictionary(searchParameters[i].table);
                            dict->query(QString("trim(%1)='%2'").arg(db->getObjectNameCom(searchParameters[i].table + "." + nameFieldName)).arg(searchParameters[i].value.toString()));
                            if (dict->getTableModel()->rowCount() == 1)
                            {
                                // Далее первый параметр такой хитрый с запросом к БД имени поля, т.к. searchParameters[i].table - всегда в нижнем регистре, а idFieldName - может быть и в верхнем и в нижнем
                                // поэтому настоящее имя поля код_<имя таблицы> получим путем запроса к БД
                                QString dictTableName = searchParameters[i].value.toString();
                                QString dictFieldName = idFieldName.toLower() + "_" + searchParameters[i].table;
//                                dictFieldName = db->getObjectName(dictTableName + "." + dictFieldName);
                                values.insert(db->getObjectName(QString("%1.%2").arg(dictTableName)
                                                                                .arg(dictFieldName)),
                                              dict->getId(0));
                            }
                            else
                            {
                                TApplication::exemplar()->getGUIFactory()->showError(QString(QObject::tr("Уточните, пожалуйста, значение связанного справочника <%1>.")).arg(dict->getFormTitle()));
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
                if (dict != NULL)                       // Если удалось открыть справочник
                    values.insert(fieldList.at(i), dict->getId());
            }
        }
    }
    if (lAddDict)
    {
        if (db->insertDictDefault(getTableName(), &values))
        {
            query();
            return true;
        }
    }
    return false;
}


bool Dictionary::remove()
{
    if (lDeleteable)
    {
        if (Essence::remove()) {
            db->removeDictValue(tableName, getId());
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


bool Dictionary::calculate(const QModelIndex& index) {
    if (Essence::calculate(index))
    {   // Если в вычислениях не было ошибки

        // Сохраним в БД все столбцы. Будут сохраняться только те, в которых произошли изменения
        int row = form->getCurrentIndex().row();
        for (int i = 0; i < tableModel->record().count(); i++)
        {
            QString fieldName = tableModel->record().fieldName(i).toUpper();
            if (getValue(fieldName) != getOldValue(fieldName))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
            {
                tableModel->submit(tableModel->index(row, i));
            }
        }

        if (db->execCommands())
        {   // Если во время работы скриптов ошибки не произошло
            // Запросим в БД содержимое текущей строки в документе и обновим содержимое строки в форме (на экране)
            selectCurrentRow();
        }
        else
        {   // Во время работы скриптов произошла ошибка
            restoreOldValues();
        }
    }
    return true;
}



void Dictionary::setForm()
{
    form = new FormGridSearch();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть справочник"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новую запись в справочнике"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить запись из справочника"));
    form->appendToolTip("buttonPrint",      trUtf8("Распечатать выбранные записи из справочника"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить справочник (загрузить повторно с сервера)"));

    form->open(parentForm, this, getTagName());
}


bool Dictionary::open(int deep)
{
    dictTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName).trimmed();
    if (dictTitle.size() == 0)
        dictTitle = tableName;
    if (Table::open())
    {     // Откроем этот справочник
        fieldList = getFieldsList();

        // Проверим, имеется ли в справочнике полнотекстовый поиск
        ftsEnabled = fieldList.contains(db->getObjectName(tableName + ".fts"), Qt::CaseInsensitive);

        // Установим порядок сортировки
        if (isSet())
            setSortClause(sortOrder);
        else
            setSortClause(QString("\"%1\".%2").arg(tableName)
                                          .arg(db->getObjectNameCom(tableName + ".имя")));

        db->getColumnsRestrictions(tableName, &columnsProperties);
        initForm();
        setScriptEngine();
        if (scriptEngine != 0)
        {
            if (!scriptEngine->open(scriptFileName))
                return false;
            if (!scriptEngine->evaluate())
                return false;
        }
        initFormEvent();
        return true;
    }
    app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено просматривать справочник <%1> пользователю %2. Либо справочник отсутствует.")).arg(dictTitle, TApplication::exemplar()->getLogin()));
    return false;
}


void Dictionary::setTableModel()
{
    QString selectList;
    QString fromList;
    QString selectStatement;

    Essence::setTableModel();

    QList<FieldType> fields;
    db->getColumnsProperties(&fields, tableName);

    QStringList tables;
    tables.append(fields.at(0).table);

    fromList = db->getObjectNameCom(tableName);

    FieldType fld, oldFld;
    int keyColumn   = 0;
    for (int i = 0; i < fields.count(); i++)
    {
        fld = fields.at(i);

        // Для основной таблицы сохраним информацию для обновления
        if (fld.table == fields.at(0).table)
        {
            if (fld.name == idFieldName)
                keyColumn = i;
            tableModel->setUpdateInfo(fld.name, fld.table, fld.name, i, keyColumn);
        }

        if (!tables.contains(fld.table))
        {
            fromList.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".\"%4\"").arg(fld.table)
                                                                                             .arg(oldFld.table)
                                                                                             .arg(oldFld.name)
                                                                                             .arg(fld.name));
            Dictionary* dict = dictionaries->getDictionary(fld.table);
            if (dict != 0)
            {                                       // Если удалось открыть справочник
                if (!lIsSet)
                    dict->setDependent(true);       // Справочник может считаться зависимым, если основной не является набором справочников
                else
                {
                    if (sortOrder.size() > 0)
                        sortOrder.append(", ");
                    sortOrder.append(QString("\"%1\".%2").arg(fld.table)
                                                         .arg(db->getObjectNameCom(fld.table + ".имя")));
                }
            }
            tables.append(fld.table);
        }

        if (selectList.size() > 0)
            selectList.append(", ");
        selectList.append(QString("\"%1\".\"%2\" AS \"%3\"").arg(fld.table)
                                                                .arg(fld.name)
                                                                .arg(fld.column.toUpper()));
        oldFld = fld;
    }

    selectStatement.append(QLatin1String("SELECT DISTINCT ")).append(selectList);;
    selectStatement.append(QLatin1String(" FROM ")).append(fromList);
    tableModel->setSelectStatement(selectStatement);
}


qulonglong Dictionary::getId(int row)
{
    if (isSet())
    {
        QString filter = "";
        for (int i = 0; i < fieldList.count(); i++)
        {       // Просмотрим список полей
            QString name = fieldList.at(i);
            if (name.left(4) == idFieldName + "_")
            {        // Если поле ссылается на другую таблицу
                name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                Dictionary* dict = dictionaries->getDictionary(name);
                if (dict != NULL)
                {                      // Если удалось открыть справочник
                    if (filter.size() > 0)
                        filter.append(" AND ");
                    filter.append(QString("%1=%2").arg(fieldList.at(i)).arg(dict->getId()));
                }
            }
        }
        if (filter.size() > 0)
        {
            query(filter);
            qulonglong result = Essence::getId(0);
            if (result == 0)
            {
                if (add())
                {
                    query(filter);
                    return Essence::getId(0);
                }
                return 0;
            }
            return result;
        }
    }
    return Essence::getId(row);
}


void Dictionary::query(QString defaultFilter)
{
    QString resFilter = defaultFilter;
    if (form != 0)
    {
        QString filter = ((FormGridSearch*)form)->getFilter();
        if (filter.size() > 0)
        {
            if (resFilter.size() > 0)
                resFilter.append(" AND " + filter);
            else
                resFilter = filter;
        }
    }
//    tableModel->setSelectStatement();
    Essence::query(resFilter);
}


void Dictionary::selectCurrentRow()
{   // Делает запрос к БД по одной строке справочника. Изменяет в текущей модели поля, которые в БД отличаются от таковых в модели.
    // Применяется после работы формул для изменения полей в строке, которые косвенно изменились

    preparedSelectCurrentRow.bindValue(":value", getId());

    Essence::selectCurrentRow();
}


void Dictionary::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->selectStatement();

    command.replace(" ORDER BY", QString(" WHERE %1.%2=:value ORDER BY").arg(getTableName()).arg(getIdFieldName()));

    preparedSelectCurrentRow.prepare(command);
}


/*
void Dictionary::setValue(QString name, QVariant value, int row)
{   // Не будем сохранять переменные в БД сразу, т.к. мы используем скрипты и обновлять будем после исполнения скриптов и с помощью транзакции
    Essence::setValue(name, value, row);
}
*/

void Dictionary::setScriptEngine()
{
    scriptEngine = new FormScriptEngine(this);
}



