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


#ifndef MYDATEITEMDELEGATE_H
#define MYDATEITEMDELEGATE_H
#include <QtDesigner/QDesignerExportWidget>
#include <QtCore/QPointer>
#include "myitemdelegate.h"

class MyDateItemDelegate : public MyItemDelegate
{
    Q_OBJECT
public:
    MyDateItemDelegate(QObject*, FormGrid* = 0);
    ~MyDateItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
};

#endif // MYDATEITEMDELEGATE_H
