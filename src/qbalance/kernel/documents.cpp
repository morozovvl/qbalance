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

#include <QtCore/QString>
#include "documents.h"
#include "document.h"
#include "../kernel/app.h"
#include "../kernel/dictionaries.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/formdocuments.h"
#include "../gui/tableview.h"
#include "../storage/dbfactory.h"
#include "../engine/documentscriptengine.h"
#include "../engine/reportcontext.h"


Documents::Documents(int, QObject *parent): Dictionary(parent)
{
    currentDocument = 0;
}


Documents::~Documents()
{
}


void Documents::postInitialize(int opNumber, QObject *parent)
{
    Dictionary::postInitialize("", parent);

    lViewable  = true;
    tableName  = "документы";
    operNumber = opNumber;
    tagName    = QString("СписокДокументов%1").arg(operNumber);
    prefix = "АТРИБУТЫ__";

    app->debug(1, "");
    app->debug(1, QString("Begin open documents list (ОПЕР=%1)").arg(operNumber));

    db->getToperData(operNumber, &topersList);              // Получим список типовых операций

    operName = db->getTopersProperties(operNumber, "имя").toString().trimmed();
    subFormTitle = operName;
    formTitle  = QString("%1 - %2").arg(operName).arg(QObject::trUtf8("Список документов"));

    lInsertable = db->getTopersProperties(operNumber, "insertable").toBool();
    lDeleteable = db->getTopersProperties(operNumber, "deleteable").toBool();
    lUpdateable = db->getTopersProperties(operNumber, "updateable").toBool();

    scriptEngine = 0;
    scriptEngineEnabled = false;
    doSubmit = true;
    lPrintable = true;
    photoEnabled = false;
}


QList<ToperType>* Documents::getTopersList()
{
    return &topersList;
}


QString Documents::getAttrPrefix()
{
    return prefix;
}


Document* Documents::getDocument()
{
    return currentDocument;
}


Document* Documents::getDocument(int docId)
{
    setCurrentDocument(docId);
    return currentDocument;
}



bool Documents::add()
{
    QDate date = QDate().currentDate();
    if ((date < TApplication::exemplar()->getBeginDate() || date > TApplication::exemplar()->getEndDate()))
    {
        QMessageBox::warning(app->getMainWindow(), "Внимание!", "Cегодняшняя дата находится вне рабочего периода. Установите правильный рабочий период.");
        if (date < TApplication::exemplar()->getBeginDate())
            date = TApplication::exemplar()->getBeginDate();
        else if (date > TApplication::exemplar()->getEndDate())
            date = TApplication::exemplar()->getEndDate();
    }
    else
    {
        int strNum = db->addDoc(operNumber, date);
        if (strNum > 0)
        {
            int newRow = tableModel->rowCount();
/*
            if (newRow == 0)
            {
                query();
                setId(strNum);
            }
            else
            {
*/
                tableModel->insertRow(newRow);          // POSSIBLY MEMORY LEAK
                grdTable->reset();
                grdTable->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
                setCurrentRow(newRow);
                updateCurrentRow(strNum);
//            }
            setCurrentDocument(strNum);
            saveOldValues();
            form->setButtons();
            grdTable->setFocus();
            return true;
        }
    }
    return false;
}


bool Documents::remove(bool noAsk)
{
    bool result = false;
    bool canRemove = true;
    if (lDeleteable)
    {
        if (Essence::remove(noAsk))
        {
            scriptEngineEnabled = true;
            if (scriptEngine != 0)
                   canRemove = scriptEngine->eventBeforeDeleteDocument();
            if (canRemove)
            {
                db->removeDoc(getValue("код").toInt());
                query();
                if (scriptEngine != 0)
                       scriptEngine->eventAfterDeleteDocument();
                result = true;
            }
            scriptEngineEnabled = false;
        }
    }
    else
        app->showError(QString(QObject::trUtf8("Запрещено удалять документы пользователю %2")).arg(app->getLogin()));
    return result;
}


void Documents::view()
{
    currentDocument->show();
}


void Documents::show()
{
    query();
    Dictionary::show();
}


void Documents::setCurrentDocument(int strNum)
{
    setId(strNum);
    currentDocument->setDocId(strNum);
}


