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
#include "formgrid.h"
#include "formgridsearch.h"
#include "searchparameters.h"
#include "../kernel/dictionary.h"
#include "../kernel/dictionaries.h"
#include "../kernel/essence.h"
#include "../kernel/app.h"
#include "../storage/dbfactory.h"
#include "../gui/mycombobox.h"

SearchParameters::SearchParameters(QWidget* parentWidget): QFrame(parentWidget) {
    dictionaries = 0;
    app = 0;
    gridLayout = 0;
}


SearchParameters::~SearchParameters()
{
}


void SearchParameters::setProgramIdFieldName(QString s)
{
    programIdFieldName = s;
}


void SearchParameters::setProgramNameFieldName(QString s)
{
    programNameFieldName = s;
}


void SearchParameters::setDictionaries(Dictionaries* dicts)
{
    dictionaries = dicts;
}


int SearchParameters::getParametersCount()
{
    return parameters.count();
}


void SearchParameters::close() {
}


void SearchParameters::setApp(TApplication* a)
{
    app = a;
}


void SearchParameters::setFieldsList(QStringList fldList)
{
    setLineWidth(1);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    int strNum = 0;
    if (gridLayout == 0)
    {
        gridLayout = new QGridLayout(this);
        gridLayout->setVerticalSpacing(1);
        setLayout(gridLayout);
    }
    else
    {
       strNum = gridLayout->rowCount();
    }
    for (int i = 0; i < fldList.count(); i++)
    {
        QString field = fldList.at(i);
        if (field.toLower() == programNameFieldName)
        {
            addString(field, strNum);
            strNum++;
        }
        else if (field.left(4).toLower() == (programIdFieldName + "_"))                          // Если это поле - столбец ИМЯ, то это справочник
        {
            addString(field, strNum++);                 // следовательно должна быть строка для поиска по наименованию
        }
    }
    gridLayout->setColumnStretch(1, 1);
}


void SearchParameters::addString(QString name, int strNum)
{
    QString labelName;
    MyComboBox* comboBox = new MyComboBox(parentWidget());
    comboBox->setSearchParameters(this);
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
            labelName = app->getDBFactory()->getDictionariesProperties(name, "имя_в_форме");
//            name = name + "." + programNameFieldName;
            if (labelName.size() == 0)
            {
                labelName = name;
            }
        }
    }
    else
    {
        Dictionary* dict = (Dictionary*)(parentForm->getParent());
        name = dict->getTableName();
        if (app != 0)
        {
            labelName = "Наименование";
        }
        // Проверим, имеется ли в связанном справочнике полнотекстовый поиск
        if (dict->isFtsEnabled())
        {
            QCheckBox* checkBox = new QCheckBox(QObject::trUtf8("ПТП"), parentWidget());
            checkBox->setToolTip(QObject::trUtf8("Использовать ПолноТекстовый Поиск"));
            checkBox->setTristate(false);
            checkBox->setObjectName(dict->getTableName());                    // Запомним в кнопке имя связанного справочника, чтобы потом извлечь его в слоте
            checkBox->setFocusPolicy(Qt::NoFocus);            // Запретим переход на кнопку по клавише TAB
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
        MyComboBox* cmb = this->findChild<MyComboBox*>(field);
//        QString text = cmb->currentText().trimmed();
        QString text = cmb->currentText();
        while (text.contains("  ")) // Если есть пробелы, идущие подряд
            text.replace("  ", " "); // то уберем их
        sParam par;
        par.table = field.replace("." + programNameFieldName, "");
        par.field = programNameFieldName;
        par.value = text;
        // Определим, включен ли полнотекстовый поиск
        QCheckBox* chb = this->findChild<QCheckBox*>(field);
        par.isFtsEnabled = (chb != 0 ? chb->isChecked(): false);
        param.append(par);
    }
    return param;
}


void SearchParameters::setParameter(QString tableName, QString parameter)
{
    for (int i = 0; i < parameters.size(); i++)
    {
        QString table = parameters.at(i);
        if (table == tableName)
        {
            MyComboBox* cmb = this->findChild<MyComboBox*>(table);
            cmb->setEditText(parameter);
            return;
        }
    }
}


