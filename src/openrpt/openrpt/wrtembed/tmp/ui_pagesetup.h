/********************************************************************************
** Form generated from reading UI file 'pagesetup.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESETUP_H
#define UI_PAGESETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PageSetup
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupPaperSize;
    QVBoxLayout *vboxLayout;
    QComboBox *comboPaperSize;
    QFrame *Line1;
    QLabel *labelCustom;
    QHBoxLayout *hboxLayout;
    QLabel *labelWidth;
    QLineEdit *linePaperWidth;
    QHBoxLayout *hboxLayout1;
    QLabel *labelHeight;
    QLineEdit *linePaperHeight;
    QLabel *labelInInches;
    QGroupBox *groupMargins;
    QGridLayout *gridLayout1;
    QLabel *labelTop;
    QLineEdit *lineTop;
    QLabel *labelBottom;
    QLineEdit *lineBottom;
    QLabel *labelLeft;
    QLineEdit *lineLeft;
    QLabel *labelRight;
    QLineEdit *lineRight;
    QLabel *TextLabel5;
    QGroupBox *groupOrientation;
    QGridLayout *gridLayout2;
    QRadioButton *radioPortrait;
    QRadioButton *radioLandscape;
    QSpacerItem *spacerItem;
    QGroupBox *grpLabels;
    QGridLayout *gridLayout3;
    QLabel *labelLabelType;
    QComboBox *comboLabelType;
    QSpacerItem *spacerItem1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PageSetup)
    {
        if (PageSetup->objectName().isEmpty())
            PageSetup->setObjectName(QString::fromUtf8("PageSetup"));
        PageSetup->resize(535, 358);
        gridLayout = new QGridLayout(PageSetup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupPaperSize = new QGroupBox(PageSetup);
        groupPaperSize->setObjectName(QString::fromUtf8("groupPaperSize"));
        vboxLayout = new QVBoxLayout(groupPaperSize);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        comboPaperSize = new QComboBox(groupPaperSize);
        comboPaperSize->setObjectName(QString::fromUtf8("comboPaperSize"));

        vboxLayout->addWidget(comboPaperSize);

        Line1 = new QFrame(groupPaperSize);
        Line1->setObjectName(QString::fromUtf8("Line1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Line1->sizePolicy().hasHeightForWidth());
        Line1->setSizePolicy(sizePolicy);
        Line1->setFrameShape(QFrame::HLine);
        Line1->setFrameShadow(QFrame::Sunken);
        Line1->setFrameShape(QFrame::HLine);

        vboxLayout->addWidget(Line1);

        labelCustom = new QLabel(groupPaperSize);
        labelCustom->setObjectName(QString::fromUtf8("labelCustom"));
        labelCustom->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelCustom->sizePolicy().hasHeightForWidth());
        labelCustom->setSizePolicy(sizePolicy1);

        vboxLayout->addWidget(labelCustom);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        labelWidth = new QLabel(groupPaperSize);
        labelWidth->setObjectName(QString::fromUtf8("labelWidth"));
        labelWidth->setEnabled(false);
        sizePolicy1.setHeightForWidth(labelWidth->sizePolicy().hasHeightForWidth());
        labelWidth->setSizePolicy(sizePolicy1);
        labelWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout->addWidget(labelWidth);

        linePaperWidth = new QLineEdit(groupPaperSize);
        linePaperWidth->setObjectName(QString::fromUtf8("linePaperWidth"));
        linePaperWidth->setEnabled(false);
        sizePolicy.setHeightForWidth(linePaperWidth->sizePolicy().hasHeightForWidth());
        linePaperWidth->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(linePaperWidth);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        labelHeight = new QLabel(groupPaperSize);
        labelHeight->setObjectName(QString::fromUtf8("labelHeight"));
        labelHeight->setEnabled(false);
        sizePolicy1.setHeightForWidth(labelHeight->sizePolicy().hasHeightForWidth());
        labelHeight->setSizePolicy(sizePolicy1);
        labelHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout1->addWidget(labelHeight);

        linePaperHeight = new QLineEdit(groupPaperSize);
        linePaperHeight->setObjectName(QString::fromUtf8("linePaperHeight"));
        linePaperHeight->setEnabled(false);
        sizePolicy.setHeightForWidth(linePaperHeight->sizePolicy().hasHeightForWidth());
        linePaperHeight->setSizePolicy(sizePolicy);

        hboxLayout1->addWidget(linePaperHeight);


        vboxLayout->addLayout(hboxLayout1);

        labelInInches = new QLabel(groupPaperSize);
        labelInInches->setObjectName(QString::fromUtf8("labelInInches"));
        labelInInches->setEnabled(false);
        sizePolicy1.setHeightForWidth(labelInInches->sizePolicy().hasHeightForWidth());
        labelInInches->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica [Cronyx]"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(true);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        labelInInches->setFont(font);
        labelInInches->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        vboxLayout->addWidget(labelInInches);


        gridLayout->addWidget(groupPaperSize, 0, 0, 1, 2);

        groupMargins = new QGroupBox(PageSetup);
        groupMargins->setObjectName(QString::fromUtf8("groupMargins"));
        gridLayout1 = new QGridLayout(groupMargins);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        labelTop = new QLabel(groupMargins);
        labelTop->setObjectName(QString::fromUtf8("labelTop"));

        gridLayout1->addWidget(labelTop, 0, 0, 1, 1);

        lineTop = new QLineEdit(groupMargins);
        lineTop->setObjectName(QString::fromUtf8("lineTop"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineTop->sizePolicy().hasHeightForWidth());
        lineTop->setSizePolicy(sizePolicy2);

        gridLayout1->addWidget(lineTop, 0, 1, 1, 1);

        labelBottom = new QLabel(groupMargins);
        labelBottom->setObjectName(QString::fromUtf8("labelBottom"));

        gridLayout1->addWidget(labelBottom, 1, 0, 1, 1);

        lineBottom = new QLineEdit(groupMargins);
        lineBottom->setObjectName(QString::fromUtf8("lineBottom"));
        sizePolicy2.setHeightForWidth(lineBottom->sizePolicy().hasHeightForWidth());
        lineBottom->setSizePolicy(sizePolicy2);

        gridLayout1->addWidget(lineBottom, 1, 1, 1, 1);

        labelLeft = new QLabel(groupMargins);
        labelLeft->setObjectName(QString::fromUtf8("labelLeft"));

        gridLayout1->addWidget(labelLeft, 2, 0, 1, 1);

        lineLeft = new QLineEdit(groupMargins);
        lineLeft->setObjectName(QString::fromUtf8("lineLeft"));
        sizePolicy2.setHeightForWidth(lineLeft->sizePolicy().hasHeightForWidth());
        lineLeft->setSizePolicy(sizePolicy2);

        gridLayout1->addWidget(lineLeft, 2, 1, 1, 1);

        labelRight = new QLabel(groupMargins);
        labelRight->setObjectName(QString::fromUtf8("labelRight"));

        gridLayout1->addWidget(labelRight, 3, 0, 1, 1);

        lineRight = new QLineEdit(groupMargins);
        lineRight->setObjectName(QString::fromUtf8("lineRight"));
        sizePolicy2.setHeightForWidth(lineRight->sizePolicy().hasHeightForWidth());
        lineRight->setSizePolicy(sizePolicy2);

        gridLayout1->addWidget(lineRight, 3, 1, 1, 1);

        TextLabel5 = new QLabel(groupMargins);
        TextLabel5->setObjectName(QString::fromUtf8("TextLabel5"));
        sizePolicy1.setHeightForWidth(TextLabel5->sizePolicy().hasHeightForWidth());
        TextLabel5->setSizePolicy(sizePolicy1);
        TextLabel5->setFont(font);
        TextLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(TextLabel5, 4, 0, 1, 2);


        gridLayout->addWidget(groupMargins, 0, 2, 1, 1);

        groupOrientation = new QGroupBox(PageSetup);
        groupOrientation->setObjectName(QString::fromUtf8("groupOrientation"));
        gridLayout2 = new QGridLayout(groupOrientation);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        radioPortrait = new QRadioButton(groupOrientation);
        radioPortrait->setObjectName(QString::fromUtf8("radioPortrait"));
        radioPortrait->setChecked(true);

        gridLayout2->addWidget(radioPortrait, 0, 0, 1, 1);

        radioLandscape = new QRadioButton(groupOrientation);
        radioLandscape->setObjectName(QString::fromUtf8("radioLandscape"));

        gridLayout2->addWidget(radioLandscape, 1, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout2->addItem(spacerItem, 2, 0, 1, 1);


        gridLayout->addWidget(groupOrientation, 1, 0, 1, 1);

        grpLabels = new QGroupBox(PageSetup);
        grpLabels->setObjectName(QString::fromUtf8("grpLabels"));
        grpLabels->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(grpLabels->sizePolicy().hasHeightForWidth());
        grpLabels->setSizePolicy(sizePolicy3);
        gridLayout3 = new QGridLayout(grpLabels);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        labelLabelType = new QLabel(grpLabels);
        labelLabelType->setObjectName(QString::fromUtf8("labelLabelType"));
        labelLabelType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout3->addWidget(labelLabelType, 0, 0, 1, 1);

        comboLabelType = new QComboBox(grpLabels);
        comboLabelType->setObjectName(QString::fromUtf8("comboLabelType"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboLabelType->sizePolicy().hasHeightForWidth());
        comboLabelType->setSizePolicy(sizePolicy4);

        gridLayout3->addWidget(comboLabelType, 0, 1, 1, 1);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacerItem1, 1, 1, 1, 1);


        gridLayout->addWidget(grpLabels, 1, 1, 1, 2);

        buttonBox = new QDialogButtonBox(PageSetup);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 3);


        retranslateUi(PageSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), PageSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PageSetup, SLOT(reject()));

        QMetaObject::connectSlotsByName(PageSetup);
    } // setupUi

    void retranslateUi(QDialog *PageSetup)
    {
        PageSetup->setWindowTitle(QApplication::translate("PageSetup", "Edit page settings...", 0, QApplication::UnicodeUTF8));
        groupPaperSize->setTitle(QApplication::translate("PageSetup", "Paper Size", 0, QApplication::UnicodeUTF8));
        labelCustom->setText(QApplication::translate("PageSetup", "Custom dimensions", 0, QApplication::UnicodeUTF8));
        labelWidth->setText(QApplication::translate("PageSetup", "Width:", 0, QApplication::UnicodeUTF8));
        linePaperWidth->setText(QApplication::translate("PageSetup", "8.5", 0, QApplication::UnicodeUTF8));
        labelHeight->setText(QApplication::translate("PageSetup", "Height:", 0, QApplication::UnicodeUTF8));
        linePaperHeight->setText(QApplication::translate("PageSetup", "11.0", 0, QApplication::UnicodeUTF8));
        labelInInches->setText(QApplication::translate("PageSetup", "in Inches", 0, QApplication::UnicodeUTF8));
        groupMargins->setTitle(QApplication::translate("PageSetup", "Margins", 0, QApplication::UnicodeUTF8));
        labelTop->setText(QApplication::translate("PageSetup", "Top:", 0, QApplication::UnicodeUTF8));
        lineTop->setText(QApplication::translate("PageSetup", "1.0", 0, QApplication::UnicodeUTF8));
        labelBottom->setText(QApplication::translate("PageSetup", "Bottom:", 0, QApplication::UnicodeUTF8));
        lineBottom->setText(QApplication::translate("PageSetup", "1.0", 0, QApplication::UnicodeUTF8));
        labelLeft->setText(QApplication::translate("PageSetup", "Left:", 0, QApplication::UnicodeUTF8));
        lineLeft->setText(QApplication::translate("PageSetup", "1.0", 0, QApplication::UnicodeUTF8));
        labelRight->setText(QApplication::translate("PageSetup", "Right:", 0, QApplication::UnicodeUTF8));
        lineRight->setText(QApplication::translate("PageSetup", "1.0", 0, QApplication::UnicodeUTF8));
        TextLabel5->setText(QApplication::translate("PageSetup", "in Inches", 0, QApplication::UnicodeUTF8));
        groupOrientation->setTitle(QApplication::translate("PageSetup", "Orientation", 0, QApplication::UnicodeUTF8));
        radioPortrait->setText(QApplication::translate("PageSetup", "Portrait", 0, QApplication::UnicodeUTF8));
        radioLandscape->setText(QApplication::translate("PageSetup", "Landscape", 0, QApplication::UnicodeUTF8));
        grpLabels->setTitle(QApplication::translate("PageSetup", "Labels", 0, QApplication::UnicodeUTF8));
        labelLabelType->setText(QApplication::translate("PageSetup", "Type: ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PageSetup: public Ui_PageSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESETUP_H
