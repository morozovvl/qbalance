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
#include "../gui/formgridsearch.h"

class TApplication;
class Dictionaries;

class Dictionary : public Essence {
    Q_OBJECT

public:
    Dictionary(QObject *parent = 0) { Dictionary("", parent); }
    Dictionary(QString name, QObject *parent = 0);
    ~Dictionary();
    Q_INVOKABLE virtual bool open(QString = "", QString = "");
    Q_INVOKABLE virtual void close();

// Функции для работы с моделью данных
    virtual bool add();
    Q_INVOKABLE virtual bool remove(bool = false);
    Q_INVOKABLE virtual void            query(QString filter = "", bool = false);
    Q_INVOKABLE virtual void            queryName(QString filter = "") { query(QString("\"%1\".\"ИМЯ\" ILIKE '%" + filter + "%'").arg(tableName)); }
    virtual bool                        calculate(bool update = true);
    Q_INVOKABLE virtual qulonglong      getId(int row = -1, bool = false);
    Q_INVOKABLE virtual void setOrderClause(QString = "");
    Q_INVOKABLE virtual void setSorted(bool sorted) { sortedTable = sorted; }
    Q_INVOKABLE virtual void setValue(QString name, QVariant value, int row = -1);
    Q_INVOKABLE virtual void setValue(qulonglong, QString, QVariant);
    Q_INVOKABLE virtual void setSqlCommand(QString);


// Функции для работы справочника в составе документа
// Используются в момент добавления новых записей в документ
// блокируют открытие связанных справочников и др.подобные функции
    void setAutoLoaded(bool al) { lIsAutoLoaded = al; }
    bool isAutoLoaded() { return lIsAutoLoaded; }
    bool canShow() { return lCanShow; }
    Q_INVOKABLE void setCanShow(bool can) { lCanShow = can; }
    bool    isCanShow() { return lCanShow; }

    Q_INVOKABLE bool isMustShow() { return lMustShow; }
    Q_INVOKABLE virtual void setMustShow(bool);
    bool isConst() { return lIsConst; }
    bool isSet() { return lIsSet; }
    bool isSaldo() { return lIsSaldo; }
    Q_INVOKABLE void setIsSaldo(bool s) { lIsSaldo = s; }
    Q_INVOKABLE void setConst(bool);
    Q_INVOKABLE void setAutoSelect(bool autoSelect) { lAutoSelect = autoSelect; }
                                                                            // которые будут блокироваться при добавлении записи в документ

    virtual QString objectName() { return "Dictionary"; }
    bool isDependent() { return isDepend; }
    void setDependent(bool d) { isDepend = d; }
    QString getPrototypeName() { return prototypeName; }
    void setPrototypeName(QString prototype) { prototypeName = prototype; }
    bool isFtsEnabled() { return ftsEnabled; }
    QString     getDictTitle() { return dictTitle; }
    QStringList getChildDicts();
    Dictionary* getParentDict() { return parentDict; }
    void setParentDict(Dictionary* dict) { parentDict = dict; }
    Q_INVOKABLE virtual void            setId(qulonglong);
    void    setIdEnabled(bool e) { lsetIdEnabled = e; }
    Q_INVOKABLE virtual void setForm(QString = "");
    Q_INVOKABLE virtual void updateCurrentRow(int = 0);

    Q_INVOKABLE virtual void        lock(bool = true);
    virtual bool isLocked() { return locked; }
    Q_INVOKABLE FormGridSearch* getForm() { return (FormGridSearch*)form; }
    Q_INVOKABLE bool isPictureExist() { return form->getPicture()->isPictureExist(); }
    Q_INVOKABLE QString getSearchExpression(QString = "");
    Q_INVOKABLE void setGetIdRefresh(bool val) { getIdRefresh = val; }

    virtual void        preparePrintValues();                   // Готовит значения для печати
    bool        getNameIntIsCode() { return nameIntIsCode; }
    Q_INVOKABLE void setNameIntIsCode(bool val) { nameIntIsCode = val; }

    Q_INVOKABLE void setExact(bool e) { exact = e; }
    bool getExact() { return exact; }

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
    bool            nameIntIsCode;  // Флаг, показывающий, будет ли число введенное в строке имени в поиске, рассматриваться как код позиции,
                                    // или как часть имени
    bool            exact;          // Значение справочника должно быть определено при добавлении строки в документ
    SearchParameters* parameters;


private:
    bool            ftsEnabled;     // Флаг, показывающий, имеется ли в связанном справочнике полнотекстовый поиск
    bool            lsetIdEnabled;
    bool            isDepend;
    QString         dictTitle;
    QString         sqlCommand;
};

#endif // DICTIONARY_H
