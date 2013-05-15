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

#include <QtCore/QDir>
#include <QtGui/QPainter>
#include <QtCore/QUrl>
#include "picture.h"
#include "../kernel/app.h"


Picture::Picture(QWidget* parent): QFrame(parent) {
    setFrameStyle(QFrame::Box);
    setVisible(true);
    setFixedSize(200, 200);
    pictureDrawn = "";
}


void Picture::setApp(TApplication* a)
{
    app = a;
    // Установим высоту и ширину картинки как 20% от среднего высоты и ширины экрана, чтобы картинка "адаптировалась" к размерам экрана
    int pictSize = (app->desktop()->width() + app->desktop()->height()) * 0.2 / 2;
    setFixedSize(pictSize, pictSize);
}


void Picture::show(QString fileName) {
    pictureFileName = fileName.size() > 0 && QDir().exists(fileName) ? fileName : "";
    update();
}

void Picture::paintEvent(QPaintEvent*) {

//    if (pictureFileName != pictureDrawn)
//    {
        QImage image(size(), QImage::Format_ARGB32_Premultiplied);
        if (pictureFileName.size() > 0)
            image.load(pictureFileName);
        else
            image.load(":noimage");
        image = image.scaled(size(), Qt::KeepAspectRatio);
        QPainter painter(this);
        painter.setClipping(false);
        painter.drawImage(0, 0, image);
        painter.end();
        pictureDrawn = pictureFileName;
//    }
}


