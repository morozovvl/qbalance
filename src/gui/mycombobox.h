#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QtGui>
//#include <QObject>
//#include <QComboBox>

class MyComboBox : public QComboBox {
   Q_OBJECT
public:
    MyComboBox(QWidget* parent = 0): QComboBox(parent) { ; }

private:
    void keyPressEvent(QKeyEvent*);     // Перехват нажатия клавиши Enter - для перехода с одного ComboBox на другой

signals:
    void enterPressed(QWidget*);

};

#endif // MYCOMBOBOX_H
