#include "qtscriptshell_QIconEngine.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qiconengine.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QIcon::State)
Q_DECLARE_METATYPE(QList<QSize>)
Q_DECLARE_METATYPE(QIconEngine*)
Q_DECLARE_METATYPE(QPainter*)

QtScriptShell_QIconEngine::QtScriptShell_QIconEngine()
    : QIconEngine() {}

QtScriptShell_QIconEngine::~QtScriptShell_QIconEngine() {}

QSize  QtScriptShell_QIconEngine::actualSize(const QSize&  size, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("actualSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actualSize") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QIconEngine::actualSize(size, mode, state);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QIconEngine::addFile(const QString&  fileName, const QSize&  size, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("addFile");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addFile") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QIconEngine::addFile(fileName, size, mode, state);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, fileName)
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QIconEngine::addPixmap(const QPixmap&  pixmap, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("addPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addPixmap") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QIconEngine::addPixmap(pixmap, mode, state);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state));
        _q_function.setData(QScriptValue(false));
    }
}

QList<QSize >  QtScriptShell_QIconEngine::availableSizes(QIcon::Mode  mode, QIcon::State  state) const
{
    QScriptValue _q_function = __qtscript_self.property("availableSizes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("availableSizes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QIconEngine::availableSizes(mode, state);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QList<QSize > _q_retval = qscriptvalue_cast<QList<QSize > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QIconEngine*  QtScriptShell_QIconEngine::clone() const
{
    QScriptValue _q_function = __qtscript_self.property("clone");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clone") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QIconEngine::clone() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QIconEngine* _q_retval = qscriptvalue_cast<QIconEngine* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QIconEngine::iconName() const
{
    QScriptValue _q_function = __qtscript_self.property("iconName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("iconName") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QIconEngine::iconName();
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QIconEngine::key() const
{
    QScriptValue _q_function = __qtscript_self.property("key");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("key") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QIconEngine::key();
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QIconEngine::paint(QPainter*  painter, const QRect&  rect, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QIconEngine::paint() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state));
        _q_function.setData(QScriptValue(false));
    }
}

QPixmap  QtScriptShell_QIconEngine::pixmap(const QSize&  size, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("pixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pixmap") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QIconEngine::pixmap(size, mode, state);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QPixmap _q_retval = qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

