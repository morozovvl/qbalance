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

#ifndef REPORT_H
#define REPORT_H

#include <QtSql/QSqlQuery>
#include <QtCore/QObject>
#include <QtCore/QDate>
#include "dictionary.h"

class Report : public Dictionary {
    Q_OBJECT

private:
    QString     selectStatement;
    QString     account;
    Dictionary* dict;
    QDate       beginDate;
    QDate       endDate;
    bool        dictEnabled;

protected:
    Report(QString = "", QObject* parent = 0 /*nullptr*/);

public:
    template <class T>
        static T* create(QString name = "", QObject* parent = 0 /*nullptr*/)
        {
            T* p(new T(name, parent));
            p->postInitialize(name, parent);
            return p;
        }

    virtual bool open(QDate, QDate, QString = "", QString = "");
    virtual void close();

    virtual void preparePrintValues();                   // Готовит значения для печати


    QString getReportSqlSelectStatement(int, QDate, QDate);     // Генерирует текст SQL-запроса для табличной части отчета
};

#endif // REPORT_H
