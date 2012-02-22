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


// QList<EventFunction> DocumentScriptEngine::eventsList;          // Список доступных в скриптах событий с комментариями


QScriptValue getSumValue(QScriptContext* context, QScriptEngine* engine) {
    return engine->evaluate(QString("document.getSumValue('%1')").arg(context->argument(0).toString()));
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
    globalObject().setProperty("getSumValue", newFunction(getSumValue));
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


QList<EventFunction>* DocumentScriptEngine::getEventsList()
{
   if (eventsList.size() == 0)
    {// Зарядим список событий
        ScriptEngine::getEventsList();
        EventFunction func;
        func.name = "EventParametersChanged";
        func.comment = "// " + QObject::trUtf8("Событие происходит в момент изменения постоянного справочника документа");
        eventsList.append(func);
        func.name = "EventBeforeAddString";
        func.comment = "// " + QObject::trUtf8("Событие происходит перед добавлением строки в документ");
        eventsList.append(func);
        func.name = "EventAfterAddString";
        func.comment = "// " + QObject::trUtf8("Событие происходит после добавления строки в документ");
        eventsList.append(func);
        func.name = "EventAfterCalculate";
        func.comment = "// " + QObject::trUtf8("Событие происходит после вычисления в ячейке");
        eventsList.append(func);
    }
    return &eventsList;
}


