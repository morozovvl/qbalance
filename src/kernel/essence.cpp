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

#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QMessageBox>
#include <QMenu>
#include <QUiLoader>
#include "essence.h"
#include "../kernel/app.h"
#include "../gui/form.h"
#include "../gui/formgridsearch.h"
#include "../gui/mainwindow.h"
#include "../report/reportengine.h"
#include "../report/ooreportengine.h"
#include "../report/openrptreportengine.h"
#include "../engine/reportscriptengine.h"
#include "../engine/reportcontext.h"


Essence::Essence(QString name, QObject *parent): Table(name, parent)
{
    form = 0;
    parentForm = 0;
    scriptEngine = 0;
    parentForm  = TApplication::exemplar()->getMainWindow()->centralWidget();
    formTitle   = "";
    lInsertable = false;
    lDeleteable = false;
    lViewable   = false;
    lUpdateable = false;
    lPrintable  = false;
    idFieldName = db->getObjectName("код");
    nameFieldName = db->getObjectName("имя");
    scriptEngine = 0;
    connect(this, SIGNAL(showError(QString)), TApplication::exemplar(), SLOT(showError(QString)));
}


Essence::~Essence() {
    disconnect(this, 0, 0, 0);
}


Dialog* Essence::getFormWidget() {
    if (!opened)
    {
        open();
    }
    return form->getForm();
}


bool Essence::calculate(const QModelIndex &index)
{
    bool lResult = true;
    if (scriptEngine != 0)
    {
        currentFieldName = tableModel->getFieldName(index.column());
        lResult = scriptEngine->evaluate();
    }
    if (lResult)
        lResult = tableModel->submit(index);
    else
        tableModel->revertAll();
    return lResult;
}


QVariant Essence::getValue(QString name, int row)
{
    QVariant result;
    if (row >= 0)
    {
        result =  tableModel->record(row).value(name);
    }
    else
    {
        int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
        result = tableModel->record(r).value(name);
    }
    // ВНИМАНИЕ!!!
    // Не могу понять, почему тип поля "p1__кол" возвращается как QString. Должен быть double
    // Типы полей "p2__кол" и "p3__кол" возвращаются нормальные - double
    // пока не разобрался, почему это так - временно делаю следующее преобразование
    if (name == "p1__кол")
        result.convert(QVariant::Double);

    return result;
}


void Essence::setValue(QString name, QVariant value, int row)
{
    int r;
    if (row >= 0)
        r = row;
    else
    {
        r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
    }
    int col = tableModel->record().indexOf(name);
    tableModel->setData(tableModel->index(r, col), value);
    tableModel->submit(tableModel->index(r, col));
}


qulonglong Essence::getId(int row)
{
    if (row >= 0)
        return getValue(idFieldName, row).toULongLong();
    int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
    return getValue(idFieldName, r).toULongLong();
}


QString Essence::getName(int row)
{
    if (row >= 0)
        return getValue(nameFieldName, row).toString();
    int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
    return getValue(nameFieldName, r).toString();
}


void Essence::setId(qulonglong id)
{
    query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(db->getObjectName("код")).arg(id));
    for (int i = 0; i < tableModel->rowCount(); i++) {
        form->getGridTable()->selectRow(i);
        if (getId() == id) {
            form->setCurrentIndex(form->getCurrentIndex().sibling(i, 0));
            return;
        }
    }
    if (tableModel->rowCount() > 0)
    {
        QModelIndex index = form->getCurrentIndex();
        form->setCurrentIndex(index.sibling(0, 0));
    }
}


QString Essence::getPhotoPath()
{
    QString path = db->getPhotoPath(tableName);
    if (!path.isEmpty()) {
        if (path.left(1) == "~") {
            path.remove(0, 1);
            path = TApplication::exemplar()->applicationDirPath() + path;
        }
    }
    return path;
}


bool Essence::add()
{
    return false;
}


bool Essence::remove()
{
    if (TApplication::exemplar()->getGUIFactory()->showYesNo("Удалить запись? Вы уверены?") == QMessageBox::Yes)
    {
        return true;
    }
    return false;
}


int Essence::exec()
{
    if (!opened)
    {
        open();
    }
    if (opened && form != 0) {
        return form->exec();
    }
    return 0;
}

void Essence::show()
{
    if (!opened) open();
    if (opened && form != 0) {
        form->show();
    }
}


void Essence::hide()
{
    if (opened && form != 0) {
        form->hide();
    }
}


void Essence::view()
{
    if (form != 0)
        form->getForm()->setFocus(Qt::OtherFocusReason);
}


bool Essence::open()
{
    if (Table::open())
    {
        initForm();
        setScriptEngine();
        return true;
    }
    return false;
}


void Essence::close()
{
    if (form != 0)
    {
        form->closeFormEvent();
        form->writeSettings();
        form->close();
    }
    delete scriptEngine;
    delete form;
    Table::close();
}


void Essence::setForm()
{
    form = new FormGrid();
    form->open(parentForm, this);
    form->setButtonsSignals();
}


void Essence::setScriptEngine()
{
    scriptEngine = new ScriptEngine(this);
}


ScriptEngine* Essence::getScriptEngine()
{
    return scriptEngine;
}


void Essence::initForm() {
    setForm();
    form->setIcons();
    form->readSettings();
    setFormTitle(formTitle);
}


void Essence::setFormTitle(QString title) {
    formTitle = title;
    form->getForm()->setWindowTitle(title);
}


QString Essence::getFormTitle()
{
    return form->getForm()->windowTitle();
}


bool Essence::isFormSelected() {
    return form->selected();
}


void Essence::cmdOk() {
}


void Essence::cmdCancel() {
}


void Essence::preparePrintValues(ReportScriptEngine* reportEngine)
{   // Зарядим константы в контекст печати
    QString constDictionaryName = db->getObjectName("константы");
    QString constNameField = db->getObjectName(constDictionaryName + ".имя");
    QString constValueField = db->getObjectName(constDictionaryName + ".значение");
    // Откроем справочник констант
    TApplication::exemplar()->getDictionaries()->addDictionary(db->getObjectName(constDictionaryName));
    if (TApplication::exemplar()->getDictionaries()->isMember(constDictionaryName))
    {
        Dictionary* dict = TApplication::exemplar()->getDictionaries()->getDictionary(constDictionaryName);
        dict->query();    // Прочитаем содержимое справочника констант
        QSqlTableModel* model = dict->getTableModel();
        for (int i = 0; i < model->rowCount(); i++)
        {
            QSqlRecord rec = model->record(i);
            reportEngine->getReportContext()->setValue(QString("%1.%2").arg(constDictionaryName).arg(rec.value(constNameField).toString()), rec.value(constValueField));
        }
    }
}


void Essence::print(QString file)
{
    // Подготовим данные для печати
    QMap<QString, QVariant> printValues;
    ReportScriptEngine scriptEngine(&printValues);
    preparePrintValues(&scriptEngine);
    QString ext = TApplication::exemplar()->getReportTemplateExt();
    if (scriptEngine.open(file + "." + ext + ".qs") && scriptEngine.evaluate())
    {
        switch (TApplication::exemplar()->getReportTemplateType())
        {
            case OOreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
                    OOReportEngine report(&printValues, file, ext);
                    report.open();
                }
                break;
            case OpenRPTreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
//                    OpenRPTreportEngine report(&printValues, file, ext);
//                    report.open();
                }
                break;
        }
    }
}

