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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QCalendarWidget>
#else
    #include <QtWidgets/QCalendarWidget>
#endif

#include "form.h"

class TApplication;

class CalendarForm : public Form {
    Q_OBJECT
public:
    CalendarForm(QObject* parent = 0 /*nullptr*/);
    ~CalendarForm();
    virtual bool open(QWidget* pwgt = 0 /*nullptr*/);
    Q_INVOKABLE virtual QDate getBeginDate(int = 0);
    Q_INVOKABLE virtual QDate getEndDate(int = 0);
    Q_INVOKABLE virtual QString getBeginDateString(int = 0);
    Q_INVOKABLE virtual QString getEndDateString(int = 0);
    Q_INVOKABLE virtual void setBeginDate(QDate);
    Q_INVOKABLE virtual void setEndDate(QDate);
public slots:
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();

private:
    QCalendarWidget* pBeginCalendar;
    QCalendarWidget* pEndCalendar;
    QDate beginDate;
    QDate endDate;
    void cmdOk();
};

#endif // CALENDAR_H
