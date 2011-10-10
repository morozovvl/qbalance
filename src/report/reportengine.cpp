#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include "../gui/app.h"
#include "../kernel/essence.h"
#include "reportengine.h"
#include "reporttemplate.h"
#include "reportcontextfunctions.cpp"

ReportEngine::ReportEngine(Essence* par, QString name) {
    parent = par;
    engine = new QScriptEngine();
    reportName = name;
    scriptFileName = reportName + ".js";
    templateFileName = reportName + ".ods";
}

bool ReportEngine::doOpen() {
    bool lResult = false;
    context = engine->globalObject();
    loadContextFunctions();
    QFile scriptFile(scriptFileName);
    if (scriptFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&scriptFile);
        QString contents = stream.readAll();
        scriptFile.close();
        engine->evaluate(contents, scriptFileName);
    }
    if (!engine->hasUncaughtException()) {                          // Если не было ошибок
        ReportTemplate report(parent, this, templateFileName);
        report.open();
        lResult = true;
    }
    else {
        TApplication::exemplar()->showError(QString(QObject::tr("Ошибка в строке %1 в программе %2")).arg(engine->uncaughtExceptionLineNumber()).arg(scriptFileName));
        lResult = false;
    }
    return lResult;
}

void ReportEngine::loadContextFunctions() {
// Загрузим в контекст отчета функций, определенные в файле reportcontextfunctions.cpp
    context.setProperty("SumToString", engine->newFunction(SumToString));
}


