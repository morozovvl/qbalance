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

#include <QtCore/QObject>
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyleOptionViewItemV2>
#include <QtCore/QModelIndex>
#include <QPalette>
#include <QtCore/QVariant>
#include <QtDesigner/QDesignerExportWidget>

class FormGrid;

enum DelegateTypes
{
    Numeric,
    Boolean,
    String,
    Date
};

class QDESIGNER_WIDGET_EXPORT MyItemDelegate : public QItemDelegate {
    Q_OBJECT

public:
    MyItemDelegate(QObject*, FormGrid*);
    ~MyItemDelegate();
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setColumnMask(const QString mask = "") { columnMask = mask; }
    virtual QString getColumnMask() { return columnMask; }
    virtual QVariant convertType(QVariant var) { return var; }
    virtual void        setReadOnly(bool val);
    virtual bool        isReadOnly() { return readOnly; }
    virtual void        setFieldName(QString name) { fieldName = name; }
    virtual QString     getFieldName() { return fieldName; }

protected:
    FormGrid*               parentForm;
    QString                 columnMask;
    DelegateTypes           delegateType;
    bool                    readOnly;
    QStyleOptionViewItemV2 setElementColor(QStyleOptionViewItem) const;
private:
    QString                 fieldName;
};

#endif // MYITEMDELEGATE_H
