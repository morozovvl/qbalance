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

#include <QString>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QSizePolicy>
#include <QFrame>
#include <QLayout>
#include <QKeyEvent>
#include "searchparameters.h"
#include "../kernel/dictionary.h"
#include "../kernel/dictionaries.h"
#include "formgrid.h"
#include "formgridsearch.h"
#include "../kernel/essence.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"

SearchParameters::SearchParameters(QWidget* parentWidget): QFrame(parentWidget) {
    gridLayout = 0;
    dictionaries = 0;
    app = 0;
}

void SearchParameters::close() {
    for(int i = gridLayout->rowCount() - 1; i >= 0; i--)
        removeString(i);
}


void SearchParameters::setApp(TApplication* a)
{
    app = a;
    dictionaries = app->getDictionaries();
}

void SearchParameters::setFieldsList(QStringList fldList) {
    setLineWidth(2);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    gridLayout = new QGridLayout(this);
    int strNum = 0;
    for (int i = 0; i < fldList.count(); i++) {
        QString field = fldList.at(i);
// Непонятно, для чего здесь  && !parentForm->getParent()->relationsIsEmpty()
//        if (field.toLower() == programNameFieldName ||
//            (field.left(4).toLower() == (programIdFieldName + "_") && !parentForm->getParent()->relationsIsEmpty()))                          // Если это поле - столбец ИМЯ, то это справочник
            if (field.toLower() == programNameFieldName ||
                (field.left(4).toLower() == (programIdFieldName + "_")))                          // Если это поле - столбец ИМЯ, то это справочник
            addString(field, strNum++);                 // следовательно должна быть строка для поиска по наименованию
    }
    setLayout(gridLayout);
    gridLayout->setColumnStretch(1, 1);
}

void SearchParameters::addString(QString name, int strNum) {
    QString labelName;
    MyComboBox* comboBox = new MyComboBox(parentWidget());
    comboBox->setEditable(true);
    comboBox->setInsertPolicy(MyComboBox::InsertAtTop);
    comboBox->setFocusPolicy(Qt::StrongFocus);
    connect(comboBox, SIGNAL(enterPressed(QWidget*)), this, SLOT(comboBoxEnterPressed(QWidget*)));
    gridLayout->addWidget(comboBox, strNum, 1, 1, 1);
    if (name.toLower() != programNameFieldName) {      // Параметр name в этом методе может принимать значения только либо ИМЯ, либо "КОД_..."
                                        // поэтому в эту точку можно попасть, если name = "КОД_..."
        name.remove(0, 4);              // выделим из ссылки на справочник имя связанного справочника
        name = name.toLower();
        QPushButton* button = new QPushButton("...", parentWidget());   // Создадим пользовательскую кнопку для связанного справочника
        button->setObjectName(name);                    // Запомним в кнопке имя связанного справочника, чтобы потом извлечь его в слоте
        button->setFixedSize(comboBox->height() * 1.2, comboBox->height());
        button->setFocusPolicy(Qt::NoFocus);            // Запретим переход на кнопку по клавише TAB
        gridLayout->addWidget(button, strNum, 2, 1, 1);
        connect(button, SIGNAL(clicked()), this, SLOT(dictionaryButtonPressed()));
        name = name + "." + programNameFieldName;
        if (app != 0)
        {
            labelName = app->getDBFactory()->getDictionariesProperties(name).value("имя_в_форме").toString();
            if (labelName.size() == 0)
                labelName = name;
        }
    }
    else {
        name = parentForm->getParent()->getTableName() + "." + programNameFieldName;
        if (app != 0)
        {
            labelName = app->getDBFactory()->getDictionariesProperties(parentForm->getParent()->getTableName()).value("имя_в_форме").toString();
            if (labelName.size() == 0)
                labelName = "Наименование";
        }
    }
    comboBox->setObjectName(name);
    parameters << name;
    QLabel* label = new QLabel(labelName + ":", parentWidget());
    gridLayout->addWidget(label, strNum, 0, 1, 1, Qt::AlignRight);
}

