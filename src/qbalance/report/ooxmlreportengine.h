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

#ifndef OOXMLREPORTENGINE_H
#define OOXMLREPORTENGINE_H
#include <QtCore/QHash>
#include <QtCore/QStringList>
#include <QtXml/QDomNodeList>
#include "reportengine.h"
#include "../kernel/essence.h"


class OOXMLEngine;
class ReportContext;

class OOXMLReportEngine : public ReportEngine
{
    Q_OBJECT
public:
    OOXMLReportEngine(Essence*, DocumentScriptEngine* = 0 /*nullptr*/);
    ~OOXMLReportEngine();
    virtual bool open();
    virtual bool open(QString name, ReportContext* context, bool = false, int = 1, QString = "");
    void         setFileName(QString fName);

private:
    TApplication*               app;
    OOXMLEngine*                ooxmlEngine;
    ReportContext*              context;
    QStringList                 expressionsForEvaluation;
    QStringList                 tablesForPrinting;
    QStringList                 invalidExpressions;
    QDomNodeList                cells;
    QString                     ooPath;
    QString                     tableNameForPrinting;
    QString                     fileName;
    Essence*                    essence;
    QProcess*                   ooProcess;

    void writeVariables(int = 0);                                              // Заполняет поля с переменными в шаблоне
    void writeHeader();
    bool readExpression(int, int = 0);
    QString getTableVariable(QDomElement, QString);
    bool writeCell(QDomNode, QString, QVariant);
    void findTables();
    QString findBarCode();
    void copyPage(int);
};

#endif // OOXMLREPORTENGINE_H
