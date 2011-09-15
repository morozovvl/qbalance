#include <QWidget>
#include <QFont>
#include "formdocument.h"
#include "docparameters.h"
#include "../document.h"
#include "../essence.h"
#include "../dictionary.h"
#include "../documents.h"

#define LABEL_ITOG     tr("Итого:")
#define LABEL_DATE     tr("Дата:")
#define LABEL_NUMBER   tr("Номер:")


extern QString programMaxSumMask;
extern QString programIdFieldName;
extern QString programNameFieldName;


FormDocument::FormDocument()
: FormGrid()
, dateEdit(NULL)
, numberEdit(NULL)
, parameters(NULL)
, itogNumeric(NULL)
{
}


void FormDocument::createForm(QString fileName, QWidget* pwgt/* = 0*/)
{
    FormGrid::createForm(fileName, pwgt);

    bool docParams = false;
    formWidget->resize(600, formWidget->height());
    foreach (QString dictName, getParent()->getDictionaries()->keys())
    {   // Просмотрим список справочников, с которыми работает форма документа
        if (getParent()->getDictionaries()->value(dictName)->isConst())
        {   // Если есть хоть один справочник текущее значение которого одинаково для всех строк табличной части
            docParams = true;   // то создадим виджет с параметрами документа
            break;
        }
    }
    if (defaultForm)
    {
        if (vbxLayout != 0)
        {
            // Вставим строчку "Итого"
            QHBoxLayout* phbxItogLayout = new QHBoxLayout();
            phbxItogLayout->setObjectName("phbxItogLayout");
            phbxItogLayout->addStretch(1);
            phbxItogLayout->addWidget(new QLabel(LABEL_ITOG, formWidget), 0, Qt::AlignRight);
            // Создадим и вставим строчку с ИТОГО документа
            itogNumeric = new NumericEdit();
            itogNumeric->setReadOnly(true);
            QFont font = itogNumeric->font();
            font.setBold(true);
            font.setPointSize(font.pointSize() + 2);
            itogNumeric->setFont(font);
            itogNumeric->setObjectName("itogNumeric");
            phbxItogLayout->addWidget(itogNumeric, 0, Qt::AlignRight);
            vbxLayout->insertLayout(1, phbxItogLayout);
            if (docParams)
            {
                parameters = new DocParameters();
                parameters->setObjectName("docParameters");
            }
            if (parameters != 0)
            {
                QHBoxLayout* phbxLayout = new QHBoxLayout();
                phbxLayout->setObjectName("phbxLayout");
                phbxLayout->insertWidget(0, parameters);
                if (vbxLayout != 0)
                {
                    vbxLayout->insertLayout(0, phbxLayout);
                }
            }
            QHBoxLayout* hbxDateLayout = new QHBoxLayout();
            hbxDateLayout->setObjectName("hbxDateLayout");
            hbxDateLayout->addWidget(new QLabel(LABEL_DATE, formWidget));
            dateEdit = new QDateEdit();
            dateEdit->setObjectName("dateEdit");
            dateEdit->setDisplayFormat("dd.MM.yyyy");
            hbxDateLayout->addWidget(dateEdit);
            hbxDateLayout->addWidget(new QLabel(LABEL_NUMBER, formWidget));
            numberEdit = new QLineEdit();
            numberEdit->setObjectName("numberEdit");
            hbxDateLayout->addWidget(numberEdit);
            hbxDateLayout->addStretch(1);
            vbxLayout->insertLayout(0, hbxDateLayout);
        }
    }
    else
    {
        if (docParams)
        {
            parameters = (DocParameters*)qFindChild<QFrame*>(formWidget, "docParameters");
        }
        dateEdit = qFindChild<QDateEdit*>(formWidget, "dateEdit");
        numberEdit = qFindChild<QLineEdit*>(formWidget, "numberEdit");
        itogNumeric = (NumericEdit*)qFindChild<QLineEdit*>(formWidget, "itogNumeric");
    }
    if (parameters != 0)
    {
        parameters->setDictionaries(getParent()->getDictionaries());
        parameters->setFormDocument(this);
        parameters->setApp(app);
        parameters->setProgramIdFieldName(programIdFieldName);
        parameters->setProgramNameFieldName(programNameFieldName);
        foreach (QString dictName, getParent()->getDictionaries()->keys())
        {
            if (getParent()->getDictionaries()->value(dictName)->isConst())
            {
                parameters->addString(dictName);
            }
        }
    }
}


