#ifndef MYBUTTONLINEEDITITEMDELEGATE_H
#define MYBUTTONLINEEDITITEMDELEGATE_H

#include <QWidget>
#include <QTableWidget>
#include <QItemDelegate>
#include <QAbstractItemModel>
#include "myitemdelegate.h"
#include "mybuttonlineedit.h"


class MyButtonLineEditItemDelegate : public MyItemDelegate
{
    Q_OBJECT
public:
    MyButtonLineEditItemDelegate();
    virtual ~MyButtonLineEditItemDelegate();
    virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const;
    virtual void setEditorData(QWidget* editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const;
    void setFormOnPushButton(QString (*form)()) { buttonForm = form; }
private:
    QString       (*buttonForm)();
};

#endif // MYBUTTONLINEEDITITEMDELEGATE_H
