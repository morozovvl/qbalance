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

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "reportscriptengine.h"
#include "../kernel/app.h"
#include "../kernel/dictionary.h"
#include "reportcontextfunctions.h"


ReportScriptEngine::ReportScriptEngine(QHash<QString, QVariant>* context, Essence *parent/* = 0*/)
:ScriptEngine(parent)
{
    reportContext = new ReportContext(context);
}


ReportScriptEngine::~ReportScriptEngine()
{
    delete reportContext;
}


void ReportScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    // инициализируем глобальные объекты скрипта печати
    globalObject().setProperty("reportContext", newQObject(reportContext));
    globalObject().setProperty("SumToString", newFunction(SumToString));
}
