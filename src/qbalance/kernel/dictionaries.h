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


class Document;


class Dictionaries : public Dictionary {
    Q_OBJECT
public:
    QHash<QString, Dictionary*> dictionariesList;                    // Объекты справочников
    QList<QString>              dictionariesNamesList;                    // Список справочников в порядке создания
    Dictionaries(QObject *parent = 0);
    Q_INVOKABLE virtual Dictionary* getDictionary(QString);   // По умолчанию добавлять справочник
    Q_INVOKABLE virtual Saldo* getSaldo(QString acc);
    Q_INVOKABLE virtual bool addDictionary(QString);
    Q_INVOKABLE virtual bool addSaldo(QString acc);
    Q_INVOKABLE virtual void removeDictionary(QString);
    virtual void removeAll();
    QString getDictionaryTitle(QString);
    virtual void            query(QString filter = "", bool = false);
    QHash<QString, Dictionary*>* getDictionariesList() { return &dictionariesList; }
    virtual void cmdOk();
    Q_INVOKABLE virtual bool add();        // Добавление справочника
    Q_INVOKABLE virtual bool remove(bool = false);     // Удаление справочника
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void view();                    // Исправление свойств справочника
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    void    setDocument(Document* doc) { document = doc; }
    Document* getDocument() { return document; }
    bool        isSaldoExist() { return lIsSaldoExist; }
    Q_INVOKABLE virtual void setOrderClause(QString = "");
    virtual void            prepareSelectCurrentRowCommand() { ; }
    Q_INVOKABLE virtual void setForm(QString = "");

private:
    Document*   document;
    bool        lIsSaldoExist;

};

//Q_DECLARE_METATYPE(Dictionaries)

#endif // DICTIONARIES_H
