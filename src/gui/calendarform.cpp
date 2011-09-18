#include "calendarform.h"
#include "../app.h"

bool CalendarForm::open(QWidget* pwgt) {
    if (Form::open(pwgt)) {

        formWidget->move(100, 100);

        formWidget->setWindowTitle(tr("Рабочий период"));

        QLabel* plblBegin = new QLabel(tr("Начало периода"));
        QLabel* plblEnd = new QLabel(tr("Конец периода"));

        pBeginCalendar = new QCalendarWidget();
        pEndCalendar = new QCalendarWidget();

        QGridLayout* ptopLayout = new QGridLayout;
        ptopLayout->addWidget(plblBegin, 0, 0, Qt::AlignCenter);
        ptopLayout->addWidget(plblEnd, 0, 1, Qt::AlignCenter);
        ptopLayout->addWidget(pBeginCalendar, 1, 0, Qt::AlignCenter);
        ptopLayout->addWidget(pEndCalendar, 1, 1, Qt::AlignCenter);

        QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
        if (vbxLayout != 0)
            vbxLayout->insertLayout(0, ptopLayout);
        return true;
    }
    return false;
}

void CalendarForm::cmdOk() {
    beginDate = pBeginCalendar->selectedDate();
    endDate = pEndCalendar->selectedDate();
    if (beginDate > endDate)
        TApplication::exemplar()->getGUIFactory()->showError(tr("Дата конца периода НЕ МОЖЕТ БЫТЬ РАНЬШЕ даты начала периода."));
    else
        Form::cmdOk();
}

void CalendarForm::setBeginDate(QDate date) { 
    beginDate = date; 
    pBeginCalendar->setSelectedDate(date);
}
 
void CalendarForm::setEndDate(QDate date) { 
    endDate = date;
    pEndCalendar->setSelectedDate(date);
}
