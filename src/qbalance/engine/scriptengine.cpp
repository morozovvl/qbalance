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

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtScript/QScriptValueIterator>
#include <QtGui/QKeyEvent>
#include <QtGui/QPushButton>
#include <QtGui/QKeyEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QLineEdit>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include "scriptengine.h"
#include "../kernel/app.h"
#include "../kernel/dictionary.h"
#include "../kernel/document.h"
#include "../kernel/documents.h"
#include "../storage/dbfactory.h"
#include "../gui/mainwindow.h"
#include "../gui/form.h"
#include "../gui/formgrid.h"
#include "../gui/formgridsearch.h"
#include "../gui/dialog.h"
#include "../gui/picture.h"
#include "../driverfr/driverfr.h"
#include "../bankterminal/bankterminal.h"
#include "../openoffice/ooxmlengine.h"

#include "eventloop.h"
#include "reportcontextfunctions.h"
#include "reportcontext.h"


Q_DECLARE_METATYPE(Dialog*)
Q_DECLARE_METATYPE(QLineEdit*)

QHash<QString, QString> ScriptEngine::scripts;
bool ScriptEngine::isSA = false;


// Функции, преобразующие вид функций в скриптах table.<функция> к виду <функция> для упрощения написания скриптов

bool isNumeric(ScriptEngine* engine, QString field = "")
{
    QString fieldName;
    if (engine->getParent() != 0)
    {
        if (field.size() == 0)
            fieldName = (engine->getParent())->getCurrentFieldName();
        else
            fieldName = field;
        if (QString((engine->getParent())->getValue(fieldName).typeName()).compare("double", Qt::CaseInsensitive) == 0)
            return true;
    }
    return false;
}


