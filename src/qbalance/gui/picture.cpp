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
#include <QPainter>
#include <QtCore/QUrl>
#include "picture.h"
#include "../kernel/app.h"


Picture::Picture(QWidget* parent): QFrame(parent) {
    setFrameStyle(QFrame::Box);
    setVisible(true);
    pictSize = 200;
    setFixedSize(pictSize, pictSize);
    pictureDrawn = "";
    isBigPicture = false;
    bigPictRect.setRect(QApplication::desktop()->availableGeometry().x(),
                        QApplication::desktop()->availableGeometry().y(),
                        QApplication::desktop()->availableGeometry().width() * 0.8,
                        QApplication::desktop()->availableGeometry().height() * 0.8);
    photoWindowTitle = "";
}


Picture::~Picture()
{
}


void Picture::setApp(TApplication* a)
{
    app = a;
    // Установим высоту и ширину картинки как 20% от среднего высоты и ширины экрана, чтобы картинка "адаптировалась" к размерам экрана
    pictSize = (app->desktop()->width() + app->desktop()->height()) * 0.2 / 2;
    setFixedSize(pictSize, pictSize);
//    bigPictRect.setRect(0, 0, app->getMainWindow()->centralWidget()->width(), app->getMainWindow()->centralWidget()->height());
}


void Picture::setPhotoFileName(QString fileName)
{
    photoFileName = fileName.size() > 0 && QDir().exists(fileName) ? fileName : "";
}


void Picture::show(QString fileName) {
    setPhotoFileName(fileName);
    update();
}


void Picture::paintEvent(QPaintEvent*) {
    QImage image(size(), QImage::Format_ARGB32_Premultiplied);
    if (photoFileName.size() > 0)
        image.load(photoFileName);
    else
        image.load(":noimage");
    image = image.scaled(size(), Qt::KeepAspectRatio);
    QPainter painter(this);
    painter.setClipping(false);
    painter.drawImage((this->width() - image.width()) / 2, (this->height() - image.height()) / 2, image);
    painter.end();
    pictureDrawn = photoFileName;
}


void Picture::setVisibility(bool vis)
{
    setVisible(vis);
    if (vis)
        setFixedSize(pictSize, pictSize);
    else
        setFixedSize(0, 0);
}


void Picture::mouseDoubleClickEvent(QMouseEvent*)
{
    if (!isBigPicture)
        showBigPicture();
}


void Picture::showBigPicture()
{
    if (photoFileName.size() > 0)
    {
        QDialog bigPicture(QApplication::activeWindow());
        bigPicture.resize(bigPictRect.size());
        if (photoWindowTitle.size() > 0)
            bigPicture.setWindowTitle(photoWindowTitle);

        Picture picture(&bigPicture);
        picture.setIsBig(true);
        picture.setFixedSize(bigPicture.width(), bigPicture.height());
        picture.show(photoFileName);

        bigPicture.exec();
        bigPictRect = bigPicture.rect();
    }
}


