#ifndef MYBUTTONLINEEDIT_H
#define MYBUTTONLINEEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include "form.h"

class MyButtonLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue)
public:
    explicit MyButtonLineEdit(QWidget *parent = 0);
    ~MyButtonLineEdit();
    QString value() { return lineEdit->text(); }
    void setValue(QString text) { lineEdit->setText(text); }
    void setFormOnPushButton(QString (*form)());
protected:
    virtual void paintEvent(QPaintEvent*);
private:
    QString         (*buttonForm)();
    QLineEdit*      lineEdit;
    QPushButton*    pushButton;
private slots:
    void            showForm();
};

#endif // MYBUTTONLINEEDIT_H
