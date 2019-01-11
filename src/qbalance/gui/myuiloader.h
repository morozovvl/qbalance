#ifndef MYUILOADER_H
#define MYUILOADER_H

#include <QtUiTools/QUiLoader>
#include <QtWidgets/QWidget>

class MyUiLoader : public QUiLoader
{
    Q_OBJECT
public:
    explicit MyUiLoader(QObject *parent = 0);
    virtual QWidget* createWidget (const QString&, QWidget* = 0, const QString& = QString());
};

#endif // MYUILOADER_H
