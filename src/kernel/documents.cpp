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

#include <QString>
#include "documents.h"
#include "document.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"


Documents::Documents(int opNumber, QObject *parent): Dictionary(parent) {
    lViewable  = true;
    tableName  = "документы";
    operNumber = opNumber;
    tagName    = QString("СписокДокументов%1").arg(operNumber);
    QSqlRecord operProperties = db->getTopersProperties(operNumber);
    formTitle  = QString("%1 - %2").arg(operProperties.value(db->getObjectName("имя")).toString()).arg(QObject::trUtf8("Список документов"));
    lInsertable = operProperties.value("insertable").toBool();
    lDeleteable = operProperties.value("deleteable").toBool();
    lUpdateable = operProperties.value("updateable").toBool();
}


Documents::~Documents() {
}


void Documents::show() {
    query();
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
        form->getGridTable()->selectRow(tableModel->rowCount() - 1);    // Установить фокус таблицы на последнюю, только что добавленную, запись
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
        showError(QString(QObject::trUtf8("Запрещено удалять документы пользователю %2")).arg(TApplication::exemplar()->getLogin()));
    return false;
}


void Documents::view() {
    currentDocument->setDocId(getValue("код").toInt());
    currentDocument->show();
}


void Documents::query(QString filter) {
    Q_UNUSED(filter)
    Essence::query(QString("дата BETWEEN cast('%1' as date) AND cast('%2' as date) AND авто=0 AND опер='%3' ORDER BY дата, код").arg(
        TApplication::exemplar()->getBeginDate().toString("dd.MM.yyyy"),
        TApplication::exemplar()->getEndDate().toString("dd.MM.yyyy"),
        QString::number(operNumber)));
}


bool Documents::open() {
    if (Essence::open()) {     // Откроем этот справочник

        // Установим форму для отображения справочника

        // Установим порядок сортировки и стратегию сохранения данных на сервере
        tableModel->setSort(tableModel->fieldIndex(db->getObjectName("имя")), Qt::AscendingOrder);

        currentDocument = new Document(operNumber, this);
        if (currentDocument->open())
            return true;
    }
    showError(QString(QObject::trUtf8("Запрещено просматривать операцию <%1> пользователю %2")).arg(
                  formTitle,
                  TApplication::exemplar()->getLogin()));
    return false;
}


void Documents::close() {
    currentDocument->close();
    delete currentDocument;
    Dictionary::close();
}


void Documents::setForm() {
    form = new FormGrid();
    form->open(parentForm, this);
    if (form->isDefaultForm())
    {
        QPushButton* button;
        button = form->getButtonCancel();
        if (button != NULL)
            button->hide();
        button = form->getButtonOk();
        if (button != NULL)
            button->setToolTip(trUtf8("Закрыть список документов"));
        button = form->getButtonAdd();
        if (button != NULL)
            button->setToolTip(trUtf8("Создать новый документ"));
        button = form->getButtonDelete();
        if (button != NULL)
            button->setToolTip(trUtf8("Удалить документ"));
        button = form->getButtonView();
        if (button != NULL)
            button->setToolTip(trUtf8("Просмотреть документ"));
        button = form->getButtonRequery();
        if (button != NULL)
            button->setToolTip(trUtf8("Обновить список документов (загрузить повторно с сервера)"));
    }
}
