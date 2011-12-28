#include <QDebug>
#include <QLayout>
#include "mybuttonlineedititemdelegate.h"


MyButtonLineEditItemDelegate::MyButtonLineEditItemDelegate(QObject* parent): MyItemDelegate(parent)
{
}


MyButtonLineEditItemDelegate::~MyButtonLineEditItemDelegate()
{
}


QWidget* MyButtonLineEditItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
Q_UNUSED(option)
Q_UNUSED(index)
MyButtonLineEdit* editor = new MyButtonLineEdit(parent);
editor->setFormOnPushButton(buttonForm);
return editor;
}


void MyButtonLineEditItemDelegate::setEditorData(QWidget* editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    MyButtonLineEdit* buttonLineEdit = static_cast<MyButtonLineEdit*>(editor);
    buttonLineEdit->setValue(value);
}


void MyButtonLineEditItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const
{
    MyButtonLineEdit* buttonLineEdit = static_cast<MyButtonLineEdit*>(editor);
    QString value = buttonLineEdit->value();
    model->setData(index, value, Qt::EditRole);
}
