#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptValue>
#include <QScriptEngine>

class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    virtual bool open() { return true; }
    virtual int showError(QString);
    QScriptValue* getScriptContext() { return &scriptContext; }
protected:
    QScriptValue scriptContext;
};


#endif // SCRIPTENGINE_H
