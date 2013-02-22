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

#ifndef CALENDARFORM_H
#define CALENDARFORM_H

#include <QtGui/QCalendarWidget>
#include "form.h"

class TApplication;

class CalendarForm : public Form {
    Q_OBJECT
public:
//    CalendarForm(QObject* parent = NULL);
//    virtual ~CalendarForm();
    virtual bool open(QWidget* pwgt = 0);
    virtual QDate getBeginDate() { return beginDate; }
    virtual QDate getEndDate() { return endDate; }
    virtual void setBeginDate(QDate);
    virtual void setEndDate(QDate);
private:
    QCalendarWidget* pBeginCalendar;
    QCalendarWidget* pEndCalendar;
    QDate beginDate;
    QDate endDate;
    void cmdOk();
};

#endif // CALENDAR_H
