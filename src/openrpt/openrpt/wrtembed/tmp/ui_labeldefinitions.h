/********************************************************************************
** Form generated from reading UI file 'labeldefinitions.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELDEFINITIONS_H
#define UI_LABELDEFINITIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LabelDefinitions
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QListWidget *ldList;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnClose;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *LabelDefinitions)
    {
        if (LabelDefinitions->objectName().isEmpty())
            LabelDefinitions->setObjectName(QString::fromUtf8("LabelDefinitions"));
        LabelDefinitions->resize(639, 405);
        gridLayout_2 = new QGridLayout(LabelDefinitions);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(LabelDefinitions);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ldList = new QListWidget(groupBox);
        ldList->setObjectName(QString::fromUtf8("ldList"));

        gridLayout->addWidget(ldList, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnClose = new QPushButton(LabelDefinitions);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        verticalLayout->addWidget(btnClose);

        btnAdd = new QPushButton(LabelDefinitions);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        verticalLayout->addWidget(btnAdd);

        btnEdit = new QPushButton(LabelDefinitions);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));

        verticalLayout->addWidget(btnEdit);

        btnDelete = new QPushButton(LabelDefinitions);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        verticalLayout->addWidget(btnDelete);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 218, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);


        retranslateUi(LabelDefinitions);

        QMetaObject::connectSlotsByName(LabelDefinitions);
    } // setupUi

    void retranslateUi(QDialog *LabelDefinitions)
    {
        LabelDefinitions->setWindowTitle(QApplication::translate("LabelDefinitions", "Label Definitions", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("LabelDefinitions", "Label Definitions", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("LabelDefinitions", "Close", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("LabelDefinitions", "New", 0, QApplication::UnicodeUTF8));
        btnEdit->setText(QApplication::translate("LabelDefinitions", "Edit", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("LabelDefinitions", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LabelDefinitions: public Ui_LabelDefinitions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELDEFINITIONS_H
