#ifndef OOREPORTENGINE_H
#define OOREPORTENGINE_H
#include <QMap>
#include "../kernel/essence.h"
#include "reportengine.h"



class OOReportEngine : public ReportEngine
{
public:
    OOReportEngine(QMap<QString, QVariant>* context, QString name, QString ext);
    virtual bool open();
};

#endif // OOREPORTENGINE_H
