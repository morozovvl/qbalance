#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include "mybuttonlineedit.h"

MyButtonLineEdit::MyButtonLineEdit(QWidget *parent) :
    QWidget(parent)
{
    lineEdit = new QLineEdit(parent);
    pushButton = new QPushButton(parent);
    pushButton->setText("...");
    pushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pushButton->setAutoDefault(false);
    QHBoxLayout* hbxLayout = new QHBoxLayout();
    hbxLayout->setSpacing(0);
    hbxLayout->addWidget(lineEdit);
    hbxLayout->addWidget(pushButton);
    hbxLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(hbxLayout);
    setFocusPolicy(Qt::StrongFocus);
}


MyButtonLineEdit::~MyButtonLineEdit()
{
}


/*virtual*/ void MyButtonLineEdit::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    pushButton->setFixedSize(lineEdit->height(), lineEdit->height());
}


