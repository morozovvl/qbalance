#ifndef REPORTSCRIPENGINE_H
#define REPORTSCRIPENGINE_H
#include <QMap>
#include "scriptengine.h"


class ReportScriptEngine : public ScriptEngine
{
public:
    ReportScriptEngine(QMap<QString, QVariant>*, QString, QObject *parent = 0);
private:
    QMap<QString, QVariant>* printContext;
};

#endif // REPORTSCRIPENGINE_H