QScriptValue getCurrentFieldName(QScriptContext *, QScriptEngine* engine)
{
    if (engine->evaluate("table").isValid())
    {
        QScriptValue value = engine->evaluate(QString("table.getCurrentFieldName()"));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getRowCount(QScriptContext *, QScriptEngine* engine)
{
    if (engine->evaluate("table").isValid())
    {
        QScriptValue value = engine->evaluate(QString("table.getRowCount()"));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getValue(QScriptContext* context, QScriptEngine* engine)
{
    if (context->argument(0).isString() && engine->evaluate("table").isValid())
    {
        QString fieldName = context->argument(0).toString();
        int row = (context->argument(1).isNumber() ? context->argument(1).toInteger() : -1);
        QScriptValue value = engine->evaluate(QString("table.getValue('%1', %2)").arg(fieldName).arg(row));
        if (value.toVariant().type() == QVariant::Double)
            value = engine->evaluate(QString("parseFloat(%1)").arg(value.toVariant().toFloat()));
        else
            value = engine->evaluate(QString("table.getValue('%1', %2)").arg(fieldName).arg(row));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getId(QScriptContext* context, QScriptEngine* engine)
{
    if (engine->evaluate("table").isValid())
    {
        QScriptValue value;
        if (context->argumentCount() > 0)
        {
            int row = (context->argument(0).isNumber() ? context->argument(1).toInteger() : -1);
            value = engine->evaluate(QString("table.getId(%1)").arg(row));
        }
        else
            value = engine->evaluate(QString("table.getId()"));

        if (value.isValid())
        {
            return value;
        }
    }
    return QScriptValue();
}


QScriptValue setValue(QScriptContext* context, QScriptEngine* engine)
{
    QScriptValue fieldName = context->argument(0);
    int row = (context->argument(2).isNumber() ? context->argument(2).toInteger() : -1);
    if (fieldName.isString() && engine->evaluate("table").isValid())
    {
        QScriptValue value = engine->evaluate(QString("table.setValue('%1', %2, %3)").arg(fieldName.toString())
                                                                                .arg(context->argument(1).toString())
                                                                                .arg(row));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getOldValue(QScriptContext* context, QScriptEngine* engine)
{
    QScriptValue fieldName = context->argument(0);
    if (engine->evaluate("table").isValid())
    {
        QScriptValue value;
        QString command;
        if (isNumeric((ScriptEngine*)engine))
            command = QString("parseFloat(table.getOldValue(%1))").arg(fieldName.toString() != "undefined" ? "'" + fieldName.toString() + "'" : "");
        else
            command = QString("table.getOldValue('%1')").arg(fieldName.toString());

        value = engine->evaluate(command);
        if (value.isValid())
        {
            return value;
        }
    }
    return QScriptValue();
}


QScriptValue getDictionary(QScriptContext* context, QScriptEngine* engine)
{
    QScriptValue dictName = context->argument(0);
    if (dictName.isString())
    {
        if (((ScriptEngine*)engine)->getDocument() != 0)
        {
            if (engine->evaluate("document").isValid())
            {
                QScriptValue value = engine->evaluate(QString("document.getDictionary('%1')").arg(dictName.toString()));
                if (value.isValid())
                    return value;
            }
        }
        else
        {
            if (engine->evaluate("app").isValid())
            {
                QScriptValue value = engine->evaluate(QString("app.getDictionaries().getDictionary('%1')").arg(dictName.toString()));
                if (value.isValid())
                    return value;
            }
        }
    }
    return QScriptValue();
}


QScriptValue quotes(QScriptContext* context, QScriptEngine*)
{   // Просто заворачивает аргумент в кавычки
    return QScriptValue('"' + context->argument(0).toString() + '"');
}


QScriptValue evaluateScript(QScriptContext* context, QScriptEngine* engine)
{
    QScriptValue result(false);
    if (context->argument(0).isString())
    {
        QString scriptFile = context->argument(0).toString();
        QString script = ScriptEngine::loadScript(scriptFile);
        if (script.size() > 0)
        {
            TApplication::exemplar()->appendScriptStack((ScriptEngine*)engine);
            QScriptContext *pc = context->parentContext();
            context->setActivationObject(pc->activationObject());
            context->setThisObject(pc->thisObject());
            result = engine->evaluate(script);
            if (engine->hasUncaughtException())
            {
                // Если в скриптах произошла ошибка
                QString errorMessage = QString(QObject::trUtf8("Ошибка в строке %1 скрипта %2: [%3]")).arg(engine->uncaughtExceptionLineNumber()).arg(scriptFile).arg(engine->uncaughtException().toString());
                TApplication::exemplar()->showError(errorMessage);
            }
            TApplication::exemplar()->removeLastScriptStack();
        }
    }
    return result;
}


QScriptValue debug(QScriptContext* context, QScriptEngine*)
{
    QScriptValue result(true);
    if (context->argument(0).isString())
    {
        QString message = context->argument(0).toString();
        TApplication::exemplar()->debug(3, message);
    }
    return result;
}


// класс DriverFR
Q_DECLARE_METATYPE(DriverFR*)

/*
QScriptValue DriverFRConstructor(QScriptContext *, QScriptEngine *engine) {
    DriverFR *object = new DriverFR(TApplication::exemplar());
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
*/

QScriptValue DriverFRToScriptValue(QScriptEngine *engine, DriverFR* const &in) {
    return engine->newQObject(in);
}

void DriverFRFromScriptValue(const QScriptValue &object, DriverFR* &out) {
    out = qobject_cast<DriverFR*>(object.toQObject());
}


// класс BankTerminal
Q_DECLARE_METATYPE(BankTerminal*)

QScriptValue BankTerminalToScriptValue(QScriptEngine *engine, BankTerminal* const &in) {
    return engine->newQObject(in);
}

void BankTerminalFromScriptValue(const QScriptValue &object, BankTerminal* &out) {
    out = (BankTerminal*)(object.toQObject());
}

// класс EventLoop
Q_DECLARE_METATYPE(EventLoop*)

QScriptValue EventLoopConstructor(QScriptContext *, QScriptEngine *engine) {
     EventLoop *object = new EventLoop();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue EventLoopToScriptValue(QScriptEngine *engine, EventLoop* const &in) {
    return engine->newQObject(in);
}

void EventLoopFromScriptValue(const QScriptValue &object, EventLoop* &out) {
    out = qobject_cast<EventLoop*>(object.toQObject());
}


// класс Picture
Q_DECLARE_METATYPE(Picture*)

QScriptValue PictureConstructor(QScriptContext *, QScriptEngine *engine) {
     Picture* object = new Picture();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue PictureToScriptValue(QScriptEngine *engine, Picture* const &in) {
    return engine->newQObject(in);
}

void PictureFromScriptValue(const QScriptValue &object, Picture* &out) {
    out = qobject_cast<Picture*>(object.toQObject());
}


// класс Dictionary
Q_DECLARE_METATYPE(Dictionary*)

QScriptValue DictionaryConstructor(QScriptContext *context, QScriptEngine *engine) {
    QString tableName;
    if (context->argumentCount() > 0)
        tableName = context->argument(0).toString();
    Dictionary* object = new Dictionary(tableName);
    return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue DictionaryToScriptValue(QScriptEngine *engine, Dictionary* const &in) {
    return engine->newQObject(in);
}

void DictionaryFromScriptValue(const QScriptValue &object, Dictionary* &out) {
    out = qobject_cast<Dictionary*>(object.toQObject());
}

// класс Saldo
Q_DECLARE_METATYPE(Saldo*)

QScriptValue SaldoConstructor(QScriptContext *context, QScriptEngine *engine) {
     Saldo* object = new Saldo(context->argument(0).toString(), context->argument(1).toString());
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue SaldoToScriptValue(QScriptEngine *engine, Saldo* const &in) {
    return engine->newQObject(in);
}

void SaldoFromScriptValue(const QScriptValue &object, Saldo* &out) {
    out = qobject_cast<Saldo*>(object.toQObject());
}

// класс Dictionaries
Q_DECLARE_METATYPE(Dictionaries*)

QScriptValue DictionariesConstructor(QScriptContext*, QScriptEngine *engine) {
     Dictionaries* object = new Dictionaries();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue DictionariesToScriptValue(QScriptEngine *engine, Dictionaries* const &in) {
    return engine->newQObject(in);
}

void DictionariesFromScriptValue(const QScriptValue &object, Dictionaries* &out) {
    out = qobject_cast<Dictionaries*>(object.toQObject());
}


// класс Documents
Q_DECLARE_METATYPE(Documents*)

QScriptValue DocumentsConstructor(QScriptContext *context, QScriptEngine *engine) {
     Documents *object = new Documents(context->argument(0).toInteger());
     return engine->newQObject(object, QScriptEngine::QtOwnership);
}


QScriptValue DocumentsToScriptValue(QScriptEngine *engine, Documents* const &in) {
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}


void DocumentsFromScriptValue(const QScriptValue &object, Documents* &out) {
    out = qobject_cast<Documents*>(object.toQObject());
}


// класс Document
Q_DECLARE_METATYPE(Document*)

QScriptValue DocumentConstructor(QScriptContext *context, QScriptEngine *engine) {
    Documents* docs;
    DocumentsFromScriptValue(context->argument(1), docs);
    Document *object = new Document(context->argument(0).toInteger(), docs);
    return engine->newQObject(object, QScriptEngine::QtOwnership);
}

QScriptValue DocumentToScriptValue(QScriptEngine *engine, Document* const &in) {
    return engine->newQObject(in, QScriptEngine::QtOwnership);
}

void DocumentFromScriptValue(const QScriptValue &object, Document* &out) {
    out = qobject_cast<Document*>(object.toQObject());
}


// класс Dialog
QScriptValue qDialogConstructor(QScriptContext *, QScriptEngine *engine) {
     Dialog *object = new Dialog();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue qDialogToScriptValue(QScriptEngine *engine, Dialog* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void qDialogFromScriptValue(const QScriptValue &object, Dialog* &out) {
    out = qobject_cast<Dialog*>(object.toQObject());
}

// класс QLineEdit
QScriptValue qLineEditToScriptValue(QScriptEngine *engine, QLineEdit* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void qLineEditFromScriptValue(const QScriptValue &object, QLineEdit* &out) {
    out = qobject_cast<QLineEdit*>(object.toQObject());
}

// класс Form
Q_DECLARE_METATYPE(Form*)

QScriptValue FormConstructor(QScriptContext *context, QScriptEngine *engine) {
     Form *object = new Form();
     object->open(TApplication::exemplar()->getMainWindow()->centralWidget(), 0, context->argument(0).toString());
     object->setButtonsSignals();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue FormToScriptValue(QScriptEngine *engine, Form* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void FormFromScriptValue(const QScriptValue &object, Form* &out) {
    out = qobject_cast<Form*>(object.toQObject());
}


// класс FormGrid
Q_DECLARE_METATYPE(FormGrid*)

QScriptValue FormGridConstructor(QScriptContext *context, QScriptEngine *engine) {
     FormGrid *object = new FormGrid();
     object->open(TApplication::exemplar()->getMainWindow()->centralWidget(), 0, context->argument(0).toString());
     object->setButtonsSignals();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue FormGridToScriptValue(QScriptEngine *engine, FormGrid* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void FormGridFromScriptValue(const QScriptValue &object, FormGrid* &out) {
    out = qobject_cast<FormGrid*>(object.toQObject());
}


// класс FormGridSearch
Q_DECLARE_METATYPE(FormGridSearch*)

QScriptValue FormGridSearchConstructor(QScriptContext *context, QScriptEngine *engine) {
     FormGridSearch *object = new FormGridSearch();
     object->open(TApplication::exemplar()->getMainWindow()->centralWidget(), 0, context->argument(0).toString());
     object->setButtonsSignals();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue FormGridSearchToScriptValue(QScriptEngine *engine, FormGridSearch* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void FormGridSearchFromScriptValue(const QScriptValue &object, FormGridSearch* &out) {
    out = qobject_cast<FormGridSearch*>(object.toQObject());
}


// класс TableView
Q_DECLARE_METATYPE(TableView*)


QScriptValue TableViewToScriptValue(QScriptEngine *engine, TableView* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void TableViewFromScriptValue(const QScriptValue &object, TableView* &out) {
    out = qobject_cast<TableView*>(object.toQObject());
}


// класс QPushButton
Q_DECLARE_METATYPE(QPushButton*)

QScriptValue QPushButtonConstructor(QScriptContext *, QScriptEngine *engine) {
     QPushButton* object = new QPushButton();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue QPushButtonToScriptValue(QScriptEngine *engine, QPushButton* const &in) {
    return engine->newQObject(in);
}

void QPushButtonFromScriptValue(const QScriptValue &object, QPushButton* &out) {
    out = qobject_cast<QPushButton*>(object.toQObject());
}


// класс QFileDialog
Q_DECLARE_METATYPE(QFileDialog*)

QScriptValue QFileDialogConstructor(QScriptContext *context, QScriptEngine *engine) {
    QFileDialog* object;
    if (context->argumentCount() > 0)
    {
        if (context->argument(0).isString())
        {
            object = new QFileDialog(0,
                                     context->argument(0).toString(),
                                     context->argument(1).toString(),
                                     context->argument(2).toString());
        }
        else
        {
            object = new QFileDialog(((FormGrid*)context->argument(0).toQObject())->getFormWidget(),
                                     Qt::SubWindow);

        }
    }
    else
    {
        object = new QFileDialog(TApplication::exemplar()->getMainWindow()->centralWidget(), Qt::SubWindow);
    }
    return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}


QScriptValue QFileDialogToScriptValue(QScriptEngine *engine, QFileDialog* const &in) {
    return engine->newQObject(in);
}

void QFileDialogFromScriptValue(const QScriptValue &object, QFileDialog* &out) {
    out = qobject_cast<QFileDialog*>(object.toQObject());
}


// класс OOXMLEngine
Q_DECLARE_METATYPE(OOXMLEngine*)

QScriptValue OOXMLEngineConstructor(QScriptContext *, QScriptEngine *engine) {
     OOXMLEngine *object = new OOXMLEngine();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue OOXMLEngineToScriptValue(QScriptEngine *engine, OOXMLEngine* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void OOXMLEngineFromScriptValue(const QScriptValue &object, OOXMLEngine* &out) {
    out = qobject_cast<OOXMLEngine*>(object.toQObject());
}


// класс MyProgressDialog
Q_DECLARE_METATYPE(MyProgressDialog*)

QScriptValue MyProgressDialogConstructor(QScriptContext *, QScriptEngine *engine) {
     MyProgressDialog *object = new MyProgressDialog();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue MyProgressDialogToScriptValue(QScriptEngine *engine, MyProgressDialog* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void MyProgressDialogFromScriptValue(const QScriptValue &object, MyProgressDialog* &out) {
    out = qobject_cast<MyProgressDialog*>(object.toQObject());
}



//================================================================================================
// Реализация класса

ScriptEngine::ScriptEngine(Essence *par) : QScriptEngine()
{
    parent = par;
    sqlFieldClass = new SqlFieldClass(this);
    sqlRecordClass = new SqlRecordClass(this, sqlFieldClass);
    sqlQueryClass = new SqlQueryClass(this, sqlRecordClass);
    errorMessage = "";
    app = TApplication::exemplar();
    document = 0;
    documents = 0;
    scriptFileName = "";
    if (parent != 0 && parent->getDictionaries() != 0)
    {
        Dictionaries* dicts = parent->getDictionaries();
        document = dicts->getDocument();
        if (document != 0)
            documents = document->getParent();
    }
    isSA = app->isSA();
    script = "";
}


ScriptEngine::~ScriptEngine()
{
    delete sqlQueryClass;
    delete sqlRecordClass;
    delete sqlFieldClass;
}


bool ScriptEngine::open(QString scriptFile)
{
    loadScriptObjects();
    if (scriptFile.size() > 0)
    {
        script = loadScript(scriptFile);
        scriptFileName = scriptFile;
    }
    return true;
}


void ScriptEngine::close()
{
    script = "";
}


void ScriptEngine::loadScriptObjects()
{
    installTranslatorFunctions(QScriptValue());

    // Объявим классы для работы с БД
    globalObject().setProperty(sqlRecordClass->name(), sqlRecordClass->constructor());
    globalObject().setProperty(sqlFieldClass->name(), sqlFieldClass->constructor());
    globalObject().setProperty(sqlQueryClass->name(), sqlQueryClass->constructor());

    // Объявим классы для работы с пользовательскими формами
    qScriptRegisterMetaType(this, DriverFRToScriptValue, DriverFRFromScriptValue);
//    globalObject().setProperty("DriverFR", newQMetaObject(&QObject::staticMetaObject, newFunction(DriverFRConstructor)));
    qScriptRegisterMetaType(this, BankTerminalToScriptValue, BankTerminalFromScriptValue);
    qScriptRegisterMetaType(this, EventLoopToScriptValue, EventLoopFromScriptValue);
    globalObject().setProperty("EventLoop", newQMetaObject(&QObject::staticMetaObject, newFunction(EventLoopConstructor)));
    qScriptRegisterMetaType(this, FormToScriptValue, FormFromScriptValue);
    globalObject().setProperty("Form", newQMetaObject(&QObject::staticMetaObject, newFunction(FormConstructor)));
    qScriptRegisterMetaType(this, FormGridToScriptValue, FormGridFromScriptValue);
    globalObject().setProperty("FormGrid", newQMetaObject(&QObject::staticMetaObject, newFunction(FormGridConstructor)));
    qScriptRegisterMetaType(this, FormGridSearchToScriptValue, FormGridSearchFromScriptValue);
    globalObject().setProperty("FormGridSearch", newQMetaObject(&QObject::staticMetaObject, newFunction(FormGridSearchConstructor)));
    qScriptRegisterMetaType(this, TableViewToScriptValue, TableViewFromScriptValue);
    qScriptRegisterMetaType(this, DictionaryToScriptValue, DictionaryFromScriptValue);
    globalObject().setProperty("Dictionary", newQMetaObject(&QObject::staticMetaObject, newFunction(DictionaryConstructor)));
    qScriptRegisterMetaType(this, PictureToScriptValue, PictureFromScriptValue);
    globalObject().setProperty("Picture", newQMetaObject(&QObject::staticMetaObject, newFunction(PictureConstructor)));
    qScriptRegisterMetaType(this, SaldoToScriptValue, SaldoFromScriptValue);
    globalObject().setProperty("Saldo", newQMetaObject(&QObject::staticMetaObject, newFunction(SaldoConstructor)));
    qScriptRegisterMetaType(this, DictionariesToScriptValue, DictionariesFromScriptValue);
    globalObject().setProperty("Dictionaries", newQMetaObject(&QObject::staticMetaObject, newFunction(DictionariesConstructor)));
    qScriptRegisterMetaType(this, DocumentsToScriptValue, DocumentsFromScriptValue);
    globalObject().setProperty("Documents", newQMetaObject(&QObject::staticMetaObject, newFunction(DocumentsConstructor)));
    qScriptRegisterMetaType(this, DocumentToScriptValue, DocumentFromScriptValue);
    globalObject().setProperty("Document", newQMetaObject(&QObject::staticMetaObject, newFunction(DocumentConstructor)));

    globalObject().setProperty("QPushButton", newQMetaObject(&QObject::staticMetaObject, newFunction(QPushButtonConstructor)));
    qScriptRegisterMetaType(this, QPushButtonToScriptValue, QPushButtonFromScriptValue);

    // Объявим класс Dialog
    qScriptRegisterMetaType(this, qDialogToScriptValue, qDialogFromScriptValue);
    globalObject().setProperty("Dialog", newQMetaObject(&QObject::staticMetaObject, newFunction(qDialogConstructor)));

    // Объявим класс QLineEdit
    qScriptRegisterMetaType(this, qLineEditToScriptValue, qLineEditFromScriptValue);

    // Объявим класс OOXMLEngine
    qScriptRegisterMetaType(this, OOXMLEngineToScriptValue, OOXMLEngineFromScriptValue);
    globalObject().setProperty("OOXMLEngine", newQMetaObject(&QObject::staticMetaObject, newFunction(OOXMLEngineConstructor)));

    // Объявим класс MyProgressDialog
    qScriptRegisterMetaType(this, MyProgressDialogToScriptValue, MyProgressDialogFromScriptValue);
    globalObject().setProperty("ProgressDialog", newQMetaObject(&QObject::staticMetaObject, newFunction(MyProgressDialogConstructor)));

    // Объявим глобальные переменные и объекты
    if (parent != 0)
    {
        globalObject().setProperty("form", newQObject(((Document*)getParent())->getForm()));
        globalObject().setProperty("table", newQObject(getParent()));
    }
    else
    {
        globalObject().setProperty("form", 0);
        globalObject().setProperty("table", 0);
    }
    globalObject().setProperty("isDocumentScript", false);   // скрипт выполняется в документе или в приложении
    globalObject().setProperty("scriptResult", true);   // результат работы скрипта
    globalObject().setProperty("errorMessage", errorMessage);   // текст с описанием ошибки работы скрипта
    globalObject().setProperty("db", newQObject(app->getDBFactory()));
    globalObject().setProperty("app", newQObject(app));
    globalObject().setProperty("getCurrentFieldName", newFunction(getCurrentFieldName));
    globalObject().setProperty("getRowCount", newFunction(getRowCount));
    globalObject().setProperty("getDictionary", newFunction(getDictionary));
    globalObject().setProperty("getId", newFunction(getId));
    globalObject().setProperty("getValue", newFunction(getValue));
    globalObject().setProperty("setValue", newFunction(setValue));
    globalObject().setProperty("getOldValue", newFunction(getOldValue));
    globalObject().setProperty("quotes", newFunction(quotes));
    globalObject().setProperty("document", newQObject(document));
    globalObject().setProperty("documents", newQObject(documents));
    globalObject().setProperty("evaluateScript", newFunction(evaluateScript));
    globalObject().setProperty("SumToString", newFunction(SumToString));
    globalObject().setProperty("debug", newFunction(debug));

    QStringList extensions;
    extensions << "qt.core"
               << "qt.gui"
               << "qt.xml"
               << "qt.svg"
               << "qt.network"
               << "qt.sql"
               << "qt.opengl"
               << "qt.webkit"
               << "qt.xmlpatterns"
               << "qt.uitools";
    QStringList failExtensions;
    QScriptValue ret;
    foreach (const QString &ext, extensions) {
        ret = importExtension(ext);
        if (ret.isError())
            failExtensions.append(ext);
    }
}


bool ScriptEngine::evaluate()
{
    bool result = true;
    scriptResult = globalObject().property("scriptResult").toBool();    // Вернем результаты работы скрипта
    if (script.size() > 0)
    {
        QScriptProgram program(script);
        result = QScriptEngine::evaluate(program).isValid();
        if (hasUncaughtException())
        {   // Если в скриптах произошла ошибка
            errorMessage = QString(QObject::trUtf8("Ошибка в строке %1 скрипта %2: [%3]")).arg(uncaughtExceptionLineNumber()).arg(scriptFileName).arg(uncaughtException().toString());
            app->showError(errorMessage);
            // Если произошла ошибка, то удалим ошибочные скрипты
            script = "";
            return false;
        }
        else
        {
            if (globalObject().property("EventKeyPressed").isValid() && !app->isScriptMode())
            {
                // Соединим сигнал нажатия кнопки на форме со слотом обработчика нажатий кнопки в скриптах, если он есть
                if (getParent() != 0)
                {
                    qScriptConnect((getParent())->getFormWidget()->getForm(),
                                   SIGNAL(keyPressed(QKeyEvent*)),
                                   globalObject(),
                                   globalObject().property("EventKeyPressed"));
                }
            }
            errorMessage = globalObject().property("errorMessage").toString();  // Вернем строку с описанием ошибки работы скрипта
        }
    }
    return result;
}


QScriptValue ScriptEngine::evaluate (const QString & program, const QString & fileName, int lineNumber)
{
    app->appendScriptStack(this);
    QScriptEngine::evaluate(program, fileName, lineNumber);
    app->removeLastScriptStack();
    return globalObject().property("scriptResult");
}


QScriptValue ScriptEngine::evaluate(const QScriptProgram &program)
{
    QScriptValue result;
    app->appendScriptStack(this);
    result = QScriptEngine::evaluate(program);
    app->removeLastScriptStack();
    return result;
}


// События
void ScriptEngine::eventInitForm(Form* form)
{
    QString eventName = "EventInitForm";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventBeforeShowForm(Form* form)
{
    QString eventName = "EventBeforeShowForm";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventAfterShowForm(Form* form)
{
    QString eventName = "EventAfterShowForm";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}



void ScriptEngine::eventBeforeHideForm(Form* form)
{
    QString eventName = "EventBeforeHideForm";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventAfterHideForm(Form* form)
{
    QString eventName = "EventAfterHideForm";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventCloseForm(Form* form)
{
    QString eventName = "EventCloseForm";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventImport(Form* form)
{
    QString eventName = "EventImport";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventExport(Form* form)
{
    QString eventName = "EventExport";
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventAfterCalculate()
{
    QString eventName = "EventAfterCalculate";
    scriptCall(eventName, QScriptValue());
}


void ScriptEngine::eventParametersChanged()
{
    QString eventName = "EventParametersChanged";
    scriptCall(eventName, QScriptValue());
}


bool ScriptEngine::eventBeforeAddString()
{
    bool result = true;
    QScriptValue res;
    QString eventName = "EventBeforeAddString";
    res = scriptCall(eventName, QScriptValue());
    if (res.toString() != "undefined")
        result = res.toBool();
    return result;
}


void ScriptEngine::eventAfterAddString()
{
    QString eventName = "EventAfterAddString";
    scriptCall(eventName, QScriptValue());
}


bool ScriptEngine::eventAfterShowNextDicts()
{
    bool result = true;
    QScriptValue res;
    QString eventName = "EventAfterShowNextDicts";
    res = scriptCall(eventName, QScriptValue());
    if (res.toString() != "undefined")
        result = res.toBool();
    return result;
}


void ScriptEngine::eventBeforeDeleteString()
{
    QString eventName = "EventBeforeDeleteString";
    scriptCall(eventName, QScriptValue());
}


void ScriptEngine::eventAfterDeleteString()
{
    QString eventName = "EventAfterDeleteString";
    scriptCall(eventName, QScriptValue());
}


void ScriptEngine::eventSetEnabled(bool enabled)
{
    QString eventName = "EventSetEnabled";
    QScriptValueList args;
    args << QScriptValue(enabled);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventBeforeRowChanged()
{
    QString eventName = "EventBeforeRowChanged";
    scriptCall(eventName, QScriptValue());
}


void ScriptEngine::eventAfterRowChanged()
{
    QString eventName = "EventAfterRowChanged";
    scriptCall(eventName, QScriptValue());
}


void ScriptEngine::eventPhotoLoaded()
{
    QString eventName = "EventPhotoLoaded";
    scriptCall(eventName, QScriptValue());
}


QString ScriptEngine::preparePictureUrl(Essence* essence)
{
    QString result;
    QString eventName = "PreparePictureUrl";
    QScriptValueList args;
    args << newQObject(essence);
    QScriptValue res = scriptCall(eventName, QScriptValue(), args);
    if (!res.isValid() || res.isUndefined())
        result = "";
    else
        result = res.toString();
    return result;
}


QString ScriptEngine::getFilter(QString filter)
{
    QString result;
    QString eventName = "GetFilter";
    QScriptValueList args;
    args << QScriptValue(filter);
    result = scriptCall(eventName, QScriptValue(), args).toString();
    if (result.size() == 0 || result == "undefined")
        result = filter;
    return result;
}




void ScriptEngine::eventCalcTable()
{
    errorMessage = "";
    scriptResult = true;
    QString eventName = "EventCalcTable";
    scriptCall(eventName, QScriptValue());
    errorMessage = globalObject().property("errorMessage").toString();  // Вернем строку с описанием ошибки работы скрипта
    scriptResult = globalObject().property("scriptResult").toBool();    // Вернем результаты работы скрипта
}


void ScriptEngine::eventBarCodeReaded(QString barCode)
{
    QString eventName = "EventBarCodeReaded";
    QScriptValueList args;
    args << QScriptValue(barCode);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventCardCodeReaded(QString cardCode)
{
    QString eventName = "EventCardCodeReaded";
    QScriptValueList args;
    args << QScriptValue(cardCode);
    scriptCall(eventName, QScriptValue(), args);
}


void ScriptEngine::eventPreparePrintValues()
{
    QString eventName = "EventPreparePrintValues";
    scriptCall(eventName, QScriptValue());
}


bool ScriptEngine::eventKeyPressed(int key, int modifiers)
{
    bool result = false;
    QVariant res;
    QString eventName = "EventKeyPressed";
    QScriptValueList args;
    args << QScriptValue(key);
    args << QScriptValue(modifiers);
    res = scriptCall(eventName, QScriptValue(), args).toVariant();
    if (res.toString() != "undefined")
        result = res.toBool();
    return result;
}


// Конец списка событий

void ScriptEngine::showScriptError(QString eventName)
{
    errorMessage = QString(QObject::trUtf8("Ошибка в строке %1 события %2 скрипта %3: [%4]")).arg(uncaughtExceptionLineNumber()).arg(eventName).arg(scriptFileName).arg(uncaughtException().toString());
    app->showError(errorMessage);
}


QString ScriptEngine::getBlankScripts()
{
    // создадим пустой скрипт с событиями
    QString scripts;
    QTextStream stream(&scripts, QIODevice::Text);
    QHash<QString, EventFunction>* events = getEventsList();
    foreach (QString funcName, events->keys())
    {
        stream << "function " << funcName << endl;
        stream << "{";
        if (events->value(funcName).comment.size() > 0)
        {
            stream << " // " << events->value(funcName).comment << endl;
            stream << QObject::trUtf8("// Здесь Вы можете вставить свой код") << endl;
        }
        if (events->value(funcName).body.size() > 0)
            stream << events->value(funcName).body << endl;
        stream << "}" << endl;
        stream << endl << endl;
    }
    return scripts;
}


QHash<QString, EventFunction>* ScriptEngine::getEventsList()
{
    EventFunction func;

    func.comment = QObject::trUtf8("Событие происходит сразу после создания формы документа");
    appendEvent("EventInitForm(form)", &func);

    func.comment = QObject::trUtf8("Событие происходит перед открытием формы документа");
    appendEvent("EventBeforeShowForm(form)", &func);

    func.comment = QObject::trUtf8("Событие происходит после открытия формы документа");
    appendEvent("EventAfterShowForm(form)", &func);

    func.comment = QObject::trUtf8("Событие происходит перед закрытием формы документа");
    appendEvent("EventBeforeHideForm(form)", &func);

    func.comment = QObject::trUtf8("Событие происходит после закрытия формы документа");
    appendEvent("EventAfterHideForm(form)", &func);

    func.comment = QObject::trUtf8("Событие происходит перед удалением формы документа");
    appendEvent("EventCloseForm(form)", &func);

    func.comment = QObject::trUtf8("Событие происходит при нажатии кнопки <Импорт>");
    appendEvent("EventImport()", &func);

    func.comment = QObject::trUtf8("Событие происходит при нажатии кнопки <Экспорт>");
    appendEvent("EventExport()", &func);

    func.comment = QObject::trUtf8("Событие происходит при нажатии любой кнопки на форме. Параметр keyEvent имеет тип QKeyEvent");
    appendEvent("EventKeyPressed(keyEvent)", &func);

    func.comment = QObject::trUtf8("Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.");
    appendEvent("PreparePictureUrl(object)", &func);

    func.comment = QObject::trUtf8("Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.");
    func.body = "return filter;";
    appendEvent("GetFilter(filter)", &func);

    func.comment = QObject::trUtf8("Событие происходит после изменения ячейки в таблице");
    if (document != 0 && document->isQuanAccount() && document->getPrvQuan() == 1)
    {
        func.body = "var кол = getValue(\"P1__КОЛ\");\n"
                    "var цена = getValue(\"P1__ЦЕНА\");\n"
                    "var сумма = getValue(\"P1__СУММА\");\n"
                    "if (getCurrentFieldName() == \"P1__СУММА\" && кол != 0)\n"
                    "  цена = сумма / кол;\n"
                    "else\n"
                    "   сумма = кол * цена;\n"
                    "setValue(\"P1__КОЛ\", кол);\n"
                    "setValue(\"P1__ЦЕНА\", цена);\n"
                    "setValue(\"P1__СУММА\", сумма);\n";
    }
    appendEvent("EventCalcTable()", &func);

    func.comment = QObject::trUtf8("Событие предназначено для изменения возможности доступа к элементам пользовательской формы");
    appendEvent("EventSetEnabled(enabled)", &func);

    func.comment = QObject::trUtf8("Событие происходит после перемещения на другую строку");
    appendEvent("EventAfterRowChanged()", &func);

    func.comment = QObject::trUtf8("Событие происходит до перемещения на другую строку");
    appendEvent("EventBeforeRowChanged()", &func);

    func.comment = QObject::trUtf8("Событие происходит после загрузки фотографии из Интернета");
    appendEvent("EventPhotoLoaded()", &func);

    func.comment = QObject::trUtf8("Событие происходит после прочтения штрих-кода");
    appendEvent("EventBarCodeReaded(barCode)", &func);

    func.comment = QObject::trUtf8("Событие происходит после прочтения магнитной карты");
    appendEvent("EventCardCodeReaded(cardCode)", &func);

    func.comment = QObject::trUtf8("Событие происходит перед добавлением строки в документ");
    func.body = "return true;";
    appendEvent("EventBeforeAddString()", &func);

    func.comment = QObject::trUtf8("Событие происходит после добавления строки в документ");
    func.body = "return true;";
    appendEvent("EventAfterAddString()", &func);

    func.comment = QObject::trUtf8("Событие происходит перед удалением строки из документа");
    func.body = "return true;";
    appendEvent("EventBeforeDeleteString()", &func);

    func.comment = QObject::trUtf8("Событие происходит после удаления строки из документа");
    func.body = "return true;";
    appendEvent("EventAfterDeleteString()", &func);

    func.comment = QObject::trUtf8("Событие происходит после показа всех необходимых справочников при добавлении строки в документ");
    func.body = "return true;";
    appendEvent("EventAfterShowNextDicts()", &func);

    func.comment = QObject::trUtf8("Событие происходит перед созданием документа печати и предназначено для создания новых данных для документа");
    appendEvent("EventPreparePrintValues()", &func);

    func.comment = QObject::trUtf8("Событие происходит при нажатии кнопки на форме. Должно вернуть ИСТИНА, если нажатие обработано");
    func.body = "return false;";
    appendEvent("EventKeyPressed(key, modifiers)", &func);

    return &eventsList;
}


void ScriptEngine::appendEvent(QString funcName, EventFunction* func)
{
    EventFunction f;
    if (eventsList.contains(funcName))
    {
        f = eventsList.value(funcName);
        if (func->comment.size() > 0)
            f.comment = func->comment;
        if (func->body.size() > 0)
            f.body = func->body;
    }
    else
        f = *func;
    eventsList.remove(funcName);
    eventsList.insert(funcName, f);
    func->comment = "";
    func->body = "";
}


QString ScriptEngine::loadScript(QString scriptFile)
{
    QString result;
    if (!scripts.contains(scriptFile) || isSA)
    {
        QString fullScriptFile = scriptFile;
        if (!QFileInfo(scriptFile).exists())
        {
            QString scriptPath = TApplication::exemplar()->getScriptsPath();
            Essence::getFile(scriptPath, scriptFile, ScriptFileType);   // Получим скрипт с сервера, при необходимости обновим его
            fullScriptFile = scriptPath + scriptFile;
        }
        QFile file(fullScriptFile);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString script(file.readAll());
            file.close();
            result = script;
        }
        scripts.insert(scriptFile, result);
    }
    else
    {
        result = scripts.value(scriptFile);
    }
//    scriptFileName = scriptFile;
    return result;
}


void ScriptEngine::removeScript(QString scriptFile)
{
    scripts.remove(scriptFile);
}


QScriptValue ScriptEngine::scriptCall(QString eventName, const QScriptValue &thisObject, const QScriptValueList &args)
{
    QScriptValue result("undefined");
    if (globalObject().property(eventName).isFunction())
    {
        app->appendScriptStack(this);
        result = globalObject().property(eventName).call(thisObject, args);
        if (hasUncaughtException())
        {   // Если в скриптах произошла ошибка
            showScriptError(eventName);
        }
        app->removeLastScriptStack();
    }
    return result;
}

