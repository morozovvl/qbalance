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

#ifndef DOCUMENTSCRIPTENGINE_H
#define DOCUMENTSCRIPTENGINE_H

#include <QtScript/QScriptValue>
#include "scriptengine.h"
#include "reportcontext.h"


class Documents;


class DocumentScriptEngine : public ScriptEngine
{
public:
    DocumentScriptEngine(Essence *parent = 0);
    DocumentScriptEngine(QHash<QString, QVariant>*, Essence *parent = 0);
    void eventAppendFromQuery(QString, QSqlRecord*);
    void eventBeforeLinePrint(int);
    void eventAfterLinePrint(int);
    void eventBeforeTotalPrint();
    virtual QHash<QString, EventFunction>* getEventsList();
    ReportContext* getReportContext() { return reportContext; }

protected:
    virtual void loadScriptObjects();

private:
    ReportContext*  reportContext;
};

#endif // DOCUMENTSCRIPTENGINE_H
