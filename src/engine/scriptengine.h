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
    explicit ScriptEngine(QString file = "", QObject *parent = 0);
    ~ScriptEngine();
    bool open();
    void showError(QString);
protected:
    virtual void loadScriptObjects();
private:
    QString             scriptFile;
    SqlQueryClass*      sqlQueryClass;
    SqlRecordClass*     sqlRecordClass;
    SqlFieldClass*      sqlFieldClass;
};


#endif // SCRIPTENGINE_H