void Documents::query(QString, bool)
{
    Essence::query(QString("%1 BETWEEN cast('%2' as date) AND cast('%3' as date) AND %4=0 AND %5='%6'").arg(db->getObjectNameCom("документы.дата"))
                                                                                                       .arg(app->getBeginDate().toString(app->dateFormat()))
                                                                                                       .arg(app->getEndDate().toString(app->dateFormat()))
                                                                                                       .arg(db->getObjectNameCom("документы.авто"))
                                                                                                       .arg(db->getObjectNameCom("документы.опер"))
                                                                                                       .arg(QString::number(operNumber)));
}


bool Documents::open()
{
    bool result = false;
    if (operNumber > 0 && Essence::open())
    {     // Откроем этот справочник
        setOrderClause();
        prepareSelectCurrentRowCommand();

        tableModel->setTestSelect(true);
        query();
        tableModel->setTestSelect(false);

        currentDocument = Document::create<Document>(operNumber, this);
        if (currentDocument->open())
        {
            currentDocument->setFormTitle(subFormTitle);
            scriptEngine = currentDocument->getScriptEngine();
            result = true;
        }
    }
    else
        app->showError(QString(QObject::trUtf8("Запрещено просматривать операцию <%1> пользователю %2")).arg(formTitle, app->getLogin()));
    app->debug(1, QString("End open documents list (ОПЕР=%1)").arg(operNumber));
    app->debug(1, "");
    return result;
}


void Documents::close()
{
    currentDocument->close();
    delete currentDocument;
    scriptEngine = 0;
    currentDocument = 0;
    Essence::close();
}


void Documents::setOrderClause(QString orderClause)
{
    if (orderClause.size() > 0)
        Table::setOrderClause(orderClause);
    else
        Table::setOrderClause(QString("%1, \"%2\".%3").arg(db->getObjectNameCom(tableName + ".дата"))
                                                 .arg(tableName)
                                                 .arg(db->getObjectNameCom(tableName + ".номер")));
}


void Documents::setValue(QString n, QVariant value)
{

    for (int i = 0; i < columnsProperties.count(); i++)
    {
        if (n.toUpper() == columnsProperties.at(i).column)
        {
            Essence::setValue(n, value, getCurrentRow());
            return;
        }
    }
    for (int i = 0; i < attrFields.count(); i++)
    {
        if ((n.toUpper() == attrFields.at(i).column) || (n.toUpper() == prefix + attrFields.at(i).column))
        {
            Essence::setValue(prefix + n, value, getCurrentRow());
            return;
        }
    }
}


QVariant Documents::getValue(QString n, int row)
{
    QVariant result;
    for (int i = 0; i < columnsProperties.count(); i++)
    {
        if (n.toUpper() == columnsProperties.at(i).column)
        {
            return Dictionary::getValue(n, row);
        }
    }
    for (int i = 0; i < attrFields.count(); i++)
    {
        if (n.toUpper() == attrFields.at(i).column)
        {
            return Dictionary::getValue(prefix + n, row);
        }
    }
    return result;
}


