#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QVariant>

class IDataSource
{
public:
    virtual ~IDataSource() {}

    virtual bool isValid()                            const = 0;

    virtual int at()                                  const = 0;

    virtual int size()                                const = 0;

    virtual QVariant value(int field)                 const = 0;
    virtual QVariant value(const QString & field)     const = 0;

    virtual bool first()                                    = 0;
    virtual bool next()                                     = 0;
    virtual bool previous()                                 = 0;

    virtual int count()                               const = 0;

    virtual QString fieldName(const int& index)       const = 0;
    virtual int findFirst(int field, int target)            = 0;
    virtual int findFirst(const QString& field, int target)           = 0;
    virtual int findFirst(const QString& field, const QString&target) = 0;

    virtual void trackFieldTotal(QString & field)           = 0;
    virtual double getFieldTotal(QString & field)           = 0;
    virtual double getFieldSubTotal(QString & field)        = 0;
    virtual void resetSubTotals()                           = 0;
    virtual void resetSubTotalsCurrent()                    = 0;
};

#endif // DATASOURCE_H
