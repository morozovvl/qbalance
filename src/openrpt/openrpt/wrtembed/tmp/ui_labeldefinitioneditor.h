/********************************************************************************
** Form generated from reading UI file 'labeldefinitioneditor.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELDEFINITIONEDITOR_H
#define UI_LABELDEFINITIONEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LabelDefinitionEditor
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *labelName;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *paperSize;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *labelColumns;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *labelRows;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *labelWidth;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *labelHeight;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpinBox *labelStartXOffset;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QSpinBox *labelStartYOffset;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QSpinBox *labelHorizontalGap;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QSpinBox *labelVerticalGap;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnCancel;
    QPushButton *btnSave;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *LabelDefinitionEditor)
    {
        if (LabelDefinitionEditor->objectName().isEmpty())
            LabelDefinitionEditor->setObjectName(QString::fromUtf8("LabelDefinitionEditor"));
        LabelDefinitionEditor->resize(459, 460);
        gridLayout_2 = new QGridLayout(LabelDefinitionEditor);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(LabelDefinitionEditor);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        labelName = new QLineEdit(LabelDefinitionEditor);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        horizontalLayout->addWidget(labelName);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        groupBox = new QGroupBox(LabelDefinitionEditor);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        paperSize = new QComboBox(groupBox);
        paperSize->setObjectName(QString::fromUtf8("paperSize"));

        horizontalLayout_2->addWidget(paperSize);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        labelColumns = new QSpinBox(groupBox);
        labelColumns->setObjectName(QString::fromUtf8("labelColumns"));
        labelColumns->setMinimum(1);
        labelColumns->setMaximum(16777215);

        horizontalLayout_3->addWidget(labelColumns);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        labelRows = new QSpinBox(groupBox);
        labelRows->setObjectName(QString::fromUtf8("labelRows"));
        labelRows->setMinimum(1);
        labelRows->setMaximum(16777215);

        horizontalLayout_4->addWidget(labelRows);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        labelWidth = new QSpinBox(groupBox);
        labelWidth->setObjectName(QString::fromUtf8("labelWidth"));
        labelWidth->setMinimum(1);
        labelWidth->setMaximum(16777215);

        horizontalLayout_5->addWidget(labelWidth);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        labelHeight = new QSpinBox(groupBox);
        labelHeight->setObjectName(QString::fromUtf8("labelHeight"));
        labelHeight->setMinimum(1);
        labelHeight->setMaximum(16777215);

        horizontalLayout_6->addWidget(labelHeight);


        gridLayout->addLayout(horizontalLayout_6, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        labelStartXOffset = new QSpinBox(groupBox);
        labelStartXOffset->setObjectName(QString::fromUtf8("labelStartXOffset"));
        labelStartXOffset->setMaximum(16777215);

        horizontalLayout_7->addWidget(labelStartXOffset);


        gridLayout->addLayout(horizontalLayout_7, 5, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_8->addWidget(label_8);

        labelStartYOffset = new QSpinBox(groupBox);
        labelStartYOffset->setObjectName(QString::fromUtf8("labelStartYOffset"));
        labelStartYOffset->setMaximum(16777215);

        horizontalLayout_8->addWidget(labelStartYOffset);


        gridLayout->addLayout(horizontalLayout_8, 6, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_9->addWidget(label_9);

        labelHorizontalGap = new QSpinBox(groupBox);
        labelHorizontalGap->setObjectName(QString::fromUtf8("labelHorizontalGap"));
        labelHorizontalGap->setMaximum(16777215);

        horizontalLayout_9->addWidget(labelHorizontalGap);


        gridLayout->addLayout(horizontalLayout_9, 7, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_10->addWidget(label_10);

        labelVerticalGap = new QSpinBox(groupBox);
        labelVerticalGap->setObjectName(QString::fromUtf8("labelVerticalGap"));
        labelVerticalGap->setMaximum(16777215);

        horizontalLayout_10->addWidget(labelVerticalGap);


        gridLayout->addLayout(horizontalLayout_10, 8, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnCancel = new QPushButton(LabelDefinitionEditor);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setAutoDefault(false);

        verticalLayout->addWidget(btnCancel);

        btnSave = new QPushButton(LabelDefinitionEditor);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        verticalLayout->addWidget(btnSave);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 258, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);


        retranslateUi(LabelDefinitionEditor);

        QMetaObject::connectSlotsByName(LabelDefinitionEditor);
    } // setupUi

    void retranslateUi(QDialog *LabelDefinitionEditor)
    {
        LabelDefinitionEditor->setWindowTitle(QApplication::translate("LabelDefinitionEditor", "Label Definition Editor", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LabelDefinitionEditor", "Label Name:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("LabelDefinitionEditor", "Label Properties", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LabelDefinitionEditor", "Paper Size:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("LabelDefinitionEditor", "Columns:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("LabelDefinitionEditor", "Rows:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("LabelDefinitionEditor", "Width:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("LabelDefinitionEditor", "Height:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("LabelDefinitionEditor", "Offset X:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("LabelDefinitionEditor", "Offset Y:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("LabelDefinitionEditor", "Horizontal Gap:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("LabelDefinitionEditor", "Vertical Gap:", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("LabelDefinitionEditor", "Cancel", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("LabelDefinitionEditor", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LabelDefinitionEditor: public Ui_LabelDefinitionEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELDEFINITIONEDITOR_H
