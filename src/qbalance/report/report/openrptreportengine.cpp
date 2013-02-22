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

#include "../kernel/app.h"
#include "openrptreportengine.h"


OpenRPTreportEngine::OpenRPTreportEngine(QMap<QString, QVariant>* context, QString name, QString ext)
:ReportEngine(context, name, ext)
{
    model = new QStandardItemModel(this);
}


bool OpenRPTreportEngine::open()
{
    TReport report;

    prepareData(&report);

    source = TWrapper::wrap((QAbstractItemModel*)model);

    QDomDocument doc;
    QString fileName = reportName + "." + reportExt;
    QFile file(fileName);
    if (!file.exists())         // Если файл с шаблоном не существует
    {                           // то создадим черновой шаблон
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            TTemplateGenerator generator;
            generator.setDataSource(source);
            doc = generator.process();
            doc.save(stream, 2);
        }
    }
    else
    {
        if (file.open(QIODevice::ReadOnly))
        {
            doc.setContent(&file);
        }

    }
    file.close();

    report.setReport(doc);
    report.preview();

    return true;
}


void OpenRPTreportEngine::prepareData(TReport* report)
{
    QString tablePrefix = "таблица1.";

    // Соберем список заголовков, которые встречаются в таблице в контексте печати
    QStringList headers;
    foreach (QString key, reportContext->keys())
    {
        if (key.left(tablePrefix.size()) == tablePrefix)
        {
            QString fieldHeader = key.remove(0, tablePrefix.size());
            if (!headers.contains(fieldHeader))
                headers.append(fieldHeader);
        }
    }

    // Создадим столько же столбцов
    for (int i = 0; i < headers.count(); i++)
    {
        QString columnName = headers.at(i);
        model->insertColumn(i);
        model->setHeaderData(i, Qt::Horizontal, columnName);
    }

    // Заполним модель данными
    int row = 1;
    bool done = false;
    while (!done)
    {
        for (int i = 0; i < headers.count(); i++)
        {
            QString fieldName = QString("таблица%1.%2").arg(row).arg(headers.at(i));
            if (reportContext->contains(fieldName))
            {                   // Если данные в контексте печати еще есть
                if (model->rowCount() < row)
                    model->insertRows(model->rowCount(), 1);    // добавим в модель строку в конце
                model->setData(model->index(row - 1, i), reportContext->value(fieldName).toString());
            }
            else
            {
                done = true;    // Искомые данные отсутствуют, похоже. что мы все сделали
                break;          // выходим из цикла
            }
        }
        row++;
    }
    report->setDataSource("таблица", source);
}

