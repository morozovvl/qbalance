/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QtCore/QStringList>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "formscriptengine.h"
#include "../gui/form.h"
#include "../gui/dialog.h"

Q_DECLARE_METATYPE(Dialog*)
Q_DECLARE_METATYPE(QLineEdit*)
Q_DECLARE_METATYPE(QPushButton*)

// класс Dialog
QScriptValue qDialogConstructor(QScriptContext *, QScriptEngine *engine) {
     Dialog *object = new Dialog();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue qDialogToScriptValue(QScriptEngine *engine, Dialog* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void qDialogFromScriptValue(const QScriptValue &object, Dialog* &out) {
    out = qobject_cast<Dialog*>(object.toQObject());
}

// класс QLineEdit
QScriptValue qLineEditToScriptValue(QScriptEngine *engine, QLineEdit* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void qLineEditFromScriptValue(const QScriptValue &object, QLineEdit* &out) {
    out = qobject_cast<QLineEdit*>(object.toQObject());
}

// класс QPushButton
QScriptValue qPushButtonToScriptValue(QScriptEngine *engine, QPushButton* const &in) {
    return engine->newQObject(in, QScriptEngine::ScriptOwnership);
}

void qPushButtonFromScriptValue(const QScriptValue &object, QPushButton* &out) {
    out = qobject_cast<QPushButton*>(object.toQObject());
}


FormScriptEngine::FormScriptEngine(QObject *parent/* = 0*/)
:ScriptEngine(parent)
{
}


void FormScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();

    // Объявим класс Dialog
    qScriptRegisterMetaType(this, qDialogToScriptValue, qDialogFromScriptValue);
    globalObject().setProperty("Dialog", newQMetaObject(&QObject::staticMetaObject, newFunction(qDialogConstructor)));

    // Объявим класс QLineEdit
    qScriptRegisterMetaType(this, qLineEditToScriptValue, qLineEditFromScriptValue);

    // Объявим класс QPushButton
    qScriptRegisterMetaType(this, qPushButtonToScriptValue, qPushButtonFromScriptValue);
}
