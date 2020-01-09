#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QtGui/QLineEdit>
#include "../kernel/app.h"

class MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MyLineEdit(QWidget*, TApplication* = nullptr);

    virtual void keyPressEvent(QKeyEvent*);

private:
    TApplication* app;
};

#endif // MYLINEEDIT_H
