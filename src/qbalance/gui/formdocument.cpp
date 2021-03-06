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

#include <QtCore/QtGlobal>

#include <QtGui/QFont>
#include "formgrid.h"
#include "formdocument.h"
#include "docparameters.h"
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "../kernel/essence.h"
#include "../kernel/dictionary.h"
#include "../kernel/documents.h"
#include "../gui/dialog.h"
#include "../gui/tableview.h"
#include "../gui/mynumericedit.h"
#include "../storage/dbfactory.h"
#include "../engine/documentscriptengine.h"

#define LABEL_ITOG     QObject::trUtf8("Итого:")
#define LABEL_DATE     QObject::trUtf8("Дата:")
#define LABEL_NUMBER   QObject::trUtf8("Номер:")


FormDocument::FormDocument(): FormGrid()
{
    dateEdit = 0 /*nullptr*/;
    numberEdit = 0 /*nullptr*/;
    parameters = 0 /*nullptr*/;
    itogNumeric = 0 /*nullptr*/;
    textEdit = 0 /*nullptr*/;
    buttonQueryAdd = 0 /*nullptr*/;
    queriesMenu = 0 /*nullptr*/;
    parent = 0 /*nullptr*/;
    formWidget = 0 /*nullptr*/;
}


FormDocument::~FormDocument()
{
}


void FormDocument::close()
{
    if (dateEdit != 0 /*nullptr*/)
        disconnect(dateEdit, SIGNAL(editingFinished()), this, SLOT(saveDate()));

    if (numberEdit != 0 /*nullptr*/)
        disconnect(numberEdit, SIGNAL(editingFinished()), this, SLOT(saveNumber()));

    FormGrid::close();
}


Document* FormDocument::getParent(bool)
{
    return static_cast<Document*>(parent);
}


QDateEdit* FormDocument::getDateEdit()
{
    return dateEdit;
}


QLineEdit* FormDocument::getNumberEdit()
{
    return numberEdit;
}


void FormDocument::showParameterText(QString dictName)
{
    if (parameters != 0 /*nullptr*/)
        parameters->showText(dictName);
}


void FormDocument::showTextEdit(bool show)
{
    textEdit->setVisible(show);
}


DocParameters*  FormDocument::getDocParameters()
{
    return parameters;
}


QPushButton* FormDocument::getButtonQueryAdd()
{
    return buttonQueryAdd;
}


