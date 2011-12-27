#include "../kernel/app.h"
#include "ooreportengine.h"

OOReportEngine::OOReportEngine(QMap<QString, QVariant>* context, QString name, QString ext)
:ReportEngine(context, name, ext)
{
}


bool OOReportEngine::open()
{
    bool result = false;
    QTemporaryFile file;
    file.setAutoRemove(false);
    if (file.open())
    {
        // Сохраним контекст печати во временном файле
        QTextStream out(&file);
        foreach (QString key, reportContext->keys())
        {
            QString value = reportContext->value(key).toString();
            if (value.size() > 0)
            {
                out << key.toLower() << ";" << value << endl;
            }
        }
        file.close();
        QTemporaryFile templateFile;
        templateFile.setFileTemplate("qt_temp_XXXXXX." + reportExt);
        templateFile.open();
        QString tmpFileName = QDir().tempPath() + "/" + templateFile.fileName();
        templateFile.close();
        if (QFile().copy(reportName + "." + reportExt, tmpFileName))
        {
            QString command = QString("soffice -invisible -quickstart %1 ""macro://./Standard.Main.Main(%2)""").arg(tmpFileName).arg(file.fileName());
            QProcess* ooProcess = new QProcess();
            ooProcess->start(command);
            if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning))
            {   // Подождем 1 секунду и если процесс не запустился
                TApplication::exemplar()->showError(QObject::trUtf8("Не удалось запустить") + " Open Office");                   // выдадим сообщение об ошибке
            }
            else
            {
                result = true;
            }
        }
        else
        {
            TApplication::exemplar()->showError(QObject::trUtf8("Не удалось скопировать шаблон во временный файл."));
        }
    }
    else {
        TApplication::exemplar()->showError(QObject::trUtf8("Не удалось создать временный файл."));
    }
    return result;
 }

