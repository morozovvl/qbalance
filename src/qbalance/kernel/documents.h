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
#include "essence.h"

class Document;

class Documents : public Dictionary {
    Q_OBJECT
public:
    Documents(int, QObject *parent = 0);
    ~Documents();
    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove(bool = false);
    Q_INVOKABLE virtual void view();
    Q_INVOKABLE virtual void query(QString filter = "", bool = false);
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    QList<ToperType>*   getTopersList() { return &topersList; }
    Q_INVOKABLE virtual void setValue(QString, QVariant);
    Q_INVOKABLE virtual QVariant getValue(QString, int = -1);
    QString getAttrPrefix() { return prefix; }
    Q_INVOKABLE virtual void  setOrderClause(QString = "");
    Q_INVOKABLE virtual void  setForm(QString = "");
    Q_INVOKABLE Document* getDocument() { return currentDocument; }
    Q_INVOKABLE virtual void updateCurrentRow(int = 0);


protected:
    virtual bool        setTableModel(int = 0);

private:
    int                 operNumber;
    int                 currentRow;
    Document*           currentDocument;
    QString             subFormTitle;
    QString             prefix;
    QList<ToperType>    topersList;
    QList<FieldType>    attrFields;

    void                setCurrentDocument(int);       // Зафиксировать текущий документ

};

#endif // DOCUMENTS_H
