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
    lIsLocked = false;
    lIsConst = false;
    lAutoSelect = false;
    lAutoAdd = false;
    dictionaries = 0;
    QSqlRecord tableProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties(tableName);
    if (!tableProperties.isEmpty())
    {
        formTitle = tableProperties.value(TApplication::nameFieldName()).toString();
        lSelectable = tableProperties.value("selectable").toBool();
        lInsertable = tableProperties.value("insertable").toBool();
        lDeleteable = tableProperties.value("deleteable").toBool();
        lUpdateable = tableProperties.value("updateable").toBool();
    }
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
    SearchParameters* parameters = (SearchParameters*)qFindChild<QFrame*>(form->getForm(), "searchParameters");
    if (parameters != 0) {
        QStringList fields;
        QVariantList values;
        QVector<sParam> searchParameters;
        parameters->getParameters(searchParameters);
        bool lAddDict = true;
        for (int i = 0; i < searchParameters.size(); i++) {
            if (searchParameters[i].table == getTableName()) {
                fields << searchParameters[i].field;
                values << searchParameters[i].value;
                }
            else {
                if (searchParameters[i].value.toString().size() > 0) {
                    Dictionary* dict = TApplication::exemplar()->getDictionaries()->getDictionary(searchParameters[i].table);
                    if (dict != 0 && !dict->getValue(TApplication::nameFieldName()).toString().contains(searchParameters[i].value.toString().trimmed(), Qt::CaseInsensitive))
                        lAddDict = false;
                    }
            }
        }
        if (lAddDict)
            return TApplication::exemplar()->getDBFactory()->insertDictDefault(getTableName(), fields, values);
    }
    return TApplication::exemplar()->getDBFactory()->insertDictDefault(getTableName());
}

bool Dictionary::remove() {
    if (lDeleteable) {
        if (Essence::remove()) {
            TApplication::exemplar()->getDBFactory()->removeDictValue(tableName, getId());
            return true;
        }
    }
    else
        showError(QString(QObject::trUtf8("Запрещено удалять записи из справочника %1 пользователю %2")).arg(
            TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tableName),
            TApplication::exemplar()->getLogin()));
    return false;
}

void Dictionary::setLock(bool lock) {
    if (lock) {                             // Если блокируем все связанные справочники
        if (dictionaries != 0) {
            QStringList columns = getFieldsList();
            foreach (QString column, columns) {
                if (column.left(4) == idFieldName + "_") {
                    qulonglong id = getValue(column).toULongLong();
                    column.remove(0, 4);
                    Dictionary* dict = dictionaries->getDictionary(column);
                    if (dict != 0) {
                        dict->setId(id);
                        dict->setCanShow(canShow());
                        dict->setLock(lock);
                    }
                }
            }
        }
    }
    lIsLocked = true;
}

void Dictionary::setForm() {
    form = new FormGridSearch();
    form->open(parentForm, this);
}

bool Dictionary::open(int deep) {
    if (lSelectable) {
        if (Essence::open()) {     // Откроем этот справочник
            QStringList fieldList = getFieldsList();
            if (deep > 0) {              // Если нужно открыть подсправочники
                int columnCount = fieldList.count();
                for (int i = 0; i < fieldList.count(); i++) {       // Просмотрим список полей
                    QString name = fieldList.at(i).toLower();
                    if (name.left(4) == idFieldName + "_") {        // Если поле ссылается на другую таблицу
                        name.remove(0, 4);                      // Уберем префикс "код_", останется только название таблицы, на которую ссылается это поле
                        TApplication::exemplar()->getDictionaries()->addDictionary(name, deep--);
                        Dictionary* dict = TApplication::exemplar()->getDictionaries()->getDictionary(name);
                        if (dict != NULL) {                 // Если удалось открыть справочник
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
            }

            // Установим порядок сортировки и стратегию сохранения данных на сервере
            tableModel->setSort(tableModel->fieldIndex(TApplication::nameFieldName()), Qt::AscendingOrder);

            // определим, это набор или обычный справочник
            if (fieldList.contains(TApplication::nameFieldName(), Qt::CaseInsensitive)) {
                lIsSet = false;                                     // это справочник, т.к. есть поле ИМЯ
            }
            else {
                for (int k = 0; k < fieldList.count(); k++)
                    if (QString(fieldList.at(k)).contains(idFieldName + "_", Qt::CaseInsensitive)) {
                        lIsSet = true;                              // это набор, т.к. нет поля ИМЯ и есть поля-ссылки на другие справочники
                        break;
                    }
                }
            TApplication::exemplar()->getDBFactory()->getColumnsRestrictions(tableName, &columnsProperties);
            dictDeep = deep;
            initForm();
            if (scriptEngine != 0)
            {
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

