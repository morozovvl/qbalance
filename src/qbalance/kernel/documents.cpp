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
#include "../gui/tableview.h"


Documents::Documents(int opNumber, QObject *parent): Dictionary(parent)
{
    lViewable  = true;
    tableName  = "документы";
    operNumber = opNumber;
    tagName    = QString("СписокДокументов%1").arg(operNumber);
    prefix = "АТРИБУТЫ__";
    QSqlRecord operProperties = db->getTopersProperties(operNumber);
    db->getToperData(operNumber, &topersList);              // Получим список типовых операций
    formTitle  = QString("%1 - %2").arg(operProperties.value(db->getObjectName("имя")).toString()).arg(QObject::trUtf8("Список документов"));
    subFormTitle = operProperties.value(db->getObjectName("имя")).toString().trimmed();
    lInsertable = operProperties.value("insertable").toBool();
    lDeleteable = operProperties.value("deleteable").toBool();
    lUpdateable = operProperties.value("updateable").toBool();
}


Documents::~Documents()
{
}


void Documents::show()
{
    QModelIndex index = form->getCurrentIndex();
    bool gotoLast = tableModel->rowCount() > 0 ? false : true;  // если список документов пока пустой, то после его загрузки
                                                                // перейдем к последней записи, иначе останемся на той записи,
                                                                // на которой находимся сейчас
    query();
    form->restoreCurrentIndex(index);
    if (gotoLast)
    {
        form->selectRow(tableModel->rowCount() - 1);
    }
    Dictionary::show();
}


bool Documents::add()
{
    QDate date = QDate().currentDate();
    if (!(date >= TApplication::exemplar()->getBeginDate() && date <= TApplication::exemplar()->getEndDate()))
    {
        if (date < TApplication::exemplar()->getBeginDate())
            date = TApplication::exemplar()->getBeginDate();
        else if (date > TApplication::exemplar()->getEndDate())
            date = TApplication::exemplar()->getEndDate();
    }

    int strNum = db->addDoc(operNumber, date);
    if (strNum > 0)
    {
         int newRow = tableModel->rowCount();
         if (newRow == 0)
         {
             query();
             form->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
         }
         else
         {
             tableModel->insertRow(newRow);
             form->getGridTable()->reset();
             form->selectRow(newRow);            // Установить фокус таблицы на последнюю, только что добавленную, запись
             updateCurrentRow(strNum);
         }
         return true;
    }
    return false;
}


bool Documents::remove()
{
    if (lDeleteable)
    {
        if (Essence::remove())
        {
            db->removeDoc(getValue("код").toInt());
            query();
            return true;
        }
    }
    else
        app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено удалять документы пользователю %2")).arg(app->getLogin()));
    return false;
}


void Documents::view()
{
    currentDocument->setDocId(getValue("код").toInt());
    currentDocument->show();
}


void Documents::query(QString filter)
{
    Q_UNUSED(filter)

    // Чтобы не потерять текущий документ после обновления, запомним его номер, а потом поставим на него указатель записи
    qulonglong currentDocId = getId();
    QModelIndex index = form->getCurrentIndex();

    Essence::query(QString("%1 BETWEEN cast('%2' as date) AND cast('%3' as date) AND %4=0 AND %5='%6'").arg(db->getObjectNameCom("документы.дата"))
                                                                                                       .arg(TApplication::exemplar()->getBeginDate().toString("dd.MM.yyyy"))
                                                                                                       .arg(TApplication::exemplar()->getEndDate().toString("dd.MM.yyyy"))
                                                                                                       .arg(db->getObjectNameCom("документы.авто"))
                                                                                                       .arg(db->getObjectNameCom("документы.опер"))
                                                                                                       .arg(QString::number(operNumber)));
    if (tableModel->rowCount() > 0)
    {
        // Восстановим указатель на текущую запись
        form->getGridTable()->reset();
        if (tableModel->rowCount() > 0 && currentDocId > 0)
        {
            for (int i = 0; i < tableModel->rowCount(); i++)
            {
                if (getId(i) == currentDocId)
                {
                    form->selectRow(i);             // Текущая запись найдена
                    return;                         // Перейдем на нее
                }
            }
        }
        if (index.row() > tableModel->rowCount() - 1)       // Если мы стояли на последней записи, но она теперь удалена
            form->selectRow(tableModel->rowCount() - 1);    // то перейдем на новую последнюю
        else
            form->restoreCurrentIndex(index);   // Иначе останемся стоять на том же месте на экране
    }
}


bool Documents::open()
{
    if (Essence::open())
    {     // Откроем этот справочник

        initForm();

        tableModel->setTestSelect(true);
        query();
        tableModel->setTestSelect(false);

        currentDocument = new Document(operNumber, this);
        currentDocument->setPhotoEnabled(true);
        if (currentDocument->open())
        {
            currentDocument->setFormTitle(subFormTitle);
            return true;
        }
    }
    app->showError(QString(QObject::trUtf8("Запрещено просматривать операцию <%1> пользователю %2")).arg(formTitle, app->getLogin()));
    return false;
}


void Documents::close()
{
    currentDocument->close();
    Essence::close();
    delete currentDocument;
}


void Documents::setOrderClause()
{
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
            Dictionary::setValue(n, value);
            return;
        }
    }
    for (int i = 0; i < attrFields.count(); i++)
    {
        if ((n.toUpper() == attrFields.at(i).column) || (n.toUpper() == prefix + attrFields.at(i).column))
        {
            Dictionary::setValue(prefix + n, value);
            return;
        }
    }
}


QVariant Documents::getValue(QString n)
{
    QVariant result;
    for (int i = 0; i < columnsProperties.count(); i++)
    {
        if (n.toUpper() == columnsProperties.at(i).column)
        {
            return Dictionary::getValue(n);
        }
    }
    for (int i = 0; i < attrFields.count(); i++)
    {
        if (n.toUpper() == attrFields.at(i).column)
        {
            return Dictionary::getValue(prefix + n);
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

    form = new FormGrid();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть список документов"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новый документ"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить документ"));
    form->appendToolTip("buttonView",       trUtf8("Просмотреть документ"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить список документов (загрузить повторно с сервера)"));

    form->open(parentForm, this, formName);
}


void Documents::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->selectStatement();

    command = command.left(command.indexOf(" WHERE "));
    command += QString(" WHERE \"%1\".\"%2\"=:value").arg(getTableName()).arg(idFieldName);

    preparedSelectCurrentRow.prepare(command);
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

            tableModel->setUpdateInfo(name, tableName, name, columnsProperties.at(i).length, i, keyColumn);
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
                        tableModel->setUpdateInfo(prefix + fld.name, fld.table, fld.name, fld.length, columnCount, keyColumn);
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
