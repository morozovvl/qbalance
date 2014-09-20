/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "../kernel/app.h"
#include "../kernel/dictionary.h"
#include "formgridsearch.h"
#include "searchparameters.h"

#define LABEL_SEARCH_PARAMETERS     QObject::trUtf8("Параметры для поиска:")

FormGridSearch::FormGridSearch(QObject* parent/* = 0*/) : FormGrid(parent)
{
    parameters = 0;
}


FormGridSearch::~FormGridSearch()
{
}


void FormGridSearch::createForm(QString fileName, QWidget* pwgt/* = 0*/)
{
    FormGrid::createForm(fileName, pwgt);
    formWidget->resize(600, formWidget->height());
    if (defaultForm)
    {
        if (vbxLayout != 0)
        {
            QHBoxLayout* hbxLayout = new QHBoxLayout();
            parameters = new SearchParameters();
            parameters->setObjectName("searchParameters");
            hbxLayout->insertWidget(0, parameters);
            QLabel* label = new QLabel(LABEL_SEARCH_PARAMETERS, formWidget);
            hbxLayout->insertWidget(0, label);
            vbxLayout->insertLayout(0, hbxLayout);
        }
    }
    else
    {
        parameters = (SearchParameters*)formWidget->findChild("searchParameters");
    }
    if (parameters != 0)
    {
        parameters->setDictionaries(((Dictionary*)parent)->getDictionaries());
        parameters->setParent(formWidget);
        parameters->setApp(app);
        parameters->setFormGrid(this);
        parameters->setProgramIdFieldName(db->getObjectName("код").toLower());
        parameters->setProgramNameFieldName(db->getObjectName("имя").toLower());
        parameters->setFieldsList(parent->getFieldsList());
        connect(parameters, SIGNAL(requery()), this, SLOT(cmdRequery()));
    }
}


void FormGridSearch::close()
{
    writeSettings();
    if (defaultForm)
    {
        if (parameters != 0)
        {
            parameters->close();
//            delete parameters;
        }
    }
    FormGrid::close();
}


void FormGridSearch::setParameter(QString tableName, QString parameter)
{
    parameters->setParameter(tableName, parameter);
}


QString FormGridSearch::getFilter()
{
    if (parameters != 0)
        return parameters->getFilter();
    return QString();
}


void FormGridSearch::activateWidget()
{
    if (parameters != 0)
        parameters->setFocus();
}


void FormGridSearch::clearAllComboBoxes()
{
    parameters->clearAllComboBoxes();
}


