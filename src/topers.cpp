#include <QString>
#include "app.h"
#include "topers.h"
#include "gui/formgridsearch.h"

extern App* app;

Topers::Topers(QObject *parent): Dictionary("vw_доступ_к_топер", parent) {
    configName = formTitle;
    topersProperties = app->getDBFactory()->getTopersProperties();
}

QVariant Topers::getToperProperty(int operNumber, QString property) {
    if (topersProperties.first()) {
        do {
            QSqlRecord rec = topersProperties.record();
            if (rec.field("опер").value().toInt() == operNumber)
                return rec.field(property).value();
        } while (topersProperties.next());
    }
    return "";
}

void Topers::cmdOk() {
    addDocuments(getValue("опер").toInt());
}

void Topers::addDocuments(int opNumber) {
    if (opNumber > 0) {
        Documents* doc = app->getDocuments(opNumber);
        if (doc != NULL) {
            doc->show();
        }
    }
}
