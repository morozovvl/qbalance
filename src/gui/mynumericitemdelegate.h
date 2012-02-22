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

#ifndef MYNUMERICITEMDELEGATE_H
#define MYNUMERICITEMDELEGATE_H

#include <QItemDelegate>
#include <QString>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QVariant>
#include "myitemdelegate.h"

class MyNumericItemDelegate : public MyItemDelegate
{
    Q_OBJECT
public:
    MyNumericItemDelegate(QObject* parent = 0, int len = 10, int prec = 0);
    virtual ~MyNumericItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setLength(int);
    int getLength() { return length; }
    void setPrecision(int);
    int getPrecision() { return precision; }
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setColumnMask(const QString mask = "");
private:
    int length;
    int precision;
};

#endif // MYNUMERICITEMDELEGATE_H
