#ifndef REPORT_H
#define REPORT_H

#include "report_global.h"

class TReport_private;
class QDomDocument;
class IDataSource;
class QString;

class REPORT_EXPORT TReport {
public:
    TReport();

    ~TReport();

    void setReport(const QDomDocument& value);
    QDomDocument& report() const;

    void setDataSource(const QString& name, IDataSource* source);
    IDataSource* dataSource(const QString& name) const;

    void preview();

    void print();

private:
    TReport_private* pd;
};

#endif // REPORT_H
