#ifndef REPORTSCRIPENGINE_H
#define REPORTSCRIPENGINE_H
#include <QMap>
#include "scriptengine.h"
#include "reportcontext.h"


class ReportScriptEngine : public ScriptEngine
{
public:
    ReportScriptEngine(QMap<QString, QVariant>*, QString, QObject *parent = 0);
    virtual bool open();
private:
    ReportContext*  reportContext;
    QString         reportFileName;
};

#endif // REPORTSCRIPENGINE_H
