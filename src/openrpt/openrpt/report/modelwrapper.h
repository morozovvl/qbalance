#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H

#include <datasource.h>
#include <valueaggregator.h>
#include <QAbstractItemModel>

class TModelWrapper : public IDataSource
{
private:
    const QAbstractItemModel*  Model;
    TAggregator*         Aggregator;
    int                  Position;
private:
    int headerSection(const QString& name) const;
    int findFirst(int field, const QVariant& target);
public:
    TModelWrapper(const QAbstractItemModel* model = NULL);
    ~TModelWrapper();

    void setModel(const QAbstractItemModel* value)               { Model = value                                      ; }

    const QAbstractItemModel* model()                      const { return Model                                       ; }

    virtual bool isValid()                            const
    {
        return Position >= 0 && Model && Model->rowCount() ;
    }

    virtual int at()                                  const
    {
        return Position                                    ;
    }

    virtual int size()                                const
    {
        return Model->rowCount()                           ;
    }

    virtual QVariant value(int field)                 const;
    virtual QVariant value(const QString & field)     const;

    virtual bool first()                                   ;
    virtual bool next()                                    ;
    virtual bool previous()                                ;

    virtual QString fieldName(const int &index)       const;

    virtual int count()                               const;

    virtual int findFirst(int field, int target)                         ;
    virtual int findFirst(const QString & field, int target)             ;
    virtual int findFirst(const QString & field, const QString & target) ;

    virtual void trackFieldTotal(QString & field)                        ;
    virtual double getFieldTotal(QString & field)                        ;
    virtual double getFieldSubTotal(QString & field)                     ;
    virtual void resetSubTotals()                                        ;
    virtual void resetSubTotalsCurrent()                                 ;
};

#endif // MODELWRAPPER_H
