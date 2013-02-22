#ifndef WRAPPER_H
#define WRAPPER_H

#include "report_global.h"

class QAbstractItemModel;
class IDataSource;

class REPORT_EXPORT TWrapper
{
public:
    static IDataSource* wrap(const QAbstractItemModel* model);
protected:
    TWrapper();
};

#endif // WRAPPER_H
