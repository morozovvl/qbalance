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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QLabel>
#else
    #include <QtWidgets/QLabel>
#endif

#include "calendarform.h"
#include "../kernel/app.h"
#include "../gui/dialog.h"



CalendarForm::CalendarForm(QObject* parent): Form(parent)
{
    configName = "calendar";
}


CalendarForm::~CalendarForm()
{
}


QDate CalendarForm::getBeginDate(int diff)
{
    return beginDate.addDays(diff);
}


QDate CalendarForm::getEndDate(int diff)
{
    return endDate.addDays(diff);
}


QString CalendarForm::getBeginDateString(int diff)
{
    return getBeginDate(diff).toString(app->dateFormat());
}


QString CalendarForm::getEndDateString(int diff)
{
    return getEndDate(diff).toString(app->dateFormat());
}


bool CalendarForm::open(QWidget* pwgt) {
    if (Form::open(pwgt))
    {
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

        QVBoxLayout* vbxLayout = static_cast<QVBoxLayout*>(formWidget->findChild("vbxLayout"));
        if (vbxLayout != 0 /*nullptr*/)
            vbxLayout->insertLayout(0, ptopLayout);
        app->setIcons(formWidget);
        formWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        return true;
    }
    return false;
}


int CalendarForm::exec()
{
    return Form::exec();
}


void CalendarForm::show()
{
    Form::show();
}


void CalendarForm::cmdOk() {
    Form::hide();
    beginDate = pBeginCalendar->selectedDate();
    endDate = pEndCalendar->selectedDate();
    if (beginDate > endDate)
        TApplication::exemplar()->showError(QObject::trUtf8("Дата конца периода НЕ МОЖЕТ БЫТЬ РАНЬШЕ даты начала периода."));
    else
    {
        Form::cmdOk();
    }
}

void CalendarForm::setBeginDate(QDate date) {
    beginDate = date; 
    pBeginCalendar->setSelectedDate(date);
}
 
void CalendarForm::setEndDate(QDate date) {
    endDate = date;
    pEndCalendar->setSelectedDate(date);
}
