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

#include <QDoubleValidator>
#include <QStyleOptionViewItemV2>
#include <QLineEdit>
#include "mynumericitemdelegate.h"

MyNumericItemDelegate::MyNumericItemDelegate(QObject* parent, int len, int prec)
: MyItemDelegate(parent)
{
    length = len;
    precision = prec;
    delegateType = Numeric;
    setColumnMask();
    setAlignment(Qt::AlignRight);
}


MyNumericItemDelegate::~MyNumericItemDelegate()
{
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


QWidget* MyNumericItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    if (!readOnly) {
        saveOldValue(index.data());
        QLineEdit* editor = new QLineEdit();
        editor->setParent(parent);
        editor->setAlignment(alignment);
        QDoubleValidator* validator = new QDoubleValidator(editor);
        validator->setDecimals(precision);
        validator->setRange(-columnMask.toDouble(), columnMask.toDouble(), precision);
        editor->setValidator(validator);
        return editor;
    }
    return 0;
}

void MyNumericItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionViewItemV2 opt;
    QLocale locale;
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    opt = setElementColor(QStyleOptionViewItem(option));
    opt.displayAlignment = alignment | Qt::AlignVCenter;
    QString text = locale.toString(index.data(Qt::DisplayRole).toDouble(), 'f', precision);
    drawDisplay(painter, opt, opt.rect, text);
}

