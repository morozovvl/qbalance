#ifndef MYITEMDELEGATE_H
#define MYITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyleOptionViewItemV2>
#include <QModelIndex>
#include <QPalette>

enum DelegateTypes {Numeric, Boolean, String};

class MyItemDelegate : public QItemDelegate {
public:
    MyItemDelegate(QObject* par = 0);
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    void setColumnMask(QString mask) { columnMask = mask; }
    QString getColumnMask() { return columnMask; }
    void setAlignment(Qt::Alignment align) { alignment = align; }
    Qt::Alignment getAlignment() { return alignment; }
    virtual QVariant convertType(QVariant var) { return var; }
    void setReadOnly(bool val) { readOnly = val; }
protected:
    QStyleOptionViewItemV2 setElementColor(QStyleOptionViewItem) const;
    QObject* parentForm;
    QString columnMask;
    Qt::Alignment alignment;
    DelegateTypes delegateType;
    bool readOnly;
};

#endif // MYITEMDELEGATE_H
