#include "reportscripengine.h"


ReportScripEngine::ReportScripEngine(QObject *parent/* = 0*/)
:ScriptEngine(parent)
{
    void ReportEngine::loadContextFunctions() {
    // Загрузим в контекст отчета функций, определенные в файле reportcontextfunctions.cpp
        context.setProperty("SumToString", scriptEngine->newFunction(SumToString));
    }


}
