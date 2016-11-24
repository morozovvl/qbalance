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
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/formdocuments.h"
#include "../gui/tableview.h"
#include "../storage/dbfactory.h"
#include "../engine/documentscriptengine.h"
#include "../engine/reportcontext.h"


Documents::Documents(int, QObject *parent): Dictionary(parent)
{
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

    QSqlRecord operProperties = db->getTopersProperties(operNumber);
    db->getToperData(operNumber, &topersList);              // Получим список типовых операций
    operName = operProperties.value(db->getObjectName("имя")).toString().trimmed();
    formTitle  = QString("%1 - %2").arg(operName).arg(QObject::trUtf8("Список документов"));
    subFormTitle = operProperties.value(db->getObjectName("имя")).toString().trimmed();
    lInsertable = operProperties.value("insertable").toBool();
    lDeleteable = operProperties.value("deleteable").toBool();
    lUpdateable = operProperties.value("updateable").toBool();
    scriptEngine = 0;
    scriptEngineEnabled = false;
    lPrintable = true;
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
            if (newRow == 0)
            {
                query();
                setId(strNum);
            }
            else
            {
                int column = getCurrentColumn();
                tableModel->insertRow(newRow);          // POSSIBLY MEMORY LEAK
                grdTable->reset();
                grdTable->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
                updateCurrentRow(strNum);
                grdTable->selectionModel()->setCurrentIndex(getCurrentIndex().sibling(newRow, column), QItemSelectionModel::Select);
            }
            setCurrentDocument(strNum);
            currentRow = tableModel->rowCount() - 1;
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
    setCurrentDocument(getId());
    currentRow = getCurrentRow();
    currentDocument->show();
}


void Documents::setCurrentDocument(int strNum)
{
    currentDocument->setDocId(strNum);
}


void Documents::query(QString, bool)
{
    Essence::query(QString("%1 BETWEEN cast('%2' as date) AND cast('%3' as date) AND %4=0 AND %5='%6'").arg(db->getObjectNameCom("документы.дата"))
                                                                                                       .arg(TApplication::exemplar()->getBeginDate().toString("dd.MM.yyyy"))
                                                                                                       .arg(TApplication::exemplar()->getEndDate().toString("dd.MM.yyyy"))
                                                                                                       .arg(db->getObjectNameCom("документы.авто"))
                                                                                                       .arg(db->getObjectNameCom("документы.опер"))
                                                                                                       .arg(QString::number(operNumber)));
}


bool Documents::open()
{
    bool result = false;
    if (operNumber > 0 && Essence::open())
    {     // Откроем этот справочник
//        initFormEvent();
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
            Essence::setValue(n, value, currentRow);
            return;
        }
    }
    for (int i = 0; i < attrFields.count(); i++)
    {
        if ((n.toUpper() == attrFields.at(i).column) || (n.toUpper() == prefix + attrFields.at(i).column))
        {
            Essence::setValue(prefix + n, value, currentRow);
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
        int keyColumn   = 0;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            QString name = columnsProperties.at(i).column;
            if (name == idFieldName)
                keyColumn = i;

            tableModel->setUpdateInfo(name, tableName, name, columnsProperties.at(i).type, columnsProperties.at(i).length, columnsProperties.at(i).precision, i, keyColumn);
        }

        QString selectStatement = db->getDictionarySqlSelectStatement(tableName);

        if (topersList.at(0).docattributes)
        {
            QString attrName = QString("%1%2").arg(db->getObjectName("докатрибуты")).arg(operNumber).toLower();
            QString attrSelectStatement = db->getDictionarySqlSelectStatement(attrName, prefix);
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


void Documents::updateCurrentRow(int strNum)
{
    Dictionary::updateCurrentRow(strNum);
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



