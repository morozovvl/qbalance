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
#include <QDebug>
#include "dictionaries.h"
#include "../kernel/app.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/wizarddictionary.h"
#include "../gui/tableview.h"


Dictionaries::Dictionaries(QObject *parent): Dictionary("доступ_к_справочникам", parent)
{
    lInsertable = app->isSA();     // Если работает пользователь SA, то можно добавить новый справочник
    lViewable = app->isSA();       // Если работает пользователь SA, то можно просмотреть свойства справочника
    lDeleteable = app->isSA();       // Если работает пользователь SA, то можно попытаться удалить справочник
    lUpdateable = false;
    lPrintable = false;
    document = 0;
    lIsSaldoExist = false;
    formTitle = QObject::trUtf8("Справочники");
    scriptEngine = 0;
    scriptEngineEnabled = false;
}


Dictionary* Dictionaries::getDictionary(QString dictName)
{
    dictName = dictName.trimmed().toLower();
    if (dictName.size() == 0)
        return 0;
    if (!dictionariesList.contains(dictName))
    {             // Если справочник с таким именем не существует, то попробуем его создать
        if (!addDictionary(dictName))
            return 0;
    }
    return dictionariesList.value(dictName);
}


Saldo* Dictionaries::getSaldo(QString acc)
{
    if (acc.size() == 0)
        return 0;
    QString alias = "saldo" + acc;
    if (!dictionariesList.contains(alias))
    {             // Если справочник с таким именем не существует, то попробуем его создать
        if (!addSaldo(acc))
            return 0;
    }
    lIsSaldoExist = true;
    return (Saldo*)dictionariesList[alias];
}


bool Dictionaries::addDictionary(QString dictName)
{
    dictName = dictName.trimmed().toLower();
    if (dictName.size() == 0)
        return false;
    if (!dictionariesList.contains(dictName))
    {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict;
        dict = new Dictionary(dictName, this);
        dict->setDictionaries(this);
        dict->setPhotoEnabled(true);

        if (dict->open()) {
            dictionariesList.insert(dictName, dict);
            dictionariesNamesList.append(dictName);
            dict->setDictionaries(this);

            // Установим прототипы справочников
            QSqlQuery* dicts = db->getDictionaries();
            if (dicts->first())
            {
                QString fieldName = db->getObjectName("справочники.имя");
                do
                {
                    if (dicts->record().value(fieldName).toString() == dictName)
                    {
                        QString prototype = dicts->record().value(db->getObjectName("справочники.прототип")).toString();
                        if (prototype.size() > 0)
                            dict->setPrototypeName(prototype);
                        else
                            dict->setPrototypeName(dictName);
                        break;
                    }
                } while (dicts->next());
            }

            // Установим "родителей" локальных справочников
            foreach(QString dictName, dictionariesList.keys())
            {
                Dictionary* dict = getDictionary(dictName);
                if (dict->isSet() && !dict->isSaldo())
                {
                    foreach (QString dictName, dict->getChildDicts())
                    {
                        Dictionary* childDict = getDictionary(dictName);
                        if (childDict != 0)
                            childDict->setParentDict(dict);
                    }
                }
            }

            return true;
        }
    }
    return false;
}


bool Dictionaries::addSaldo(QString acc)
{
    if (acc.size() == 0)
        return false;
    QString alias = "saldo" + acc;
    if (!dictionariesList.contains(alias))
    {
        dictionariesNamesList.append(alias);
        // Имя справочника, который используется в бухгалтерском счете acc возьмем из справочника "Счета"
        Dictionary* accDict = app->getDictionaries()->getDictionary(db->getObjectName("счета"));
        accDict->query(QString("%1='%2'").arg(db->getObjectNameCom("счета.счет")).arg(acc));
        QString dictName = accDict->getValue(db->getObjectName("счета.имясправочника")).toString().trimmed().toLower();
        Saldo* saldo = new Saldo(acc, dictName);
        saldo->setDictionaries(this);
//        if (document != 0)                         // Была команда выключить скрипты
//            saldo->setScriptEngineEnabled(false);
        if (saldo->open()) {
            saldo->getFormWidget()->setWindowTitle(QString(QObject::trUtf8("Остаток на счете %1")).arg(acc));
            dictionariesList.insert(alias, saldo);
            saldo->setPhotoEnabled(true);
            saldo->setQuan(true);
//            addDictionary(dictName);
            return true;
        }
    }
    return false;
}


