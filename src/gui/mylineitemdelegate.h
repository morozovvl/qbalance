#ifndef MYLINEITEMDELEGATE_H
#define MYLINEITEMDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include "myitemdelegate.h"

class MyLineItemDelegate : public MyItemDelegate {
    Q_OBJECT
public:
    MyLineItemDelegate(QObject*);
    virtual ~MyLineItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
};

#endif // MYLINEITEMDELEGATE_H
