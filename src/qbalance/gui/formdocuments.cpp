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

#include <QtCore/QtGlobal>

#include <QtCore/QObject>
#include "dialog.h"
#include "formgrid.h"
#include "formdocuments.h"
#include "mynumericedit.h"
#include "../kernel/essence.h"
#include "../storage/dbfactory.h"


#define LABEL_FILTER   QObject::trUtf8("Фильтр:")


FormDocuments::FormDocuments(): FormGrid()
{
    filterLabel = 0 /*nullptr*/;
    filterEdit = 0 /*nullptr*/;
    itogNumeric = 0 /*nullptr*/;
}


void FormDocuments::close()
{
    if (defaultForm)
    {
        if (filterLabel != 0 /*nullptr*/)
        {
            delete filterLabel;
            filterLabel = 0 /*nullptr*/;
        }

        if (filterEdit != 0 /*nullptr*/)
        {
            delete filterEdit;
            filterEdit = 0 /*nullptr*/;
        }

        if (itogNumeric != 0 /*nullptr*/)
        {
            delete itogNumeric;
            itogNumeric = 0 /*nullptr*/;
        }
    }
    FormGrid::close();
}


void FormDocuments::createForm(QString fileName, QWidget* pwgt)
{
    FormGrid::createForm(fileName, pwgt);
    if (defaultForm)
    {
        // Вставим строчку "Итого"
        QHBoxLayout* phbxItogLayout = new QHBoxLayout();
        phbxItogLayout->setObjectName("phbxItogLayout");
        phbxItogLayout->addStretch(1);
        phbxItogLayout->addWidget(new QLabel(QObject::trUtf8("Итого:"), formWidget), 0, Qt::AlignRight);

        // Создадим и вставим строчку с ИТОГО документа
        itogNumeric = new MyNumericEdit();
        itogNumeric->setReadOnly(true);
        QFont font = itogNumeric->font();
        font.setBold(true);
        font.setPointSize(font.pointSize() + 2);
        itogNumeric->setFont(font);
        itogNumeric->setObjectName("itogNumeric");
        phbxItogLayout->addWidget(itogNumeric, 0, Qt::AlignRight);
        vbxLayout->insertLayout(1, phbxItogLayout);

        QHBoxLayout* hbxFilterLayout = new QHBoxLayout();
        filterLabel = new QLabel(LABEL_FILTER, formWidget);
        filterLabel->setVisible(false);
        filterEdit = new QLineEdit(formWidget);
        filterEdit->setObjectName("filterEdit");
        filterEdit->setVisible(false);
        hbxFilterLayout->addWidget(filterLabel);
        hbxFilterLayout->addWidget(filterEdit);
//        hbxFilterLayout->addStretch(1);
        vbxLayout->insertLayout(0, hbxFilterLayout);
        connect(filterEdit, SIGNAL(returnPressed()), this, SLOT(cmdRequery()));
    }
    else
    {
         itogNumeric = static_cast<MyNumericEdit*>(formWidget->findChild("itogNumeric"));
    }
    connect(buttonRequery, SIGNAL(clicked()), this, SLOT(showItog()));
 }


void FormDocuments::cmdAdd()
{
    FormGrid::cmdAdd();
    showItog();
}


void FormDocuments::cmdDelete()
{
    FormGrid::cmdDelete();
    showItog();
}


void FormDocuments::cmdView()
{
    FormGrid::cmdView();
    showItog();
}


void FormDocuments::cmdRequery()
{
    FormGrid::cmdRequery();
    showItog();
}


void FormDocuments::show()
{
    FormGrid::show();
    showItog();
}


void FormDocuments::showItog()
{
        itogNumeric->setValue(parent->getSumValue(db->getObjectName("документы.сумма")));
}


void FormDocuments::showFilterEdit(bool show)
{
    if (filterLabel != 0 /*nullptr*/)
        filterLabel->setVisible(show);

    if (filterEdit != 0 /*nullptr*/)
        filterEdit->setVisible(show);
}


QLineEdit* FormDocuments::getFilterEdit()
{
    return filterEdit;
}


QString FormDocuments::getFilter()
{
    return filterEdit->text();
}
