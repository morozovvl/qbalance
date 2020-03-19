#ifndef MYUILOADER_H
#define MYUILOADER_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QWidget>
#else
    #include <QtWidgets/QWidget>
#endif

#include <QtUiTools/QUiLoader>

class MyUiLoader : public QUiLoader
{
    Q_OBJECT
public:
    explicit MyUiLoader(QObject *parent = 0 /*nullptr*/);
    virtual QWidget* createWidget (const QString&, QWidget* = 0 /*nullptr*/, const QString& = QString());
};

#endif // MYUILOADER_H
