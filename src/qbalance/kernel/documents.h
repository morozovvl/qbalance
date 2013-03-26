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
    virtual void show();
    virtual bool add();
    virtual bool remove();
    virtual void view();
    virtual void query(QString filter = "");
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    virtual void setScriptEngine() { scriptEngine = 0; }

protected:
    virtual void setForm();
    virtual void        prepareSelectCurrentRowCommand();

private:
    int operNumber;
    Document* currentDocument;
    QString     subFormTitle;
};

#endif // DOCUMENTS_H
