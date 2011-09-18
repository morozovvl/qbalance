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
#include "../dictionary.h"
#include "../dictionaries.h"
#include "formgrid.h"
#include "formgridsearch.h"
#include "../essence.h"


SearchParameters::SearchParameters(QWidget* parentWidget): QFrame(parentWidget) {
    gridLayout = 0;
}

void SearchParameters::close() {
    for(int i = gridLayout->rowCount() - 1; i >= 0; i--)
        removeString(i);
}

void SearchParameters::setFieldsList(QStringList fldList) {
    setLineWidth(2);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    gridLayout = new QGridLayout(this);
    int strNum = 0;
    for (int i = 0; i < fldList.count(); i++) {
        QString field = fldList.at(i);
        if (field.toLower() == programNameFieldName ||
            (field.left(4).toLower() == (programIdFieldName + "_") && !parentForm->getParent()->relationsIsEmpty()))                          // Если это поле - столбец ИМЯ, то это справочник
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
        QPushButton* button = new QPushButton("...", parentWidget());   // Создадим пользовательскую кнопку для связанного справочника
        button->setObjectName(name);                    // Запомним в кнопке имя связанного справочника, чтобы потом извлечь его в слоте
        button->setFixedSize(comboBox->height() * 1.2, comboBox->height());
        button->setFocusPolicy(Qt::NoFocus);            // Запретим переход на кнопку по клавише TAB
        gridLayout->addWidget(button, strNum, 2, 1, 1);
        connect(button, SIGNAL(clicked()), this, SLOT(dictionaryButtonPressed()));
        labelName = TApplication::exemplar()->getDictionaries()->getDictionaryProperty(name, "имя_в_форме").toString();
        name = name + "." + programNameFieldName;
        if (labelName.size() == 0)
            labelName = name;
    }
    else {
        labelName = TApplication::exemplar()->getDictionaries()->getDictionaryProperty(parentForm->getParent()->getTableName(), "имя_в_форме").toString();
        if (labelName.size() == 0)
            labelName = "Наименование";
        name = parentForm->getParent()->getTableName() + "." + programNameFieldName;
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

void SearchParameters::getParameters(QVector<sParam> &param) {
    param.clear();
    for(int i = 0; i < parameters.size(); i++) {
        QString field = parameters.at(i);
        MyComboBox* cmb = (MyComboBox*)qFindChild<QComboBox*>(this, field);
        QString text = cmb->currentText().trimmed();
        while (text.contains("  "))                                   // Если есть пробелы, идущие подряд
            text.replace("  ", " ");                                  // то уберем их
        sParam par;
        par.table = field.replace("." + programNameFieldName, "");
        par.field = programNameFieldName;
        par.value = text;
        if (text.size() > 0)
            param.append(par);
        if (par.table != parentForm->getParent()->getTableName()) {
            par.field = programIdFieldName + "_" + par.table;
            par.value = 0;
            if (TApplication::exemplar()->getDictionaries()->isMember(par.table))              // Если такой справочник существует
                par.value = TApplication::exemplar()->getDictionaries()->getDictionary(par.table)->getId();                          // то возьмем идентификатор его текущей записи
            par.table = parentForm->getParent()->getTableName();
            if (par.value.toLongLong() > 0)
                param.append(par);
        }
    }
}

void SearchParameters::dictionaryButtonPressed() {
    TApplication::exemplar()->getDictionaries()->addDictionary(sender()->objectName(), 0);
    Dictionary* dict = TApplication::exemplar()->getDictionaries()->getDictionary(sender()->objectName());    // Поместим связанный справочник в список справочников приложения
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
    parentForm->setShowFocus();
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
    if (gridLayout != 0) {
        QWidget* widget = gridLayout->itemAtPosition(0, 1)->widget();
        widget->setFocus();
    }
}
