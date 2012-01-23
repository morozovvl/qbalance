#include <QSqlDatabase>
#include <QSqlQuery>
#include "scriptengine.h"
#include "../kernel/app.h"
#include "../kernel/dictionary.h"
#include "../storage/dbfactory.h"
#include "../storage/mysqlrecord.h"
#include "../gui/mainwindow.h"
#include "../gui/form.h"
#include "eventloop.h"


// Функции, преобразующие вид функций в скриптах table.<функция> к виду <функция> для упрощения написания скриптов

bool isNumeric(ScriptEngine* engine, QString field = "")
{
    QString fieldName;
    if (field.size() == 0)
        fieldName = ((Essence*)engine->parent())->getCurrentFieldName();
    else
        fieldName = field;
    if (((Essence*)engine->parent())->getValue(fieldName).canConvert(QVariant::Double))
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
    QScriptValue fieldName = context->argument(0);
    if (fieldName.isString() && engine->evaluate("table").isValid())
    {
        QScriptValue value;
        if (isNumeric((ScriptEngine*)engine, fieldName.toString()))
            value = engine->evaluate(QString("parseFloat(table.getValue('%1'))").arg(fieldName.toString()));
        else
            value = engine->evaluate(QString("table.getValue('%1')").arg(fieldName.toString()));
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

// класс Form
Q_DECLARE_METATYPE(Form*)

QScriptValue FormConstructor(QScriptContext *context, QScriptEngine *engine) {
     Form *object = new Form();
     object->open(context->argument(0).toString(), TApplication::exemplar()->getMainWindow()->centralWidget());
     object->setIcons();
     object->setButtonsSignals();
     return engine->newQObject(object, QScriptEngine::AutoOwnership);
//     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue FormToScriptValue(QScriptEngine *engine, Form* const &in) {
    return engine->newQObject(in);
}

void FormFromScriptValue(const QScriptValue &object, Form* &out) {
    out = qobject_cast<Form*>(object.toQObject());
}


//================================================================================================
// Реализация класса

// QList<EventFunction> ScriptEngine::eventsList;          // Список доступных в скриптах событий с комментариями


ScriptEngine::ScriptEngine(QObject *parent/* = 0*/) : QScriptEngine(parent)
{
    sqlFieldClass = new SqlFieldClass(this);
    sqlRecordClass = new SqlRecordClass(this, sqlFieldClass);
    sqlQueryClass = new SqlQueryClass(this, sqlRecordClass);
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
        {
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
    qScriptRegisterMetaType(this, FormToScriptValue, FormFromScriptValue);
    globalObject().setProperty("Form", newQMetaObject(&QObject::staticMetaObject, newFunction(FormConstructor)));
    qScriptRegisterMetaType(this, DictionaryToScriptValue, DictionaryFromScriptValue);
    globalObject().setProperty("Dictionary", newQMetaObject(&QObject::staticMetaObject, newFunction(DictionaryConstructor)));

    // Объявим глобальные переменные и объекты
    globalObject().setProperty("table", newQObject(parent()));
    globalObject().setProperty("scriptResult", true);   // результат работы скрипта
    globalObject().setProperty("DBFactory", newQObject(TApplication::exemplar()->getDBFactory()));
    globalObject().setProperty("getCurrentFieldName", newFunction(getCurrentFieldName));
    globalObject().setProperty("getValue", newFunction(getValue));
    globalObject().setProperty("setValue", newFunction(setValue));
    globalObject().setProperty("getOldValue", newFunction(getOldValue));
}


bool ScriptEngine::evaluate()
{
    scriptResult = true;
    if (script.size() > 0)
    {
        loadScriptObjects();
        QScriptEngine::evaluate(script);
        if (hasUncaughtException())
        {   // Если в скриптах произошла ошибка
            errorMessage = QString(QObject::trUtf8("Ошибка в строке %1 скрипта %2: [%3]")).arg(uncaughtExceptionLineNumber()).arg(scriptFileName).arg(uncaughtException().toString());
            return false;
        }
        scriptResult = globalObject().property("scriptResult").toBool();    // Вернем результаты работы скрипта
        return scriptResult;
    }
    return true;
}


// События
void ScriptEngine::eventInitForm()
{
    globalObject().property("EventInitForm").call();
}


void ScriptEngine::eventBeforeShowForm()
{
    globalObject().property("EventBeforeShowForm").call();
}


void ScriptEngine::eventAfterHideForm()
{
    globalObject().property("EventAfterHideForm").call();
}


void ScriptEngine::eventCloseForm()
{
    globalObject().property("EventCloseForm").call();
}


QString ScriptEngine::getBlankScripts()
{
    // создадим пустой скрипт с событиями
    QString scripts;
    QTextStream stream(&scripts, QIODevice::Text);
    QList<EventFunction>* events = getEventsList();
    for (int i = 0; i < events->count(); i++)
    {
        stream << "function " << events->at(i).name << "()" << endl;
        stream << "{ " << events->at(i).comment << endl;
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

        func.name = "EventInitForm";
        func.comment = "// " + QObject::trUtf8("Событие происходит сразу после создания формы документа");
        eventsList.append(func);

        func.name = "EventBeforeShowForm";
        func.comment = "// " + QObject::trUtf8("Событие происходит перед открытием формы документа");
        eventsList.append(func);

        func.name = "EventAfterHideForm";
        func.comment = "// " + QObject::trUtf8("Событие происходит после закрытия формы документа");
        eventsList.append(func);

        func.name = "EventCloseForm";
        func.comment = "// " + QObject::trUtf8("Событие происходит перед удалением формы документа");
        eventsList.append(func);

    }
    return &eventsList;
}