void FormDocument::createForm(QString fileName, QWidget* pwgt)
{
    FormGrid::createForm(fileName, pwgt);
    // Подключим кнопку "Добавить из запроса"
    if (parent != 0 /*nullptr*/)
    {
        if (defaultForm)
        {
            buttonQueryAdd = insertButton("buttonQueryAdd", 1);
        }
        else
        {
            if (formWidget != 0 /*nullptr*/)
            {
                buttonQueryAdd = static_cast<QPushButton*>(formWidget->findChild("buttonQueryAdd"));
            }
        }
        if (buttonQueryAdd != 0 /*nullptr*/)
        {
            connect(buttonQueryAdd, SIGNAL(clicked()), this, SLOT(cmdQueryAdd()));

            queriesMenu = new QMenu(formWidget);    // Создадим меню со списком возможных запросов

            QSqlQuery queries = db->getDocumentAddQueriesList(getParent()->getOperNumber());
            if (queries.size() > 0)
            {
                while (queries.next())
                {
                    addQueryMenuAction(queries.value(0).toString(), queries.value(2).toString());
                }
            }
            else
                buttonQueryAdd->hide();     // в противном случае скроем ее
        }
    }

    bool docParams = false;

    if (formWidget != 0 /*nullptr*/)
        formWidget->resize(600, formWidget->height());

    foreach (QString dictName, getParent()->getDictionariesList()->keys())
    {   // Просмотрим список справочников, с которыми работает форма документа
        if (getParent()->getDictionariesList()->value(dictName)->isConst())
        {   // Если есть хоть один справочник текущее значение которого одинаково для всех строк табличной части
            docParams = true;   // то создадим виджет с параметрами документа
            break;
        }
    }
    if (defaultForm)
    {
        if (vbxLayout != 0 /*nullptr*/)
        {
            // Вставим текстовое содержимое документа

            textEdit = new QTextEdit();
            QFontMetrics m(textEdit->font());
            int rowHeight = m.lineSpacing();
            textEdit->setFixedHeight(5 * rowHeight);    // В комментарии покажем 4 строки
            textEdit->setObjectName("commentText");
            textEdit->setVisible(false);
            vbxLayout->insertWidget(2, textEdit);

            // Вставим строчку "Итого"
            QHBoxLayout* phbxItogLayout = new QHBoxLayout();
//            phbxItogLayout->setObjectName("phbxItogLayout");
//            QSpacerItem* docItogSpacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
//            phbxItogLayout->addItem(docItogSpacer);
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
//            pvbxItogLayout->addStretch(1);
            imageLayout->addLayout(pvbxItogLayout);

            if (docParams)
            {
                parameters = new DocParameters();
                parameters->setObjectName("docParameters");
            }
            if (parameters != 0 /*nullptr*/)
            {
                QHBoxLayout* phbxLayout = new QHBoxLayout();
                phbxLayout->setObjectName("phbxLayout");
                phbxLayout->insertWidget(0, parameters);
                if (vbxLayout != 0 /*nullptr*/)
                {
                    vbxLayout->insertLayout(0, phbxLayout);
                }
            }
            QHBoxLayout* hbxDateLayout = new QHBoxLayout();
            hbxDateLayout->setObjectName("hbxDateLayout");
            hbxDateLayout->addWidget(new QLabel(LABEL_DATE, formWidget));
            dateEdit = new QDateEdit();
            dateEdit->setObjectName("dateEdit");
            dateEdit->setDisplayFormat(app->dateFormat());
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
    else if (formWidget != 0 /*nullptr*/)
    {
        if (docParams)
        {
            parameters = static_cast<DocParameters*>(formWidget->findChild("docParameters"));
        }
        dateEdit        = static_cast<QDateEdit*>(formWidget->findChild("dateEdit"));
        numberEdit      = static_cast<QLineEdit*>(formWidget->findChild("numberEdit"));
        itogNumeric     = static_cast<MyNumericEdit*>(formWidget->findChild("itogNumeric"));
        textEdit        = static_cast<QTextEdit*>(formWidget->findChild("commentText"));
    }
    if (parameters != 0 /*nullptr*/)
    {
        parameters->setDictionaries(getParent()->getDictionariesList());
        parameters->setFormDocument(this);
        parameters->setApp(app);
        foreach (QString dictName, getParent()->getDictionariesList()->keys())
        {
            if (getParent()->getDictionariesList()->value(dictName)->isConst())
            {
                if (!(dictName.left(9) == "документы" && dictName.size() > 9))
                    parameters->addString(dictName);
            }
        }
    }

    // Если в документе должна быть только одна строка, то заблокируем кнопки "Добавить" и "Удалить"
    if (getParent()->getIsSingleString())
    {
        if (buttonAdd != 0 /*nullptr*/)
            buttonAdd->hide();
        if (buttonQueryAdd != 0 /*nullptr*/)
            buttonQueryAdd->hide();
        if (buttonDelete != 0 /*nullptr*/)
            buttonDelete->hide();
    }

    if (dateEdit != 0 /*nullptr*/)
    {
        dateEdit->setDisplayFormat(app->dateFormat());
        connect(dateEdit, SIGNAL(editingFinished()), this, SLOT(saveDate()));
    }

    if (numberEdit != 0 /*nullptr*/)
        connect(numberEdit, SIGNAL(editingFinished()), this, SLOT(saveNumber()));

}


void FormDocument::show()
{
    if (dateEdit != 0 /*nullptr*/)
        dateEdit->setDate(db->toDate(getParent()->getParent()->getValue("ДАТА")));
    if (numberEdit != 0 /*nullptr*/)
        numberEdit->setText(getParent()->getParent()->getValue("НОМЕР").toString());
    if (itogNumeric != 0 /*nullptr*/)
        itogNumeric->setValue(getParent()->getParent()->getValue("СУММА"));
    if (parameters != 0 /*nullptr*/)
    {
        foreach (QString dictName, parameters->getKeys())
            parameters->showText(dictName);
    }
    if (textEdit != 0 /*nullptr*/)
        textEdit->setText(getParent()->getParent()->getValue("описание").toString());

    FormGrid::show();
    if (parent->getCurrentRow() + 1 > parent->rowCount())
    {
        grdTable->selectRow(parent->rowCount() - 1);
        if (grdTable->columnIsReadOnly())
            grdTable->selectNextColumn();
    }
}


void FormDocument::hide()
{
    FormGrid::hide();
    getParent()->saveVariablesToDB();
}


void FormDocument::cmdOk()
{
    if (getParent() != 0 /*nullptr*/)
    {
        getParent()->getParent()->getGrdTable()->setFocus();
        if (dateEdit->date() < app->getBeginDate() || dateEdit->date() > app->getEndDate())
        {
            app->showError(QObject::trUtf8("Документ сохранен на пределами рабочего периода"));
            cmdQuery();
        }
    }
    FormGrid::cmdOk();
}


void FormDocument::cmdCancel()
{
    FormGrid::cmdCancel();
    if (getParent() != 0 /*nullptr*/)
    {
        getParent()->getParent()->getGrdTable()->setFocus();
    }
}


void FormDocument::cmdQueryAdd()
{
    QAction* action = queriesMenu->exec(formWidget->mapToGlobal(QPoint(cmdButtonLayout->contentsRect().x() + 100, cmdButtonLayout->contentsRect().y()-queriesMenu->height())));
    if (action != 0 /*nullptr*/)
    {
        getParent()->addFromQuery(action->data().toString().trimmed());
    }
    grdTable->setFocus();
    setButtons();
}


void FormDocument::parametersChangedEvent()
{
    if (getParent()->getScriptEngine() != 0 /*nullptr*/) {
        getParent()->getScriptEngine()->eventParametersChanged();
    }
}


void FormDocument::setEnabled(bool enabled)
{
    FormGrid::setEnabled(enabled);
    dateEdit->setReadOnly(!enabled);
    numberEdit->setReadOnly(!enabled);
    if (textEdit != 0 /*nullptr*/)
        textEdit->setEnabled(!enabled);
    if (parameters != 0 /*nullptr*/)
        parameters->setEnabled(enabled);
    if (queriesMenu != 0 /*nullptr*/)
        queriesMenu->setEnabled(enabled);
}


void FormDocument::saveDate()
{
    getParent()->setDate(dateEdit->text());
}


void FormDocument::saveNumber()
{
    getParent()->setNumber(numberEdit->text());
}


void FormDocument::addQueryMenuAction(QString name, QString comment)
{
    if (queriesMenu != 0 /*nullptr*/)
    {
        QAction* action = new QAction(comment, queriesMenu);
        action->setData(name);
        queriesMenu->addAction(action);
        buttonQueryAdd->show();                 // Покажем кнопку заполнения документа из запроса
    }
    else
        app->showError("На форме документа не найдена кнопка \"Добавить из запроса\"");
}
