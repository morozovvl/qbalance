#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QUiLoader>
#include "essence.h"
#include "app.h"
#include "reporttemplate.h"
#include "reportengine.h"
#include "gui/form.h"
#include "gui/formgridsearch.h"
#include "gui/mainwindow.h"

extern App* app;
extern QString programErrorFileName;
extern QString programIdFieldName;

Essence::Essence(QString name, QObject *parent) : Table(name, parent) {
    form = 0;
    parentForm = app->getMainWindow()->centralWidget();
    formTitle = "";
    lInsertable = false;
    lDeleteable = false;
    lViewable = false;
    lUpdateable = false;
    lPrintable = false;
    idFieldName = programIdFieldName;
    connect(this, SIGNAL(showError(QString)), app, SLOT(showError(QString)));
}

Essence::~Essence() {
    disconnect(this, 0, 0, 0);
}

QDialog* Essence::getFormWidget() {
    if (!opened) open();
    return form->getForm();
}

void Essence::setScriptForTable(QString scr) {
    if (scr.size() > 0) {
        if (engine == 0) {
            engine = new ScriptEngine(this);
        }
        script = scr;
// Временно отключено, пока не сделаем скриптовый движок
//        scripts = engine->evaluate(script);
    }
}

bool Essence::calculate(const QModelIndex &index) {
    if (engine != 0) {
        setCalculateProperties(index);
        QScriptValue value = engine->globalObject().property("calcTable").call();
        if (value.isError()) {
            revertCalculateProperties(index);
            showError(value.toString());
            return false;
        }
        getCalculateProperties(index);
        if (!tableModel->submit(index)) {
            revertCalculateProperties(index);
            return false;
        }
        for (int i = 0; i < tableModel->record().count(); i++) {
            QModelIndex index = form->getCurrentIndex();
            index = index.sibling(form->getCurrentRowIndex(), i);
            tableModel->setData(index, tableModel->data(index));
        }
    }
    return true;
}

void Essence::getCalculateProperties(const QModelIndex &index) {
    if (engine != 0) {
        QVariant var;
        int col;
        QString fieldName;
        foreach (QString field, getFieldsList()) {
            QVariant var = engine->evaluate(QString("Table[\"%1\"]").arg(field), programErrorFileName).toVariant();
            col = tableModel->record().indexOf(field);
            if (col > -1)
                tableModel->setData(index.sibling(index.row(), col), var);
        }
    }
}

void Essence::setCalculateProperties(const QModelIndex &index) {
    if (engine != 0) {
        engine->globalObject().setProperty("Table", engine->newArray());
        foreach (QString field, getFieldsList()) {
            QVariant var(tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(field))));
            engine->globalObject().setProperty("__temp__", engine->newVariant(var));
            engine->evaluate(QString("Table[\"%1\"] = __temp__").arg(field), programErrorFileName);
        }
        engine->globalObject().setProperty("__Column_Name__", engine->newVariant(tableModel->record().fieldName(index.column())));
    }
}

void Essence::setOldCalculateProperties(const QModelIndex &index) {
    if (engine != 0) {
        QVariant var;
        engine->globalObject().setProperty("OldTable", engine->newArray());
        foreach (QString field, getFieldsList()) {
            var = tableModel->data(index.sibling(index.row(), tableModel->record().indexOf(field)));
            engine->globalObject().setProperty("__temp__", engine->newVariant(var));
            engine->evaluate(QString("OldTable[\"%1\"] = __temp__").arg(field), programErrorFileName);
        }
    }
}

void Essence::revertCalculateProperties(const QModelIndex &index) {
    if (engine != 0) {
        foreach (QString field, getFieldsList()) {
            QVariant var = engine->evaluate(QString("OldTable[\"%1\"]").arg(field), programErrorFileName).toVariant();
            tableModel->setData(index.sibling(index.row(), tableModel->record().indexOf(field)), var);
        }
    }
}

QVariant Essence::getValue(QString name, int row) {
    if (row >= 0)
        return tableModel->record(row).value(name);
    return tableModel->record(form->getCurrentRowIndex()).value(name);
}

bool Essence::setValue(QString name, QVariant value, int row) {
    int col = tableModel->record().indexOf(name);
    QModelIndex index = form->getCurrentIndex();
    if (row >= 0)
        index = index.sibling(row, col);
    else
        index = index.sibling(form->getCurrentRowIndex(), col);
    return tableModel->setData(index, value);
}

qulonglong Essence::getId(int row) {
    if (row > 0)
        return getValue(idFieldName, row).toULongLong();
    return getValue(idFieldName, form->getCurrentRowIndex()).toULongLong();
}

void Essence::setId(qulonglong id) {
    if (id > 0) {
        QModelIndex index = form->getCurrentIndex();
        query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(programIdFieldName).arg(id));
        for (int i = 0; i < tableModel->rowCount(); i++) {
            form->getGridTable()->selectRow(i);
            if (getId() == id) {
                return;
            }
        }

        if (tableModel->rowCount() > 0)
            form->setCurrentIndex(index.sibling(0, 0));
    }
}

QSqlQuery Essence::getColumnsHeaders() {
    return app->getDBFactory()->getColumnsHeaders(tableName);
}

QString Essence::getPhotoPath() {
    QString path = app->getDBFactory()->getPhotoPath(tableName);
    if (path.size() > 0) {
        if (path.left(1) == "~") {
            path.remove(0, 1);
            path = app->getHomePath() + path;
        }
    }
    return path;
}


bool Essence::remove() {
    if (app->getGUIFactory()->showYesNo("Удалить запись? Вы уверены?") == QMessageBox::Yes)
        return true;
    return false;
}

int Essence::exec() {
    if (!opened) open();
    if (opened && form != 0) {
        return form->exec();
    }
    return 0;
}

void Essence::show() {
    if (!opened) open();
    if (opened && form != 0) {
        form->show();
    }
}

void Essence::hide() {
    if (opened && form != 0) {
        form->hide();
    }
}

void Essence::view() {
    if (form != 0)
        form->getForm()->setFocus(Qt::OtherFocusReason);
}

bool Essence::doOpen() {
    return Table::doOpen();
}

void Essence::doClose() {
//    if (engine != 0)
//        delete engine;
    form->closeFormEvent();
    form->writeSettings();
//    form->setParent(0);
    form->close();
    delete form;
    Table::doClose();
}

void Essence::setForm() {
    form = new FormGrid();
    form->open(parentForm, this);
}

void Essence::initForm() {
    setForm();
    form->readSettings();
    setFormTitle(formTitle);
    form->initFormEvent();
}

void Essence::setFormTitle(QString title) {
    formTitle = title;
    form->getForm()->setWindowTitle(title);
}

bool Essence::isFormSelected() {
    return form->selected();
}

void Essence::print(QString file) {
    ReportEngine report(this, file);
    report.open();
}

void Essence::cmdOk() {
}

void Essence::cmdCancel() {
}
