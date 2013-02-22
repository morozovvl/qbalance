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

#ifndef DICTIONARIES_H
#define DICTIONARIES_H

#include <QtSql/QSqlQuery>
#include "dictionary.h"
#include "saldo.h"

class Dictionaries : public Dictionary {
    Q_OBJECT
public:
    QMap<QString, Dictionary*> dictionaries;                    // Объекты справочников
    Dictionaries(QObject *parent = 0);
    Q_INVOKABLE virtual Dictionary* getDictionary(QString, int = 0, bool add = true);   // По умолчанию добавлять справочник
    Q_INVOKABLE virtual Saldo* getSaldo(QString acc, int deep = 0);
    Q_INVOKABLE virtual bool addDictionary(QString, int = 0);
    Q_INVOKABLE virtual bool addSaldo(QString acc, int deep = 0);
    Q_INVOKABLE virtual void removeDictionary(QString);
    QString getDictionaryTitle(QString);
    bool isMember(QString dictName) { return dictionaries.contains(dictName); }
    void query(QString);
    QMap<QString, Dictionary*>* getDictionaries() { return &dictionaries; }
    virtual void cmdOk();
    Q_INVOKABLE virtual bool add();        // Добавление справочника
    Q_INVOKABLE virtual bool remove();     // Удаление справочника
    Q_INVOKABLE virtual void view();       // Исправление свойств справочника
    Q_INVOKABLE virtual bool open(bool openForm = true);
    Q_INVOKABLE virtual void close();
    virtual void setScriptEngine() { scriptEngine = 0; }
protected:
    virtual void setForm();
private:
//    Dictionary* dictListDict;
};

//Q_DECLARE_METATYPE(Dictionaries)

#endif // DICTIONARIES_H
