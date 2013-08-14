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
#include <QtCore/QFileInfo>
#include <QtCore/QTemporaryFile>
#include <QtCore/QTimer>
#include <QDebug>
#include "ooxmlreportengine.h"


OOXMLReportEngine::OOXMLReportEngine(ReportScriptEngine* engine) : ReportEngine(engine)
{
    app = TApplication::exemplar();
}


OOXMLReportEngine::~OOXMLReportEngine()
{
}


bool OOXMLReportEngine::open(QString fileName, QMap<QString, QVariant>* cont)
{
    templateFileName = fileName;
    context = cont;
    // Создадим временный каталог
    QString tmpDir = fileName + ".tmp";
    if (QDir().mkdir(tmpDir))
    {
        // Распакуем файл OpenOffice
        QProcess* unzip = new QProcess();
        unzip->setWorkingDirectory(tmpDir);
#ifdef Q_OS_WIN32
        unzip->start(app->applicationDirPath() + "/unzip", QStringList() << fileName);
#else
        unzip->start("unzip", QStringList() << fileName);
#endif
        if (waitProcessEnd(unzip)) {

            // Запишем контент в файл
            QFile file(tmpDir + "/content.xml");
            if (file.open(QIODevice::ReadOnly))
            {
                if (doc.setContent(&file))
                {
                    file.close();

                    writeVariables();

                    if (file.open(QIODevice::WriteOnly))
                    {
                        QTextStream stream(&file);
                        doc.save(stream, 5);
                    }
                }
                file.close();
            }

            // Запакуем файл OpenOffice обратно
            QProcess* zip = new QProcess();
            zip->setWorkingDirectory(tmpDir);
#ifdef Q_OS_WIN32
            zip->start(app->applicationDirPath() + "/zip", QStringList() << "-r" << fileName << ".");
#else
            zip->start("zip", QStringList() << "-r" << fileName << ".");
#endif
            if (waitProcessEnd(zip)) {

                // удалим временный каталог
                removeDir(tmpDir);

                QProcess* ooProcess = new QProcess();
                ooProcess->start("soffice", QStringList() << "--invisible" << "--quickstart" << fileName);
                if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning))    // Подождем 1 секунду и если процесс не запустился
                    app->showError(QObject::trUtf8("Не удалось запустить") + " Open Office");                  // выдадим сообщение об ошибке
                else
                    return true;
            }
            else
                app->showError(QObject::trUtf8("Не удалось запустить программу") + " zip");
        }
        else
            app->showError(QObject::trUtf8("Не удалось запустить программу") + " unzip");
    }
    return false;
}


bool OOXMLReportEngine::waitProcessEnd(QProcess* proc)
{   // Процедура ждет окончания процесса или истечения 30 секунд
    bool result = true;
    QTimer t;
    t.start(30000);
    QEventLoop loop;
    connect(&t, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), &loop, SLOT(quit()));
    loop.exec();
    if (proc->exitStatus() != QProcess::NormalExit)
        result = false;
    delete proc;
    return result;
}


bool OOXMLReportEngine::removeDir(QString dirName)
{
    bool result = false;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
                                                    QDir::System |
                                                    QDir::Hidden  |
                                                    QDir::AllDirs |
                                                    QDir::Files,
                                                    QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}


