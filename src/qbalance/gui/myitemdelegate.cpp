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

#include <QtCore/QObject>
#include <QtGui/QLineEdit>
#include "../storage/mysqlrelationaltablemodel.h"
#include "myitemdelegate.h"
#include "formgrid.h"


MyItemDelegate::MyItemDelegate(QObject* par, FormGrid* form)
: QItemDelegate(par)
{
    columnMask = "";
    delegateType = String;
    setReadOnly(false);
//    parentForm = form;
    dictionary = 0;
    if (form != 0)
        dictionary = form->getParent();
}


MyItemDelegate::~MyItemDelegate()
{
    this->disconnect();
}


void MyItemDelegate::setColumnMask(const QString mask)
{
    columnMask = mask;
}


QString MyItemDelegate::getColumnMask()
{
    return columnMask;
}


bool MyItemDelegate::isReadOnly()
{
    return readOnly;
}


void MyItemDelegate::setFieldName(QString name)
{
    fieldName = name;
}


QString MyItemDelegate::getFieldName()
{
    return fieldName;
}


void MyItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QItemDelegate::paint(painter, setElementColor(option), index);
}


QStyleOptionViewItemV2 MyItemDelegate::setElementColor(QStyleOptionViewItem option) const {
    QStyleOptionViewItemV2 opt(option);
    if (!readOnly && option.state.testFlag(QStyle::State_HasFocus)) {           // Если делегат можно редактировать и он получил фокус
        QPalette p = opt.palette;
        p.setColor(QPalette::Active, QPalette::Highlight, Qt::darkBlue);        // То установим палитру белые буквы на темно-синем фоне
        p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);;
        opt.palette = p;
        opt.showDecorationSelected = true;
    }
    else
    {
        if (option.state.testFlag(QStyle::State_Enabled)) {                     // Если делегат находится в текущей строке
            if (readOnly)                                                       // и его нельзя редактировать
            {
                QPalette p = opt.palette;
                p.setColor(QPalette::Active, QPalette::Highlight, Qt::lightGray);        // То установим палитру белые буквы на сером фоне
                p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::black);;
                opt.palette = p;
                opt.showDecorationSelected = true;
            }
            else
            {                                                                       // если его можно редактировать
                QPalette p = opt.palette;
                p.setColor(QPalette::Active, QPalette::Highlight, QColor(148, 202, 239));        // То установим палитру белые буквы на голубом фоне
                p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);;
                opt.palette = p;
                opt.showDecorationSelected = true;

            }
        }

    }
    return opt;
}


void MyItemDelegate::setReadOnly(bool val)
{
    readOnly = val;
}


QWidget* MyItemDelegate::getEditorWidget()
{
    return editorWidget.data();
}
