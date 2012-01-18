#include <QLineEdit>
#include <QDebug>
#include "mylineitemdelegate.h"


MyLineItemDelegate::MyLineItemDelegate(QObject* parent): MyItemDelegate(parent)
{
    setAlignment(Qt::AlignVCenter);
}


MyLineItemDelegate::~MyLineItemDelegate()
{
}


QWidget* MyLineItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)
    if (!readOnly) {
        saveOldValue(index.data());
        QLineEdit* editor = new QLineEdit();
        editor->setParent(parent);
        editor->setAlignment(alignment);
        return editor;
    }
    return 0;
}
