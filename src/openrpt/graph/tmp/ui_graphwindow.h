/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2012 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
*/

/********************************************************************************
** Form generated from reading UI file 'graphwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHWINDOW_H
#define UI_GRAPHWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "graph.h"

QT_BEGIN_NAMESPACE

class Ui_GraphWindow
{
public:
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QFrame *_graphFrame;
    QHBoxLayout *hboxLayout1;
    Graph *_graph;
    QVBoxLayout *vboxLayout1;
    QGroupBox *_gbLabel;
    QGridLayout *gridLayout;
    QLabel *_dataLabel;
    QLabel *_titleLabel;
    QLabel *_valueLabel;
    QLineEdit *_titleEdit;
    QLineEdit *_dataEdit;
    QLineEdit *_valueEdit;
    QGroupBox *_gbPadding;
    QGridLayout *gridLayout1;
    QLabel *_vPadLabel;
    QLabel *_hPadLabel;
    QSpinBox *_hPadSpinbox;
    QSpinBox *_vPadSpinbox;
    QGroupBox *_gbValueRange;
    QGridLayout *gridLayout2;
    QLabel *_maxValueLabel;
    QLabel *_minValueLabel;
    QSpinBox *_minValueSpinbox;
    QSpinBox *_maxValueSpinbox;
    QPushButton *_btnClear;
    QGroupBox *_styleGroup;
    QHBoxLayout *hboxLayout2;
    QCheckBox *_cbBars;
    QCheckBox *_cbLines;
    QCheckBox *_cbPoints;
    QHBoxLayout *hboxLayout3;
    QLabel *_numSetLabel;
    QSpinBox *_numSetSpinbox;
    QLabel *_numRefLabel;
    QSpinBox *_numRefSpinbox;
    QHBoxLayout *hboxLayout4;
    QTableWidget *_labelTable;
    QTableWidget *_dataTable;
    QGroupBox *_gbSql;
    QHBoxLayout *hboxLayout5;
    QTextEdit *_editSql;
    QVBoxLayout *vboxLayout2;
    QSpacerItem *spacerItem;
    QPushButton *_btnSql;

    void setupUi(QMainWindow *GraphWindow)
    {
        if (GraphWindow->objectName().isEmpty())
            GraphWindow->setObjectName(QString::fromUtf8("GraphWindow"));
        GraphWindow->resize(677, 763);
        widget = new QWidget(GraphWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        vboxLayout = new QVBoxLayout(widget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        _graphFrame = new QFrame(widget);
        _graphFrame->setObjectName(QString::fromUtf8("_graphFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(_graphFrame->sizePolicy().hasHeightForWidth());
        _graphFrame->setSizePolicy(sizePolicy);
        _graphFrame->setFrameShape(QFrame::Box);
        _graphFrame->setFrameShadow(QFrame::Plain);
        _graphFrame->setLineWidth(2);
        hboxLayout1 = new QHBoxLayout(_graphFrame);
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(2, 2, 2, 2);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        _graph = new Graph(_graphFrame);
        _graph->setObjectName(QString::fromUtf8("_graph"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_graph->sizePolicy().hasHeightForWidth());
        _graph->setSizePolicy(sizePolicy1);
        _graph->setMinimumSize(QSize(0, 0));

        hboxLayout1->addWidget(_graph);


        hboxLayout->addWidget(_graphFrame);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        _gbLabel = new QGroupBox(widget);
        _gbLabel->setObjectName(QString::fromUtf8("_gbLabel"));
        gridLayout = new QGridLayout(_gbLabel);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _dataLabel = new QLabel(_gbLabel);
        _dataLabel->setObjectName(QString::fromUtf8("_dataLabel"));
        _dataLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_dataLabel, 1, 0, 1, 1);

        _titleLabel = new QLabel(_gbLabel);
        _titleLabel->setObjectName(QString::fromUtf8("_titleLabel"));
        _titleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_titleLabel, 0, 0, 1, 1);

        _valueLabel = new QLabel(_gbLabel);
        _valueLabel->setObjectName(QString::fromUtf8("_valueLabel"));
        _valueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(_valueLabel, 2, 0, 1, 1);

        _titleEdit = new QLineEdit(_gbLabel);
        _titleEdit->setObjectName(QString::fromUtf8("_titleEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(_titleEdit->sizePolicy().hasHeightForWidth());
        _titleEdit->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(_titleEdit, 0, 1, 1, 1);

        _dataEdit = new QLineEdit(_gbLabel);
        _dataEdit->setObjectName(QString::fromUtf8("_dataEdit"));
        sizePolicy2.setHeightForWidth(_dataEdit->sizePolicy().hasHeightForWidth());
        _dataEdit->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(_dataEdit, 1, 1, 1, 1);

        _valueEdit = new QLineEdit(_gbLabel);
        _valueEdit->setObjectName(QString::fromUtf8("_valueEdit"));
        sizePolicy2.setHeightForWidth(_valueEdit->sizePolicy().hasHeightForWidth());
        _valueEdit->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(_valueEdit, 2, 1, 1, 1);


        vboxLayout1->addWidget(_gbLabel);

        _gbPadding = new QGroupBox(widget);
        _gbPadding->setObjectName(QString::fromUtf8("_gbPadding"));
        gridLayout1 = new QGridLayout(_gbPadding);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        _vPadLabel = new QLabel(_gbPadding);
        _vPadLabel->setObjectName(QString::fromUtf8("_vPadLabel"));
        _vPadLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(_vPadLabel, 1, 0, 1, 1);

        _hPadLabel = new QLabel(_gbPadding);
        _hPadLabel->setObjectName(QString::fromUtf8("_hPadLabel"));
        _hPadLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(_hPadLabel, 0, 0, 1, 1);

        _hPadSpinbox = new QSpinBox(_gbPadding);
        _hPadSpinbox->setObjectName(QString::fromUtf8("_hPadSpinbox"));
        sizePolicy2.setHeightForWidth(_hPadSpinbox->sizePolicy().hasHeightForWidth());
        _hPadSpinbox->setSizePolicy(sizePolicy2);
        _hPadSpinbox->setValue(5);

        gridLayout1->addWidget(_hPadSpinbox, 0, 1, 1, 1);

        _vPadSpinbox = new QSpinBox(_gbPadding);
        _vPadSpinbox->setObjectName(QString::fromUtf8("_vPadSpinbox"));
        sizePolicy2.setHeightForWidth(_vPadSpinbox->sizePolicy().hasHeightForWidth());
        _vPadSpinbox->setSizePolicy(sizePolicy2);
        _vPadSpinbox->setValue(5);

        gridLayout1->addWidget(_vPadSpinbox, 1, 1, 1, 1);


        vboxLayout1->addWidget(_gbPadding);

        _gbValueRange = new QGroupBox(widget);
        _gbValueRange->setObjectName(QString::fromUtf8("_gbValueRange"));
        gridLayout2 = new QGridLayout(_gbValueRange);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        _maxValueLabel = new QLabel(_gbValueRange);
        _maxValueLabel->setObjectName(QString::fromUtf8("_maxValueLabel"));
        _maxValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(_maxValueLabel, 0, 0, 1, 1);

        _minValueLabel = new QLabel(_gbValueRange);
        _minValueLabel->setObjectName(QString::fromUtf8("_minValueLabel"));
        _minValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(_minValueLabel, 1, 0, 1, 1);

        _minValueSpinbox = new QSpinBox(_gbValueRange);
        _minValueSpinbox->setObjectName(QString::fromUtf8("_minValueSpinbox"));
        sizePolicy2.setHeightForWidth(_minValueSpinbox->sizePolicy().hasHeightForWidth());
        _minValueSpinbox->setSizePolicy(sizePolicy2);
        _minValueSpinbox->setMinimum(-999);
        _minValueSpinbox->setMaximum(0);

        gridLayout2->addWidget(_minValueSpinbox, 1, 1, 1, 1);

        _maxValueSpinbox = new QSpinBox(_gbValueRange);
        _maxValueSpinbox->setObjectName(QString::fromUtf8("_maxValueSpinbox"));
        sizePolicy2.setHeightForWidth(_maxValueSpinbox->sizePolicy().hasHeightForWidth());
        _maxValueSpinbox->setSizePolicy(sizePolicy2);
        _maxValueSpinbox->setMinimum(1);
        _maxValueSpinbox->setMaximum(999999);
        _maxValueSpinbox->setValue(100);

        gridLayout2->addWidget(_maxValueSpinbox, 0, 1, 1, 1);


        vboxLayout1->addWidget(_gbValueRange);

        _btnClear = new QPushButton(widget);
        _btnClear->setObjectName(QString::fromUtf8("_btnClear"));

        vboxLayout1->addWidget(_btnClear);


        hboxLayout->addLayout(vboxLayout1);


        vboxLayout->addLayout(hboxLayout);

        _styleGroup = new QGroupBox(widget);
        _styleGroup->setObjectName(QString::fromUtf8("_styleGroup"));
        hboxLayout2 = new QHBoxLayout(_styleGroup);
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(11, 11, 11, 11);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        _cbBars = new QCheckBox(_styleGroup);
        _cbBars->setObjectName(QString::fromUtf8("_cbBars"));
        _cbBars->setChecked(true);

        hboxLayout2->addWidget(_cbBars);

        _cbLines = new QCheckBox(_styleGroup);
        _cbLines->setObjectName(QString::fromUtf8("_cbLines"));

        hboxLayout2->addWidget(_cbLines);

        _cbPoints = new QCheckBox(_styleGroup);
        _cbPoints->setObjectName(QString::fromUtf8("_cbPoints"));

        hboxLayout2->addWidget(_cbPoints);


        vboxLayout->addWidget(_styleGroup);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        _numSetLabel = new QLabel(widget);
        _numSetLabel->setObjectName(QString::fromUtf8("_numSetLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(_numSetLabel->sizePolicy().hasHeightForWidth());
        _numSetLabel->setSizePolicy(sizePolicy3);
        _numSetLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout3->addWidget(_numSetLabel);

        _numSetSpinbox = new QSpinBox(widget);
        _numSetSpinbox->setObjectName(QString::fromUtf8("_numSetSpinbox"));
        _numSetSpinbox->setMinimum(1);

        hboxLayout3->addWidget(_numSetSpinbox);

        _numRefLabel = new QLabel(widget);
        _numRefLabel->setObjectName(QString::fromUtf8("_numRefLabel"));
        sizePolicy3.setHeightForWidth(_numRefLabel->sizePolicy().hasHeightForWidth());
        _numRefLabel->setSizePolicy(sizePolicy3);
        _numRefLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout3->addWidget(_numRefLabel);

        _numRefSpinbox = new QSpinBox(widget);
        _numRefSpinbox->setObjectName(QString::fromUtf8("_numRefSpinbox"));
        _numRefSpinbox->setMinimum(1);

        hboxLayout3->addWidget(_numRefSpinbox);


        vboxLayout->addLayout(hboxLayout3);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        _labelTable = new QTableWidget(widget);
        if (_labelTable->columnCount() < 1)
            _labelTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        _labelTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        _labelTable->setObjectName(QString::fromUtf8("_labelTable"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(_labelTable->sizePolicy().hasHeightForWidth());
        _labelTable->setSizePolicy(sizePolicy4);
        _labelTable->setMinimumSize(QSize(80, 0));

        hboxLayout4->addWidget(_labelTable);

        _dataTable = new QTableWidget(widget);
        _dataTable->setObjectName(QString::fromUtf8("_dataTable"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(_dataTable->sizePolicy().hasHeightForWidth());
        _dataTable->setSizePolicy(sizePolicy5);

        hboxLayout4->addWidget(_dataTable);


        vboxLayout->addLayout(hboxLayout4);

        _gbSql = new QGroupBox(widget);
        _gbSql->setObjectName(QString::fromUtf8("_gbSql"));
        _gbSql->setEnabled(false);
        hboxLayout5 = new QHBoxLayout(_gbSql);
        hboxLayout5->setSpacing(6);
        hboxLayout5->setContentsMargins(11, 11, 11, 11);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        _editSql = new QTextEdit(_gbSql);
        _editSql->setObjectName(QString::fromUtf8("_editSql"));

        hboxLayout5->addWidget(_editSql);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacerItem);

        _btnSql = new QPushButton(_gbSql);
        _btnSql->setObjectName(QString::fromUtf8("_btnSql"));

        vboxLayout2->addWidget(_btnSql);


        hboxLayout5->addLayout(vboxLayout2);


        vboxLayout->addWidget(_gbSql);

        GraphWindow->setCentralWidget(widget);
#ifndef QT_NO_SHORTCUT
        _dataLabel->setBuddy(_dataEdit);
        _titleLabel->setBuddy(_titleEdit);
        _valueLabel->setBuddy(_valueEdit);
        _vPadLabel->setBuddy(_vPadSpinbox);
        _hPadLabel->setBuddy(_hPadSpinbox);
        _maxValueLabel->setBuddy(_maxValueSpinbox);
        _minValueLabel->setBuddy(_minValueSpinbox);
        _numSetLabel->setBuddy(_numSetSpinbox);
        _numRefLabel->setBuddy(_numRefSpinbox);
#endif // QT_NO_SHORTCUT

        retranslateUi(GraphWindow);
        QObject::connect(_hPadSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setHPadding(int)));
        QObject::connect(_vPadSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setVPadding(int)));
        QObject::connect(_titleEdit, SIGNAL(textChanged(QString)), _graph, SLOT(setTitle(QString)));
        QObject::connect(_dataEdit, SIGNAL(textChanged(QString)), _graph, SLOT(setDataLabel(QString)));
        QObject::connect(_valueEdit, SIGNAL(textChanged(QString)), _graph, SLOT(setValueLabel(QString)));
        QObject::connect(_maxValueSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setMaxValue(int)));
        QObject::connect(_minValueSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setMinValue(int)));
        QObject::connect(_cbBars, SIGNAL(toggled(bool)), _graph, SLOT(setDrawBars(bool)));
        QObject::connect(_cbLines, SIGNAL(toggled(bool)), _graph, SLOT(setDrawLines(bool)));
        QObject::connect(_cbPoints, SIGNAL(toggled(bool)), _graph, SLOT(setDrawPoints(bool)));

        QMetaObject::connectSlotsByName(GraphWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GraphWindow)
    {
        GraphWindow->setWindowTitle(QApplication::translate("GraphWindow", "Graph Window", 0, QApplication::UnicodeUTF8));
        _gbLabel->setTitle(QApplication::translate("GraphWindow", "Labels", 0, QApplication::UnicodeUTF8));
        _dataLabel->setText(QApplication::translate("GraphWindow", "Data:", 0, QApplication::UnicodeUTF8));
        _titleLabel->setText(QApplication::translate("GraphWindow", "Title:", 0, QApplication::UnicodeUTF8));
        _valueLabel->setText(QApplication::translate("GraphWindow", "Value:", 0, QApplication::UnicodeUTF8));
        _gbPadding->setTitle(QApplication::translate("GraphWindow", "Padding (in pixels)", 0, QApplication::UnicodeUTF8));
        _vPadLabel->setText(QApplication::translate("GraphWindow", "Vertical:", 0, QApplication::UnicodeUTF8));
        _hPadLabel->setText(QApplication::translate("GraphWindow", "Horizontal:", 0, QApplication::UnicodeUTF8));
        _gbValueRange->setTitle(QApplication::translate("GraphWindow", "Value Range", 0, QApplication::UnicodeUTF8));
        _maxValueLabel->setText(QApplication::translate("GraphWindow", "Max:", 0, QApplication::UnicodeUTF8));
        _minValueLabel->setText(QApplication::translate("GraphWindow", "Min:", 0, QApplication::UnicodeUTF8));
        _btnClear->setText(QApplication::translate("GraphWindow", "Clear All", 0, QApplication::UnicodeUTF8));
        _styleGroup->setTitle(QApplication::translate("GraphWindow", "Graph Style", 0, QApplication::UnicodeUTF8));
        _cbBars->setText(QApplication::translate("GraphWindow", "Bars", 0, QApplication::UnicodeUTF8));
        _cbLines->setText(QApplication::translate("GraphWindow", "Lines", 0, QApplication::UnicodeUTF8));
        _cbPoints->setText(QApplication::translate("GraphWindow", "Points", 0, QApplication::UnicodeUTF8));
        _numSetLabel->setText(QApplication::translate("GraphWindow", "Number of Sets:", 0, QApplication::UnicodeUTF8));
        _numRefLabel->setText(QApplication::translate("GraphWindow", "Number of References:", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = _labelTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("GraphWindow", "Label", 0, QApplication::UnicodeUTF8));
        _gbSql->setTitle(QApplication::translate("GraphWindow", "Populate with SQL", 0, QApplication::UnicodeUTF8));
        _btnSql->setText(QApplication::translate("GraphWindow", "Execute", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GraphWindow: public Ui_GraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHWINDOW_H
