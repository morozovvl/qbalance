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
#include "../engine/documentscriptengine.h"
#include "../engine/reportcontext.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"
#include "report.h"


Report::Report(QString name, QObject* parent): Dictionary(name, parent)
{
    dict = nullptr;
}


bool Report::open(QDate bDate, QDate eDate, QString acc, QString)
{
    bool result = false;
    account = acc;
    setTagName("оборот" + account);

    dict = app->getDictionary(db->getAccountsValue(account, "ИМЯСПРАВОЧНИКА").toString());

    if (dict != nullptr)
    {
        dictEnabled = dict->isEnabled();
        dict->setEnabled(false);
        dict->exec();
        if (dict->isFormSelected())
        {
            beginDate = bDate;
            endDate = eDate;
            if (Dictionary::open(getReportqlSelectStatement(dict->getId(), beginDate, endDate)))
            {
                form->setFormTitle(QString("Обороты по счету %1 - %2").arg(account).arg(dict->getName()));

                TableView* table = form->getGrdTable();
                table->setHideZero();
                table->clearColumnDefinitions();
                table->appendColumnDefinition("ДАТА", "Дата");
                table->appendColumnDefinition("ОПЕРНОМЕР", "№ оп.");
                table->appendColumnDefinition("ОПЕРИМЯ", "Наименование операции");
                table->appendColumnDefinition("ДОКУМЕНТ", "Документ");
                table->appendColumnDefinition("НОМЕР", "№ док.");
                table->appendColumnDefinition("КОММЕНТАРИЙ", "Комментарий");
                table->appendColumnDefinition("ДЕБЕТ", "Дебет", true, 10, 2);
                table->appendColumnDefinition("КРЕДИТ", "Кредит", true, 10, 2);

                if (form->getButtonView() != nullptr)
                    form->getButtonView()->setVisible(true);

                result = true;
            }
        }
    }
    return result;
}


void Report::close()
{
    if (dict != nullptr)
        dict->setEnabled(dictEnabled);

    Dictionary::close();
}


void Report::preparePrintValues()   // Готовит значения для печати
{
    Dictionary::preparePrintValues();

    foreach(QString field, dict->getFieldsList())
    {
        if (field.left(4) != idFieldName)       // Если поле не является ссылкой на другой справочник
            reportScriptEngine->getReportContext()->setValue(QString("%1.%2")
                                                             .arg(dict->getTableName())
                                                             .arg(field).toLower(),
                                                             dict->getValue(field));
    }

    reportScriptEngine->getReportContext()->setValue("НачалоПериода", beginDate.toString(app->dateFormat()));
    reportScriptEngine->getReportContext()->setValue("КонецПериода", endDate.toString(app->dateFormat()));
}


QString Report::getReportqlSelectStatement(int id, QDate begDate, QDate endDate)
{
    QString command = db->getCalcObjOborotCommand(account, id, begDate, endDate);
    command = QString("SELECT ДАТА, ОПЕРНОМЕР, ОПЕРИМЯ, ДОКУМЕНТ, НОМЕР, КОММЕНТАРИЙ, ДЕБЕТ, КРЕДИТ FROM (%1) s").arg(command);
    return command;
}

