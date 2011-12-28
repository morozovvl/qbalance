#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <QFrame>
#include <QString>
#include <QImage>
#include <QPaintEvent>
#include "formgrid.h"

class MyPicture: public QFrame {
    Q_OBJECT
public:
    MyPicture(QWidget* parent = 0);
    void show(QString);
protected:
    QString pictureFileName;
    virtual void paintEvent(QPaintEvent*);
};

#endif // MYPICTURE_H
