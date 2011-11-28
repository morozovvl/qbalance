#include <QSqlDatabase>
#include <QSqlQuery>
#include "scriptengine.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"
#include "../storage/mysqlrecord.h"
#include "../gui/mainwindow.h"
#include "../gui/form.h"
#include "eventloop.h"


QScriptValue value(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue fieldName = context->argument(0);
    if (fieldName.isString())
    {
        if (engine->evaluate("table").isValid())
        {
            QScriptValue value = engine->evaluate(QString("table.getValue('%1')").arg(fieldName.toString()));
            if (value.isValid())
            {
                return value;
            }
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


void ScriptEngine::showError(QString text)
{
    TApplication::exemplar()->showError(text);
}


bool ScriptEngine::open(QString scriptFile)
{
    if (scriptFile.size() > 0)
    {   // Если в параметрах дано имя файла
        QString scriptFileName = scriptFile + ".qs";
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
        if (script.size() > 0)
        {
            loadScriptObjects();
            evaluate(script);
            if (hasUncaughtException())
            {   // Если в скриптах произошла ошибка
                showError(QString(QObject::trUtf8("Ошибка в строке %1 скрипта %2")).arg(uncaughtExceptionLineNumber()).arg(scriptFileName));
                return false;
            }
            return globalObject().property("scriptResult").toBool();    // Вернем результаты работы скрипта
        }
        showError(QString(QObject::trUtf8("Не удалось открыть скрипт %1")).arg(scriptFileName));
        return false;
    }
    if (script.size() > 0)
    {   // Если задан текст скрипта, то в первую очередь выполним его
        loadScriptObjects();
        evaluate(script);
        if (hasUncaughtException())
        {   // Если в скриптах произошла ошибка
           showError(QString(QObject::trUtf8("Ошибка в строке %1 скрипта")).arg(uncaughtExceptionLineNumber()));
           return false;
        }
        return globalObject().property("scriptResult").toBool();    // Вернем результаты работы скрипта
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

    // Объявим глобальные переменные и объекты
    globalObject().setProperty("scriptResult", true);   // результат работы скрипта
    globalObject().setProperty("DBFactory", newQObject(TApplication::exemplar()->getDBFactory()));

    globalObject().setProperty("value", newFunction(value));
}


void ScriptEngine::calcTable()
{
//    globalObject().property("calcTable").call();
    evaluate(script);
}


