#ifndef MYPLUGINS_H
#define MYPLUGINS_H

#include "pictureplugin.h"
#include "tableviewplugin.h"
#include "searchparametersplugin.h"
#include "docparametersplugin.h"
#include "numericeditplugin.h"

#include <QtDesigner/QtDesigner>
#include <QtCore/qplugin.h>

class MyPlugins: public QObject, public QDesignerCustomWidgetCollectionInterface {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    MyPlugins(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};

#endif // MYPLUGINS_H
