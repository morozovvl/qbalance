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

#include "documentscriptengine.h"
#include "../kernel/document.h"
#include "../kernel/documents.h"
#include "../engine/reportcontext.h"


QScriptValue getSaldo(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue acc = context->argument(0);
    if (acc.isString() && engine->evaluate("document").isValid())
    {
        QScriptValue value = engine->evaluate(QString("document.getSaldo('%1')").arg(acc.toString()));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue saveVariable(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(1).isString())
        return engine->evaluate(QString("document.saveVariable('%1', %2)").arg(context->argument(0).toString()).arg(context->argument(1).toString()));
    else
        return engine->evaluate(QString("document.saveVariable('%1', '%2')").arg(context->argument(0).toString()).arg(context->argument(1).toString()));
}


QScriptValue restoreVariable(QScriptContext* context, QScriptEngine* engine) {
    return engine->evaluate(QString("document.restoreVariable('%1')").arg(context->argument(0).toString()));
}



DocumentScriptEngine::DocumentScriptEngine(Essence* parent)
:ScriptEngine(parent)
{
    reportContext = new ReportContext(0 /*nullptr*/);
    reportContext->setScriptEngine(this);
}


DocumentScriptEngine::DocumentScriptEngine(QHash<QString, QVariant>* context, Essence *parent)
:ScriptEngine(parent)
{
    reportContext = new ReportContext(context);
    reportContext->setScriptEngine(this);
}


DocumentScriptEngine::~DocumentScriptEngine()
{
    if (reportContext != 0 /*nullptr*/)
    {
        reportContext->clear();
        delete reportContext;
        reportContext = 0 /*nullptr*/;
    }
}


void DocumentScriptEngine::setReportContext(QHash<QString, QVariant>* context)
{
    reportContext = new ReportContext(context);
}


ReportContext* DocumentScriptEngine::getReportContext()
{
    return reportContext;
}


void DocumentScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    globalObject().setProperty("getSaldo", newFunction(getSaldo));
    globalObject().setProperty("saveVariable", newFunction(saveVariable));
    globalObject().setProperty("restoreVariable", newFunction(restoreVariable));
    if (documents != 0 /*nullptr*/)
        globalObject().setProperty("isDocumentScript", true);   // скрипт выполняется в контексте документа
    else
        globalObject().setProperty("isDocumentScript", false);

    // инициализируем глобальные объекты скрипта печати
    if (reportContext != 0 /*nullptr*/)
    {
        globalObject().setProperty("reportContext", newQObject(reportContext, QScriptEngine::ScriptOwnership));
    }
}


// События
void DocumentScriptEngine::eventAppendFromQuery(QString queryName, QSqlRecord* values)
{
    QString eventName = "EventAppendFromQuery";
    // Сначала преобразуем данные в записи к виду, пригодному для передачи в скрипты
    QScriptValue row = newObject();
    for (int i = 0; i < values->count(); i++)
        row.setProperty(values->fieldName(i), QScriptValue(this, values->value(i).toString()));

    // Подготовим номер запроса и запись с данными запроса для передачи в скрипт через параметры функции
    QScriptValueList args;
    args << newVariant(QVariant(queryName));
    args << row;
    scriptCall(eventName, currentContext()->thisObject(), args);
}


bool DocumentScriptEngine::eventBeforeLinePrint(int strNum)
{
    bool result = true;
    QScriptValue res;
    QString eventName = "EventBeforeLinePrint";
    QScriptValueList args;
    args << newVariant(QVariant(strNum));
    res = scriptCall(eventName, currentContext()->thisObject(), args);
    if (res.toString() != "undefined")
        result = res.toBool();
    return result;
}


void DocumentScriptEngine::eventAfterLinePrint(int strNum)
{
    QString eventName = "EventAfterLinePrint";
    QScriptValueList args;
    args << newVariant(QVariant(strNum));
    scriptCall(eventName, currentContext()->thisObject(), args);
}


void DocumentScriptEngine::eventBeforeTotalPrint()
{
    QString eventName = "EventBeforeTotalPrint";
    scriptCall(eventName, currentContext()->thisObject());
}


QHash<QString, EventFunction>* DocumentScriptEngine::getEventsList()
{
    ScriptEngine::getEventsList();
    EventFunction func;
    func.comment = QObject::trUtf8("Событие происходит в момент изменения постоянного справочника документа");
    appendEvent("EventParametersChanged()", &func);
    func.comment = QObject::trUtf8("Событие происходит после вычисления в ячейке");
    appendEvent("EventAfterCalculate()", &func);
    func.comment = QObject::trUtf8("Вызывается при добавлении каждой новой записи из запроса. Если готового запроса на сервере нет, то тогда вызывается один раз и скрипт сам должен создать и обработать запрос.");
    appendEvent("EventAppendFromQuery(queryName, record)", &func);
    func.comment = QObject::trUtf8("Вызывается до печати очередной строки в документе");
    appendEvent("EventBeforeLinePrint(strNum)", &func);
    func.comment = QObject::trUtf8("Вызывается после печати очередной строки в документе");
    appendEvent("EventAfterLinePrint(strNum)", &func);
    return &eventsList;
}


