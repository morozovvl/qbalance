#include <QFile>
#include <QTextStream>
#include "reportscriptengine.h"
#include "../kernel/app.h"
#include "reportcontextfunctions.cpp"


ReportScriptEngine::ReportScriptEngine(QMap<QString, QVariant>* context, QString reportName, QObject *parent/* = 0*/)
:ScriptEngine(reportName, parent)
{
    reportContext = new ReportContext(context);
}

void ReportScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    // инициализируем глобальные объекты скрипта печати
    globalObject().setProperty("reportContext", newQObject(reportContext));
    globalObject().setProperty("SumToString", newFunction(SumToString));
}
