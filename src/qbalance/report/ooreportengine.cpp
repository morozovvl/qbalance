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

#include <QtCore/QTemporaryFile>
#include "../kernel/app.h"
#include "ooreportengine.h"

OOReportEngine::OOReportEngine(DocumentScriptEngine* engine) : ReportEngine(engine)
{
}


OOReportEngine::~OOReportEngine()
{
}


bool OOReportEngine::open(QHash<QString, QVariant>* context, QString name, QString ext)
{
    bool result = false;
    if (ReportEngine::open(context, name, ext))
    {
        QTemporaryFile file;
        file.setAutoRemove(false);
        if (file.open())
        {
            // Сохраним контекст печати во временном файле
            QTextStream out(&file);
            foreach (QString key, reportContext->keys())
            {
                if (!reportContext->value(key).isNull())
                {
                    QString value;
                    if (reportContext->value(key).type() == QVariant::Double)
                    {
                        value = QString("%1").arg(reportContext->value(key).toDouble());
                        value.replace(".", ",");        // В числовых значениях заменим точку на запятую, т.к. OpenOffice не правильно воспринимает точку (а может я чего не понимаю)
                    }
                    else
                        value = reportContext->value(key).toString();
                    out << "[" << key.toLower() << "]" << ";" << value << endl;
                }
            }
            file.close();
            QTemporaryFile templateFile;
            templateFile.setFileTemplate("qt_temp_XXXXXX." + reportExt);
            templateFile.open();
            QString tmpFileName = QDir().tempPath() + templateFile.fileName();
            templateFile.close();
            QString destFile = reportName + "." + reportExt;
            if (!QDir().exists(destFile))
                QFile().copy(QDir::currentPath() + "/reports/default_report." + reportExt, destFile);
            if (QFile().copy(destFile, tmpFileName))
            {
                if (TApplication::exemplar()->runProcess(QString("soffice -invisible -quickstart %1 ""macro://./Standard.Main.Main(%2)""").arg(tmpFileName).arg(file.fileName()), "OpenOffice") != 0 /*nullptr*/)
                    result = true;
            }
            else
            {
                TApplication::exemplar()->showError(QObject::trUtf8("Не удалось скопировать шаблон во временный файл."));
            }
        }
        else {
            TApplication::exemplar()->showError(QObject::trUtf8("Не удалось создать временный файл."));
        }
    }
    return result;
 }


bool OOReportEngine::open()
{
    return ReportEngine::open();
}

