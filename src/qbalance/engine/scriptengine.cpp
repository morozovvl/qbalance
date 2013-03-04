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
#include <QtGui/QFileDialog>
#include <QDebug>
#include "scriptengine.h"
#include "../kernel/app.h"
#include "../kernel/dictionary.h"
#include "../storage/dbfactory.h"
#include "../gui/mainwindow.h"
#include "../gui/form.h"
#include "../gui/formgrid.h"
#include "eventloop.h"


// Функции, преобразующие вид функций в скриптах table.<функция> к виду <функция> для упрощения написания скриптов

bool isNumeric(ScriptEngine* engine, QString field = "")
{
    QString fieldName;
    if (field.size() == 0)
        fieldName = ((Essence*)engine->parent())->getCurrentFieldName();
    else
        fieldName = field;
    if (QString(((Essence*)engine->parent())->getValue(fieldName).typeName()).compare("double", Qt::CaseInsensitive) == 0)
        return true;
    return false;
}


QScriptValue getCurrentFieldName(QScriptContext *, QScriptEngine* engine) {
    if (engine->evaluate("table").isValid())
    {
        QScriptValue value = engine->evaluate(QString("table.getCurrentFieldName()"));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getValue(QScriptContext* context, QScriptEngine* engine) {
    if (context->argument(0).isString() && engine->evaluate("table").isValid())
    {
        QString fieldName = context->argument(0).toString();
        QScriptValue value;
        if (isNumeric((ScriptEngine*)engine, fieldName))
            value = engine->evaluate(QString("parseFloat(table.getValue('%1'))").arg(fieldName));
        else
            value = engine->evaluate(QString("table.getValue('%1')").arg(fieldName));
        if (value.isValid())
        {
            return value;
        }
    }
    return QScriptValue();
}


QScriptValue setValue(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue fieldName = context->argument(0);
    if (fieldName.isString() && engine->evaluate("table").isValid())
    {
        QScriptValue value = engine->evaluate(QString("table.setValue('%1', %2)").arg(fieldName.toString()).arg(context->argument(1).toString()));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getOldValue(QScriptContext*, QScriptEngine* engine) {
    if (engine->evaluate("table").isValid())
    {
        QScriptValue value;
        if (isNumeric((ScriptEngine*)engine))
            value = engine->evaluate(QString("parseFloat(table.getOldValue())"));
        else
            value = engine->evaluate(QString("table.getOldValue()"));
        if (value.isValid())
        {
            return value;
        }
    }
    return QScriptValue();
}

/*
QScriptValue getId(QScriptContext* context, QScriptEngine* engine) {
    if (engine->evaluate("table").isValid())
    {
        int row = context->argument(0).toInteger();
        QScriptValue value;
        value = engine->evaluate(QString("table.getId(%1)").arg(row));
        if (value.isValid())
        {
            return value;
        }
    }
    return QScriptValue();
}


QScriptValue getName(QScriptContext* context, QScriptEngine* engine) {
    if (engine->evaluate("table").isValid())
    {
        int row = context->argument(0).toInteger();
        QScriptValue value;
        value = engine->evaluate(QString("table.getName(%1)").arg(row));
        if (value.isValid())
        {
            return value;
        }
    }
    return QScriptValue();
}
*/

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

// класс Dictionary
Q_DECLARE_METATYPE(Dictionary*)

QScriptValue DictionaryConstructor(QScriptContext *context, QScriptEngine *engine) {
     Dictionary* object = new Dictionary(context->argument(0).toString());
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



/*
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
*/

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
            object = new QFileDialog(((FormGrid*)context->argument(0).toQObject())->getForm(),
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


QScriptValue importExtension(QScriptContext *context, QScriptEngine *engine)
{
    return engine->importExtension(context->argument(0).toString());
}

//================================================================================================
// Реализация класса

// QList<EventFunction> ScriptEngine::eventsList;          // Список доступных в скриптах событий с комментариями


ScriptEngine::ScriptEngine(QObject *parent/* = 0*/) : QScriptEngine(parent)
{
    sqlFieldClass = new SqlFieldClass(this);
    sqlRecordClass = new SqlRecordClass(this, sqlFieldClass);
    sqlQueryClass = new SqlQueryClass(this, sqlRecordClass);
    errorMessage = QObject::trUtf8("Ошибка скрипта!");
}


ScriptEngine::~ScriptEngine()
{
    delete sqlQueryClass;
    delete sqlRecordClass;
    delete sqlFieldClass;
}


bool ScriptEngine::open(QString scriptFile)
{
    if (scriptFile.size() > 0)
    {   // Если в параметрах дано имя файла
        scriptFileName = scriptFile;
        // Попытаемся сначала получить скрипты на сервере
        script = QString(TApplication::exemplar()->getDBFactory()->getFile(scriptFileName, ScriptFileType));
        if (script.size() == 0)
        {   // Скрипты на сервере отсутствуют. Попытаемся загрузить локальные скрипты
            QFile file(scriptFileName);
            if (file.open(QIODevice::ReadOnly))
            {   // Если существуют скрипты
                // прочитаем и запустим их
                QTextStream in(&file);
                script = in.readAll();
                file.close();
            }
        }
    }
    loadScriptObjects();
    return true;
}


void ScriptEngine::loadScriptObjects()
{
    installTranslatorFunctions(QScriptValue());

    // Объявим классы для работы с БД
    globalObject().setProperty(sqlRecordClass->name(), sqlRecordClass->constructor());
    globalObject().setProperty(sqlFieldClass->name(), sqlFieldClass->constructor());
    globalObject().setProperty(sqlQueryClass->name(), sqlQueryClass->constructor());

    // Объявим классы для работы с пользовательскими формами
    qScriptRegisterMetaType(this, EventLoopToScriptValue, EventLoopFromScriptValue);
    globalObject().setProperty("EventLoop", newQMetaObject(&QObject::staticMetaObject, newFunction(EventLoopConstructor)));
//    qScriptRegisterMetaType(this, FormToScriptValue, FormFromScriptValue);
//    globalObject().setProperty("Form", newQMetaObject(&QObject::staticMetaObject, newFunction(FormConstructor)));
//    qScriptRegisterMetaType(this, FormGridToScriptValue, FormGridFromScriptValue);
//    globalObject().setProperty("FormGrid", newQMetaObject(&QObject::staticMetaObject, newFunction(FormGridConstructor)));
    qScriptRegisterMetaType(this, DictionaryToScriptValue, DictionaryFromScriptValue);
    globalObject().setProperty("Dictionary", newQMetaObject(&QObject::staticMetaObject, newFunction(DictionaryConstructor)));
    qScriptRegisterMetaType(this, SaldoToScriptValue, SaldoFromScriptValue);
    globalObject().setProperty("Saldo", newQMetaObject(&QObject::staticMetaObject, newFunction(SaldoConstructor)));
    qScriptRegisterMetaType(this, DictionariesToScriptValue, DictionariesFromScriptValue);
    globalObject().setProperty("Dictionaries", newQMetaObject(&QObject::staticMetaObject, newFunction(DictionariesConstructor)));

    globalObject().setProperty("QPushButton", newQMetaObject(&QObject::staticMetaObject, newFunction(QPushButtonConstructor)));
    qScriptRegisterMetaType(this, QPushButtonToScriptValue, QPushButtonFromScriptValue);
//    globalObject().setProperty("QFileDialog", newQMetaObject(&QObject::staticMetaObject, newFunction(QFileDialogConstructor)));
//    qScriptRegisterMetaType(this, QFileDialogToScriptValue, QFileDialogFromScriptValue);

    // Объявим глобальные переменные и объекты
//    globalObject().setProperty("form", newQObject(((Essence*)parent())->getForm()->getForm()));
    globalObject().setProperty("table", newQObject(parent()));
    globalObject().setProperty("scriptResult", true);   // результат работы скрипта
    globalObject().setProperty("errorMessage", errorMessage);   // текст с описанием ошибки работы скрипта
    globalObject().setProperty("db", newQObject(TApplication::exemplar()->getDBFactory()));
    globalObject().setProperty("app", newQObject(TApplication::exemplar()));
    globalObject().setProperty("getCurrentFieldName", newFunction(getCurrentFieldName));
//    globalObject().setProperty("getId", newFunction(getId));
//    globalObject().setProperty("getName", newFunction(getName));
    globalObject().setProperty("getValue", newFunction(getValue));
    globalObject().setProperty("setValue", newFunction(setValue));
    globalObject().setProperty("getOldValue", newFunction(getOldValue));

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

//    QScriptValueIterator it(globalObject().property("form"));
//    while (it.hasNext())
//    {
//        it.next();
//        qDebug() << it.name() << ": " << it.value().toString();
//    }

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
            return false;
        }
        if (globalObject().property("EventKeyPressed").isValid())
        {
            // Соединим сигнал нажатия кнопки на форме со слотом обработчика нажатий кнопки в скриптах, если он есть
            qScriptConnect(((Essence*)parent())->getForm()->getForm(),
                           SIGNAL(keyPressed(QKeyEvent*)),
                           globalObject(),
                           globalObject().property("EventKeyPressed"));
        }
        errorMessage = globalObject().property("errorMessage").toString();  // Вернем строку с описанием ошибки работы скрипта
        return result;
    }
    return result;
}


QScriptValue ScriptEngine::evaluate (const QString & program, const QString & fileName, int lineNumber)
{
    return QScriptEngine::evaluate(program, fileName, lineNumber);
}


// События
void ScriptEngine::eventInitForm(Form* form)
{
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    globalObject().property("EventInitForm").call(QScriptValue(), args);
}


void ScriptEngine::eventBeforeShowForm(Form* form)
{
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    globalObject().property("EventBeforeShowForm").call(QScriptValue(), args);
}


void ScriptEngine::eventAfterHideForm(Form* form)
{
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    globalObject().property("EventAfterHideForm").call(QScriptValue(), args);
}


void ScriptEngine::eventCloseForm(Form* form)
{
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    globalObject().property("EventCloseForm").call(QScriptValue(), args);
}


void ScriptEngine::eventImport(Form* form)
{
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    globalObject().property("EventImport").call(QScriptValue(), args);
}


void ScriptEngine::eventExport(Form* form)
{
    QScriptValueList args;
    args << newQObject((FormGrid*)form);
    globalObject().property("EventExport").call(QScriptValue(), args);
}


void ScriptEngine::eventAfterCalculate()
{
    globalObject().property("EventAfterCalculate").call();
}


void ScriptEngine::eventParametersChanged()
{
    globalObject().property("EventParametersChanged").call();
}


void ScriptEngine::eventBeforeAddString()
{
    globalObject().property("EventBeforeAddString").call();
}


void ScriptEngine::eventAfterAddString()
{
    globalObject().property("EventAfterAddString").call();
}


QString ScriptEngine::preparePictureUrl(Essence* essence)
{
    QScriptValueList args;
    QString result;
    args << newQObject(essence);
    result = globalObject().property("PreparePictureUrl").call(QScriptValue(), args).toString();
    if (result == "undefined")
        result = "";
    return result;
}


void ScriptEngine::eventCalcTable()
{
    globalObject().property("EventCalcTable").call();
}


QString ScriptEngine::getBlankScripts()
{
    // создадим пустой скрипт с событиями
    QString scripts;
    QTextStream stream(&scripts, QIODevice::Text);
    QList<EventFunction>* events = getEventsList();
    for (int i = 0; i < events->count(); i++)
    {
        stream << "function " << events->at(i).name << endl;
        stream << "{";
        if (events->at(i).comment.size() > 0)
            stream << " // " << events->at(i).comment << endl;
        stream << QObject::trUtf8("// Здесь Вы можете вставить свой код") << endl;
        stream << "}" << endl;
        stream << endl << endl;
    }
    return scripts;
}


QList<EventFunction>* ScriptEngine::getEventsList()
{
    if (eventsList.size() == 0)
    {// Зарядим список событий

        EventFunction func;

        func.name = "EventInitForm()";
        func.comment = QObject::trUtf8("Событие происходит сразу после создания формы документа");
        eventsList.append(func);

        func.name = "EventBeforeShowForm()";
        func.comment = QObject::trUtf8("Событие происходит перед открытием формы документа");
        eventsList.append(func);

        func.name = "EventAfterHideForm()";
        func.comment = QObject::trUtf8("Событие происходит после закрытия формы документа");
        eventsList.append(func);

        func.name = "EventCloseForm()";
        func.comment = QObject::trUtf8("Событие происходит перед удалением формы документа");
        eventsList.append(func);

        func.name = "EventImport()";
        func.comment = QObject::trUtf8("Событие происходит при нажатии кнопки <Импорт>");
        eventsList.append(func);

        func.name = "EventExport()";
        func.comment = QObject::trUtf8("Событие происходит при нажатии кнопки <Экспорт>");
        eventsList.append(func);

        func.name = "EventKeyPressed(keyEvent)";
        func.comment = QObject::trUtf8("Событие происходит при нажатии любой кнопки на форме. Параметр keyEvent имеет тип QKeyEvent");
        eventsList.append(func);

        func.name = "PreparePictureUrl(object)";
        func.comment = QObject::trUtf8("Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.");
        eventsList.append(func);

        func.name = "EventCalcTable()";
        func.comment = QObject::trUtf8("Событие происходит после изменения ячейки в таблице");
        eventsList.append(func);

    }
    return &eventsList;
}

