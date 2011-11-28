#include "documentscriptengine.h"
#include "../kernel/document.h"


DocumentScriptEngine::DocumentScriptEngine(QObject *parent/* = 0*/)
:ScriptEngine(parent)
{
}


void DocumentScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    globalObject().setProperty("table", newQObject(parent()));
    globalObject().setProperty("documents", newQObject(parent()->parent()));
}


