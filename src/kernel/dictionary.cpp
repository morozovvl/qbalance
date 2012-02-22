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


Dictionary::Dictionary(QString name, QObject *parent): Essence(name, parent) {
    formTitle = "";
    lPrintable = true;
    lIsSet = false;
    lCanShow = true;
    lMustShow = false;
    lIsConst = false;
    lAutoSelect = false;
    dictionaries = TApplication::exemplar()->getDictionaries();
    QSqlRecord tableProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties(tableName);
    if (!tableProperties.isEmpty())
    {
        formTitle = tableProperties.value(TApplication::nameFieldName()).toString();
        lSelectable = tableProperties.value("selectable").toBool();
        lInsertable = tableProperties.value("insertable").toBool();
        lDeleteable = tableProperties.value("deleteable").toBool();
        lUpdateable = tableProperties.value("updateable").toBool();
    }
    lIsSet = TApplication::exemplar()->getDBFactory()->isSet(tableName);
}


Dictionary::~Dictionary() {
}


bool Dictionary::add() {
    if (!lInsertable) {
        showError(QString(QObject::trUtf8("Запрещено добавлять записи в справочник %1 пользователю %2")).arg(
                      TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName),
                      TApplication::exemplar()->getLogin()));
        return false;
    }
    QMap<QString, QVariant> values;
    bool lAddDict = true;
    SearchParameters* parameters = (SearchParameters*)qFindChild<QFrame*>(form->getForm(), "searchParameters");
    if (parameters != 0) {
        QVector<sParam> searchParameters = parameters->getParameters();
        if (searchParameters.size() > 0)
        {
            for (int i = 0; i < searchParameters.size(); i++) {
                if (searchParameters[i].table == getTableName()) {
                    values.insert(searchParameters[i].field, searchParameters[i].value);
                    }
                else {
                    if (searchParameters[i].value.toString().size() > 0) {
                        Dictionary* dict = dictionaries->getDictionary(searchParameters[i].table);
                        dict->query(QString("%1='%2'").arg(nameFieldName).arg(searchParameters[i].value.toString()));
                        if (dict->getTableModel()->rowCount() == 1)
                            values.insert(idFieldName + "_" + searchParameters[i].table, dict->getId(0));
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
    if (lAddDict)
    {
        if (TApplication::exemplar()->getDBFactory()->insertDictDefault(getTableName(), &values))
        {
            query();
            return true;
        }
        return false;
    }
}


bool Dictionary::remove() {
    if (lDeleteable) {
        if (Essence::remove()) {
            TApplication::exemplar()->getDBFactory()->removeDictValue(tableName, getId());
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


void Dictionary::setForm() {
    form = new FormGridSearch();
    form->open(parentForm, this);
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


bool Dictionary::open(int deep) {
    if (lSelectable) {
        if (Essence::open()) {     // Откроем этот справочник
            fieldList = getFieldsList();
            if (deep > 0) {              // Если нужно открыть подсправочники
                int columnCount = fieldList.count();
                for (int i = 0; i < fieldList.count(); i++) {       // Просмотрим список полей
                    QString name = fieldList.at(i).toLower();
                    if (name.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                        name.remove(0, 4);                      // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                        Dictionary* dict = dictionaries->getDictionary(name, deep - 1);
                        if (dict != NULL) {                      // Если удалось открыть справочник
                            QStringList relFieldList = dict->getFieldsList();
                            tableModel->setRelation(i, QSqlRelation(name, "код", "код"));
                            for (int j = 0; j < relFieldList.count(); j++) {       // Просмотрим список полей в подсправочнике
                                if (relFieldList.at(j) != "код") {
                                    tableModel->insertColumns(columnCount, 1);
                                    tableModel->setRelation(columnCount, i, QSqlRelation(name, "код", relFieldList.at(j)));
                                    tableModel->setHeaderData(columnCount, Qt::Horizontal, QVariant(name + "." + relFieldList.at(j)));
                                    columnCount++;
                                }
                            }
                        }
                    }
                }
                deep--;
            }

            // Установим порядок сортировки и стратегию сохранения данных на сервере
            tableModel->setSort(tableModel->fieldIndex(TApplication::nameFieldName()), Qt::AscendingOrder);

            TApplication::exemplar()->getDBFactory()->getColumnsRestrictions(tableName, &columnsProperties);
            dictDeep = deep;
            if (scriptEngine != 0)
            {
                form->initFormEvent();
                return scriptEngine->open("");
            }
            return true;
        }
    }
    QString dictTitle = TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName);
    if (dictTitle.isEmpty())
        dictTitle = tableName;
    showError(QString(QObject::trUtf8("Запрещено просматривать справочник %1 пользователю %2. Либо справочник отсутствует.")).arg(
        dictTitle, TApplication::exemplar()->getLogin()));
    return false;
}


qulonglong Dictionary::getId(int row)
{
    if (isSet())
    {
/*
        QString filter;
        QStringList fieldList = getFieldsList();
        for (int i = 0; i < fieldList.count(); i++) {       // Просмотрим список полей
            QString fieldName = fieldList.at(i).toLower();
            if (fieldName.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                QString dictName = fieldName;
                dictName.remove(0, 4);
                Dictionary* dict = dictionaries->getDictionary(dictName);
                if (dict != NULL) {                      // Если удалось открыть справочник
                    if (filter.size() > 0)
                        filter.append(" AND ");
                    filter.append(QString("%1=%2").arg(fieldName).arg(dict->getId()));
                }
            }
        }
        query(filter);
*/
        query();
        qulonglong result = Essence::getId(0);
        if (result == 0)
        {
            if (add())
            {
                query();
                return Essence::getId(0);
            }
            return 0;
        }
        return result;
    }
    return Essence::getId(row);
}


void Dictionary::query(QString defaultFilter)
{
    if (defaultFilter.size() == 0)
    {
        QString filter;
        QVector<sParam> searchParameters = ((FormGridSearch*)form)->getSearchParameters()->getParameters();
        for (int i = 0; i < searchParameters.size(); i++) {
            if (filter.size() > 0)
                filter.append(" AND ");
            QString text = searchParameters[i].value.toString();
            while (text.contains("  "))                                   // Если есть пробелы, идущие подряд
                text.replace("  ", " ");                                  // то уберем их
            text = "%" + text.replace(" ", "%") + "%";
            filter.append(QString("%1.%2 ILIKE '%3'").arg(searchParameters[i].table).arg(searchParameters[i].field).arg(text));
        }
        Essence::query(filter);
    }
    else
        Essence::query(defaultFilter);
}
