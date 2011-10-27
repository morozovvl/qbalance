#include <QSqlDatabase>
#include <QSqlQuery>
#include "scriptengine.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"
#include "../storage/mysqlrecord.h"

//================================================================================================
// Реализация класса
ScriptEngine::ScriptEngine(QString file/* = ""*/, QObject *parent/* = 0*/) : QScriptEngine(parent)
{
    scriptFile = file;
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

bool ScriptEngine::open()
{
    if (scriptFile.size() > 0)
    {
        QString scriptFileName = scriptFile + ".qs";
        QFile file(scriptFileName);
        if (file.open(QIODevice::ReadOnly))
        {   // Если существуют скрипты
            // прочитаем и запустим их
            loadScriptObjects();
            QTextStream in(&file);
            QString script = in.readAll();
            file.close();
            evaluate(script);
            if (hasUncaughtException())
            {   // Если в скриптах произошла ошибка
                showError(QString(QObject::tr("Ошибка в строке %1 скрипта %2")).arg(uncaughtExceptionLineNumber()).arg(scriptFileName));
                return false;
            }
            return globalObject().property("scriptResult").toBool();    // Вернем результаты работы скрипта
        }
        showError(QString(QObject::tr("Не удалось открыть скрипт %1")).arg(scriptFileName));
        return false;
    }
    return true;
}

void ScriptEngine::loadScriptObjects()
{
    installTranslatorFunctions(QScriptValue());

    // Объявим классы
    globalObject().setProperty(sqlRecordClass->name(), sqlRecordClass->constructor());
    globalObject().setProperty(sqlFieldClass->name(), sqlFieldClass->constructor());
    globalObject().setProperty(sqlQueryClass->name(), sqlQueryClass->constructor());

    // Объявим глобальные переменные и объекты
    globalObject().setProperty("scriptResult", true);   // результат работы скрипта
    globalObject().setProperty("DBFactory", newQObject(TApplication::exemplar()->getDBFactory()));

}
