#include "qtscriptshell_QTextCodec.h"

#include <QtScript/QScriptEngine>
#include <QTextCodec>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qtextcodec.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QList<QByteArray>)
Q_DECLARE_METATYPE(QChar*)
Q_DECLARE_METATYPE(QTextCodec::ConverterState*)
Q_DECLARE_METATYPE(char*)

QtScriptShell_QTextCodec::QtScriptShell_QTextCodec()
    : QTextCodec() {}

QtScriptShell_QTextCodec::~QtScriptShell_QTextCodec() {}

QList<QByteArray >  QtScriptShell_QTextCodec::aliases() const
{
    QScriptValue _q_function = __qtscript_self.property("aliases");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("aliases") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QTextCodec::aliases();
    } else {
        _q_function.setData(QScriptValue(true));
        QList<QByteArray > _q_retval = qscriptvalue_cast<QList<QByteArray > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QByteArray  QtScriptShell_QTextCodec::convertFromUnicode(const QChar*  in, int  length, QTextCodec::ConverterState*  state) const
{
    QScriptValue _q_function = __qtscript_self.property("convertFromUnicode");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("convertFromUnicode") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QTextCodec::convertFromUnicode() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QByteArray _q_retval = qscriptvalue_cast<QByteArray >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QChar *>(in))
            << qScriptValueFromValue(_q_engine, length)
            << qScriptValueFromValue(_q_engine, state)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QTextCodec::convertToUnicode(const char*  in, int  length, QTextCodec::ConverterState*  state) const
{
    QScriptValue _q_function = __qtscript_self.property("convertToUnicode");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("convertToUnicode") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QTextCodec::convertToUnicode() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<char *>(in))
            << qScriptValueFromValue(_q_engine, length)
            << qScriptValueFromValue(_q_engine, state)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QTextCodec::mibEnum() const
{
    QScriptValue _q_function = __qtscript_self.property("mibEnum");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mibEnum") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QTextCodec::mibEnum() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QByteArray  QtScriptShell_QTextCodec::name() const
{
    QScriptValue _q_function = __qtscript_self.property("name");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("name") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QTextCodec::name() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QByteArray _q_retval = qscriptvalue_cast<QByteArray >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

