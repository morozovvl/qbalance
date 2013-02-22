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

#ifndef REPORTCONTEXT_H
#define REPORTCONTEXT_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVariant>

class ReportContext : public QObject
{
    Q_OBJECT
public:
    explicit ReportContext(QMap<QString, QVariant>*, QObject *parent = 0);
    Q_INVOKABLE int count() { return data->count(); }
    Q_INVOKABLE QVariant getValue(QString);
    Q_INVOKABLE void setValue(QString, QVariant);
//    Q_INVOKABLE void sortTable(QString);    // сортировка контекста печати в разделе таблица по заданному полю
private:
    QMap<QString, QVariant>*    data;
};

#endif // REPORTCONTEXT_H
