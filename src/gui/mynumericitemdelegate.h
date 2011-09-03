#ifndef MYNUMERICITEMDELEGATE_H
#define MYNUMERICITEMDELEGATE_H

#include <QItemDelegate>
#include <QString>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QVariant>
#include "mylineedit.h"
#include "myitemdelegate.h"

class MyNumericItemDelegate : public MyItemDelegate {
    Q_OBJECT
public:
//    MyNumericItemDelegate(QObject* parent = 0);
    MyNumericItemDelegate(QObject* parent = 0, int len = 10, int prec = 0);
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setLength(int);
    int getLength() { return length; }
    void setPrecision(int);
    int getPrecision() { return precision; }
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
private:
    int length;
    int precision;
    void setMask();
};

#endif // MYNUMERICITEMDELEGATE_H
