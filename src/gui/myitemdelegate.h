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
    void setAlignment(Qt::Alignment align) { alignment = align; }
    Qt::Alignment getAlignment() { return alignment; }
    virtual QVariant convertType(QVariant var) { return var; }
    void        setReadOnly(bool val) { readOnly = val; }
    QVariant    getOldValue() { return oldValue; }
protected:
    QString                 columnMask;
    Qt::Alignment           alignment;
    DelegateTypes           delegateType;
    bool                    readOnly;
    QStyleOptionViewItemV2 setElementColor(QStyleOptionViewItem) const;
    void                    saveOldValue(QVariant value) const { oldValue = value; }
private:
    mutable QVariant        oldValue;
};

#endif // MYITEMDELEGATE_H
