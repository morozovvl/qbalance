#include <QModelIndex>
#include "dictionary.h"
#include "saldo.h"
#include "document.h"
#include "../engine/documentscriptengine.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formdocument.h"
#include "../storage/documenttablemodel.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"


Document::Document(int oper, Documents* par)
: Essence()
, parent(par)
, operNumber(oper)
{
    DbFactory = TApplication::exemplar()->getDBFactory();
    lPrintable = true;
    tableName = DbFactory->getObjectName("проводки");
    tagName = QString("Документ%1").arg(oper);
    formTitle = TApplication::exemplar()->getDBFactory()->getTopersProperties(oper).value(TApplication::nameFieldName()).toString();
    idFieldName = "p1__" + TApplication::idFieldName();

    dictionaries = new Dictionaries();
    if (dictionaries->open())
    {
        dicts = dictionaries->getDictionaries();
    }

    QMap<QString, DictType> dictsList;  // Список справочников, которые будут присутствовать в документе
    DbFactory->getToperData(operNumber, &topersList, &dictsList);

    // Создадим локальный для документа список справочников
    Dictionary* dict;
    foreach (QString dictName, dictsList.keys())
    {
        if (dictName == "saldo")
        {
            Saldo* sal = dictionaries->getSaldo(dictsList.value(dictName).acc, dictsList.value(dictName).name);
            if (sal != 0)
            {
                sal->setAutoSelect(true);               // автоматически нажимать кнопку Ok, если выбрана одна позиция
                sal->setQuan(true);
                sal->setCanShow((dictsList.value(dictName).isConst || sal->isSet())? false: true);
            }
        }
        else
        {
            dict = dictionaries->getDictionary(dictName, dictsList.value(dictName).name);
            if (dict != 0)
            {
                if (dict->isSet())              // если это набор
                    dict->setAutoAdd(true);     // ... то для дебетовых наборов - автоматическое добавление
                dict->setCanShow(true);
                dict->setConst(dictsList.value(dictName).isConst);
            }
        }
    }

    foreach (QString dictName, dicts->keys())
    {
        dict = dicts->value(dictName);
        dict->setMustShow(dict->isConst()? false: dict->canShow()); // Если справочник документа является постоянным, то не показывать его при добавлении новой записи в документ
                                                                    // иначе это справочник должен быть показан, если может быть показан
        dict->setMustShow(dict->getDeep() == 0 ? dict->isMustShow() : false);     // Если это зависимый справочник, то он не показывается
    }

    QSqlRecord docProperties = TApplication::exemplar()->getDBFactory()->getDictionariesProperties(tableName);
    lInsertable = docProperties.value("insertable").toBool();
    lDeleteable = docProperties.value("deleteable").toBool();
    lUpdateable = docProperties.value("updateable").toBool();
}

Document::~Document() {
}


bool Document::calculate(const QModelIndex& index) {
    bool lResult = true;
    if (index.isValid())
        lResult = Essence::calculate(index);
    if (lResult) {
        double itog = 0;
        for (int i = 0; i < topersList.count(); i++)
        {
            QString sign = topersList.at(i).itog;
            if (sign == "+" || sign == "-") {
                double sum = 0;
                int col = tableModel->record().indexOf(QString("p%1__сумма").arg(topersList.at(i).number));
                for (int j = 0; j < tableModel->rowCount(); j++) {
                    sum += tableModel->data(tableModel->index(j, col)).toDouble();
                }
                if (sign == "+")
                    itog += sum;
                else
                    itog -= sum;
            }
        }
        MyNumericEdit* itogWidget = (MyNumericEdit*)qFindChild<QLineEdit*>(form->getForm(), "itogNumeric");
        if (itogWidget != 0)
            itogWidget->setValue(itog);
        parent->setValue("сумма", itog);
    }
    else
    {
        if (scriptEngine->getScriptResult())
        {
            TApplication::exemplar()->showError(scriptEngine->getErrorMessage());
        }
    }
    return lResult;
}


bool Document::add()
{
    unlock();               // Разблокируем все связанные справочники, чтобы можно было показать те, которые надо показать
    if (showNextDict())     // Показать все справочники, которые должны быть показаны перед добавлением новой записи
    {
        insertDocString();
        return true;
    }
    return false;
}