void Dictionaries::removeDictionary(QString dictName)
{
    if (dictName.size() == 0)
        return;
    if (dictionariesList.contains(dictName))
    {             // Если справочник с таким именем не существует, то попробуем его создать
        Dictionary* dict = getDictionary(dictName);
        if (!dict->isSaldo())
        {
            dict->close();
            delete dict;
        }
        else
        {
            Saldo* sal = (Saldo*)dict;
            sal->close();
        }
        dictionariesList.remove(dictName);
        dictionariesNamesList.removeAt(dictionariesNamesList.indexOf(dictName));
    }
}


QString Dictionaries::getDictionaryTitle(QString dictName) {
    return db->getDictionariesProperties(dictName).value(db->getObjectName("доступ_к_справочникам.имя")).toString().trimmed();
}


bool Dictionaries::add()
{
    bool result = false;
    WizardDictionary wizard(true);
    wizard.open(app->getMainWindow());
    wizard.getFormWidget()->setWindowTitle(QObject::trUtf8("Новый справочник"));
    wizard.exec();
    wizard.close();
    if (wizard.getResult())
    {   // Если удалось создать справочник, то обновим список справочников
        query();
        result = true;
    }
    return result;
}


void Dictionaries::view()
{
    QString dictName = getValue(db->getObjectName("доступ_к_справочникам.справочник")).toString().trimmed();
    WizardDictionary wizard;
    wizard.open(app->getMainWindow(), dictName);
    wizard.getFormWidget()->setWindowTitle(QObject::trUtf8("Свойства справочника"));
    wizard.exec();
    wizard.close();
    if (wizard.getResult())
    {
        removeDictionary(dictName);
    }
}


void Dictionaries::show()
{
    Dictionary::show();
}


bool Dictionaries::remove(bool noAsk)
{
    if (Essence::remove(noAsk))
    {
        if (db->removeDictionary(getValue(db->getObjectName("доступ_к_справочникам.справочник")).toString().trimmed()))
        {   // если удалось удалить справочник, то обновим список справочников
            query();
            return true;
        }
    }
    return false;
}


bool Dictionaries::open()
{
    if (Dictionary::open())
    {
        return true;
    }
    return false;
}


void Dictionaries::close()
{
    foreach(QString dictName, dictionariesList.keys())
    {
        removeDictionary(dictName);
    }
    Dictionary::close();
}


void Dictionaries::query(QString, bool)
{
    Dictionary::query(QString("%1=true").arg(db->getObjectNameCom("доступ_к_справочникам.меню")));
}


void Dictionaries::cmdOk() {
    Dictionary::cmdOk();
    QString dictName = getValue(db->getObjectName("доступ_к_справочникам.справочник")).toString().trimmed();
    if (dictName.size() > 0) {
        Dictionaries* dicts = app->getDictionaries();
        Dictionary* dict = dicts->getDictionary(dictName);         // Откроем справочник и подсправочники 1-го уровня
        if (dict != 0)
        {
            dict->show();
        }
    }
}


void Dictionaries::setForm(QString formName)
{
    if (form != 0)
    {
        form->close();
        delete form;
    }

    form = new FormGridSearch();

    form->appendToolTip("buttonOk",         trUtf8("Открыть справочник"));
    form->appendToolTip("buttonCancel",     trUtf8("Закрыть список справочников"));
    form->appendToolTip("buttonAdd",        trUtf8("Создать новый справочник"));
    form->appendToolTip("buttonDelete",     trUtf8("Удалить справочник"));
    form->appendToolTip("buttonView",       trUtf8("Просмотреть свойства справочника"));
    form->appendToolTip("buttonRequery",    trUtf8("Обновить список справочников (загрузить повторно с сервера)"));

    form->open(parentForm, this, formName.size() == 0 ? getTagName() : formName);
}


void Dictionaries::setOrderClause(QString)
{
    Table::setOrderClause(db->getObjectNameCom("доступ_к_справочникам.имя"));
}
