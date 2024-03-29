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

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include "essence.h"


class TApplication;
class Dictionaries;
class FormGridSearch;
class SearchParameters;


class Dictionary : public Essence {
    Q_OBJECT

    friend class Table;

private:
    bool            ftsEnabled;     // Флаг, показывающий, имеется ли в связанном справочнике полнотекстовый поиск
    bool            lsetIdEnabled;
    bool            isDepend;
    QString         dictTitle;
    bool            lNameExist;

protected:
    QString         prototypeName;          // Имя справочника - прототипа
    Dictionary*     parentDict;
    bool            lIsSet;
    bool            lCanShow;
    bool            lMustShow;
    bool            lIsConst;
    bool            lAutoSelect;
    bool            lIsSaldo;
    bool            lIsAutoLoaded;
    virtual void    prepareSelectCurrentRowCommand();
    virtual bool    setTableModel(int = 0);
    bool            locked;
    bool            getIdRefresh;
    bool            exact;          // Значение справочника должно быть определено при добавлении строки в документ
    QString         filter;
//    bool            isFtsEnabled;

    SearchParameters* parameters;

    Dictionary(QObject* = 0 /*nullptr*/);
    Dictionary(QString, QObject* = 0 /*nullptr*/);
    virtual void postInitialize(QString, QObject*);

public:
    ~Dictionary();

    Q_INVOKABLE virtual bool open(QString = "", QString = "");
    Q_INVOKABLE virtual void close();

// Функции для работы с моделью данных
    virtual bool add();
    Q_INVOKABLE virtual bool remove(bool = false);
    Q_INVOKABLE virtual void query(QString filter = "", bool = false);
    Q_INVOKABLE virtual void queryName(QString filter = "");
    Q_INVOKABLE virtual int  getId(int row = -1, bool = false);
    Q_INVOKABLE virtual void setOrderClause(QString = "");
    Q_INVOKABLE virtual void setSorted(bool sorted);
    Q_INVOKABLE virtual void setValue(QString name, QVariant value, int row = -1);
    Q_INVOKABLE virtual void setValue(int, QString, QVariant, int row = -1);


// Функции для работы справочника в составе документа
// Используются в момент добавления новых записей в документ
// блокируют открытие связанных справочников и др.подобные функции
    void setAutoLoaded(bool al);
    bool isAutoLoaded();
    bool canShow();
    Q_INVOKABLE void setCanShow(bool can);
    bool    isCanShow();

    Q_INVOKABLE bool isMustShow();
    Q_INVOKABLE virtual void setMustShow(bool);
    bool isConst();
    bool isSet();
    bool isSaldo();
    Q_INVOKABLE void setIsSaldo(bool s);
    Q_INVOKABLE void setConst(bool);
    Q_INVOKABLE void setAutoSelect(bool autoSelect);
//    Q_INVOKABLE virtual void cmdOk();


    virtual QString objectName();
    bool isDependent();
    void setDependent(bool d);
    QString getPrototypeName();
    void setPrototypeName(QString prototype);
    virtual bool isFtsEnabled();
    QString     getDictTitle();
    QStringList getChildDicts();
    Dictionary* getParentDict();
    void setParentDict(Dictionary* dict);
    Q_INVOKABLE virtual bool            setId(int);
    void    setIdEnabled(bool e);
    Q_INVOKABLE virtual void setForm(QString = "");
    Q_INVOKABLE virtual void updateCurrentRow(int = 0);

    Q_INVOKABLE virtual void        lock(bool = true);
    Q_INVOKABLE virtual bool isLocked();
    Q_INVOKABLE bool isPictureExist();
    Q_INVOKABLE QString getSearchExpression(QString = "");
    Q_INVOKABLE void setGetIdRefresh(bool val);

    virtual void        preparePrintValues();                   // Готовит значения для печати

    Q_INVOKABLE void setExact(bool e);
    bool getExact();
    Q_INVOKABLE virtual void            setSqlCommand(QString);

    Q_INVOKABLE virtual void            setFilter(QString);
    Q_INVOKABLE virtual QString         getFilter(QString) const;

};

#endif // DICTIONARY_H