void OOXMLReportEngine::writeVariables() {
    QDomNodeList cells = doc.elementsByTagName("text:p");
    QRegExp rx("\\[.+\\]");
    QString type;
    QStringList expressionsForEvaluation;

    // Сначала вставим табличные переменные
    QDomNode firstRowNode;
    for (int i = 0; i < cells.count() && firstRowNode.isNull(); i++)
    {
        QString cellText = cells.at(i).toElement().text().trimmed();
        int fpos = 0;
        int lpos = 0;
        while (true)
        {
            fpos = cellText.indexOf(rx, lpos);
            if (fpos >= 0)
            {
                lpos = cellText.indexOf("]", fpos) + 1;
                QString svar = cellText.mid(fpos, lpos - fpos);
                QString dvar = QString(svar).remove("[").remove("]");
                if (dvar.left(7).toLower() == "таблица")
                {
                    firstRowNode = cells.at(i).parentNode().parentNode();
                    break;
                }
            }
            else
                break;
        }
    }
    if (!firstRowNode.isNull())
    {
        // Найдена табличная часть
        QDomNode lastNode = firstRowNode;
        bool valFound = true;
        for (int strNum = 1; true && valFound; strNum++)
        {
            QDomNode clone = firstRowNode.cloneNode(true);

            cells = clone.toElement().elementsByTagName("text:p");
            for (int i = 0; i < cells.count() && valFound; i++)
            {
                QString cellText = cells.at(i).toElement().text().trimmed();
                bool error = false;
                bool replacement = false;
                int fpos = 0;
                int lpos = 0;
                type = "string";
                while (true)
                {
                    fpos = cellText.indexOf(rx, lpos);
                    if (fpos >= 0)
                    {
                        lpos = cellText.indexOf("]", fpos) + 1;
                        QString svar = cellText.mid(fpos, lpos - fpos);
                        QString dvar = QString(svar).remove("[").remove("]");
                        if (dvar.left(7).toLower() == "таблица")
                        {
                            QVariant var;
                            QString value = QString(dvar.toLower()).replace("таблица", QString("таблица%1").arg(strNum));
                            if (context->contains(value))
                            {
                                var = context->value(value);

                                if (!var.isNull())                          // Если не было ошибок
                                {
                                    QString valueString;
                                    if ((var.type() == QVariant::Double) ||
                                        (var.type() == QVariant::Int) ||
                                        (var.type() == QVariant::UInt))
                                    {
                                        valueString = QString("%1").arg(var.toDouble());
                                        if (svar == cellText)
                                            type = "float";
                                    }
                                    else
                                    {
                                        if (var.type() == QVariant::DateTime)
                                            valueString = var.toDateTime().toString("dd.MM.yyyy hh:mm:ss");
                                        else
                                            valueString = var.toString().trimmed();
                                    }
                                    cellText.replace(svar, valueString);
                                    if (cellText != valueString)                    // Результат не равен исходному выражению
                                        expressionsForEvaluation.append(cellText);  // Позднее пропустим выражение через скриптовый движок
                                    replacement = true;
                                }
                                else
                                {
                                    if (strNum == 1)
                                        app->showError(QString(QObject::trUtf8("Неизвестное выражение %1")).arg(dvar));
                                    error = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                        break;
                }
                if (!error && replacement)
                {
                    writeCell(cells.at(i).parentNode().toElement(), cellText, type);
                }
                else
                {
                    valFound = false;           // Очередное значение переменной не найдено, выйдем из заполнения таблицы
                }
            }
            if (valFound)
                lastNode = firstRowNode.parentNode().insertAfter(clone, lastNode);
        }
        firstRowNode.parentNode().removeChild(firstRowNode);
    }

    // Теперь вставим все оставшиеся переменные
    int counter;
    do {
        counter = 0;
        cells =  doc.elementsByTagName("text:p");
        for (int i = 0; i < cells.count(); i++)
        {
            QString cellText = cells.at(i).toElement().text().trimmed();
            bool error = false;
            bool replacement = false;
            int fpos = 0;
            int lpos = 0;
            type = "string";
            while (true)
            {
                fpos = cellText.indexOf(rx, lpos);
                if (fpos >= 0)
                {
                    lpos = cellText.indexOf("]", fpos) + 1;
                    QString svar = cellText.mid(fpos, lpos - fpos);
                    QString dvar = QString(svar).remove("[").remove("]");

                    QVariant var;
                    QString value;
                    if (dvar.left(7).toLower() != "таблица")
                    {
                        value = dvar.toLower();
                    }
                    else
                        value = QString(dvar.toLower()).replace("таблица", "таблица1");

                    if (context->contains(value))
                    {
                        var = context->value(value);

                        if (!var.isNull())                          // Если не было ошибок
                        {
                            QString valueString;
                            if ((var.type() == QVariant::Double) ||
                                (var.type() == QVariant::Int) ||
                                (var.type() == QVariant::UInt))
                            {
                                valueString = QString("%1").arg(var.toDouble());
                                if (svar == cellText)
                                    type = "float";
                            }
                            else
                            {
                                if (var.type() == QVariant::DateTime)
                                    valueString = var.toDateTime().toString("dd.MM.yyyy hh:mm:ss");
                                else
                                {
                                    if (var.type() == QVariant::Date)
                                        valueString = var.toDate().toString("dd.MM.yyyy");
                                    else
                                        valueString = var.toString().trimmed();
                                }
                            }
                            cellText.replace(svar, valueString);
                            if (cellText != valueString)                    // Результат не равен исходному выражению
                                expressionsForEvaluation.append(cellText);  // Позднее пропустим выражение через скриптовый движок
                            replacement = true;
                            counter++;
                        }
                        else
                        {
                            app->showError(QString(QObject::trUtf8("Неизвестное выражение %1")).arg(dvar));
                            error = true;
                            break;
                        }
                    }
                }
                else
                    break;
            }
            if (!error && replacement)
            {
                writeCell(cells.at(i).parentNode().toElement(), cellText, type);
            }
        }
    } while (counter > 0);


    // Теперь пропустим результат через скрипты
    cells =  doc.elementsByTagName("text:p");
    for (int i = 0; i < cells.count(); i++)
    {
        QString cellText = cells.at(i).toElement().text().trimmed();
        if (expressionsForEvaluation.contains(cellText))                    // Если текущее значение находится в списке
        {                                                                   // выражений, которые нужно оценить скриптовым движком
            QVariant var = scriptEngine->evaluate(cellText).toVariant();
            type = "string";
            if (!scriptEngine->hasUncaughtException())                          // Если не было ошибок
            {
                QString valueString;
                if ((var.type() == QVariant::Double) ||
                    (var.type() == QVariant::Int) ||
                    (var.type() == QVariant::UInt))
                {
                    valueString = QString("%1").arg(var.toDouble());
                    type = "float";
                }
                else
                    valueString = var.toString().trimmed();

                writeCell(cells.at(i).parentNode().toElement(), valueString, type);
            }
        }
    }
}


void OOXMLReportEngine::writeCell(QDomElement node, QString value, QString type) {
    // Заполним ячейку
    if (node.tagName() != "table:table-cell")                  // Установим тег ячейки
        node.setTagName("table:table-cell");
    node.setAttribute("office:value-type", type);               // Установим атрибут с типом значения ячейки
    node.setAttribute("office:value", value);
    QDomElement textElement = node.firstChildElement("text:p");
    if (!textElement.isNull())
        node.removeChild(textElement);
    QDomElement element = doc.createElement("text:p");
    QDomText text = doc.createTextNode(value);
    element.appendChild(text);
    node.appendChild(element);
}


