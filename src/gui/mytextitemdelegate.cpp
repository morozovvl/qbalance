#include "mytextitemdelegate.h"

MyTextItemDelegate::MyTextItemDelegate(QObject* parent): QItemDelegate(parent) {
    editor = new QPlainTextEdit();
}

QWidget* MyTextItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) {
    Q_UNUSED(option)
    Q_UNUSED(index)
    editor->setParent(parent);
    return editor;
}
