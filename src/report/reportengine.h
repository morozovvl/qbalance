#ifndef REPORTENGINE_H
#define REPORTENGINE_H

#include <QObject>
#include <QString>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptContext>
#include "../kernel/essence.h"

class Essence;

class ReportEngine : public QObject {
    Q_OBJECT
public:
    ReportEngine(Essence*, QString);
    Q_INVOKABLE virtual bool open();
private:
    Essence*                    parent;
    QScriptEngine*              scriptEngine;
    QMap<QString, QVariant>*    printContext;
    QString                     reportName;
    QString                     reportExt;
    void openExternEngine();
};

#endif // REPORTENGINE_H
