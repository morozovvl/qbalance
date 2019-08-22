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
#include <QtCore/QDebug>
#include "dictionaries.h"
#include "../kernel/app.h"
#include "../kernel/saldo.h"
#include "../gui/mainwindow.h"
#include "../gui/formgridsearch.h"
#include "../gui/wizarddictionary.h"
#include "../gui/dialog.h"
#include "../storage/dbfactory.h"


Dictionaries::Dictionaries(QObject *parent): Dictionary("", parent)
{
    document = nullptr;
}


Dictionaries::~Dictionaries()
{
}


void Dictionaries::close()
{
    removeAll();
    Dictionary::close();
}


void Dictionaries::postInitialize(QObject* parent)
{
    Dictionary::postInitialize("доступ_к_справочникам", parent);

    lInsertable = app->isSA();     // Если работает пользователь SA, то можно добавить новый справочник
    lViewable = app->isSA();       // Если работает пользователь SA, то можно просмотреть свойства справочника
    lDeleteable = app->isSA();       // Если работает пользователь SA, то можно попытаться удалить справочник
    lUpdateable = false;
    lPrintable = false;
    document = nullptr;
    lIsSaldoExist = false;
    formTitle = QObject::trUtf8("Справочники");
    scriptEngine = nullptr;
    scriptEngineEnabled = false;
    photoEnabled = false;
}


QHash<QString, Dictionary*>* Dictionaries::getDictionariesList()
{
    return &dictionariesList;
}


void Dictionaries::setDocument(Document* doc)
{
    document = doc;
}


Document* Dictionaries::getDocument()
{
    return document;
}


bool Dictionaries::isSaldoExist()
{
    return lIsSaldoExist;
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
        Dictionary* dict = Dictionary::create<Dictionary>(dictName, this);

        dict->setDictionaries(this);

        if (dict->open())
        {
            dictionariesList.insert(dictName, dict);
            dictionariesNamesList.insert(0, dictName);
            dict->setDictionaries(this);
            dict->setPrototypeName(db->getDictPrototype(dictName));

            // Установим "родителей" локальных справочников
            foreach(QString dictName, dictionariesList.keys())
            {
                Dictionary* dict = getDictionary(dictName);
                if (dict->isSet() && !dict->isSaldo())
                {
                    foreach (QString dictName, dict->getChildDicts())
                    {
                        Dictionary* childDict = getDictionary(dictName);
                        if (childDict != nullptr)
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
        dictionariesNamesList.insert(0, alias);

        // Имя справочника, который используется в бухгалтерском счете acc возьмем из справочника "Счета"
        QString dictName = db->getAccountsValue(acc, "ИМЯСПРАВОЧНИКА").toString().trimmed().toLower();

        Saldo* saldo = Saldo::create<Saldo>(acc, dictName);
        saldo->setDictionaries(this);

        if (saldo->open())
        {
            saldo->getFormWidget()->setWindowTitle(QString(QObject::trUtf8("Остаток на счете %1")).arg(acc));
            dictionariesList.insert(alias, saldo);
            saldo->setQuan(true);
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
            delete sal;
        }
        dictionariesList.remove(dictName);
        dictionariesNamesList.removeAt(dictionariesNamesList.indexOf(dictName));
    }
}


void Dictionaries::removeAll()
{
    QStringList dictsList = dictionariesNamesList;
    foreach (QString dictName, dictsList)
        removeDictionary(dictName);
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
    query();
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


void Dictionaries::query(QString, bool)
{
    Dictionary::query(QString("%1=%2").arg(db->getObjectNameCom("доступ_к_справочникам.меню")).arg(db->getTrueValue()));
}


void Dictionaries::cmdOk()
{
    Dictionary::cmdOk();
    QString dictName = getValue(db->getObjectName("доступ_к_справочникам.справочник")).toString().trimmed();
    if (dictName.size() > 0) {
        Dictionaries* dicts = app->getDictionaries();
        Dictionary* dict = dicts->getDictionary(dictName);         // Откроем справочник и подсправочники 1-го уровня
        if (dict != nullptr)
        {
            dict->show();
        }
    }
}


void Dictionaries::setForm(QString formName)
{
    if (form != nullptr)
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


QString Dictionaries::getDictionarySqlSelectStatement(QString tableName, QString prefix)
{
    QString selectList;
    QString fromList;
    QString selectStatement;
    QList<FieldType> columnsProperties;
    QStringList tables;
    DBFactory* db = TApplication::exemplar()->getDBFactory();
    db->getColumnsProperties(&columnsProperties, tableName, tableName, 0);
    if (columnsProperties.size() > 0)
    {
        tables.append(columnsProperties.at(0).table);
        fromList = db->getObjectNameCom(tableName);
        FieldType fld, oldFld;
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            fld = columnsProperties.at(i);
            if (!tables.contains(fld.table) && fld.name == db->getObjectName(fld.table + ".код"))
            {
                if (fld.table.left(9) == "документы" && fld.table.size() > 9)
                {
                    fromList.append(QString(" LEFT OUTER JOIN \"vw_спрдокументы\" \"%1\" ON \"%2\".\"%3\"=\"%1\".\"%4\"").arg(fld.table)
                                                                                                 .arg(oldFld.table)
                                                                                                 .arg(oldFld.name)
                                                                                                 .arg(fld.name));
                    QString docAttr = fld.table;
                    docAttr = QString("докатрибуты%1").arg(docAttr.remove("документы"));
                    if (db->isTableExists(docAttr))
                    {
                        if (!tables.contains(docAttr))
                        {
                            fromList.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%1\".\"%2\"=\"%3\".\"%4\"").arg(docAttr)
                                                                                                             .arg("КОД")
                                                                                                             .arg(oldFld.table)
                                                                                                             .arg(oldFld.name));
                            tables.append(docAttr);
                        }
                    }
                }
                else
                    fromList.append(QString(" LEFT OUTER JOIN \"%1\" ON \"%2\".\"%3\"=\"%1\".\"%4\"").arg(fld.table)
                                                                                                 .arg(oldFld.table)
                                                                                                 .arg(oldFld.name)
                                                                                                 .arg(fld.name));
                tables.append(fld.table);
            }
            if (selectList.size() > 0)
                selectList.append(", ");
            selectList.append(QString("\"%1\".\"%2\" AS \"%3%4\"").arg(fld.table)
                                                                  .arg(fld.name)
                                                                  .arg(prefix.toUpper())
                                                                  .arg(fld.column.toUpper()));
            oldFld = fld;
        }
        selectStatement.append(QLatin1String("SELECT DISTINCT ")).append(selectList);;
        selectStatement.append(QLatin1String(" FROM ")).append(fromList);
    }
    return selectStatement;
}




