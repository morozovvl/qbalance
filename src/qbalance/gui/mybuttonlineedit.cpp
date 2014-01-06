/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include "mybuttonlineedit.h"
#include "../kernel/essence.h"
#include "../kernel/app.h"

MyButtonLineEdit::MyButtonLineEdit(QWidget *parent)
: QWidget(parent)
, buttonForm(0)
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
