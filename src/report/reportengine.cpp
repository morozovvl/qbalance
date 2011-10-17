#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include "../kernel/app.h"
#include "../kernel/essence.h"
#include "../engine/reportscriptengine.h"
#include "reportengine.h"
#include "reportcontextfunctions.cpp"


ReportEngine::ReportEngine(Essence* par, QMap<QString, QVariant>* context, QString name, QString ext)
:QObject()
, parent(NULL)
{
    parent = par;
    printContext = context;
    reportName = name;
    reportExt = ext;
}
