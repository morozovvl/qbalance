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

#include <QtWidgets/QWidget>
#include <QtSql/QSqlTableModel>
#include "formgrid.h"


class Dictionary;
class SearchParameters;


struct sParam {
    QString field;
    QString table;
    QVariant value;
    bool    isFtsEnabled;
    Dictionary* dict;
};

class FormGridSearch : public FormGrid {
    Q_OBJECT
public:
    FormGridSearch(QObject* parent = 0);
    ~FormGridSearch();
    Q_INVOKABLE virtual void close();
    virtual QString getFilter();    // Возвращает фильтр для поиска в справочнике
    virtual QString getFilter(QString, QString = "");    // Возвращает фильтр для поиска в справочнике
    Q_INVOKABLE virtual QString getSearchValue(QString);
    virtual void activateWidget();
    SearchParameters* getSearchParameters();
    Q_INVOKABLE void clearAllComboBoxes();
    Q_INVOKABLE void setParameter(QString, QString);


private:
    SearchParameters*   parameters;
    virtual void        createForm(QString, QWidget* pwgt = 0);

};

#endif // FORMGRIDSEARCH_H
