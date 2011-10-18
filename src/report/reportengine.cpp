#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include "../kernel/app.h"
#include "../kernel/essence.h"
#include "../engine/reportscriptengine.h"
#include "reportengine.h"


ReportEngine::ReportEngine(QMap<QString, QVariant>* context, QString name, QString ext)
:QObject()
{
    reportContext = context;
    reportName = name;
    reportExt = ext;
}
