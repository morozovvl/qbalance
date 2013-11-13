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

#include <QtGui/QWidget>
#include <QtGui/QFont>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include "tableview.h"
#include "formgrid.h"
#include "formdocument.h"
#include "docparameters.h"
#include "../kernel/document.h"
#include "../kernel/essence.h"
#include "../kernel/dictionary.h"
#include "../kernel/documents.h"

#define LABEL_ITOG     QObject::trUtf8("Итого:")
#define LABEL_DATE     QObject::trUtf8("Дата:")
#define LABEL_NUMBER   QObject::trUtf8("Номер:")


FormDocument::FormDocument(): FormGrid()
{
    dateEdit = 0;
    numberEdit = 0;
    parameters = 0;
    itogNumeric = 0;
    buttonQueryAdd = 0;
    queriesMenu = 0;
}


FormDocument::~FormDocument()
{
}


void FormDocument::createForm(QString fileName, QWidget* pwgt/* = 0*/)
{
    FormGrid::createForm(fileName, pwgt);
    // Подключим кнопку "Добавить из запроса"
    if (parent != 0)
    {
        if (defaultForm)
        {
            buttonQueryAdd = new QPushButton();
            buttonQueryAdd->setObjectName("buttonQueryAdd");
            cmdButtonLayout->insertWidget(1, buttonQueryAdd);
        }
        else
        {
            if (formWidget != 0)
            {
                buttonQueryAdd = (QPushButton*)qFindChild<QPushButton*>(formWidget, "buttonQueryAdd");
            }
        }
        if (buttonQueryAdd != 0)
        {
            connect(buttonQueryAdd, SIGNAL(clicked()), this, SLOT(cmdQueryAdd()));
            // Если для этой типовой операции имеются запросы к БД, позволяющие автоматически заполнять документ
            QSqlQuery queries = db->getDocumentAddQueriesList(getParent()->getOperNumber());
            if (queries.size() > 0)
            {
                queriesMenu = new QMenu(formWidget);    // то создадим меню со списком возможных запросов
                while (queries.next())
                {
                    QAction* action = new QAction(queries.value(0).toString(), queriesMenu);
                    action->setData(queries.value(1).toInt());
                    queriesMenu->addAction(action);
                }
                buttonQueryAdd->show();                 // и покажем кнопку заполнения документа из запроса
            }
            else
                buttonQueryAdd->hide();     // в противном случае скроем ее
        }
    }

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
            itogNumeric = new MyNumericEdit();
            itogNumeric->setReadOnly(true);
            QFont font = itogNumeric->font();
            font.setBold(true);
            font.setPointSize(font.pointSize() + 2);
            itogNumeric->setFont(font);
            itogNumeric->setObjectName("itogNumeric");
            phbxItogLayout->addWidget(itogNumeric, 0, Qt::AlignRight);
            QVBoxLayout* pvbxItogLayout = new QVBoxLayout();
            pvbxItogLayout->addLayout(phbxItogLayout);
            pvbxItogLayout->addStretch(1);
            imageLayout->addLayout(pvbxItogLayout);
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
        buttonCancel->hide();
    }
    else
    {
        if (docParams)
        {
            parameters = (DocParameters*)qFindChild<QFrame*>(formWidget, "docParameters");
        }
        dateEdit = qFindChild<QDateEdit*>(formWidget, "dateEdit");
        numberEdit = qFindChild<QLineEdit*>(formWidget, "numberEdit");
        itogNumeric = (MyNumericEdit*)qFindChild<QLineEdit*>(formWidget, "itogNumeric");
    }
    if (parameters != 0)
    {
        parameters->setDictionaries(getParent()->getDictionaries());
        parameters->setFormDocument(this);
        parameters->setApp(app);
        foreach (QString dictName, getParent()->getDictionaries()->keys())
        {
            if (getParent()->getDictionaries()->value(dictName)->isConst())
            {
                parameters->addString(dictName);
            }
        }
    }
    // Если в документе должна быть только одна строка, то заблокируем кнопки "Добавить" и "Удалить"
    if (getParent()->getIsSingleString())
    {
        if (buttonAdd != 0)
            buttonAdd->hide();
        if (buttonQueryAdd != 0)
            buttonQueryAdd->hide();
        if (buttonDelete != 0)
            buttonDelete->hide();
    }
}


void FormDocument::show()
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
    FormGrid::show();
}


void FormDocument::hide()
{
    FormGrid::hide();
    getParent()->saveVariablesToDB();
}


void FormDocument::cmdDelete()
{
    FormGrid::cmdDelete();
}


void FormDocument::cmdOk()
{
    FormGrid::cmdOk();
    if (getParent() != 0)
    {
        if (dateEdit != 0)
            getParent()->getParent()->setValue("дата", QVariant(dateEdit->date()));
        if (numberEdit != 0)
            getParent()->getParent()->setValue("номер", QVariant(numberEdit->text()));
        getParent()->getParent()->getForm()->setGridFocus();
    }
}


void FormDocument::cmdCancel()
{
    FormGrid::cmdCancel();
    if (getParent() != 0)
    {
        getParent()->getParent()->getForm()->setGridFocus();
    }
}


void FormDocument::cmdQueryAdd()
{
    QAction* action = queriesMenu->exec(formWidget->mapToGlobal(QPoint(cmdButtonLayout->contentsRect().x() + 100, cmdButtonLayout->contentsRect().y()-queriesMenu->height())));
    if (action != 0)
    {
        if (getParent()->addFromQuery(action->data().toInt()) > 0)
            buttonDelete->setDisabled(false);
    }
}


void FormDocument::parametersChangedEvent()
{
    if (getParent()->getScriptEngine() != 0) {
        getParent()->getScriptEngine()->eventParametersChanged();
    }
}


void FormDocument::setEnabled(bool enabled)
{
    FormGrid::setEnabled(enabled);
    dateEdit->setReadOnly(!enabled);
    numberEdit->setReadOnly(!enabled);
    if (parameters != 0)
        parameters->setEnabled(enabled);
    if (queriesMenu != 0)
        queriesMenu->setEnabled(enabled);
}


