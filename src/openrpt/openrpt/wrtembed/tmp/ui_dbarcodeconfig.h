/********************************************************************************
** Form generated from reading UI file 'dbarcodeconfig.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBARCODECONFIG_H
#define UI_DBARCODECONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBarcodeConfig
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QSlider *_SliderMaxVal;
    QLabel *_LMaxVal;

    void setupUi(QWidget *DBarcodeConfig)
    {
        if (DBarcodeConfig->objectName().isEmpty())
            DBarcodeConfig->setObjectName(QString::fromUtf8("DBarcodeConfig"));
        DBarcodeConfig->resize(176, 84);
        gridLayout = new QGridLayout(DBarcodeConfig);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(DBarcodeConfig);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        _SliderMaxVal = new QSlider(groupBox);
        _SliderMaxVal->setObjectName(QString::fromUtf8("_SliderMaxVal"));
        _SliderMaxVal->setMinimum(1);
        _SliderMaxVal->setValue(5);
        _SliderMaxVal->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(_SliderMaxVal);

        _LMaxVal = new QLabel(groupBox);
        _LMaxVal->setObjectName(QString::fromUtf8("_LMaxVal"));

        horizontalLayout->addWidget(_LMaxVal);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(DBarcodeConfig);
        QObject::connect(_SliderMaxVal, SIGNAL(valueChanged(int)), _LMaxVal, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(DBarcodeConfig);
    } // setupUi

    void retranslateUi(QWidget *DBarcodeConfig)
    {
        DBarcodeConfig->setWindowTitle(QApplication::translate("DBarcodeConfig", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DBarcodeConfig", "Maximum Length of Value", 0, QApplication::UnicodeUTF8));
        _LMaxVal->setText(QApplication::translate("DBarcodeConfig", "5", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DBarcodeConfig: public Ui_DBarcodeConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBARCODECONFIG_H
