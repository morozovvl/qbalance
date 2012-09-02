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

#include <QDebug>
#include "documentscriptengine.h"
#include "../kernel/document.h"


QScriptValue getDictionary(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue dictName = context->argument(0);
    if (dictName.isString() && engine->evaluate("document").isValid())
    {
        QScriptValue value = engine->evaluate(QString("document.getDictionary('%1')").arg(dictName.toString()));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getSaldo(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue acc = context->argument(0);
    QScriptValue dictName = context->argument(1);
    if (acc.isString() && dictName.isString() && engine->evaluate("document").isValid())
    {
        QScriptValue value = engine->evaluate(QString("document.getSaldo('%1', '%2')").arg(acc.toString()).arg(dictName.toString()));
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


DocumentScriptEngine::DocumentScriptEngine(QObject* parent/* = 0*/)
:ScriptEngine(parent)
{
}


void DocumentScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    globalObject().setProperty("document", newQObject((Document*)parent()));
    globalObject().setProperty("documents", newQObject((QObject*)((Document*)parent())->getParent()));
    globalObject().setProperty("getDictionary", newFunction(getDictionary));
    globalObject().setProperty("getSaldo", newFunction(getSaldo));
    globalObject().setProperty("getSumValue", newFunction(getSumValue));
    globalObject().setProperty("saveVariable", newFunction(saveVariable));
    globalObject().setProperty("restoreVariable", newFunction(restoreVariable));
}


// События
void DocumentScriptEngine::eventParametersChanged()
{
    globalObject().property("EventParametersChanged").call();
}


void DocumentScriptEngine::eventBeforeAddString()
{
    globalObject().property("EventBeforeAddString").call();
}


void DocumentScriptEngine::eventAfterAddString()
{
    globalObject().property("EventAfterAddString").call();
}


void DocumentScriptEngine::eventAfterCalculate()
{
    globalObject().property("EventAfterCalculate").call();
}


void DocumentScriptEngine::eventAppendFromQuery(int number, QSqlRecord* values)
{
    // Сначала преобразуем данные в записи к виду, пригодному для передачи в скрипты
    QScriptValue row = newObject();
    for (int i = 0; i < values->count(); i++)
        row.setProperty(values->fieldName(i), QScriptValue(this, values->value(i).toString()));

    // Подготовим номер запроса и запись с данными запроса для передачи в скрипт через параметры функции
    QScriptValueList args;
    args << newVariant(QVariant(number));
    args << row;
    globalObject().property("EventAppendFromQuery").call(QScriptValue(), args);
}


QList<EventFunction>* DocumentScriptEngine::getEventsList()
{
   if (eventsList.size() == 0)
    {// Зарядим список событий
        ScriptEngine::getEventsList();
        EventFunction func;
        func.name = "EventParametersChanged()";
        func.comment = QObject::trUtf8("Событие происходит в момент изменения постоянного справочника документа");
        eventsList.append(func);
        func.name = "EventBeforeAddString()";
        func.comment = QObject::trUtf8("Событие происходит перед добавлением строки в документ");
        eventsList.append(func);
        func.name = "EventAfterAddString()";
        func.comment = QObject::trUtf8("Событие происходит после добавления строки в документ");
        eventsList.append(func);
        func.name = "EventAfterCalculate()";
        func.comment = QObject::trUtf8("Событие происходит после вычисления в ячейке");
        eventsList.append(func);
        func.name = "EventAppendFromQuery(id, record)";
        func.comment = QObject::trUtf8("Вызывается при добавлении новой записи из запроса");
        eventsList.append(func);
    }
    return &eventsList;
}


