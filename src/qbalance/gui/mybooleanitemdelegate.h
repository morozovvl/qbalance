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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QStyleOptionButton>
    #include <QtGui/QStyle>
    #include <QtGui/QApplication>
    #include <QtGui/QItemDelegate>
    #include <QtGui/QCheckBox>
#else
    #include <QtWidgets/QStyleOptionButton>
    #include <QtWidgets/QStyle>
    #include <QtWidgets/QApplication>
    #include <QtWidgets/QItemDelegate>
    #include <QtWidgets/QCheckBox>
#endif

#include <QtCore/QPointer>
#include "myitemdelegate.h"

class MyBooleanItemDelegate : public MyItemDelegate {
    Q_OBJECT
public:
    MyBooleanItemDelegate(QObject*, FormGrid* = nullptr);
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
};

#endif // MYBOOLEANITEMDELEGATE_H
