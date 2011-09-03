#include <QHBoxLayout>
#include "../app.h"
#include "../dictionary.h"
#include "formgridsearch.h"
#include "searchparameters.h"

#define LABEL_SEARCH_PARAMETERS     tr("Параметры для поиска:")

extern QString programIdFieldName;
extern QString programNameFieldName;

bool FormGridSearch::open(QWidget* pwgt, Essence* parent) {
    if (FormGrid::open(pwgt, parent)) {
        formWidget->resize(600, formWidget->height());
        if (defaultForm) {
            if (vbxLayout != 0) {
                QHBoxLayout* hbxLayout = new QHBoxLayout();
                parameters = new SearchParameters();
                parameters->setObjectName("searchParameters");
                hbxLayout->insertWidget(0, parameters);
                QLabel* label = new QLabel(LABEL_SEARCH_PARAMETERS, formWidget);
                hbxLayout->insertWidget(0, label);
                vbxLayout->insertLayout(0, hbxLayout);
            }
        }
        else {
            parameters = (SearchParameters*)qFindChild<QFrame*>(formWidget, "searchParameters");
        }
        if (parameters != 0) {
            parameters->setApp(app);
            parameters->setParent(formWidget);
            parameters->setFormGrid(this);
            parameters->setProgramIdFieldName(programIdFieldName);
            parameters->setProgramNameFieldName(programNameFieldName);
            parameters->setFieldsList(parent->getFieldsList());
            connect(parameters, SIGNAL(requery()), this, SLOT(cmdRequery()));
        }
        return true;
    }
    return false;
}

void FormGridSearch::close() {
    if (!defaultForm)
        if (parameters != 0) {
            disconnect(parameters, 0, 0, 0);
            parameters->close();
        }
    FormGrid::close();
}

void FormGridSearch::query(QString param) {
    param = "";
    if (parameters != 0) {
        parameters->getParameters(searchParameters);
        for (int i = 0; i < searchParameters.size(); i++) {
            if ((searchParameters[i].field == programNameFieldName) && searchParameters[i].value.toString().size() > 0) {
                QString str = searchParameters[i].value.toString().trimmed() + " ";
                while (str.contains("  "))                    // Уберем лишние пробелы
                    str.replace("  ", " ");
                while (str.size() > 0) {
                    if (param.size() > 0)
                        param.append(" AND ");
                    param.append(searchParameters[i].table).append("." + programNameFieldName).append(" ILIKE '%" + str.left(str.indexOf(' ')) + "%'");
                    str = str.remove(0, str.indexOf(' ') + 1);
                }
            }
        }
    }
    FormGrid::query(param);
}

void FormGridSearch::setShowFocus() {
    FormGrid::setShowFocus();
    if (parameters != 0)
        parameters->setFocus();
}

QDomElement FormGridSearch::createWidgetsStructure() {
    QDomDocument doc;
    QDomElement vboxLayout = FormGrid::createWidgetsStructure();
    if (vbxLayout != 0) {
        QDomElement item, widget, hlayout;
        hlayout = doc.createElement("layout");
        hlayout.setAttribute("class", "QHBoxLayout");
        widget = createLabelElement(LABEL_SEARCH_PARAMETERS);
        item = doc.createElement("item");
        item.appendChild(widget);
        hlayout.appendChild(item);
        if (parameters != 0) {
            widget = doc.createElement("widget");
            widget.setAttribute("class", parameters->metaObject()->className());
            widget.setAttribute("name", parameters->objectName());
            item = doc.createElement("item");
            item.appendChild(widget);
            hlayout.appendChild(item);
        }
        item = doc.createElement("item");
        item.appendChild(hlayout);
        vboxLayout.insertBefore(item, QDomNode());
    }
    return vboxLayout;
}

