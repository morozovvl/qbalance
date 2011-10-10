#include <QModelIndex>
#include "app.h"
#include "dictionary.h"
#include "saldo.h"
#include "document.h"
#include "documenttablemodel.h"
#include "gui/formdocument.h"
#include "gui/mainwindow.h"
#include "mysqlrelationaltablemodel.h"


Document::Document(int oper, Documents* par)
: Essence()
, parent(par)
, operNumber(oper)
{
    Dictionary* dict;
    DbFactory = TApplication::exemplar()->getDBFactory();
    lPrintable = true;
    tableName = DbFactory->getObjectName("проводки");
    tagName = QString("Документ%1").arg(oper);
    formTitle = TApplication::exemplar()->getToperProperty(oper, TApplication::nameFieldName()).toString();
    idFieldName = "p1__" + TApplication::idFieldName();

    dictionaries = new Dictionaries;
    if (dictionaries->open())
    {
        dicts = dictionaries->getDictionaries();
    }

    // Загрузим описание типовой операции
    toper.setTable(DbFactory->getObjectName("vw_топер"));
    toper.setFilter(QString("опер=%1").arg(operNumber));
    toper.setSort(2, Qt::AscendingOrder);
    toper.setEditStrategy(QSqlTableModel::OnManualSubmit);
    toper.select();

    // Составим список справочников, которые используются при работе с документом
    QString dictName;
    QList<QString> spravList;
    for (int i = 0; i < toper.rowCount(); i++)
    {
        // получим имя дебетового справочника из описания проводок
        dictName = toper.record(i).value("дбсправ").toString().trimmed();

        // если имя справочника не пустое, этот справочник "видим" и еще не содержится в списке
        if (dictName.size() > 0 && toper.record(i).value("дбвидим").toBool() && !spravList.contains("дб" + dictName))

            // .. то добавим его в список
            spravList << "дб" + dictName;

        // получим имя кредитового справочника из описания проводок
        dictName = toper.record(i).value("крсправ").toString().trimmed();

        // если имя справочника не пустое, этот справочник "видим" и еще не содержится в списке
        if (!dictName.isEmpty() && toper.record(i).value("крвидим").toBool() && !spravList.contains("кр" + dictName))

            // и если в кредитовом справочнике не ведется количественный учет
            if (!toper.record(i).value("кркол").toBool())

                // .. то добавим его в список
                spravList << "кр" + dictName;

    }

    QModelIndex index;
    for (int i = 0; i < toper.rowCount(); i++)
    {
        dictName = toper.record(i).value("дбсправ").toString().trimmed();
        if (!dictName.isEmpty())
        {
            index = toper.index(i, toper.record().indexOf("дбсправалиас"));
            if (dicts->contains("дб" + dictName) && dicts->contains("кр" + dictName))
                toper.setData(index, QVariant("дб" + dictName));
            else
                toper.setData(index, QVariant(dictName));
        }
        dictName = toper.record(i).value("крсправ").toString().trimmed();
        if (!dictName.isEmpty())
        {
            index = toper.index(i, toper.record().indexOf("крсправалиас"));
            if (dicts->contains("кр" + dictName) && dicts->contains("дб" + dictName))
                toper.setData(index, QVariant("кр" + dictName));
            else
                toper.setData(index, QVariant(dictName));
        }
    }

    QString cAccount, alias;
    for (int i = 0; i < toper.rowCount(); i++) {
        dictName = toper.record(i).value("крсправ").toString().trimmed();
        if (dictName.size() > 0) {
            if (toper.record(i).value("кркол").toBool())
            {      // Если в кредитовом справочнике ведется количественный учет
                cAccount = toper.record(i).value("крсчет").toString().trimmed();
                alias = "saldo" + cAccount;
                if (!dicts->contains(alias))
                {
                    Saldo* sal = new Saldo(cAccount, dictName); // ... то заведем справочник сальдо по указанному счету
                    if (sal->open(1))
                    {
                        sal->setAutoSelect(true);               // автоматически нажимать кнопку Ok, если выбрана одна позиция
                        sal->setQuan(true);
                        sal->setDictionaries(dictionaries);
                        dicts->insert(alias, sal);
                    }
                }
            }
            else
            {
                alias = toper.record(i).value("крсправалиас").toString().trimmed();     // Если количественный учет не ведется
                if (!dicts->contains(alias))
                {
                    dict = new Dictionary(dictName, this);                        // ... то заведем обычный справочник
                    if (dict->open(1))
                    {
                        dict->setConst(toper.record(i).value("крпост").toBool());
                        dict->setDictionaries(dictionaries);
                        dicts->insert(alias, dict);
                    }
                }
            }
        }
    }
    for (int i = 0; i < toper.rowCount(); i++)
    {
        dictName = toper.record(i).value("дбсправ").toString().trimmed();
        if (dictName.size() > 0)
        {
            alias = toper.record(i).value("дбсправалиас").toString().trimmed();
            if (!dicts->contains(alias))
            {
                dict = new Dictionary(dictName, this);
                if (dict->open(1))
                {
                    if (dict->isSet())              // если это набор
                        dict->setAutoAdd(true);     // ... то для дебетовых наборов - автоматическое добавление
                    dict->setDictionaries(dictionaries);
                    dicts->insert(alias, dict);
                }
            }
        }
    }

    foreach (QString dictName, dicts->keys())
    {
        dict = dicts->value(dictName);
        dict->setCanShow(false);
        if (QString(dict->objectName()).compare("Saldo", Qt::CaseInsensitive) != 0)
        {
            dict->setAutoSelect(true);
            dict->setCanShow((dict->isConst() || dict->isSet())? false: true);
        }
        else
            dict->setCanShow(true);
    }
//    setScriptForTable(toper.record(0).value("формулы").toString());
}