bool Document::remove() {
    if (lDeleteable) {
        if (Essence::remove()) {
            DbFactory->removeDocStr(docId, getValue("p1__стр").toInt());
            return true;
        }
    }
    else
        showError(QString(QObject::trUtf8("Запрещено удалять строки в документах пользователю %2")).arg(TApplication::exemplar()->getLogin()));
    return false;
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
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("p%1__дбкод").arg(prvNumber)).toULongLong());
                }
            }
            dictName = topersList.at(i).crDictAlias;   // то же самое для справочников по кредиту проводок
            if (dicts->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = dicts->value(dictName);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("p%1__кркод").arg(prvNumber)).toULongLong());
                }
            }
        }
    }
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
                    DbFactory->setConstDictId("дбкод", id, docId, operNumber, topersList.at(i).number);
                    dict->setId(id.toULongLong());
                }
            }
            dictName = topersList.at(i).crDictAlias;
            if (dictName.compare(dName, Qt::CaseSensitive) == 0) {
                dict = dicts->value(dictName);
                if (dict->isConst()) {
                    DbFactory->setConstDictId("кркод", id, docId, operNumber, topersList.at(i).number);
                    dict->setId(id.toULongLong());
                }
            }
        }
    }
    Essence::show();
}


bool Document::open()
{
    if (Essence::open()) {
        initForm();
        if (scriptEngine != 0)
        {
            bool result = scriptEngine->open(SCRIPT_DIR + QString("формулы%1").arg(operNumber));
            if (result)
                scriptEngine->evaluate();
            return result;
        }
        return true;
    }
    return false;
}


void Document::close()
{
    foreach(QString dictName, dicts->keys()) {
        dicts->value(dictName)->close();
    }
    Essence::close();
}


void Document::setForm()
{
    form = new FormDocument();
    form->open(parentForm, (Document*)this);
}


void Document::setScriptEngine()
{
    scriptEngine = new DocumentScriptEngine(this);
}


QString Document::transformSelectStatement(QString string)
{   // Модифицирует команду SELECT... заменяя пустую секцию WHERE реальным фильтром с номером текущего документа
    // Вызывается перед каждым запросом содержимого табличной части документа
    string.replace(" WHERE", QString(" WHERE p%3.доккод=%1 AND p%3.опер=%2 AND p%3.номеропер=%3").arg(docId).arg(operNumber).arg(prv1));
    return string;
}


void Document::setTableModel()
{   // Генерирует заготовку запроса для получения данных для табличной части документа
    // Вызывается 1 раз
    tableModel = new DocumentTableModel();
    tableModel->setParent(this);
    tableModel->setTable(tableName);
    tableModel->setBlockUpdate(!isUpdateable());
    QList<ToperType> topersList;
    selectStatement = DbFactory->getDocumentSqlSelectStatement(operNumber, &topersList, &columnsProperties, &prv1);
    if (selectStatement.size() > 0)
    {
        tableModel->setSelectStatement(selectStatement);
        DbFactory->getColumnsRestrictions(tagName, &columnsProperties);

        // Соберем информацию об обновляемых полях таблицы "проводки"
        QStringList updateFields;
        updateFields << DbFactory->getObjectName("проводки.кол") << DbFactory->getObjectName("проводки.цена") << DbFactory->getObjectName("проводки.сумма");
        int columnCount = 0;
        int keyColumn   = 0;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            QString field = columnsProperties.value(i).name;
            field = field.mid(field.indexOf("__") + 2);
            if (field == DbFactory->getObjectName("проводки.код"))
            {// Если в списке полей встретилось поле ключа
                keyColumn = columnCount;                                    // Запомним номер столбца с ключом
            }
            if (updateFields.contains(field))
            {// Если поле входит в список сохраняемых полей
                tableModel->setUpdateInfo(columnCount, keyColumn, field);   // То сохраним информацию, необходимую для генерации команды сохранения этого поля (номер столбца поля, номер столбца ключа и имя поля)
            }
            columnCount++;      // Считаем столбцы
        }

        // Заполним модель пустыми данными. Это необходимо только в случае, если мы сами генерировали команду запроса для модели.
        int oldDocId = docId;
        docId = 0;
        query();
        docId = oldDocId;
    }
}


