#ifndef AGGREAGATOR_H
#define AGGREAGATOR_H

#include <QMap>
#include <QString>

#include <datasource.h>

class TAggregator
{
public:
    enum Kind{
        Static  //Total
    ,   Dynamic //SubTotal
    };

    enum Operation{
        Addition
    ,   Subtraction
    };

    typedef QMap<QString, double> Container;
private:

    static const double NullValue = 0.0;


public:
    TAggregator(IDataSource* source = NULL)
    {
        Source = source;

        Q_ASSERT(Source);
    }

    Container currentValues() const
    {
        Container result;

        makeReset(result, false);

        return result;
    }

    void process(const Container& values, const Operation& operation)
    {
        switch(operation)
        {
            case Addition:
                for (Container::const_iterator i = values.constBegin(); i != values.constEnd(); ++i)
                {
                    StaticAggregate[i.key()]  += i.value();
                    DynamicAggregate[i.key()] += i.value();
                }; break;
            case Subtraction:
                for (Container::const_iterator i = values.constBegin(); i != values.constEnd(); ++i)
                {
                    StaticAggregate[i.key()]  -= i.value();
                    DynamicAggregate[i.key()] -= i.value();
                }; break;
        }
    }

    void track(const QString& field)
    {
        if (StaticAggregate.contains(field))
            StaticAggregate[field] = NullValue;

        if (DynamicAggregate.contains(field))
            DynamicAggregate[field] = NullValue;

    }

    void reset(const TAggregator::Kind& track_kind, const bool& current = false)
    {
        makeReset(track_kind == TAggregator::Static ? StaticAggregate : DynamicAggregate, current);
    }

    double value(const TAggregator::Kind& track_kind, const QString& field) const
    {
        double result = 0.0;
        const Container& container = track_kind == TAggregator::Static ? StaticAggregate
                                                                       : DynamicAggregate;

        if (container.contains(field))
            result = container.value(field);

        return result;
    }
private:
    void makeReset(Container& container, const bool& current) const
    {
        if (current && Source && Source->isValid())
            for (Container::iterator i = container.begin(); i != container.end(); ++i)
                i.value() = Source->value(i.key()).toDouble();
        else
            for (Container::iterator i = container.begin(); i != container.end(); ++i)
                i.value() = NullValue;
    }

private:
    IDataSource* Source;
    Container    StaticAggregate;
    Container    DynamicAggregate;
};

#endif // AGGREAGATOR_H
