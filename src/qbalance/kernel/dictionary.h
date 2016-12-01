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
    QString         sqlCommand;

protected:
    QString         prototypeName;          // Имя справочника - прототипа
    Dictionary*     parentDict;
    bool            lSelectable;
    bool            lIsSet;
    bool            lCanShow;
    bool            lMustShow;
    bool            lIsConst;
    bool            lAutoSelect;
    bool            lIsSaldo;
    bool            lIsAutoLoaded;
    QStringList     fieldList;
    virtual void    prepareSelectCurrentRowCommand();
    virtual bool    setTableModel(int = 0);
    bool            locked;
    bool            getIdRefresh;
    bool            exact;          // Значение справочника должно быть определено при добавлении строки в документ
    SearchParameters* parameters;

    Dictionary(QObject* = 0);
    Dictionary(QString, QObject* = 0);
    virtual void postInitialize(QString, QObject*);

public:
    ~Dictionary();

    Q_INVOKABLE virtual bool open(QString = "", QString = "");
    Q_INVOKABLE virtual void close();

// Функции для работы с моделью данных
    virtual bool add();
    Q_INVOKABLE virtual bool remove(bool = false);
    Q_INVOKABLE virtual void            query(QString filter = "", bool = false);
    Q_INVOKABLE virtual void            queryName(QString filter = "");
    virtual bool                        calculate(bool update = true);
    Q_INVOKABLE virtual qulonglong      getId(int row = -1, bool = false);
    Q_INVOKABLE virtual void setOrderClause(QString = "");
    Q_INVOKABLE virtual void setSorted(bool sorted);
    Q_INVOKABLE virtual void setValue(QString name, QVariant value, int row = -1);
    Q_INVOKABLE virtual void setValue(qulonglong, QString, QVariant);
    Q_INVOKABLE virtual void setSqlCommand(QString);


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
    Q_INVOKABLE virtual void            setId(qulonglong);
    void    setIdEnabled(bool e);
    Q_INVOKABLE virtual void setForm(QString = "");
    Q_INVOKABLE virtual void updateCurrentRow(int = 0);

    Q_INVOKABLE virtual void        lock(bool = true);
    virtual bool isLocked();
    Q_INVOKABLE virtual FormGridSearch* getForm();
    Q_INVOKABLE bool isPictureExist();
    Q_INVOKABLE QString getSearchExpression(QString = "");
    Q_INVOKABLE void setGetIdRefresh(bool val);

    virtual void        preparePrintValues();                   // Готовит значения для печати

    Q_INVOKABLE void setExact(bool e);
    bool getExact();

};

#endif // DICTIONARY_H
