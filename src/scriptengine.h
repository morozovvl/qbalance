#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValue>
#include <QScriptEngine>
#include "custom.h"
//#include "gui/form.h"

class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    virtual int showError(QString);
//    void setParentForm(Form* parent) { parentForm = parent; }
//    Form* getParentForm() { return parentForm; }
private:
//    Form* parentForm;
};


#endif // SCRIPTENGINE_H
