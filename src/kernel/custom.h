#ifndef CUSTOM_H
#define CUSTOM_H

#include <QObject>
#include <QScriptable>

class Custom: public QObject {
    Q_OBJECT
public:
    Custom(QObject *parent = 0) : QObject(parent) { opened = false; }
    Q_INVOKABLE virtual bool open() { return doOpen(); }
    Q_INVOKABLE virtual void close() { doClose(); }
    Q_INVOKABLE bool isOpened() { return opened; }
protected:
    bool opened;
    virtual bool doOpen() { opened = true; return true; }
    virtual void doClose() { ; }
};

#endif
