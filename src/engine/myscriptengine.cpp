#include "myscriptengine.h"

extern QString programErrorFileName;

MyScriptEngine::MyScriptEngine(Essence* par) {
    parent = par;
    errorReportFileName = programErrorFileName;
}

bool MyScriptEngine::setScript(QString scr) {
    script = scr;
    return true;
}

bool MyScriptEngine::evaluate() {
    if (script.size() > 0) {
        if (engine.canEvaluate(script)) {
            engine.setProperty("abc", 125);
            QScriptValue value = engine.evaluate(script, errorReportFileName);
//            if (engine.hasUncaughtException())      // произошла ошибка во время выполнения скрипта выполнения
//                return false;
            if (value.isError()) {
                parent->showError(value.toString());
                return false;
            }
            qDebug() << value.toVariant();
            return true;
        }
        else
            parent->showError(QObject::tr("Ошибка в синтаксисе формул."));
    }
    return false;
}

