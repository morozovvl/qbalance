/********************************************************************************
** Form generated from reading UI file 'dmatrixsquareconfig.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMATRIXSQUARECONFIG_H
#define UI_DMATRIXSQUARECONFIG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMatrixSquareConfig
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSlider *_Format;
    QLabel *label;
    QLabel *label_2;
    QLabel *_LCapacite;
    QLabel *_LFormat;
    QPushButton *_previewButton;

    void setupUi(QWidget *DMatrixSquareConfig)
    {
        if (DMatrixSquareConfig->objectName().isEmpty())
            DMatrixSquareConfig->setObjectName(QString::fromUtf8("DMatrixSquareConfig"));
        DMatrixSquareConfig->setEnabled(true);
        DMatrixSquareConfig->resize(210, 108);
        DMatrixSquareConfig->setContextMenuPolicy(Qt::DefaultContextMenu);
        gridLayout_2 = new QGridLayout(DMatrixSquareConfig);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(DMatrixSquareConfig);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _Format = new QSlider(groupBox);
        _Format->setObjectName(QString::fromUtf8("_Format"));
        _Format->setMaximum(23);
        _Format->setValue(4);
        _Format->setTracking(true);
        _Format->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(_Format, 0, 0, 1, 4);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        _LCapacite = new QLabel(groupBox);
        _LCapacite->setObjectName(QString::fromUtf8("_LCapacite"));

        gridLayout->addWidget(_LCapacite, 2, 1, 1, 1);

        _LFormat = new QLabel(groupBox);
        _LFormat->setObjectName(QString::fromUtf8("_LFormat"));

        gridLayout->addWidget(_LFormat, 1, 1, 1, 1);

        _previewButton = new QPushButton(groupBox);
        _previewButton->setObjectName(QString::fromUtf8("_previewButton"));
        _previewButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        _previewButton->setCheckable(true);

        gridLayout->addWidget(_previewButton, 1, 3, 2, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(DMatrixSquareConfig);

        QMetaObject::connectSlotsByName(DMatrixSquareConfig);
    } // setupUi

    void retranslateUi(QWidget *DMatrixSquareConfig)
    {
        DMatrixSquareConfig->setWindowTitle(QApplication::translate("DMatrixSquareConfig", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DMatrixSquareConfig", "Datamatrix Format", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DMatrixSquareConfig", "Format :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DMatrixSquareConfig", "Capacity :", 0, QApplication::UnicodeUTF8));
        _LCapacite->setText(QApplication::translate("DMatrixSquareConfig", "36/25", 0, QApplication::UnicodeUTF8));
        _LFormat->setText(QApplication::translate("DMatrixSquareConfig", "18x18", 0, QApplication::UnicodeUTF8));
        _previewButton->setText(QApplication::translate("DMatrixSquareConfig", "Preview", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DMatrixSquareConfig: public Ui_DMatrixSquareConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMATRIXSQUARECONFIG_H
