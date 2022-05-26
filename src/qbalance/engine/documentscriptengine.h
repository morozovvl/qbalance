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
#include <QtSql/QSqlRecord>
#include "scriptengine.h"


class Documents;


class DocumentScriptEngine : public ScriptEngine
{
public:
    DocumentScriptEngine(Essence *parent = 0 /*nullptr*/);
    DocumentScriptEngine(QHash<QString, QVariant>*, Essence *parent = 0 /*nullptr*/);
    ~DocumentScriptEngine();
    virtual int eventAppendFromQuery(QString, QSqlRecord*);
    virtual bool eventBeforeLinePrint(int);
    virtual void eventAfterLinePrint(int);
    virtual void eventBeforeTotalPrint();
    virtual QHash<QString, EventFunction>* getEventsList();
    virtual ReportContext* getReportContext();
    virtual void setReportContext(QHash<QString, QVariant>*);

protected:
    virtual void loadScriptObjects();

private:
    ReportContext*  reportContext;
};

#endif // DOCUMENTSCRIPTENGINE_H