void SearchParameters::removeString(int strNum) {
    QWidget* widget;
    if (gridLayout->itemAtPosition(strNum, 0) != 0) {
        widget = gridLayout->itemAtPosition(strNum, 0)->widget();
        if (widget != 0)
            gridLayout->removeWidget(widget);
    }
    if (gridLayout->itemAtPosition(strNum, 1) != 0) {
        widget = gridLayout->itemAtPosition(strNum, 1)->widget();       // удалим ComboBox
        if (widget != 0) {
            disconnect(widget, 0, 0, 0);
            gridLayout->removeWidget(widget);
        }
    }
    if (gridLayout->itemAtPosition(strNum, 2) != 0) {
        widget = gridLayout->itemAtPosition(strNum, 2)->widget();       // удалим PushButton
        if (widget != 0) {
            disconnect(widget, 0, 0, 0);
            gridLayout->removeWidget(widget);
        }
    }
}

QVector<sParam> SearchParameters::getParameters() {
    QVector<sParam> param;
    for(int i = 0; i < parameters.size(); i++) {
        QString field = parameters.at(i);
        MyComboBox* cmb = (MyComboBox*)qFindChild<QComboBox*>(this, field);
        QString text = cmb->currentText().trimmed();
        while (text.contains("  ")) // Если есть пробелы, идущие подряд
            text.replace("  ", " "); // то уберем их
        sParam par;
        par.table = field.replace("." + programNameFieldName, "");
        par.field = programNameFieldName;
        par.value = text;
        if (text.size() > 0)
            param.append(par);
    }
    return param;
}


QString SearchParameters::getFilter()
{
    DBFactory* db = app->getDBFactory();
    QString filter;
    QVector<sParam> searchParameters = getParameters();
    for (int i = 0; i < searchParameters.size(); i++) {
        QString text = searchParameters[i].value.toString();
        QStringList paramList = text.split(QRegExp("\\s+"));
        foreach (QString param, paramList)
        {
            if (filter.size() > 0)
                filter.append(" AND ");
            filter.append(QString("%1.%2 ILIKE '%3'").arg(db->getObjectName(searchParameters[i].table))
                                                     .arg(db->getObjectName(searchParameters[i].field))
                                                     .arg("%" + param + "%"));
        }
    }
    return filter;
}


void SearchParameters::dictionaryButtonPressed() {
    if (dictionaries != 0)
    {
        dictionaries->addDictionary(sender()->objectName(), 0);
        Dictionary* dict = dictionaries->getDictionary(sender()->objectName());    // Поместим связанный справочник в список справочников приложения
        if (dict != 0) {
            dict->exec();
            if (dict->isFormSelected()) {
                MyComboBox* cmb = (MyComboBox*)qFindChild<QComboBox*>(this, sender()->objectName() + "." + programNameFieldName);
                QString text = dict->getValue(programNameFieldName).toString();
                int index = cmb->findText(text);
                if (index > 0)
                    cmb->setCurrentIndex(index);
                else {
                    cmb->insertItem(0, text);
                    cmb->setCurrentIndex(0);
                }
            }
        }
    }
}


void SearchParameters::comboBoxEnterPressed(QWidget* wdgt) {    // Была нажата кнопка Enter на одной из ComboBox
    int i = 0;
    while (i < gridLayout->rowCount()) {                        // Пока мы не достигли последней ComboBox в параметрах поиска
        if (gridLayout->itemAtPosition(i, 1)->widget()->objectName() == wdgt->objectName()) {   // На этой ComboBox была нажата Enter
            if ((i + 1) < gridLayout->rowCount())                               // Если ниже есть еще одна ComboBox
                gridLayout->itemAtPosition(i + 1, 1)->widget()->setFocus();     // то переставим фокус на нее
            else
                requery();
        }
        i++;
    }
}


void SearchParameters::setFocus() {
    if (gridLayout != 0 && gridLayout->rowCount() > 0) {
        QWidget* widget = gridLayout->itemAtPosition(0, 1)->widget();
        widget->setFocus();
    }
}
