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

#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include <QtSql/QSqlQuery>
#include <QtCore/QObject>
#include "dictionary.h"

class Document;

struct ToperType;

class Documents : public Dictionary {
    Q_OBJECT

private:
    int                 operNumber;
    int                 currentRow;
    Document*           currentDocument;
    QString             subFormTitle;
    QString             prefix;
    QString             operName;
    QList<ToperType>    topersList;
    QList<FieldType>    attrFields;

protected:
    virtual bool        setTableModel(int = 0);

    Documents(int, QObject* parent = 0);
    virtual void postInitialize(int, QObject*);

public:
    ~Documents();

    template <class T>
        static T* create(int opNumber, QObject *parent = 0)
        {
            T* p(new T(opNumber, parent));
            p->postInitialize(opNumber, parent);
            return p;
        }

    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove(bool = false);
    Q_INVOKABLE virtual void view();
    Q_INVOKABLE virtual void query(QString filter = "", bool = false);
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    QList<ToperType>*   getTopersList();
    Q_INVOKABLE virtual void setValue(QString, QVariant);
    Q_INVOKABLE virtual QVariant getValue(QString, int = -1);
    QString getAttrPrefix();
    Q_INVOKABLE virtual void  setOrderClause(QString = "");
    Q_INVOKABLE virtual void  setForm(QString = "");
    Q_INVOKABLE Document* getDocument();
    Q_INVOKABLE virtual void updateCurrentRow(int = 0);
    void                setCurrentDocument(int);       // Зафиксировать текущий документ
    virtual void        preparePrintValues();                   // Готовит значения для печати

};

#endif // DOCUMENTS_H
