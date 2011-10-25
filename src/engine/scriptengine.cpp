#include <QSqlDatabase>
#include <QSqlQuery>
#include "scriptengine.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"
#include "../storage/mysqlrecord.h"
#include "sqlqueryclass.h"

//================================================================================================
// Реализация класса
ScriptEngine::ScriptEngine(QString file/* = ""*/, QObject *parent/* = 0*/) : QScriptEngine(parent)
{
    scriptFile = file;
}

void ScriptEngine::showError(QString text) {
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

    // Объявим класс SqlQuery
    SqlQueryClass *sqlQueryClass = new SqlQueryClass(this);                 // Не нравится эта конструкция
    globalObject().setProperty("SqlQuery", sqlQueryClass->constructor());   // но походу так надо заряжать класс

    // Объявим глобальные переменные и объекты
    globalObject().setProperty("scriptResult", true);   // результат работы скрипта
    globalObject().setProperty("DBFactory", newQObject(TApplication::exemplar()->getDBFactory()));

}
