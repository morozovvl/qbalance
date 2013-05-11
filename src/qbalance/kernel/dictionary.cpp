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
    sortOrder = "";
    dictionaries = app->getDictionaries();
    QSqlRecord tableProperties = db->getDictionariesProperties(tableName);
    if (!tableProperties.isEmpty())
    {
        formTitle = tableProperties.value(db->getObjectName("доступ_к_справочникам.имя_в_списке")).toString().trimmed();
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
                if (dict != 0)                       // Если удалось открыть справочник
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
            updateCurrentRow();
        }
        else
        {   // Во время работы скриптов произошла ошибка
            restoreOldValues();
        }
    }
    return true;
}


qulonglong Dictionary::getId(int row)
{
    if (!lIsSet)
        return Essence::getId(row);

    // Если это набор, то продолжаем
    QString filter;
    QString variables, values;
    for (int i = 0; i < fieldList.count(); i++)
    {       // Просмотрим список полей
        QString name = fieldList.at(i);
        if (name.left(4) == idFieldName + "_")
        {        // Если поле ссылается на другую таблицу
            if (filter.size() > 0)
                filter.append(" AND ");
            filter.append(name + "=");

            if (variables.size() > 0)
                variables.append(",");
            variables.append(name);

            name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
            name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
            Dictionary* dict = dictionaries->getDictionary(name);
            if (dict != 0)                       // Если удалось открыть справочник
            {
                filter.append(QString("%1").arg(dict->getId()));
                if (values.size() > 0)
                    values.append(",");
                values.append(QString("%1").arg(dict->getId()));
            }
            else
                return 0;
        }
    }
    if (filter.size() > 0)
    {
        query(filter);
        if (tableModel->rowCount() == 0)
        {
            QString command = QString("INSERT INTO %1 (%2) VALUES (%3);").arg(tableName).arg(variables).arg(values);
            qDebug() << command;
            db->exec(command);
            query(filter);
        }
        return Essence::getId(0);
    }
    return 0;
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


bool Dictionary::open(int)
{
    dictTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName).trimmed();
    if (dictTitle.size() == 0)
        dictTitle = tableName;
    if (Essence::open())
    {
        tableModel->setTestSelect(true);
        query();
        tableModel->setTestSelect(false);

        // Откроем этот справочник
        fieldList = getFieldsList();

        // Проверим, имеется ли в справочнике полнотекстовый поиск
        ftsEnabled = fieldList.contains(db->getObjectName(tableName + ".fts"), Qt::CaseInsensitive);

        // Установим порядок сортировки
        if (isSet())
            setSortClause(sortOrder);
        else
            setSortClause(QString("\"%1\".%2").arg(tableName)
                                          .arg(db->getObjectNameCom(tableName + ".имя")));

        return true;
    }
    return false;
}


bool Dictionary::setTableModel(int)
{
    if (Essence::setTableModel(0))
    {
        tableModel->setSelectStatement(db->getDictionarySqlSelectStatement(tableName));
        db->getColumnsRestrictions(tableName, &columnsProperties);

        QStringList tables;
        tables.append(columnsProperties.at(0).table);

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
                tableModel->setUpdateInfo(fld.name, fld.table, fld.name, i, keyColumn);
            }

            if (!tables.contains(fld.table) && dictionaries != 0)
            {
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
        }
        return true;
    }
    return false;
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
    Essence::query(resFilter);
}


void Dictionary::updateCurrentRow()
{   // Делает запрос к БД по одной строке справочника. Изменяет в текущей модели поля, которые в БД отличаются от таковых в модели.
    // Применяется после работы формул для изменения полей в строке, которые косвенно изменились

    preparedSelectCurrentRow.bindValue(":value", getId());

    Essence::updateCurrentRow();
}


void Dictionary::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->selectStatement();

    command.replace(" ORDER BY", QString(" WHERE \"%1\".\"%2\"=:value ORDER BY").arg(getTableName()).arg(getIdFieldName()));

    preparedSelectCurrentRow.prepare(command);
}



