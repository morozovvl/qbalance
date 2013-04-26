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
public:
    Saldo(QString, QString, QObject *parent = 0);
    Q_INVOKABLE virtual bool open();
    virtual QString transformSelectStatement(QString);
    Q_INVOKABLE virtual QString objectName() { return "Saldo"; }
    void setQuan(bool q) { quan = q; }

protected:
    virtual void setTableModel(int = 0);

private:
    QString account;
    QString dictionaryName;
    bool quan;
};

#endif // SALDO_H
