#include <QString>
#include "app.h"
#include "document.h"
#include "documents.h"
#include "gui/formgridsearch.h"
#include "gui/mainwindow.h"

extern App* app;
extern QString programNameFieldName;

Documents::Documents(int opNumber, QObject *parent): Dictionary(parent) {
    lViewable = true;
    tableName = "документы";
    operNumber = opNumber;
    tagName = QString("СписокДокументов%1").arg(operNumber);
    formTitle = QString("%1 - %2").arg(app->getToperProperty(operNumber, programNameFieldName).toString()).arg(QObject::tr("Список документов"));
}

Documents::~Documents() {
}

void Documents::show() {
    query();
    Dictionary::show();
}

bool Documents::add() {
    QDate date = QDate().currentDate();
    if (!(date >= app->getBeginDate() && date <= app->getEndDate())) {
        if (date < app->getBeginDate())
            date = app->getBeginDate();
        else if (date > app->getEndDate())
            date = app->getEndDate();
    }
    return app->getDBFactory()->addDoc(operNumber, date);
}

bool Documents::remove() {
    if (lDeleteable) {
        if (Essence::remove()) {
            app->getDBFactory()->removeDoc(getValue("код").toInt());
            return true;
        }
    }
    else
        showError(QString(QObject::tr("Запрещено удалять документы пользователю %2")).arg(app->getLogin()));
    return false;
}

void Documents::view() {
    currentRow = getForm()->getCurrentRowIndex();
    currentDocument->setDocId(getValue("код").toInt());
    currentDocument->show();
}

void Documents::query(QString filter) {
    Q_UNUSED(filter)
    Essence::query(QString("дата BETWEEN cast('%1' as date) AND cast('%2' as date) AND авто=0 AND опер='%3' ORDER BY дата, код").arg(app->getBeginDate().toString("dd.MM.yyyy")).arg(app->getEndDate().toString("dd.MM.yyyy")).arg(operNumber));
}

bool Documents::doOpen() {
    lInsertable = app->getToperProperty(operNumber, "insertable").toBool();
    lDeleteable = app->getToperProperty(operNumber, "deleteable").toBool();
    lUpdateable = app->getToperProperty(operNumber, "updateable").toBool();
    if (Essence::doOpen()) {     // Откроем этот справочник

        // Установим форму для отображения справочника

        // Установим порядок сортировки и стратегию сохранения данных на сервере
        tableModel->setSort(tableModel->fieldIndex(programNameFieldName), Qt::AscendingOrder);

        currentDocument = new Document(operNumber, this);
        if (currentDocument->open())
            initForm();
            return true;
    }
    showError(QString(QObject::tr("Запрещено просматривать операцию <%1> пользователю %2")).arg(formTitle).arg(app->getLogin()));
    return false;
}

void Documents::doClose() {
    currentDocument->close();
    delete currentDocument;
    Dictionary::doClose();
}

void Documents::setForm() {
    form = new FormGrid();
    form->open(parentForm, this);
}
