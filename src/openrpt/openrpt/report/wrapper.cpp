#include "wrapper.h"
#include "modelwrapper.h"
#include <QAbstractItemModel>

TWrapper::TWrapper()
{
}

IDataSource* TWrapper::wrap(const QAbstractItemModel* model)
{
    return new TModelWrapper(model);
}
