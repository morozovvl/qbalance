#include <QDir>
#include <QPainter>
#include "picture.h"

Picture::Picture(QWidget* parent): QFrame(parent) {
    setFrameStyle(QFrame::Box);
    setVisible(true);
    setFixedSize(200, 200);
}

void Picture::show(QString fileName) {
    pictureFileName = QDir().exists(fileName) ? fileName : "";
    update();
}

void Picture::paintEvent(QPaintEvent*) {
    QImage image(size(), QImage::Format_ARGB32_Premultiplied);
    if (pictureFileName.size() > 0)
        image.load(pictureFileName);
    else
        image.load(":noimage");
    image = image.scaled(size(), Qt::KeepAspectRatio);
    QPainter painter(this);
    painter.setClipping(false);
    painter.drawImage(0, 0, image);
}

