#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include "../gui/app.h"
#include "../kernel/essence.h"
#include "reportengine.h"
#include "reporttemplate.h"
#include "reportcontextfunctions.cpp"


ReportEngine::ReportEngine(Essence* par, QMap<QString, QVariant>* context, QString name, QString ext)
:QObject()
, parent(NULL)
, scriptEngine(NULL)
{
    parent = par;
    scriptEngine = new ReportScriptEngine();
    printContext = context;
    reportName = name;
    reportExt = ext;
}


bool ReportEngine::open()
{
    bool result = true;
    scriptContext = scriptEngine->globalObject();
    QString scriptFileName = reportName + ".js";
    QFile scriptFile(scriptFileName);
    if (scriptFile.open(QIODevice::ReadOnly))
    {   // Если существуют скрипты к этому файлу, то запустить скрипты
        QTextStream stream(&scriptFile);
        QString contents = stream.readAll();
        scriptFile.close();
        scriptEngine->evaluate(contents, scriptFileName);
        if (scriptEngine->hasUncaughtException())
        {   // Если в скриптах произошла ошибка
            TApplication::exemplar()->showError(QString(QObject::tr("Ошибка в строке %1 в программе %2")).arg(scriptEngine->uncaughtExceptionLineNumber()).arg(scriptFileName));
            result = false;
        }
    }
    if (result)
    {
        openExternEngine();
    }
    return result;
}


void ReportEngine::openExternEngine()
{
    QTemporaryFile file;
    file.setAutoRemove(true);
    file.setFileTemplate("tmp_XXXXXX");
    if (file.open())
    {
        QTextStream out(&file);
        foreach (QString key, printContext->keys()) {
//            out << key << printContext.value(key);
            qDebug() << key << printContext->value(key);
        }
/*
        if (reportExt == "ods")
        {
            QProcess* ooProcess = new QProcess();
            ooProcess->setWorkingDirectory(REPORT_DIR);
            ooProcess->start("soffice -invisible -quickstart", QStringList() << fileName);
            if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning))
            {   // Подождем 1 секунду и если процесс не запустился
                TApplication::exemplar()->showError(QObject::tr("Не удалось запустить") + " Open Office");                   // выдадим сообщение об ошибке
                result = false;
            }
        }
*/
    }
}

