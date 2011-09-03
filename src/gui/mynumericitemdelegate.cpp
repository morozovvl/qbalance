#include <QDoubleValidator>
#include <QStyleOptionViewItemV2>
#include "mynumericitemdelegate.h"
#include "mylineedit.h"
#include "formgrid.h"

/*
MyNumericItemDelegate::MyNumericItemDelegate(QObject* parent): MyItemDelegate(parent) {
    length = 1;
    precision = 0;
    delegateType = Numeric;
    setMask();
    setAlignment(Qt::AlignRight);
}
*/

MyNumericItemDelegate::MyNumericItemDelegate(QObject* parent, int len, int prec): MyItemDelegate(parent) {
    length = len;
    precision = prec;
    delegateType = Numeric;
    setMask();
    setAlignment(Qt::AlignRight);
}

void MyNumericItemDelegate::setLength(int len) {
    length = len;
    setMask();
}

void MyNumericItemDelegate::setPrecision(int prec) {
    precision = prec;
    setMask();
}

void MyNumericItemDelegate::setMask() {
    QString mask = QString("%1").arg(QString().fill('9', length - precision));
    if (precision > 0)
        mask = QString(mask + "%1%2").arg(QLocale().decimalPoint()).arg(QString().fill('9', precision));
    setColumnMask(mask);
}

QWidget* MyNumericItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex &index) const {
    Q_UNUSED(option)
    if (!readOnly) {
        QModelIndex idx = index;
        MyLineEdit* editor = new MyLineEdit(delegateType, parent, parentForm, idx);
        QDoubleValidator* validator = new QDoubleValidator(editor);
        editor->setValidator(validator);
        validator->setDecimals(precision);
        validator->setRange(-columnMask.toDouble(), columnMask.toDouble(), precision);
        qobject_cast<QLineEdit *>(editor)->setAlignment(alignment);
        return editor;
    }
    return 0;
}

void MyNumericItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    QStyleOptionViewItemV2 opt;
    QLocale locale;
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    opt = setElementColor(QStyleOptionViewItem(option));
    opt.displayAlignment = alignment | Qt::AlignVCenter;
    QString text = locale.toString(index.data(Qt::DisplayRole).toDouble(), 'f', precision);
    drawDisplay(painter, opt, opt.rect, text);
}

