#include <QStringList>
#include <QDialog>
#include <QLineEdit>
#include <QAbstractItemModel>
#include "scriptengine.h"
#include "../gui/app.h"
#include "../kernel/essence.h"
#include "../kernel/dictionary.h"
#include "../storage/table.h"
#include "../storage/dbfactory.h"
#include "../storage/mysqlquery.h"
#include "../storage/mysqlrelationaltablemodel.h"

Q_DECLARE_METATYPE(Table*)
Q_DECLARE_METATYPE(Dictionary*)
Q_DECLARE_METATYPE(Essence*)
Q_DECLARE_METATYPE(Form*)
Q_DECLARE_METATYPE(QDialog*)
Q_DECLARE_METATYPE(MySqlQuery*)
Q_DECLARE_METATYPE(QLineEdit*)
Q_DECLARE_METATYPE(DBFactory*)
Q_DECLARE_METATYPE(MySqlRelationalTableModel*)

// класс Table
QScriptValue TableConstructor(QScriptContext *context, QScriptEngine *engine) {
     Table *object = new Table(context->argument(0).toString());
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
 }

QScriptValue TableToScriptValue(QScriptEngine *engine, Table* const &in) {
    return engine->newQObject(in);
}

void TableFromScriptValue(const QScriptValue &object, Table* &out) {
    out = qobject_cast<Table*>(object.toQObject());
}

// класс Dictionary
QScriptValue DictionaryConstructor(QScriptContext *context, QScriptEngine *engine) {
     Dictionary *object = new Dictionary(context->argument(0).toString());
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue DictionaryToScriptValue(QScriptEngine *engine, Dictionary* const &in) {
    return engine->newQObject(in);
}

void DictionaryFromScriptValue(const QScriptValue &object, Dictionary* &out) {
    out = qobject_cast<Dictionary*>(object.toQObject());
}

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

// класс Essence
QScriptValue EssenceToScriptValue(QScriptEngine *engine, Essence* const &in) {
    return engine->newQObject(in);
}

void EssenceFromScriptValue(const QScriptValue &object, Essence* &out) {
    out = qobject_cast<Essence*>(object.toQObject());
}

// класс MySqlQuery

QScriptValue MySqlQueryConstructor(QScriptContext *context, QScriptEngine *engine) {
     MySqlQuery *object = new MySqlQuery(context->argument(0).toString());
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue MySqlQueryToScriptValue(QScriptEngine *engine, MySqlQuery* const &in) {
    return engine->newQObject(in);
}

void MySqlQueryFromScriptValue(const QScriptValue &object, MySqlQuery* &out) {
    out = qobject_cast<MySqlQuery*>(object.toQObject());
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

// класс DBFactory
QScriptValue DBFactoryToScriptValue(QScriptEngine *engine, DBFactory* const &in) {
    return engine->newQObject(in);
}

void DBFactoryFromScriptValue(const QScriptValue &object, DBFactory* &out) {
    out = qobject_cast<DBFactory*>(object.toQObject());
}

// класс MySqlRelationalTableModel
QScriptValue MySqlRelationalTableModelConstructor(QScriptContext *, QScriptEngine *engine) {
     MySqlRelationalTableModel *object = new MySqlRelationalTableModel();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
 }

QScriptValue MySqlRelationalTableModelToScriptValue(QScriptEngine *engine, MySqlRelationalTableModel* const &in) {
    return engine->newQObject(in);
}

void MySqlRelationalTableModelFromScriptValue(const QScriptValue &object, MySqlRelationalTableModel* &out) {
    out = qobject_cast<MySqlRelationalTableModel*>(object.toQObject());
}


//////////////
ScriptEngine::ScriptEngine(QObject *parent) : QScriptEngine(parent) {
    installTranslatorFunctions(QScriptValue());

    // Объявим глобальный объект App
    globalObject().setProperty("App", newQObject(TApplication::exemplar()));

    // Объявим класс Essence
    qScriptRegisterMetaType(this, EssenceToScriptValue, EssenceFromScriptValue);

    // Объявим класс Form
    qScriptRegisterMetaType(this, FormToScriptValue, FormFromScriptValue);
    globalObject().setProperty("Form", newQMetaObject(&QObject::staticMetaObject, newFunction(FormConstructor)));

    // Объявим класс MySqlQuery
    qScriptRegisterMetaType(this, MySqlQueryToScriptValue, MySqlQueryFromScriptValue);
    globalObject().setProperty("SqlQuery", newQMetaObject(&QObject::staticMetaObject, newFunction(MySqlQueryConstructor)));

    // Объявим класс QDialog
    qScriptRegisterMetaType(this, qDialogToScriptValue, qDialogFromScriptValue);
    globalObject().setProperty("QDialog", newQMetaObject(&QObject::staticMetaObject, newFunction(qDialogConstructor)));

    // Объявим класс QLineEdit
    qScriptRegisterMetaType(this, qLineEditToScriptValue, qLineEditFromScriptValue);

    // Объявим класс Table
    qScriptRegisterMetaType(this, TableToScriptValue, TableFromScriptValue);
    globalObject().setProperty("Table", newQMetaObject(&QObject::staticMetaObject, newFunction(TableConstructor)));

    // Объявим класс Dictionary
    qScriptRegisterMetaType(this, DictionaryToScriptValue, DictionaryFromScriptValue);
    globalObject().setProperty("Dictionary", newQMetaObject(&QObject::staticMetaObject, newFunction(DictionaryConstructor)));

    // Объявим класс DBFactory
    qScriptRegisterMetaType(this, DBFactoryToScriptValue, DBFactoryFromScriptValue);

    // Объявим класс MySqlRelationalTableModel
    qScriptRegisterMetaType(this, MySqlRelationalTableModelToScriptValue, MySqlRelationalTableModelFromScriptValue);
    globalObject().setProperty("SqlRelationalTableModel", newQMetaObject(&QObject::staticMetaObject, newFunction(MySqlRelationalTableModelConstructor)));

}

int ScriptEngine::showError(QString text) {
    return TApplication::exemplar()->getGUIFactory()->showError(text);
}
