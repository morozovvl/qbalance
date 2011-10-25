#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptValue>
#include <QScriptEngine>

class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QString file = "", QObject *parent = 0);
    bool open();
    void showError(QString);
protected:
    virtual void loadScriptObjects();
private:
    QString     scriptFile;
};


#endif // SCRIPTENGINE_H
