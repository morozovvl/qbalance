/********************************************************************************
** Form generated from reading UI file 'selectmql.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMQL_H
#define UI_SELECTMQL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMQL
{
public:
    QGridLayout *gridLayout;
    QLabel *_schemaLit;
    QComboBox *_schema;
    QDialogButtonBox *_buttons;
    QTreeView *_list;

    void setupUi(QWidget *SelectMQL)
    {
        if (SelectMQL->objectName().isEmpty())
            SelectMQL->setObjectName(QString::fromUtf8("SelectMQL"));
        SelectMQL->resize(470, 247);
        gridLayout = new QGridLayout(SelectMQL);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _schemaLit = new QLabel(SelectMQL);
        _schemaLit->setObjectName(QString::fromUtf8("_schemaLit"));

        gridLayout->addWidget(_schemaLit, 0, 0, 1, 1);

        _schema = new QComboBox(SelectMQL);
        _schema->setObjectName(QString::fromUtf8("_schema"));

        gridLayout->addWidget(_schema, 0, 1, 1, 1);

        _buttons = new QDialogButtonBox(SelectMQL);
        _buttons->setObjectName(QString::fromUtf8("_buttons"));
        _buttons->setOrientation(Qt::Vertical);
        _buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(_buttons, 0, 2, 2, 1);

        _list = new QTreeView(SelectMQL);
        _list->setObjectName(QString::fromUtf8("_list"));
        _list->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(_list, 1, 0, 1, 2);


        retranslateUi(SelectMQL);

        QMetaObject::connectSlotsByName(SelectMQL);
    } // setupUi

    void retranslateUi(QWidget *SelectMQL)
    {
        SelectMQL->setWindowTitle(QApplication::translate("SelectMQL", "Choose a MetaSQL Query", 0, QApplication::UnicodeUTF8));
        _schemaLit->setText(QApplication::translate("SelectMQL", "Schema or Package:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectMQL: public Ui_SelectMQL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMQL_H
