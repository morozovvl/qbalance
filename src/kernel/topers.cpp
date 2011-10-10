#include <QString>
#include "topers.h"
#include "../gui/app.h"
#include "../gui/formgridsearch.h"

Topers::Topers(QObject *parent): Dictionary("vw_доступ_к_топер", parent) {
    topersProperties = TApplication::exemplar()->getDBFactory()->getTopersProperties();
}


QVariant Topers::getToperProperty(int operNumber, QString property)
{
    QVariant result;
    QSqlRecord record;

    for (topersProperties.first(); topersProperties.isValid(); topersProperties.next())
    {
        record = topersProperties.record();
        if (record.field("опер").value().toInt() == operNumber)
        {
            result = record.field(property).value();
            break;
        }
    }
    return result;
}


void Topers::cmdOk() {
    addDocuments(getValue("опер").toInt());
}

void Topers::addDocuments(int opNumber) {
    if (opNumber > 0) {
        Documents* doc = TApplication::exemplar()->getDocuments(opNumber);
        if (doc != NULL) {
            doc->show();
        }
    }
}
