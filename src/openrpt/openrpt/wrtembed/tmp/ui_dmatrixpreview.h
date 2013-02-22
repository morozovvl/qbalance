/********************************************************************************
** Form generated from reading UI file 'dmatrixpreview.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMATRIXPREVIEW_H
#define UI_DMATRIXPREVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMatrixPreview
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *DMatrixPreview)
    {
        if (DMatrixPreview->objectName().isEmpty())
            DMatrixPreview->setObjectName(QString::fromUtf8("DMatrixPreview"));
        DMatrixPreview->resize(400, 300);
        gridLayout = new QGridLayout(DMatrixPreview);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(DMatrixPreview);

        QMetaObject::connectSlotsByName(DMatrixPreview);
    } // setupUi

    void retranslateUi(QWidget *DMatrixPreview)
    {
        DMatrixPreview->setWindowTitle(QApplication::translate("DMatrixPreview", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DMatrixPreview: public Ui_DMatrixPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMATRIXPREVIEW_H