void Documents::setForm(QString formName)
{
    if (form != 0)
    {
        form->close();
        delete form;
    }
    form = new FormDocuments();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть список документов"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новый документ (Ctrl+Ins)"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить документ (Ctrl+Del)"));
    form->appendToolTip("buttonView",       trUtf8("Просмотреть документ (F2)"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить список документов (загрузить повторно с сервера) (F3)"));

    form->open(parentForm, this, formName);
    parameters = 0;
}


bool Documents::setTableModel(int)
{
    if (Essence::setTableModel(0))
    {
        FieldType fld;
        int keyColumn   = 0;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            fld = columnsProperties.at(i);
            if (fld.table == columnsProperties.at(0).table)
            {
                QString name = columnsProperties.at(i).column;
                if (name == idFieldName)
                    keyColumn = i;
                else
                    tableModel->setUpdateInfo(name, tableName, name, columnsProperties.at(i).type, columnsProperties.at(i).length, columnsProperties.at(i).precision, i, keyColumn);
            }
        }

        QString selectStatement = Dictionaries::getDictionarySqlSelectStatement(tableName);

        if (topersList.at(0).docattributes)
        {
            QString attrName = QString("%1%2").arg(db->getObjectName("докатрибуты")).arg(operNumber).toLower();
            QString attrSelectStatement = Dictionaries::getDictionarySqlSelectStatement(attrName, prefix);
            if (attrSelectStatement.size() > 0)
            {
                selectStatement.replace(" FROM ", ",a.* FROM ");
                selectStatement.append(QString(" LEFT OUTER JOIN (%1) a ON \"%2\".\"%3\"=a.\"%4\"").arg(attrSelectStatement)
                                                                                                   .arg(tableName)
                                                                                                   .arg(db->getObjectName(tableName + ".код"))
                                                                                                   .arg(prefix + "КОД"));
                db->getColumnsProperties(&attrFields, attrName);
                FieldType fld;
                int keyColumn   = 0;
                int columnCount = columnsProperties.count();
                for (int i = 0; i < attrFields.count(); i++)
                {
                    fld = attrFields.at(i);
                    if (fld.table == attrName)
                    {
                        if (fld.name == db->getObjectName(attrName + ".код"))
                            keyColumn = columnCount;
                        else
                            tableModel->setUpdateInfo(prefix + fld.name, fld.table, fld.name, fld.type, fld.length, fld.precision, columnCount, keyColumn);
                    }
                    fld.column = prefix + fld.column;
                    columnsProperties.append(fld);
                    columnCount++;
                }
            }
        }
        tableModel->setSelectStatement(selectStatement);
        db->getColumnsRestrictions(tableName, &columnsProperties);
        return true;
    }
    return false;
}


void Documents::preparePrintValues()
{
    if (reportScriptEngine != 0)
    {
        reportScriptEngine->getReportContext()->setValue("документы.СУММА", getSumValue(db->getObjectName("документы.сумма")));
        reportScriptEngine->getReportContext()->setValue("документы.ИМЯ", operName);
        Dictionary::preparePrintValues();
    }
}


void Documents::showItog()
{
    if (form != 0)
        ((FormDocuments*)form)->showItog();
}


bool Documents::calculate(bool)
{
    bool lResult = true;
    saveChanges();            // сохраним изменения
    return lResult;
}


QString Documents::getDocumentSqlSelectStatement(int oper,  QList<ToperType>* topersList, QList<FieldType>* columnsProperties, int* retPrv1)
{
    QString selectStatement;
    QStringList columns;
    DBFactory* db = TApplication::exemplar()->getDBFactory();
    if (topersList->count() == 0)
    {   // В случае, если таблица проводок типовой операции пустая, то запрашиваем ее с сервера. Но она может быть и не пустая, если ее сформировал мастер
        db->getToperData(oper, topersList);
    }
    if (topersList->count() > 0)
    {
        QString selectClause, fromClause, whereClause;
        int prv, prv1 = 0;
        if (columnsProperties != 0)
            columnsProperties->clear();

        // Создадим клаузу проводок в секции SELECT
        QString tableName = db->getObjectName("проводки").toLower();
        QString idFieldName = db->getObjectName("код");
        QStringList prvFieldsList = db->getFieldsList(tableName, 0);
        QList<FieldType> fields;
        db->getColumnsProperties(&fields, tableName);
        for (int i = 0; i < topersList->count(); i++)
        {   // Для всех проводок данной типовой операции
            prv = topersList->at(i).number;                     // получим номер проводки в типовой операции
            if (prv > 0)
            {
                foreach (const QString field, prvFieldsList)
                {// Для всех полей таблицы "проводки"
                    selectClause += (!selectClause.isEmpty() ? "," : "");                   // Добавим запятую, если это необходимо
                    selectClause.append(QString("p%1.\"%2\" AS \"P%1__%3\"").arg(prv).arg(db->getObjectName("проводки." + field)).arg(field.toUpper()));  // запишем в клаузу элемент <таблица>.<поле> с именем <таблица>__<поле>
                    for (int i = 0; i < fields.count(); i++)
                    {
                        if (fields.at(i).table == tableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            db->addColumnProperties(columnsProperties, tableName, QString("P%1__%2").arg(prv).arg(field), fields.at(i).type, fields.at(i).length, fields.at(i).precision, fields.at(i).readOnly, fields.at(i).constReadOnly);
                    }
                }
                if (i == 0)
                {
                    fromClause = QString(" FROM \"%1\" p%2").arg(tableName).arg(prv);
                    prv1 = prv;
                    whereClause = " WHERE p";       // Создадим пометку в команде с пустой секцией WHERE.
                                                    // Непосредственно перед отправкой команды на сервер
                                                    // пустая секция WHERE заполняется реальной с фильтрами для текущего документа
                                                    // в фунции transformSelectStatement(QString)
                                                    // p в конце означает, что нужно ставить фильтр для типовой операции с проводками
                }
                else
                    fromClause.append(QString(" LEFT OUTER JOIN \"%1\" p%2 ON p%3.%4=p%2.%4 AND p%3.%5=p%2.%5 AND p%3.%6=p%2.%6 AND p%2.%7=%2").arg(tableName).arg(prv).arg(prv1).arg(db->getObjectNameCom("проводки.доккод")).arg(db->getObjectNameCom("проводки.стр")).arg(db->getObjectNameCom("проводки.опер")).arg(db->getObjectNameCom("проводки.номеропер")));
            }
        }
        // Соберем команду SELECT для проводок табличной части документа
        selectClause = QString("SELECT ").append(selectClause);
        selectStatement = selectClause + fromClause + whereClause;

        fromClause = QString("(%1) p").arg(selectStatement);
        selectClause = "SELECT DISTINCT p.*";
        // Приступим к генерации секции SELECT, которая относится к задействованным в типовой операции справочникам
        QString dictName, prDictName__, prDictName, prefix;
        QStringList dictsNames;

        for (int i = 0; i < topersList->count(); i++)
        {
            prv = topersList->at(i).number;
            if (!topersList->at(i).dbConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).dbDict.toLower();
                if (topersList->at(i).dbAcc == topersList->at(i).crAcc && topersList->at(i).dbDict == topersList->at(i).crDict)
                {
                    prefix = "ДБ";
                    prDictName__ = QString(prefix + dictName + "__").toUpper();
                    prDictName = QString(prefix + dictName).toLower();
                }
                else
                {
                    prefix = "";
                    prDictName__ = dictName;
                    prDictName = dictName;
                }
                if (dictName.size() > 0 && !dictsNames.contains(prefix + dictName))
                {   // Если в по дебетовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (db->isSet(dictName))
                    { // Это набор (справочников)
                      // Сгенерируем команду SELECT для набора и входящих в него справочников
                        QString setSelectClause, setFromClause;
                        foreach (QString fieldName, db->getFieldsList(dictName, 0))
                        {
                            if (fieldName.left(4) == idFieldName + "_")
                            {        // Если поле ссылается на другую таблицу
                                QString setDictName = fieldName.toLower();
                                setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                db->getColumnsProperties(&fields, setDictName);
                                foreach (QString setDictFieldName, db->getFieldsList(setDictName, 0))
                                {
                                    QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper());
                                    if (!columns.contains(alias))
                                    {
                                        setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3\"").arg(setDictName).arg(setDictFieldName).arg(alias));
                                        selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(prDictName).arg(alias));
                                        for (int i = 0; i < fields.count(); i++)
                                            if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                                db->addColumnProperties(columnsProperties, prDictName, alias, fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                                        columns.append(alias);
                                    }
                                }
                                if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                {
                                    setFromClause.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(db->getObjectNameCom(setDictName + ".код")));
                                }
                                else
                                    setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(db->getObjectNameCom(setDictName + ".код")));
                            }
                            else
                            {
                                db->getColumnsProperties(&fields, dictName);
                                QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(fieldName.toUpper());
                                if (!columns.contains(alias))
                                {
                                    selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(fieldName).arg(alias));
                                    for (int i = 0; i < fields.count(); i++)
                                        if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                                            db->addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(fieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                                    columns.append(alias);
                                }
                            }
                        }
                        setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(db->getObjectNameCom(dictName + ".код")).append(setSelectClause);
                        setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                        setSelectClause.append(setFromClause);
                        fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(prDictName).arg(prv).arg(db->getObjectName("проводки.дбкод").toUpper()).arg(db->getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        db->getColumnsProperties(&fields, dictName);
                        foreach (QString field, db->getFieldsList(dictName, 0))
                        {
                            QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(field.toUpper());
                            if (!columns.contains(alias))
                            {
                                selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(field).arg(alias));
                                for (int i = 0; i < fields.count(); i++)
                                    if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                        db->addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                                columns.append(alias);
                            }
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(prDictName).arg(prv).arg(db->getObjectName("проводки.дбкод").toUpper()).arg(db->getObjectName(dictName + ".код")));
                    }
                    dictsNames << prefix + dictName;
                }
            }
            if (!topersList->at(i).crConst)
            {   // Если счет не является постоянным, т.е. он фигурирует в табличной части
                dictName = topersList->at(i).crDict.toLower();
                if (topersList->at(i).dbAcc == topersList->at(i).crAcc && topersList->at(i).dbDict == topersList->at(i).crDict)
                {
                    prefix = "КР";
                    prDictName__ = QString(prefix + dictName + "__").toUpper();
                    prDictName = QString(prefix + dictName).toLower();
                }
                else
                {
                    prefix = "";
                    prDictName__ = dictName;
                    prDictName = dictName;
                }
                if (dictName.size() > 0 && !dictsNames.contains(prefix + dictName))
                {   // Если в по кредитовому счету указан какой-либо справочник и этот справочник мы еще не обрабатывали
                    if (db->isSet(dictName))
                    {  // Это набор (справочников)
                        // Сгенерируем команду SELECT для набора и входящих в него справочников
                          QString setSelectClause, setFromClause;
                          foreach (QString fieldName, db->getFieldsList(dictName, 0))
                          {
                              if (fieldName.left(4) == idFieldName + "_")
                              {        // Если поле ссылается на другую таблицу
                                  QString setDictName = fieldName.toLower();
                                  setDictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                                  db->getColumnsProperties(&fields, setDictName);
                                  foreach (QString setDictFieldName, db->getFieldsList(setDictName, 0))
                                  {
                                      QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(setDictName.toUpper()).arg(setDictFieldName.toUpper());
                                      if (!columns.contains(alias))
                                      {
                                          setSelectClause.append(QString(",\"%1\".\"%2\" AS \"%3\"").arg(setDictName).arg(setDictFieldName).arg(alias));
                                          selectClause.append(QString(",\"%1\".\"%2\" AS \"%2\"").arg(prDictName).arg(alias));
                                          for (int i = 0; i < fields.count(); i++)
                                              if (fields.at(i).table == setDictName && fields.at(i).name.toUpper() == setDictFieldName.toUpper() && columnsProperties != 0)
                                                  db->addColumnProperties(columnsProperties, prDictName, alias, fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                                          columns.append(alias);
                                      }
                                  }
                                  if (setDictName.left(9) == "документы" && setDictName.size() > 9)
                                  {
                                      setFromClause.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(db->getObjectNameCom(setDictName + ".код")));
                                  }
                                  else
                                      setFromClause.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".%4").arg(setDictName).arg(dictName).arg(fieldName).arg(db->getObjectNameCom(setDictName + ".код")));
                              }
                              else
                              {
                                  db->getColumnsProperties(&fields, dictName);
                                  QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(fieldName.toUpper());
                                  if (!columns.contains(alias))
                                  {
                                      selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(fieldName).arg(alias));
                                      for (int i = 0; i < fields.count(); i++)
                                          if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                                              db->addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(fieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                                      columns.append(alias);
                                  }
                              }
                          }
                          setSelectClause = QString("SELECT \"%1\".%2").arg(dictName).arg(db->getObjectNameCom(dictName + ".код")).append(setSelectClause);
                          setFromClause = QString(" FROM \"%1\"").arg(dictName).append(setFromClause);
                          setSelectClause.append(setFromClause);
                          fromClause.append(QString(" LEFT OUTER JOIN (%1) \"%2\" ON p.\"P%3__%4\"=\"%2\".%5").arg(setSelectClause).arg(prDictName).arg(prv).arg(db->getObjectName("проводки.кркод").toUpper()).arg(db->getObjectNameCom(dictName + ".код")));
                    }
                    else
                    {  // Это обычный справочник
                        db->getColumnsProperties(&fields, dictName);
                        foreach (QString field, db->getFieldsList(dictName, 0))
                        {
                            QString alias = QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName.toUpper()).arg(field.toUpper());
                            if (!columns.contains(alias))
                            {
                                selectClause.append(QString(",%1.\"%2\" AS \"%3\"").arg(prDictName).arg(field).arg(alias));
                                for (int i = 0; i < fields.count(); i++)
                                    if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                                        db->addColumnProperties(columnsProperties, prDictName, QString("%1%2__%3").arg(prefix.size() > 0 ? prDictName__ : "").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                                columns.append(alias);
                            }
                        }
                        fromClause.append(QString(" LEFT OUTER JOIN %1 ON p.\"P%2__%3\"=%1.%4").arg(prDictName).arg(prv).arg(db->getObjectName("проводки.кркод").toUpper()).arg(db->getObjectName(dictName + ".код")));
                    }
                    dictsNames << prefix + dictName;
                }
            }
            // Приступим к генерации списка сальдо
            QString salTableName = db->getObjectName("сальдо");
            db->getColumnsProperties(&fields, salTableName);
            QString field;
            if (topersList->at(i).dbSaldoVisible)
            {
                dictName = QString("дб%1").arg(topersList->at(i).dbAcc);
                if (topersList->at(i).dbQuan)
                {
                    field = db->getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            db->addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                    field = db->getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            db->addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                }
                field = db->getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                for (int i  = 0; i < fields.count(); i++)
                    if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                        db->addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.\"P%3__%4\"=%2.%5 AND p.\"P%3__%6\"=%2.%7").arg(db->getObjectNameCom("сальдо")).arg(dictName).arg(prv).arg(db->getObjectName("проводки.дбсчет").toUpper()).arg(db->getObjectNameCom("сальдо.счет")).arg(db->getObjectName("проводки.дбкод").toUpper()).arg(db->getObjectNameCom("сальдо.код")));
            }
            if (topersList->at(i).crSaldoVisible)
            {
                dictName = QString("кр%1").arg(topersList->at(i).crAcc);
                if (topersList->at(i).crQuan)
                {
                    field = db->getObjectName("сальдо.конкол");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            db->addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                    field = db->getObjectName("сальдо.концена");
                    selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                    for (int i  = 0; i < fields.count(); i++)
                        if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                            db->addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                }
                field = db->getObjectName("сальдо.консальдо");
                selectClause.append(QString(",%1.\"%2\" AS \"%3__%4\"").arg(dictName).arg(field).arg(dictName.toUpper()).arg(field.toUpper()));
                for (int i  = 0; i < fields.count(); i++)
                    if (fields.at(i).table == salTableName && fields.at(i).name.toUpper() == field.toUpper() && columnsProperties != 0)
                        db->addColumnProperties(columnsProperties, salTableName, QString("%1__%2").arg(dictName).arg(field.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                fromClause.append(QString(" LEFT OUTER JOIN %1 %2 ON p.\"P%3__%4\"=%2.%5 AND p.\"P%3__%6\"=%2.%7").arg(db->getObjectNameCom("сальдо")).arg(dictName).arg(prv).arg(db->getObjectName("проводки.крсчет").toUpper()).arg(db->getObjectNameCom("сальдо.счет")).arg(db->getObjectName("проводки.кркод").toUpper()).arg(db->getObjectNameCom("сальдо.код")));
            }
        }

        if (topersList->at(0).attributes)
        {   // Если имеются атрибуты для документа в данной операции
            QString attrName = QString("%1%2").arg(db->getObjectName("атрибуты")).arg(oper).toLower();
            db->getColumnsProperties(&fields, attrName);
            selectClause += ", a.*,";
            QString attrSelectClause = "";
            QString attrFromClause = "";
            foreach (QString fieldName, db->getFieldsList(attrName, 0))
            {
                if (fieldName.left(4) == idFieldName + "_")
                {        // Если поле ссылается на другую таблицу
                    QString dictName = fieldName.toLower();
                    dictName.remove(0, 4);                       // Получим наименование справочника, который входит в набор
                    QString alias = QString("%1").arg(fieldName.toUpper());
                    if (!columns.contains(alias))
                    {
                        columns.append(alias);
                    }
                    attrSelectClause.append(QString("a.\"%1\" AS %2,").arg(fieldName).arg(fieldName.toUpper()));
                    for (int i = 0; i < fields.count(); i++)
                        if (fields.at(i).table == attrName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                            db->addColumnProperties(columnsProperties, attrName, fieldName, fields.at(i).type, fields.at(i).length, fields.at(i).precision, false, false, 0, 1);
                    db->getColumnsProperties(&fields, dictName);
                    foreach (QString dictFieldName, db->getFieldsList(dictName, 0))
                    {
                        QString alias = QString("%1__%2").arg(dictName.toUpper()).arg(dictFieldName.toUpper());
                        attrSelectClause.append(QString("\"%1\".\"%3\" AS \"%2__%4\",").arg(dictName).arg(dictName.toUpper()).arg(dictFieldName).arg(dictFieldName.toUpper()));
                        if (!columns.contains(alias))
                        {
                            for (int i = 0; i < fields.count(); i++)
                                if (fields.at(i).table == dictName && fields.at(i).name.toUpper() == dictFieldName.toUpper() && columnsProperties != 0)
                                    db->addColumnProperties(columnsProperties, dictName, QString("%1__%2").arg(dictName).arg(dictFieldName.toUpper()), fields.at(i).type, fields.at(i).length, fields.at(i).precision, true, true, 0, 1);
                            columns.append(alias);
                        }
                    }
                    attrFromClause.append(QString(" LEFT OUTER JOIN %1 ON a.%2=%1.%3").arg(dictName.toLower()).arg(fieldName).arg(db->getObjectName(dictName.toLower() + ".код")));
                }
                else
                {
                    QString alias = fieldName.toUpper();
                    attrSelectClause.append(QString("a.\"%1\" AS \"%2\",").arg(fieldName).arg(fieldName.toUpper()));
                    if (!columns.contains(alias))
                    {
                        for (int i = 0; i < fields.count(); i++)
                            if (fields.at(i).table == attrName && fields.at(i).name.toUpper() == fieldName.toUpper() && columnsProperties != 0)
                                db->addColumnProperties(columnsProperties, attrName, fieldName, fields.at(i).type, fields.at(i).length, fields.at(i).precision, false, false);
                        columns.append(alias);
                    }
                }
            }
            selectClause.chop(1);
            attrSelectClause.chop(1);
            attrSelectClause = QString("SELECT DISTINCT ").append(attrSelectClause);
            attrFromClause = QString(" FROM %1 a").arg(attrName).append(attrFromClause);
            attrSelectClause.append(attrFromClause);


            fromClause.append(QString(" LEFT OUTER JOIN (%1) a ON p.\"P1__%2\"=a.%3 AND p.\"P1__%4\"=a.%5").arg(attrSelectClause)
                                                                                                          .arg(db->getObjectName("атрибуты.доккод").toUpper())
                                                                                                          .arg(db->getObjectNameCom("атрибуты.доккод"))
                                                                                                          .arg(db->getObjectName("атрибуты.стр").toUpper())
                                                                                                          .arg(db->getObjectNameCom("атрибуты.стр")));
        }
        if (retPrv1 != 0)
            *retPrv1 = prv1;
        if (topersList->at(0).attributes && topersList->at(0).number == 0)
            selectStatement = selectClause + " FROM " + fromClause + QString(" ORDER BY %1 ASC;").arg(db->getObjectNameCom("атрибуты.стр"));
        else
            selectStatement = selectClause + " FROM " + fromClause + QString(" ORDER BY \"P1__%1\" ASC;").arg(db->getObjectName("проводки.стр").toUpper());

        // Получим заголовки столбцов
        db->getColumnsHeaders(QString("Документ%1").arg(oper), columnsProperties);
    }
    return selectStatement;
}
