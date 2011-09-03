#include <QLineEdit>
#include <QDebug>
#include "mylineitemdelegate.h"

MyLineItemDelegate::MyLineItemDelegate(QObject* parent): MyItemDelegate(parent) {
    setAlignment(Qt::AlignVCenter);
}

QWidget* MyLineItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)
    if (!readOnly) {
        QLineEdit* editor = new QLineEdit();
        editor->setParent(parent);
        return editor;
    }
    return 0;
}