Document::~Document() {
}


void Document::getCalculateProperties(const QModelIndex &index) {
    QVariant var;
    int col;
    QString fieldName;
    Essence::getCalculateProperties(index);
    for (int i = 0; i < toper.rowCount(); i++) {
        int prv = toper.record(i).value("номер").toInt();
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("p%1__кол").arg(prv))));
        if (var.isValid()) {
            fieldName = QString("дбсальдо%1__конкол").arg(prv);
            col = tableModel->record().indexOf(fieldName);
            if (col > -1)
                tableModel->setData(index.sibling(index.row(), col), saldo.value(i).dbQuan + var.toDouble());
            fieldName = QString("крсальдо%1__конкол").arg(prv);
            col = tableModel->record().indexOf(fieldName);
            if (col > -1) {
                tableModel->setData(index.sibling(index.row(), col), saldo.value(i).crQuan - var.toDouble());
            }
        }
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("p%1__сумма").arg(prv))));
        if (var.isValid()) {
            fieldName = QString("дбсальдо%1__консальдо").arg(prv);
            col = tableModel->record().indexOf(fieldName);
            if (col > -1)
                tableModel->setData(index.sibling(index.row(), col), saldo.value(i).dbSaldo + var.toDouble());
            fieldName = QString("крсальдо%1__консальдо").arg(prv);
            col = tableModel->record().indexOf(fieldName);
            if (col > -1)
                tableModel->setData(index.sibling(index.row(), col), saldo.value(i).crSaldo - var.toDouble());
        }
    }
}


void Document::setOldCalculateProperties(const QModelIndex &index)
{
    QVariant var;
    prvSaldo sal;
    Essence::setOldCalculateProperties(index);
    saldo.clear();
    for (int i = 0; i < toper.rowCount(); i++)
    {
        int prv = toper.record(i).value("номер").toInt();
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("дбсальдо%1__конкол").arg(prv))));
        sal.dbQuan = (var.isValid() ? var.toDouble() : 0);
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("дбсальдо%1__консальдо").arg(prv))));
        sal.dbSaldo = (var.isValid() ? var.toDouble() : 0);
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("крсальдо%1__конкол").arg(prv))));
        sal.crQuan = (var.isValid() ? var.toDouble() : 0);
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("крсальдо%1__консальдо").arg(prv))));
        sal.crSaldo = (var.isValid() ? var.toDouble() : 0);
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("p%1__кол").arg(prv))));
        if (var.isValid())
        {
            sal.dbQuan = sal.dbQuan - var.toDouble();
            sal.crQuan = sal.crQuan + var.toDouble();
        }
        var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(QString("p%1__сумма").arg(prv))));
        if (var.isValid())
        {
            sal.dbSaldo = sal.dbSaldo - var.toDouble();
            sal.crSaldo = sal.crSaldo + var.toDouble();
        }
        saldo.insert(i, sal);
    }
}


