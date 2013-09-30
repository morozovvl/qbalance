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

#include <QtCore/QString>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSizePolicy>
#include <QtGui/QFrame>
#include <QtGui/QLayout>
#include <QtGui/QKeyEvent>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
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


SearchParameters::~SearchParameters()
{
}


void SearchParameters::close() {
//    delete gridLayout;
}


void SearchParameters::setApp(TApplication* a)
{
    app = a;
    dictionaries = app->getDictionaries();
}


void SearchParameters::setFieldsList(QStringList fldList)
{
    setLineWidth(2);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    gridLayout = new QGridLayout(this);
    int strNum = 0;
    for (int i = 0; i < fldList.count(); i++)
    {
        QString field = fldList.at(i);
        if (field.toLower() == programNameFieldName)
        {
            addString(field, strNum++);
        }
        else if (field.left(4).toLower() == (programIdFieldName + "_"))                          // Если это поле - столбец ИМЯ, то это справочник
        {
            QString tableName = field;
            tableName = tableName.remove(programIdFieldName + "_", Qt::CaseInsensitive).toLower();
            if (app->getDictionaries()->getDictionary(tableName) != 0)
                addString(field, strNum++);                 // следовательно должна быть строка для поиска по наименованию
        }
    }
    setLayout(gridLayout);
    gridLayout->setColumnStretch(1, 1);
}


void SearchParameters::addString(QString name, int strNum)
{
    QString labelName;
    MyComboBox* comboBox = new MyComboBox(parentWidget());
    comboBox->setEditable(true);
    comboBox->setInsertPolicy(MyComboBox::InsertAtTop);
    comboBox->setFocusPolicy(Qt::StrongFocus);
    connect(comboBox, SIGNAL(enterPressed(QWidget*)), this, SLOT(comboBoxEnterPressed(QWidget*)));
    gridLayout->addWidget(comboBox, strNum, 1, 1, 1);
    if (name.toLower() != programNameFieldName)
    {      // Параметр name в этом методе может принимать значения только либо ИМЯ, либо "КОД_..."
                                        // поэтому в эту точку можно попасть, если name = "КОД_..."
        name.remove(0, 4);              // выделим из ссылки на справочник имя связанного справочника
        name = name.toLower();
        QPushButton* button = new QPushButton("...", parentWidget());   // Создадим пользовательскую кнопку для связанного справочника
        button->setObjectName(name);                    // Запомним в кнопке имя связанного справочника, чтобы потом извлечь его в слоте
        button->setFixedSize(comboBox->height() * 1.2, comboBox->height());
        button->setFocusPolicy(Qt::NoFocus);            // Запретим переход на кнопку по клавише TAB
        gridLayout->addWidget(button, strNum, 2, 1, 1);
        connect(button, SIGNAL(clicked()), this, SLOT(dictionaryButtonPressed()));
        if (app != 0)
        {
            labelName = app->getDBFactory()->getDictionariesProperties(name).value("имя_в_форме").toString();
            name = name + "." + programNameFieldName;
            if (labelName.size() == 0)
            {
                labelName = name;
            }
        }
    }
    else
    {
        name = parentForm->getParent()->getTableName();
        if (app != 0)
        {
            labelName = "Наименование";
        }
        // Проверим, имеется ли в связанном справочнике полнотекстовый поиск
        if (((Dictionary*)parentForm->getParent())->isFtsEnabled())
        {
            QCheckBox* checkBox = new QCheckBox(QObject::trUtf8("ПТП"), parentWidget());
            checkBox->setToolTip(QObject::trUtf8("Использовать ПолноТекстовый Поиск"));
            checkBox->setTristate(false);
            checkBox->setObjectName(parentForm->getParent()->getTableName());                    // Запомним в кнопке имя связанного справочника, чтобы потом извлечь его в слоте
            gridLayout->addWidget(checkBox, strNum, 2, 1, 1);
        }
    }
    comboBox->setObjectName(name);
    parameters << name;
    QLabel* label = new QLabel(labelName + ":", parentWidget());
    gridLayout->addWidget(label, strNum, 0, 1, 1, Qt::AlignRight);
}


