#include <QStringList>
#include <QDialog>
#include <QLineEdit>
#include "formscriptengine.h"

Q_DECLARE_METATYPE(Form*)
Q_DECLARE_METATYPE(QDialog*)
Q_DECLARE_METATYPE(QLineEdit*)

// класс Form
QScriptValue FormConstructor(QScriptContext *context, QScriptEngine *engine) {
     Form *object = new Form();
     object->open(context->argument(0).toString(), engine->parent());
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue FormToScriptValue(QScriptEngine *engine, Form* const &in) {
    return engine->newQObject(in);
}

void FormFromScriptValue(const QScriptValue &object, Form* &out) {
    out = qobject_cast<Form*>(object.toQObject());
}

// класс QDialog
QScriptValue qDialogConstructor(QScriptContext *, QScriptEngine *engine) {
     QDialog *object = new QDialog();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue qDialogToScriptValue(QScriptEngine *engine, QDialog* const &in) {
    return engine->newQObject(in);
}

void qDialogFromScriptValue(const QScriptValue &object, QDialog* &out) {
    out = qobject_cast<QDialog*>(object.toQObject());
}

// класс QLineEdit
QScriptValue qLineEditToScriptValue(QScriptEngine *engine, QLineEdit* const &in) {
    return engine->newQObject(in);
}

void qLineEditFromScriptValue(const QScriptValue &object, QLineEdit* &out) {
    out = qobject_cast<QLineEdit*>(object.toQObject());
}


FormScriptEngine::FormScriptEngine()
:ScriptEngine()
{
    // Объявим класс Form
    qScriptRegisterMetaType(this, FormToScriptValue, FormFromScriptValue);
    globalObject().setProperty("Form", newQMetaObject(&QObject::staticMetaObject, newFunction(FormConstructor)));

    // Объявим класс QDialog
    qScriptRegisterMetaType(this, qDialogToScriptValue, qDialogFromScriptValue);
    globalObject().setProperty("QDialog", newQMetaObject(&QObject::staticMetaObject, newFunction(qDialogConstructor)));

    // Объявим класс QLineEdit
    qScriptRegisterMetaType(this, qLineEditToScriptValue, qLineEditFromScriptValue);


}
