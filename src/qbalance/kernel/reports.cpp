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

#include <QtCore/QString>
#include "reports.h"
#include "../kernel/app.h"
#include "../kernel/documents.h"
#include "../kernel/report.h"
#include "../gui/formgridsearch.h"
#include "../gui/wizardoperation.h"
#include "../gui/mainwindow.h"
#include "../gui/dialog.h"
#include "../gui/tableview.h"
#include "../storage/dbfactory.h"


Reports::Reports(QObject *parent): Dictionary("", parent)
{
    menuMode = true;
    calendar = new CalendarForm();
}


Reports::~Reports()
{
    delete calendar;
}


void Reports::postInitialize(QObject* parent)
{
    Dictionary::postInitialize("доступ_к_оборотам", parent);

    lPrintable = false;
    formTitle = QObject::trUtf8("Отчеты");
    scriptEngineEnabled = false;

    calendar->open(app->getMainWindow()->centralWidget());
    calendar->setBeginDate(app->getBeginDate());
    calendar->setEndDate(app->getEndDate());
}


void Reports::cmdOk()
{
    Dictionary::cmdOk();
    calendar->exec();
    if (calendar->isFormSelected())
    {
        Report* rep = Report::create<Report>();
        if (rep->open(calendar->getBeginDate(), calendar->getEndDate(), getValue("СЧЕТ").toString().trimmed()))
        {
            rep->query();
            rep->exec();
        }
        rep->close();
        delete rep;
    }
}


void Reports::show()
{
    Dictionary::show();
    grdTable->cmdRequery();
}


void Reports::setForm(QString)
{
    if (form != 0 /*nullptr*/)
    {
        form->close();
        delete form;
    }

    form = new FormGridSearch();

    form->appendToolTip("buttonOk", trUtf8("Открыть отчет"));

    form->open(parentForm, this, getTagName());
}


