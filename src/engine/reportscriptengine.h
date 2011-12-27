#ifndef REPORTSCRIPENGINE_H
#define REPORTSCRIPENGINE_H
#include <QMap>
#include "scriptengine.h"
#include "reportcontext.h"


class ReportScriptEngine : public ScriptEngine
{
public:
    ReportScriptEngine(QMap<QString, QVariant>*, QObject *parent = 0);
    ~ReportScriptEngine();
protected:
    virtual void loadScriptObjects();
private:
    ReportContext*  reportContext;
};

#endif // REPORTSCRIPENGINE_H
