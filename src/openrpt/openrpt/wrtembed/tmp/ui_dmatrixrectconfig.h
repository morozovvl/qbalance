/********************************************************************************
** Form generated from reading UI file 'dmatrixrectconfig.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMATRIXRECTCONFIG_H
#define UI_DMATRIXRECTCONFIG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMatrixRectConfig
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *_LCapacite;
    QPushButton *_previewButton;
    QComboBox *_CFormat;

    void setupUi(QWidget *DMatrixRectConfig)
    {
        if (DMatrixRectConfig->objectName().isEmpty())
            DMatrixRectConfig->setObjectName(QString::fromUtf8("DMatrixRectConfig"));
        DMatrixRectConfig->resize(196, 100);
        gridLayout = new QGridLayout(DMatrixRectConfig);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(DMatrixRectConfig);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_2->addWidget(label, 0, 0, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        _LCapacite = new QLabel(groupBox);
        _LCapacite->setObjectName(QString::fromUtf8("_LCapacite"));

        gridLayout_2->addWidget(_LCapacite, 1, 1, 1, 1);

        _previewButton = new QPushButton(groupBox);
        _previewButton->setObjectName(QString::fromUtf8("_previewButton"));
        _previewButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        _previewButton->setCheckable(true);

        gridLayout_2->addWidget(_previewButton, 1, 2, 1, 1);

        _CFormat = new QComboBox(groupBox);
        _CFormat->setObjectName(QString::fromUtf8("_CFormat"));

        gridLayout_2->addWidget(_CFormat, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(DMatrixRectConfig);

        QMetaObject::connectSlotsByName(DMatrixRectConfig);
    } // setupUi

    void retranslateUi(QWidget *DMatrixRectConfig)
    {
        DMatrixRectConfig->setWindowTitle(QApplication::translate("DMatrixRectConfig", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DMatrixRectConfig", "Datamatrix Format", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DMatrixRectConfig", "Format :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DMatrixRectConfig", "Capacity :", 0, QApplication::UnicodeUTF8));
        _LCapacite->setText(QApplication::translate("DMatrixRectConfig", "10/6", 0, QApplication::UnicodeUTF8));
        _previewButton->setText(QApplication::translate("DMatrixRectConfig", "Preview", 0, QApplication::UnicodeUTF8));
        _CFormat->clear();
        _CFormat->insertItems(0, QStringList()
         << QApplication::translate("DMatrixRectConfig", "8x18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DMatrixRectConfig", "8x32", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DMatrixRectConfig", "12x26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DMatrixRectConfig", "12x36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DMatrixRectConfig", "16x36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DMatrixRectConfig", "16x48", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class DMatrixRectConfig: public Ui_DMatrixRectConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMATRIXRECTCONFIG_H
