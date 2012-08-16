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

#include "dictionary.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/searchparameters.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../engine/documentscriptengine.h"



Dictionary::Dictionary(QString name, QObject *parent): Essence(name, parent)
{
    formTitle = "";
    lPrintable = true;
    lIsSet = false;
    lCanShow = true;
    lMustShow = false;
    lIsConst = false;
    lAutoSelect = false;
    isDepend = false;
    ftsEnabled = false;
    dictionaries = TApplication::exemplar()->getDictionaries();
    QSqlRecord tableProperties = db->getDictionariesProperties(tableName);
    if (!tableProperties.isEmpty())
    {
        formTitle = tableProperties.value(db->getObjectName("имя")).toString().trimmed();
        lSelectable = tableProperties.value("selectable").toBool();
        lInsertable = tableProperties.value("insertable").toBool();
        lDeleteable = tableProperties.value("deleteable").toBool();
        lUpdateable = tableProperties.value("updateable").toBool();
    }
    lIsSet = db->isSet(tableName);
}


Dictionary::~Dictionary() {
}


bool Dictionary::add()
{
    if (!lInsertable)
    {
        showError(QString(QObject::trUtf8("Запрещено добавлять записи в справочник %1 пользователю %2")).arg(
                      TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName),
                      TApplication::exemplar()->getLogin()));
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
                            dict->query(QString("%1='%2'").arg(nameFieldName).arg(searchParameters[i].value.toString()));
                            if (dict->getTableModel()->rowCount() == 1)
                                // Далее первый параметр такой хитрый с запросом к БД имени поля, т.к. searchParameters[i].table - всегда в нижнем регистре, а idFieldName - может быть и в верхнем и в нижнем
                                // поэтому настоящее имя поля код_<имя таблицы> получим путем запроса к БД
                                values.insert(db->getObjectName(QString("%1.%2").arg(searchParameters[i].value.toString())
                                                                                .arg(idFieldName.toLower() + "_" + searchParameters[i].table)), dict->getId(0));
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
        showError(QString(QObject::trUtf8("Запрещено удалять записи из справочника %1 пользователю %2")).arg(
            TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName),
            TApplication::exemplar()->getLogin()));
    return false;
}


void Dictionary::setForm()
{
    form = new FormGridSearch();
    form->open(parentForm, this, getTagName());
    if (form->isDefaultForm())
    {
        QPushButton* button;
        button = form->getButtonCancel();
        if (button != NULL)
            form->getButtonCancel()->hide();
        button = form->getButtonOk();
        if (button != NULL)
            button->setToolTip(trUtf8("Закрыть справочник"));
        button = form->getButtonAdd();
        if (button != NULL)
            button->setToolTip(trUtf8("Создать новую запись в справочнике"));
        button = form->getButtonDelete();
        if (button != NULL)
            button->setToolTip(trUtf8("Удалить запись из справочника"));
        button = form->getButtonPrint();
        if (button != NULL)
            button->setToolTip(trUtf8("Распечатать выбранные записи из справочника"));
        button = form->getButtonRequery();
        if (button != NULL)
            button->setToolTip(trUtf8("Обновить справочник (загрузить повторно с сервера)"));
    }
}


bool Dictionary::open(int deep)
{
    if (Table::open())
    {     // Откроем этот справочник
        fieldList = getFieldsList();
        if (deep > 0)
        {              // Если нужно открыть подсправочники
            int columnCount = fieldList.count();
            for (int i = 0; i < fieldList.count(); i++)
            {       // Просмотрим список полей
                QString name = fieldList.at(i);
                if (name.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    name.remove(0, 4);                          // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                    name = name.toLower();                      // и переведем в нижний регистр, т.к. имена таблиц в БД могут быть только маленькими буквами
                    Dictionary* dict = dictionaries->getDictionary(name, deep - 1);
                    if (dict != NULL)
                    {                      // Если удалось открыть справочник
                        if (!lIsSet)
                            dict->setDependent(true);       // Справочник может считаться зависимым, если основной не является набором справочников
                        QStringList relFieldList = dict->getFieldsList();
                        tableModel->setRelation(i, QSqlRelation(name, idFieldName, idFieldName));
                        for (int j = 0; j < relFieldList.count(); j++)
                        {       // Просмотрим список полей в подсправочнике
                            if (relFieldList.at(j) != idFieldName)
                            {    // добавляем в модель все колонки зависимого справочника, кроме колонки "код"
                                tableModel->insertColumns(columnCount, 1);
                                tableModel->setRelation(columnCount, i, QSqlRelation(name, idFieldName, relFieldList.at(j)));
                                tableModel->setHeaderData(columnCount, Qt::Horizontal, QVariant(name + "__" + relFieldList.at(j)));
                                columnCount++;
                            }
                        }
                    }
                }
            }
            deep--;
        }
        // Проверим, имеется ли в справочнике полнотекстовый поиск
        ftsEnabled = fieldList.contains(db->getObjectName(tableName + ".fts"), Qt::CaseInsensitive);
        // Установим порядок сортировки и стратегию сохранения данных на сервере
        tableModel->setSort(tableModel->fieldIndex(db->getObjectName("имя")), Qt::AscendingOrder);
        db->getColumnsRestrictions(tableName, &columnsProperties);

        initForm();
        setScriptEngine();
        if (scriptEngine != 0)
        {
            if (scriptEngine->open(tableName + ".qs"))
            {
                scriptEngine->evaluate();
                form->initFormEvent();
                return true;
            }
            return false;
        }
        return true;
    }
    QString dictTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName).trimmed();
    if (dictTitle.isEmpty())
        dictTitle = tableName;
    showError(QString(QObject::trUtf8("Запрещено просматривать справочник <%1> пользователю %2. Либо справочник отсутствует.")).arg(dictTitle, TApplication::exemplar()->getLogin()));
    return false;
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
    QString filter = ((FormGridSearch*)form)->getSearchParameters()->getFilter();
    if (filter.size() > 0)
    {
        if (resFilter.size() > 0)
            resFilter.append(" AND " + filter);
        else
            resFilter = filter;
    }
    Essence::query(resFilter);
}



