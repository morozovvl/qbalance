#include <QDebug>
#include <QLineEdit>
#include <QTableView>
#include "mytableview.h"
#include "formgrid.h"

MyTableView::MyTableView(FormGrid* par, QWidget* parentWidget): QTableView(parentWidget) {
    parent = par;
}


MyTableView::MyTableView(QWidget* parentWidget): QTableView(parentWidget) {
    parent = 0;
}


void MyTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    QTableView::currentChanged(current, previous);
    if (parent != 0)
        emit showPicture();
}


void MyTableView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint) {
    QTableView::closeEditor(editor, hint);
}

void MyTableView::keyPressEvent(QKeyEvent* event) {
    if (event->modifiers() == Qt::NoModifier) {              // Не были нажаты клавиши модификации
        if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {   // и <Enter>
// обработка нажатия клавиши Enter
        } else if (event->key() == Qt::Key_F2)
            parent->cmdView();
            else
                QTableView::keyPressEvent(event);
    }
    else
        QTableView::keyPressEvent(event);
}
