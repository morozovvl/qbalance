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

#include <QtGui/QDoubleValidator>
#include <QtGui/QStyleOptionViewItemV2>
#include <QtGui/QLineEdit>
#include "mynumericitemdelegate.h"
#include "formgrid.h"
#include "../kernel/dictionary.h"


MyNumericItemDelegate::MyNumericItemDelegate(QObject* parent, FormGrid* form, int len, int prec)
: MyItemDelegate(parent, form)
{
    length = len;
    precision = prec;
    delegateType = Numeric;
    setColumnMask();
    editorWidget = 0;
}


MyNumericItemDelegate::~MyNumericItemDelegate()
{
    if (editorWidget != 0)
        delete editorWidget;
}


int MyNumericItemDelegate::getLength()
{
    return length;
}


int MyNumericItemDelegate::getPrecision()
{
    return precision;
}


void MyNumericItemDelegate::setLength(int len)
{
    length = len;
    setColumnMask();
}


void MyNumericItemDelegate::setPrecision(int prec)
{
    precision = prec;
    setColumnMask();
}


void MyNumericItemDelegate::setColumnMask(QString mask/* = ""*/)
{
    if (mask.size() == 0)
    {
        QString m = QString("%1").arg(QString().fill('9', length - precision));
        if (precision > 0)
        {
            m = QString(m + "%1%2").arg(QLocale().decimalPoint()).arg(QString().fill('9', precision));
        }
        MyItemDelegate::setColumnMask(m);
    }
    else
    {
        MyItemDelegate::setColumnMask(mask);
    }
}


QWidget* MyNumericItemDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem&, const QModelIndex &) const
{
    editorWidget = new QLineEdit(parent);
    editorWidget->setAlignment(Qt::AlignRight);
    if (!readOnly)
    {
//        if (parentForm != 0)
//            parentForm->getParent()->saveOldValues();
        if (essence != 0)
            essence->saveOldValues();
        editorWidget->setReadOnly(false);
    }
    else
        editorWidget->setReadOnly(true);
    return editorWidget;
}


void MyNumericItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionViewItemV2 opt;
    QLocale locale;
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    opt = setElementColor(QStyleOptionViewItem(option));
    opt.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
    QString text = locale.toString(index.data(Qt::DisplayRole).toDouble(), 'f', precision);
    drawDisplay(painter, opt, opt.rect, text);
}

