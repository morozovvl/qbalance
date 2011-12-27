#ifndef CONFIGFORM_H
#define CONFIGFORM_H
#include <QFrame>
#include "form.h"

class ConfigForm : public Form
{
    Q_OBJECT
public:
    ConfigForm(QObject* parent = NULL);
    bool open(QWidget* pwgt = 0);
    void close();
public slots:
    void dispatch(QTreeWidgetItem*, int);
private:
    QFrame* frame;
    void dictAdd();
    void dictProperties();
    void dictColumns();
    void dictPermissions();
};

#endif // CONFIGFORM_H
