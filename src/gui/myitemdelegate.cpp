#include <QDebug>
#include "myitemdelegate.h"
#include "formgrid.h"

MyItemDelegate::MyItemDelegate(QObject* parent): QItemDelegate(((FormGrid*)parent)->getForm()) {
    parentForm = parent;
    columnMask = "";
    delegateType = String;
    readOnly = false;
}

void MyItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    QItemDelegate::paint(painter, setElementColor(option), index);
}

QStyleOptionViewItemV2 MyItemDelegate::setElementColor(QStyleOptionViewItem option) const {
    QStyleOptionViewItemV2 opt(option);
    if (option.state.testFlag(QStyle::State_HasFocus)) {
        QPalette p = opt.palette;
        p.setColor(QPalette::Active, QPalette::Highlight, Qt::darkBlue);
        p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);;
        opt.palette = p;
        opt.showDecorationSelected = true;
    }
    return opt;
}
