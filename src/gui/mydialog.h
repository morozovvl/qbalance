#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QDebug>

class MyDialog : public QDialog {
    Q_OBJECT
public:
    explicit MyDialog(QWidget *parent = 0);
//    Q_INVOKABLE void setWindowTitle(QString title) { QDialog::setWindowTitle(title); }
    Q_INVOKABLE QString windowTitle() { return QDialog::windowTitle(); }
    Q_INVOKABLE QString myWindowTitle() { return QDialog::windowTitle(); }
signals:

public slots:
};

#endif // MYDIALOG_H
