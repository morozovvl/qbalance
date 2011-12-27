#ifndef PICTURE_H
#define PICTURE_H

#include <QFrame>
#include <QString>
#include <QImage>
#include <QPaintEvent>

class Picture: public QFrame {
    Q_OBJECT
public:
    Picture(QWidget* parent = 0);
    void show(QString);
protected:
    QString pictureFileName;
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTURE_H
