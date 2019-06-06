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


class Document;
class Saldo;


class Dictionaries : public Dictionary {
    Q_OBJECT

private:
    Document*   document;
    bool        lIsSaldoExist;

protected:
    Dictionaries(QObject* = nullptr);
    virtual void postInitialize(QObject*);

public:
    QHash<QString, Dictionary*> dictionariesList;                    // Объекты справочников
    QList<QString>              dictionariesNamesList;                    // Список справочников в порядке создания

    ~Dictionaries();

    Q_INVOKABLE virtual void close();

    template <class T>
        static T* create(QObject *parent = 0)
        {
            T* p(new T(parent));
            p->postInitialize(parent);
            p->open();
            return p;
        }

    Q_INVOKABLE virtual Dictionary* getDictionary(QString);   // По умолчанию добавлять справочник
    Q_INVOKABLE virtual Saldo* getSaldo(QString acc);
    Q_INVOKABLE virtual bool addDictionary(QString);
    Q_INVOKABLE virtual bool addSaldo(QString acc);
    Q_INVOKABLE virtual void removeDictionary(QString);
    Q_INVOKABLE virtual void removeAll();
    Q_INVOKABLE QString getDictionaryTitle(QString);
    Q_INVOKABLE virtual void            query(QString filter = "", bool = false);
    QHash<QString, Dictionary*>* getDictionariesList();
    virtual void cmdOk();
    Q_INVOKABLE virtual bool add();        // Добавление справочника
    Q_INVOKABLE virtual bool remove(bool = false);     // Удаление справочника
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void view();                    // Исправление свойств справочника
    void    setDocument(Document* doc);
    Document* getDocument();
    bool        isSaldoExist();
    Q_INVOKABLE virtual void setOrderClause(QString = "");
    virtual void            prepareSelectCurrentRowCommand() { ; }
    Q_INVOKABLE virtual void setForm(QString = "");

    static QString getDictionarySqlSelectStatement(QString, QString = "");       // Генерирует текст SQL-запроса для справочника
};

//Q_DECLARE_METATYPE(Dictionaries)

#endif // DICTIONARIES_H
