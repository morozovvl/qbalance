#ifndef MYNUMERICITEMDELEGATE_H
#define MYNUMERICITEMDELEGATE_H

#include <QItemDelegate>
#include <QString>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QVariant>
#include "myitemdelegate.h"

class MyNumericItemDelegate : public MyItemDelegate
{
    Q_OBJECT
public:
    MyNumericItemDelegate(QObject* parent = 0, int len = 10, int prec = 0);
    virtual ~MyNumericItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setLength(int);
    int getLength() { return length; }
    void setPrecision(int);
    int getPrecision() { return precision; }
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setColumnMask(const QString mask = "");
private:
    int length;
    int precision;
};

#endif // MYNUMERICITEMDELEGATE_H
