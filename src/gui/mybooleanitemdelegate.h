#ifndef MYBOOLEANITEMDELEGATE_H
#define MYBOOLEANITEMDELEGATE_H

#include <QItemDelegate>
#include <QCheckBox>
#include "myitemdelegate.h"
#include "mybooleanitemdelegate.h"

class MyBooleanItemDelegate : public MyItemDelegate {
    Q_OBJECT
public:
    MyBooleanItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    virtual void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
};

#endif // MYBOOLEANITEMDELEGATE_H