bool Document::showNextDict()
{  // функция решает, по каким справочникам нужно пробежаться при добавлении новой строки в документе
    bool anyShown = true;
    foreach (QString dictName, dicts->keys()) {
        Dictionary* dict = dicts->value(dictName);
        if (dict->isMustShow() && !dict->isLocked()) {
            dict->exec();
            if (dict->isFormSelected()) {
                if (dict->getTableModel()->rowCount() == 0) {       // Если в выбранном справочнике нет записей
                    anyShown = false;                               // то считать, что этот справочник не был показан и не давать добавить строчку в документ
                    break;
                }
                dict->setLock(true);    // заблокируем справочник, чтобы повторно его не вводить
            }
            else {
                anyShown = false;    // пользователь отказался от работы со справочниками. Прекратим процесс добавления записи
                break;
            }
        }
    }
    return anyShown;
}


void Document::unlock()
{
    Dictionary* dict;
    foreach (QString dictName, dicts->keys())
    {
        dict = dicts->value(dictName);
        if (!dict->isConst())
            dict->unlock();
    }
}


void Document::insertDocString()
{
    Dictionary* dict;
    QString dictName, parameter;
    qulonglong dbId, crId;
    for (int i = 0; i < topersList.count(); i++)
    {
        dbId = 0;
        dictName = topersList.at(i).dbDictAlias;
        if (dictName.size() > 0)
        {
            dict = dicts->value(dictName);
            dbId = dict->getId();
        }
        crId = 0;
        dictName = topersList.at(i).crDictAlias;
        if (dictName.size() > 0)
        {
            dict = dicts->value(dictName);
            crId = dict->getId();
        }
        parameter.append(QString("%1,%2,0,0,0,").arg(dbId).arg(crId));
    }
    DbFactory->addDocStr(operNumber, docId, parameter);
}


void Document::preparePrintValues(QMap<QString, QVariant>* printValues)
{
    Essence::preparePrintValues(printValues);
    // Зарядим постоянные справочники
    foreach (QString dictName, dicts->keys())
    {
        Dictionary* dict = dicts->value(dictName);
        if (dict->isConst())
        {   // Нам нужны только постоянные справочники
            foreach(QString field, dict->getFieldsList())
            {
                if (field.left(4) != TApplication::exemplar()->getDBFactory()->getIdFieldPrefix())       // Если поле не является ссылкой на другой справочник
                {
                    printValues->insert(QString("[%1.%2]").arg(dictName).arg(field), dict->getValue(field));
                }
            }
        }
    }
    // Зарядим реквизиты документа
    QStringList enabledFields;
    enabledFields << "дата" << "датавремя" << "номер" << "комментарий" << "сумма";
    foreach(QString field, getParent()->getFieldsList())
    {
        if (enabledFields.contains(field))
        {
            printValues->insert(QString("[%1.%2]").arg(getParent()->getTableName()).arg(field), getParent()->getValue(field));
        }
    }
    // Зарядим таблицу проводок
    enabledFields.clear();
    enabledFields << "кол" << "цена" << "сумма";     // список полей таблицы "проводки", которые актуальны при печати документа
    for (int i = 0; i < getTableModel()->rowCount(); i++)
    {
        QSqlRecord rec = getTableModel()->record(i);
        foreach(QString field, getFieldsList())
        {
            if (field.at(0) == 'p' && field.at(1).isDigit())      // если в списке полей встретилось поле, начинающееся с "p<цифра>...",
            {   // т.е. это поле из таблицы "проводки"
                QString fld = field.section("__", 1);               // проверим, актуально ли это поле для печати
                if (enabledFields.contains(fld))
                {
                    printValues->insert(QString("[Таблица%1.%2]").arg(i+1).arg(field), rec.value(field));
                }
            }
            else
            {
                printValues->insert(QString("[Таблица%1.%2]").arg(i+1).arg(field), rec.value(field));
            }
        }
    }

}


