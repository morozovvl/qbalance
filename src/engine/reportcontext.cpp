#include "reportcontext.h"


ReportContext::ReportContext(QMap<QString, QVariant>* d, QObject *parent/* = 0*/) :
    QObject(parent)
{
    data = d;
}


QVariant ReportContext::getValue(QString tag)
{
    return data->value(tag);
}


void ReportContext::setValue(QString tag, QVariant val)
{
    if (data->contains(tag))
    {
        data->remove(tag);
    }
    data->insert(tag, val);
}
