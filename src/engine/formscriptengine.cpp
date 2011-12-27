#include <QStringList>
#include <QDialog>
#include <QLineEdit>
#include "formscriptengine.h"
#include "../gui/form.h"

Q_DECLARE_METATYPE(QDialog*)
Q_DECLARE_METATYPE(QLineEdit*)

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


FormScriptEngine::FormScriptEngine(QObject *parent/* = 0*/)
:ScriptEngine(parent)
{
}


void FormScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();

    // Объявим класс QDialog
    qScriptRegisterMetaType(this, qDialogToScriptValue, qDialogFromScriptValue);
    globalObject().setProperty("QDialog", newQMetaObject(&QObject::staticMetaObject, newFunction(qDialogConstructor)));

    // Объявим класс QLineEdit
    qScriptRegisterMetaType(this, qLineEditToScriptValue, qLineEditFromScriptValue);
}
