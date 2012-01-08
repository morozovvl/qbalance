#ifndef DOCUMENTSCRIPTENGINE_H
#define DOCUMENTSCRIPTENGINE_H

#include <QScriptValue>
#include "scriptengine.h"


class DocumentScriptEngine : public ScriptEngine
{
public:
    DocumentScriptEngine(QObject *parent = 0);
// События
    void eventParametersChanged();
    static QList<EventFunction>* getEventsList();
protected:
    virtual void loadScriptObjects();
};

#endif // DOCUMENTSCRIPTENGINE_H
