#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptValue>
#include <QScriptEngine>

class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    virtual int showError(QString);
private:
};


#endif // SCRIPTENGINE_H
