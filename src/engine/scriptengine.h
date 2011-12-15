#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptValue>
#include <QScriptEngine>
#include "sqlqueryclass.h"
#include "sqlrecordclass.h"
#include "sqlfieldclass.h"


class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    ~ScriptEngine();
    bool open(QString fileName = "");
    bool evaluate();
    QString getErrorMessage() { return errorMessage; }
    bool getScriptResult() { return scriptResult; }
protected:
    virtual void loadScriptObjects();
private:
    bool                scriptResult;
    QString             script;
    QString             errorMessage;
    QString             scriptFileName;
    SqlQueryClass*      sqlQueryClass;
    SqlRecordClass*     sqlRecordClass;
    SqlFieldClass*      sqlFieldClass;
};


#endif // SCRIPTENGINE_H
