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


QScriptValue getSumValue(QScriptContext* context, QScriptEngine* engine) {
    return engine->evaluate(QString("document.getSumValue('%1')").arg(context->argument(0).toString()));
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


DocumentScriptEngine::DocumentScriptEngine(Essence* parent/* = 0*/)
:ScriptEngine(parent)
{
    reportContext = 0;
}


DocumentScriptEngine::DocumentScriptEngine(QHash<QString, QVariant>* context, Essence *parent/* = 0*/)
:ScriptEngine(parent)
{
    reportContext = new ReportContext(context);
}


void DocumentScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    globalObject().setProperty("getSaldo", newFunction(getSaldo));
    globalObject().setProperty("getSumValue", newFunction(getSumValue));
    globalObject().setProperty("saveVariable", newFunction(saveVariable));
    globalObject().setProperty("restoreVariable", newFunction(restoreVariable));
    if (documents != 0)
    {
        globalObject().setProperty("isDocumentScript", true);   // скрипт выполняется в контексте документа
        globalObject().setProperty("documents", newQObject(documents));
    }
    else
        globalObject().setProperty("isDocumentScript", false);

    // инициализируем глобальные объекты скрипта печати
    if (reportContext != 0)
        globalObject().setProperty("reportContext", newQObject(reportContext));
}


// События
void DocumentScriptEngine::eventAppendFromQuery(QString queryName, QSqlRecord* values)
{
    // Сначала преобразуем данные в записи к виду, пригодному для передачи в скрипты
    QScriptValue row = newObject();
    for (int i = 0; i < values->count(); i++)
        row.setProperty(values->fieldName(i), QScriptValue(this, values->value(i).toString()));

    // Подготовим номер запроса и запись с данными запроса для передачи в скрипт через параметры функции
    QScriptValueList args;
    args << newVariant(QVariant(queryName));
    args << row;
    globalObject().property("EventAppendFromQuery").call(QScriptValue(), args);
}


void DocumentScriptEngine::eventBeforeLinePrint(int strNum)
{
    QScriptValueList args;
    args << newVariant(QVariant(strNum));
    globalObject().property("EventBeforeLinePrint").call(QScriptValue(), args);
}


void DocumentScriptEngine::eventAfterLinePrint(int strNum)
{
    QScriptValueList args;
    args << newVariant(QVariant(strNum));
    globalObject().property("EventAfterLinePrint").call(QScriptValue(), args);
}


QHash<QString, EventFunction>* DocumentScriptEngine::getEventsList()
{
    ScriptEngine::getEventsList();
    EventFunction func;
    func.comment = QObject::trUtf8("Событие происходит в момент изменения постоянного справочника документа");
    appendEvent("EventParametersChanged()", func);
    func.comment = QObject::trUtf8("Событие происходит после вычисления в ячейке");
    appendEvent("EventAfterCalculate()", func);
    func.comment = QObject::trUtf8("Вызывается при добавлении каждой новой записи из запроса. Если готового запроса на сервере нет, то тогда вызывается один раз и скрипт сам должен создать и обработать запрос.");
    appendEvent("EventAppendFromQuery(queryName, record)", func);
    func.comment = QObject::trUtf8("Вызывается до печати очередной строки в документе");
    appendEvent("EventBeforeLinePrint(strNum)", func);
    func.comment = QObject::trUtf8("Вызывается после печати очередной строки в документе");
    appendEvent("EventAfterLinePrint(strNum)", func);
    return &eventsList;
}


