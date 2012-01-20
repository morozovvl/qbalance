#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QUiLoader>
#include "essence.h"
#include "../kernel/app.h"
#include "../gui/form.h"
#include "../gui/formgridsearch.h"
#include "../gui/mainwindow.h"
#include "../report/reportengine.h"
#include "../report/ooreportengine.h"
#include "../engine/reportscriptengine.h"
#include "../engine/reportcontext.h"

Essence::Essence(QString name, QObject *parent): Table(name, parent),
form(NULL),
parentForm(NULL),
scriptEngine(NULL)
{
    parentForm  = TApplication::exemplar()->getMainWindow()->centralWidget();
    formTitle   = "";
    lInsertable = false;
    lDeleteable = false;
    lViewable   = false;
    lUpdateable = false;
    lPrintable  = false;
    idFieldName = TApplication::idFieldName();
    nameFieldName = TApplication::nameFieldName();
    scriptEngine = 0;
    connect(this, SIGNAL(showError(QString)), TApplication::exemplar(), SLOT(showError(QString)));
}

Essence::~Essence() {
    disconnect(this, 0, 0, 0);
}

QDialog* Essence::getFormWidget() {
    if (!opened)
    {
        open();
    }
    return form->getForm();
}

bool Essence::setData(const QModelIndex & index, const QVariant & value, int role/* = Qt::EditRole*/)
{
    return tableModel->setData(index, value, role);
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
    if (row >= 0)
        return tableModel->record(row).value(name);
    return tableModel->record(form->getCurrentIndex().row()).value(name);
}


void Essence::setValue(QString name, QVariant value, int row)
{
    QModelIndex index = form->getCurrentIndex();
    int col = tableModel->record().indexOf(name);
    if (row >= 0)
    {
        index = index.sibling(row, col);
    }
    else
    {
        index = index.sibling(index.row(), col);
    }
    tableModel->setData(index, value);
}


qulonglong Essence::getId(int row)
{
    if (row >= 0)
        return getValue(idFieldName, row).toULongLong();
    return getValue(idFieldName, form->getCurrentIndex().row()).toULongLong();
}


QString Essence::getName(int row)
{
    if (row >= 0)
        return getValue(nameFieldName, row).toString();
    return getValue(nameFieldName, form->getCurrentIndex().row()).toString();
}


void Essence::setId(qulonglong id)
{
    if (id > 0) {
        query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(TApplication::idFieldName()).arg(id));
        for (int i = 0; i < tableModel->rowCount(); i++) {
            form->getGridTable()->selectRow(i);
            if (getId() == id) {
                return;
            }
        }

        if (tableModel->rowCount() > 0)
        {
            QModelIndex index = form->getCurrentIndex();
            form->setCurrentIndex(index.sibling(0, 0));
        }
    }
}


QString Essence::getPhotoPath()
{
    QString path = TApplication::exemplar()->getDBFactory()->getPhotoPath(tableName);
    if (!path.isEmpty()) {
        if (path.left(1) == "~") {
            path.remove(0, 1);
            path = TApplication::exemplar()->applicationDirPath() + path;
        }
    }
    return path;
}


bool Essence::remove()
{
    return TApplication::exemplar()->getGUIFactory()->showYesNo("Удалить запись? Вы уверены?") == QMessageBox::Yes;
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
    scriptEngine = new ScriptEngine();
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
    form->initFormEvent();
}


void Essence::setFormTitle(QString title) {
    formTitle = title;
    form->getForm()->setWindowTitle(title);
}


bool Essence::isFormSelected() {
    return form->selected();
}


void Essence::cmdOk() {
}


void Essence::cmdCancel() {
}


void Essence::preparePrintValues(QMap<QString, QVariant>* printValues)
{   // Зарядим константы в контекст печати
    DBFactory* db = TApplication::exemplar()->getDBFactory();
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
            printValues->insert(QString("[%1.%2]").arg(constDictionaryName).arg(rec.value(constNameField).toString()), rec.value(constValueField));
        }
    }
}


void Essence::print(QString file)
{
    // Подготовим данные для печати
    QMap<QString, QVariant> printValues;
    preparePrintValues(&printValues);
    QString ext = TApplication::exemplar()->getReportTemplateExt();
    ReportScriptEngine scriptEngine(&printValues);
    if (scriptEngine.open(file + "." + ext))
    {
        switch (TApplication::exemplar()->getReportTemplateType())
        {
            case OOreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
                    OOReportEngine report(&printValues, file, ext);
                    report.open();
                }
                break;
        }
    }
}

