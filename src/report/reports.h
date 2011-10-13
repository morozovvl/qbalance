#ifndef REPORTS_H
#define REPORTS_H

#include <QMap>
#include "../kernel/dictionaries.h"
#include "report.h"

class Reports : public Dictionaries
{
public:
    QMap<QString, Report*> reports;                    // Объекты отчетов
    Reports();
};

#endif // REPORTS_H
