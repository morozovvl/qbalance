#ifndef QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H
#define QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H

#include <qglframebufferobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGLFramebufferObject : public QGLFramebufferObject
{
public:
    QtScriptShell_QGLFramebufferObject(const QSize&  size, QGLFramebufferObject::Attachment  attachment, unsigned int  target = 0x0DE1, unsigned int  internal_format = 0x8058);
    QtScriptShell_QGLFramebufferObject(const QSize&  size, const QGLFramebufferObjectFormat&  format);
    QtScriptShell_QGLFramebufferObject(const QSize&  size, unsigned int  target = 0x0DE1);
    QtScriptShell_QGLFramebufferObject(int  width, int  height, QGLFramebufferObject::Attachment  attachment, unsigned int  target = 0x0DE1, unsigned int  internal_format = 0x8058);
    QtScriptShell_QGLFramebufferObject(int  width, int  height, const QGLFramebufferObjectFormat&  format);
    QtScriptShell_QGLFramebufferObject(int  width, int  height, unsigned int  target = 0x0DE1);
    ~QtScriptShell_QGLFramebufferObject();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H
