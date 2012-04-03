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

#ifndef OPENRPTPORTENGINE_H
#define OPENRPTPORTENGINE_H
#include <QMap>
#include <QStandardItemModel>
#include "../kernel/essence.h"
#include "reportengine.h"
#include "../../openrpt/openrpt/report/report.h"
#include "../../openrpt/openrpt/report/wrapper.h"
#include "../../openrpt/openrpt/report/templategenerator.h"


class OpenRPTreportEngine : public ReportEngine
{
    Q_OBJECT
public:
    OpenRPTreportEngine(QMap<QString, QVariant>* context, QString name, QString ext);
    virtual bool open();
private:
    QAbstractItemModel*     model;
    IDataSource*            source;
    void prepareData(TReport*);
};

#endif // OPENRPTPORTENGINE_H