QString SearchParameters::getFilter(QString dictName, QString defFilter)
{
    QString filter;
    QVector<sParam> searchParameters = getParameters();
    for (int i = 0; i < searchParameters.size(); i++)
    {
        if (searchParameters[i].table == dictName)
        {
            QString text = searchParameters[i].value.toString();
            bool isInt = true;
            int id = 0;
            if (text.size() > 0 && text.at(0).isDigit())
            {
                id = text.toInt(&isInt);    // Проверим, не является ли значение кодом
            }
            else
            {
                isInt = false;
                text = text.trimmed();
            }
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
                        if (parentForm != 0 && dictionaries != 0)
                        {
                            Dictionary* dict = dictionaries->getDictionary(searchParameters[i].table);    // Поместим связанный справочник в список справочников приложения
                            if (dict != 0)
                            {
                                if (dict->getForm()->isLeftPercent())
                                    param = "%" + param;
                                if (dict->getForm()->isRightPercent())
                                    param = param + "%";
                            }
                        }
                        else
                            param = "%" + param + "%";

                        if (filter.size() > 0)
                            filter.append(" AND ");
                        filter.append(QString("%1.%2 ILIKE '%3'").arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table))
                                                                 .arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table + "." + searchParameters[i].field))
                                                                 .arg(param));
                    }
                }
            }
            if (isInt)
            {
                filter = QString("%1.%2 = %3").arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table))
                                                       .arg(app->getDBFactory()->getObjectNameCom(searchParameters[i].table + ".КОД"))
                                                       .arg(id);
                filter = "(" + filter + ")";
            }
            break;
        }
    }
    if (defFilter.size() > 0 && filter.size() > 0)
        filter = " AND " + filter;
    return defFilter + filter;
}


QString SearchParameters::getFilter()
{
    QString filter;
    QVector<sParam> searchParameters = getParameters();
    for (int i = 0; i < searchParameters.size(); i++)
    {
        filter = getFilter(searchParameters[i].table, filter);
    }
    return filter;
}


QString SearchParameters::getSearchValue(QString dictName)
{
    QString result;
    QVector<sParam> searchParameters = getParameters();
    for (int i = 0; i < searchParameters.size(); i++)
    {
        if (searchParameters[i].table == dictName)
        {
            result = searchParameters[i].value.toString();
            result.replace("'", "''");
            break;
        }
    }
    return result;
}


void SearchParameters::dictionaryButtonPressed()
{
    if (dictionaries != 0)
    {
        Dictionary* dict = dictionaries->getDictionary(sender()->objectName());    // Поместим связанный справочник в список справочников приложения
        if (dict != 0) {
            dict->exec();
            if (dict->isFormSelected())
            {
                MyComboBox* cmb = (MyComboBox*)this->findChild<QObject*>(sender()->objectName());
                if (cmb != 0)
                {
                    QString text = dict->getValue(programNameFieldName).toString().trimmed();
                    int index = cmb->findText(text);
                    if (index > 0)
                        cmb->setCurrentIndex(index);
                    else
                    {
                        cmb->insertItem(0, text);
                        cmb->setCurrentIndex(0);
                    }
                    cmb->lineEdit()->home(true);
                    cmb->setFocus();
                }
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
    if (gridLayout->rowCount() > 0)
    {
        // При активации фокуса подсветим все строчки
        for (int i = 0; i < gridLayout->rowCount(); i++)
        {
            QLayoutItem* item = gridLayout->itemAtPosition(i, 1);
            if (item != 0)
            {
                MyComboBox* widget = (MyComboBox*)(item->widget());
                if (widget != 0 && QString::compare(widget->metaObject()->className(), "MyComboBox") == 0)
                {
                    widget->lineEdit()->selectAll();
                    if (i == 0)
                        widget->setFocus();
                }
            }
        }
    }
}


void SearchParameters::keyPressEvent(QKeyEvent *event)
{
    parentForm->keyPressEvent(event);
}


void SearchParameters::setParent(QWidget* parent)
{
    QFrame::setParent(parent);
    if (gridLayout != 0)
        gridLayout->setParent(parent);
}


void SearchParameters::setFormGrid(FormGridSearch* par)
{
    parentForm = par;
}


void SearchParameters::clearAllComboBoxes()
{
    // При активации фокуса подсветим все строчки
    for (int i = 0; i < gridLayout->rowCount(); i++)
    {
        QLayoutItem* item = gridLayout->itemAtPosition(i, 1);
        if (item != 0)
        {
            MyComboBox* widget = (MyComboBox*)(item->widget());
            if (widget != 0 && QString::compare(widget->metaObject()->className(), "MyComboBox") == 0)
            {
                widget->lineEdit()->clear();
            }
        }
    }
}
