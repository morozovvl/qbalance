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

#ifndef MYITEMDELEGATE_H
#define MYITEMDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyleOptionViewItemV2>
#include <QModelIndex>
#include <QPalette>
#include <QVariant>
#include <QDebug>
//#include "../essence.h"

enum DelegateTypes
{
    Numeric,
    Boolean,
    String
};

class MyItemDelegate : public QItemDelegate {
    Q_OBJECT

public:
    MyItemDelegate(QObject* par = 0);
    virtual ~MyItemDelegate();
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setColumnMask(const QString mask = "") { columnMask = mask; }
    QString getColumnMask() { return columnMask; }
//    void setAlignment(Qt::Alignment align) { alignment = align; }
//    Qt::Alignment getAlignment() { return alignment; }
    virtual QVariant convertType(QVariant var) { return var; }
    void        setReadOnly(bool val);
    bool        isReadOnly() { return readOnly; }
    QVariant    getOldValue() { return oldValue; }
protected:
    QString                 columnMask;
//    Qt::Alignment           alignment;
    DelegateTypes           delegateType;
    bool                    readOnly;
    QStyleOptionViewItemV2 setElementColor(QStyleOptionViewItem) const;
    void                    saveOldValue(QVariant value) const { oldValue = value; }
private:
    mutable QVariant        oldValue;
};

#endif // MYITEMDELEGATE_H
