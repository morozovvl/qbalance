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
#include <QtCore/QMap>
#include "../kernel/essence.h"
#include "./kernel/app.h"
#include "reportengine.h"

class OOXMLReportEngine : public ReportEngine
{
    Q_OBJECT
public:
    OOXMLReportEngine(ReportScriptEngine*);
    ~OOXMLReportEngine();
    virtual bool open() { return ReportEngine::open(); }
    virtual bool open(QString name, QMap<QString, QVariant>* context);

private:
    TApplication*               app;
    QString                     templateFileName;
    QMap<QString, QVariant>*    context;
    QDomDocument                doc;
/*
    QList<QString> columns;
    QDomElement rootElement;
    QDomElement tableElement;               // Первая таблица в файле
    Essence* parent;
    ReportEngine* engine;
    bool doOpen();
    QString prepareDefaultDocument(QString fileName);   // Готовит документ по умолчанию: берет пустую копию, разархивирует ее, заполняет данными (через метод writeDefaultDocument()), архивирует, передает в каталог с документами
    bool writeDefaultDocument(QString);                                  // Заполняет распакованный документ в XML формате содержимым отчета
    void writeTableHeader(QDomNode);
    void writeTableBody(QDomNode, int);
    void writeTableEnd(QDomNode);
    void writeCellAnnotation(QDomElement, QString);
    QDomNode findAnnotation(QString);
    void readAvailableColumns();                                        // Читает из шаблона отчета, какие колонки присутствуют в отчете
*/
    bool removeDir(QString);
    void writeVariables();                                              // Заполняет поля с переменными в шаблоне
    void writeCell(QDomElement, QString, QString = "string");
//    void writeTableBody(QDomNode, int);
    bool waitProcessEnd(QProcess *);

};

#endif // OOXMLREPORTENGINE_H