bool Document::calculate(const QModelIndex& index) {
    bool lResult = true;
    if (index.isValid())
        lResult = Essence::calculate(index);
    if (lResult) {
        double itog = 0;
        for (int i = 0; i < toper.rowCount(); i++) {
            QString sign = toper.record(i).value("итоги").toString().trimmed();
            if (sign == "+" || sign == "-") {
                double sum = 0;
                int col = tableModel->record().indexOf(QString("p%1__сумма").arg(i + 1));
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
        parent->getMyRelationalTableModel()->setData(parent->getMyRelationalTableModel()->index(parent->getCurrentRow(), parent->getMyRelationalTableModel()->record().indexOf("сумма")), itog);
    }
    return lResult;
}


bool Document::add()
{
    unlock();               // разблокировать все связанные справочники
    foreach (QString dictName, dicts->keys())
    {
        Dictionary* dict = dicts->value(dictName);
        dict->setMustShow(dict->isConst()? false: dict->canShow()); // Если справочник документа является постоянным, то не показывать его при добавлении новой записи в документ
                                                                    // иначе это справочник должен быть показан, если может быть показан
        dict->setMustShow(dict->getDeep() == 0 ? true : false);     // Если это зависимый справочник, то он не показывается
    }
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
        showError(QString(QObject::tr("Запрещено удалять строки в документах пользователю %2")).arg(TApplication::exemplar()->getLogin()));
    return false;
}


void Document::show()
{   // Перед открытием документа запрашивается его содержимое, а для постоянных справочников в документе устанавливаются их значения
    query();
    if (tableModel->rowCount() > 0) {
        Dictionary* dict;
        QString dictName;
        for (int i = 0; i < toper.rowCount(); i++)
        {
            int prvNumber = toper.record(i).value("номер").toInt();
            dictName = toper.record(i).value("дбсправ").toString().trimmed();   // Получим имя справочника, который участвует в проводках бух.операции по дебету
            if (dicts->contains(dictName))
            {   // если этот справочник открыт в локальных справочниках документа...
                dict = dicts->value(dictName);
                if (dict->isConst())
                {   // ... и помечен как "постоянный"
                    // то установим его значение, которое актуально для всего документа
                    dict->setId(tableModel->record(0).value(QString("p%1__дбкод").arg(prvNumber)).toULongLong());
                }
            }
            dictName = toper.record(i).value("крсправ").toString().trimmed();   // то же самое для справочников по кредиту проводок
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
        for (int i = 0; i < toper.rowCount(); i++) {
            dictName = toper.record(i).value("дбсправ").toString().trimmed();
            if (dictName.compare(dName, Qt::CaseSensitive) == 0) {
                dict = dicts->value(dictName);
                if (dict->isConst()) {
                    DbFactory->setConstDictId("дбкод", id, docId, operNumber, toper.record(i).value("номер").toInt());
                    dict->setId(id.toULongLong());
                }
            }
            dictName = toper.record(i).value("крсправ").toString().trimmed();
            if (dictName.compare(dName, Qt::CaseSensitive) == 0) {
                dict = dicts->value(dictName);
                if (dict->isConst()) {
                    DbFactory->setConstDictId("кркод", id, docId, operNumber, toper.record(i).value("номер").toInt());
                    dict->setId(id.toULongLong());
                }
            }
        }
    }
    Essence::show();
}


bool Document::open()
{
    lInsertable = TApplication::exemplar()->getDictionaryProperty(tableName, "insertable").toBool();
    lDeleteable = TApplication::exemplar()->getDictionaryProperty(tableName, "deleteable").toBool();
    lUpdateable = TApplication::exemplar()->getDictionaryProperty(tableName, "updateable").toBool();
    if (Essence::open()) {
        initForm();
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

    QString selectClause, fromClause, whereClause;
    QStringList prvFieldsList = tableModel->getFieldsList();
    int prv;
    int columnCount = 0;
    int keyColumn   = 0;

    QStringList updateFields;
    updateFields << "кол" << "цена" << "сумма";

    columnsProperties.clear();
    QMap<int, FieldType> fields;
    DbFactory->getColumnsProperties(&fields, tableName);
    // Создадим клаузу проводок в секции SELECT
    for (int i = 0; i < toper.rowCount(); i++)
    {   // Для всех проводок данной типовой операции
        prv = toper.record(i).value("номер").toInt();       // получим номер проводки в типовой операции
        foreach (const QString field, prvFieldsList)
        {// Для всех полей таблицы "проводки"
            if (!selectClause.isEmpty())
            {   // Если уже что-то писали в эту клаузу, то добавим запятую
                selectClause.append(',');
            }
            selectClause.append(QString("p%1.%2 AS p%1__%2").arg(prv).arg(field));  // запишем в клаузу элемент <таблица>.<поле> с именем <таблица>__<поле>
            if (field == "код")
            {// Если в списке полей встретилось поле ключа
                keyColumn = columnCount;// Запомним номер столбца с ключом
            }
            if (updateFields.contains(field))
            {// Если поле входит в список сохраняемых полей
                tableModel->setUpdateInfo(columnCount, keyColumn, field);   // То сохраним информацию, необходимую для генерации команды сохранения этого поля (номер столбца поля, номер столбца ключа и имя поля)
            }
            columnCount++;      // Считаем столбцы
            foreach(int i, fields.keys())
            {
                if (fields.value(i).name == field)
                {
                    DbFactory->addColumnProperties(&columnsProperties, QString("p%1__%2").arg(prv).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, fields.value(i).readOnly);
                }
            }
        }
        if (i == 0)
        {
            fromClause = QString(" FROM %1 p%2").arg(tableName).arg(prv);
            prv1 = prv;
            whereClause = " WHERE";     // Создадим пометку в команде с пустой секцией WHERE.
                                        // Непосредственно перед отправкой команды на сервер
                                        // пустая секция WHERE заполняется реальной с фильтрами для текущего документа
                                        // в фунции transformSelectStatement(QString)
        }
        else
        {
            fromClause.append(QString(" LEFT OUTER JOIN %1 p%2 ON p%3.доккод=p%2.доккод AND p%3.стр=p%2.стр AND p%3.опер=p%2.опер AND p%2.номеропер=%2").arg(tableName).arg(prv).arg(prv1));
        }
    }
    // Соберем команду SELECT для проводок табличной части документа
    selectClause = QString("SELECT ").append(selectClause);
    selectStatement = selectClause + fromClause + whereClause;
    selectClause = "SELECT DISTINCT p.*";
    fromClause = " FROM (" + selectStatement + ") p";

    // Приступим к генерации секции SELECT более высокого уровня
    QString dictName;
    QStringList dictsNames;
    Dictionary* dict;
    for (int i = 0; i < toper.rowCount(); i++) {
        prv = toper.record(i).value("номер").toInt();
        if (toper.record(i).value("дбвидим").toBool())
        {
            dictName = toper.record(i).value("дбсправалиас").toString();
            if (!dictsNames.contains(dictName) && dictName.size() > 0 && dicts->contains(dictName)) {
                DbFactory->getColumnsProperties(&fields, dictName);
                dict = dicts->value(dictName);
                foreach (QString field, dict->getFieldsList()) {
                    selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                    foreach(int i, fields.keys())
                        if (fields.value(i).name == field)
                            DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                }
                fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.p%2__дбкод=%1.код").arg(dictName).arg(prv));
                dictsNames << dictName;
            }
        }
        if (toper.record(i).value("крвидим").toBool())
        {
            dictName = toper.record(i).value("крсправалиас").toString();
            if (!dictsNames.contains(dictName) && dictName.size() > 0 && dicts->contains(dictName)) {
                DbFactory->getColumnsProperties(&fields, dictName);
                dict = dicts->value(dictName);
                foreach (QString field, dict->getFieldsList()) {
                    selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                    foreach(int i, fields.keys())
                        if (fields.value(i).name == field)
                            DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                }
                fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.p%2__кркод=%1.код").arg(dictName).arg(prv));
                dictsNames << dictName;
            }
        }
        DbFactory->getColumnsProperties(&fields, "сальдо");
        QString field;
        if (toper.record(i).value("дбсалвидим").toBool()) {
            dictName = QString("дбсальдо%1").arg(prv);
            if (toper.record(i).value("дбкол").toBool()) {
                field = "конкол";
                selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                foreach(int i, fields.keys())
                    if (fields.value(i).name == field)
                        DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                field = "концена";
                selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                foreach(int i, fields.keys())
                    if (fields.value(i).name == field)
                        DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
            }
            field = "консальдо";
            selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
            foreach(int i, fields.keys())
                if (fields.value(i).name == field)
                    DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
            fromClause.append(QString(" LEFT OUTER JOIN сальдо %1 ON p.p%2__дбсчет=%1.счет AND p.p%2__дбкод=%1.код").arg(dictName).arg(prv));
        }
        if (toper.record(i).value("крсалвидим").toBool()) {
            dictName = QString("крсальдо%1").arg(prv);
            if (toper.record(i).value("кркол").toBool()) {
                field = "конкол";
                selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                foreach(int i, fields.keys())
                    if (fields.value(i).name == field)
                        DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
                field = "концена";
                selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
                foreach(int i, fields.keys())
                    if (fields.value(i).name == field)
                        DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
            }
            field = "консальдо";
            selectClause.append(QString(",%1.%2 AS %1__%2").arg(dictName).arg(field));
            foreach(int i, fields.keys())
                if (fields.value(i).name == field)
                    DbFactory->addColumnProperties(&columnsProperties, QString("%1__%2").arg(dictName).arg(field), fields.value(i).type, fields.value(i).length, fields.value(i).precision, true);
            fromClause.append(QString(" LEFT OUTER JOIN сальдо %1 ON p.p%2__крсчет=%1.счет AND p.p%2__кркод=%1.код").arg(dictName).arg(prv));
        }
    }
    selectStatement = selectClause + fromClause + " ORDER BY p.p1__стр ASC";
    tableModel->setSelectStatement(selectStatement);
    DbFactory->getColumnsRestrictions(tagName, &columnsProperties);
    // Заполним модель пустыми данными. Это необходимо только в случае, если мы сами генерировали команду запроса для модели.
    int oldDocId = docId;
    docId = 0;
    query();
    docId = oldDocId;
}


bool Document::showNextDict()
{             // функция решает, по каким справочникам нужно пробежаться при добавлении новой строки в документе
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
                dict->setMustShow(false);
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
    for (int i = 0; i < toper.rowCount(); i++)
    {
        dbId = 0;
        dictName = toper.record(i).value("дбсправ").toString().trimmed();
        if (dictName.size() > 0)
        {
            dict = dicts->value(dictName);
            dbId = dict->getId();
        }
        crId = 0;
        dictName = toper.record(i).value("крсправ").toString().trimmed();
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
    foreach(QString field, getParent()->getFieldsList())
    {
        printValues->insert(QString("[%1.%2]").arg(getParent()->getTableName()).arg(field), getParent()->getValue(field));
    }
    // Зарядим таблицу
    QStringList EnabledPrvFields;
    EnabledPrvFields << "кол" << "цена" << "сумма";     // список полей таблицы "проводки", которые актуальны при печати документа
    for (int i = 0; i < getTableModel()->rowCount(); i++)
    {
        QSqlRecord rec = getTableModel()->record(i);
        foreach(QString field, getFieldsList())
        {
            if (field.at(0) == 'p' && field.at(1).isDigit())      // если в списке полей встретилось поле, начинающееся с "p<цифра>...",
            {   // т.е. это поле из таблицы "проводки"
                QString fld = field.section("__", 1);               // проверим, актуально ли это поле для печати
                if (EnabledPrvFields.contains(fld))
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


