#include "qtscriptshell_QImageIOHandler.h"

#include <QtScript/QScriptEngine>
#include <QRect>
#include <QVariant>
#include <qbytearray.h>
#include <qimage.h>
#include <qimageiohandler.h>
#include <qiodevice.h>
#include <qrect.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QImageIOHandler::ImageOption)
Q_DECLARE_METATYPE(QImage*)

QtScriptShell_QImageIOHandler::QtScriptShell_QImageIOHandler()
    : QImageIOHandler() {}

QtScriptShell_QImageIOHandler::~QtScriptShell_QImageIOHandler() {}

bool  QtScriptShell_QImageIOHandler::canRead() const
{
    QScriptValue _q_function = __qtscript_self.property("canRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canRead") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QImageIOHandler::canRead() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QImageIOHandler::currentImageNumber() const
{
    QScriptValue _q_function = __qtscript_self.property("currentImageNumber");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentImageNumber") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::currentImageNumber();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QImageIOHandler::currentImageRect() const
{
    QScriptValue _q_function = __qtscript_self.property("currentImageRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentImageRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::currentImageRect();
    } else {
        _q_function.setData(QScriptValue(true));
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QImageIOHandler::imageCount() const
{
    QScriptValue _q_function = __qtscript_self.property("imageCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("imageCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::imageCount();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QImageIOHandler::jumpToImage(int  imageNumber)
{
    QScriptValue _q_function = __qtscript_self.property("jumpToImage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("jumpToImage") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::jumpToImage(imageNumber);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, imageNumber)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QImageIOHandler::jumpToNextImage()
{
    QScriptValue _q_function = __qtscript_self.property("jumpToNextImage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("jumpToNextImage") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::jumpToNextImage();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QImageIOHandler::loopCount() const
{
    QScriptValue _q_function = __qtscript_self.property("loopCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("loopCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::loopCount();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QImageIOHandler::nextImageDelay() const
{
    QScriptValue _q_function = __qtscript_self.property("nextImageDelay");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextImageDelay") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::nextImageDelay();
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QImageIOHandler::option(QImageIOHandler::ImageOption  option) const
{
    QScriptValue _q_function = __qtscript_self.property("option");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("option") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::option(option);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QImageIOHandler::read(QImage*  image)
{
    QScriptValue _q_function = __qtscript_self.property("read");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("read") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QImageIOHandler::read() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, image)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QImageIOHandler::setOption(QImageIOHandler::ImageOption  option, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setOption") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QImageIOHandler::setOption(option, value);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, value));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QImageIOHandler::supportsOption(QImageIOHandler::ImageOption  option) const
{
    QScriptValue _q_function = __qtscript_self.property("supportsOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportsOption") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::supportsOption(option);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QImageIOHandler::write(const QImage&  image)
{
    QScriptValue _q_function = __qtscript_self.property("write");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("write") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QImageIOHandler::write(image);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, image)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

