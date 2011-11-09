#ifndef FORMSCRIPTENGINE_H
#define FORMSCRIPTENGINE_H
#include "scriptengine.h"


class FormScriptEngine : public ScriptEngine
{
public:
    FormScriptEngine(QObject *parent = 0);
protected:
    virtual void loadScriptObjects();
};

#endif // FORMSCRIPTENGINE_H
