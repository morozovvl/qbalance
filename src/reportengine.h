#ifndef REPORTENGINE_H
#define REPORTENGINE_H

#include <QObject>
#include <QString>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptContext>
#include "essence.h"

class Essence;

class ReportEngine : public QObject {
    Q_OBJECT
public:
    ReportEngine(Essence*, QString);
    QScriptEngine* getEngine() { return engine; }
    QScriptValue* getContext() { return &context; }
    Q_INVOKABLE virtual bool open();
private:
    Essence* parent;
    QScriptEngine* engine;
    QString reportName;
    QString scriptFileName;
    QString templateFileName;
    QScriptValue context;

    void loadContextFunctions();
};

#endif // REPORTENGINE_H
