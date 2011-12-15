#include <QString>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QSizePolicy>
#include <QFrame>
#include <QLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include "../definitions.h"
#include "docparameters.h"
#include "../kernel/dictionary.h"
#include "formgrid.h"
#include "formdocument.h"
#include "../kernel/app.h"
#include "../kernel/essence.h"
#include "../kernel/document.h"

DocParameters::DocParameters(QWidget* pwgt): QFrame(pwgt) {
    setLineWidth(2);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    gridLayout = new QGridLayout(this);
    strNum = 0;
    setLayout(gridLayout);
    gridLayout->setColumnStretch(1, 1);
}

DocParameters::~DocParameters() {
    for(int i = gridLayout->rowCount() - 1; i >= 0; i--)
        removeString(i);
}

void DocParameters::addString(QString name) {
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setReadOnly(true);
    lineEdit->setObjectName(name);
    gridLayout->addWidget(lineEdit, strNum, 1, 1, 1);
    QPushButton* button = new QPushButton("...");   // Создадим пользовательскую кнопку для связанного справочника
    button->setObjectName(name);                    // Запомним в кнопке имя связанного справочника, чтобы потом извлечь его в слоте
    button->setFixedSize(lineEdit->sizeHint().height(), lineEdit->sizeHint().height());   // сделаем кнопочку квадратной со стороной как высота строки Combo
    button->setFocusPolicy(Qt::NoFocus);            // Запретим переход на кнопку по клавише TAB
    gridLayout->addWidget(button, strNum, 2, 1, 1);
    connect(button, SIGNAL(clicked()), this, SLOT(dictionaryButtonPressed()));        // При нажатии этой кнопки будем показывать связанный справочник
    lineEdit->setObjectName(name);
    QString labelName = TApplication::exemplar()->getDBFactory()->getDictionariesProperties(name).value(__NAME_IN_FORM__).toString();
    if (labelName.size() == 0)
        labelName = name;
    QLabel* label = new QLabel(labelName + ":");
    gridLayout->addWidget(label, strNum, 0, 1, 1, Qt::AlignRight);
    dictList << name;
    strNum++;
}

void DocParameters::removeString(int strNum) {
    QLabel* label = (QLabel*)gridLayout->itemAtPosition(strNum, 0)->widget();                   // удалим Label
    if (label != 0)
        gridLayout->removeWidget(label);
    QLineEdit* lineEdit = (QLineEdit*)gridLayout->itemAtPosition(strNum, 1)->widget();       // удалим ComboBox
    if (lineEdit != 0) {
        disconnect(lineEdit, 0, 0, 0);
        gridLayout->removeWidget(lineEdit);
    }
    QPushButton* button = (QPushButton*)gridLayout->itemAtPosition(strNum, 2)->widget();       // удалим PushButton
    if (button != 0) {
        disconnect(button, 0, 0, 0);
        gridLayout->removeWidget(button);
    }
}


void DocParameters::dictionaryButtonPressed() {
    foreach (QString dictName, dictionaries->keys()) {
        if (dictName.compare(sender()->objectName(), Qt::CaseInsensitive) == 0) {
            dictionaries->value(dictName)->exec();
            if (dictionaries->value(dictName)->isFormSelected()) {
                QLineEdit* lineEdit = qFindChild<QLineEdit*>(this, dictName);
                QVariant id = dictionaries->value(dictName)->getValue(programIdFieldName);
                dictionaries->value(dictName)->setId(id.toULongLong());;
                parentForm->getParent()->setConstDictId(dictName, id);
                lineEdit->setText(dictionaries->value(dictName)->getValue(programNameFieldName).toString());
            }
            break;
        }
    }
    parentForm->getForm()->activateWindow();
    parentForm->parametersChangedEvent();
//    parentForm->setShowFocus();
}


void DocParameters::showText(QString dName)
{   // На форме документа выводит текущие значения поля ИМЯ постоянных справочников
    foreach (QString dictName, dictionaries->keys()) {
        if (dictName.compare(dName, Qt::CaseInsensitive) == 0)
        {   // В списке локальных для документа справочников разыщем справочник <dName>
            QLineEdit* lineEdit = qFindChild<QLineEdit*>(this, dictName);       // На форме документа разыщем строку, в которой будем отображать поле ИМЯ
            QVariant id = dictionaries->value(dictName)->getValue(programIdFieldName);
            dictionaries->value(dictName)->setId(id.toULongLong());;
            lineEdit->setText(dictionaries->value(dictName)->getValue(programNameFieldName).toString());
            break;
        }
    }
}


void DocParameters::setFocus() {
    QWidget* widget = gridLayout->itemAtPosition(0, 1)->widget();
    widget->setFocus();
}
