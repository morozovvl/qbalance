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


Documents::Documents(int opNumber, QObject *parent): Dictionary(parent) {
    lViewable  = true;
    tableName  = "документы";
    operNumber = opNumber;
    tagName    = QString("СписокДокументов%1").arg(operNumber);
    QSqlRecord operProperties = db->getTopersProperties(operNumber);
    db->getToperData(operNumber, &topersList);              // Получим список типовых операций
    formTitle  = QString("%1 - %2").arg(operProperties.value(db->getObjectName("имя")).toString()).arg(QObject::trUtf8("Список документов"));
    subFormTitle = operProperties.value(db->getObjectName("имя")).toString().trimmed();
    lInsertable = operProperties.value("insertable").toBool();
    lDeleteable = operProperties.value("deleteable").toBool();
    lUpdateable = operProperties.value("updateable").toBool();
}


Documents::~Documents() {
}


void Documents::show() {
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


bool Documents::add() {
    QDate date = QDate().currentDate();
    if (!(date >= TApplication::exemplar()->getBeginDate() && date <= TApplication::exemplar()->getEndDate())) {
        if (date < TApplication::exemplar()->getBeginDate())
            date = TApplication::exemplar()->getBeginDate();
        else if (date > TApplication::exemplar()->getEndDate())
            date = TApplication::exemplar()->getEndDate();
    }
    if (db->addDoc(operNumber, date))
    {
        query();
        form->selectRow(tableModel->rowCount() - 1);            // Установить фокус таблицы на последнюю, только что добавленную, запись
        return true;
    }
    return false;
}


bool Documents::remove() {
    if (lDeleteable) {
        if (Essence::remove()) {
            db->removeDoc(getValue("код").toInt());
            query();
            return true;
        }
    }
    else
        app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено удалять документы пользователю %2")).arg(app->getLogin()));
    return false;
}


void Documents::view() {
    currentDocument->setDocId(getValue("код").toInt());
    currentDocument->show();
}


void Documents::query(QString filter) {
    Q_UNUSED(filter)
    Essence::query(QString("%1 BETWEEN cast('%2' as date) AND cast('%3' as date) AND %4=0 AND %5='%6'").arg(db->getObjectNameCom("документы.дата"))
                                                                                                       .arg(TApplication::exemplar()->getBeginDate().toString("dd.MM.yyyy"))
                                                                                                       .arg(TApplication::exemplar()->getEndDate().toString("dd.MM.yyyy"))
                                                                                                       .arg(db->getObjectNameCom("документы.авто"))
                                                                                                       .arg(db->getObjectNameCom("документы.опер"))
                                                                                                       .arg(QString::number(operNumber)));
}


bool Documents::open() {
    if (Essence::open()) {     // Откроем этот справочник
        fieldList = getFieldsList();
        int keyColumn   = 0;
        for (int i = 0; i < fieldList.count(); i++)
        {       // Просмотрим список полей
            QString name = fieldList.at(i);
            if (name == idFieldName)
                keyColumn = i;
            tableModel->setUpdateInfo(name, tableName, name, i, keyColumn);
        }
        // Установим порядок сортировки
        setSortClause(QString("%1, \"%2\".%3").arg(db->getObjectNameCom(tableName + ".дата"))
                                          .arg(tableName)
                                          .arg(db->getObjectNameCom(tableName + ".номер")));

        currentDocument = new Document(operNumber, this);
        if (currentDocument->open())
        {
            currentDocument->setFormTitle(subFormTitle);
            currentDocument->setPhotoEnabled(true);
            return true;
        }
    }
    app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено просматривать операцию <%1> пользователю %2")).arg(
                  formTitle,
                  app->getLogin()));
    return false;
}


void Documents::close() {
    currentDocument->close();
    delete currentDocument;
    Dictionary::close();
}


void Documents::setForm() {
    form = new FormGrid();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть список документов"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новый документ"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить документ"));
    form->appendToolTip("buttonView",       trUtf8("Просмотреть документ"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить список документов (загрузить повторно с сервера)"));

    form->open(parentForm, this);
}


void Documents::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->selectStatement();

    command = command.left(command.indexOf(" WHERE "));
    command += QString(" WHERE %1.%2=:value").arg(getTableName()).arg(getIdFieldName());

    preparedSelectCurrentRow.prepare(command);
}


QString Documents::transformSelectStatement(QString string)
{
/*
    if (topersList.at(0).docattributes)
    {
        if (!string.contains("INNER JOIN"))
        {
            string.replace(" FROM ", ", a.* FROM ");
            string.replace(" WHERE ", QString(" LEFT OUTER JOIN \"%1%2\" a ON \"%3\".%4=a.%5 WHERE ").arg(db->getObjectName("докатрибуты"))
                                                                                                      .arg(operNumber)
                                                                                                      .arg(tableName)
                                                                                                      .arg(db->getObjectNameCom(tableName + ".код"))
                                                                                                      .arg(db->getObjectNameCom("докатрибуты.код")));
        }
    }
*/
    return string;
}


