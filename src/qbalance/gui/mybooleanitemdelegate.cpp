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

#include "mybooleanitemdelegate.h"
#include "../kernel/dictionary.h"


MyBooleanItemDelegate::MyBooleanItemDelegate(QObject* parent, FormGrid* form): MyItemDelegate(parent, form)
{
    delegateType = Boolean;
}


QWidget* MyBooleanItemDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QCheckBox* editorWidget = 0 /*nullptr*/;
    if (!menuMode)
    {
        editorWidget = new QCheckBox(parent);
        if (!readOnly)
        {
            if (essence != 0 /*nullptr*/)
            {
                essence->saveOldValues();
                disconnect(this, SIGNAL(closeEditor(QWidget*)), this, SLOT(calculate()));
                connect(this, SIGNAL(closeEditor(QWidget*)), this, SLOT(calculate()));
                editorWidget->setDisabled(false);
            }
        }
        else
            editorWidget->setDisabled(true);
    }
    return editorWidget;
}


void MyBooleanItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionButton BtnStyle;
    BtnStyle.state = QStyle::State_Enabled;
    if (index.model()->data(index, Qt::DisplayRole).toBool())
        BtnStyle.state |= QStyle::State_On;
    else
        BtnStyle.state |= QStyle::State_Off;
    BtnStyle.direction = QApplication::layoutDirection();
    BtnStyle.rect = option.rect;
    QApplication::style()->drawControl(QStyle::CE_CheckBox,&BtnStyle,painter);
}

