#ifndef CALENDARFORM_H
#define CALENDARFORM_H

#include "form.h"

class TApplication;

class CalendarForm : public Form {
public:
    bool open(QWidget* pwgt = 0);
    QDate getBeginDate() { return beginDate; }
    QDate getEndDate() { return endDate; }
    void setBeginDate(QDate);
    void setEndDate(QDate);
private:
    QCalendarWidget* pBeginCalendar;
    QCalendarWidget* pEndCalendar;
    QDate beginDate;
    QDate endDate;
    void cmdOk();
};

#endif // CALENDAR_H
