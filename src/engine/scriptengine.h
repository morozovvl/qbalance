#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptValue>
#include <QScriptEngine>
#include "sqlqueryclass.h"
#include "sqlrecordclass.h"
#include "sqlfieldclass.h"


struct EventFunction {
    QString     name;
    QString     comment;
};


class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    ~ScriptEngine();
    bool open(QString fileName = "");
    bool evaluate();
    QString getErrorMessage() { return errorMessage; }
    bool getScriptResult() { return scriptResult; }
// События
    static QList<EventFunction>* getEventsList();
    static QString getBlankScripts();
    void eventInitForm();
    void eventBeforeShowForm();
    void eventAfterHideForm();
    void eventCloseForm();
protected:
    static QList<EventFunction> eventsList;          // Список доступных в скриптах событий с комментариями
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
