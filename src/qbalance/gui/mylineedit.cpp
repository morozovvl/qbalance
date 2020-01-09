#include <QtGui/QtEvents>
#include <QtGui/QLineEdit>
#include "mylineedit.h"
#include "tableview.h"

MyLineEdit::MyLineEdit(QWidget* parent, TApplication* a): QLineEdit(parent)
{
    app = a;
}


void MyLineEdit::keyPressEvent(QKeyEvent* event)
{
    event->setAccepted(false);

    static_cast<TableView*>(parentWidget())->keyPressEvent(event);

    if (!event->isAccepted())
    {
        QLineEdit::keyPressEvent(event);
    }
}
