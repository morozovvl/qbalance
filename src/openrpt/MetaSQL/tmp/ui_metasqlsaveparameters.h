/********************************************************************************
** Form generated from reading UI file 'metasqlsaveparameters.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METASQLSAVEPARAMETERS_H
#define UI_METASQLSAVEPARAMETERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_MetaSQLSaveParameters
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *_schemaLit;
    QLabel *_groupLit;
    QLabel *_nameLit;
    QComboBox *_schema;
    QComboBox *_group;
    QLineEdit *_name;
    QLabel *_gradeLit;
    QSpinBox *_grade;
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *_notes;
    QLabel *_notesLit;

    void setupUi(QDialog *MetaSQLSaveParameters)
    {
        if (MetaSQLSaveParameters->objectName().isEmpty())
            MetaSQLSaveParameters->setObjectName(QString::fromUtf8("MetaSQLSaveParameters"));
        MetaSQLSaveParameters->resize(407, 264);
        gridLayout = new QGridLayout(MetaSQLSaveParameters);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        _schemaLit = new QLabel(MetaSQLSaveParameters);
        _schemaLit->setObjectName(QString::fromUtf8("_schemaLit"));

        formLayout->setWidget(0, QFormLayout::LabelRole, _schemaLit);

        _groupLit = new QLabel(MetaSQLSaveParameters);
        _groupLit->setObjectName(QString::fromUtf8("_groupLit"));

        formLayout->setWidget(1, QFormLayout::LabelRole, _groupLit);

        _nameLit = new QLabel(MetaSQLSaveParameters);
        _nameLit->setObjectName(QString::fromUtf8("_nameLit"));

        formLayout->setWidget(2, QFormLayout::LabelRole, _nameLit);

        _schema = new QComboBox(MetaSQLSaveParameters);
        _schema->setObjectName(QString::fromUtf8("_schema"));

        formLayout->setWidget(0, QFormLayout::FieldRole, _schema);

        _group = new QComboBox(MetaSQLSaveParameters);
        _group->setObjectName(QString::fromUtf8("_group"));
        _group->setEditable(true);
        _group->setInsertPolicy(QComboBox::InsertAlphabetically);

        formLayout->setWidget(1, QFormLayout::FieldRole, _group);

        _name = new QLineEdit(MetaSQLSaveParameters);
        _name->setObjectName(QString::fromUtf8("_name"));

        formLayout->setWidget(2, QFormLayout::FieldRole, _name);

        _gradeLit = new QLabel(MetaSQLSaveParameters);
        _gradeLit->setObjectName(QString::fromUtf8("_gradeLit"));

        formLayout->setWidget(3, QFormLayout::LabelRole, _gradeLit);

        _grade = new QSpinBox(MetaSQLSaveParameters);
        _grade->setObjectName(QString::fromUtf8("_grade"));
        _grade->setMinimum(-1);
        _grade->setValue(-1);

        formLayout->setWidget(3, QFormLayout::FieldRole, _grade);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(MetaSQLSaveParameters);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 0, 1, 1, 1);

        _notes = new QPlainTextEdit(MetaSQLSaveParameters);
        _notes->setObjectName(QString::fromUtf8("_notes"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        _notes->setFont(font);

        gridLayout->addWidget(_notes, 2, 0, 1, 2);

        _notesLit = new QLabel(MetaSQLSaveParameters);
        _notesLit->setObjectName(QString::fromUtf8("_notesLit"));

        gridLayout->addWidget(_notesLit, 1, 0, 1, 1);


        retranslateUi(MetaSQLSaveParameters);
        QObject::connect(buttonBox, SIGNAL(accepted()), MetaSQLSaveParameters, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MetaSQLSaveParameters, SLOT(reject()));

        QMetaObject::connectSlotsByName(MetaSQLSaveParameters);
    } // setupUi

    void retranslateUi(QDialog *MetaSQLSaveParameters)
    {
        MetaSQLSaveParameters->setWindowTitle(QApplication::translate("MetaSQLSaveParameters", "MetaSQL Save Parameters", 0, QApplication::UnicodeUTF8));
        _schemaLit->setText(QApplication::translate("MetaSQLSaveParameters", "Schema:", 0, QApplication::UnicodeUTF8));
        _groupLit->setText(QApplication::translate("MetaSQLSaveParameters", "Group:", 0, QApplication::UnicodeUTF8));
        _nameLit->setText(QApplication::translate("MetaSQLSaveParameters", "Name:", 0, QApplication::UnicodeUTF8));
        _gradeLit->setText(QApplication::translate("MetaSQLSaveParameters", "Grade:", 0, QApplication::UnicodeUTF8));
        _grade->setSpecialValueText(QApplication::translate("MetaSQLSaveParameters", "##", 0, QApplication::UnicodeUTF8));
        _notesLit->setText(QApplication::translate("MetaSQLSaveParameters", "Notes:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MetaSQLSaveParameters: public Ui_MetaSQLSaveParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METASQLSAVEPARAMETERS_H
