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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QLineEdit>
    #include <QtGui/QItemDelegate>
    #include <QtGui/QStyleOptionViewItem>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QLineEdit>
    #include <QtWidgets/QItemDelegate>
    #include <QtWidgets/QStyleOptionViewItem>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtCore/QString>
#include <QtGui/QPainter>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QPointer>
#include "myitemdelegate.h"


class MyNumericItemDelegate : public MyItemDelegate
{
    Q_OBJECT
public:
    MyNumericItemDelegate(QObject*, FormGrid*, int len = 10, int prec = 0);
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    virtual void setLength(int);
    virtual int getLength();
    virtual void setPrecision(int);
    virtual int getPrecision();
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setColumnMask(const QString mask = "");
    virtual void setHideZero(bool);
private:
    int length;
    int precision;
    bool hideZero;
};

#endif // MYNUMERICITEMDELEGATE_H
