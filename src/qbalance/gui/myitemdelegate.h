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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QLineEdit>
    #include <QtGui/QItemDelegate>
    #include <QtGui/QStyleOptionViewItem>
    #include <QtGui/QStyleOptionViewItem>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QLineEdit>
    #include <QtWidgets/QItemDelegate>
    #include <QtWidgets/QStyleOptionViewItem>
    #include <QtWidgets/QStyleOptionViewItem>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtCore/QObject>
#include <QtGui/QPainter>
#include <QtCore/QModelIndex>
#include <QtGui/QPalette>
#include <QtCore/QVariant>
#include <QtCore/QPointer>

class FormGrid;
class Essence;

enum DelegateTypes
{
    Numeric,
    Boolean,
    String,
    Date
};

class MyItemDelegate : public QItemDelegate {
    Q_OBJECT

public:
    MyItemDelegate(QObject*, FormGrid* = nullptr);
    ~MyItemDelegate();
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setColumnMask(const QString mask = "");
    virtual QString getColumnMask();
    virtual void        setReadOnly(bool val);
    virtual bool        isReadOnly();
    virtual void        setFieldName(QString name);
    virtual QString     getFieldName();
    virtual void setEssence(Essence*);

public slots:
    virtual void            calculate();

protected:
    Essence*                essence;
    QString                 columnMask;
    DelegateTypes           delegateType;
    bool                    readOnly;
    QStyleOptionViewItem setElementColor(QStyleOptionViewItem) const;
    bool                    menuMode;

private:
    QString                 fieldName;

};

#endif // MYITEMDELEGATE_H
