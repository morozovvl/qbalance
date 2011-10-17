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
    ReportEngine(Essence*, QMap<QString, QVariant>*, QString, QString);
    virtual bool open() { return true; }
protected:
    Essence*                    parent;
    QMap<QString, QVariant>*    printContext;
    QString                     reportName;
    QString                     reportExt;
};

#endif // REPORTENGINE_H
