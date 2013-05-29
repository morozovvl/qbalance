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
#include "mylineitemdelegate.h"
#include "formgrid.h"
#include "../kernel/essence.h"


MyLineItemDelegate::MyLineItemDelegate(QObject* parent, FormGrid* form): MyItemDelegate(parent, form)
{
//    setAlignment(Qt::AlignVCenter);
    length = 0;
}


MyLineItemDelegate::~MyLineItemDelegate()
{
}


QWidget* MyLineItemDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    if (!readOnly) {
        parentForm->getParent()->saveOldValues();
        QLineEdit* editor = new QLineEdit(parent);
        editor->setMaxLength(length);
        return editor;
    }
    return 0;
}
