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

#ifndef MYBUTTONLINEEDITITEMDELEGATE_H
#define MYBUTTONLINEEDITITEMDELEGATE_H

#include <QtGui/QWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QItemDelegate>
#include <QtCore/QAbstractItemModel>
#include "myitemdelegate.h"


class MyButtonLineEditItemDelegate : public MyItemDelegate
{
    Q_OBJECT
public:
    MyButtonLineEditItemDelegate(QObject*, FormGrid* = 0);
    ~MyButtonLineEditItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    virtual void setEditorData(QWidget* editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const;
    void setFormOnPushButton(QString (*form)());
private:
    QString       (*buttonForm)();
};

#endif // MYBUTTONLINEEDITITEMDELEGATE_H
