#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include "mybuttonlineedit.h"
#include "../kernel/essence.h"
#include "../kernel/app.h"

MyButtonLineEdit::MyButtonLineEdit(QWidget *parent)
: QWidget(parent)
, buttonForm(NULL)
{
    lineEdit = new QLineEdit(parent);
    lineEdit->setReadOnly(true);
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


void MyButtonLineEdit::setFormOnPushButton(QString (*form)())
{
    buttonForm = form;
    connect(pushButton, SIGNAL(clicked()), this, SLOT(showForm()));
}


void MyButtonLineEdit::showForm()
{
    QString result = (*buttonForm)();
    if (result.size() > 0)
        lineEdit->setText(result);
}
