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

#include <QtCore/QProcess>

#include "oounoreportengine.h"
#include "../kernel/app.h"


OOUNOReportEngine::OOUNOReportEngine(ReportScriptEngine* engine) : ReportEngine(engine)
{
    oo = new OpenOffice();
}


OOUNOReportEngine::~OOUNOReportEngine()
{
    delete oo;
}


bool OOUNOReportEngine::open(){
    return ReportEngine::open();
}


bool OOUNOReportEngine::open(QString name, QMap<QString, QVariant>* context)
{
    if (oo->open(name))
    {
        oo->load(context);
        return true;
    }
    return false;
}


void OOUNOReportEngine::close() {
    oo->close();
}
