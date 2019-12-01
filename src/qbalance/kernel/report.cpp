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
#include "dictionary.h"
#include "../kernel/app.h"
#include "../kernel/dictionary.h"
#include "../gui/formgrid.h"
#include "../gui/tableview.h"
#include "../gui/mainwindow.h"
#include "../gui/calendarform.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"
#include "report.h"


Report::Report(QString name, QObject* parent): Dictionary(name, parent)
{
}


bool Report::open(QString, QString)
{
    setTagName("оборот60");

    Dictionary* dict = app->getDictionary("организации");
    dict->exec();
    if (dict->isFormSelected())
    {
        CalendarForm* calendar = new CalendarForm();
        calendar->open(app->getMainWindow()->centralWidget());
        calendar->setBeginDate(app->getBeginDate());
        calendar->setEndDate(app->getEndDate());
        calendar->exec();
        if (calendar->isFormSelected())
        {
            if (Essence::open(getReportqlSelectStatement(dict->getId(), calendar->getBeginDate(), calendar->getEndDate())))
            {
                form->setFormTitle("Обороты по счету 60");
                form->getGrdTable()->clearColumnDefinitions();
                form->getGrdTable()->appendColumnDefinition("ДАТА", "Дата", true);
                form->getGrdTable()->appendColumnDefinition("ОПЕРНОМЕР", "№ оп.", true);
                form->getGrdTable()->appendColumnDefinition("ОПЕРИМЯ", "Наименование операции", true);
                form->getGrdTable()->appendColumnDefinition("ДОКУМЕНТ", "Документ", true);
                form->getGrdTable()->appendColumnDefinition("НОМЕР", "№ док.", true);
                form->getGrdTable()->appendColumnDefinition("КОММЕНТАРИЙ", "Комментарий", true);
                form->getGrdTable()->appendColumnDefinition("ДЕБЕТ", "Дебет", true);
                form->getGrdTable()->appendColumnDefinition("КРЕДИТ", "Кредит", true);
                return true;
            }
        }
        delete calendar;
    }
    return false;
}


void Report::preparePrintValues()   // Готовит значения для печати
{
}


QString Report::getReportqlSelectStatement(int orgId, QDate begDate, QDate endDate)
{
    QString command = QString("SELECT ДАТА, ОПЕРНОМЕР, ОПЕРИМЯ, ДОКУМЕНТ, НОМЕР, КОММЕНТАРИЙ, ДЕБЕТ, КРЕДИТ FROM sp_calcobjoborot('60', %1, '%2', '%3')")
            .arg(orgId)
            .arg(begDate.toString(app->dateFormat()))
            .arg(endDate.toString(app->dateFormat()));
    return command;
}


void Report::setForm(QString formName)
{
    form = new FormGrid();

    form->appendToolTip("buttonOk",         trUtf8("Закрыть список документов"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить список документов (загрузить повторно с сервера) (F3)"));

    form->open(parentForm, this, formName);
}


