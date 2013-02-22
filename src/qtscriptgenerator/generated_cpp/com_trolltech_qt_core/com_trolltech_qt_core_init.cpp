#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QFutureSynchronizerVoid_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFuture_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFutureIterator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFutureWatcher_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFutureVoid_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFutureWatcherVoid_class(QScriptEngine *engine);
QScriptValue qtscript_create_QFutureSynchronizer_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_core_class_names[] = {
    "QFutureSynchronizerVoid"
    , "QFuture"
    , "QFutureIterator"
    , "QFutureWatcher"
    , "QFutureVoid"
    , "QFutureWatcherVoid"
    , "QFutureSynchronizer"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_core_class_functions[] = {
    qtscript_create_QFutureSynchronizerVoid_class
    , qtscript_create_QFuture_class
    , qtscript_create_QFutureIterator_class
    , qtscript_create_QFutureWatcher_class
    , qtscript_create_QFutureVoid_class
    , qtscript_create_QFutureWatcherVoid_class
    , qtscript_create_QFutureSynchronizer_class
};

void qtscript_initialize_com_trolltech_qt_core_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 7; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_core_class_names[i],
            qtscript_com_trolltech_qt_core_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
