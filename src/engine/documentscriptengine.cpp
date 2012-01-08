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


DocumentScriptEngine::DocumentScriptEngine(QObject* parent/* = 0*/)
:ScriptEngine(parent)
{
}


void DocumentScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    globalObject().setProperty("table", newQObject(parent()));
    globalObject().setProperty("document", newQObject((Document*)parent()));
    globalObject().setProperty("documents", newQObject((QObject*)((Document*)parent())->getParent()));
    globalObject().setProperty("getDictionary", newFunction(getDictionary));
}


// События
void DocumentScriptEngine::eventParametersChanged()
{
    globalObject().property("EventParametersChanged").call();
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
    }
    return &eventsList;
}
