#ifndef MYBUTTONLINEEDIT_H
#define MYBUTTONLINEEDIT_H

#include <QLineEdit>
#include <QPushButton>

class MyButtonLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue)
public:
    explicit MyButtonLineEdit(QWidget *parent = 0);
    ~MyButtonLineEdit();
    QString value() { return lineEdit->text(); }
    void setValue(QString text) { lineEdit->setText(text); }
protected:
    virtual void paintEvent(QPaintEvent*);
private:
    QLineEdit*      lineEdit;
    QPushButton*    pushButton;
};

#endif // MYBUTTONLINEEDIT_H
