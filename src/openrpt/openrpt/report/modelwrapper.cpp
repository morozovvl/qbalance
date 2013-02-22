#include "modelwrapper.h"
#include <QtSql>
#include <QModelIndex>

TModelWrapper::TModelWrapper(const QAbstractItemModel* model)
{
    setModel(model);
    Position = QSql::BeforeFirstRow;
    Aggregator = new TAggregator(this);
}

TModelWrapper::~TModelWrapper()
{
    if (Aggregator)
    {
        delete Aggregator;
        Aggregator = NULL;
    }
}

 QVariant TModelWrapper::value(int field) const
{
    QVariant result;

    if (field >= 0 && Position >= 0 && Model)
    {
        QModelIndex index = Model->index(Position, field);

        result = Model->data(index);
    }

    return result;
}

 QVariant TModelWrapper::value(const QString & field) const
{
    return value(headerSection(field));
}

int TModelWrapper::headerSection(const QString& name) const
{
    int result = -1;

//    qDebug() << Model->columnCount();

    for(int i = 0; i < Model->columnCount(); ++i)
    {
//        qDebug() << Model->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
//        qDebug() << Model->headerData(0, Qt::Horizontal, Qt::EditRole).toString();

        if (Model->headerData(i, Qt::Horizontal).toString() == name)
        {
            result = i;
            break;
        }
    }

    return result;
}

bool TModelWrapper::first()
{
    bool result = false;

    if (size() > 0)
    {
        Position = 0;

        Aggregator->reset(TAggregator::Static, true);
        Aggregator->reset(TAggregator::Dynamic, true);

        result = true;
    }
    return result;
}

bool TModelWrapper::next()
{
    bool result = false;

    if (at() < size())
        ++Position;

    if (Position >= size())
        Position = QSql::AfterLastRow;
    else
    {
        Aggregator->process(Aggregator->currentValues(), TAggregator::Addition);
        result = true;
    }

    return result;
}

bool TModelWrapper::previous()
{
    bool result = false;

    if (Position >= 0)
    {
        result = true;

        Aggregator->process(Aggregator->currentValues(), TAggregator::Subtraction);
    }

    return result;
}

int TModelWrapper::findFirst(int field, const QVariant& target)
{
    int result = -1;

    for (first(); result < 0; next())
    {
        if (value(field) == target)
          result = at();
    }

    return result;
}

int TModelWrapper::findFirst(int field, int target)
{
    return findFirst(field, QVariant(target));
}

int TModelWrapper::findFirst(const QString & field, int target)
{
    return findFirst(headerSection(field), QVariant(target));
}

int TModelWrapper::findFirst(const QString & field, const QString & target)
{
    return findFirst(headerSection(field), QVariant(target));
}

void TModelWrapper::trackFieldTotal(QString & field)
{
    Aggregator->track(field);
}

double TModelWrapper::getFieldTotal(QString & field)
{
    return Aggregator->value(TAggregator::Static, field);
}

double TModelWrapper::getFieldSubTotal(QString & field)
{
    return Aggregator->value(TAggregator::Dynamic, field);
}

void TModelWrapper::resetSubTotals()
{
    Aggregator->reset(TAggregator::Dynamic);
}

void TModelWrapper::resetSubTotalsCurrent()
{
    Aggregator->reset(TAggregator::Dynamic, true);
}

QString TModelWrapper::fieldName(const int &index) const
{
    return Model->headerData(index, Qt::Horizontal).toString();
}

int TModelWrapper::count() const
{
    return Model->columnCount();
}
