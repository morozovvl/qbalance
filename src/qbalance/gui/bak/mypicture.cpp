#include "mypicture.h"

MyPicture::MyPicture(QWidget* parent): QFrame(parent) {
    setFrameStyle(QFrame::Box);
    setVisible(true);
    setFixedSize(200, 200);
}

void MyPicture::show(QString fileName) {
    pictureFileName = QDir().exists(fileName) ? fileName : "";
    update();
}

void MyPicture::paintEvent(QPaintEvent*) {
    resize(128, 128);
    QImage image(size(), QImage::Format_ARGB32_Premultiplied);
    if (pictureFileName.size() > 0)
        image.load(pictureFileName);
    else
        image.load(":icon_noimage");
    image = image.scaled(size(), Qt::KeepAspectRatio);
    QPainter painter(this);
    painter.setClipping(false);
    painter.drawImage(0, 0, image);
}

