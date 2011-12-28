#ifndef MYSCRIPTENGINE_H
#define MYSCRIPTENGINE_H

#include <QtScript>
#include <QScriptEngine>
#include "essence.h"

class Essence;

class MyScriptEngine {
public:
    MyScriptEngine(Essence*);
    bool setScript(QString scr);
    void setErrorReportFileName(QString name) { errorReportFileName = name; }
    bool evaluate();
private:
    Essence* parent;
    QString script;
    QString errorReportFileName;
    QScriptEngine engine;
};

#endif // MYSCRIPTENGINE_H
