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

#include <QtGui/QLabel>
#include "calendarform.h"
#include "../kernel/app.h"



//CalendarForm::CalendarForm(QObject* parent/* = NULL*/): Form(parent)
//{
//}


//CalendarForm::~CalendarForm()
//{
//}


bool CalendarForm::open(QWidget* pwgt) {
    if (Form::open(pwgt)) {

        formWidget->move(100, 100);

        formWidget->setWindowTitle(QObject::trUtf8("Рабочий период"));

        QLabel* plblBegin = new QLabel(QObject::trUtf8("Начало периода"));
        QLabel* plblEnd = new QLabel(QObject::trUtf8("Конец периода"));

        pBeginCalendar = new QCalendarWidget();
        pEndCalendar = new QCalendarWidget();

        QGridLayout* ptopLayout = new QGridLayout();
        ptopLayout->addWidget(plblBegin, 0, 0, Qt::AlignCenter);
        ptopLayout->addWidget(plblEnd, 0, 1, Qt::AlignCenter);
        ptopLayout->addWidget(pBeginCalendar, 1, 0, Qt::AlignCenter);
        ptopLayout->addWidget(pEndCalendar, 1, 1, Qt::AlignCenter);

        QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
        if (vbxLayout != 0)
            vbxLayout->insertLayout(0, ptopLayout);
        app->setIcons(formWidget);
        return true;
    }
    return false;
}

void CalendarForm::cmdOk() {
    beginDate = pBeginCalendar->selectedDate();
    endDate = pEndCalendar->selectedDate();
    if (beginDate > endDate)
        TApplication::exemplar()->getGUIFactory()->showError(QObject::trUtf8("Дата конца периода НЕ МОЖЕТ БЫТЬ РАНЬШЕ даты начала периода."));
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
