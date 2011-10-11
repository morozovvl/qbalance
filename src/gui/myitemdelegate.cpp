#include <QObject>
#include <QDebug>
#include "../mysqlrelationaltablemodel.h"
#include "myitemdelegate.h"
#include "formgrid.h"


MyItemDelegate::MyItemDelegate(QObject* par)
: QItemDelegate(((FormGrid*)par)->getForm())
{
    parentForm = par;
    columnMask = "";
    delegateType = String;
    readOnly = false;
    connect(this, SIGNAL(closeEditor(QWidget*)), this, SLOT(calculate()));
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
    if (option.state.testFlag(QStyle::State_HasFocus)) {
        QPalette p = opt.palette;
        p.setColor(QPalette::Active, QPalette::Highlight, Qt::darkBlue);
        p.setColor(QPalette::Active, QPalette::HighlightedText, Qt::white);;
        opt.palette = p;
        opt.showDecorationSelected = true;
    }
    return opt;
}


void MyItemDelegate::calculate()
{
    ((FormGrid*)parentForm)->calculate();
}