void FormDocument::doShow()
{
    if (dateEdit != 0)
        dateEdit->setDate(getParent()->getParent()->getValue("дата").toDate());
    if (numberEdit != 0)
        numberEdit->setText(getParent()->getParent()->getValue("номер").toString());
    if (itogNumeric != 0)
        itogNumeric->setValue(getParent()->getParent()->getValue("сумма"));
    if (parameters != 0)
    {
        foreach (QString dictName, parameters->getKeys())
            parameters->showText(dictName);
    }
    FormGrid::doShow();
}


void FormDocument::doHide()
{
    getParent()->getParent()->getForm()->getForm()->activateWindow();
    FormGrid::doHide();
}


void FormDocument::remove()
{
    FormGrid::remove();
    getParent()->calculate(QModelIndex());
}


void FormDocument::cmdOk()
{
    if (dateEdit != 0)
        getParent()->getParent()->setValue("дата", QVariant(dateEdit->date()));
    if (numberEdit != 0)
        getParent()->getParent()->setValue("номер", QVariant(numberEdit->text()));
    if (itogNumeric != 0)
        getParent()->getParent()->setValue("сумма", QVariant(itogNumeric->getValue()));
    FormGrid::cmdOk();
}


QDomElement FormDocument::createWidgetsStructure()
{
    QDomDocument doc;
    QDomElement vboxLayout = FormGrid::createWidgetsStructure();
    if (vbxLayout != 0)
    {
        QDomElement item, widget, layout, hlayout, element;
        if (itogNumeric != 0)
            for (int i = 0; vboxLayout.childNodes().count(); i++)
            {
                item = vboxLayout.childNodes().at(i).firstChildElement("widget");
                if (!item.isNull())
                {
                   layout = item.firstChildElement("layout");
                    if (!layout.isNull() && layout.attribute("name").compare("cmdButtonLayout", Qt::CaseSensitive) == 0)
                    {
                        hlayout = doc.createElement("layout");
                        hlayout.setAttribute("class", "QHBoxLayout");
                        hlayout.setAttribute("name", "phbxItogLayout");

                        item = doc.createElement("item");
                        item.appendChild(createHStretchElement());
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(createLabelElement(LABEL_ITOG));
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(createLineEditElement(itogNumeric));
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(hlayout);

                        vboxLayout.insertBefore(item, vboxLayout.childNodes().at(i));

                        if (parameters != 0)
                        {
                            widget = doc.createElement("widget");
                            widget.setAttribute("class", parameters->metaObject()->className());
                            widget.setAttribute("name", parameters->objectName());
                            item = doc.createElement("item");
                            item.appendChild(widget);
                            vboxLayout.insertBefore(item, QDomNode());
                        }

                        hlayout = doc.createElement("layout");
                        hlayout.setAttribute("class", "QHBoxLayout");

                        item = doc.createElement("item");
                        item.appendChild(createLabelElement(LABEL_DATE));
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(createDateEditElement(dateEdit));
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(createLabelElement(LABEL_NUMBER));
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(createLineEditElement(numberEdit));
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(createHStretchElement());
                        hlayout.appendChild(item);

                        item = doc.createElement("item");
                        item.appendChild(hlayout);
                        vboxLayout.insertBefore(item, QDomNode());
                        break;
                    }
                }
            }
    }
    return vboxLayout;
}

