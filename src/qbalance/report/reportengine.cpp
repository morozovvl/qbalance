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
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include "../kernel/app.h"
#include "../kernel/essence.h"
#include "reportengine.h"


ReportEngine::ReportEngine(DocumentScriptEngine* engine) :QObject()
{
    scriptEngine = engine;
    reportContext = nullptr;
}


ReportEngine::~ReportEngine()
{

}


bool ReportEngine::open()
{
    return true;
}


bool ReportEngine::open(QHash<QString, QVariant>* context, QString name, QString ext)
{
    reportContext = context;
    reportName = name;
    reportExt = ext;
    return true;
}
