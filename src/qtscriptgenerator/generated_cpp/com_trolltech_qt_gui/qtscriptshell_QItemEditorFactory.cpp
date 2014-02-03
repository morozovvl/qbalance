#include "qtscriptshell_QItemEditorFactory.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qitemeditorfactory.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QWidget*)

QtScriptShell_QItemEditorFactory::QtScriptShell_QItemEditorFactory()
    : QItemEditorFactory() {}

QtScriptShell_QItemEditorFactory::~QtScriptShell_QItemEditorFactory() {}

QWidget*  QtScriptShell_QItemEditorFactory::createEditor(int  userType, QWidget*  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("createEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createEditor") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemEditorFactory::createEditor(userType, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QWidget* _q_retval = qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, userType)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QByteArray  QtScriptShell_QItemEditorFactory::valuePropertyName(int  userType) const
{
    QScriptValue _q_function = __qtscript_self.property("valuePropertyName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("valuePropertyName") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QItemEditorFactory::valuePropertyName(userType);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QByteArray _q_retval = qscriptvalue_cast<QByteArray >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, userType)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

