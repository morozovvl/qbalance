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

#ifndef FORMGRIDSEARCH_H
#define FORMGRIDSEARCH_H

#include <QWidget>
#include <QSqlTableModel>
#include <QShowEvent>
#include "formgrid.h"

class Dictionary;
class SearchParameters;

struct sParam {
    QString field;
    QString table;
    QVariant value;
};

class FormGridSearch : public FormGrid {

public:
    explicit FormGridSearch(QObject* parent = NULL);
    Q_INVOKABLE virtual void close();
    Dictionary* getParent() { return (Dictionary*)parent; }
    SearchParameters* getSearchParameters() { return parameters; }

public slots:
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();

private:
    SearchParameters*   parameters;
    QVector<sParam>     searchParameters;
    virtual void        createForm(QString, QWidget* pwgt = 0);
    virtual QDomElement createWidgetsStructure();

};

#endif // FORMGRIDSEARCH_H
