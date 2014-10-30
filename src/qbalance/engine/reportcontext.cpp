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

#include "reportcontext.h"


ReportContext::ReportContext(QHash<QString, QVariant>* d, QObject *parent/* = 0*/) :
    QObject(parent)
{
    data = d;
}


QVariant ReportContext::getValue(QString tag)
{
    return data->value(tag);
}


void ReportContext::setValue(QString tag, QVariant val)
{
    if (data->contains(tag))
    {
        data->remove(tag);
    }
    data->insert(tag, val);
}
