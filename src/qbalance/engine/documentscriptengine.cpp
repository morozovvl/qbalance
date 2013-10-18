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

#include "documentscriptengine.h"
#include "../kernel/document.h"
#include "../kernel/documents.h"


// класс Documents
Q_DECLARE_METATYPE(Documents*)

QScriptValue DocumentsConstructor(QScriptContext *context, QScriptEngine *engine) {
     Documents *object = new Documents(context->argument(0).toInteger());
     return engine->newQObject(object, QScriptEngine::QtOwnership);
}


QScriptValue DocumentsToScriptValue(QScriptEngine *engine, Documents* const &in) {
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}


void DocumentsFromScriptValue(const QScriptValue &object, Documents* &out) {
    out = qobject_cast<Documents*>(object.toQObject());
}


// класс Document
Q_DECLARE_METATYPE(Document*)

QScriptValue DocumentConstructor(QScriptContext *context, QScriptEngine *engine) {
    Documents* docs;
    DocumentsFromScriptValue(context->argument(1), docs);
    Document *object = new Document(context->argument(0).toInteger(), docs);
    return engine->newQObject(object, QScriptEngine::QtOwnership);
}

QScriptValue DocumentToScriptValue(QScriptEngine *engine, Document* const &in) {
    return engine->newQObject(in, QScriptEngine::QtOwnership);
}

void DocumentFromScriptValue(const QScriptValue &object, Document* &out) {
    out = qobject_cast<Document*>(object.toQObject());
}


QScriptValue getDictionary(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue dictName = context->argument(0);
    if (dictName.isString() && engine->evaluate("document").isValid())
    {
        QScriptValue value = engine->evaluate(QString("document.getDictionary('%1')").arg(dictName.toString()));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getSaldo(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue acc = context->argument(0);
    if (acc.isString() && engine->evaluate("document").isValid())
    {
        QScriptValue value = engine->evaluate(QString("document.getSaldo('%1')").arg(acc.toString()));
        if (value.isValid())
            return value;
    }
    return QScriptValue();
}


QScriptValue getSumValue(QScriptContext* context, QScriptEngine* engine) {
    return engine->evaluate(QString("document.getSumValue('%1')").arg(context->argument(0).toString()));
}


QScriptValue saveVariable(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(1).isString())
        return engine->evaluate(QString("document.saveVariable('%1', %2)").arg(context->argument(0).toString()).arg(context->argument(1).toString()));
    else
        return engine->evaluate(QString("document.saveVariable('%1', '%2')").arg(context->argument(0).toString()).arg(context->argument(1).toString()));
}


QScriptValue restoreVariable(QScriptContext* context, QScriptEngine* engine) {
    return engine->evaluate(QString("document.restoreVariable('%1')").arg(context->argument(0).toString()));
}


DocumentScriptEngine::DocumentScriptEngine(QObject* parent/* = 0*/)
:ScriptEngine(parent)
{
}


void DocumentScriptEngine::loadScriptObjects()
{
    ScriptEngine::loadScriptObjects();
    qScriptRegisterMetaType(this, DocumentsToScriptValue, DocumentsFromScriptValue);
    globalObject().setProperty("Documents", newQMetaObject(&QObject::staticMetaObject, newFunction(DocumentsConstructor)));
    qScriptRegisterMetaType(this, DocumentToScriptValue, DocumentFromScriptValue);
    globalObject().setProperty("Document", newQMetaObject(&QObject::staticMetaObject, newFunction(DocumentConstructor)));
    globalObject().setProperty("getDictionary", newFunction(getDictionary));
    globalObject().setProperty("getSaldo", newFunction(getSaldo));
    globalObject().setProperty("getSumValue", newFunction(getSumValue));
    globalObject().setProperty("saveVariable", newFunction(saveVariable));
    globalObject().setProperty("restoreVariable", newFunction(restoreVariable));
}


// События
void DocumentScriptEngine::eventAppendFromQuery(int number, QSqlRecord* values)
{
    // Сначала преобразуем данные в записи к виду, пригодному для передачи в скрипты
    QScriptValue row = newObject();
    for (int i = 0; i < values->count(); i++)
        row.setProperty(values->fieldName(i), QScriptValue(this, values->value(i).toString()));

    // Подготовим номер запроса и запись с данными запроса для передачи в скрипт через параметры функции
    QScriptValueList args;
    args << newVariant(QVariant(number));
    args << row;
    globalObject().property("EventAppendFromQuery").call(QScriptValue(), args);
}


QMap<QString, EventFunction>* DocumentScriptEngine::getEventsList()
{
    ScriptEngine::getEventsList();
    EventFunction func;
    func.comment = QObject::trUtf8("Событие происходит в момент изменения постоянного справочника документа");
    appendEvent("EventParametersChanged()", func);
    func.comment = QObject::trUtf8("Событие происходит перед добавлением строки в документ");
    appendEvent("EventBeforeAddString()", func);
    func.comment = QObject::trUtf8("Событие происходит после добавления строки в документ");
    appendEvent("EventAfterAddString()", func);
    func.comment = QObject::trUtf8("Событие происходит после вычисления в ячейке");
    appendEvent("EventAfterCalculate()", func);
    func.comment = QObject::trUtf8("Вызывается при добавлении новой записи из запроса");
    appendEvent("EventAppendFromQuery(id, record)", func);
    return &eventsList;
}


