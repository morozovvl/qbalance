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


class OOXMLEngine;
class ReportContext;

class OOXMLReportEngine : public ReportEngine
{
    Q_OBJECT
public:
    OOXMLReportEngine(DocumentScriptEngine* = 0);
    ~OOXMLReportEngine();
    virtual bool open();
    virtual bool open(QString name, ReportContext* context);
    void         setFileName(QString fName);

private:
    OOXMLEngine*                ooxmlEngine;
    ReportContext*              context;
    QStringList                 expressionsForEvaluation;
    QStringList                 tablesForPrinting;
    QStringList                 invalidExpressions;
    QDomNodeList                cells;
    QString                     ooPath;
    QString                     tableNameForPrinting;
    QString                     fileName;

    void writeVariables();                                              // Заполняет поля с переменными в шаблоне
    void writeHeader();
    bool readExpression(int, int);
    QString getTableVariable(QDomElement, QString);
    bool writeCell(QDomNode, QString, QVariant);
    void findTables();
};

#endif // OOXMLREPORTENGINE_H