QVector<sParam> SearchParameters::getParameters()
{
    QVector<sParam> param;
    for(int i = 0; i < parameters.size(); i++)
    {
        QString field = parameters.at(i);
        MyComboBox* cmb = (MyComboBox*)qFindChild<QComboBox*>(this, field);
        QString text = cmb->currentText().trimmed();
        while (text.contains("  ")) // Если есть пробелы, идущие подряд
            text.replace("  ", " "); // то уберем их
        sParam par;
        par.table = field.replace("." + programNameFieldName, "");
        par.field = programNameFieldName;
        par.value = text;
        // Определим, включен ли полнотекстовый поиск
        QCheckBox* chb = (QCheckBox*)qFindChild<QCheckBox*>(this, field);
        par.isFtsEnabled = (chb != 0 ? chb->isChecked(): false);
        param.append(par);
    }
    return param;
}


QString SearchParameters::getFilter()
{
    QString filter;
    QVector<sParam> searchParameters = getParameters();
    for (int i = 0; i < searchParameters.size(); i++)
    {
        QString text = searchParameters[i].value.toString();
        QStringList paramList = text.split(QRegExp("\\s+"));
        if (searchParameters[i].isFtsEnabled && searchParameters[i].value.toString().size() > 0)   // Если включен полнотектовый поиск
        {
            if (filter.size() > 0)
                filter.append(" AND ");
            filter.append(QString("%1.fts @@ to_tsquery('").arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table)));
            QString f = "";
            foreach (QString param, paramList)
            {
                if (f.size() > 0)
                    f.append("&");
                f.append(param);
            }
            filter.append(f + "')");
        }
        else
        { // Если полнотекстовый поиск отключен
            foreach (QString param, paramList)
            {
                if (param.size() > 0)
                {
                    if (filter.size() > 0)
                        filter.append(" AND ");
                    filter.append(QString("%1.%2 ILIKE '%3'").arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table))
                                                             .arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table + "." + searchParameters[i].field))
                                                             .arg("%" + param + "%"));
                }
            }
        }
    }
    return filter;
}


void SearchParameters::dictionaryButtonPressed()
{
    if (dictionaries != 0)
    {
        Dictionary* dict = dictionaries->getDictionary(sender()->objectName(), 0);    // Поместим связанный справочник в список справочников приложения
        if (dict != 0) {
            dict->exec();
            if (dict->isFormSelected())
            {
                MyComboBox* cmb = (MyComboBox*)qFindChild<QComboBox*>(this, sender()->objectName() + "." + programNameFieldName);
                QString text = dict->getValue(programNameFieldName).toString().trimmed();
                int index = cmb->findText(text);
                if (index > 0)
                    cmb->setCurrentIndex(index);
                else
                {
                    cmb->insertItem(0, text);
                    cmb->setCurrentIndex(0);
                }
                cmb->lineEdit()->selectAll();
                cmb->setFocus();
            }
        }
    }
}


void SearchParameters::comboBoxEnterPressed(QWidget* wdgt)
{    // Была нажата кнопка Enter на одной из ComboBox
    int i = 0;
    while (i < gridLayout->rowCount())
    {                        // Пока мы не достигли последней ComboBox в параметрах поиска
        MyComboBox* cmb = (MyComboBox*)gridLayout->itemAtPosition(i, 1)->widget();
        if (cmb->objectName() == wdgt->objectName())
        {   // На этой ComboBox была нажата Enter
            if ((i + 1) < gridLayout->rowCount())                               // Если ниже есть еще одна ComboBox
            {
                cmb = (MyComboBox*)gridLayout->itemAtPosition(i + 1, 1)->widget();
                cmb->lineEdit()->selectAll();
                cmb->setFocus();     // то переставим фокус на нее
            }
            else
                requery();
        }
        i++;
    }
}


void SearchParameters::setFocus()
{
    if (gridLayout != 0 && gridLayout->rowCount() > 0)
    {
        // При активации фокуса подсветим все строчки
        for (int i = 0; i < gridLayout->rowCount(); i++)
        {
            MyComboBox* widget = (MyComboBox*)(gridLayout->itemAtPosition(i, 1)->widget());
            widget->lineEdit()->selectAll();
            if (i == 0)
                widget->setFocus();
        }
    }
}


void SearchParameters::keyPressEvent(QKeyEvent *event)
{
    parentForm->keyPressEvent(event);
}


