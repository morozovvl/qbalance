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

#include <QLineEdit>
#include "mydateitemdelegate.h"
#include "formgrid.h"
#include "../kernel/essence.h"


MyDateItemDelegate::MyDateItemDelegate(QObject* parent, FormGrid* form): MyItemDelegate(parent, form)
{
    delegateType = Date;
}


MyDateItemDelegate::~MyDateItemDelegate()
{
}


QWidget* MyDateItemDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QLineEdit* editor = new QLineEdit(parent);
    if (!readOnly)
    {
        if (parentForm != 0)
            parentForm->getParent()->saveOldValues();
        editor->setReadOnly(false);
    }
    else
        editor->setReadOnly(true);
    return editor;
}


