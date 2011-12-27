#include "myplugins.h"

MyPlugins::MyPlugins(QObject *parent) : QObject(parent) {
    widgets.append(new PicturePlugin(this));
    widgets.append(new TableViewPlugin(this));
    widgets.append(new SearchParametersPlugin(this));
    widgets.append(new DocParametersPlugin(this));
    widgets.append(new MyNumericEditPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> MyPlugins::customWidgets() const {
    return widgets;
}

Q_EXPORT_PLUGIN2(myplugins, MyPlugins)
