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
#include "topers.h"
#include "../kernel/app.h"
#include "../kernel/documents.h"
#include "../gui/formgridsearch.h"
#include "../gui/wizardoperation.h"
#include "../gui/mainwindow.h"
#include "../gui/dialog.h"
#include "../storage/dbfactory.h"


Topers::Topers(QObject *parent): Dictionary("", parent) {
}


Topers::~Topers()
{
}


void Topers::postInitialize(QObject* parent)
{
    Dictionary::postInitialize("доступ_к_топер", parent);

    lPrintable = false;
    lInsertable = TApplication::exemplar()->isSA();     // Если работает пользователь SA, то можно добавить операцию
    lViewable = TApplication::exemplar()->isSA();       // Если работает пользователь SA, то можно просмотреть свойства операции
    lDeleteable = TApplication::exemplar()->isSA();       // Если работает пользователь SA, то можно попытаться удалить операцию
    formTitle = QObject::trUtf8("Операции");
    scriptEngineEnabled = false;
}

void Topers::cmdOk()
{
    addDocument(getValue("опер").toInt());
}


void Topers::addDocument(int opNumber)
{
    if (opNumber > 0) {
        Documents* doc = TApplication::exemplar()->getDocuments(opNumber);
        if (doc != 0) {
            doc->show();
        }
    }
}


void Topers::removeDocument(int opNumber)
{
    if (opNumber > 0) {
        TApplication::exemplar()->removeDocuments(opNumber);
    }
}


bool Topers::add()
{
    bool result = false;
    WizardOperation* wizard = new WizardOperation();
    wizard->open(TApplication::exemplar()->getMainWindow());
    wizard->getFormWidget()->setWindowTitle(QObject::trUtf8("Новая операция"));
    wizard->exec();
    wizard->close();
    if (wizard->getResult())
    {   // Если удалось создать операцию, то обновим список операций
        result = true;
    }
    delete wizard;
    return result;
}


void Topers::view()
{
    int operNumber = getValue("опер").toInt();
    WizardOperation* wizard = new WizardOperation();
    wizard->open(TApplication::exemplar()->getMainWindow(), operNumber);
    wizard->getFormWidget()->setWindowTitle(QObject::trUtf8("Свойства операции"));
    wizard->exec();
    wizard->close();
    if (wizard->getResult())
    {
        removeDocument(operNumber);
    }
    delete wizard;
}


void Topers::show()
{
    query();
    Dictionary::show();
}


void Topers::setForm(QString)
{
    if (form != 0)
    {
        form->close();
        delete form;
    }

    form = new FormGridSearch();

    form->appendToolTip("buttonOk",         trUtf8("Открыть список документов"));
    form->appendToolTip("buttonCancel",     trUtf8("Закрыть список типовых операций"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новую типовую операцию"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить типовую операцию"));
    form->appendToolTip("buttonView",       trUtf8("Свойства типовой операции"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить список типовых операций (загрузить повторно с сервера)"));

    form->open(parentForm, this, getTagName());
}


bool Topers::remove()
{
    int operNumber = getValue("опер").toInt();
    if (db->deleteAllToperInfo(operNumber))
    {   // если удалось удалить типовую операцию
        return true;
    }
    return false;
}


void Topers::setOrderClause(QString)
{
    Table::setOrderClause(db->getObjectNameCom("доступ_к_топер.имя"));
}


