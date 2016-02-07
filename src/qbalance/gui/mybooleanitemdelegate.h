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

#ifndef MYBOOLEANITEMDELEGATE_H
#define MYBOOLEANITEMDELEGATE_H

#include <QtCore/QPointer>
#include <QtGui/QItemDelegate>
#include <QtGui/QCheckBox>
#include "myitemdelegate.h"

class QDESIGNER_WIDGET_EXPORT MyBooleanItemDelegate : public MyItemDelegate {
    Q_OBJECT
public:
    MyBooleanItemDelegate(QObject*, FormGrid* = 0);
    ~MyBooleanItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
private:
    mutable QPointer<QCheckBox>  editorWidget;
};

#endif // MYBOOLEANITEMDELEGATE_H
