#ifndef MYTEXTITEMDELEGATE_H
#define MYTEXTITEMDELEGATE_H

#include <QPlainTextEdit>
#include <QItemDelegate>

class MyTextItemDelegate : public QItemDelegate {
public:
    MyTextItemDelegate(QObject* parent = 0);
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &);
private:
    QPlainTextEdit* editor;
};

#endif // MYTEXTITEMDELEGATE_H
