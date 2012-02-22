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

#ifndef SQLRECORD_H
#define SQLRECORD_H

#include <QObject>
#include <QScriptable>
#include <QVariant>
#include <QSqlRecord>


class MySqlRecord : public QObject, protected QScriptable
{
    Q_OBJECT
public:
    explicit MySqlRecord(QObject* parent = 0);
    ~MySqlRecord();
    void setRecord(QSqlRecord rec) { *record = rec; }

public slots:
    QVariant value(int index) const { return record->value(index); }
    QVariant value(const QString &name) const { return record->value(name); }
    QString myString() { return "MySqlRecord"; }

private:
    QSqlRecord* record;
};

#endif // SQLRECORD_H
