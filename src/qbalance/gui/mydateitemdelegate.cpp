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

#include <QtGui/QLineEdit>
#include "mydateitemdelegate.h"
#include "formgrid.h"
#include "../kernel/dictionary.h"


MyDateItemDelegate::MyDateItemDelegate(QObject* parent, FormGrid* form): MyItemDelegate(parent, form)
{
    delegateType = Date;
    editorWidget = 0;
}


MyDateItemDelegate::~MyDateItemDelegate()
{
    if (editorWidget != 0)
        delete editorWidget;
}


QWidget* MyDateItemDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    editorWidget = new QLineEdit(parent);
    if (!readOnly)
    {
//        if (parentForm != 0)
//            parentForm->getParent()->saveOldValues();
        if (essence != 0)
            essence->saveOldValues();
        editorWidget->setReadOnly(false);
    }
    else
        editorWidget->setReadOnly(true);
    return editorWidget;
}


