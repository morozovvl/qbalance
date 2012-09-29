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

#include <QObject>
#include "../storage/mysqlrelationaltablemodel.h"
#include "myitemdelegate.h"
#include "formgrid.h"


MyItemDelegate::MyItemDelegate(QObject* par)
: QItemDelegate(par)
{
    columnMask = "";
    delegateType = String;
    setReadOnly(false);
}


MyItemDelegate::~MyItemDelegate()
{
    disconnect(this, 0, this, 0);
}


void MyItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QItemDelegate::paint(painter, setElementColor(option), index);
}


QStyleOptionViewItemV2 MyItemDelegate::setElementColor(QStyleOptionViewItem option) const {
    QStyleOptionViewItemV2 opt(option);
    if (!readOnly && option.state.testFlag(QStyle::State_HasFocus)) {
        QPalette p = opt.palette;
        p.setColor(QPalette::Active, QPalette::Highlight, Qt::darkBlue);
        p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);;
        opt.palette = p;
        opt.showDecorationSelected = true;
    }
    return opt;
}


void MyItemDelegate::setReadOnly(bool val)
{
    readOnly = val;
}
