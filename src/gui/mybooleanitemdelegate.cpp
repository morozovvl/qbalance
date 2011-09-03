#include <QCheckBox>
#include <QStyleOptionButton>
#include <QStyle>
#include <QApplication>
#include "mybooleanitemdelegate.h"

MyBooleanItemDelegate::MyBooleanItemDelegate(QObject* parent): MyItemDelegate(parent) {
    delegateType = Boolean;
}

QWidget* MyBooleanItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)
    return new QCheckBox(parent);
}

void MyBooleanItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    MyItemDelegate::paint(painter, option, QModelIndex());
    QStyleOptionButton optionButton;
    optionButton.rect = option.rect;
    Qt::CheckState state = (Qt::CheckState)index.data().toInt();
    switch(state) {
        case Qt::Unchecked:
            optionButton.state = QStyle::State_Off;
            break;
        case Qt::PartiallyChecked:
            optionButton.state = QStyle::State_NoChange;
            break;
        case Qt::Checked:
            optionButton.state = QStyle::State_On;
            break;
    }
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &optionButton, painter);
}

