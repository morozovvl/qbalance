#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include "mycombobox.h"

void MyComboBox::keyPressEvent(QKeyEvent* event) {
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))
        emit enterPressed(this);
    else
        QComboBox::keyPressEvent(event);
}

