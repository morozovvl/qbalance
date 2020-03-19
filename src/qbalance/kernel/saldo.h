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

#ifndef SALDO_H
#define SALDO_H

#include "dictionary.h"

class Saldo : public Dictionary {
    Q_OBJECT

private:
    QString account;
    QString dictionaryName;
    bool quan;
    bool leftOuterJoin;

protected:
    virtual bool    setTableModel(int = 0);
    Saldo(QString, QString, QObject* parent = 0 /*nullptr*/);
    virtual void postInitialize(QString, QString, QObject*);

public:
    ~Saldo();

    template <class T>
        static T* create(QString acc, QString name = "", QObject* parent = 0 /*nullptr*/)
        {
            T* p(new T(acc, name, parent));
            p->postInitialize(acc, name, parent);
            return p;
        }

    virtual QString transformSelectStatement(QString);
    Q_INVOKABLE virtual QString objectName();
    Q_INVOKABLE void setQuan(bool q);
    Q_INVOKABLE virtual void setOrderClause(QString = "");
    Q_INVOKABLE virtual bool setId(int);
    virtual void        lock(bool = true);
    Q_INVOKABLE virtual void setPhotoPath(QString path);
};

#endif // SALDO_H
