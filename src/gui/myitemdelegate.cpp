#include <QObject>
#include <QDebug>
#include "../storage/mysqlrelationaltablemodel.h"
#include "myitemdelegate.h"
#include "formgrid.h"


MyItemDelegate::MyItemDelegate(QObject* par)
: QItemDelegate(par)
{
    columnMask = "";
    delegateType = String;
    readOnly = false;
}


MyItemDelegate::~MyItemDelegate()
{
    disconnect(this, 0, this, 0);
}


void MyItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QItemDelegate::paint(painter, setElementColor(option), index);
}


QStyleOptionViewItemV2 MyItemDelegate::setElementColor(QStyleOptionViewItem option) const {
    QStyleOptionViewItemV2 opt(option);
    if (!readOnly && option.state.testFlag(QStyle::State_HasFocus)) {
        QPalette p = opt.palette;
        p.setColor(QPalette::Active, QPalette::Highlight, Qt::darkBlue);
        p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);;
        opt.palette = p;
        opt.showDecorationSelected = true;
    }
    return opt;
}
