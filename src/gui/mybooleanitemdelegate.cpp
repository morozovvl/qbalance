#include <QCheckBox>
#include <QStyleOptionButton>
#include <QStyle>
#include <QApplication>
#include "mybooleanitemdelegate.h"

MyBooleanItemDelegate::MyBooleanItemDelegate(QObject* parent): MyItemDelegate(parent)
{
    delegateType = Boolean;
}


QWidget* MyBooleanItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    saveOldValue(index.data());
    return new QCheckBox(parent);
}


void MyBooleanItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionButton BtnStyle;
    BtnStyle.state = QStyle::State_Enabled;
    if (index.model()->data(index, Qt::DisplayRole).toBool())
        BtnStyle.state |= QStyle::State_On;
    else
        BtnStyle.state |= QStyle::State_Off;
    BtnStyle.direction = QApplication::layoutDirection();
    BtnStyle.rect = option.rect;
    QApplication::style()->drawControl(QStyle::CE_CheckBox,&BtnStyle,painter);
}

