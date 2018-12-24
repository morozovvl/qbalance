#include "myuiloader.h"
#include "dialog.h"
#include "searchparameters.h"
#include "tableview.h"
#include "picture.h"

MyUiLoader::MyUiLoader(QObject *parent) :  QUiLoader(parent)
{
}

QWidget* MyUiLoader::createWidget(const QString& className, QWidget* parent, const QString& name)
{
    if (className == "Dialog")
    {
        Dialog* d = new Dialog(parent);
        d->setObjectName(name);
        return d;
    }
    else if (className == "SearchParameters")
    {
        SearchParameters* s = new SearchParameters(parent);
        s->setObjectName(name);
        return s;
    }
    else if (className == "TableView")
    {
        TableView* t = new TableView();
        t->setObjectName(name);
        return t;
    }

    else if (className == "Picture")
    {
        Picture* p = new Picture(parent);
        p->setObjectName(name);
        return p;
    }

    return QUiLoader::createWidget(className, parent, name);
}
