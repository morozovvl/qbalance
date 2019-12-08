
/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich MorozovVladimir@mail.ru

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

#ifndef TOPERS_H
#define TOPERS_H

#include <QtCore/QString>
#include "dictionary.h"

class Topers : public Dictionary {

private:
    void addDocument(int);
    void removeDocument(int opNumber);

protected:
    Q_INVOKABLE virtual void setForm(QString = "");

    Topers(QObject* parent = nullptr);
    virtual void postInitialize(QObject* parent = nullptr);

public:
    ~Topers();

    template <class T>
        static T* create(QObject* parent = nullptr)
        {
            T* p(new T(parent));
            p->postInitialize(parent);
            p->open();
            return p;
        }

    void cmdOk();
    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void view();
    Q_INVOKABLE virtual void setOrderClause(QString = "");
};

#endif // TOPERS_H
