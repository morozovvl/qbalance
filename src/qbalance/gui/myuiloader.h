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
    explicit MyUiLoader(QObject *parent = nullptr);
    virtual QWidget* createWidget (const QString&, QWidget* = nullptr, const QString& = QString());
};

#endif // MYUILOADER_H
