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

#ifndef FORMDOCUMENTS_H
#define FORMDOCUMENTS_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QLabel>
#else
    #include <QtWidgets/QLabel>
#endif

#include "formgrid.h"

class MyNumericEdit;


class FormDocuments : public FormGrid {
    Q_OBJECT

public:
     FormDocuments();

     virtual void close();

public slots:
    virtual void cmdAdd();
    virtual void cmdDelete();
    virtual void cmdView();
    virtual void cmdRequery();

    void showItog();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void showFilterEdit(bool);
    Q_INVOKABLE virtual QLineEdit* getFilterEdit();
    Q_INVOKABLE virtual QString    getFilter();

private:
    QLabel*          filterLabel;
    QLineEdit*      filterEdit;
    MyNumericEdit*    itogNumeric;
    virtual void createForm(QString, QWidget* pwgt = 0 /*nullptr*/);
};

#endif //FORMDOCUMENTS_H
