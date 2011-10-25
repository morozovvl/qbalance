#ifndef REPORTSCRIPENGINE_H
#define REPORTSCRIPENGINE_H
#include <QMap>
#include "scriptengine.h"
#include "reportcontext.h"


class ReportScriptEngine : public ScriptEngine
{
public:
    ReportScriptEngine(QMap<QString, QVariant>*, QString, QObject *parent = 0);
protected:
    virtual void loadScriptObjects();
private:
    ReportContext*  reportContext;
};

#endif // REPORTSCRIPENGINE_H
